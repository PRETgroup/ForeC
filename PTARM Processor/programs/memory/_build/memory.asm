
_build/memory.elf:     file format elf32-littlearm

SYMBOL TABLE:
00000000 l    d  .text	00000000 .text
00000998 l    d  .rodata	00000000 .rodata
00000a90 l    d  .bss	00000000 .bss
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
00000000 l    df *ABS*	00000000 memory.c
00000a90 g     O .bss	00000002 ptarmLcdCharCount
00000278 g     F .text	0000013c ptarmLcdOutputStr
000003b4 g     F .text	0000004c ptarmUartOutputChar
00000aa0 g       .bss	00000000 addr_stack_limit
00000400 g     F .text	0000004c ptarmUartOutputStr
0000044c g     F .text	00000114 itoa
0000008c g     F .text	0000003c ptarmLedOutput
00000560 g     F .text	000000e4 utoa
00000aa0 g       .bss	00000000 bss_end
00000010 g       *ABS*	00000000 bss_size
00000a90 g       .rodata	00000000 bss_start
000000c8 g     F .text	0000004c ptarmSevenSegOutput
000006ec g     F .text	000002ac main
00000a94 g     O .bss	0000000c ptarmStringBuffer
000001a8 g     F .text	00000084 ptarmLcdOutput
0001efdc g       *ABS*	00000000 addr_stack_end
00000998 g     O .rodata	00000010 hexMap
0001ffe0 g       *ABS*	00000000 eoe_table
00000644 g     F .text	000000a8 hex
0000022c g     F .text	0000004c ptarmLcdInit
00000114 g     F .text	00000094 ptarmSevenSegChar
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
  58:	eb0001a3 	bl	6ec <main>
  5c:	ee001d00 	cdp	13, 0, cr1, cr0, cr0, {0}
  60:	e3a02004 	mov	r2, #4, 0
  64:	e0010192 	mul	r1, r2, r1
  68:	e59f2008 	ldr	r2, [pc, #8]	; 78 <stack_setup_complete+0x20>
  6c:	e0810002 	add	r0, r1, r2
  70:	e5901000 	ldr	r1, [r0]
  74:	e1a0f001 	mov	pc, r1
  78:	0001fff0 	.word	0x0001fff0
  7c:	00000a90 	.word	0x00000a90
  80:	00000aa0 	.word	0x00000aa0
  84:	00000010 	.word	0x00000010
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
 1a4:	00000998 	.word	0x00000998

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
 274:	00000a90 	.word	0x00000a90

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
 3b0:	00000a90 	.word	0x00000a90

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
 55c:	00000a94 	.word	0x00000a94

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
 640:	00000a94 	.word	0x00000a94

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
 6e8:	00000a94 	.word	0x00000a94

000006ec <main>:
// Variable whose address is at the end of the PTARM hardware threads' stacks.
// Defined in the linker script.
extern unsigned int addr_stack_end;

int main() {
 6ec:	e92d4880 	push	{r7, fp, lr}
 6f0:	e28db008 	add	fp, sp, #8, 0
 6f4:	e24dd014 	sub	sp, sp, #20, 0
	// Only hardware thread 0 is allowed to execute this test.
	unsigned int hwThreadId;
	PTARM_THREAD_GET_ID(hwThreadId);
 6f8:	ee007d00 	cdp	13, 0, cr7, cr0, cr0, {0}
 6fc:	e1a03007 	mov	r3, r7
 700:	e50b3018 	str	r3, [fp, #-24]
	if (hwThreadId != 0) {
 704:	e51b3018 	ldr	r3, [fp, #-24]
 708:	e3530000 	cmp	r3, #0, 0
 70c:	0a000001 	beq	718 <main+0x2c>
		return 0;
 710:	e3a03000 	mov	r3, #0, 0
 714:	ea00008b 	b	948 <main+0x25c>
	}

	printf("Memory test\n");
 718:	e59f0234 	ldr	r0, [pc, #564]	; 954 <main+0x268>
 71c:	ebffff37 	bl	400 <ptarmUartOutputStr>
	printf("-----------\n");
 720:	e59f0230 	ldr	r0, [pc, #560]	; 958 <main+0x26c>
 724:	ebffff35 	bl	400 <ptarmUartOutputStr>
	printf("Memory range: 0x");
 728:	e59f022c 	ldr	r0, [pc, #556]	; 95c <main+0x270>
 72c:	ebffff33 	bl	400 <ptarmUartOutputStr>
	printf(hex((unsigned int)&addr_stack_limit));
 730:	e59f3228 	ldr	r3, [pc, #552]	; 960 <main+0x274>
 734:	e1a00003 	mov	r0, r3
 738:	ebffffc1 	bl	644 <hex>
 73c:	e1a03000 	mov	r3, r0
 740:	e1a00003 	mov	r0, r3
 744:	ebffff2d 	bl	400 <ptarmUartOutputStr>
	printf(" to 0x");
 748:	e59f0214 	ldr	r0, [pc, #532]	; 964 <main+0x278>
 74c:	ebffff2b 	bl	400 <ptarmUartOutputStr>
	printf(hex((unsigned int)&addr_stack_end));
 750:	e59f3210 	ldr	r3, [pc, #528]	; 968 <main+0x27c>
 754:	e1a00003 	mov	r0, r3
 758:	ebffffb9 	bl	644 <hex>
 75c:	e1a03000 	mov	r3, r0
 760:	e1a00003 	mov	r0, r3
 764:	ebffff25 	bl	400 <ptarmUartOutputStr>
	printf(" (");
 768:	e59f01fc 	ldr	r0, [pc, #508]	; 96c <main+0x280>
 76c:	ebffff23 	bl	400 <ptarmUartOutputStr>
	printf(utoa(1 + ((unsigned int)&addr_stack_end - (unsigned int)&addr_stack_limit)/sizeof(unsigned int)));
 770:	e59f21f0 	ldr	r2, [pc, #496]	; 968 <main+0x27c>
 774:	e59f31e4 	ldr	r3, [pc, #484]	; 960 <main+0x274>
 778:	e0633002 	rsb	r3, r3, r2
 77c:	e1a03123 	lsr	r3, r3, #2
 780:	e2833001 	add	r3, r3, #1, 0
 784:	e1a00003 	mov	r0, r3
 788:	ebffff74 	bl	560 <utoa>
 78c:	e1a03000 	mov	r3, r0
 790:	e1a00003 	mov	r0, r3
 794:	ebffff19 	bl	400 <ptarmUartOutputStr>
	printf(" ");
 798:	e59f01d0 	ldr	r0, [pc, #464]	; 970 <main+0x284>
 79c:	ebffff17 	bl	400 <ptarmUartOutputStr>
	printf(utoa(sizeof(unsigned int)));
 7a0:	e3a00004 	mov	r0, #4, 0
 7a4:	ebffff6d 	bl	560 <utoa>
 7a8:	e1a03000 	mov	r3, r0
 7ac:	e1a00003 	mov	r0, r3
 7b0:	ebffff12 	bl	400 <ptarmUartOutputStr>
	printf(" byte memory locations).\n");
 7b4:	e59f01b8 	ldr	r0, [pc, #440]	; 974 <main+0x288>
 7b8:	ebffff10 	bl	400 <ptarmUartOutputStr>

	printf("* Writing phase ... ");
 7bc:	e59f01b4 	ldr	r0, [pc, #436]	; 978 <main+0x28c>
 7c0:	ebffff0e 	bl	400 <ptarmUartOutputStr>
	unsigned int counter = 0;
 7c4:	e3a03000 	mov	r3, #0, 0
 7c8:	e50b3010 	str	r3, [fp, #-16]
	unsigned int *address;
	for (address = &addr_stack_limit; address <= &addr_stack_end; address++) {
 7cc:	e59f318c 	ldr	r3, [pc, #396]	; 960 <main+0x274>
 7d0:	e50b3014 	str	r3, [fp, #-20]
 7d4:	ea000008 	b	7fc <main+0x110>
		*address = counter;
 7d8:	e51b3014 	ldr	r3, [fp, #-20]
 7dc:	e51b2010 	ldr	r2, [fp, #-16]
 7e0:	e5832000 	str	r2, [r3]
		counter++;
 7e4:	e51b3010 	ldr	r3, [fp, #-16]
 7e8:	e2833001 	add	r3, r3, #1, 0
 7ec:	e50b3010 	str	r3, [fp, #-16]
 7f0:	e51b3014 	ldr	r3, [fp, #-20]
 7f4:	e2833004 	add	r3, r3, #4, 0
 7f8:	e50b3014 	str	r3, [fp, #-20]
 7fc:	e51b3014 	ldr	r3, [fp, #-20]
 800:	e59f2160 	ldr	r2, [pc, #352]	; 968 <main+0x27c>
 804:	e1530002 	cmp	r3, r2
 808:	9afffff2 	bls	7d8 <main+0xec>
	}
	printf(utoa(counter));
 80c:	e51b0010 	ldr	r0, [fp, #-16]
 810:	ebffff52 	bl	560 <utoa>
 814:	e1a03000 	mov	r3, r0
 818:	e1a00003 	mov	r0, r3
 81c:	ebfffef7 	bl	400 <ptarmUartOutputStr>
	printf(" ");
 820:	e59f0148 	ldr	r0, [pc, #328]	; 970 <main+0x284>
 824:	ebfffef5 	bl	400 <ptarmUartOutputStr>
	printf(utoa(sizeof(unsigned int)));
 828:	e3a00004 	mov	r0, #4, 0
 82c:	ebffff4b 	bl	560 <utoa>
 830:	e1a03000 	mov	r3, r0
 834:	e1a00003 	mov	r0, r3
 838:	ebfffef0 	bl	400 <ptarmUartOutputStr>
	printf(" byte memory locations.\n");
 83c:	e59f0138 	ldr	r0, [pc, #312]	; 97c <main+0x290>
 840:	ebfffeee 	bl	400 <ptarmUartOutputStr>

	printf("* Reading phase ... ");
 844:	e59f0134 	ldr	r0, [pc, #308]	; 980 <main+0x294>
 848:	ebfffeec 	bl	400 <ptarmUartOutputStr>
	counter = 0;
 84c:	e3a03000 	mov	r3, #0, 0
 850:	e50b3010 	str	r3, [fp, #-16]
	for (address = &addr_stack_limit; address <= &addr_stack_end; address++) {
 854:	e59f3104 	ldr	r3, [pc, #260]	; 960 <main+0x274>
 858:	e50b3014 	str	r3, [fp, #-20]
 85c:	ea000024 	b	8f4 <main+0x208>
		unsigned int value = *address;
 860:	e51b3014 	ldr	r3, [fp, #-20]
 864:	e5933000 	ldr	r3, [r3]
 868:	e50b301c 	str	r3, [fp, #-28]

		if (value != counter) {
 86c:	e51b201c 	ldr	r2, [fp, #-28]
 870:	e51b3010 	ldr	r3, [fp, #-16]
 874:	e1520003 	cmp	r2, r3
 878:	0a000017 	beq	8dc <main+0x1f0>
			printf("  address = ");
 87c:	e59f0100 	ldr	r0, [pc, #256]	; 984 <main+0x298>
 880:	ebfffede 	bl	400 <ptarmUartOutputStr>
			printf(hex((unsigned int)address));
 884:	e51b3014 	ldr	r3, [fp, #-20]
 888:	e1a00003 	mov	r0, r3
 88c:	ebffff6c 	bl	644 <hex>
 890:	e1a03000 	mov	r3, r0
 894:	e1a00003 	mov	r0, r3
 898:	ebfffed8 	bl	400 <ptarmUartOutputStr>

			printf(", value = ");
 89c:	e59f00e4 	ldr	r0, [pc, #228]	; 988 <main+0x29c>
 8a0:	ebfffed6 	bl	400 <ptarmUartOutputStr>
			printf(utoa(value));
 8a4:	e51b001c 	ldr	r0, [fp, #-28]
 8a8:	ebffff2c 	bl	560 <utoa>
 8ac:	e1a03000 	mov	r3, r0
 8b0:	e1a00003 	mov	r0, r3
 8b4:	ebfffed1 	bl	400 <ptarmUartOutputStr>

			printf(", counter = ");
 8b8:	e59f00cc 	ldr	r0, [pc, #204]	; 98c <main+0x2a0>
 8bc:	ebfffecf 	bl	400 <ptarmUartOutputStr>
			printf(utoa(counter));
 8c0:	e51b0010 	ldr	r0, [fp, #-16]
 8c4:	ebffff25 	bl	560 <utoa>
 8c8:	e1a03000 	mov	r3, r0
 8cc:	e1a00003 	mov	r0, r3
 8d0:	ebfffeca 	bl	400 <ptarmUartOutputStr>

			printf(".\n");
 8d4:	e59f00b4 	ldr	r0, [pc, #180]	; 990 <main+0x2a4>
 8d8:	ebfffec8 	bl	400 <ptarmUartOutputStr>
		}

		counter++;
 8dc:	e51b3010 	ldr	r3, [fp, #-16]
 8e0:	e2833001 	add	r3, r3, #1, 0
 8e4:	e50b3010 	str	r3, [fp, #-16]
 8e8:	e51b3014 	ldr	r3, [fp, #-20]
 8ec:	e2833004 	add	r3, r3, #4, 0
 8f0:	e50b3014 	str	r3, [fp, #-20]
 8f4:	e51b3014 	ldr	r3, [fp, #-20]
 8f8:	e59f2068 	ldr	r2, [pc, #104]	; 968 <main+0x27c>
 8fc:	e1530002 	cmp	r3, r2
 900:	9affffd6 	bls	860 <main+0x174>
	}
	printf(utoa(counter));
 904:	e51b0010 	ldr	r0, [fp, #-16]
 908:	ebffff14 	bl	560 <utoa>
 90c:	e1a03000 	mov	r3, r0
 910:	e1a00003 	mov	r0, r3
 914:	ebfffeb9 	bl	400 <ptarmUartOutputStr>
	printf(" ");
 918:	e59f0050 	ldr	r0, [pc, #80]	; 970 <main+0x284>
 91c:	ebfffeb7 	bl	400 <ptarmUartOutputStr>
	printf(utoa(sizeof(unsigned int)));
 920:	e3a00004 	mov	r0, #4, 0
 924:	ebffff0d 	bl	560 <utoa>
 928:	e1a03000 	mov	r3, r0
 92c:	e1a00003 	mov	r0, r3
 930:	ebfffeb2 	bl	400 <ptarmUartOutputStr>
	printf(" byte memory locations.\n");
 934:	e59f0040 	ldr	r0, [pc, #64]	; 97c <main+0x290>
 938:	ebfffeb0 	bl	400 <ptarmUartOutputStr>

	printf("Completed. ");
 93c:	e59f0050 	ldr	r0, [pc, #80]	; 994 <main+0x2a8>
 940:	ebfffeae 	bl	400 <ptarmUartOutputStr>

	return 0;
 944:	e3a03000 	mov	r3, #0, 0
}
 948:	e1a00003 	mov	r0, r3
 94c:	e24bd008 	sub	sp, fp, #8, 0
 950:	e8bd8880 	pop	{r7, fp, pc}
 954:	000009a8 	.word	0x000009a8
 958:	000009b8 	.word	0x000009b8
 95c:	000009c8 	.word	0x000009c8
 960:	00000aa0 	.word	0x00000aa0
 964:	000009dc 	.word	0x000009dc
 968:	0001efdc 	.word	0x0001efdc
 96c:	000009e4 	.word	0x000009e4
 970:	000009e8 	.word	0x000009e8
 974:	000009ec 	.word	0x000009ec
 978:	00000a08 	.word	0x00000a08
 97c:	00000a20 	.word	0x00000a20
 980:	00000a3c 	.word	0x00000a3c
 984:	00000a54 	.word	0x00000a54
 988:	00000a64 	.word	0x00000a64
 98c:	00000a70 	.word	0x00000a70
 990:	00000a80 	.word	0x00000a80
 994:	00000a84 	.word	0x00000a84
