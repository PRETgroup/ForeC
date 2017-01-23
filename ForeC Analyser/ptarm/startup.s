
        .text
start: 
		cdp		p13, 0, cr1, cr0, cr0	@ Get thread ID
		ldr     r2, =4					@ Set r2 to the value 4.
        mul 	r1, r2, r1          	@ Set r1 to thread_id * 4
		ldr     r2, =0xfff0 			@ Set r2 to the first boot loader lr.
		add		r0,	r1, r2				@ Boot loader lr + thread_id * 4.
        str     lr, [r0]				@ Store lr into the address of r0.

        # Initiate bss section
        ldr     r0, =bss_start        	@ Get bss addresses from the linker script
        ldr     r1, =bss_end
        ldr     r2, =bss_size
        
        cmp     r2, #0
        beq     skip_bss
        mov     r4, #0					@ Set r4 to the value 0.
bss_loop:
        strb    r4, [r0], #1			@ Set the bss section to 0.
        subs    r2, r2, #1
        bne     bss_loop        
skip_bss:
        # Initate the stack
        cdp		p13, 0, cr1, cr0, cr0	@ Get thread ID
		ldr     sp, =0xffdc				@ Load the address of the stack pointer.
stack_setup:
		cmp		r1, #0					@ If thread ID is now 0, go to the main function.
		beq		stack_setup_complete
		sub		sp, sp, #0x400			@ Give each PTARM hardware thread 4 kilobytes of stack.
		sub		r1, r1, #1				@ Decrement the thread ID
		b		stack_setup				@ Keep decrementing the stack pointer.
		
stack_setup_complete:		
        # Jump to the C main function
        bl      main

        # Return to the bootloader
		cdp 	p13, 0, cr1, cr0, cr0	@ Get thread ID
		ldr     r2, =4					@ Set r2 to the value 4.
        mul 	r1, r2, r1          	@ Set r1 to thread_id * 4
		ldr     r2, =0xfff0				@ Set r2 to the first boot loader lr.
		add		r0,	r1, r2				@ Boot loader lr + thread_id * 4.
        ldr     r1, [r0]				@ Load boot loader lr from the address of r0.
		mov 	pc, r1					@ Go to r1
