
_build/io.elf:     file format elf32-littlearm

SYMBOL TABLE:
00000000 l    d  .text	00000000 .text
00001388 l    d  .rodata	00000000 .rodata
00001540 l    d  .text.memset	00000000 .text.memset
00001634 l    d  .data	00000000 .data
0000178c l    d  .bss	00000000 .bss
00000000 l    d  .ARM.attributes	00000000 .ARM.attributes
00000000 l    d  .comment	00000000 .comment
00000000 l    d  .debug_info	00000000 .debug_info
00000000 l    d  .debug_abbrev	00000000 .debug_abbrev
00000000 l    d  .debug_aranges	00000000 .debug_aranges
00000000 l    d  .debug_line	00000000 .debug_line
00000000 l    d  .debug_str	00000000 .debug_str
00000000 l    d  .debug_frame	00000000 .debug_frame
00000000 l    df *ABS*	00000000 _build/startup.o
00000000 l       .text	00000000 start
0000003c l       .text	00000000 skip_bss
00000030 l       .text	00000000 bss_loop
00000044 l       .text	00000000 stack_setup
00000058 l       .text	00000000 stack_setup_complete
00000000 l    df *ABS*	00000000 io.c
00000000 l    df *ABS*	00000000 _udivsi3.o
00001270 l       .text	00000000 .udivsi3_skip_div0_test
00000000 l    df *ABS*	00000000 _dvmd_tls.o
00000000 l    df *ABS*	00000000 memset.c
00000740 g     F .text	000001a8 ptarmCreateTask
0000178c g     O .bss	00000002 ptarmLcdCharCount
000006ec g     F .text	00000054 foreMcGetIndex
00000278 g     F .text	0000013c ptarmLcdOutputStr
00001690 g     O .data	00000054 two
000003b4 g     F .text	0000004c ptarmUartOutputChar
000017e0 g       .bss	00000000 addr_stack_limit
00001798 g     O .bss	0000003c globalScheduler
00000400 g     F .text	0000004c ptarmUartOutputStr
00001270 g     F .text	000000f4 .hidden __udivsi3
00001634 g     O .data	00000004 ptarmPreviousTaskStackEnd
0000044c g     F .text	00000114 itoa
0000008c g     F .text	0000003c ptarmLedOutput
00000560 g     F .text	000000e4 utoa
000017e0 g       .bss	00000000 bss_end
00000054 g       *ABS*	00000000 bss_size
0000178c g       .data	00000000 bss_start
000000c8 g     F .text	0000004c ptarmSevenSegOutput
00001384  w    F .text	00000004 .hidden __aeabi_ldiv0
00001540 g     F .text.memset	000000f4 memset
000008e8 g     F .text	00000988 main
000017d4 g     O .bss	0000000c ptarmStringBuffer
000001a8 g     F .text	00000084 ptarmLcdOutput
00001270 g     F .text	00000000 .hidden __aeabi_uidiv
00001639 g     O .data	00000001 loopForever
0001efdc g       *ABS*	00000000 addr_stack_end
00001388 g     O .rodata	00000010 hexMap
0000163c g     O .data	00000054 one
0001ffe0 g       *ABS*	00000000 eoe_table
00001364 g     F .text	00000020 .hidden __aeabi_uidivmod
00001638 g     O .data	00000001 halt
00000644 g     F .text	000000a8 hex
00001384  w    F .text	00000004 .hidden __aeabi_idiv0
00001790 g     O .bss	00000008 nullTime
0000022c g     F .text	0000004c ptarmLcdInit
000016e4 g     O .data	00000054 three
00000114 g     F .text	00000094 ptarmSevenSegChar
00001738 g     O .data	00000054 four
0001ffdc g       *ABS*	00000000 addr_stack_start



Disassembly of section .text:

00000000 <start>:
       0:	ee001d00 	cdp	13, 0, cr1, cr0, cr0, {0}
       4:	e3a02004 	mov	r2, #4, 0
       8:	e0010192 	mul	r1, r2, r1
       c:	e59f2064 	ldr	r2, [pc, #100]	; 78 <stack_setup_complete+0x20>
      10:	e0810002 	add	r0, r1, r2
      14:	e580e000 	str	lr, [r0]
      18:	e59f005c 	ldr	r0, [pc, #92]	; 7c <stack_setup_complete+0x24>
      1c:	e59f105c 	ldr	r1, [pc, #92]	; 80 <stack_setup_complete+0x28>
      20:	e59f205c 	ldr	r2, [pc, #92]	; 84 <stack_setup_complete+0x2c>
      24:	e3520000 	cmp	r2, #0, 0
      28:	0a000003 	beq	3c <skip_bss>
      2c:	e3a04000 	mov	r4, #0, 0

00000030 <bss_loop>:
      30:	e4c04001 	strb	r4, [r0], #1
      34:	e2522001 	subs	r2, r2, #1, 0
      38:	1afffffc 	bne	30 <bss_loop>

0000003c <skip_bss>:
      3c:	ee001d00 	cdp	13, 0, cr1, cr0, cr0, {0}
      40:	e59fd040 	ldr	sp, [pc, #64]	; 88 <stack_setup_complete+0x30>

00000044 <stack_setup>:
      44:	e3510000 	cmp	r1, #0, 0
      48:	0a000002 	beq	58 <stack_setup_complete>
      4c:	e24ddb01 	sub	sp, sp, #1024	; 0x400
      50:	e2411001 	sub	r1, r1, #1, 0
      54:	eafffffa 	b	44 <stack_setup>

00000058 <stack_setup_complete>:
      58:	eb000222 	bl	8e8 <main>
      5c:	ee001d00 	cdp	13, 0, cr1, cr0, cr0, {0}
      60:	e3a02004 	mov	r2, #4, 0
      64:	e0010192 	mul	r1, r2, r1
      68:	e59f2008 	ldr	r2, [pc, #8]	; 78 <stack_setup_complete+0x20>
      6c:	e0810002 	add	r0, r1, r2
      70:	e5901000 	ldr	r1, [r0]
      74:	e1a0f001 	mov	pc, r1
      78:	0001fff0 	.word	0x0001fff0
      7c:	0000178c 	.word	0x0000178c
      80:	000017e0 	.word	0x000017e0
      84:	00000054 	.word	0x00000054
      88:	0001ffdc 	.word	0x0001ffdc

0000008c <ptarmLedOutput>:
#define ptarmLedGreenOutput(bitPattern)	ptarmLedOutput(LEDG, bitPattern, LEDG_MASK)


// Outputs a bit pattern to an LED base address. Not a thread-safe function.
void ptarmLedOutput(const unsigned int LedBaseAddress, const unsigned int bitPattern, const unsigned int mask) {
      8c:	e92d0810 	push	{r4, fp}
      90:	e28db004 	add	fp, sp, #4, 0
      94:	e24dd010 	sub	sp, sp, #16, 0
      98:	e50b0008 	str	r0, [fp, #-8]
      9c:	e50b100c 	str	r1, [fp, #-12]
      a0:	e50b2010 	str	r2, [fp, #-16]
	// Memory mapped address for the LEDs.
	register unsigned int * const ptarmLed = (unsigned int * const) LedBaseAddress;
      a4:	e51b4008 	ldr	r4, [fp, #-8]
	*ptarmLed = mask & bitPattern;
      a8:	e51b2010 	ldr	r2, [fp, #-16]
      ac:	e51b300c 	ldr	r3, [fp, #-12]
      b0:	e0033002 	and	r3, r3, r2
      b4:	e5843000 	str	r3, [r4]
}
      b8:	e1a00000 	nop			; (mov r0, r0)
      bc:	e24bd004 	sub	sp, fp, #4, 0
      c0:	e8bd0810 	pop	{r4, fp}
      c4:	e1a0f00e 	mov	pc, lr

000000c8 <ptarmSevenSegOutput>:


//======================================================================
// PTARM 7-Segment display functions.
//======================================================================

// Maps lowercase characters to their 7-Segment bit patterns.
//								 0	   1     2     3     4     5     6	   7	 8	   9	 A	   B	 C	   D	 E	   F
const unsigned char hexMap[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};


// Outputs a bit pattern to a 7-segment display. Not a thread-safe function.
void ptarmSevenSegOutput(const unsigned int index, const unsigned int bitPattern) {
      c8:	e92d0810 	push	{r4, fp}
      cc:	e28db004 	add	fp, sp, #4, 0
      d0:	e24dd008 	sub	sp, sp, #8, 0
      d4:	e50b0008 	str	r0, [fp, #-8]
      d8:	e50b100c 	str	r1, [fp, #-12]
	// Memory mapped address for the 7-Segment.
	register unsigned char * const ptarmHex = (unsigned char * const) (HEX + (HEX_SIZE * index));
      dc:	e51b3008 	ldr	r3, [fp, #-8]
      e0:	e2833202 	add	r3, r3, #536870912	; 0x20000000
      e4:	e243301c 	sub	r3, r3, #28, 0
      e8:	e1a03183 	lsl	r3, r3, #3
      ec:	e1a04003 	mov	r4, r3
	*ptarmHex = HEX_MASK & bitPattern;
      f0:	e51b300c 	ldr	r3, [fp, #-12]
      f4:	e20330ff 	and	r3, r3, #255, 0	; 0xff
      f8:	e203307f 	and	r3, r3, #127, 0	; 0x7f
      fc:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     100:	e5c43000 	strb	r3, [r4]
}
     104:	e1a00000 	nop			; (mov r0, r0)
     108:	e24bd004 	sub	sp, fp, #4, 0
     10c:	e8bd0810 	pop	{r4, fp}
     110:	e1a0f00e 	mov	pc, lr

00000114 <ptarmSevenSegChar>:


// Outputs a hexidecimal number to a 7-segment display. Not a thread-safe function.
void ptarmSevenSegChar(const unsigned int index, const unsigned char character) {
     114:	e92d4810 	push	{r4, fp, lr}
     118:	e28db008 	add	fp, sp, #8, 0
     11c:	e24dd00c 	sub	sp, sp, #12, 0
     120:	e50b0010 	str	r0, [fp, #-16]
     124:	e1a03001 	mov	r3, r1
     128:	e54b3011 	strb	r3, [fp, #-17]
	register unsigned int bitPattern = 0x7F;
     12c:	e3a0407f 	mov	r4, #127, 0	; 0x7f
	if ('/' < character && character < ':') {
     130:	e55b3011 	ldrb	r3, [fp, #-17]
     134:	e353002f 	cmp	r3, #47, 0	; 0x2f
     138:	9a000008 	bls	160 <ptarmSevenSegChar+0x4c>
     13c:	e55b3011 	ldrb	r3, [fp, #-17]
     140:	e3530039 	cmp	r3, #57, 0	; 0x39
     144:	8a000005 	bhi	160 <ptarmSevenSegChar+0x4c>
		// 0 - 9
		bitPattern = hexMap[character - '0' ];
     148:	e55b3011 	ldrb	r3, [fp, #-17]
     14c:	e2433030 	sub	r3, r3, #48, 0	; 0x30
     150:	e59f204c 	ldr	r2, [pc, #76]	; 1a4 <ptarmSevenSegChar+0x90>
     154:	e7d23003 	ldrb	r3, [r2, r3]
     158:	e1a04003 	mov	r4, r3
     15c:	ea00000a 	b	18c <ptarmSevenSegChar+0x78>
	} else if ('@' < character && character < 'G') {
     160:	e55b3011 	ldrb	r3, [fp, #-17]
     164:	e3530040 	cmp	r3, #64, 0	; 0x40
     168:	9a000007 	bls	18c <ptarmSevenSegChar+0x78>
     16c:	e55b3011 	ldrb	r3, [fp, #-17]
     170:	e3530046 	cmp	r3, #70, 0	; 0x46
     174:	8a000004 	bhi	18c <ptarmSevenSegChar+0x78>
		// A - F
		bitPattern = hexMap[character - 0x37];
     178:	e55b3011 	ldrb	r3, [fp, #-17]
     17c:	e2433037 	sub	r3, r3, #55, 0	; 0x37
     180:	e59f201c 	ldr	r2, [pc, #28]	; 1a4 <ptarmSevenSegChar+0x90>
     184:	e7d23003 	ldrb	r3, [r2, r3]
     188:	e1a04003 	mov	r4, r3
	}
	
	ptarmSevenSegOutput(index, bitPattern);
     18c:	e1a01004 	mov	r1, r4
     190:	e51b0010 	ldr	r0, [fp, #-16]
     194:	ebffffcb 	bl	c8 <ptarmSevenSegOutput>
}
     198:	e1a00000 	nop			; (mov r0, r0)
     19c:	e24bd008 	sub	sp, fp, #8, 0
     1a0:	e8bd8810 	pop	{r4, fp, pc}
     1a4:	00001388 	.word	0x00001388

000001a8 <ptarmLcdOutput>:


//======================================================================
// PTARM LCD display functions.
//======================================================================

// Track the number of characters that have been written to the LCD display.
unsigned short int ptarmLcdCharCount = 0;


// Output a command or datum to the LCD display.
#define ptarmLcdCommand(command)	ptarmLcdOutput(command, 0x0, 26000)
#define ptarmLcdChar(char)			ptarmLcdOutput(char, LCD_D, 80)

// Useful LCD commands.
#define ptarmLcdClear()				ptarmLcdCommand(0x00)
#define ptarmLcdGotoLineOne()		ptarmLcdCommand(0x80)
#define ptarmLcdGotoLineTwo()		ptarmLcdCommand(0xC0)

#define printfLcd(str)				ptarmLcdClear(); ptarmLcdCharCount = 0; ptarmLcdGotoLineOne(); ptarmLcdOutputStr(str)


// Outputs a command or datum to the LCD display. Not a thread-safe function.
void ptarmLcdOutput(const unsigned int bitPattern, const unsigned int isData, const unsigned int delay) {
     1a8:	e92d0810 	push	{r4, fp}
     1ac:	e28db004 	add	fp, sp, #4, 0
     1b0:	e24dd018 	sub	sp, sp, #24, 0
     1b4:	e50b0010 	str	r0, [fp, #-16]
     1b8:	e50b1014 	str	r1, [fp, #-20]
     1bc:	e50b2018 	str	r2, [fp, #-24]
	// Memory mapped addresses for the LCD.
	register unsigned int * const ptarmLcd = (unsigned int * const) LCD;
     1c0:	e3e0409f 	mvn	r4, #159, 0	; 0x9f
	*ptarmLcd = LCD_MASK & (LCD_EN | isData | LCD_ON | bitPattern);
     1c4:	e51b2014 	ldr	r2, [fp, #-20]
     1c8:	e51b3010 	ldr	r3, [fp, #-16]
     1cc:	e1823003 	orr	r3, r2, r3
     1d0:	e3c33c01 	bic	r3, r3, #256	; 0x100
     1d4:	e1a03a83 	lsl	r3, r3, #21
     1d8:	e1a03aa3 	lsr	r3, r3, #21
     1dc:	e3833c09 	orr	r3, r3, #2304	; 0x900
     1e0:	e5843000 	str	r3, [r4]
	
	int i = delay;
     1e4:	e51b3018 	ldr	r3, [fp, #-24]
     1e8:	e50b3008 	str	r3, [fp, #-8]
	while(--i);
     1ec:	e51b3008 	ldr	r3, [fp, #-8]
     1f0:	e2433001 	sub	r3, r3, #1, 0
     1f4:	e50b3008 	str	r3, [fp, #-8]
     1f8:	e51b3008 	ldr	r3, [fp, #-8]
     1fc:	e3530000 	cmp	r3, #0, 0
     200:	1afffff9 	bne	1ec <ptarmLcdOutput+0x44>
	
	*ptarmLcd = LCD_MASK & (LCD_ON | bitPattern);
     204:	e51b3010 	ldr	r3, [fp, #-16]
     208:	e3c33c01 	bic	r3, r3, #256	; 0x100
     20c:	e1a03a03 	lsl	r3, r3, #20
     210:	e1a03a23 	lsr	r3, r3, #20
     214:	e3833c01 	orr	r3, r3, #256	; 0x100
     218:	e5843000 	str	r3, [r4]
}
     21c:	e1a00000 	nop			; (mov r0, r0)
     220:	e24bd004 	sub	sp, fp, #4, 0
     224:	e8bd0810 	pop	{r4, fp}
     228:	e1a0f00e 	mov	pc, lr

0000022c <ptarmLcdInit>:


// Initialises the LCD display. Not a thread-safe function.
void ptarmLcdInit(void) {
     22c:	e92d4800 	push	{fp, lr}
     230:	e28db004 	add	fp, sp, #4, 0
	ptarmLcdCharCount = 0;
     234:	e59f3038 	ldr	r3, [pc, #56]	; 274 <ptarmLcdInit+0x48>
     238:	e3a02000 	mov	r2, #0, 0
     23c:	e5c32000 	strb	r2, [r3]
     240:	e5c32001 	strb	r2, [r3, #1]

	// Function set to 8-bits and 2 lines
	ptarmLcdOutput(0x0038, 0x0, 30000);
     244:	e3a02c75 	mov	r2, #29952	; 0x7500
     248:	e2822030 	add	r2, r2, #48, 0	; 0x30
     24c:	e3a01000 	mov	r1, #0, 0
     250:	e3a00038 	mov	r0, #56, 0	; 0x38
     254:	ebffffd3 	bl	1a8 <ptarmLcdOutput>
	
	// Turn on the display and turn off the cursor
	ptarmLcdCommand(0x000C);
     258:	e3a02c65 	mov	r2, #25856	; 0x6500
     25c:	e2822090 	add	r2, r2, #144, 0	; 0x90
     260:	e3a01000 	mov	r1, #0, 0
     264:	e3a0000c 	mov	r0, #12, 0
     268:	ebffffce 	bl	1a8 <ptarmLcdOutput>
}
     26c:	e1a00000 	nop			; (mov r0, r0)
     270:	e8bd8800 	pop	{fp, pc}
     274:	0000178c 	.word	0x0000178c

00000278 <ptarmLcdOutputStr>:


// Outputs a string to the LCD display. Not a thread-safe function.
void ptarmLcdOutputStr(const char *str) {
     278:	e92d4800 	push	{fp, lr}
     27c:	e28db004 	add	fp, sp, #4, 0
     280:	e24dd008 	sub	sp, sp, #8, 0
     284:	e50b0008 	str	r0, [fp, #-8]
	while (*str != NULL) {
     288:	ea000041 	b	394 <ptarmLcdOutputStr+0x11c>
		// Check for the newline character
		if (*str == '\n') {
     28c:	e51b3008 	ldr	r3, [fp, #-8]
     290:	e5d33000 	ldrb	r3, [r3]
     294:	e353000a 	cmp	r3, #10, 0
     298:	1a00000d 	bne	2d4 <ptarmLcdOutputStr+0x5c>
			ptarmLcdCharCount = (1 + (ptarmLcdCharCount > LCD_LEN)) * LCD_LEN;
     29c:	e59f310c 	ldr	r3, [pc, #268]	; 3b0 <ptarmLcdOutputStr+0x138>
     2a0:	e5d32000 	ldrb	r2, [r3]
     2a4:	e5d33001 	ldrb	r3, [r3, #1]
     2a8:	e1823403 	orr	r3, r2, r3, lsl #8
     2ac:	e353000f 	cmp	r3, #15, 0
     2b0:	9a000001 	bls	2bc <ptarmLcdOutputStr+0x44>
     2b4:	e3a0301e 	mov	r3, #30, 0
     2b8:	ea000000 	b	2c0 <ptarmLcdOutputStr+0x48>
     2bc:	e3a0300f 	mov	r3, #15, 0
     2c0:	e59f20e8 	ldr	r2, [pc, #232]	; 3b0 <ptarmLcdOutputStr+0x138>
     2c4:	e5c23000 	strb	r3, [r2]
     2c8:	e1a03443 	asr	r3, r3, #8
     2cc:	e5c23001 	strb	r3, [r2, #1]
     2d0:	ea000010 	b	318 <ptarmLcdOutputStr+0xa0>
		} else {
			ptarmLcdChar(*str);
     2d4:	e51b3008 	ldr	r3, [fp, #-8]
     2d8:	e5d33000 	ldrb	r3, [r3]
     2dc:	e3a02050 	mov	r2, #80, 0	; 0x50
     2e0:	e3a01b01 	mov	r1, #1024	; 0x400
     2e4:	e1a00003 	mov	r0, r3
     2e8:	ebffffae 	bl	1a8 <ptarmLcdOutput>
			ptarmLcdCharCount++;
     2ec:	e59f30bc 	ldr	r3, [pc, #188]	; 3b0 <ptarmLcdOutputStr+0x138>
     2f0:	e5d32000 	ldrb	r2, [r3]
     2f4:	e5d33001 	ldrb	r3, [r3, #1]
     2f8:	e1823403 	orr	r3, r2, r3, lsl #8
     2fc:	e2833001 	add	r3, r3, #1, 0
     300:	e1a03803 	lsl	r3, r3, #16
     304:	e1a03823 	lsr	r3, r3, #16
     308:	e59f20a0 	ldr	r2, [pc, #160]	; 3b0 <ptarmLcdOutputStr+0x138>
     30c:	e5c23000 	strb	r3, [r2]
     310:	e1a03443 	asr	r3, r3, #8
     314:	e5c23001 	strb	r3, [r2, #1]
		}
		str++;
     318:	e51b3008 	ldr	r3, [fp, #-8]
     31c:	e2833001 	add	r3, r3, #1, 0
     320:	e50b3008 	str	r3, [fp, #-8]
		
		if (ptarmLcdCharCount == LCD_LEN) {
     324:	e59f3084 	ldr	r3, [pc, #132]	; 3b0 <ptarmLcdOutputStr+0x138>
     328:	e5d32000 	ldrb	r2, [r3]
     32c:	e5d33001 	ldrb	r3, [r3, #1]
     330:	e1823403 	orr	r3, r2, r3, lsl #8
     334:	e353000f 	cmp	r3, #15, 0
     338:	1a000005 	bne	354 <ptarmLcdOutputStr+0xdc>
			// Go to the second line.
			ptarmLcdGotoLineTwo();
     33c:	e3a02c65 	mov	r2, #25856	; 0x6500
     340:	e2822090 	add	r2, r2, #144, 0	; 0x90
     344:	e3a01000 	mov	r1, #0, 0
     348:	e3a000c0 	mov	r0, #192, 0	; 0xc0
     34c:	ebffff95 	bl	1a8 <ptarmLcdOutput>
     350:	ea00000f 	b	394 <ptarmLcdOutputStr+0x11c>
		} else if (ptarmLcdCharCount == (LCD_LEN * 2)) {
     354:	e59f3054 	ldr	r3, [pc, #84]	; 3b0 <ptarmLcdOutputStr+0x138>
     358:	e5d32000 	ldrb	r2, [r3]
     35c:	e5d33001 	ldrb	r3, [r3, #1]
     360:	e1823403 	orr	r3, r2, r3, lsl #8
     364:	e353001e 	cmp	r3, #30, 0
     368:	1a000009 	bne	394 <ptarmLcdOutputStr+0x11c>
			// Go back to the first line and don't output the remaining string.
			ptarmLcdGotoLineOne();
     36c:	e3a02c65 	mov	r2, #25856	; 0x6500
     370:	e2822090 	add	r2, r2, #144, 0	; 0x90
     374:	e3a01000 	mov	r1, #0, 0
     378:	e3a00080 	mov	r0, #128, 0	; 0x80
     37c:	ebffff89 	bl	1a8 <ptarmLcdOutput>
			ptarmLcdCharCount = 0;
     380:	e59f3028 	ldr	r3, [pc, #40]	; 3b0 <ptarmLcdOutputStr+0x138>
     384:	e3a02000 	mov	r2, #0, 0
     388:	e5c32000 	strb	r2, [r3]
     38c:	e5c32001 	strb	r2, [r3, #1]
			break;
     390:	ea000003 	b	3a4 <ptarmLcdOutputStr+0x12c>
     394:	e51b3008 	ldr	r3, [fp, #-8]
     398:	e5d33000 	ldrb	r3, [r3]
     39c:	e3530000 	cmp	r3, #0, 0
     3a0:	1affffb9 	bne	28c <ptarmLcdOutputStr+0x14>
		}
	}
}
     3a4:	e1a00000 	nop			; (mov r0, r0)
     3a8:	e24bd004 	sub	sp, fp, #4, 0
     3ac:	e8bd8800 	pop	{fp, pc}
     3b0:	0000178c 	.word	0x0000178c

000003b4 <ptarmUartOutputChar>:


//======================================================================
// PTARM UART functions.
//======================================================================

// Use UART as the standard output.
#define printf(str) ptarmUartOutputStr(str)


// Output a character to UART. Not a thread-safe function.
void ptarmUartOutputChar(const char c) {
     3b4:	e92d0830 	push	{r4, r5, fp}
     3b8:	e28db008 	add	fp, sp, #8, 0
     3bc:	e24dd00c 	sub	sp, sp, #12, 0
     3c0:	e1a03000 	mov	r3, r0
     3c4:	e54b300d 	strb	r3, [fp, #-13]
	// Memory mapped addresses for the UART.
	register char * const ptarUartCout = (char * const) UART_COUT;
     3c8:	e3e05cff 	mvn	r5, #65280	; 0xff00
     3cc:	e24550f7 	sub	r5, r5, #247, 0	; 0xf7
	register char * const ptarmUartDout = (char * const) UART_DOUT;
     3d0:	e3e04cff 	mvn	r4, #65280	; 0xff00
     3d4:	e24440f3 	sub	r4, r4, #243, 0	; 0xf3

	while(*ptarUartCout != NULL);
     3d8:	e1a00000 	nop			; (mov r0, r0)
     3dc:	e5d53000 	ldrb	r3, [r5]
     3e0:	e3530000 	cmp	r3, #0, 0
     3e4:	1afffffc 	bne	3dc <ptarmUartOutputChar+0x28>
	*ptarmUartDout = c;
     3e8:	e55b300d 	ldrb	r3, [fp, #-13]
     3ec:	e5c43000 	strb	r3, [r4]
}
     3f0:	e1a00000 	nop			; (mov r0, r0)
     3f4:	e24bd008 	sub	sp, fp, #8, 0
     3f8:	e8bd0830 	pop	{r4, r5, fp}
     3fc:	e1a0f00e 	mov	pc, lr

00000400 <ptarmUartOutputStr>:


// Output a string to UART. Not a thread-safe function.
void ptarmUartOutputStr(const char *str) {
     400:	e92d4800 	push	{fp, lr}
     404:	e28db004 	add	fp, sp, #4, 0
     408:	e24dd008 	sub	sp, sp, #8, 0
     40c:	e50b0008 	str	r0, [fp, #-8]
	while (*str != NULL) {
     410:	ea000006 	b	430 <ptarmUartOutputStr+0x30>
		ptarmUartOutputChar(*str);
     414:	e51b3008 	ldr	r3, [fp, #-8]
     418:	e5d33000 	ldrb	r3, [r3]
     41c:	e1a00003 	mov	r0, r3
     420:	ebffffe3 	bl	3b4 <ptarmUartOutputChar>
		str++;
     424:	e51b3008 	ldr	r3, [fp, #-8]
     428:	e2833001 	add	r3, r3, #1, 0
     42c:	e50b3008 	str	r3, [fp, #-8]
     430:	e51b3008 	ldr	r3, [fp, #-8]
     434:	e5d33000 	ldrb	r3, [r3]
     438:	e3530000 	cmp	r3, #0, 0
     43c:	1afffff4 	bne	414 <ptarmUartOutputStr+0x14>
	}
}
     440:	e1a00000 	nop			; (mov r0, r0)
     444:	e24bd004 	sub	sp, fp, #4, 0
     448:	e8bd8800 	pop	{fp, pc}

0000044c <itoa>:


// Output a string to UART. Thread-safe function.
#define safe_printf(str)	\
	PTARM_MUTEX_LOCK();		\
	printf(str);			\
	PTARM_MUTEX_UNLOCK()


//======================================================================
// String functions.
//======================================================================

// String buffer to hold string representations of values.
char ptarmStringBuffer[12];


// Return a string representation of a signed integer value.
const char * itoa(const int n) {
     44c:	e92d0ff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp}
     450:	e28db01c 	add	fp, sp, #28, 0
     454:	e24dd008 	sub	sp, sp, #8, 0
     458:	e50b0020 	str	r0, [fp, #-32]
	register int next = 0;
     45c:	e3a05000 	mov	r5, #0, 0
	register unsigned int number;

	if (n < 0) {
     460:	e51b3020 	ldr	r3, [fp, #-32]
     464:	e3530000 	cmp	r3, #0, 0
     468:	aa000008 	bge	490 <itoa+0x44>
        ptarmStringBuffer[next++] = '-';
     46c:	e1a03005 	mov	r3, r5
     470:	e2835001 	add	r5, r3, #1, 0
     474:	e59f20e0 	ldr	r2, [pc, #224]	; 55c <itoa+0x110>
     478:	e3a0102d 	mov	r1, #45, 0	; 0x2d
     47c:	e7c21003 	strb	r1, [r2, r3]
		number = -n;
     480:	e51b3020 	ldr	r3, [fp, #-32]
     484:	e2633000 	rsb	r3, r3, #0, 0
     488:	e1a09003 	mov	r9, r3
     48c:	ea000000 	b	494 <itoa+0x48>
	} else {
		number = n;
     490:	e51b9020 	ldr	r9, [fp, #-32]
	}

	if (number == 0) {
     494:	e3590000 	cmp	r9, #0, 0
     498:	1a000005 	bne	4b4 <itoa+0x68>
		ptarmStringBuffer[next++] = '0';
     49c:	e1a03005 	mov	r3, r5
     4a0:	e2835001 	add	r5, r3, #1, 0
     4a4:	e59f20b0 	ldr	r2, [pc, #176]	; 55c <itoa+0x110>
     4a8:	e3a01030 	mov	r1, #48, 0	; 0x30
     4ac:	e7c21003 	strb	r1, [r2, r3]
     4b0:	ea000021 	b	53c <itoa+0xf0>
	} else {
		register int flag = 0;
     4b4:	e3a0a000 	mov	sl, #0, 0
		register unsigned int k = 1000000000;
     4b8:	e3a045ee 	mov	r4, #998244352	; 0x3b800000
     4bc:	e284496b 	add	r4, r4, #1753088	; 0x1ac000
     4c0:	e2844c0a 	add	r4, r4, #2560	; 0xa00
		while (k > 0) {
     4c4:	ea00001a 	b	534 <itoa+0xe8>
			register int r;
			PTARM_UNSIGNED_DIV(r, number, k);
     4c8:	e1a07009 	mov	r7, r9
     4cc:	e1a08004 	mov	r8, r4
     4d0:	ee076908 	cdp	9, 0, cr6, cr7, cr8, {0}
     4d4:	e1a03006 	mov	r3, r6
     4d8:	e1a06003 	mov	r6, r3
			if (flag || r > 0) {
     4dc:	e35a0000 	cmp	sl, #0, 0
     4e0:	1a000001 	bne	4ec <itoa+0xa0>
     4e4:	e3560000 	cmp	r6, #0, 0
     4e8:	da000007 	ble	50c <itoa+0xc0>
				ptarmStringBuffer[next++] = '0' + r;
     4ec:	e1a03005 	mov	r3, r5
     4f0:	e2835001 	add	r5, r3, #1, 0
     4f4:	e20620ff 	and	r2, r6, #255, 0	; 0xff
     4f8:	e2822030 	add	r2, r2, #48, 0	; 0x30
     4fc:	e20210ff 	and	r1, r2, #255, 0	; 0xff
     500:	e59f2054 	ldr	r2, [pc, #84]	; 55c <itoa+0x110>
     504:	e7c21003 	strb	r1, [r2, r3]
				flag = 1;
     508:	e3a0a001 	mov	sl, #1, 0
			}
			number -= r * k;
     50c:	e1a03006 	mov	r3, r6
     510:	e0030394 	mul	r3, r4, r3
     514:	e0639009 	rsb	r9, r3, r9
			register const unsigned int k1 = k;
     518:	e1a03004 	mov	r3, r4
			register const unsigned int ten = 10;
     51c:	e3a0400a 	mov	r4, #10, 0
			PTARM_UNSIGNED_DIV(k, k1, ten);
     520:	e1a07003 	mov	r7, r3
     524:	e1a08004 	mov	r8, r4
     528:	ee076908 	cdp	9, 0, cr6, cr7, cr8, {0}
     52c:	e1a03006 	mov	r3, r6
     530:	e1a04003 	mov	r4, r3
     534:	e3540000 	cmp	r4, #0, 0
     538:	1affffe2 	bne	4c8 <itoa+0x7c>
		}
	}

	ptarmStringBuffer[next] = NULL;
     53c:	e59f3018 	ldr	r3, [pc, #24]	; 55c <itoa+0x110>
     540:	e3a02000 	mov	r2, #0, 0
     544:	e7c32005 	strb	r2, [r3, r5]
	return ptarmStringBuffer;
     548:	e59f300c 	ldr	r3, [pc, #12]	; 55c <itoa+0x110>
}
     54c:	e1a00003 	mov	r0, r3
     550:	e24bd01c 	sub	sp, fp, #28, 0
     554:	e8bd0ff0 	pop	{r4, r5, r6, r7, r8, r9, sl, fp}
     558:	e1a0f00e 	mov	pc, lr
     55c:	000017d4 	.word	0x000017d4

00000560 <utoa>:


// Return a string representation of an unsigned integer value.
const char * utoa(const unsigned int n) {
     560:	e92d0ff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp}
     564:	e28db01c 	add	fp, sp, #28, 0
     568:	e24dd008 	sub	sp, sp, #8, 0
     56c:	e50b0020 	str	r0, [fp, #-32]
	register int next = 0;
     570:	e3a09000 	mov	r9, #0, 0
	register unsigned int number = n;
     574:	e51b5020 	ldr	r5, [fp, #-32]

	if (number == 0) {
     578:	e3550000 	cmp	r5, #0, 0
     57c:	1a000005 	bne	598 <utoa+0x38>
		ptarmStringBuffer[next++] = '0';
     580:	e1a03009 	mov	r3, r9
     584:	e2839001 	add	r9, r3, #1, 0
     588:	e59f20b0 	ldr	r2, [pc, #176]	; 640 <utoa+0xe0>
     58c:	e3a01030 	mov	r1, #48, 0	; 0x30
     590:	e7c21003 	strb	r1, [r2, r3]
     594:	ea000021 	b	620 <utoa+0xc0>
	} else {
		register int flag = 0;
     598:	e3a0a000 	mov	sl, #0, 0
		register unsigned int k = 1000000000;
     59c:	e3a045ee 	mov	r4, #998244352	; 0x3b800000
     5a0:	e284496b 	add	r4, r4, #1753088	; 0x1ac000
     5a4:	e2844c0a 	add	r4, r4, #2560	; 0xa00
		while (k > 0) {
     5a8:	ea00001a 	b	618 <utoa+0xb8>
			register int r;
			PTARM_UNSIGNED_DIV(r, number, k);
     5ac:	e1a07005 	mov	r7, r5
     5b0:	e1a08004 	mov	r8, r4
     5b4:	ee076908 	cdp	9, 0, cr6, cr7, cr8, {0}
     5b8:	e1a03006 	mov	r3, r6
     5bc:	e1a06003 	mov	r6, r3
			if (flag || r > 0) {
     5c0:	e35a0000 	cmp	sl, #0, 0
     5c4:	1a000001 	bne	5d0 <utoa+0x70>
     5c8:	e3560000 	cmp	r6, #0, 0
     5cc:	da000007 	ble	5f0 <utoa+0x90>
				ptarmStringBuffer[next++] = '0' + r;
     5d0:	e1a03009 	mov	r3, r9
     5d4:	e2839001 	add	r9, r3, #1, 0
     5d8:	e20620ff 	and	r2, r6, #255, 0	; 0xff
     5dc:	e2822030 	add	r2, r2, #48, 0	; 0x30
     5e0:	e20210ff 	and	r1, r2, #255, 0	; 0xff
     5e4:	e59f2054 	ldr	r2, [pc, #84]	; 640 <utoa+0xe0>
     5e8:	e7c21003 	strb	r1, [r2, r3]
				flag = 1;
     5ec:	e3a0a001 	mov	sl, #1, 0
			}
			number -= r * k;
     5f0:	e1a03006 	mov	r3, r6
     5f4:	e0030394 	mul	r3, r4, r3
     5f8:	e0635005 	rsb	r5, r3, r5
			register const unsigned int k1 = k;
     5fc:	e1a03004 	mov	r3, r4
			register const unsigned int ten = 10;
     600:	e3a0400a 	mov	r4, #10, 0
			PTARM_UNSIGNED_DIV(k, k1, ten);
     604:	e1a07003 	mov	r7, r3
     608:	e1a08004 	mov	r8, r4
     60c:	ee076908 	cdp	9, 0, cr6, cr7, cr8, {0}
     610:	e1a03006 	mov	r3, r6
     614:	e1a04003 	mov	r4, r3
     618:	e3540000 	cmp	r4, #0, 0
     61c:	1affffe2 	bne	5ac <utoa+0x4c>
		}
	}

	ptarmStringBuffer[next] = NULL;
     620:	e59f3018 	ldr	r3, [pc, #24]	; 640 <utoa+0xe0>
     624:	e3a02000 	mov	r2, #0, 0
     628:	e7c32009 	strb	r2, [r3, r9]
	return ptarmStringBuffer;
     62c:	e59f300c 	ldr	r3, [pc, #12]	; 640 <utoa+0xe0>
}
     630:	e1a00003 	mov	r0, r3
     634:	e24bd01c 	sub	sp, fp, #28, 0
     638:	e8bd0ff0 	pop	{r4, r5, r6, r7, r8, r9, sl, fp}
     63c:	e1a0f00e 	mov	pc, lr
     640:	000017d4 	.word	0x000017d4

00000644 <hex>:


// Return a string representation of an unsigned hexadecimal value.
const char * hex(const unsigned int number) {
     644:	e92d0870 	push	{r4, r5, r6, fp}
     648:	e28db00c 	add	fp, sp, #12, 0
     64c:	e24dd008 	sub	sp, sp, #8, 0
     650:	e50b0010 	str	r0, [fp, #-16]
	ptarmStringBuffer[0] = '0';
     654:	e59f308c 	ldr	r3, [pc, #140]	; 6e8 <hex+0xa4>
     658:	e3a02030 	mov	r2, #48, 0	; 0x30
     65c:	e5c32000 	strb	r2, [r3]
	ptarmStringBuffer[1] = 'x';
     660:	e59f3080 	ldr	r3, [pc, #128]	; 6e8 <hex+0xa4>
     664:	e3a02078 	mov	r2, #120, 0	; 0x78
     668:	e5c32001 	strb	r2, [r3, #1]
	register int i, k;
	for(i = 32-4, k = 2; i >= 0; i -= 4, k++) {
     66c:	e3a0501c 	mov	r5, #28, 0
     670:	e3a04002 	mov	r4, #2, 0
     674:	ea000011 	b	6c0 <hex+0x7c>
		register unsigned int a = (number >> i) & 0xf;
     678:	e51b3010 	ldr	r3, [fp, #-16]
     67c:	e1a03533 	lsr	r3, r3, r5
     680:	e203600f 	and	r6, r3, #15, 0
		if (a < 10) {
     684:	e3560009 	cmp	r6, #9, 0
     688:	8a000005 	bhi	6a4 <hex+0x60>
			ptarmStringBuffer[k] = a + '0';
     68c:	e20630ff 	and	r3, r6, #255, 0	; 0xff
     690:	e2833030 	add	r3, r3, #48, 0	; 0x30
     694:	e20320ff 	and	r2, r3, #255, 0	; 0xff
     698:	e59f3048 	ldr	r3, [pc, #72]	; 6e8 <hex+0xa4>
     69c:	e7c32004 	strb	r2, [r3, r4]
     6a0:	ea000004 	b	6b8 <hex+0x74>
		} else {
			ptarmStringBuffer[k] = a + 'a' - 10;
     6a4:	e20630ff 	and	r3, r6, #255, 0	; 0xff
     6a8:	e2833057 	add	r3, r3, #87, 0	; 0x57
     6ac:	e20320ff 	and	r2, r3, #255, 0	; 0xff
     6b0:	e59f3030 	ldr	r3, [pc, #48]	; 6e8 <hex+0xa4>
     6b4:	e7c32004 	strb	r2, [r3, r4]
     6b8:	e2455004 	sub	r5, r5, #4, 0
     6bc:	e2844001 	add	r4, r4, #1, 0
     6c0:	e3550000 	cmp	r5, #0, 0
     6c4:	aaffffeb 	bge	678 <hex+0x34>
		}
	}

	ptarmStringBuffer[k] = NULL;
     6c8:	e59f3018 	ldr	r3, [pc, #24]	; 6e8 <hex+0xa4>
     6cc:	e3a02000 	mov	r2, #0, 0
     6d0:	e7c32004 	strb	r2, [r3, r4]
	return ptarmStringBuffer;
     6d4:	e59f300c 	ldr	r3, [pc, #12]	; 6e8 <hex+0xa4>
}
     6d8:	e1a00003 	mov	r0, r3
     6dc:	e24bd00c 	sub	sp, fp, #12, 0
     6e0:	e8bd0870 	pop	{r4, r5, r6, fp}
     6e4:	e1a0f00e 	mov	pc, lr
     6e8:	000017d4 	.word	0x000017d4

000006ec <foreMcGetIndex>:
	)


// Maps the index of the buffer array to the index of the circular buffer.
const unsigned int foreMcGetIndex(const unsigned int indexPlusFirst, const unsigned int maxSize) {
     6ec:	e92d09c0 	push	{r6, r7, r8, fp}
     6f0:	e28db00c 	add	fp, sp, #12, 0
     6f4:	e24dd010 	sub	sp, sp, #16, 0
     6f8:	e50b0018 	str	r0, [fp, #-24]
     6fc:	e50b101c 	str	r1, [fp, #-28]
	unsigned int quotient;
	PTARM_UNSIGNED_DIV(quotient, indexPlusFirst, maxSize);
     700:	e51b3018 	ldr	r3, [fp, #-24]
     704:	e51b201c 	ldr	r2, [fp, #-28]
     708:	e1a07003 	mov	r7, r3
     70c:	e1a08002 	mov	r8, r2
     710:	ee076908 	cdp	9, 0, cr6, cr7, cr8, {0}
     714:	e1a03006 	mov	r3, r6
     718:	e50b3010 	str	r3, [fp, #-16]
	return (indexPlusFirst) - (quotient * maxSize);
     71c:	e51b3010 	ldr	r3, [fp, #-16]
     720:	e51b201c 	ldr	r2, [fp, #-28]
     724:	e0030392 	mul	r3, r2, r3
     728:	e51b2018 	ldr	r2, [fp, #-24]
     72c:	e0633002 	rsb	r3, r3, r2
}
     730:	e1a00003 	mov	r0, r3
     734:	e24bd00c 	sub	sp, fp, #12, 0
     738:	e8bd09c0 	pop	{r6, r7, r8, fp}
     73c:	e1a0f00e 	mov	pc, lr

00000740 <ptarmCreateTask>:
//======================================================================

// Create a task. Checks that there will be enough memory.
// Thread-safe function.
void ptarmCreateTask(volatile Task *task, unsigned int *startPc, volatile LocalScheduler *localScheduler) {
     740:	e92d4b80 	push	{r7, r8, r9, fp, lr}
     744:	e28db010 	add	fp, sp, #16, 0
     748:	e24dd01c 	sub	sp, sp, #28, 0
     74c:	e50b0020 	str	r0, [fp, #-32]
     750:	e50b1024 	str	r1, [fp, #-36]	; 0x24
     754:	e50b2028 	str	r2, [fp, #-40]	; 0x28
	PTARM_MUTEX_LOCK();
     758:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
	const unsigned int frameSize = 0x0100;
     75c:	e3a03c01 	mov	r3, #256	; 0x100
     760:	e50b3018 	str	r3, [fp, #-24]
	const unsigned int limit = 0x0200;		// 0x0200 * sizeof(unsigned int) byte sized stack.
     764:	e3a03c02 	mov	r3, #512	; 0x200
     768:	e50b301c 	str	r3, [fp, #-28]

	// Check that there is enough memory to create a task stack.
	if ((ptarmPreviousTaskStackEnd - &addr_stack_limit) < limit) {
     76c:	e59f315c 	ldr	r3, [pc, #348]	; 8d0 <ptarmCreateTask+0x190>
     770:	e5933000 	ldr	r3, [r3]
     774:	e1a02003 	mov	r2, r3
     778:	e59f3154 	ldr	r3, [pc, #340]	; 8d4 <ptarmCreateTask+0x194>
     77c:	e0633002 	rsb	r3, r3, r2
     780:	e1a03143 	asr	r3, r3, #2
     784:	e1a02003 	mov	r2, r3
     788:	e51b301c 	ldr	r3, [fp, #-28]
     78c:	e1520003 	cmp	r2, r3
     790:	2a00001b 	bcs	804 <ptarmCreateTask+0xc4>
		printf("PTARM_TASK_CREATE: Stack limit exceeded!\n");
     794:	e59f013c 	ldr	r0, [pc, #316]	; 8d8 <ptarmCreateTask+0x198>
     798:	ebffff18 	bl	400 <ptarmUartOutputStr>
		printf("  Available amount: ");
     79c:	e59f0138 	ldr	r0, [pc, #312]	; 8dc <ptarmCreateTask+0x19c>
     7a0:	ebffff16 	bl	400 <ptarmUartOutputStr>
		printf(utoa((ptarmPreviousTaskStackEnd -  &addr_stack_limit)*sizeof(unsigned int)));
     7a4:	e59f3124 	ldr	r3, [pc, #292]	; 8d0 <ptarmCreateTask+0x190>
     7a8:	e5933000 	ldr	r3, [r3]
     7ac:	e1a02003 	mov	r2, r3
     7b0:	e59f311c 	ldr	r3, [pc, #284]	; 8d4 <ptarmCreateTask+0x194>
     7b4:	e0633002 	rsb	r3, r3, r2
     7b8:	e1a00003 	mov	r0, r3
     7bc:	ebffff67 	bl	560 <utoa>
     7c0:	e1a03000 	mov	r3, r0
     7c4:	e1a00003 	mov	r0, r3
     7c8:	ebffff0c 	bl	400 <ptarmUartOutputStr>
		printf(" bytes.\n");
     7cc:	e59f010c 	ldr	r0, [pc, #268]	; 8e0 <ptarmCreateTask+0x1a0>
     7d0:	ebffff0a 	bl	400 <ptarmUartOutputStr>
		printf("  Requested amount: ");
     7d4:	e59f0108 	ldr	r0, [pc, #264]	; 8e4 <ptarmCreateTask+0x1a4>
     7d8:	ebffff08 	bl	400 <ptarmUartOutputStr>
		printf(utoa(limit*sizeof(unsigned int)));
     7dc:	e51b301c 	ldr	r3, [fp, #-28]
     7e0:	e1a03103 	lsl	r3, r3, #2
     7e4:	e1a00003 	mov	r0, r3
     7e8:	ebffff5c 	bl	560 <utoa>
     7ec:	e1a03000 	mov	r3, r0
     7f0:	e1a00003 	mov	r0, r3
     7f4:	ebffff01 	bl	400 <ptarmUartOutputStr>
		printf(" bytes.\n");
     7f8:	e59f00e0 	ldr	r0, [pc, #224]	; 8e0 <ptarmCreateTask+0x1a0>
     7fc:	ebfffeff 	bl	400 <ptarmUartOutputStr>
		while(1);
     800:	eafffffe 	b	800 <ptarmCreateTask+0xc0>
	}

	// Create a stack for the task.
	PTARM_TASK_CREATE_STACK(task, frameSize, startPc);
     804:	e59f30c4 	ldr	r3, [pc, #196]	; 8d0 <ptarmCreateTask+0x190>
     808:	e5932000 	ldr	r2, [r3]
     80c:	e51b3018 	ldr	r3, [fp, #-24]
     810:	e1a03103 	lsl	r3, r3, #2
     814:	e2633000 	rsb	r3, r3, #0, 0
     818:	e0822003 	add	r2, r2, r3
     81c:	e59f30ac 	ldr	r3, [pc, #172]	; 8d0 <ptarmCreateTask+0x190>
     820:	e5931000 	ldr	r1, [r3]
     824:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
     828:	e1a0800d 	mov	r8, sp
     82c:	e1a0d002 	mov	sp, r2
     830:	e1a09001 	mov	r9, r1
     834:	e1a07003 	mov	r7, r3
     838:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     83c:	e3a07000 	mov	r7, #0, 0
     840:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     844:	e52d9004 	push	{r9}		; (str r9, [sp, #-4]!)
     848:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     84c:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     850:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     854:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     858:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     85c:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     860:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     864:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     868:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     86c:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     870:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     874:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
     878:	e1a0200d 	mov	r2, sp
     87c:	e1a0d008 	mov	sp, r8
     880:	e51b3020 	ldr	r3, [fp, #-32]
     884:	e5832010 	str	r2, [r3, #16]

	// Update where the last stack frame ends.
	ptarmPreviousTaskStackEnd = ptarmPreviousTaskStackEnd - limit;
     888:	e59f3040 	ldr	r3, [pc, #64]	; 8d0 <ptarmCreateTask+0x190>
     88c:	e5932000 	ldr	r2, [r3]
     890:	e51b301c 	ldr	r3, [fp, #-28]
     894:	e1a03103 	lsl	r3, r3, #2
     898:	e2633000 	rsb	r3, r3, #0, 0
     89c:	e0823003 	add	r3, r2, r3
     8a0:	e59f2028 	ldr	r2, [pc, #40]	; 8d0 <ptarmCreateTask+0x190>
     8a4:	e5823000 	str	r3, [r2]

	// Initialise the SPSR of the task.
	task->spsr = 0;
     8a8:	e51b3020 	ldr	r3, [fp, #-32]
     8ac:	e3a02000 	mov	r2, #0, 0
     8b0:	e5832014 	str	r2, [r3, #20]
	
	// Initialise the static and current local schedulers.
	task->localScheduler = localScheduler;
     8b4:	e51b3020 	ldr	r3, [fp, #-32]
     8b8:	e51b2028 	ldr	r2, [fp, #-40]	; 0x28
     8bc:	e5832008 	str	r2, [r3, #8]

	/*
	// Task = xxx, FP = xxx, SP = xxx, PC = xxx.
	printf("Task = "); printf(task->name);
	printf(", FP = "); printf(hex(stackFrameStart));
	printf(", SP = "); printf(hex((unsigned int)(task->sp)));
	printf(", PC = "); printf(hex(task->sp[14]));
	printf(".\n");
	*/
	PTARM_MUTEX_UNLOCK();
     8c0:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
}
     8c4:	e1a00000 	nop			; (mov r0, r0)
     8c8:	e24bd010 	sub	sp, fp, #16, 0
     8cc:	e8bd8b80 	pop	{r7, r8, r9, fp, pc}
     8d0:	00001634 	.word	0x00001634
     8d4:	000017e0 	.word	0x000017e0
     8d8:	00001398 	.word	0x00001398
     8dc:	000013c4 	.word	0x000013c4
     8e0:	000013dc 	.word	0x000013dc
     8e4:	000013e8 	.word	0x000013e8

000008e8 <main>:
GlobalScheduler globalScheduler = {.isInitialised = false};


// Main entry point of the program that is executed by all hardware threads.
int main(void) {
     8e8:	e92d4980 	push	{r7, r8, fp, lr}
     8ec:	e28db00c 	add	fp, sp, #12, 0
     8f0:	e24dd0b8 	sub	sp, sp, #184, 0	; 0xb8
	// Create a local scheduler that uses the hardware thread's stack.
	ptarmCreateLocalScheduler(localScheduler, &&localScheduler);
     8f4:	ee007d00 	cdp	13, 0, cr7, cr0, cr0, {0}
     8f8:	e1a03007 	mov	r3, r7
     8fc:	e50b301c 	str	r3, [fp, #-28]
     900:	e24b3038 	sub	r3, fp, #56, 0	; 0x38
     904:	e3a02000 	mov	r2, #0, 0
     908:	e5832000 	str	r2, [r3]
     90c:	e5832004 	str	r2, [r3, #4]
     910:	e5832008 	str	r2, [r3, #8]
     914:	e583200c 	str	r2, [r3, #12]
     918:	e5832010 	str	r2, [r3, #16]
     91c:	e59f28c8 	ldr	r2, [pc, #2248]	; 11ec <main+0x904>
     920:	e24b3044 	sub	r3, fp, #68, 0	; 0x44
     924:	e8920007 	ldm	r2, {r0, r1, r2}
     928:	e8a30003 	stmia	r3!, {r0, r1}
     92c:	e5c32000 	strb	r2, [r3]
     930:	e1a01442 	asr	r1, r2, #8
     934:	e5c31001 	strb	r1, [r3, #1]
     938:	e2833002 	add	r3, r3, #2, 0
     93c:	e1a02822 	lsr	r2, r2, #16
     940:	e5c32000 	strb	r2, [r3]
     944:	e51b301c 	ldr	r3, [fp, #-28]
     948:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     94c:	e2833030 	add	r3, r3, #48, 0	; 0x30
     950:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     954:	e54b303b 	strb	r3, [fp, #-59]	; 0x3b
     958:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     95c:	e3a02068 	mov	r2, #104, 0	; 0x68
     960:	e3a01000 	mov	r1, #0, 0
     964:	e1a00003 	mov	r0, r3
     968:	eb0002f4 	bl	1540 <memset>
     96c:	e24b3044 	sub	r3, fp, #68, 0	; 0x44
     970:	e50b30ac 	str	r3, [fp, #-172]	; 0xac
     974:	e51b301c 	ldr	r3, [fp, #-28]
     978:	e50b30a8 	str	r3, [fp, #-168]	; 0xa8
     97c:	e24b3038 	sub	r3, fp, #56, 0	; 0x38
     980:	e50b3090 	str	r3, [fp, #-144]	; 0x90
     984:	e51b3038 	ldr	r3, [fp, #-56]	; 0x38
     988:	e50b308c 	str	r3, [fp, #-140]	; 0x8c
     98c:	e24b3038 	sub	r3, fp, #56, 0	; 0x38
     990:	e50b3088 	str	r3, [fp, #-136]	; 0x88
     994:	e1a0200d 	mov	r2, sp
     998:	e1a0300b 	mov	r3, fp
     99c:	e50b20a0 	str	r2, [fp, #-160]	; 0xa0
     9a0:	e50b30a4 	str	r3, [fp, #-164]	; 0xa4
     9a4:	e59f3844 	ldr	r3, [pc, #2116]	; 11f0 <main+0x908>
     9a8:	e50b309c 	str	r3, [fp, #-156]	; 0x9c

	// Each hardware thread performs some type of start up work.
	switch (localScheduler.hwThreadId) {
     9ac:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     9b0:	e3530003 	cmp	r3, #3, 0
     9b4:	979ff103 	ldrls	pc, [pc, r3, lsl #2]
     9b8:	ea00004e 	b	af8 <main+0x210>
     9bc:	000009cc 	.word	0x000009cc
     9c0:	00000a2c 	.word	0x00000a2c
     9c4:	00000a70 	.word	0x00000a70
     9c8:	00000ab4 	.word	0x00000ab4
		case (0):	// Hardware thread 0.

					safe_printf("Input/Output example.\n\n");
     9cc:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
     9d0:	e59f081c 	ldr	r0, [pc, #2076]	; 11f4 <main+0x90c>
     9d4:	ebfffe89 	bl	400 <ptarmUartOutputStr>
     9d8:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
			
					ptarmCreateTask(&one, &&one, &localScheduler);						// Create task one.
     9dc:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
     9e0:	e59f3810 	ldr	r3, [pc, #2064]	; 11f8 <main+0x910>
     9e4:	e1a01003 	mov	r1, r3
     9e8:	e59f080c 	ldr	r0, [pc, #2060]	; 11fc <main+0x914>
     9ec:	ebffff53 	bl	740 <ptarmCreateTask>
					localScheduler.currentTask = &one;									// Assign a task to execute.
     9f0:	e59f3804 	ldr	r3, [pc, #2052]	; 11fc <main+0x914>
     9f4:	e50b308c 	str	r3, [fp, #-140]	; 0x8c
					globalScheduler.localScheduler0 = &localScheduler;					// Set the global reference to the local scheduler
     9f8:	e59f2800 	ldr	r2, [pc, #2048]	; 1200 <main+0x918>
     9fc:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     a00:	e5823014 	str	r3, [r2, #20]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler0);	// Register the EOE handler.
     a04:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     a08:	e1a03103 	lsl	r3, r3, #2
     a0c:	e59f27f0 	ldr	r2, [pc, #2032]	; 1204 <main+0x91c>
     a10:	e0833002 	add	r3, r3, r2
     a14:	e59f27ec 	ldr	r2, [pc, #2028]	; 1208 <main+0x920>
     a18:	e5832000 	str	r2, [r3]

					globalScheduler.isInitialised = true;								// Initialisation complete.
     a1c:	e59f37dc 	ldr	r3, [pc, #2012]	; 1200 <main+0x918>
     a20:	e3a02001 	mov	r2, #1, 0
     a24:	e5c32000 	strb	r2, [r3]
					break;
     a28:	ea000045 	b	b44 <main+0x25c>

		case (1):	// Hardware thread 1.

					ptarmCreateTask(&two, &&two, &localScheduler);						// Create task two.
     a2c:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
     a30:	e59f37d4 	ldr	r3, [pc, #2004]	; 120c <main+0x924>
     a34:	e1a01003 	mov	r1, r3
     a38:	e59f07d0 	ldr	r0, [pc, #2000]	; 1210 <main+0x928>
     a3c:	ebffff3f 	bl	740 <ptarmCreateTask>
					localScheduler.currentTask = &two;									// Assign a task to execute.
     a40:	e59f37c8 	ldr	r3, [pc, #1992]	; 1210 <main+0x928>
     a44:	e50b308c 	str	r3, [fp, #-140]	; 0x8c
					globalScheduler.localScheduler1 = &localScheduler;					// Set the global reference to the local scheduler
     a48:	e59f27b0 	ldr	r2, [pc, #1968]	; 1200 <main+0x918>
     a4c:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     a50:	e5823018 	str	r3, [r2, #24]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler1);	// Register the EOE handler.
     a54:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     a58:	e1a03103 	lsl	r3, r3, #2
     a5c:	e59f27a0 	ldr	r2, [pc, #1952]	; 1204 <main+0x91c>
     a60:	e0833002 	add	r3, r3, r2
     a64:	e59f27a8 	ldr	r2, [pc, #1960]	; 1214 <main+0x92c>
     a68:	e5832000 	str	r2, [r3]
					break;
     a6c:	ea000034 	b	b44 <main+0x25c>

		case (2):	// Hardware thread 2.

					ptarmCreateTask(&three, &&three, &localScheduler);
     a70:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
     a74:	e59f379c 	ldr	r3, [pc, #1948]	; 1218 <main+0x930>
     a78:	e1a01003 	mov	r1, r3
     a7c:	e59f0798 	ldr	r0, [pc, #1944]	; 121c <main+0x934>
     a80:	ebffff2e 	bl	740 <ptarmCreateTask>
					localScheduler.currentTask = &three;
     a84:	e59f3790 	ldr	r3, [pc, #1936]	; 121c <main+0x934>
     a88:	e50b308c 	str	r3, [fp, #-140]	; 0x8c
					globalScheduler.localScheduler2 = &localScheduler;
     a8c:	e59f276c 	ldr	r2, [pc, #1900]	; 1200 <main+0x918>
     a90:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     a94:	e582301c 	str	r3, [r2, #28]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler2);
     a98:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     a9c:	e1a03103 	lsl	r3, r3, #2
     aa0:	e59f275c 	ldr	r2, [pc, #1884]	; 1204 <main+0x91c>
     aa4:	e0833002 	add	r3, r3, r2
     aa8:	e59f2770 	ldr	r2, [pc, #1904]	; 1220 <main+0x938>
     aac:	e5832000 	str	r2, [r3]
					break;
     ab0:	ea000023 	b	b44 <main+0x25c>

		case (3):	// Hardware thread 3.

					ptarmCreateTask(&four, &&four, &localScheduler);
     ab4:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
     ab8:	e59f3764 	ldr	r3, [pc, #1892]	; 1224 <main+0x93c>
     abc:	e1a01003 	mov	r1, r3
     ac0:	e59f0760 	ldr	r0, [pc, #1888]	; 1228 <main+0x940>
     ac4:	ebffff1d 	bl	740 <ptarmCreateTask>
					localScheduler.currentTask = &four;
     ac8:	e59f3758 	ldr	r3, [pc, #1880]	; 1228 <main+0x940>
     acc:	e50b308c 	str	r3, [fp, #-140]	; 0x8c
					globalScheduler.localScheduler3 = &localScheduler;
     ad0:	e59f2728 	ldr	r2, [pc, #1832]	; 1200 <main+0x918>
     ad4:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     ad8:	e5823020 	str	r3, [r2, #32]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler3);
     adc:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     ae0:	e1a03103 	lsl	r3, r3, #2
     ae4:	e59f2718 	ldr	r2, [pc, #1816]	; 1204 <main+0x91c>
     ae8:	e0833002 	add	r3, r3, r2
     aec:	e59f2738 	ldr	r2, [pc, #1848]	; 122c <main+0x944>
     af0:	e5832000 	str	r2, [r3]
					break;
     af4:	ea000012 	b	b44 <main+0x25c>

		default:	// Unknown hardware thread ID.

					PTARM_MUTEX_LOCK();
     af8:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
					printf("!! Initialisation error: Unknown hwThreadId = ");
     afc:	e59f072c 	ldr	r0, [pc, #1836]	; 1230 <main+0x948>
     b00:	ebfffe3e 	bl	400 <ptarmUartOutputStr>
					printf(utoa(localScheduler.hwThreadId));
     b04:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     b08:	e1a00003 	mov	r0, r3
     b0c:	ebfffe93 	bl	560 <utoa>
     b10:	e1a03000 	mov	r3, r0
     b14:	e1a00003 	mov	r0, r3
     b18:	ebfffe38 	bl	400 <ptarmUartOutputStr>
					printf("\n");
     b1c:	e59f0710 	ldr	r0, [pc, #1808]	; 1234 <main+0x94c>
     b20:	ebfffe36 	bl	400 <ptarmUartOutputStr>
					PTARM_MUTEX_UNLOCK();
     b24:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
					while (halt);
     b28:	e1a00000 	nop			; (mov r0, r0)
     b2c:	e59f3704 	ldr	r3, [pc, #1796]	; 1238 <main+0x950>
     b30:	e5d33000 	ldrb	r3, [r3]
     b34:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     b38:	e3530000 	cmp	r3, #0, 0
     b3c:	1afffffa 	bne	b2c <main+0x244>
					break;
     b40:	e1a00000 	nop			; (mov r0, r0)
	}

	// All hardware threads execute this.
	while(globalScheduler.isInitialised == false);
     b44:	e1a00000 	nop			; (mov r0, r0)
     b48:	e59f36b0 	ldr	r3, [pc, #1712]	; 1200 <main+0x918>
     b4c:	e5d33000 	ldrb	r3, [r3]
     b50:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     b54:	e3530000 	cmp	r3, #0, 0
     b58:	0afffffa 	beq	b48 <main+0x260>
	localScheduler.basePeriodStart = globalScheduler.basePeriodFirstStart;
     b5c:	e59f269c 	ldr	r2, [pc, #1692]	; 1200 <main+0x918>
     b60:	e24b3080 	sub	r3, fp, #128, 0	; 0x80
     b64:	e282200c 	add	r2, r2, #12, 0
     b68:	e8920003 	ldm	r2, {r0, r1}
     b6c:	e8830003 	stm	r3, {r0, r1}
	PTARM_GOTO(localScheduler);
     b70:	ea00006d 	b	d2c <main+0x444>


// The registered EOE handler of each hardware thread.
// An exception can occur during the execution of any task (or scheduler). When
// an exception does occur, the registered EOE handler is called. We cannot immediately
// query what task was preempted because that will cause some registers to
// be overwritten. Hence, we save the task's context anonymously before querying
// what task was preempted so that the saved context can be assigned to the correct task.

// For hardware thread 0.
eoeHandler0: {
	// Save the context of the preempted (anonymous) task and then restore the scheduler's context
	// to query which task was preempted.
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler0);
     b74:	e1a00000 	nop			; (mov r0, r0)
     b78:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     b7c:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     b80:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     b84:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     b88:	e59f3670 	ldr	r3, [pc, #1648]	; 1200 <main+0x918>
     b8c:	e5933014 	ldr	r3, [r3, #20]
     b90:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     b94:	e58d7038 	str	r7, [sp, #56]	; 0x38
     b98:	e1a0200d 	mov	r2, sp
     b9c:	e5832014 	str	r2, [r3, #20]
     ba0:	e59f3658 	ldr	r3, [pc, #1624]	; 1200 <main+0x918>
     ba4:	e5933014 	ldr	r3, [r3, #20]
     ba8:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     bac:	e1a02007 	mov	r2, r7
     bb0:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler0);
     bb4:	e59f3644 	ldr	r3, [pc, #1604]	; 1200 <main+0x918>
     bb8:	e5933014 	ldr	r3, [r3, #20]
     bbc:	e593300c 	ldr	r3, [r3, #12]
     bc0:	e59f2638 	ldr	r2, [pc, #1592]	; 1200 <main+0x918>
     bc4:	e5922014 	ldr	r2, [r2, #20]
     bc8:	e5922008 	ldr	r2, [r2, #8]
     bcc:	e1a0d003 	mov	sp, r3
     bd0:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     bd4:	ea00004a 	b	d04 <main+0x41c>
}

// For hardware thread 1.
eoeHandler1: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler1);
     bd8:	e1a00000 	nop			; (mov r0, r0)
     bdc:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     be0:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     be4:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     be8:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     bec:	e59f360c 	ldr	r3, [pc, #1548]	; 1200 <main+0x918>
     bf0:	e5933018 	ldr	r3, [r3, #24]
     bf4:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     bf8:	e58d7038 	str	r7, [sp, #56]	; 0x38
     bfc:	e1a0200d 	mov	r2, sp
     c00:	e5832014 	str	r2, [r3, #20]
     c04:	e59f35f4 	ldr	r3, [pc, #1524]	; 1200 <main+0x918>
     c08:	e5933018 	ldr	r3, [r3, #24]
     c0c:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     c10:	e1a02007 	mov	r2, r7
     c14:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler1);
     c18:	e59f35e0 	ldr	r3, [pc, #1504]	; 1200 <main+0x918>
     c1c:	e5933018 	ldr	r3, [r3, #24]
     c20:	e593300c 	ldr	r3, [r3, #12]
     c24:	e59f25d4 	ldr	r2, [pc, #1492]	; 1200 <main+0x918>
     c28:	e5922018 	ldr	r2, [r2, #24]
     c2c:	e5922008 	ldr	r2, [r2, #8]
     c30:	e1a0d003 	mov	sp, r3
     c34:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     c38:	ea000031 	b	d04 <main+0x41c>
}

// For hardware thread 2.
eoeHandler2: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler2);
     c3c:	e1a00000 	nop			; (mov r0, r0)
     c40:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     c44:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     c48:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     c4c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     c50:	e59f35a8 	ldr	r3, [pc, #1448]	; 1200 <main+0x918>
     c54:	e593301c 	ldr	r3, [r3, #28]
     c58:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     c5c:	e58d7038 	str	r7, [sp, #56]	; 0x38
     c60:	e1a0200d 	mov	r2, sp
     c64:	e5832014 	str	r2, [r3, #20]
     c68:	e59f3590 	ldr	r3, [pc, #1424]	; 1200 <main+0x918>
     c6c:	e593301c 	ldr	r3, [r3, #28]
     c70:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     c74:	e1a02007 	mov	r2, r7
     c78:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler2);
     c7c:	e59f357c 	ldr	r3, [pc, #1404]	; 1200 <main+0x918>
     c80:	e593301c 	ldr	r3, [r3, #28]
     c84:	e593300c 	ldr	r3, [r3, #12]
     c88:	e59f2570 	ldr	r2, [pc, #1392]	; 1200 <main+0x918>
     c8c:	e592201c 	ldr	r2, [r2, #28]
     c90:	e5922008 	ldr	r2, [r2, #8]
     c94:	e1a0d003 	mov	sp, r3
     c98:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     c9c:	ea000018 	b	d04 <main+0x41c>
}

// For hardware thread 3.
eoeHandler3: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler3);
     ca0:	e1a00000 	nop			; (mov r0, r0)
     ca4:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     ca8:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     cac:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     cb0:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     cb4:	e59f3544 	ldr	r3, [pc, #1348]	; 1200 <main+0x918>
     cb8:	e5933020 	ldr	r3, [r3, #32]
     cbc:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     cc0:	e58d7038 	str	r7, [sp, #56]	; 0x38
     cc4:	e1a0200d 	mov	r2, sp
     cc8:	e5832014 	str	r2, [r3, #20]
     ccc:	e59f352c 	ldr	r3, [pc, #1324]	; 1200 <main+0x918>
     cd0:	e5933020 	ldr	r3, [r3, #32]
     cd4:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     cd8:	e1a02007 	mov	r2, r7
     cdc:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler3);
     ce0:	e59f3518 	ldr	r3, [pc, #1304]	; 1200 <main+0x918>
     ce4:	e5933020 	ldr	r3, [r3, #32]
     ce8:	e593300c 	ldr	r3, [r3, #12]
     cec:	e59f250c 	ldr	r2, [pc, #1292]	; 1200 <main+0x918>
     cf0:	e5922020 	ldr	r2, [r2, #32]
     cf4:	e5922008 	ldr	r2, [r2, #8]
     cf8:	e1a0d003 	mov	sp, r3
     cfc:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     d00:	eaffffff 	b	d04 <main+0x41c>
}

eoeHandler: {
	// Assign the saved context to the preempted task.
	localScheduler.currentTask->state = PTARM_TASK_PREEMPTED;
     d04:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     d08:	e3a02001 	mov	r2, #1, 0
     d0c:	e5c3200c 	strb	r2, [r3, #12]
	localScheduler.currentTask->sp = localScheduler.preemptedSp;
     d10:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     d14:	e51b2098 	ldr	r2, [fp, #-152]	; 0x98
     d18:	e5832010 	str	r2, [r3, #16]
	localScheduler.currentTask->spsr = localScheduler.preemptedSpsr;
     d1c:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     d20:	e51b2094 	ldr	r2, [fp, #-148]	; 0x94
     d24:	e5832014 	str	r2, [r3, #20]

	PTARM_GOTO(localScheduler);
     d28:	eaffffff 	b	d2c <main+0x444>
}


// Local scheduler for each hardware thread.
localScheduler: {
	Timer64Bit delay = {.msb = 0, .lsb = 0};
     d2c:	e3a03000 	mov	r3, #0, 0
     d30:	e50b30b4 	str	r3, [fp, #-180]	; 0xb4
     d34:	e3a03000 	mov	r3, #0, 0
     d38:	e50b30b0 	str	r3, [fp, #-176]	; 0xb0
	switch (localScheduler.hwThreadId) {
     d3c:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     d40:	e3530003 	cmp	r3, #3, 0
     d44:	979ff103 	ldrls	pc, [pc, r3, lsl #2]
     d48:	ea000017 	b	dac <main+0x4c4>
     d4c:	00000d5c 	.word	0x00000d5c
     d50:	00000d70 	.word	0x00000d70
     d54:	00000d84 	.word	0x00000d84
     d58:	00000d98 	.word	0x00000d98
		case (0):	delay.lsb = 1000000000u;	// 1s.
     d5c:	e3a035ee 	mov	r3, #998244352	; 0x3b800000
     d60:	e283396b 	add	r3, r3, #1753088	; 0x1ac000
     d64:	e2833c0a 	add	r3, r3, #2560	; 0xa00
     d68:	e50b30b0 	str	r3, [fp, #-176]	; 0xb0
					break;
     d6c:	ea000038 	b	e54 <main+0x56c>

		case (1):	delay.lsb = 2000000000u;	// 2s.
     d70:	e3a03477 	mov	r3, #1996488704	; 0x77000000
     d74:	e28339d6 	add	r3, r3, #3506176	; 0x358000
     d78:	e2833b05 	add	r3, r3, #5120	; 0x1400
     d7c:	e50b30b0 	str	r3, [fp, #-176]	; 0xb0
					break;
     d80:	ea000033 	b	e54 <main+0x56c>

		case (2):	delay.lsb = 3000000000u;	// 3s.
     d84:	e3a034b2 	mov	r3, #-1308622848	; 0xb2000000
     d88:	e283360d 	add	r3, r3, #13631488	; 0xd00000
     d8c:	e2833c5e 	add	r3, r3, #24064	; 0x5e00
     d90:	e50b30b0 	str	r3, [fp, #-176]	; 0xb0
					break;
     d94:	ea00002e 	b	e54 <main+0x56c>

		case (3):	delay.lsb = 4000000000u;	// 4s.
     d98:	e3a034ee 	mov	r3, #-301989888	; 0xee000000
     d9c:	e283386b 	add	r3, r3, #7012352	; 0x6b0000
     da0:	e2833b0a 	add	r3, r3, #10240	; 0x2800
     da4:	e50b30b0 	str	r3, [fp, #-176]	; 0xb0
					break;
     da8:	ea000029 	b	e54 <main+0x56c>

		default:	PTARM_MUTEX_LOCK();
     dac:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
					printf("!! Scheduling error: Unknown hardware thread.\n  ");
     db0:	e59f0484 	ldr	r0, [pc, #1156]	; 123c <main+0x954>
     db4:	ebfffd91 	bl	400 <ptarmUartOutputStr>
					// "Task = xxx, SP = xxx, PC = xxx, hwThreadId = xxx."
					printf("Task = "); printf(localScheduler.name);
     db8:	e59f0480 	ldr	r0, [pc, #1152]	; 1240 <main+0x958>
     dbc:	ebfffd8f 	bl	400 <ptarmUartOutputStr>
     dc0:	e51b30ac 	ldr	r3, [fp, #-172]	; 0xac
     dc4:	e1a00003 	mov	r0, r3
     dc8:	ebfffd8c 	bl	400 <ptarmUartOutputStr>
					printf(", SP = "); printf(hex((unsigned int)localScheduler.sp));
     dcc:	e59f0470 	ldr	r0, [pc, #1136]	; 1244 <main+0x95c>
     dd0:	ebfffd8a 	bl	400 <ptarmUartOutputStr>
     dd4:	e51b30a0 	ldr	r3, [fp, #-160]	; 0xa0
     dd8:	e1a00003 	mov	r0, r3
     ddc:	ebfffe18 	bl	644 <hex>
     de0:	e1a03000 	mov	r3, r0
     de4:	e1a00003 	mov	r0, r3
     de8:	ebfffd84 	bl	400 <ptarmUartOutputStr>
					printf(", PC = "); printf(hex((unsigned int)localScheduler.pc));
     dec:	e59f0454 	ldr	r0, [pc, #1108]	; 1248 <main+0x960>
     df0:	ebfffd82 	bl	400 <ptarmUartOutputStr>
     df4:	e51b309c 	ldr	r3, [fp, #-156]	; 0x9c
     df8:	e1a00003 	mov	r0, r3
     dfc:	ebfffe10 	bl	644 <hex>
     e00:	e1a03000 	mov	r3, r0
     e04:	e1a00003 	mov	r0, r3
     e08:	ebfffd7c 	bl	400 <ptarmUartOutputStr>
					printf(", hwThreadId = "); printf(utoa(localScheduler.hwThreadId));
     e0c:	e59f0438 	ldr	r0, [pc, #1080]	; 124c <main+0x964>
     e10:	ebfffd7a 	bl	400 <ptarmUartOutputStr>
     e14:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     e18:	e1a00003 	mov	r0, r3
     e1c:	ebfffdcf 	bl	560 <utoa>
     e20:	e1a03000 	mov	r3, r0
     e24:	e1a00003 	mov	r0, r3
     e28:	ebfffd74 	bl	400 <ptarmUartOutputStr>
					printf("\n");
     e2c:	e59f0400 	ldr	r0, [pc, #1024]	; 1234 <main+0x94c>
     e30:	ebfffd72 	bl	400 <ptarmUartOutputStr>
					PTARM_MUTEX_UNLOCK();
     e34:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
					while (halt);
     e38:	e1a00000 	nop			; (mov r0, r0)
     e3c:	e59f33f4 	ldr	r3, [pc, #1012]	; 1238 <main+0x950>
     e40:	e5d33000 	ldrb	r3, [r3]
     e44:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     e48:	e3530000 	cmp	r3, #0, 0
     e4c:	1afffffa 	bne	e3c <main+0x554>
					break;
     e50:	e1a00000 	nop			; (mov r0, r0)
	}

	PTARM_TIME_GET(localScheduler.currentTime);
     e54:	ee870d08 	cdp	13, 8, cr0, cr7, cr8, {0}
     e58:	e1a02007 	mov	r2, r7
     e5c:	e1a03008 	mov	r3, r8
     e60:	e50b2054 	str	r2, [fp, #-84]	; 0x54
     e64:	e50b3050 	str	r3, [fp, #-80]	; 0x50
	PTARM_EOE_ENABLE(delay, localScheduler.currentTime);
     e68:	e51b3054 	ldr	r3, [fp, #-84]	; 0x54
     e6c:	e51b2050 	ldr	r2, [fp, #-80]	; 0x50
     e70:	e51b10b4 	ldr	r1, [fp, #-180]	; 0xb4
     e74:	e51b00b0 	ldr	r0, [fp, #-176]	; 0xb0
     e78:	e1a07003 	mov	r7, r3
     e7c:	e1a08002 	mov	r8, r2
     e80:	e0988000 	adds	r8, r8, r0
     e84:	e0a77001 	adc	r7, r7, r1
     e88:	ee270d08 	cdp	13, 2, cr0, cr7, cr8, {0}
	PTARM_TASK_RESTORE_CONTEXT(localScheduler.currentTask);
     e8c:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     e90:	e5933014 	ldr	r3, [r3, #20]
     e94:	e1a08003 	mov	r8, r3
     e98:	ee200c08 	cdp	12, 2, cr0, cr0, cr8, {0}
     e9c:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     ea0:	e5933010 	ldr	r3, [r3, #16]
     ea4:	e1a0d003 	mov	sp, r3
     ea8:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     eac:	e8bd1fff 	pop	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     eb0:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)

	safe_printf("!! Scheduling error: Oops!\n");
     eb4:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
     eb8:	e59f0390 	ldr	r0, [pc, #912]	; 1250 <main+0x968>
     ebc:	ebfffd4f 	bl	400 <ptarmUartOutputStr>
     ec0:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
}

// The tasks.
// Note that they are defined within the main function.
one: {
	while (loopForever) {
     ec4:	ea000023 	b	f58 <main+0x670>
		int i = 1;
     ec8:	e3a03001 	mov	r3, #1, 0
     ecc:	e50b3020 	str	r3, [fp, #-32]
		if (i) {
     ed0:	e51b3020 	ldr	r3, [fp, #-32]
     ed4:	e3530000 	cmp	r3, #0, 0
     ed8:	0a00001c 	beq	f50 <main+0x668>
			volatile unsigned int keys = 0;
     edc:	e3a03000 	mov	r3, #0, 0
     ee0:	e50b30b8 	str	r3, [fp, #-184]	; 0xb8
			PTARM_READ_KEYS(keys);
     ee4:	e3a03102 	mov	r3, #-2147483648	; 0x80000000
     ee8:	e1a039c3 	asr	r3, r3, #19
     eec:	e5933000 	ldr	r3, [r3]
     ef0:	e203300f 	and	r3, r3, #15, 0
     ef4:	e50b30b8 	str	r3, [fp, #-184]	; 0xb8
			ptarmLedGreenOutput(keys);
     ef8:	e51b30b8 	ldr	r3, [fp, #-184]	; 0xb8
     efc:	e3a02f7f 	mov	r2, #508	; 0x1fc
     f00:	e2822003 	add	r2, r2, #3, 0
     f04:	e1a01003 	mov	r1, r3
     f08:	e3e000ff 	mvn	r0, #255, 0	; 0xff
     f0c:	ebfffc5e 	bl	8c <ptarmLedOutput>
			
			volatile unsigned int switches = 0;
     f10:	e3a03000 	mov	r3, #0, 0
     f14:	e50b30bc 	str	r3, [fp, #-188]	; 0xbc
			PTARM_READ_SWITCHES(switches);
     f18:	e3a03102 	mov	r3, #-2147483648	; 0x80000000
     f1c:	e1a039c3 	asr	r3, r3, #19
     f20:	e5933000 	ldr	r3, [r3]
     f24:	e1a03223 	lsr	r3, r3, #4
     f28:	e3c334ff 	bic	r3, r3, #-16777216	; 0xff000000
     f2c:	e3c3373f 	bic	r3, r3, #16515072	; 0xfc0000
     f30:	e50b30bc 	str	r3, [fp, #-188]	; 0xbc
			ptarmLedRedOutput(switches);
     f34:	e51b30bc 	ldr	r3, [fp, #-188]	; 0xbc
     f38:	e3a02701 	mov	r2, #262144	; 0x40000
     f3c:	e2422001 	sub	r2, r2, #1, 0
     f40:	e1a01003 	mov	r1, r3
     f44:	e3e000f6 	mvn	r0, #246, 0	; 0xf6
     f48:	ebfffc4f 	bl	8c <ptarmLedOutput>
     f4c:	ea000001 	b	f58 <main+0x670>
		} else {
			printf("task one\n");
     f50:	e59f02fc 	ldr	r0, [pc, #764]	; 1254 <main+0x96c>
     f54:	ebfffd29 	bl	400 <ptarmUartOutputStr>
     f58:	e59f32f8 	ldr	r3, [pc, #760]	; 1258 <main+0x970>
     f5c:	e5d33000 	ldrb	r3, [r3]
     f60:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     f64:	e3530000 	cmp	r3, #0, 0
     f68:	1affffd6 	bne	ec8 <main+0x5e0>
		}
	}
}

two: {
	while (loopForever) {
     f6c:	ea000006 	b	f8c <main+0x6a4>
		int i = 0;
     f70:	e3a03000 	mov	r3, #0, 0
     f74:	e50b3024 	str	r3, [fp, #-36]	; 0x24
		if (i) {
     f78:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
     f7c:	e3530000 	cmp	r3, #0, 0
     f80:	0a000001 	beq	f8c <main+0x6a4>
			printf("task two\n");
     f84:	e59f02d0 	ldr	r0, [pc, #720]	; 125c <main+0x974>
     f88:	ebfffd1c 	bl	400 <ptarmUartOutputStr>
     f8c:	e59f32c4 	ldr	r3, [pc, #708]	; 1258 <main+0x970>
     f90:	e5d33000 	ldrb	r3, [r3]
     f94:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     f98:	e3530000 	cmp	r3, #0, 0
     f9c:	1afffff3 	bne	f70 <main+0x688>
		}
	}
}

three: {
	ptarmSevenSegOutput(0, 0x40);
     fa0:	e3a01040 	mov	r1, #64, 0	; 0x40
     fa4:	e3a00000 	mov	r0, #0, 0
     fa8:	ebfffc46 	bl	c8 <ptarmSevenSegOutput>
	ptarmSevenSegChar(1, 'A');
     fac:	e3a01041 	mov	r1, #65, 0	; 0x41
     fb0:	e3a00001 	mov	r0, #1, 0
     fb4:	ebfffc56 	bl	114 <ptarmSevenSegChar>
	ptarmSevenSegChar(2, 'B');
     fb8:	e3a01042 	mov	r1, #66, 0	; 0x42
     fbc:	e3a00002 	mov	r0, #2, 0
     fc0:	ebfffc53 	bl	114 <ptarmSevenSegChar>
	ptarmSevenSegChar(3, 'C');
     fc4:	e3a01043 	mov	r1, #67, 0	; 0x43
     fc8:	e3a00003 	mov	r0, #3, 0
     fcc:	ebfffc50 	bl	114 <ptarmSevenSegChar>
	ptarmSevenSegChar(4, 'D');
     fd0:	e3a01044 	mov	r1, #68, 0	; 0x44
     fd4:	e3a00004 	mov	r0, #4, 0
     fd8:	ebfffc4d 	bl	114 <ptarmSevenSegChar>
	ptarmSevenSegChar(5, 'E');
     fdc:	e3a01045 	mov	r1, #69, 0	; 0x45
     fe0:	e3a00005 	mov	r0, #5, 0
     fe4:	ebfffc4a 	bl	114 <ptarmSevenSegChar>
	ptarmSevenSegChar(6, 'F');
     fe8:	e3a01046 	mov	r1, #70, 0	; 0x46
     fec:	e3a00006 	mov	r0, #6, 0
     ff0:	ebfffc47 	bl	114 <ptarmSevenSegChar>
	
	unsigned int i = 0;
     ff4:	e3a03000 	mov	r3, #0, 0
     ff8:	e50b3010 	str	r3, [fp, #-16]
	while (loopForever) {
     ffc:	ea00001b 	b	1070 <main+0x788>
		ptarmSevenSegChar(7, utoa(i)[0]);
    1000:	e51b0010 	ldr	r0, [fp, #-16]
    1004:	ebfffd55 	bl	560 <utoa>
    1008:	e1a03000 	mov	r3, r0
    100c:	e5d33000 	ldrb	r3, [r3]
    1010:	e1a01003 	mov	r1, r3
    1014:	e3a00007 	mov	r0, #7, 0
    1018:	ebfffc3d 	bl	114 <ptarmSevenSegChar>
		i++;
    101c:	e51b3010 	ldr	r3, [fp, #-16]
    1020:	e2833001 	add	r3, r3, #1, 0
    1024:	e50b3010 	str	r3, [fp, #-16]
		i %= 9;
    1028:	e51b3010 	ldr	r3, [fp, #-16]
    102c:	e3a01009 	mov	r1, #9, 0
    1030:	e1a00003 	mov	r0, r3
    1034:	eb0000ca 	bl	1364 <__aeabi_uidivmod>
    1038:	e1a03001 	mov	r3, r1
    103c:	e50b3010 	str	r3, [fp, #-16]
		
		int j;
		for (j = 0; j < 100000; j++);
    1040:	e3a03000 	mov	r3, #0, 0
    1044:	e50b3014 	str	r3, [fp, #-20]
    1048:	ea000002 	b	1058 <main+0x770>
    104c:	e51b3014 	ldr	r3, [fp, #-20]
    1050:	e2833001 	add	r3, r3, #1, 0
    1054:	e50b3014 	str	r3, [fp, #-20]
    1058:	e51b2014 	ldr	r2, [fp, #-20]
    105c:	e3a03b61 	mov	r3, #99328	; 0x18400
    1060:	e2833fa7 	add	r3, r3, #668	; 0x29c
    1064:	e2833003 	add	r3, r3, #3, 0
    1068:	e1520003 	cmp	r2, r3
    106c:	dafffff6 	ble	104c <main+0x764>
    1070:	e59f31e0 	ldr	r3, [pc, #480]	; 1258 <main+0x970>
    1074:	e5d33000 	ldrb	r3, [r3]
    1078:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    107c:	e3530000 	cmp	r3, #0, 0
    1080:	1affffde 	bne	1000 <main+0x718>
	}
}

four: {
	ptarmLcdInit();
    1084:	ebfffc68 	bl	22c <ptarmLcdInit>
	printfLcd("Hello World!\nPTARM\n");
    1088:	e3a02c65 	mov	r2, #25856	; 0x6500
    108c:	e2822090 	add	r2, r2, #144, 0	; 0x90
    1090:	e3a01000 	mov	r1, #0, 0
    1094:	e3a00000 	mov	r0, #0, 0
    1098:	ebfffc42 	bl	1a8 <ptarmLcdOutput>
    109c:	e59f31bc 	ldr	r3, [pc, #444]	; 1260 <main+0x978>
    10a0:	e3a02000 	mov	r2, #0, 0
    10a4:	e5c32000 	strb	r2, [r3]
    10a8:	e5c32001 	strb	r2, [r3, #1]
    10ac:	e3a02c65 	mov	r2, #25856	; 0x6500
    10b0:	e2822090 	add	r2, r2, #144, 0	; 0x90
    10b4:	e3a01000 	mov	r1, #0, 0
    10b8:	e3a00080 	mov	r0, #128, 0	; 0x80
    10bc:	ebfffc39 	bl	1a8 <ptarmLcdOutput>
    10c0:	e59f019c 	ldr	r0, [pc, #412]	; 1264 <main+0x97c>
    10c4:	ebfffc6b 	bl	278 <ptarmLcdOutputStr>

	volatile unsigned int keys, lastKeys;
	PTARM_READ_KEYS(keys);
    10c8:	e3a03102 	mov	r3, #-2147483648	; 0x80000000
    10cc:	e1a039c3 	asr	r3, r3, #19
    10d0:	e5933000 	ldr	r3, [r3]
    10d4:	e203300f 	and	r3, r3, #15, 0
    10d8:	e50b30c0 	str	r3, [fp, #-192]	; 0xc0
	lastKeys = keys;
    10dc:	e51b30c0 	ldr	r3, [fp, #-192]	; 0xc0
    10e0:	e50b30c4 	str	r3, [fp, #-196]	; 0xc4
	bool updated = false;
    10e4:	e3a03000 	mov	r3, #0, 0
    10e8:	e54b3015 	strb	r3, [fp, #-21]
	
	while (loopForever) {
    10ec:	ea000035 	b	11c8 <main+0x8e0>
		PTARM_READ_KEYS(keys);
    10f0:	e3a03102 	mov	r3, #-2147483648	; 0x80000000
    10f4:	e1a039c3 	asr	r3, r3, #19
    10f8:	e5933000 	ldr	r3, [r3]
    10fc:	e203300f 	and	r3, r3, #15, 0
    1100:	e50b30c0 	str	r3, [fp, #-192]	; 0xc0

		if (keys != lastKeys) {
    1104:	e51b20c0 	ldr	r2, [fp, #-192]	; 0xc0
    1108:	e51b30c4 	ldr	r3, [fp, #-196]	; 0xc4
    110c:	e1520003 	cmp	r2, r3
    1110:	0a00002c 	beq	11c8 <main+0x8e0>
			if (keys != KEY_MASK) {
    1114:	e51b30c0 	ldr	r3, [fp, #-192]	; 0xc0
    1118:	e353000f 	cmp	r3, #15, 0
    111c:	0a000015 	beq	1178 <main+0x890>
				if (!updated) {
    1120:	e55b3015 	ldrb	r3, [fp, #-21]
    1124:	e3530000 	cmp	r3, #0, 0
    1128:	1a000024 	bne	11c0 <main+0x8d8>
					printfLcd(" A key is being    pressed!");
    112c:	e3a02c65 	mov	r2, #25856	; 0x6500
    1130:	e2822090 	add	r2, r2, #144, 0	; 0x90
    1134:	e3a01000 	mov	r1, #0, 0
    1138:	e3a00000 	mov	r0, #0, 0
    113c:	ebfffc19 	bl	1a8 <ptarmLcdOutput>
    1140:	e59f3118 	ldr	r3, [pc, #280]	; 1260 <main+0x978>
    1144:	e3a02000 	mov	r2, #0, 0
    1148:	e5c32000 	strb	r2, [r3]
    114c:	e5c32001 	strb	r2, [r3, #1]
    1150:	e3a02c65 	mov	r2, #25856	; 0x6500
    1154:	e2822090 	add	r2, r2, #144, 0	; 0x90
    1158:	e3a01000 	mov	r1, #0, 0
    115c:	e3a00080 	mov	r0, #128, 0	; 0x80
    1160:	ebfffc10 	bl	1a8 <ptarmLcdOutput>
    1164:	e59f00fc 	ldr	r0, [pc, #252]	; 1268 <main+0x980>
    1168:	ebfffc42 	bl	278 <ptarmLcdOutputStr>
					updated = true;
    116c:	e3a03001 	mov	r3, #1, 0
    1170:	e54b3015 	strb	r3, [fp, #-21]
    1174:	ea000011 	b	11c0 <main+0x8d8>
				}
			} else {
				printfLcd("  Press a key!");
    1178:	e3a02c65 	mov	r2, #25856	; 0x6500
    117c:	e2822090 	add	r2, r2, #144, 0	; 0x90
    1180:	e3a01000 	mov	r1, #0, 0
    1184:	e3a00000 	mov	r0, #0, 0
    1188:	ebfffc06 	bl	1a8 <ptarmLcdOutput>
    118c:	e59f30cc 	ldr	r3, [pc, #204]	; 1260 <main+0x978>
    1190:	e3a02000 	mov	r2, #0, 0
    1194:	e5c32000 	strb	r2, [r3]
    1198:	e5c32001 	strb	r2, [r3, #1]
    119c:	e3a02c65 	mov	r2, #25856	; 0x6500
    11a0:	e2822090 	add	r2, r2, #144, 0	; 0x90
    11a4:	e3a01000 	mov	r1, #0, 0
    11a8:	e3a00080 	mov	r0, #128, 0	; 0x80
    11ac:	ebfffbfd 	bl	1a8 <ptarmLcdOutput>
    11b0:	e59f00b4 	ldr	r0, [pc, #180]	; 126c <main+0x984>
    11b4:	ebfffc2f 	bl	278 <ptarmLcdOutputStr>
				updated = false;
    11b8:	e3a03000 	mov	r3, #0, 0
    11bc:	e54b3015 	strb	r3, [fp, #-21]
			}
			lastKeys = keys;
    11c0:	e51b30c0 	ldr	r3, [fp, #-192]	; 0xc0
    11c4:	e50b30c4 	str	r3, [fp, #-196]	; 0xc4
    11c8:	e59f3088 	ldr	r3, [pc, #136]	; 1258 <main+0x970>
    11cc:	e5d33000 	ldrb	r3, [r3]
    11d0:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    11d4:	e3530000 	cmp	r3, #0, 0
    11d8:	1affffc4 	bne	10f0 <main+0x808>
		}
	}
}

	return 0;
    11dc:	e3a03000 	mov	r3, #0, 0
}
    11e0:	e1a00003 	mov	r0, r3
    11e4:	e24bd00c 	sub	sp, fp, #12, 0
    11e8:	e8bd8980 	pop	{r7, r8, fp, pc}
    11ec:	00001534 	.word	0x00001534
    11f0:	00000d2c 	.word	0x00000d2c
    11f4:	00001418 	.word	0x00001418
    11f8:	00000ec4 	.word	0x00000ec4
    11fc:	0000163c 	.word	0x0000163c
    1200:	00001798 	.word	0x00001798
    1204:	0001ffe0 	.word	0x0001ffe0
    1208:	00000b74 	.word	0x00000b74
    120c:	00000f6c 	.word	0x00000f6c
    1210:	00001690 	.word	0x00001690
    1214:	00000bd8 	.word	0x00000bd8
    1218:	00000fa0 	.word	0x00000fa0
    121c:	000016e4 	.word	0x000016e4
    1220:	00000c3c 	.word	0x00000c3c
    1224:	00001084 	.word	0x00001084
    1228:	00001738 	.word	0x00001738
    122c:	00000ca0 	.word	0x00000ca0
    1230:	00001430 	.word	0x00001430
    1234:	00001460 	.word	0x00001460
    1238:	00001638 	.word	0x00001638
    123c:	00001464 	.word	0x00001464
    1240:	00001498 	.word	0x00001498
    1244:	000014a0 	.word	0x000014a0
    1248:	000014a8 	.word	0x000014a8
    124c:	000014b0 	.word	0x000014b0
    1250:	000014c0 	.word	0x000014c0
    1254:	000014dc 	.word	0x000014dc
    1258:	00001639 	.word	0x00001639
    125c:	000014e8 	.word	0x000014e8
    1260:	0000178c 	.word	0x0000178c
    1264:	000014f4 	.word	0x000014f4
    1268:	00001508 	.word	0x00001508
    126c:	00001524 	.word	0x00001524

00001270 <__aeabi_uidiv>:
    1270:	e2512001 	subs	r2, r1, #1, 0
    1274:	01a0f00e 	moveq	pc, lr
    1278:	3a000036 	bcc	1358 <__aeabi_uidiv+0xe8>
    127c:	e1500001 	cmp	r0, r1
    1280:	9a000022 	bls	1310 <__aeabi_uidiv+0xa0>
    1284:	e1110002 	tst	r1, r2
    1288:	0a000023 	beq	131c <__aeabi_uidiv+0xac>
    128c:	e311020e 	tst	r1, #-536870912	; 0xe0000000
    1290:	01a01181 	lsleq	r1, r1, #3
    1294:	03a03008 	moveq	r3, #8, 0
    1298:	13a03001 	movne	r3, #1, 0
    129c:	e3510201 	cmp	r1, #268435456	; 0x10000000
    12a0:	31510000 	cmpcc	r1, r0
    12a4:	31a01201 	lslcc	r1, r1, #4
    12a8:	31a03203 	lslcc	r3, r3, #4
    12ac:	3afffffa 	bcc	129c <__aeabi_uidiv+0x2c>
    12b0:	e3510102 	cmp	r1, #-2147483648	; 0x80000000
    12b4:	31510000 	cmpcc	r1, r0
    12b8:	31a01081 	lslcc	r1, r1, #1
    12bc:	31a03083 	lslcc	r3, r3, #1
    12c0:	3afffffa 	bcc	12b0 <__aeabi_uidiv+0x40>
    12c4:	e3a02000 	mov	r2, #0, 0
    12c8:	e1500001 	cmp	r0, r1
    12cc:	20400001 	subcs	r0, r0, r1
    12d0:	21822003 	orrcs	r2, r2, r3
    12d4:	e15000a1 	cmp	r0, r1, lsr #1
    12d8:	204000a1 	subcs	r0, r0, r1, lsr #1
    12dc:	218220a3 	orrcs	r2, r2, r3, lsr #1
    12e0:	e1500121 	cmp	r0, r1, lsr #2
    12e4:	20400121 	subcs	r0, r0, r1, lsr #2
    12e8:	21822123 	orrcs	r2, r2, r3, lsr #2
    12ec:	e15001a1 	cmp	r0, r1, lsr #3
    12f0:	204001a1 	subcs	r0, r0, r1, lsr #3
    12f4:	218221a3 	orrcs	r2, r2, r3, lsr #3
    12f8:	e3500000 	cmp	r0, #0, 0
    12fc:	11b03223 	lsrsne	r3, r3, #4
    1300:	11a01221 	lsrne	r1, r1, #4
    1304:	1affffef 	bne	12c8 <__aeabi_uidiv+0x58>
    1308:	e1a00002 	mov	r0, r2
    130c:	e1a0f00e 	mov	pc, lr
    1310:	03a00001 	moveq	r0, #1, 0
    1314:	13a00000 	movne	r0, #0, 0
    1318:	e1a0f00e 	mov	pc, lr
    131c:	e3510801 	cmp	r1, #65536	; 0x10000
    1320:	21a01821 	lsrcs	r1, r1, #16
    1324:	23a02010 	movcs	r2, #16, 0
    1328:	33a02000 	movcc	r2, #0, 0
    132c:	e3510c01 	cmp	r1, #256	; 0x100
    1330:	21a01421 	lsrcs	r1, r1, #8
    1334:	22822008 	addcs	r2, r2, #8, 0
    1338:	e3510010 	cmp	r1, #16, 0
    133c:	21a01221 	lsrcs	r1, r1, #4
    1340:	22822004 	addcs	r2, r2, #4, 0
    1344:	e3510004 	cmp	r1, #4, 0
    1348:	82822003 	addhi	r2, r2, #3, 0
    134c:	908220a1 	addls	r2, r2, r1, lsr #1
    1350:	e1a00230 	lsr	r0, r0, r2
    1354:	e1a0f00e 	mov	pc, lr
    1358:	e3500000 	cmp	r0, #0, 0
    135c:	13e00000 	mvnne	r0, #0, 0
    1360:	ea000007 	b	1384 <__aeabi_idiv0>

00001364 <__aeabi_uidivmod>:
    1364:	e3510000 	cmp	r1, #0, 0
    1368:	0afffffa 	beq	1358 <__aeabi_uidiv+0xe8>
    136c:	e92d4003 	push	{r0, r1, lr}
    1370:	ebffffbe 	bl	1270 <__aeabi_uidiv>
    1374:	e8bd4006 	pop	{r1, r2, lr}
    1378:	e0030092 	mul	r3, r2, r0
    137c:	e0411003 	sub	r1, r1, r3
    1380:	e1a0f00e 	mov	pc, lr

00001384 <__aeabi_idiv0>:
    1384:	e1a0f00e 	mov	pc, lr

Disassembly of section .text.memset:

00001540 <memset>:
    1540:	e3100003 	tst	r0, #3, 0
    1544:	e92d4010 	push	{r4, lr}
    1548:	0a000037 	beq	162c <memset+0xec>
    154c:	e3520000 	cmp	r2, #0, 0
    1550:	e2422001 	sub	r2, r2, #1, 0
    1554:	0a000032 	beq	1624 <memset+0xe4>
    1558:	e201c0ff 	and	ip, r1, #255, 0	; 0xff
    155c:	e1a03000 	mov	r3, r0
    1560:	ea000002 	b	1570 <memset+0x30>
    1564:	e3520000 	cmp	r2, #0, 0
    1568:	e2422001 	sub	r2, r2, #1, 0
    156c:	0a00002c 	beq	1624 <memset+0xe4>
    1570:	e4c3c001 	strb	ip, [r3], #1
    1574:	e3130003 	tst	r3, #3, 0
    1578:	1afffff9 	bne	1564 <memset+0x24>
    157c:	e3520003 	cmp	r2, #3, 0
    1580:	9a000020 	bls	1608 <memset+0xc8>
    1584:	e201e0ff 	and	lr, r1, #255, 0	; 0xff
    1588:	e18ee40e 	orr	lr, lr, lr, lsl #8
    158c:	e352000f 	cmp	r2, #15, 0
    1590:	e18ee80e 	orr	lr, lr, lr, lsl #16
    1594:	9a000010 	bls	15dc <memset+0x9c>
    1598:	e1a04002 	mov	r4, r2
    159c:	e283c010 	add	ip, r3, #16, 0
    15a0:	e2444010 	sub	r4, r4, #16, 0
    15a4:	e354000f 	cmp	r4, #15, 0
    15a8:	e50ce010 	str	lr, [ip, #-16]
    15ac:	e50ce00c 	str	lr, [ip, #-12]
    15b0:	e50ce008 	str	lr, [ip, #-8]
    15b4:	e50ce004 	str	lr, [ip, #-4]
    15b8:	e28cc010 	add	ip, ip, #16, 0
    15bc:	8afffff7 	bhi	15a0 <memset+0x60>
    15c0:	e242c010 	sub	ip, r2, #16, 0
    15c4:	e3ccc00f 	bic	ip, ip, #15, 0
    15c8:	e202200f 	and	r2, r2, #15, 0
    15cc:	e28cc010 	add	ip, ip, #16, 0
    15d0:	e3520003 	cmp	r2, #3, 0
    15d4:	e083300c 	add	r3, r3, ip
    15d8:	9a00000a 	bls	1608 <memset+0xc8>
    15dc:	e1a04003 	mov	r4, r3
    15e0:	e1a0c002 	mov	ip, r2
    15e4:	e24cc004 	sub	ip, ip, #4, 0
    15e8:	e35c0003 	cmp	ip, #3, 0
    15ec:	e484e004 	str	lr, [r4], #4
    15f0:	8afffffb 	bhi	15e4 <memset+0xa4>
    15f4:	e242c004 	sub	ip, r2, #4, 0
    15f8:	e3ccc003 	bic	ip, ip, #3, 0
    15fc:	e28cc004 	add	ip, ip, #4, 0
    1600:	e083300c 	add	r3, r3, ip
    1604:	e2022003 	and	r2, r2, #3, 0
    1608:	e3520000 	cmp	r2, #0, 0
    160c:	120110ff 	andne	r1, r1, #255, 0	; 0xff
    1610:	10832002 	addne	r2, r3, r2
    1614:	0a000002 	beq	1624 <memset+0xe4>
    1618:	e4c31001 	strb	r1, [r3], #1
    161c:	e1530002 	cmp	r3, r2
    1620:	1afffffc 	bne	1618 <memset+0xd8>
    1624:	e8bd4010 	pop	{r4, lr}
    1628:	e1a0f00e 	mov	pc, lr
    162c:	e1a03000 	mov	r3, r0
    1630:	eaffffd1 	b	157c <memset+0x3c>
