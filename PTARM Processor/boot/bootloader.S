# ***************************************************
# PTARM Bootloader
# By David Broman 2012
# ***************************************************

.set    ENABLE_ALL, 0        
# ===================================================
# Definitions
# ===================================================
# I/O memory mapped addresses
.equ    LEDG,  0xFFFFFF00
.equ    LEDR,  0xFFFFFF09

.equ	HEX0,  0xFFFFFF20
.equ	HEX1,  0xFFFFFF28
.equ	HEX2,  0xFFFFFF30
.equ	HEX3,  0xFFFFFF38
.equ	HEX4,  0xFFFFFF40
.equ	HEX5,  0xFFFFFF48
.equ	HEX6,  0xFFFFFF50
.equ	HEX7,  0xFFFFFF58

.equ	LCD,   0xFFFFFF60

.equ    UART_CIN,  0xFFFF0000
.equ    UART_DIN,  0xFFFF0004
.equ    UART_COUT, 0xFFFF0008
.equ    UART_DOUT, 0xFFFF000C

# Program memory addresses
.equ    CODE_SPM_ADDR,   0x00000000
.equ    EXCEP_TBL_ADDR,  0x0001FFE0
.equ	PROG_LOADED,	 EXCEP_TBL_ADDR @ temporarily use this memory location for thread communicationn when program loaded
.equ    BOOTROM_ADDR,    0xFFFE0000

		
	   
# ===================================================
# Macros
# ===================================================

# gettime (gt)
.macro gt a, b
		cdp p13, 8, c0, \a, \b
.endm

# delayuntil (du)
.macro du a, b        
		cdp p13, 4, c0, \a, \b
.endm

# reset instruction and cycle count (ricc)
.macro ricc
		cdp 13, 15, cr0, cr0, cr0, 0
.endm        

# get instruction and cycle count (gicc)
.macro gicc a, b
		cdp 13, 15, cr0, \a, \b, 1
.endm        

# get thread ID (gtid)
.macro gtid a
		cdp p13, 0, \a, cr0, cr0
.endm      
		
# ===================================================
# ARM excecption vector
# ===================================================
		.section "vectors"

reset:  b       boot           
undef:  b       infloop
swi:    b       infloop
pabt:   b       infloop
dabt:   b       infloop
		nop
irq:    b       infloop
fiq:    b       infloop

# ===================================================
# Exception on expire. PTARM exception extension
# ===================================================
eoe: 
		nop		@ temp fix for multi cycle instruction being interrupted and executing another multi cycle instruction in EOE causing random write
		push	{lr}
		push	{r1}
		push	{r2}
		gtid	cr1
		ldr     r2, =4
		mul 	r1, r2, r1          	@ Should be get_thread_id * 4
		ldr     r2, =EXCEP_TBL_ADDR 
		add		lr,	r1, r2
		pop		{r2}
		pop		{r1}
		ldr     pc, [lr]
		

# ===================================================
# Start of the bootloader code.         
# ===================================================
		.text
boot:	
		# initalise
		ldr     r2, =PROG_LOADED  		@ thread start
		ldr     r3, =0                    
		strb    r3, [r2]                @ program loaded is set to false
		# get thread ID
		gtid	cr5
		cmp		r5, #0
		# if thread0, continue to boot loader
		beq		uart_loader_start
		# else wait until given pc
wait_until_loaded:
		ldrb	r4, [r2] 
		cmp		r4, #0
		beq		wait_until_loaded
		mov     lr, pc                  @ Save pc manually. Absolute addr.
		ldr     pc, =CODE_SPM_ADDR      @ Note that we get PC+8 beause of how
										@ how ARM is defined.
		b 		boot
		
infloop:
		b       infloop
	

# ===================================================
# UART program loader
# ===================================================
		.equ    UART_TIMEOUT, 892857	@ timeout ~ 500 ms on 50Mhz. 
										@ Calculated as 500ms/(7 instructions * 80ns thread cycle)

		
# Text string sent when the system boots up.
start_msg: .string   "PTARM 50Mhz Eugene 24 June 2016\r\n"
end_msg: 
		
# Magic string used for determining that a program has terminated.
terminate_magic:
		.byte   0xff, 0x07, 0xa1, 0x73
		.align        

uart_loader_start:

		# Setup UART registers
		bl      uart_setup
		
		# Print out welcome message to UART
		ldr     r2,=end_msg-start_msg-1 @Length, excluding zero termination
		ldr     r3,=start_msg + BOOTROM_ADDR
		bl      uart_send_seq

		# Turn off LEDs
		bl      turn_off_leds
		
restart_loader:       
		
start_command_loop:
		# Wait for start command (0xff). Echo if other char.
		# Light up the LED in a round-robin fashion.
		ldr     r2, =LEDR           	@ LED memory mapped address
		ldr     r3, =1                  @ LED display
wait_command_loop:      
		str     r3, [r2]                @ Light up the LED
		mov     r3, r3, lsl #1          @ Next LED light
		tst     r3, #0b10000            @ Check if round robin restart
		movne   r3, #1

		ldr     r1, =UART_TIMEOUT
		bl      uart_receive_byte       @ Read a byte
		cmp     r1, #0
		beq     wait_command_loop       @ Restart if timeout
		cmp     r0, #0xff               @ Check if start command
		beq     send_ready_command
		ldr     r1, =UART_TIMEOUT
		bl      uart_send_byte          @ Echo if not start command        
		b       start_command_loop

		
		# Send ready to send command (0xfe).
send_ready_command:
		ldr     r0, =0xfe
		ldr     r1, =UART_TIMEOUT
		bl      uart_send_byte
		cmp     r1, #0        
		beq     restart_loader

		# Receive program size (4 bytes, big-endian)
		ldr     r2, =0                  @ Target register for the size
		ldr     r3, =24                 @ Start to shift 24 bits
receive_size_loop:
		ldr     r1, =UART_TIMEOUT
		bl      uart_receive_byte
		cmp     r1, #0        
		beq     restart_loader
		orr     r2, r2, r0, lsl r3      @ Mask the bits with shifted val
		subs    r3, r3, #8              @ Shift 8 bits less
		bpl     receive_size_loop

		# Receive program 
		ldr     r3, =CODE_SPM_ADDR
receive_prog_loop:
		ldr     r1, =UART_TIMEOUT
		bl      uart_receive_byte
		cmp     r1, #0
		beq     restart_loader
		strb    r0, [r3], #1            @ Move one byte and post increment r3
		subs    r2, r2, #1
		bne     receive_prog_loop
				
		# Turn off LEDs
		bl      turn_off_leds
	   
		# signal done loading
		ldr     r5, =PROG_LOADED  		@ thread start
		ldr     r6, =1                    
		strb    r6, [r5]                @ 1
	   
		# Reset instruction and cycle counter
		ricc
		
		# Branch and link to the program
		mov     lr, pc                  @ Save pc manually. Absolute addr.
		ldr     pc, =CODE_SPM_ADDR      @ Note that we get PC+8 beause of how
										@ how ARM is defined.

		# Get values from instruction and cycle counter
		gicc    cr4, cr5
		sub     r4, r4, #2              @ Do not count the branching to the program
		sub     r5, r5, #2
		
		# Setup UART registers 
		bl      uart_setup
		
		# Send program termination magic
		ldr     r2, =4
		ldr     r3, =terminate_magic + BOOTROM_ADDR
		bl      uart_send_seq

		# Send the instruction count as 4 bytes (big-endian)
		mov     r2, r4
		bl      uart_send_word

		# Send the cycle count as 4 bytes (big-endian)
		mov     r2, r5
		bl      uart_send_word
		
		# Restart loader
		b       restart_loader

# Function: Send a sequence of bytes
# Input:
#         r2 = Length in bytes
#         r3 = Adress to the data sequence        
#         r8-r11 = UART addresses
# Output: Nothing        
#         r6 = Affected        
#         r7 = Affected        
uart_send_seq:
		mov     r6, lr
send_loop:      
		ldrb    r0, [r3], #1
		ldr     r1, =UART_TIMEOUT
		bl      uart_send_byte
		cmp     r1, #0
		beq     restart_loader
		subs    r2, r2, #1
		bne     send_loop
		mov     pc, r6

# Function: Send a word in big-endian format
# Input:  r2 = word to be sent        
#         r8-r11 = UART addresses
# Output: Nothing        
#         r0, r1, r3, r6 = Affected        
uart_send_word:
		mov     r6, lr
		ldr     r3, =24
send_word_loop: 
		mov     r0, r2, lsr r3
		and     r0, r0, #0xff
		ldr     r1, =UART_TIMEOUT
		bl      uart_send_byte
		cmp     r1, #0
		beq     restart_loader
		subs    r3, r3, #8             
		bpl     send_word_loop
		mov     pc, r6
		
	
# Function: Setup UART variables
# Input:  Nothing
# Output: 
#         r8  = UART_CIN, 0xFFFF0000
#         r9  = UART_DIN, 0xFFFF0004
#         r10 = UART_COUT, 0xFFFF0008
#         r11 = UART_DOUT, 0xFFFF000C
uart_setup:
		ldr     r8, =UART_CIN
		ldr     r9, =UART_DIN
		ldr     r10, =UART_COUT
		ldr     r11, =UART_DOUT
		mov     pc, lr

		
# Function: Sending one byte to UART
# Input:  r0 = byte to send
#         r1 = timeout in milli seconds
#         r8-r11 = UART addresses
#         r7     = Affected        
# Output:
#         r1 = 0 if timed out       
uart_send_byte:
		ldrb    r7, [r10]
		cmp     r7, #0
		streqb  r0, [r11]
		moveq   pc, lr
		subs    r1, r1, #1
		bne     uart_send_byte
		mov     pc, lr
		
# Function: Receive one byte qfrom UART
# Input:  r1 = timeout in milli seconds        
#         r8-r11 = UART addresses
# Output: r0 = reveived byte
#         r1 = 0 if timed out
#         r7 = affected
uart_receive_byte:
		ldrb    r7, [r8]
		cmp     r7, #1
		ldreqb  r0, [r9]
		moveq   pc, lr
		subs    r1, r1, #1
		bne     uart_receive_byte
		mov     pc, lr

# Function: Turn of the LEDs, HEXs, and LCD.
# Input: None
# Output: r0, r1 affected        
turn_off_leds:  
		ldr     r0, =0
		ldr     r1, =LEDR
		strb    r0, [r1]
		ldr     r1, =LEDG
		strb    r0, [r1]
		ldr     r0, =-1
		ldr     r1, =HEX0
		strb    r0, [r1]
		ldr     r1, =HEX1
		strb    r0, [r1]
		ldr     r1, =HEX2
		strb    r0, [r1]
		ldr     r1, =HEX3
		strb    r0, [r1]
		ldr     r1, =HEX4
		strb    r0, [r1]
		ldr     r1, =HEX5
		strb    r0, [r1]
		ldr     r1, =HEX6
		strb    r0, [r1]
		ldr     r1, =HEX7
		strb    r0, [r1]
		ldr     r0, =0
		ldr     r1, =LCD
		strb    r0, [r1]
		mov     pc, lr
			   

