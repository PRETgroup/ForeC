
_build/test.elf:     file format elf32-littlearm

SYMBOL TABLE:
00000000 l    d  .text	00000000 .text
00000c54 l    d  .rodata	00000000 .rodata
00000ce8 l    d  .text.memset	00000000 .text.memset
00000ddc l    d  .data	00000000 .data
00000de0 l    d  .bss	00000000 .bss
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
00000000 l    df *ABS*	00000000 test.c
00000000 l    df *ABS*	00000000 memset.c
000006ec g     F .text	000001a8 ptarmCreateTask
00000de0 g     O .bss	00000002 ptarmLcdCharCount
00000894 g     F .text	00000054 foreMcGetIndex
00000278 g     F .text	0000013c ptarmLcdOutputStr
000003b4 g     F .text	0000004c ptarmUartOutputChar
00000e44 g       .bss	00000000 addr_stack_limit
00000400 g     F .text	0000004c ptarmUartOutputStr
00000ddc g     O .data	00000004 ptarmPreviousTaskStackEnd
0000044c g     F .text	00000114 itoa
0000008c g     F .text	0000003c ptarmLedOutput
00000560 g     F .text	000000e4 utoa
00000e44 g       .bss	00000000 bss_end
00000064 g       *ABS*	00000000 bss_size
00000de0 g       .data	00000000 bss_start
000000c8 g     F .text	0000004c ptarmSevenSegOutput
00000ce8 g     F .text.memset	000000f4 memset
000008e8 g     F .text	0000036c main
00000e38 g     O .bss	0000000c ptarmStringBuffer
000001a8 g     F .text	00000084 ptarmLcdOutput
0001efdc g       *ABS*	00000000 addr_stack_end
00000c54 g     O .rodata	00000010 hexMap
00000de4 g     O .bss	00000054 one
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
   c:	e59f2064 	ldr	r2, [pc, #100]	; 78 <bss_size+0x14>
  10:	e0810002 	add	r0, r1, r2
  14:	e580e000 	str	lr, [r0]
  18:	e59f005c 	ldr	r0, [pc, #92]	; 7c <bss_size+0x18>
  1c:	e59f105c 	ldr	r1, [pc, #92]	; 80 <bss_size+0x1c>
  20:	e59f205c 	ldr	r2, [pc, #92]	; 84 <bss_size+0x20>
  24:	e3520000 	cmp	r2, #0, 0
  28:	0a000003 	beq	3c <skip_bss>
  2c:	e3a04000 	mov	r4, #0, 0

00000030 <bss_loop>:
  30:	e4c04001 	strb	r4, [r0], #1
  34:	e2522001 	subs	r2, r2, #1, 0
  38:	1afffffc 	bne	30 <bss_loop>

0000003c <skip_bss>:
  3c:	ee001d00 	cdp	13, 0, cr1, cr0, cr0, {0}
  40:	e59fd040 	ldr	sp, [pc, #64]	; 88 <bss_size+0x24>

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
  68:	e59f2008 	ldr	r2, [pc, #8]	; 78 <bss_size+0x14>
  6c:	e0810002 	add	r0, r1, r2
  70:	e5901000 	ldr	r1, [r0]
  74:	e1a0f001 	mov	pc, r1
  78:	0001fff0 	.word	0x0001fff0
  7c:	00000de0 	.word	0x00000de0
  80:	00000e44 	.word	0x00000e44
  84:	00000064 	.word	0x00000064
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
 1a4:	00000c54 	.word	0x00000c54

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
 274:	00000de0 	.word	0x00000de0

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
 3b0:	00000de0 	.word	0x00000de0

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
 55c:	00000e38 	.word	0x00000e38

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
 640:	00000e38 	.word	0x00000e38

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
 6e8:	00000e38 	.word	0x00000e38

000006ec <ptarmCreateTask>:
//======================================================================

// Create a task. Checks that there will be enough memory.
// Thread-safe function.
void ptarmCreateTask(volatile Task *task, unsigned int *startPc, volatile LocalScheduler *localScheduler) {
 6ec:	e92d4b80 	push	{r7, r8, r9, fp, lr}
 6f0:	e28db010 	add	fp, sp, #16, 0
 6f4:	e24dd01c 	sub	sp, sp, #28, 0
 6f8:	e50b0020 	str	r0, [fp, #-32]
 6fc:	e50b1024 	str	r1, [fp, #-36]	; 0x24
 700:	e50b2028 	str	r2, [fp, #-40]	; 0x28
	PTARM_MUTEX_LOCK();
 704:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
	const unsigned int frameSize = 0x0100;
 708:	e3a03c01 	mov	r3, #256	; 0x100
 70c:	e50b3018 	str	r3, [fp, #-24]
	const unsigned int limit = 0x0200;		// 0x0200 * sizeof(unsigned int) byte sized stack.
 710:	e3a03c02 	mov	r3, #512	; 0x200
 714:	e50b301c 	str	r3, [fp, #-28]

	// Check that there is enough memory to create a task stack.
	if ((ptarmPreviousTaskStackEnd - &addr_stack_limit) < limit) {
 718:	e59f315c 	ldr	r3, [pc, #348]	; 87c <ptarmCreateTask+0x190>
 71c:	e5933000 	ldr	r3, [r3]
 720:	e1a02003 	mov	r2, r3
 724:	e59f3154 	ldr	r3, [pc, #340]	; 880 <ptarmCreateTask+0x194>
 728:	e0633002 	rsb	r3, r3, r2
 72c:	e1a03143 	asr	r3, r3, #2
 730:	e1a02003 	mov	r2, r3
 734:	e51b301c 	ldr	r3, [fp, #-28]
 738:	e1520003 	cmp	r2, r3
 73c:	2a00001b 	bcs	7b0 <ptarmCreateTask+0xc4>
		printf("PTARM_TASK_CREATE: Stack limit exceeded!\n");
 740:	e59f013c 	ldr	r0, [pc, #316]	; 884 <ptarmCreateTask+0x198>
 744:	ebffff2d 	bl	400 <ptarmUartOutputStr>
		printf("  Available amount: ");
 748:	e59f0138 	ldr	r0, [pc, #312]	; 888 <ptarmCreateTask+0x19c>
 74c:	ebffff2b 	bl	400 <ptarmUartOutputStr>
		printf(utoa((ptarmPreviousTaskStackEnd -  &addr_stack_limit)*sizeof(unsigned int)));
 750:	e59f3124 	ldr	r3, [pc, #292]	; 87c <ptarmCreateTask+0x190>
 754:	e5933000 	ldr	r3, [r3]
 758:	e1a02003 	mov	r2, r3
 75c:	e59f311c 	ldr	r3, [pc, #284]	; 880 <ptarmCreateTask+0x194>
 760:	e0633002 	rsb	r3, r3, r2
 764:	e1a00003 	mov	r0, r3
 768:	ebffff7c 	bl	560 <utoa>
 76c:	e1a03000 	mov	r3, r0
 770:	e1a00003 	mov	r0, r3
 774:	ebffff21 	bl	400 <ptarmUartOutputStr>
		printf(" bytes.\n");
 778:	e59f010c 	ldr	r0, [pc, #268]	; 88c <ptarmCreateTask+0x1a0>
 77c:	ebffff1f 	bl	400 <ptarmUartOutputStr>
		printf("  Requested amount: ");
 780:	e59f0108 	ldr	r0, [pc, #264]	; 890 <ptarmCreateTask+0x1a4>
 784:	ebffff1d 	bl	400 <ptarmUartOutputStr>
		printf(utoa(limit*sizeof(unsigned int)));
 788:	e51b301c 	ldr	r3, [fp, #-28]
 78c:	e1a03103 	lsl	r3, r3, #2
 790:	e1a00003 	mov	r0, r3
 794:	ebffff71 	bl	560 <utoa>
 798:	e1a03000 	mov	r3, r0
 79c:	e1a00003 	mov	r0, r3
 7a0:	ebffff16 	bl	400 <ptarmUartOutputStr>
		printf(" bytes.\n");
 7a4:	e59f00e0 	ldr	r0, [pc, #224]	; 88c <ptarmCreateTask+0x1a0>
 7a8:	ebffff14 	bl	400 <ptarmUartOutputStr>
		while(1);
 7ac:	eafffffe 	b	7ac <ptarmCreateTask+0xc0>
	}

	// Create a stack for the task.
	PTARM_TASK_CREATE_STACK(task, frameSize, startPc);
 7b0:	e59f30c4 	ldr	r3, [pc, #196]	; 87c <ptarmCreateTask+0x190>
 7b4:	e5932000 	ldr	r2, [r3]
 7b8:	e51b3018 	ldr	r3, [fp, #-24]
 7bc:	e1a03103 	lsl	r3, r3, #2
 7c0:	e2633000 	rsb	r3, r3, #0, 0
 7c4:	e0822003 	add	r2, r2, r3
 7c8:	e59f30ac 	ldr	r3, [pc, #172]	; 87c <ptarmCreateTask+0x190>
 7cc:	e5931000 	ldr	r1, [r3]
 7d0:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
 7d4:	e1a0800d 	mov	r8, sp
 7d8:	e1a0d002 	mov	sp, r2
 7dc:	e1a09001 	mov	r9, r1
 7e0:	e1a07003 	mov	r7, r3
 7e4:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 7e8:	e3a07000 	mov	r7, #0, 0
 7ec:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 7f0:	e52d9004 	push	{r9}		; (str r9, [sp, #-4]!)
 7f4:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 7f8:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 7fc:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 800:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 804:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 808:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 80c:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 810:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 814:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 818:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 81c:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 820:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
 824:	e1a0200d 	mov	r2, sp
 828:	e1a0d008 	mov	sp, r8
 82c:	e51b3020 	ldr	r3, [fp, #-32]
 830:	e5832010 	str	r2, [r3, #16]

	// Update where the last stack frame ends.
	ptarmPreviousTaskStackEnd = ptarmPreviousTaskStackEnd - limit;
 834:	e59f3040 	ldr	r3, [pc, #64]	; 87c <ptarmCreateTask+0x190>
 838:	e5932000 	ldr	r2, [r3]
 83c:	e51b301c 	ldr	r3, [fp, #-28]
 840:	e1a03103 	lsl	r3, r3, #2
 844:	e2633000 	rsb	r3, r3, #0, 0
 848:	e0823003 	add	r3, r2, r3
 84c:	e59f2028 	ldr	r2, [pc, #40]	; 87c <ptarmCreateTask+0x190>
 850:	e5823000 	str	r3, [r2]

	// Initialise the SPSR of the task.
	task->spsr = 0;
 854:	e51b3020 	ldr	r3, [fp, #-32]
 858:	e3a02000 	mov	r2, #0, 0
 85c:	e5832014 	str	r2, [r3, #20]
	
	// Initialise the static and current local schedulers.
	task->localScheduler = localScheduler;
 860:	e51b3020 	ldr	r3, [fp, #-32]
 864:	e51b2028 	ldr	r2, [fp, #-40]	; 0x28
 868:	e5832008 	str	r2, [r3, #8]

	/*
	// Task = xxx, FP = xxx, SP = xxx, PC = xxx.
	printf("Task = "); printf(task->name);
	printf(", FP = "); printf(hex(stackFrameStart));
	printf(", SP = "); printf(hex((unsigned int)(task->sp)));
	printf(", PC = "); printf(hex(task->sp[14]));
	printf(".\n");
	*/
	PTARM_MUTEX_UNLOCK();
 86c:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
}
 870:	e1a00000 	nop			; (mov r0, r0)
 874:	e24bd010 	sub	sp, fp, #16, 0
 878:	e8bd8b80 	pop	{r7, r8, r9, fp, pc}
 87c:	00000ddc 	.word	0x00000ddc
 880:	00000e44 	.word	0x00000e44
 884:	00000c64 	.word	0x00000c64
 888:	00000c90 	.word	0x00000c90
 88c:	00000ca8 	.word	0x00000ca8
 890:	00000cb4 	.word	0x00000cb4

00000894 <foreMcGetIndex>:
	)


// Maps the index of the buffer array to the index of the circular buffer.
const unsigned int foreMcGetIndex(const unsigned int indexPlusFirst, const unsigned int maxSize) {
 894:	e92d09c0 	push	{r6, r7, r8, fp}
 898:	e28db00c 	add	fp, sp, #12, 0
 89c:	e24dd010 	sub	sp, sp, #16, 0
 8a0:	e50b0018 	str	r0, [fp, #-24]
 8a4:	e50b101c 	str	r1, [fp, #-28]
	unsigned int quotient;
	PTARM_UNSIGNED_DIV(quotient, indexPlusFirst, maxSize);
 8a8:	e51b3018 	ldr	r3, [fp, #-24]
 8ac:	e51b201c 	ldr	r2, [fp, #-28]
 8b0:	e1a07003 	mov	r7, r3
 8b4:	e1a08002 	mov	r8, r2
 8b8:	ee076908 	cdp	9, 0, cr6, cr7, cr8, {0}
 8bc:	e1a03006 	mov	r3, r6
 8c0:	e50b3010 	str	r3, [fp, #-16]
	return (indexPlusFirst) - (quotient * maxSize);
 8c4:	e51b3010 	ldr	r3, [fp, #-16]
 8c8:	e51b201c 	ldr	r2, [fp, #-28]
 8cc:	e0030392 	mul	r3, r2, r3
 8d0:	e51b2018 	ldr	r2, [fp, #-24]
 8d4:	e0633002 	rsb	r3, r3, r2
}
 8d8:	e1a00003 	mov	r0, r3
 8dc:	e24bd00c 	sub	sp, fp, #12, 0
 8e0:	e8bd09c0 	pop	{r6, r7, r8, fp}
 8e4:	e1a0f00e 	mov	pc, lr

000008e8 <main>:

Task one = {.receiveBuffers = { NULL }};


int main() {
 8e8:	e92d4890 	push	{r4, r7, fp, lr}
 8ec:	e28db00c 	add	fp, sp, #12, 0
 8f0:	e24dd030 	sub	sp, sp, #48, 0	; 0x30
	// Only hardware thread 0 is allowed to execute this test.
	unsigned int hwThreadId;
	PTARM_THREAD_GET_ID(hwThreadId);
 8f4:	ee007d00 	cdp	13, 0, cr7, cr0, cr0, {0}
 8f8:	e1a03007 	mov	r3, r7
 8fc:	e50b3014 	str	r3, [fp, #-20]
	if (hwThreadId != 0) {
 900:	e51b3014 	ldr	r3, [fp, #-20]
 904:	e3530000 	cmp	r3, #0, 0
 908:	0a000001 	beq	914 <main+0x2c>
		return 0;
 90c:	e3a03000 	mov	r3, #0, 0
 910:	ea0000c9 	b	c3c <main+0x354>
	}
	
	printf("ForeMC buffer test\n");
 914:	e59f032c 	ldr	r0, [pc, #812]	; c48 <main+0x360>
 918:	ebfffeb8 	bl	400 <ptarmUartOutputStr>
	
	// Define and declare the buffer.
	FORECMC_BUFFER(int, 4, buffer);
 91c:	e24b3038 	sub	r3, fp, #56, 0	; 0x38
 920:	e3a02024 	mov	r2, #36, 0	; 0x24
 924:	e3a01000 	mov	r1, #0, 0
 928:	e1a00003 	mov	r0, r3
 92c:	eb0000ed 	bl	ce8 <memset>
 930:	e3a03001 	mov	r3, #1, 0
 934:	e50b3020 	str	r3, [fp, #-32]
 938:	e3a03004 	mov	r3, #4, 0
 93c:	e50b3018 	str	r3, [fp, #-24]
		
	// Read the last buffered data for the receiver.
	printf(utoa(FOREMC_BUFFER_READ_COUNT(buffer))); printf(":"); printf(utoa(FOREMC_BUFFER_AT_INDEX(buffer, FOREMC_BUFFER_READ_COUNT(buffer)))); printf("\n");
 940:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
 944:	e1a00003 	mov	r0, r3
 948:	ebffff04 	bl	560 <utoa>
 94c:	e1a03000 	mov	r3, r0
 950:	e1a00003 	mov	r0, r3
 954:	ebfffea9 	bl	400 <ptarmUartOutputStr>
 958:	e59f02ec 	ldr	r0, [pc, #748]	; c4c <main+0x364>
 95c:	ebfffea7 	bl	400 <ptarmUartOutputStr>
 960:	e51b2024 	ldr	r2, [fp, #-36]	; 0x24
 964:	e51b3028 	ldr	r3, [fp, #-40]	; 0x28
 968:	e0823003 	add	r3, r2, r3
 96c:	e1a02003 	mov	r2, r3
 970:	e51b3018 	ldr	r3, [fp, #-24]
 974:	e1a01003 	mov	r1, r3
 978:	e1a00002 	mov	r0, r2
 97c:	ebffffc4 	bl	894 <foreMcGetIndex>
 980:	e1a03000 	mov	r3, r0
 984:	e1a03103 	lsl	r3, r3, #2
 988:	e24b200c 	sub	r2, fp, #12, 0
 98c:	e0823003 	add	r3, r2, r3
 990:	e513302c 	ldr	r3, [r3, #-44]	; 0x2c
 994:	e1a00003 	mov	r0, r3
 998:	ebfffef0 	bl	560 <utoa>
 99c:	e1a03000 	mov	r3, r0
 9a0:	e1a00003 	mov	r0, r3
 9a4:	ebfffe95 	bl	400 <ptarmUartOutputStr>
 9a8:	e59f02a0 	ldr	r0, [pc, #672]	; c50 <main+0x368>
 9ac:	ebfffe93 	bl	400 <ptarmUartOutputStr>

	// Write data into the buffer
	FOREMC_BUFFER_SEND(buffer, 10);
 9b0:	e51b201c 	ldr	r2, [fp, #-28]
 9b4:	e51b3020 	ldr	r3, [fp, #-32]
 9b8:	e0823003 	add	r3, r2, r3
 9bc:	e1a02003 	mov	r2, r3
 9c0:	e51b3018 	ldr	r3, [fp, #-24]
 9c4:	e1a01003 	mov	r1, r3
 9c8:	e1a00002 	mov	r0, r2
 9cc:	ebffffb0 	bl	894 <foreMcGetIndex>
 9d0:	e1a03000 	mov	r3, r0
 9d4:	e1a03103 	lsl	r3, r3, #2
 9d8:	e24b200c 	sub	r2, fp, #12, 0
 9dc:	e0823003 	add	r3, r2, r3
 9e0:	e3a0200a 	mov	r2, #10, 0
 9e4:	e503202c 	str	r2, [r3, #-44]	; 0x2c
 9e8:	e51b301c 	ldr	r3, [fp, #-28]
 9ec:	e2833001 	add	r3, r3, #1, 0
 9f0:	e50b301c 	str	r3, [fp, #-28]
	FOREMC_BUFFER_SEND(buffer, 20);
 9f4:	e51b201c 	ldr	r2, [fp, #-28]
 9f8:	e51b3020 	ldr	r3, [fp, #-32]
 9fc:	e0823003 	add	r3, r2, r3
 a00:	e1a02003 	mov	r2, r3
 a04:	e51b3018 	ldr	r3, [fp, #-24]
 a08:	e1a01003 	mov	r1, r3
 a0c:	e1a00002 	mov	r0, r2
 a10:	ebffff9f 	bl	894 <foreMcGetIndex>
 a14:	e1a03000 	mov	r3, r0
 a18:	e1a03103 	lsl	r3, r3, #2
 a1c:	e24b200c 	sub	r2, fp, #12, 0
 a20:	e0823003 	add	r3, r2, r3
 a24:	e3a02014 	mov	r2, #20, 0
 a28:	e503202c 	str	r2, [r3, #-44]	; 0x2c
 a2c:	e51b301c 	ldr	r3, [fp, #-28]
 a30:	e2833001 	add	r3, r3, #1, 0
 a34:	e50b301c 	str	r3, [fp, #-28]

	// Read the last buffered data for the receiver.
	printf(utoa(FOREMC_BUFFER_READ_COUNT(buffer))); printf(":"); printf(utoa(FOREMC_BUFFER_AT_INDEX(buffer, FOREMC_BUFFER_READ_COUNT(buffer)))); printf("\n");
 a38:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
 a3c:	e1a00003 	mov	r0, r3
 a40:	ebfffec6 	bl	560 <utoa>
 a44:	e1a03000 	mov	r3, r0
 a48:	e1a00003 	mov	r0, r3
 a4c:	ebfffe6b 	bl	400 <ptarmUartOutputStr>
 a50:	e59f01f4 	ldr	r0, [pc, #500]	; c4c <main+0x364>
 a54:	ebfffe69 	bl	400 <ptarmUartOutputStr>
 a58:	e51b2024 	ldr	r2, [fp, #-36]	; 0x24
 a5c:	e51b3028 	ldr	r3, [fp, #-40]	; 0x28
 a60:	e0823003 	add	r3, r2, r3
 a64:	e1a02003 	mov	r2, r3
 a68:	e51b3018 	ldr	r3, [fp, #-24]
 a6c:	e1a01003 	mov	r1, r3
 a70:	e1a00002 	mov	r0, r2
 a74:	ebffff86 	bl	894 <foreMcGetIndex>
 a78:	e1a03000 	mov	r3, r0
 a7c:	e1a03103 	lsl	r3, r3, #2
 a80:	e24b200c 	sub	r2, fp, #12, 0
 a84:	e0823003 	add	r3, r2, r3
 a88:	e513302c 	ldr	r3, [r3, #-44]	; 0x2c
 a8c:	e1a00003 	mov	r0, r3
 a90:	ebfffeb2 	bl	560 <utoa>
 a94:	e1a03000 	mov	r3, r0
 a98:	e1a00003 	mov	r0, r3
 a9c:	ebfffe57 	bl	400 <ptarmUartOutputStr>
 aa0:	e59f01a8 	ldr	r0, [pc, #424]	; c50 <main+0x368>
 aa4:	ebfffe55 	bl	400 <ptarmUartOutputStr>

	// Swap the buffers.
	FOREMC_BUFFER_RELEASE(&buffer);
 aa8:	e51b3020 	ldr	r3, [fp, #-32]
 aac:	e50b3028 	str	r3, [fp, #-40]	; 0x28
 ab0:	e51b301c 	ldr	r3, [fp, #-28]
 ab4:	e50b3024 	str	r3, [fp, #-36]	; 0x24
 ab8:	e51b201c 	ldr	r2, [fp, #-28]
 abc:	e51b3020 	ldr	r3, [fp, #-32]
 ac0:	e0823003 	add	r3, r2, r3
 ac4:	e1a02003 	mov	r2, r3
 ac8:	e51b3018 	ldr	r3, [fp, #-24]
 acc:	e1a01003 	mov	r1, r3
 ad0:	e1a00002 	mov	r0, r2
 ad4:	ebffff6e 	bl	894 <foreMcGetIndex>
 ad8:	e1a03000 	mov	r3, r0
 adc:	e50b3020 	str	r3, [fp, #-32]
 ae0:	e3a03000 	mov	r3, #0, 0
 ae4:	e50b301c 	str	r3, [fp, #-28]
 ae8:	e51b4020 	ldr	r4, [fp, #-32]
 aec:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
 af0:	e2432001 	sub	r2, r3, #1, 0
 af4:	e51b3028 	ldr	r3, [fp, #-40]	; 0x28
 af8:	e0823003 	add	r3, r2, r3
 afc:	e1a02003 	mov	r2, r3
 b00:	e51b3018 	ldr	r3, [fp, #-24]
 b04:	e1a01003 	mov	r1, r3
 b08:	e1a00002 	mov	r0, r2
 b0c:	ebffff60 	bl	894 <foreMcGetIndex>
 b10:	e1a03000 	mov	r3, r0
 b14:	e1a03103 	lsl	r3, r3, #2
 b18:	e24b200c 	sub	r2, fp, #12, 0
 b1c:	e0823003 	add	r3, r2, r3
 b20:	e513202c 	ldr	r2, [r3, #-44]	; 0x2c
 b24:	e1a03104 	lsl	r3, r4, #2
 b28:	e24b100c 	sub	r1, fp, #12, 0
 b2c:	e0813003 	add	r3, r1, r3
 b30:	e503202c 	str	r2, [r3, #-44]	; 0x2c

	// Read the last (latest) buffered data for the receiver.
	printf(utoa(FOREMC_BUFFER_AT_INDEX(buffer, FOREMC_BUFFER_BOUND(-1, buffer)))); printf("\n");
 b34:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
 b38:	e3530000 	cmp	r3, #0, 0
 b3c:	0a000003 	beq	b50 <main+0x268>
 b40:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
 b44:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
 b48:	e2433001 	sub	r3, r3, #1, 0
 b4c:	ea000000 	b	b54 <main+0x26c>
 b50:	e3a03000 	mov	r3, #0, 0
 b54:	e51b2028 	ldr	r2, [fp, #-40]	; 0x28
 b58:	e0833002 	add	r3, r3, r2
 b5c:	e1a02003 	mov	r2, r3
 b60:	e51b3018 	ldr	r3, [fp, #-24]
 b64:	e1a01003 	mov	r1, r3
 b68:	e1a00002 	mov	r0, r2
 b6c:	ebffff48 	bl	894 <foreMcGetIndex>
 b70:	e1a03000 	mov	r3, r0
 b74:	e1a03103 	lsl	r3, r3, #2
 b78:	e24b200c 	sub	r2, fp, #12, 0
 b7c:	e0823003 	add	r3, r2, r3
 b80:	e513302c 	ldr	r3, [r3, #-44]	; 0x2c
 b84:	e1a00003 	mov	r0, r3
 b88:	ebfffe74 	bl	560 <utoa>
 b8c:	e1a03000 	mov	r3, r0
 b90:	e1a00003 	mov	r0, r3
 b94:	ebfffe19 	bl	400 <ptarmUartOutputStr>
 b98:	e59f00b0 	ldr	r0, [pc, #176]	; c50 <main+0x368>
 b9c:	ebfffe17 	bl	400 <ptarmUartOutputStr>
	
	int i;
	for (i = 0; i < FOREMC_BUFFER_READ_COUNT(buffer); i++) {
 ba0:	e3a03000 	mov	r3, #0, 0
 ba4:	e50b3010 	str	r3, [fp, #-16]
 ba8:	ea00001e 	b	c28 <main+0x340>
		printf(utoa(FOREMC_BUFFER_READ_COUNT(buffer))); printf(":"); printf(utoa(FOREMC_BUFFER_AT_INDEX(buffer, i))); printf("\n");
 bac:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
 bb0:	e1a00003 	mov	r0, r3
 bb4:	ebfffe69 	bl	560 <utoa>
 bb8:	e1a03000 	mov	r3, r0
 bbc:	e1a00003 	mov	r0, r3
 bc0:	ebfffe0e 	bl	400 <ptarmUartOutputStr>
 bc4:	e59f0080 	ldr	r0, [pc, #128]	; c4c <main+0x364>
 bc8:	ebfffe0c 	bl	400 <ptarmUartOutputStr>
 bcc:	e51b2028 	ldr	r2, [fp, #-40]	; 0x28
 bd0:	e51b3010 	ldr	r3, [fp, #-16]
 bd4:	e0823003 	add	r3, r2, r3
 bd8:	e1a02003 	mov	r2, r3
 bdc:	e51b3018 	ldr	r3, [fp, #-24]
 be0:	e1a01003 	mov	r1, r3
 be4:	e1a00002 	mov	r0, r2
 be8:	ebffff29 	bl	894 <foreMcGetIndex>
 bec:	e1a03000 	mov	r3, r0
 bf0:	e1a03103 	lsl	r3, r3, #2
 bf4:	e24b200c 	sub	r2, fp, #12, 0
 bf8:	e0823003 	add	r3, r2, r3
 bfc:	e513302c 	ldr	r3, [r3, #-44]	; 0x2c
 c00:	e1a00003 	mov	r0, r3
 c04:	ebfffe55 	bl	560 <utoa>
 c08:	e1a03000 	mov	r3, r0
 c0c:	e1a00003 	mov	r0, r3
 c10:	ebfffdfa 	bl	400 <ptarmUartOutputStr>
 c14:	e59f0034 	ldr	r0, [pc, #52]	; c50 <main+0x368>
 c18:	ebfffdf8 	bl	400 <ptarmUartOutputStr>
 c1c:	e51b3010 	ldr	r3, [fp, #-16]
 c20:	e2833001 	add	r3, r3, #1, 0
 c24:	e50b3010 	str	r3, [fp, #-16]
 c28:	e51b2024 	ldr	r2, [fp, #-36]	; 0x24
 c2c:	e51b3010 	ldr	r3, [fp, #-16]
 c30:	e1520003 	cmp	r2, r3
 c34:	caffffdc 	bgt	bac <main+0x2c4>
	}

	return 0;
 c38:	e3a03000 	mov	r3, #0, 0
}
 c3c:	e1a00003 	mov	r0, r3
 c40:	e24bd00c 	sub	sp, fp, #12, 0
 c44:	e8bd8890 	pop	{r4, r7, fp, pc}
 c48:	00000ccc 	.word	0x00000ccc
 c4c:	00000ce0 	.word	0x00000ce0
 c50:	00000ce4 	.word	0x00000ce4

Disassembly of section .text.memset:

00000ce8 <memset>:
 ce8:	e3100003 	tst	r0, #3, 0
 cec:	e92d4010 	push	{r4, lr}
 cf0:	0a000037 	beq	dd4 <memset+0xec>
 cf4:	e3520000 	cmp	r2, #0, 0
 cf8:	e2422001 	sub	r2, r2, #1, 0
 cfc:	0a000032 	beq	dcc <memset+0xe4>
 d00:	e201c0ff 	and	ip, r1, #255, 0	; 0xff
 d04:	e1a03000 	mov	r3, r0
 d08:	ea000002 	b	d18 <memset+0x30>
 d0c:	e3520000 	cmp	r2, #0, 0
 d10:	e2422001 	sub	r2, r2, #1, 0
 d14:	0a00002c 	beq	dcc <memset+0xe4>
 d18:	e4c3c001 	strb	ip, [r3], #1
 d1c:	e3130003 	tst	r3, #3, 0
 d20:	1afffff9 	bne	d0c <memset+0x24>
 d24:	e3520003 	cmp	r2, #3, 0
 d28:	9a000020 	bls	db0 <memset+0xc8>
 d2c:	e201e0ff 	and	lr, r1, #255, 0	; 0xff
 d30:	e18ee40e 	orr	lr, lr, lr, lsl #8
 d34:	e352000f 	cmp	r2, #15, 0
 d38:	e18ee80e 	orr	lr, lr, lr, lsl #16
 d3c:	9a000010 	bls	d84 <memset+0x9c>
 d40:	e1a04002 	mov	r4, r2
 d44:	e283c010 	add	ip, r3, #16, 0
 d48:	e2444010 	sub	r4, r4, #16, 0
 d4c:	e354000f 	cmp	r4, #15, 0
 d50:	e50ce010 	str	lr, [ip, #-16]
 d54:	e50ce00c 	str	lr, [ip, #-12]
 d58:	e50ce008 	str	lr, [ip, #-8]
 d5c:	e50ce004 	str	lr, [ip, #-4]
 d60:	e28cc010 	add	ip, ip, #16, 0
 d64:	8afffff7 	bhi	d48 <memset+0x60>
 d68:	e242c010 	sub	ip, r2, #16, 0
 d6c:	e3ccc00f 	bic	ip, ip, #15, 0
 d70:	e202200f 	and	r2, r2, #15, 0
 d74:	e28cc010 	add	ip, ip, #16, 0
 d78:	e3520003 	cmp	r2, #3, 0
 d7c:	e083300c 	add	r3, r3, ip
 d80:	9a00000a 	bls	db0 <memset+0xc8>
 d84:	e1a04003 	mov	r4, r3
 d88:	e1a0c002 	mov	ip, r2
 d8c:	e24cc004 	sub	ip, ip, #4, 0
 d90:	e35c0003 	cmp	ip, #3, 0
 d94:	e484e004 	str	lr, [r4], #4
 d98:	8afffffb 	bhi	d8c <memset+0xa4>
 d9c:	e242c004 	sub	ip, r2, #4, 0
 da0:	e3ccc003 	bic	ip, ip, #3, 0
 da4:	e28cc004 	add	ip, ip, #4, 0
 da8:	e083300c 	add	r3, r3, ip
 dac:	e2022003 	and	r2, r2, #3, 0
 db0:	e3520000 	cmp	r2, #0, 0
 db4:	120110ff 	andne	r1, r1, #255, 0	; 0xff
 db8:	10832002 	addne	r2, r3, r2
 dbc:	0a000002 	beq	dcc <memset+0xe4>
 dc0:	e4c31001 	strb	r1, [r3], #1
 dc4:	e1530002 	cmp	r3, r2
 dc8:	1afffffc 	bne	dc0 <memset+0xd8>
 dcc:	e8bd4010 	pop	{r4, lr}
 dd0:	e1a0f00e 	mov	pc, lr
 dd4:	e1a03000 	mov	r3, r0
 dd8:	eaffffd1 	b	d24 <memset+0x3c>
