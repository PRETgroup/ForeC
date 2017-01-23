
_build/dynamic.elf:     file format elf32-littlearm

SYMBOL TABLE:
00000000 l    d  .text	00000000 .text
00001ab8 l    d  .rodata	00000000 .rodata
00001c80 l    d  .text.memset	00000000 .text.memset
00001d74 l    d  .data	00000000 .data
00001e68 l    d  .bss	00000000 .bss
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
00000000 l    df *ABS*	00000000 dynamic.c
00000000 l    df *ABS*	00000000 memset.c
000006ec g     F .text	000001a8 ptarmCreateTask
00001e68 g     O .bss	00000002 ptarmLcdCharCount
00000894 g     F .text	00000054 foreMcGetIndex
00000278 g     F .text	0000013c ptarmLcdOutputStr
00001da8 g     O .data	0000002c two
00001f0c g     O .bss	00000050 priorityQueueLife
000003b4 g     F .text	0000004c ptarmUartOutputChar
00001f68 g       .bss	00000000 addr_stack_limit
00001ebc g     O .bss	00000050 priorityQueueMission
00001e2c g     O .data	0000003c globalScheduler
00000400 g     F .text	0000004c ptarmUartOutputStr
00001e6c g     O .bss	00000050 priorityQueueNonCritical
00001d74 g     O .data	00000004 ptarmPreviousTaskStackEnd
0000044c g     F .text	00000114 itoa
0000008c g     F .text	0000003c ptarmLedOutput
00000560 g     F .text	000000e4 utoa
00001f68 g       .bss	00000000 bss_end
00000100 g       *ABS*	00000000 bss_size
00001e68 g       .data	00000000 bss_start
000000c8 g     F .text	0000004c ptarmSevenSegOutput
00001c80 g     F .text.memset	000000f4 memset
000008e8 g     F .text	000011d0 main
00001f5c g     O .bss	0000000c ptarmStringBuffer
000001a8 g     F .text	00000084 ptarmLcdOutput
00001d79 g     O .data	00000001 loopForever
0000efdc g       *ABS*	00000000 addr_stack_end
00001ab8 g     O .rodata	00000010 hexMap
00001d7c g     O .data	0000002c one
0000ffe0 g       *ABS*	00000000 eoe_table
00001d78 g     O .data	00000001 halt
00000644 g     F .text	000000a8 hex
0000022c g     F .text	0000004c ptarmLcdInit
00001dd4 g     O .data	0000002c three
00000114 g     F .text	00000094 ptarmSevenSegChar
00001e00 g     O .data	0000002c four
0000ffdc g       *ABS*	00000000 addr_stack_start



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
      78:	0000fff0 	.word	0x0000fff0
      7c:	00001e68 	.word	0x00001e68
      80:	00001f68 	.word	0x00001f68
      84:	00000100 	.word	0x00000100
      88:	0000ffdc 	.word	0x0000ffdc

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
     1a4:	00001ab8 	.word	0x00001ab8

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
     274:	00001e68 	.word	0x00001e68

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
     3b0:	00001e68 	.word	0x00001e68

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
     55c:	00001f5c 	.word	0x00001f5c

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
     640:	00001f5c 	.word	0x00001f5c

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
     6e8:	00001f5c 	.word	0x00001f5c

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
     87c:	00001d74 	.word	0x00001d74
     880:	00001f68 	.word	0x00001f68
     884:	00001ac8 	.word	0x00001ac8
     888:	00001af4 	.word	0x00001af4
     88c:	00001b0c 	.word	0x00001b0c
     890:	00001b18 	.word	0x00001b18

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
										.counterLife = -1
									};

// Main entry point of the program that is executed by all hardware threads.
int main(void) {
     8e8:	e92d4980 	push	{r7, r8, fp, lr}
     8ec:	e28db00c 	add	fp, sp, #12, 0
     8f0:	e24dd0a0 	sub	sp, sp, #160, 0	; 0xa0
	// Create a local scheduler that uses the hardware thread's stack.
	ptarmCreateLocalScheduler(localScheduler, &&localScheduler);
     8f4:	ee007d00 	cdp	13, 0, cr7, cr0, cr0, {0}
     8f8:	e1a03007 	mov	r3, r7
     8fc:	e50b3020 	str	r3, [fp, #-32]
     900:	e24b3038 	sub	r3, fp, #56, 0	; 0x38
     904:	e3a02000 	mov	r2, #0, 0
     908:	e5832000 	str	r2, [r3]
     90c:	e5832004 	str	r2, [r3, #4]
     910:	e5832008 	str	r2, [r3, #8]
     914:	e583200c 	str	r2, [r3, #12]
     918:	e5832010 	str	r2, [r3, #16]
     91c:	e59f2f18 	ldr	r2, [pc, #3864]	; 183c <main+0xf54>
     920:	e24b3044 	sub	r3, fp, #68, 0	; 0x44
     924:	e8920007 	ldm	r2, {r0, r1, r2}
     928:	e8a30003 	stmia	r3!, {r0, r1}
     92c:	e5c32000 	strb	r2, [r3]
     930:	e1a01442 	asr	r1, r2, #8
     934:	e5c31001 	strb	r1, [r3, #1]
     938:	e2833002 	add	r3, r3, #2, 0
     93c:	e1a02822 	lsr	r2, r2, #16
     940:	e5c32000 	strb	r2, [r3]
     944:	e51b3020 	ldr	r3, [fp, #-32]
     948:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     94c:	e2833030 	add	r3, r3, #48, 0	; 0x30
     950:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     954:	e54b303b 	strb	r3, [fp, #-59]	; 0x3b
     958:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     95c:	e3a02068 	mov	r2, #104, 0	; 0x68
     960:	e3a01000 	mov	r1, #0, 0
     964:	e1a00003 	mov	r0, r3
     968:	eb0004c4 	bl	1c80 <memset>
     96c:	e24b3044 	sub	r3, fp, #68, 0	; 0x44
     970:	e50b30ac 	str	r3, [fp, #-172]	; 0xac
     974:	e51b3020 	ldr	r3, [fp, #-32]
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
     9a4:	e59f3e94 	ldr	r3, [pc, #3732]	; 1840 <main+0xf58>
     9a8:	e50b309c 	str	r3, [fp, #-156]	; 0x9c

	// Each hardware thread performs some type of start up work.
	switch (localScheduler.hwThreadId) {
     9ac:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     9b0:	e3530003 	cmp	r3, #3, 0
     9b4:	979ff103 	ldrls	pc, [pc, r3, lsl #2]
     9b8:	ea0000c1 	b	cc4 <main+0x3dc>
     9bc:	000009cc 	.word	0x000009cc
     9c0:	00000acc 	.word	0x00000acc
     9c4:	00000b94 	.word	0x00000b94
     9c8:	00000c2c 	.word	0x00000c2c
		case (0):;	// Hardware thread 0.

					safe_printf("Dynamic scheduling example.\n\n");
     9cc:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
     9d0:	e59f0e6c 	ldr	r0, [pc, #3692]	; 1844 <main+0xf5c>
     9d4:	ebfffe89 	bl	400 <ptarmUartOutputStr>
     9d8:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

					// Create a static schedule for hardware thread 0.
					// [one -> two]
					ptarmCreateTask(&one, &&one, &localScheduler);
     9dc:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
     9e0:	e59f3e60 	ldr	r3, [pc, #3680]	; 1848 <main+0xf60>
     9e4:	e1a01003 	mov	r1, r3
     9e8:	e59f0e5c 	ldr	r0, [pc, #3676]	; 184c <main+0xf64>
     9ec:	ebffff3e 	bl	6ec <ptarmCreateTask>
					ptarmCreateTask(&two, &&two, &localScheduler);
     9f0:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
     9f4:	e59f3e54 	ldr	r3, [pc, #3668]	; 1850 <main+0xf68>
     9f8:	e1a01003 	mov	r1, r3
     9fc:	e59f0e50 	ldr	r0, [pc, #3664]	; 1854 <main+0xf6c>
     a00:	ebffff39 	bl	6ec <ptarmCreateTask>
					staticSchedule[0] = &one;
     a04:	e59f3e40 	ldr	r3, [pc, #3648]	; 184c <main+0xf64>
     a08:	e50b3038 	str	r3, [fp, #-56]	; 0x38
					staticSchedule[1] = &two;
     a0c:	e59f3e40 	ldr	r3, [pc, #3648]	; 1854 <main+0xf6c>
     a10:	e50b3034 	str	r3, [fp, #-52]	; 0x34

					// Calculate the duration of the base period that can be used to execute tasks.
					localScheduler.basePeriodStartOverhead.msb = 0;
     a14:	e3a03000 	mov	r3, #0, 0
     a18:	e50b3074 	str	r3, [fp, #-116]	; 0x74
					localScheduler.basePeriodStartOverhead.lsb = 10000000;	// 0.1s
     a1c:	e3a03726 	mov	r3, #9961472	; 0x980000
     a20:	e2833c96 	add	r3, r3, #38400	; 0x9600
     a24:	e2833080 	add	r3, r3, #128, 0	; 0x80
     a28:	e50b3070 	str	r3, [fp, #-112]	; 0x70
					localScheduler.basePeriodEndOverhead.msb = 0;
     a2c:	e3a03000 	mov	r3, #0, 0
     a30:	e50b306c 	str	r3, [fp, #-108]	; 0x6c
					localScheduler.basePeriodEndOverhead.lsb = 10000000;	// 0.1s
     a34:	e3a03726 	mov	r3, #9961472	; 0x980000
     a38:	e2833c96 	add	r3, r3, #38400	; 0x9600
     a3c:	e2833080 	add	r3, r3, #128, 0	; 0x80
     a40:	e50b3068 	str	r3, [fp, #-104]	; 0x68
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);
     a44:	e59f3e0c 	ldr	r3, [pc, #3596]	; 1858 <main+0xf70>
     a48:	e5933004 	ldr	r3, [r3, #4]
     a4c:	e59f2e04 	ldr	r2, [pc, #3588]	; 1858 <main+0xf70>
     a50:	e5922008 	ldr	r2, [r2, #8]
     a54:	e51b106c 	ldr	r1, [fp, #-108]	; 0x6c
     a58:	e51b0068 	ldr	r0, [fp, #-104]	; 0x68
     a5c:	e1a07003 	mov	r7, r3
     a60:	e1a08002 	mov	r8, r2
     a64:	e0588000 	subs	r8, r8, r0
     a68:	e0c77001 	sbc	r7, r7, r1
     a6c:	e1a02007 	mov	r2, r7
     a70:	e1a03008 	mov	r3, r8
     a74:	e50b205c 	str	r2, [fp, #-92]	; 0x5c
     a78:	e50b3058 	str	r3, [fp, #-88]	; 0x58

					globalScheduler.localScheduler0 = &localScheduler;					// Set the global reference to the local scheduler.
     a7c:	e59f2dd4 	ldr	r2, [pc, #3540]	; 1858 <main+0xf70>
     a80:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     a84:	e5823014 	str	r3, [r2, #20]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler0);	// Register the EOE handler.
     a88:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     a8c:	e1a03103 	lsl	r3, r3, #2
     a90:	e59f2dc4 	ldr	r2, [pc, #3524]	; 185c <main+0xf74>
     a94:	e0833002 	add	r3, r3, r2
     a98:	e59f2dc0 	ldr	r2, [pc, #3520]	; 1860 <main+0xf78>
     a9c:	e5832000 	str	r2, [r3]

					PTARM_TIME_GET(globalScheduler.basePeriodFirstStart);				// Save the time stamp of the first base period.
     aa0:	ee870d08 	cdp	13, 8, cr0, cr7, cr8, {0}
     aa4:	e1a02007 	mov	r2, r7
     aa8:	e1a03008 	mov	r3, r8
     aac:	e59f1da4 	ldr	r1, [pc, #3492]	; 1858 <main+0xf70>
     ab0:	e581200c 	str	r2, [r1, #12]
     ab4:	e59f2d9c 	ldr	r2, [pc, #3484]	; 1858 <main+0xf70>
     ab8:	e5823010 	str	r3, [r2, #16]
					globalScheduler.isInitialised = true;								// Initialisation complete.
     abc:	e59f3d94 	ldr	r3, [pc, #3476]	; 1858 <main+0xf70>
     ac0:	e3a02001 	mov	r2, #1, 0
     ac4:	e5c32000 	strb	r2, [r3]
					break;
     ac8:	ea000090 	b	d10 <main+0x428>

		case (1):	// Hardware thread 1.

					// Create a static schedule for hardware thread 1.
					// [three -> four]
					ptarmCreateTask(&three, &&three, &localScheduler);
     acc:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
     ad0:	e59f3d8c 	ldr	r3, [pc, #3468]	; 1864 <main+0xf7c>
     ad4:	e1a01003 	mov	r1, r3
     ad8:	e59f0de8 	ldr	r0, [pc, #3560]	; 18c8 <main+0xfe0>
     adc:	ebffff02 	bl	6ec <ptarmCreateTask>
					ptarmCreateTask(&four, &&four, &localScheduler);
     ae0:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
     ae4:	e59f3d7c 	ldr	r3, [pc, #3452]	; 1868 <main+0xf80>
     ae8:	e1a01003 	mov	r1, r3
     aec:	e59f0de4 	ldr	r0, [pc, #3556]	; 18d8 <main+0xff0>
     af0:	ebfffefd 	bl	6ec <ptarmCreateTask>
					staticSchedule[0] = &three;
     af4:	e59f3dcc 	ldr	r3, [pc, #3532]	; 18c8 <main+0xfe0>
     af8:	e50b3038 	str	r3, [fp, #-56]	; 0x38
					staticSchedule[1] = &four;
     afc:	e59f3dd4 	ldr	r3, [pc, #3540]	; 18d8 <main+0xff0>
     b00:	e50b3034 	str	r3, [fp, #-52]	; 0x34

					// Calculate the duration of the base period that can be used to execute tasks.
					localScheduler.basePeriodStartOverhead.msb = 0;
     b04:	e3a03000 	mov	r3, #0, 0
     b08:	e50b3074 	str	r3, [fp, #-116]	; 0x74
					localScheduler.basePeriodStartOverhead.lsb = 10000000;	// 0.1s
     b0c:	e3a03726 	mov	r3, #9961472	; 0x980000
     b10:	e2833c96 	add	r3, r3, #38400	; 0x9600
     b14:	e2833080 	add	r3, r3, #128, 0	; 0x80
     b18:	e50b3070 	str	r3, [fp, #-112]	; 0x70
					localScheduler.basePeriodEndOverhead.msb = 0;
     b1c:	e3a03000 	mov	r3, #0, 0
     b20:	e50b306c 	str	r3, [fp, #-108]	; 0x6c
					localScheduler.basePeriodEndOverhead.lsb = 10000000;	// 0.1s
     b24:	e3a03726 	mov	r3, #9961472	; 0x980000
     b28:	e2833c96 	add	r3, r3, #38400	; 0x9600
     b2c:	e2833080 	add	r3, r3, #128, 0	; 0x80
     b30:	e50b3068 	str	r3, [fp, #-104]	; 0x68
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);
     b34:	e59f3d1c 	ldr	r3, [pc, #3356]	; 1858 <main+0xf70>
     b38:	e5933004 	ldr	r3, [r3, #4]
     b3c:	e59f2d14 	ldr	r2, [pc, #3348]	; 1858 <main+0xf70>
     b40:	e5922008 	ldr	r2, [r2, #8]
     b44:	e51b106c 	ldr	r1, [fp, #-108]	; 0x6c
     b48:	e51b0068 	ldr	r0, [fp, #-104]	; 0x68
     b4c:	e1a07003 	mov	r7, r3
     b50:	e1a08002 	mov	r8, r2
     b54:	e0588000 	subs	r8, r8, r0
     b58:	e0c77001 	sbc	r7, r7, r1
     b5c:	e1a02007 	mov	r2, r7
     b60:	e1a03008 	mov	r3, r8
     b64:	e50b205c 	str	r2, [fp, #-92]	; 0x5c
     b68:	e50b3058 	str	r3, [fp, #-88]	; 0x58

					globalScheduler.localScheduler1 = &localScheduler;					// Set the global reference to the local scheduler.
     b6c:	e59f2ce4 	ldr	r2, [pc, #3300]	; 1858 <main+0xf70>
     b70:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     b74:	e5823018 	str	r3, [r2, #24]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler1);	// Register the EOE handler.
     b78:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     b7c:	e1a03103 	lsl	r3, r3, #2
     b80:	e59f2cd4 	ldr	r2, [pc, #3284]	; 185c <main+0xf74>
     b84:	e0833002 	add	r3, r3, r2
     b88:	e59f2cdc 	ldr	r2, [pc, #3292]	; 186c <main+0xf84>
     b8c:	e5832000 	str	r2, [r3]
					break;
     b90:	ea00005e 	b	d10 <main+0x428>

		case (2):	// Hardware thread 2.

					staticSchedule[0] = NULL;
     b94:	e3a03000 	mov	r3, #0, 0
     b98:	e50b3038 	str	r3, [fp, #-56]	; 0x38

					localScheduler.basePeriodStartOverhead.msb = 0;
     b9c:	e3a03000 	mov	r3, #0, 0
     ba0:	e50b3074 	str	r3, [fp, #-116]	; 0x74
					localScheduler.basePeriodStartOverhead.lsb = 10000000;	// 0.1s
     ba4:	e3a03726 	mov	r3, #9961472	; 0x980000
     ba8:	e2833c96 	add	r3, r3, #38400	; 0x9600
     bac:	e2833080 	add	r3, r3, #128, 0	; 0x80
     bb0:	e50b3070 	str	r3, [fp, #-112]	; 0x70
					localScheduler.basePeriodEndOverhead.msb = 0;
     bb4:	e3a03000 	mov	r3, #0, 0
     bb8:	e50b306c 	str	r3, [fp, #-108]	; 0x6c
					localScheduler.basePeriodEndOverhead.lsb = 10000000;	// 0.1s
     bbc:	e3a03726 	mov	r3, #9961472	; 0x980000
     bc0:	e2833c96 	add	r3, r3, #38400	; 0x9600
     bc4:	e2833080 	add	r3, r3, #128, 0	; 0x80
     bc8:	e50b3068 	str	r3, [fp, #-104]	; 0x68
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);
     bcc:	e59f3c84 	ldr	r3, [pc, #3204]	; 1858 <main+0xf70>
     bd0:	e5933004 	ldr	r3, [r3, #4]
     bd4:	e59f2c7c 	ldr	r2, [pc, #3196]	; 1858 <main+0xf70>
     bd8:	e5922008 	ldr	r2, [r2, #8]
     bdc:	e51b106c 	ldr	r1, [fp, #-108]	; 0x6c
     be0:	e51b0068 	ldr	r0, [fp, #-104]	; 0x68
     be4:	e1a07003 	mov	r7, r3
     be8:	e1a08002 	mov	r8, r2
     bec:	e0588000 	subs	r8, r8, r0
     bf0:	e0c77001 	sbc	r7, r7, r1
     bf4:	e1a02007 	mov	r2, r7
     bf8:	e1a03008 	mov	r3, r8
     bfc:	e50b205c 	str	r2, [fp, #-92]	; 0x5c
     c00:	e50b3058 	str	r3, [fp, #-88]	; 0x58

					globalScheduler.localScheduler2 = &localScheduler;
     c04:	e59f2c4c 	ldr	r2, [pc, #3148]	; 1858 <main+0xf70>
     c08:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     c0c:	e582301c 	str	r3, [r2, #28]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler2);
     c10:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     c14:	e1a03103 	lsl	r3, r3, #2
     c18:	e59f2c3c 	ldr	r2, [pc, #3132]	; 185c <main+0xf74>
     c1c:	e0833002 	add	r3, r3, r2
     c20:	e59f2c48 	ldr	r2, [pc, #3144]	; 1870 <main+0xf88>
     c24:	e5832000 	str	r2, [r3]
					break;
     c28:	ea000038 	b	d10 <main+0x428>

		case (3):	// Hardware thread 3.

					staticSchedule[0] = NULL;
     c2c:	e3a03000 	mov	r3, #0, 0
     c30:	e50b3038 	str	r3, [fp, #-56]	; 0x38
			
					// Calculate the duration of the base period that can be used to execute tasks.
					localScheduler.basePeriodStartOverhead.msb = 0;
     c34:	e3a03000 	mov	r3, #0, 0
     c38:	e50b3074 	str	r3, [fp, #-116]	; 0x74
					localScheduler.basePeriodStartOverhead.lsb = 10000000;	// 0.1s
     c3c:	e3a03726 	mov	r3, #9961472	; 0x980000
     c40:	e2833c96 	add	r3, r3, #38400	; 0x9600
     c44:	e2833080 	add	r3, r3, #128, 0	; 0x80
     c48:	e50b3070 	str	r3, [fp, #-112]	; 0x70
					localScheduler.basePeriodEndOverhead.msb = 0;
     c4c:	e3a03000 	mov	r3, #0, 0
     c50:	e50b306c 	str	r3, [fp, #-108]	; 0x6c
					localScheduler.basePeriodEndOverhead.lsb = 10000000;	// 0.1s
     c54:	e3a03726 	mov	r3, #9961472	; 0x980000
     c58:	e2833c96 	add	r3, r3, #38400	; 0x9600
     c5c:	e2833080 	add	r3, r3, #128, 0	; 0x80
     c60:	e50b3068 	str	r3, [fp, #-104]	; 0x68
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);
     c64:	e59f3bec 	ldr	r3, [pc, #3052]	; 1858 <main+0xf70>
     c68:	e5933004 	ldr	r3, [r3, #4]
     c6c:	e59f2be4 	ldr	r2, [pc, #3044]	; 1858 <main+0xf70>
     c70:	e5922008 	ldr	r2, [r2, #8]
     c74:	e51b106c 	ldr	r1, [fp, #-108]	; 0x6c
     c78:	e51b0068 	ldr	r0, [fp, #-104]	; 0x68
     c7c:	e1a07003 	mov	r7, r3
     c80:	e1a08002 	mov	r8, r2
     c84:	e0588000 	subs	r8, r8, r0
     c88:	e0c77001 	sbc	r7, r7, r1
     c8c:	e1a02007 	mov	r2, r7
     c90:	e1a03008 	mov	r3, r8
     c94:	e50b205c 	str	r2, [fp, #-92]	; 0x5c
     c98:	e50b3058 	str	r3, [fp, #-88]	; 0x58

					globalScheduler.localScheduler3 = &localScheduler;
     c9c:	e59f2bb4 	ldr	r2, [pc, #2996]	; 1858 <main+0xf70>
     ca0:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     ca4:	e5823020 	str	r3, [r2, #32]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler3);
     ca8:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     cac:	e1a03103 	lsl	r3, r3, #2
     cb0:	e59f2ba4 	ldr	r2, [pc, #2980]	; 185c <main+0xf74>
     cb4:	e0833002 	add	r3, r3, r2
     cb8:	e59f2bb4 	ldr	r2, [pc, #2996]	; 1874 <main+0xf8c>
     cbc:	e5832000 	str	r2, [r3]
					break;
     cc0:	ea000012 	b	d10 <main+0x428>

		default:	// Unknown hardware thread ID.

					PTARM_MUTEX_LOCK();
     cc4:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
					printf("!! Initialisation error: Unknown hwThreadId = "); printf(utoa(localScheduler.hwThreadId)); printf("\n");
     cc8:	e59f0ba8 	ldr	r0, [pc, #2984]	; 1878 <main+0xf90>
     ccc:	ebfffdcb 	bl	400 <ptarmUartOutputStr>
     cd0:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     cd4:	e1a00003 	mov	r0, r3
     cd8:	ebfffe20 	bl	560 <utoa>
     cdc:	e1a03000 	mov	r3, r0
     ce0:	e1a00003 	mov	r0, r3
     ce4:	ebfffdc5 	bl	400 <ptarmUartOutputStr>
     ce8:	e59f0b8c 	ldr	r0, [pc, #2956]	; 187c <main+0xf94>
     cec:	ebfffdc3 	bl	400 <ptarmUartOutputStr>
					PTARM_MUTEX_UNLOCK();
     cf0:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
					while (halt);
     cf4:	e1a00000 	nop			; (mov r0, r0)
     cf8:	e59f3b80 	ldr	r3, [pc, #2944]	; 1880 <main+0xf98>
     cfc:	e5d33000 	ldrb	r3, [r3]
     d00:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     d04:	e3530000 	cmp	r3, #0, 0
     d08:	1afffffa 	bne	cf8 <main+0x410>
					break;
     d0c:	e1a00000 	nop			; (mov r0, r0)
	}

	// All hardware threads execute this.
	while(globalScheduler.isInitialised == false);
     d10:	e1a00000 	nop			; (mov r0, r0)
     d14:	e59f3b3c 	ldr	r3, [pc, #2876]	; 1858 <main+0xf70>
     d18:	e5d33000 	ldrb	r3, [r3]
     d1c:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     d20:	e3530000 	cmp	r3, #0, 0
     d24:	0afffffa 	beq	d14 <main+0x42c>
	localScheduler.basePeriodStart = globalScheduler.basePeriodFirstStart;
     d28:	e59f2b28 	ldr	r2, [pc, #2856]	; 1858 <main+0xf70>
     d2c:	e24b3080 	sub	r3, fp, #128, 0	; 0x80
     d30:	e282200c 	add	r2, r2, #12, 0
     d34:	e8920003 	ldm	r2, {r0, r1}
     d38:	e8830003 	stm	r3, {r0, r1}
	PTARM_GOTO(localScheduler);
     d3c:	ea000100 	b	1144 <main+0x85c>


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
     d40:	e1a00000 	nop			; (mov r0, r0)
     d44:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     d48:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     d4c:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     d50:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     d54:	e59f3afc 	ldr	r3, [pc, #2812]	; 1858 <main+0xf70>
     d58:	e5933014 	ldr	r3, [r3, #20]
     d5c:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     d60:	e58d7038 	str	r7, [sp, #56]	; 0x38
     d64:	e1a0200d 	mov	r2, sp
     d68:	e5832014 	str	r2, [r3, #20]
     d6c:	e59f3ae4 	ldr	r3, [pc, #2788]	; 1858 <main+0xf70>
     d70:	e5933014 	ldr	r3, [r3, #20]
     d74:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     d78:	e1a02007 	mov	r2, r7
     d7c:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler0);
     d80:	e59f3ad0 	ldr	r3, [pc, #2768]	; 1858 <main+0xf70>
     d84:	e5933014 	ldr	r3, [r3, #20]
     d88:	e593300c 	ldr	r3, [r3, #12]
     d8c:	e59f2ac4 	ldr	r2, [pc, #2756]	; 1858 <main+0xf70>
     d90:	e5922014 	ldr	r2, [r2, #20]
     d94:	e5922008 	ldr	r2, [r2, #8]
     d98:	e1a0d003 	mov	sp, r3
     d9c:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     da0:	ea00004a 	b	ed0 <main+0x5e8>
}

// For hardware thread 1.
eoeHandler1: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler1);
     da4:	e1a00000 	nop			; (mov r0, r0)
     da8:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     dac:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     db0:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     db4:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     db8:	e59f3a98 	ldr	r3, [pc, #2712]	; 1858 <main+0xf70>
     dbc:	e5933018 	ldr	r3, [r3, #24]
     dc0:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     dc4:	e58d7038 	str	r7, [sp, #56]	; 0x38
     dc8:	e1a0200d 	mov	r2, sp
     dcc:	e5832014 	str	r2, [r3, #20]
     dd0:	e59f3a80 	ldr	r3, [pc, #2688]	; 1858 <main+0xf70>
     dd4:	e5933018 	ldr	r3, [r3, #24]
     dd8:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     ddc:	e1a02007 	mov	r2, r7
     de0:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler1);
     de4:	e59f3a6c 	ldr	r3, [pc, #2668]	; 1858 <main+0xf70>
     de8:	e5933018 	ldr	r3, [r3, #24]
     dec:	e593300c 	ldr	r3, [r3, #12]
     df0:	e59f2a60 	ldr	r2, [pc, #2656]	; 1858 <main+0xf70>
     df4:	e5922018 	ldr	r2, [r2, #24]
     df8:	e5922008 	ldr	r2, [r2, #8]
     dfc:	e1a0d003 	mov	sp, r3
     e00:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     e04:	ea000031 	b	ed0 <main+0x5e8>
}

// For hardware thread 2.
eoeHandler2: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler2);
     e08:	e1a00000 	nop			; (mov r0, r0)
     e0c:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     e10:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     e14:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     e18:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     e1c:	e59f3a34 	ldr	r3, [pc, #2612]	; 1858 <main+0xf70>
     e20:	e593301c 	ldr	r3, [r3, #28]
     e24:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     e28:	e58d7038 	str	r7, [sp, #56]	; 0x38
     e2c:	e1a0200d 	mov	r2, sp
     e30:	e5832014 	str	r2, [r3, #20]
     e34:	e59f3a1c 	ldr	r3, [pc, #2588]	; 1858 <main+0xf70>
     e38:	e593301c 	ldr	r3, [r3, #28]
     e3c:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     e40:	e1a02007 	mov	r2, r7
     e44:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler2);
     e48:	e59f3a08 	ldr	r3, [pc, #2568]	; 1858 <main+0xf70>
     e4c:	e593301c 	ldr	r3, [r3, #28]
     e50:	e593300c 	ldr	r3, [r3, #12]
     e54:	e59f29fc 	ldr	r2, [pc, #2556]	; 1858 <main+0xf70>
     e58:	e592201c 	ldr	r2, [r2, #28]
     e5c:	e5922008 	ldr	r2, [r2, #8]
     e60:	e1a0d003 	mov	sp, r3
     e64:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     e68:	ea000018 	b	ed0 <main+0x5e8>
}

// For hardware thread 3.
eoeHandler3: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler3);
     e6c:	e1a00000 	nop			; (mov r0, r0)
     e70:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     e74:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     e78:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     e7c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     e80:	e59f39d0 	ldr	r3, [pc, #2512]	; 1858 <main+0xf70>
     e84:	e5933020 	ldr	r3, [r3, #32]
     e88:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     e8c:	e58d7038 	str	r7, [sp, #56]	; 0x38
     e90:	e1a0200d 	mov	r2, sp
     e94:	e5832014 	str	r2, [r3, #20]
     e98:	e59f39b8 	ldr	r3, [pc, #2488]	; 1858 <main+0xf70>
     e9c:	e5933020 	ldr	r3, [r3, #32]
     ea0:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     ea4:	e1a02007 	mov	r2, r7
     ea8:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler3);
     eac:	e59f39a4 	ldr	r3, [pc, #2468]	; 1858 <main+0xf70>
     eb0:	e5933020 	ldr	r3, [r3, #32]
     eb4:	e593300c 	ldr	r3, [r3, #12]
     eb8:	e59f2998 	ldr	r2, [pc, #2456]	; 1858 <main+0xf70>
     ebc:	e5922020 	ldr	r2, [r2, #32]
     ec0:	e5922008 	ldr	r2, [r2, #8]
     ec4:	e1a0d003 	mov	sp, r3
     ec8:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     ecc:	eaffffff 	b	ed0 <main+0x5e8>
}

eoeHandler: {
	// Assign the saved context to the preempted task.
	if (localScheduler.currentTask != NULL) {
     ed0:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     ed4:	e3530000 	cmp	r3, #0, 0
     ed8:	0a00001b 	beq	f4c <main+0x664>
	
		// "Preempted xxx."
		PTARM_MUTEX_LOCK();
     edc:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Preempted "); printf(localScheduler.currentTask->name); printf(".\n");
     ee0:	e59f09e4 	ldr	r0, [pc, #2532]	; 18cc <main+0xfe4>
     ee4:	ebfffd45 	bl	400 <ptarmUartOutputStr>
     ee8:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     eec:	e1a00003 	mov	r0, r3
     ef0:	ebfffd55 	bl	44c <itoa>
     ef4:	e1a03000 	mov	r3, r0
     ef8:	e1a00003 	mov	r0, r3
     efc:	ebfffd3f 	bl	400 <ptarmUartOutputStr>
     f00:	e59f097c 	ldr	r0, [pc, #2428]	; 1884 <main+0xf9c>
     f04:	ebfffd3d 	bl	400 <ptarmUartOutputStr>
     f08:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     f0c:	e5933000 	ldr	r3, [r3]
     f10:	e1a00003 	mov	r0, r3
     f14:	ebfffd39 	bl	400 <ptarmUartOutputStr>
     f18:	e59f0968 	ldr	r0, [pc, #2408]	; 1888 <main+0xfa0>
     f1c:	ebfffd37 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
     f20:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

		localScheduler.currentTask->state = PTARM_TASK_PREEMPTED;
     f24:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     f28:	e3a02001 	mov	r2, #1, 0
     f2c:	e5c3200c 	strb	r2, [r3, #12]
		localScheduler.currentTask->sp = localScheduler.preemptedSp;
     f30:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     f34:	e51b2098 	ldr	r2, [fp, #-152]	; 0x98
     f38:	e5832010 	str	r2, [r3, #16]
		localScheduler.currentTask->spsr = localScheduler.preemptedSpsr;
     f3c:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     f40:	e51b2094 	ldr	r2, [fp, #-148]	; 0x94
     f44:	e5832014 	str	r2, [r3, #20]
     f48:	ea000010 	b	f90 <main+0x6a8>
	} else {
		// A null task is only possible when the scheduler is preempted during the
		// dynamic scheduling phase.
	
		// "Preempted scheduler x."
		PTARM_MUTEX_LOCK();
     f4c:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Preempted "); printf(localScheduler.name); printf(".\n");
     f50:	e59f0974 	ldr	r0, [pc, #2420]	; 18cc <main+0xfe4>
     f54:	ebfffd29 	bl	400 <ptarmUartOutputStr>
     f58:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     f5c:	e1a00003 	mov	r0, r3
     f60:	ebfffd39 	bl	44c <itoa>
     f64:	e1a03000 	mov	r3, r0
     f68:	e1a00003 	mov	r0, r3
     f6c:	ebfffd23 	bl	400 <ptarmUartOutputStr>
     f70:	e59f090c 	ldr	r0, [pc, #2316]	; 1884 <main+0xf9c>
     f74:	ebfffd21 	bl	400 <ptarmUartOutputStr>
     f78:	e51b30ac 	ldr	r3, [fp, #-172]	; 0xac
     f7c:	e1a00003 	mov	r0, r3
     f80:	ebfffd1e 	bl	400 <ptarmUartOutputStr>
     f84:	e59f08fc 	ldr	r0, [pc, #2300]	; 1888 <main+0xfa0>
     f88:	ebfffd1c 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
     f8c:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
	}

	// If the preemption occured during the dynamic scheduling phase, then we know
	// that the base period has ended.
	if (localScheduler.phase == PTARM_SCHEDULER_DYNAMIC) {
     f90:	e55b3084 	ldrb	r3, [fp, #-132]	; 0x84
     f94:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     f98:	e3530002 	cmp	r3, #2, 0
     f9c:	1a000030 	bne	1064 <main+0x77c>
		// Prepare to resume the static scheduling phase.

		// Return back to the release phase.
		localScheduler.phase = PTARM_SCHEDULER_RELEASE;
     fa0:	e3a03000 	mov	r3, #0, 0
     fa4:	e54b3084 	strb	r3, [fp, #-132]	; 0x84

		if (localScheduler.hwThreadId == 0) {
     fa8:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     fac:	e3530000 	cmp	r3, #0, 0
     fb0:	1a000014 	bne	1008 <main+0x720>
		
			// Reset the dynamic scheduling lists.
			PTARM_SCHEDULER_DYNAMIC_LIST_RESET(globalScheduler);
     fb4:	e59f389c 	ldr	r3, [pc, #2204]	; 1858 <main+0xf70>
     fb8:	e3e02000 	mvn	r2, #0, 0
     fbc:	e5832030 	str	r2, [r3, #48]	; 0x30
     fc0:	e59f3890 	ldr	r3, [pc, #2192]	; 1858 <main+0xf70>
     fc4:	e3e02000 	mvn	r2, #0, 0
     fc8:	e5832034 	str	r2, [r3, #52]	; 0x34
     fcc:	e59f3884 	ldr	r3, [pc, #2180]	; 1858 <main+0xf70>
     fd0:	e3e02000 	mvn	r2, #0, 0
     fd4:	e5832038 	str	r2, [r3, #56]	; 0x38

			// "Base period xxx ended."
			PTARM_MUTEX_LOCK();
     fd8:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
			printf("Base period "); printf(utoa(localScheduler.basePeriodCounter)); printf(" ended.\n");
     fdc:	e59f08a8 	ldr	r0, [pc, #2216]	; 188c <main+0xfa4>
     fe0:	ebfffd06 	bl	400 <ptarmUartOutputStr>
     fe4:	e51b3078 	ldr	r3, [fp, #-120]	; 0x78
     fe8:	e1a00003 	mov	r0, r3
     fec:	ebfffd5b 	bl	560 <utoa>
     ff0:	e1a03000 	mov	r3, r0
     ff4:	e1a00003 	mov	r0, r3
     ff8:	ebfffd00 	bl	400 <ptarmUartOutputStr>
     ffc:	e59f088c 	ldr	r0, [pc, #2188]	; 1890 <main+0xfa8>
    1000:	ebfffcfe 	bl	400 <ptarmUartOutputStr>
			PTARM_MUTEX_UNLOCK();
    1004:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		}

		// Update the timestamp of the start of the next base period.
		localScheduler.basePeriodCounter++;
    1008:	e51b3078 	ldr	r3, [fp, #-120]	; 0x78
    100c:	e2833001 	add	r3, r3, #1, 0
    1010:	e50b3078 	str	r3, [fp, #-120]	; 0x78
		PTARM_ADD(localScheduler.basePeriodStart, localScheduler.basePeriodStart, globalScheduler.basePeriodDuration);
    1014:	e51b3080 	ldr	r3, [fp, #-128]	; 0x80
    1018:	e51b207c 	ldr	r2, [fp, #-124]	; 0x7c
    101c:	e59f1834 	ldr	r1, [pc, #2100]	; 1858 <main+0xf70>
    1020:	e5911004 	ldr	r1, [r1, #4]
    1024:	e59f082c 	ldr	r0, [pc, #2092]	; 1858 <main+0xf70>
    1028:	e5900008 	ldr	r0, [r0, #8]
    102c:	e1a07003 	mov	r7, r3
    1030:	e1a08002 	mov	r8, r2
    1034:	e0988000 	adds	r8, r8, r0
    1038:	e0a77001 	adc	r7, r7, r1
    103c:	e1a02007 	mov	r2, r7
    1040:	e1a03008 	mov	r3, r8
    1044:	e50b2080 	str	r2, [fp, #-128]	; 0x80
    1048:	e50b307c 	str	r3, [fp, #-124]	; 0x7c

		// Wait until the next base period starts. This synchronises the start of the base period with other hardware threads to minimise jitter.
		PTARM_DELAY(localScheduler.basePeriodStart);
    104c:	e51b3080 	ldr	r3, [fp, #-128]	; 0x80
    1050:	e51b207c 	ldr	r2, [fp, #-124]	; 0x7c
    1054:	e1a07003 	mov	r7, r3
    1058:	e1a08002 	mov	r8, r2
    105c:	ee470d08 	cdp	13, 4, cr0, cr7, cr8, {0}
    1060:	ea000036 	b	1140 <main+0x858>
	} else {
	
		// Add the task to the dynamic scheduling list.
		PTARM_MUTEX_LOCK();
    1064:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		// "Adding xxx to dynamic queue."
		printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Queuing "); printf(localScheduler.currentTask->name); printf(".\n");
    1068:	e59f085c 	ldr	r0, [pc, #2140]	; 18cc <main+0xfe4>
    106c:	ebfffce3 	bl	400 <ptarmUartOutputStr>
    1070:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
    1074:	e1a00003 	mov	r0, r3
    1078:	ebfffcf3 	bl	44c <itoa>
    107c:	e1a03000 	mov	r3, r0
    1080:	e1a00003 	mov	r0, r3
    1084:	ebfffcdd 	bl	400 <ptarmUartOutputStr>
    1088:	e59f0804 	ldr	r0, [pc, #2052]	; 1894 <main+0xfac>
    108c:	ebfffcdb 	bl	400 <ptarmUartOutputStr>
    1090:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    1094:	e5933000 	ldr	r3, [r3]
    1098:	e1a00003 	mov	r0, r3
    109c:	ebfffcd7 	bl	400 <ptarmUartOutputStr>
    10a0:	e59f07e0 	ldr	r0, [pc, #2016]	; 1888 <main+0xfa0>
    10a4:	ebfffcd5 	bl	400 <ptarmUartOutputStr>
		PTARM_SCHEDULER_DYNAMIC_LIST_PUSH_LIFE_MISSION(globalScheduler, localScheduler.currentTask);
    10a8:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    10ac:	e5d33004 	ldrb	r3, [r3, #4]
    10b0:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    10b4:	e3530000 	cmp	r3, #0, 0
    10b8:	1a00000d 	bne	10f4 <main+0x80c>
    10bc:	e59f3794 	ldr	r3, [pc, #1940]	; 1858 <main+0xf70>
    10c0:	e5933038 	ldr	r3, [r3, #56]	; 0x38
    10c4:	e2833001 	add	r3, r3, #1, 0
    10c8:	e59f2788 	ldr	r2, [pc, #1928]	; 1858 <main+0xf70>
    10cc:	e5823038 	str	r3, [r2, #56]	; 0x38
    10d0:	e59f3780 	ldr	r3, [pc, #1920]	; 1858 <main+0xf70>
    10d4:	e593202c 	ldr	r2, [r3, #44]	; 0x2c
    10d8:	e59f3778 	ldr	r3, [pc, #1912]	; 1858 <main+0xf70>
    10dc:	e5933038 	ldr	r3, [r3, #56]	; 0x38
    10e0:	e1a03103 	lsl	r3, r3, #2
    10e4:	e0823003 	add	r3, r2, r3
    10e8:	e51b208c 	ldr	r2, [fp, #-140]	; 0x8c
    10ec:	e5832000 	str	r2, [r3]
    10f0:	ea000011 	b	113c <main+0x854>
    10f4:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    10f8:	e5d33004 	ldrb	r3, [r3, #4]
    10fc:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1100:	e3530001 	cmp	r3, #1, 0
    1104:	1a00000c 	bne	113c <main+0x854>
    1108:	e59f3748 	ldr	r3, [pc, #1864]	; 1858 <main+0xf70>
    110c:	e5933034 	ldr	r3, [r3, #52]	; 0x34
    1110:	e2833001 	add	r3, r3, #1, 0
    1114:	e59f273c 	ldr	r2, [pc, #1852]	; 1858 <main+0xf70>
    1118:	e5823034 	str	r3, [r2, #52]	; 0x34
    111c:	e59f3734 	ldr	r3, [pc, #1844]	; 1858 <main+0xf70>
    1120:	e5932028 	ldr	r2, [r3, #40]	; 0x28
    1124:	e59f372c 	ldr	r3, [pc, #1836]	; 1858 <main+0xf70>
    1128:	e5933034 	ldr	r3, [r3, #52]	; 0x34
    112c:	e1a03103 	lsl	r3, r3, #2
    1130:	e0823003 	add	r3, r2, r3
    1134:	e51b208c 	ldr	r2, [fp, #-140]	; 0x8c
    1138:	e5832000 	str	r2, [r3]
		PTARM_MUTEX_UNLOCK();
    113c:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
	}

	PTARM_GOTO(localScheduler);
    1140:	eaffffff 	b	1144 <main+0x85c>
}


// Local scheduler for each hardware thread.
// It always begins each base period with the static scheduling phase, followed by the dynamic scheduling phase.
localScheduler: {
	/*
	// "Scheduler = xxx, Current Task = xxx."
	PTARM_MUTEX_LOCK();
	printf(itoa(localScheduler.hwThreadId)); printf(":Scheduler = "); printf(localScheduler.name); printf(", Current task = "); printf(localScheduler.currentTask->name); printf(".\n");
	PTARM_MUTEX_UNLOCK();
	*/

	switch (localScheduler.phase) {
    1144:	e55b3084 	ldrb	r3, [fp, #-132]	; 0x84
    1148:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    114c:	e3530001 	cmp	r3, #1, 0
    1150:	0a00004d 	beq	128c <main+0x9a4>
    1154:	e3530002 	cmp	r3, #2, 0
    1158:	0a00009c 	beq	13d0 <main+0xae8>
    115c:	e3530000 	cmp	r3, #0, 0
    1160:	1a00011f 	bne	15e4 <main+0xcfc>
		case (PTARM_SCHEDULER_RELEASE):
			
			// Go through the static schedule and release any eligible tasks.
			for (localScheduler.nextStaticTask = localScheduler.staticSchedule; (*localScheduler.nextStaticTask) != NULL; localScheduler.nextStaticTask++) {
    1164:	e51b3090 	ldr	r3, [fp, #-144]	; 0x90
    1168:	e50b3088 	str	r3, [fp, #-136]	; 0x88
    116c:	ea00002d 	b	1228 <main+0x940>
				
				volatile Task *currentTask = *localScheduler.nextStaticTask;
    1170:	e51b3088 	ldr	r3, [fp, #-136]	; 0x88
    1174:	e5933000 	ldr	r3, [r3]
    1178:	e50b3024 	str	r3, [fp, #-36]	; 0x24
				
				// If the task is paused, check if it can be released for execution (i.e., the minimum number of base periods has elapsed).
				if (currentTask->state == PTARM_TASK_PAUSED && (currentTask->earliestRelease <= localScheduler.basePeriodCounter)) {
    117c:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    1180:	e5d3300c 	ldrb	r3, [r3, #12]
    1184:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1188:	e3530000 	cmp	r3, #0, 0
    118c:	1a000022 	bne	121c <main+0x934>
    1190:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    1194:	e5932028 	ldr	r2, [r3, #40]	; 0x28
    1198:	e51b3078 	ldr	r3, [fp, #-120]	; 0x78
    119c:	e1520003 	cmp	r2, r3
    11a0:	8a00001d 	bhi	121c <main+0x934>
					
					// "Releasing xxx."
					PTARM_MUTEX_LOCK();
    11a4:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
					printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Releasing "); printf(currentTask->name); printf(".\n");
    11a8:	e59f071c 	ldr	r0, [pc, #1820]	; 18cc <main+0xfe4>
    11ac:	ebfffc93 	bl	400 <ptarmUartOutputStr>
    11b0:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
    11b4:	e1a00003 	mov	r0, r3
    11b8:	ebfffca3 	bl	44c <itoa>
    11bc:	e1a03000 	mov	r3, r0
    11c0:	e1a00003 	mov	r0, r3
    11c4:	ebfffc8d 	bl	400 <ptarmUartOutputStr>
    11c8:	e59f06c8 	ldr	r0, [pc, #1736]	; 1898 <main+0xfb0>
    11cc:	ebfffc8b 	bl	400 <ptarmUartOutputStr>
    11d0:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    11d4:	e5933000 	ldr	r3, [r3]
    11d8:	e1a00003 	mov	r0, r3
    11dc:	ebfffc87 	bl	400 <ptarmUartOutputStr>
    11e0:	e59f06a0 	ldr	r0, [pc, #1696]	; 1888 <main+0xfa0>
    11e4:	ebfffc85 	bl	400 <ptarmUartOutputStr>
					PTARM_MUTEX_UNLOCK();
    11e8:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
					
					// The minimum number of base periods has elapsed, so release the task.
					currentTask->state = PTARM_TASK_RELEASED;
    11ec:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    11f0:	e3a02002 	mov	r2, #2, 0
    11f4:	e5c3200c 	strb	r2, [r3, #12]
					
					// Update its last released timestamp.
					currentTask->lastRelease = localScheduler.basePeriodCounter;
    11f8:	e51b2078 	ldr	r2, [fp, #-120]	; 0x78
    11fc:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    1200:	e5832024 	str	r2, [r3, #36]	; 0x24
					
					// Update its next earliest release timestamp.
					currentTask->earliestRelease = (localScheduler.basePeriodCounter + currentTask->basePeriodsMin);
    1204:	e51b2078 	ldr	r2, [fp, #-120]	; 0x78
    1208:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    120c:	e5933020 	ldr	r3, [r3, #32]
    1210:	e0822003 	add	r2, r2, r3
    1214:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    1218:	e5832028 	str	r2, [r3, #40]	; 0x28
    121c:	e51b3088 	ldr	r3, [fp, #-136]	; 0x88
    1220:	e2833004 	add	r3, r3, #4, 0
    1224:	e50b3088 	str	r3, [fp, #-136]	; 0x88
    1228:	e51b3088 	ldr	r3, [fp, #-136]	; 0x88
    122c:	e5933000 	ldr	r3, [r3]
    1230:	e3530000 	cmp	r3, #0, 0
    1234:	1affffcd 	bne	1170 <main+0x888>
				}
			}
			
			// Reset the static schedule (to the first task).
			localScheduler.nextStaticTask = localScheduler.staticSchedule;
    1238:	e51b3090 	ldr	r3, [fp, #-144]	; 0x90
    123c:	e50b3088 	str	r3, [fp, #-136]	; 0x88
			
			// Continue through to the next case statement for the static scheduling phase.
			// Start time = basePeriodStartOverhead + basePeriodStart.
			localScheduler.phase = PTARM_SCHEDULER_STATIC;
    1240:	e3a03001 	mov	r3, #1, 0
    1244:	e54b3084 	strb	r3, [fp, #-132]	; 0x84
			PTARM_ADD(localScheduler.basePeriodStartAfterOverhead, localScheduler.basePeriodStartOverhead, localScheduler.basePeriodStart);
    1248:	e51b3074 	ldr	r3, [fp, #-116]	; 0x74
    124c:	e51b2070 	ldr	r2, [fp, #-112]	; 0x70
    1250:	e51b1080 	ldr	r1, [fp, #-128]	; 0x80
    1254:	e51b007c 	ldr	r0, [fp, #-124]	; 0x7c
    1258:	e1a07003 	mov	r7, r3
    125c:	e1a08002 	mov	r8, r2
    1260:	e0988000 	adds	r8, r8, r0
    1264:	e0a77001 	adc	r7, r7, r1
    1268:	e1a02007 	mov	r2, r7
    126c:	e1a03008 	mov	r3, r8
    1270:	e50b2064 	str	r2, [fp, #-100]	; 0x64
    1274:	e50b3060 	str	r3, [fp, #-96]	; 0x60
			PTARM_DELAY(localScheduler.basePeriodStartAfterOverhead);
    1278:	e51b3064 	ldr	r3, [fp, #-100]	; 0x64
    127c:	e51b2060 	ldr	r2, [fp, #-96]	; 0x60
    1280:	e1a07003 	mov	r7, r3
    1284:	e1a08002 	mov	r8, r2
    1288:	ee470d08 	cdp	13, 4, cr0, cr7, cr8, {0}
	
		case (PTARM_SCHEDULER_STATIC):;
			// Static scheduling phase.
			// Schedule all the tasks in its static schedule before going into the dynamic scheduling phase.

			// Get the next statically scheduled task.
			localScheduler.currentTask = *localScheduler.nextStaticTask;
    128c:	e51b3088 	ldr	r3, [fp, #-136]	; 0x88
    1290:	e5933000 	ldr	r3, [r3]
    1294:	e50b308c 	str	r3, [fp, #-140]	; 0x8c

			// Check if we have reached the end of the static schedule.
			if (localScheduler.currentTask != NULL) {
    1298:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    129c:	e3530000 	cmp	r3, #0, 0
    12a0:	0a00003c 	beq	1398 <main+0xab0>
				// The end of the static schedule has not been reached.

				// Update the next statically scheduled task.
				localScheduler.nextStaticTask++;
    12a4:	e51b3088 	ldr	r3, [fp, #-136]	; 0x88
    12a8:	e2833004 	add	r3, r3, #4, 0
    12ac:	e50b3088 	str	r3, [fp, #-136]	; 0x88

				// Execute the task if it has been preempted or released.
				if (localScheduler.currentTask->state == PTARM_TASK_PREEMPTED || localScheduler.currentTask->state == PTARM_TASK_RELEASED) {
    12b0:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    12b4:	e5d3300c 	ldrb	r3, [r3, #12]
    12b8:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    12bc:	e3530001 	cmp	r3, #1, 0
    12c0:	0a000004 	beq	12d8 <main+0x9f0>
    12c4:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    12c8:	e5d3300c 	ldrb	r3, [r3, #12]
    12cc:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    12d0:	e3530002 	cmp	r3, #2, 0
    12d4:	1affff9a 	bne	1144 <main+0x85c>
					
					// "Executing xxx."
					PTARM_MUTEX_LOCK();
    12d8:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
					printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Executing "); printf(localScheduler.currentTask->name); printf(".\n");
    12dc:	e59f05e8 	ldr	r0, [pc, #1512]	; 18cc <main+0xfe4>
    12e0:	ebfffc46 	bl	400 <ptarmUartOutputStr>
    12e4:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
    12e8:	e1a00003 	mov	r0, r3
    12ec:	ebfffc56 	bl	44c <itoa>
    12f0:	e1a03000 	mov	r3, r0
    12f4:	e1a00003 	mov	r0, r3
    12f8:	ebfffc40 	bl	400 <ptarmUartOutputStr>
    12fc:	e59f0598 	ldr	r0, [pc, #1432]	; 189c <main+0xfb4>
    1300:	ebfffc3e 	bl	400 <ptarmUartOutputStr>
    1304:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    1308:	e5933000 	ldr	r3, [r3]
    130c:	e1a00003 	mov	r0, r3
    1310:	ebfffc3a 	bl	400 <ptarmUartOutputStr>
    1314:	e59f056c 	ldr	r0, [pc, #1388]	; 1888 <main+0xfa0>
    1318:	ebfffc38 	bl	400 <ptarmUartOutputStr>
					PTARM_MUTEX_UNLOCK();
    131c:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

					// Set the task's deadline in this base period to be the end of its statically allocated execution time.
					PTARM_TIME_GET(localScheduler.currentTime);
    1320:	ee870d08 	cdp	13, 8, cr0, cr7, cr8, {0}
    1324:	e1a02007 	mov	r2, r7
    1328:	e1a03008 	mov	r3, r8
    132c:	e50b2054 	str	r2, [fp, #-84]	; 0x54
    1330:	e50b3050 	str	r3, [fp, #-80]	; 0x50
					PTARM_EOE_ENABLE(localScheduler.currentTask->allocatedTime, localScheduler.currentTime);
    1334:	e51b3054 	ldr	r3, [fp, #-84]	; 0x54
    1338:	e51b2050 	ldr	r2, [fp, #-80]	; 0x50
    133c:	e51b108c 	ldr	r1, [fp, #-140]	; 0x8c
    1340:	e5911018 	ldr	r1, [r1, #24]
    1344:	e51b008c 	ldr	r0, [fp, #-140]	; 0x8c
    1348:	e590001c 	ldr	r0, [r0, #28]
    134c:	e1a07003 	mov	r7, r3
    1350:	e1a08002 	mov	r8, r2
    1354:	e0988000 	adds	r8, r8, r0
    1358:	e0a77001 	adc	r7, r7, r1
    135c:	ee270d08 	cdp	13, 2, cr0, cr7, cr8, {0}
					
					// (Re)set the task's local scheduler to this static local scheduler.
					PTARM_TASK_SET_SCHEDULER(localScheduler.currentTask, &localScheduler);
    1360:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    1364:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
    1368:	e5832008 	str	r2, [r3, #8]

					// Context switch to the current task.
					PTARM_TASK_RESTORE_CONTEXT(localScheduler.currentTask);
    136c:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    1370:	e5933014 	ldr	r3, [r3, #20]
    1374:	e1a08003 	mov	r8, r3
    1378:	ee200c08 	cdp	12, 2, cr0, cr0, cr8, {0}
    137c:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    1380:	e5933010 	ldr	r3, [r3, #16]
    1384:	e1a0d003 	mov	sp, r3
    1388:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
    138c:	e8bd1fff 	pop	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    1390:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)
    1394:	ea00000d 	b	13d0 <main+0xae8>
				} else {
					// Pick the next task to execute instead.
					goto localScheduler;
				}
			} else {
				// The end of the static schedule has been reached. Prepare for the dynamic scheduling phase.
				
				// "Dynamic phase."
				PTARM_MUTEX_LOCK();
    1398:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
				printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Dynamic phase.\n");
    139c:	e59f0528 	ldr	r0, [pc, #1320]	; 18cc <main+0xfe4>
    13a0:	ebfffc16 	bl	400 <ptarmUartOutputStr>
    13a4:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
    13a8:	e1a00003 	mov	r0, r3
    13ac:	ebfffc26 	bl	44c <itoa>
    13b0:	e1a03000 	mov	r3, r0
    13b4:	e1a00003 	mov	r0, r3
    13b8:	ebfffc10 	bl	400 <ptarmUartOutputStr>
    13bc:	e59f04dc 	ldr	r0, [pc, #1244]	; 18a0 <main+0xfb8>
    13c0:	ebfffc0e 	bl	400 <ptarmUartOutputStr>
				PTARM_MUTEX_UNLOCK();
    13c4:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

				// We are now entering the dynamic scheduling phase.
				localScheduler.phase = PTARM_SCHEDULER_DYNAMIC;
    13c8:	e3a03002 	mov	r3, #2, 0
    13cc:	e54b3084 	strb	r3, [fp, #-132]	; 0x84

				// Continue through to the next case statement for the dynamic scheduling phase.
			}
		case (PTARM_SCHEDULER_DYNAMIC):;
			// Dynamic scheduling phase.
			
			// (Re)set the current task in case a timing exception occurs when the scheduler is executing.
			localScheduler.currentTask = NULL;
    13d0:	e3a03000 	mov	r3, #0, 0
    13d4:	e50b308c 	str	r3, [fp, #-140]	; 0x8c

			// Set the dynamic execution deadline to be the end of the base period, minus the expected scheduling overhead.
			PTARM_EOE_ENABLE(localScheduler.basePeriodMinusEndingOverhead, localScheduler.basePeriodStart);
    13d8:	e51b3080 	ldr	r3, [fp, #-128]	; 0x80
    13dc:	e51b207c 	ldr	r2, [fp, #-124]	; 0x7c
    13e0:	e51b105c 	ldr	r1, [fp, #-92]	; 0x5c
    13e4:	e51b0058 	ldr	r0, [fp, #-88]	; 0x58
    13e8:	e1a07003 	mov	r7, r3
    13ec:	e1a08002 	mov	r8, r2
    13f0:	e0988000 	adds	r8, r8, r0
    13f4:	e0a77001 	adc	r7, r7, r1
    13f8:	ee270d08 	cdp	13, 2, cr0, cr7, cr8, {0}

			// Check if there is enough time to execute a task.
			// elapsedTime = currentTime - basePeriodStart.
			PTARM_TIME_GET(localScheduler.currentTime);
    13fc:	ee870d08 	cdp	13, 8, cr0, cr7, cr8, {0}
    1400:	e1a02007 	mov	r2, r7
    1404:	e1a03008 	mov	r3, r8
    1408:	e50b2054 	str	r2, [fp, #-84]	; 0x54
    140c:	e50b3050 	str	r3, [fp, #-80]	; 0x50
			PTARM_MINUS(localScheduler.elapsedTime, localScheduler.currentTime, localScheduler.basePeriodStart);
    1410:	e51b3054 	ldr	r3, [fp, #-84]	; 0x54
    1414:	e51b2050 	ldr	r2, [fp, #-80]	; 0x50
    1418:	e51b1080 	ldr	r1, [fp, #-128]	; 0x80
    141c:	e51b007c 	ldr	r0, [fp, #-124]	; 0x7c
    1420:	e1a07003 	mov	r7, r3
    1424:	e1a08002 	mov	r8, r2
    1428:	e0588000 	subs	r8, r8, r0
    142c:	e0c77001 	sbc	r7, r7, r1
    1430:	e1a02007 	mov	r2, r7
    1434:	e1a03008 	mov	r3, r8
    1438:	e50b204c 	str	r2, [fp, #-76]	; 0x4c
    143c:	e50b3048 	str	r3, [fp, #-72]	; 0x48

			if ((localScheduler.basePeriodMinusEndingOverhead.msb > localScheduler.elapsedTime.msb) ||
    1440:	e51b205c 	ldr	r2, [fp, #-92]	; 0x5c
    1444:	e51b304c 	ldr	r3, [fp, #-76]	; 0x4c
    1448:	e1520003 	cmp	r2, r3
    144c:	ca000007 	bgt	1470 <main+0xb88>
			   ((localScheduler.basePeriodMinusEndingOverhead.msb == localScheduler.elapsedTime.msb) && (localScheduler.basePeriodMinusEndingOverhead.lsb >= localScheduler.elapsedTime.lsb))) {
    1450:	e51b205c 	ldr	r2, [fp, #-92]	; 0x5c
    1454:	e51b304c 	ldr	r3, [fp, #-76]	; 0x4c
    1458:	e1520003 	cmp	r2, r3
    145c:	1affff38 	bne	1144 <main+0x85c>
    1460:	e51b2058 	ldr	r2, [fp, #-88]	; 0x58
    1464:	e51b3048 	ldr	r3, [fp, #-72]	; 0x48
    1468:	e1520003 	cmp	r2, r3
    146c:	3affff34 	bcc	1144 <main+0x85c>
				// Enough time to execute a task. Find a task to execute.

				// Find a task from the dynamic scheduling lists to execute.
				PTARM_MUTEX_LOCK();
    1470:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
				PTARM_SCHEDULER_DYNAMIC_LIST_POP(globalScheduler, localScheduler.currentTask);
    1474:	e59f33dc 	ldr	r3, [pc, #988]	; 1858 <main+0xf70>
    1478:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    147c:	e3530000 	cmp	r3, #0, 0
    1480:	ba00000d 	blt	14bc <main+0xbd4>
    1484:	e59f33cc 	ldr	r3, [pc, #972]	; 1858 <main+0xf70>
    1488:	e5932024 	ldr	r2, [r3, #36]	; 0x24
    148c:	e59f33c4 	ldr	r3, [pc, #964]	; 1858 <main+0xf70>
    1490:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    1494:	e1a03103 	lsl	r3, r3, #2
    1498:	e0823003 	add	r3, r2, r3
    149c:	e5933000 	ldr	r3, [r3]
    14a0:	e50b308c 	str	r3, [fp, #-140]	; 0x8c
    14a4:	e59f33ac 	ldr	r3, [pc, #940]	; 1858 <main+0xf70>
    14a8:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    14ac:	e2433001 	sub	r3, r3, #1, 0
    14b0:	e59f23a0 	ldr	r2, [pc, #928]	; 1858 <main+0xf70>
    14b4:	e5823030 	str	r3, [r2, #48]	; 0x30
    14b8:	ea000025 	b	1554 <main+0xc6c>
    14bc:	e59f3394 	ldr	r3, [pc, #916]	; 1858 <main+0xf70>
    14c0:	e5933034 	ldr	r3, [r3, #52]	; 0x34
    14c4:	e3530000 	cmp	r3, #0, 0
    14c8:	ba00000d 	blt	1504 <main+0xc1c>
    14cc:	e59f3384 	ldr	r3, [pc, #900]	; 1858 <main+0xf70>
    14d0:	e5932028 	ldr	r2, [r3, #40]	; 0x28
    14d4:	e59f337c 	ldr	r3, [pc, #892]	; 1858 <main+0xf70>
    14d8:	e5933034 	ldr	r3, [r3, #52]	; 0x34
    14dc:	e1a03103 	lsl	r3, r3, #2
    14e0:	e0823003 	add	r3, r2, r3
    14e4:	e5933000 	ldr	r3, [r3]
    14e8:	e50b308c 	str	r3, [fp, #-140]	; 0x8c
    14ec:	e59f3364 	ldr	r3, [pc, #868]	; 1858 <main+0xf70>
    14f0:	e5933034 	ldr	r3, [r3, #52]	; 0x34
    14f4:	e2433001 	sub	r3, r3, #1, 0
    14f8:	e59f2358 	ldr	r2, [pc, #856]	; 1858 <main+0xf70>
    14fc:	e5823034 	str	r3, [r2, #52]	; 0x34
    1500:	ea000013 	b	1554 <main+0xc6c>
    1504:	e59f334c 	ldr	r3, [pc, #844]	; 1858 <main+0xf70>
    1508:	e5933038 	ldr	r3, [r3, #56]	; 0x38
    150c:	e3530000 	cmp	r3, #0, 0
    1510:	ba00000d 	blt	154c <main+0xc64>
    1514:	e59f333c 	ldr	r3, [pc, #828]	; 1858 <main+0xf70>
    1518:	e593202c 	ldr	r2, [r3, #44]	; 0x2c
    151c:	e59f3334 	ldr	r3, [pc, #820]	; 1858 <main+0xf70>
    1520:	e5933038 	ldr	r3, [r3, #56]	; 0x38
    1524:	e1a03103 	lsl	r3, r3, #2
    1528:	e0823003 	add	r3, r2, r3
    152c:	e5933000 	ldr	r3, [r3]
    1530:	e50b308c 	str	r3, [fp, #-140]	; 0x8c
    1534:	e59f331c 	ldr	r3, [pc, #796]	; 1858 <main+0xf70>
    1538:	e5933038 	ldr	r3, [r3, #56]	; 0x38
    153c:	e2433001 	sub	r3, r3, #1, 0
    1540:	e59f2310 	ldr	r2, [pc, #784]	; 1858 <main+0xf70>
    1544:	e5823038 	str	r3, [r2, #56]	; 0x38
    1548:	ea000001 	b	1554 <main+0xc6c>
    154c:	e3a03000 	mov	r3, #0, 0
    1550:	e50b308c 	str	r3, [fp, #-140]	; 0x8c
				PTARM_MUTEX_UNLOCK();
    1554:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

				// Check if it is an available task.
				if (localScheduler.currentTask != NULL) {
    1558:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    155c:	e3530000 	cmp	r3, #0, 0
    1560:	0afffef7 	beq	1144 <main+0x85c>

					// "Picking xxx."
					PTARM_MUTEX_LOCK();
    1564:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
					printf(" "); printf(utoa(localScheduler.hwThreadId)); printf(":Picking "); printf(localScheduler.currentTask->name); printf(".\n");
    1568:	e59f035c 	ldr	r0, [pc, #860]	; 18cc <main+0xfe4>
    156c:	ebfffba3 	bl	400 <ptarmUartOutputStr>
    1570:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
    1574:	e1a00003 	mov	r0, r3
    1578:	ebfffbf8 	bl	560 <utoa>
    157c:	e1a03000 	mov	r3, r0
    1580:	e1a00003 	mov	r0, r3
    1584:	ebfffb9d 	bl	400 <ptarmUartOutputStr>
    1588:	e59f0314 	ldr	r0, [pc, #788]	; 18a4 <main+0xfbc>
    158c:	ebfffb9b 	bl	400 <ptarmUartOutputStr>
    1590:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    1594:	e5933000 	ldr	r3, [r3]
    1598:	e1a00003 	mov	r0, r3
    159c:	ebfffb97 	bl	400 <ptarmUartOutputStr>
    15a0:	e59f02e0 	ldr	r0, [pc, #736]	; 1888 <main+0xfa0>
    15a4:	ebfffb95 	bl	400 <ptarmUartOutputStr>
					PTARM_MUTEX_UNLOCK();
    15a8:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

					// Set the task's local scheduler to this dynamic local scheduler.
					PTARM_TASK_SET_SCHEDULER(localScheduler.currentTask, &localScheduler);
    15ac:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    15b0:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
    15b4:	e5832008 	str	r2, [r3, #8]

					// The task is available, so context switch to it.
					PTARM_TASK_RESTORE_CONTEXT(localScheduler.currentTask);
    15b8:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    15bc:	e5933014 	ldr	r3, [r3, #20]
    15c0:	e1a08003 	mov	r8, r3
    15c4:	ee200c08 	cdp	12, 2, cr0, cr0, cr8, {0}
    15c8:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    15cc:	e5933010 	ldr	r3, [r3, #16]
    15d0:	e1a0d003 	mov	sp, r3
    15d4:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
    15d8:	e8bd1fff 	pop	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    15dc:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)
				}
			}

			// Wait for a task to become available, or until the base period ends.
			goto localScheduler;
    15e0:	eafffed7 	b	1144 <main+0x85c>
			break;

		default:;
			// Undefined scheduling phase.
			PTARM_MUTEX_LOCK();
    15e4:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
			printf("!!"); printf(utoa(localScheduler.hwThreadId)); printf(" Scheduling error. Phase = "); printf(utoa(localScheduler.phase)); printf(".\n");
    15e8:	e59f02b8 	ldr	r0, [pc, #696]	; 18a8 <main+0xfc0>
    15ec:	ebfffb83 	bl	400 <ptarmUartOutputStr>
    15f0:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
    15f4:	e1a00003 	mov	r0, r3
    15f8:	ebfffbd8 	bl	560 <utoa>
    15fc:	e1a03000 	mov	r3, r0
    1600:	e1a00003 	mov	r0, r3
    1604:	ebfffb7d 	bl	400 <ptarmUartOutputStr>
    1608:	e59f029c 	ldr	r0, [pc, #668]	; 18ac <main+0xfc4>
    160c:	ebfffb7b 	bl	400 <ptarmUartOutputStr>
    1610:	e55b3084 	ldrb	r3, [fp, #-132]	; 0x84
    1614:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1618:	e1a00003 	mov	r0, r3
    161c:	ebfffbcf 	bl	560 <utoa>
    1620:	e1a03000 	mov	r3, r0
    1624:	e1a00003 	mov	r0, r3
    1628:	ebfffb74 	bl	400 <ptarmUartOutputStr>
    162c:	e59f0254 	ldr	r0, [pc, #596]	; 1888 <main+0xfa0>
    1630:	ebfffb72 	bl	400 <ptarmUartOutputStr>
			PTARM_MUTEX_UNLOCK();
    1634:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

			while (halt);
    1638:	e1a00000 	nop			; (mov r0, r0)
    163c:	e59f323c 	ldr	r3, [pc, #572]	; 1880 <main+0xf98>
    1640:	e5d33000 	ldrb	r3, [r3]
    1644:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1648:	e3530000 	cmp	r3, #0, 0
    164c:	1afffffa 	bne	163c <main+0xd54>
			break;
    1650:	e1a00000 	nop			; (mov r0, r0)
	}
}

// The tasks. Note that they are defined within the main function.

one: {
	while (loopForever) {
    1654:	ea000034 	b	172c <main+0xe44>
		int i;
		for (i = 0; i < 2000000u; i++);
    1658:	e3a03000 	mov	r3, #0, 0
    165c:	e50b3010 	str	r3, [fp, #-16]
    1660:	ea000002 	b	1670 <main+0xd88>
    1664:	e51b3010 	ldr	r3, [fp, #-16]
    1668:	e2833001 	add	r3, r3, #1, 0
    166c:	e50b3010 	str	r3, [fp, #-16]
    1670:	e51b2010 	ldr	r2, [fp, #-16]
    1674:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    1678:	e2833e47 	add	r3, r3, #1136	; 0x470
    167c:	e283300f 	add	r3, r3, #15, 0
    1680:	e1520003 	cmp	r2, r3
    1684:	9afffff6 	bls	1664 <main+0xd7c>

		PTARM_MUTEX_LOCK();
    1688:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(one.localScheduler->hwThreadId)); printf(":one pausing.\n");
    168c:	e59f0238 	ldr	r0, [pc, #568]	; 18cc <main+0xfe4>
    1690:	ebfffb5a 	bl	400 <ptarmUartOutputStr>
    1694:	e59f31b0 	ldr	r3, [pc, #432]	; 184c <main+0xf64>
    1698:	e5933008 	ldr	r3, [r3, #8]
    169c:	e5933004 	ldr	r3, [r3, #4]
    16a0:	e1a00003 	mov	r0, r3
    16a4:	ebfffb68 	bl	44c <itoa>
    16a8:	e1a03000 	mov	r3, r0
    16ac:	e1a00003 	mov	r0, r3
    16b0:	ebfffb52 	bl	400 <ptarmUartOutputStr>
    16b4:	e59f01f4 	ldr	r0, [pc, #500]	; 18b0 <main+0xfc8>
    16b8:	ebfffb50 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    16bc:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(one, 1);
    16c0:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    16c4:	e59f3180 	ldr	r3, [pc, #384]	; 184c <main+0xf64>
    16c8:	e3a02000 	mov	r2, #0, 0
    16cc:	e5c3200c 	strb	r2, [r3, #12]
    16d0:	e1a00000 	nop			; (mov r0, r0)
    16d4:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    16d8:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    16dc:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    16e0:	e59f31cc 	ldr	r3, [pc, #460]	; 18b4 <main+0xfcc>
    16e4:	e1a07003 	mov	r7, r3
    16e8:	e58d7038 	str	r7, [sp, #56]	; 0x38
    16ec:	e1a0300d 	mov	r3, sp
    16f0:	e59f2154 	ldr	r2, [pc, #340]	; 184c <main+0xf64>
    16f4:	e5823010 	str	r3, [r2, #16]
    16f8:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    16fc:	e1a03007 	mov	r3, r7
    1700:	e59f2144 	ldr	r2, [pc, #324]	; 184c <main+0xf64>
    1704:	e5823014 	str	r3, [r2, #20]
    1708:	e59f313c 	ldr	r3, [pc, #316]	; 184c <main+0xf64>
    170c:	e5933008 	ldr	r3, [r3, #8]
    1710:	e593300c 	ldr	r3, [r3, #12]
    1714:	e59f2130 	ldr	r2, [pc, #304]	; 184c <main+0xf64>
    1718:	e5922008 	ldr	r2, [r2, #8]
    171c:	e5922008 	ldr	r2, [r2, #8]
    1720:	e1a0d003 	mov	sp, r3
    1724:	e1a0b002 	mov	fp, r2
    1728:	eafffe85 	b	1144 <main+0x85c>
    172c:	e59f31a8 	ldr	r3, [pc, #424]	; 18dc <main+0xff4>
    1730:	e5d33000 	ldrb	r3, [r3]
    1734:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1738:	e3530000 	cmp	r3, #0, 0
    173c:	1affffc5 	bne	1658 <main+0xd70>
	}
}

two: {
	while (loopForever) {
    1740:	ea000034 	b	1818 <main+0xf30>
		int i;
		for (i = 0; i < 2000000u; i++);
    1744:	e3a03000 	mov	r3, #0, 0
    1748:	e50b3014 	str	r3, [fp, #-20]
    174c:	ea000002 	b	175c <main+0xe74>
    1750:	e51b3014 	ldr	r3, [fp, #-20]
    1754:	e2833001 	add	r3, r3, #1, 0
    1758:	e50b3014 	str	r3, [fp, #-20]
    175c:	e51b2014 	ldr	r2, [fp, #-20]
    1760:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    1764:	e2833e47 	add	r3, r3, #1136	; 0x470
    1768:	e283300f 	add	r3, r3, #15, 0
    176c:	e1520003 	cmp	r2, r3
    1770:	9afffff6 	bls	1750 <main+0xe68>

		PTARM_MUTEX_LOCK();
    1774:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(two.localScheduler->hwThreadId)); printf(":two pausing.\n");
    1778:	e59f014c 	ldr	r0, [pc, #332]	; 18cc <main+0xfe4>
    177c:	ebfffb1f 	bl	400 <ptarmUartOutputStr>
    1780:	e59f30cc 	ldr	r3, [pc, #204]	; 1854 <main+0xf6c>
    1784:	e5933008 	ldr	r3, [r3, #8]
    1788:	e5933004 	ldr	r3, [r3, #4]
    178c:	e1a00003 	mov	r0, r3
    1790:	ebfffb2d 	bl	44c <itoa>
    1794:	e1a03000 	mov	r3, r0
    1798:	e1a00003 	mov	r0, r3
    179c:	ebfffb17 	bl	400 <ptarmUartOutputStr>
    17a0:	e59f0110 	ldr	r0, [pc, #272]	; 18b8 <main+0xfd0>
    17a4:	ebfffb15 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    17a8:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(two, 1);
    17ac:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    17b0:	e59f309c 	ldr	r3, [pc, #156]	; 1854 <main+0xf6c>
    17b4:	e3a02000 	mov	r2, #0, 0
    17b8:	e5c3200c 	strb	r2, [r3, #12]
    17bc:	e1a00000 	nop			; (mov r0, r0)
    17c0:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    17c4:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    17c8:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    17cc:	e59f30e8 	ldr	r3, [pc, #232]	; 18bc <main+0xfd4>
    17d0:	e1a07003 	mov	r7, r3
    17d4:	e58d7038 	str	r7, [sp, #56]	; 0x38
    17d8:	e1a0300d 	mov	r3, sp
    17dc:	e59f2070 	ldr	r2, [pc, #112]	; 1854 <main+0xf6c>
    17e0:	e5823010 	str	r3, [r2, #16]
    17e4:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    17e8:	e1a03007 	mov	r3, r7
    17ec:	e59f2060 	ldr	r2, [pc, #96]	; 1854 <main+0xf6c>
    17f0:	e5823014 	str	r3, [r2, #20]
    17f4:	e59f3058 	ldr	r3, [pc, #88]	; 1854 <main+0xf6c>
    17f8:	e5933008 	ldr	r3, [r3, #8]
    17fc:	e593300c 	ldr	r3, [r3, #12]
    1800:	e59f204c 	ldr	r2, [pc, #76]	; 1854 <main+0xf6c>
    1804:	e5922008 	ldr	r2, [r2, #8]
    1808:	e5922008 	ldr	r2, [r2, #8]
    180c:	e1a0d003 	mov	sp, r3
    1810:	e1a0b002 	mov	fp, r2
    1814:	eafffe4a 	b	1144 <main+0x85c>
    1818:	e59f30bc 	ldr	r3, [pc, #188]	; 18dc <main+0xff4>
    181c:	e5d33000 	ldrb	r3, [r3]
    1820:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1824:	e3530000 	cmp	r3, #0, 0
    1828:	1affffc5 	bne	1744 <main+0xe5c>
	}
}

three: {
	while (loopForever) {
    182c:	ea00005d 	b	19a8 <main+0x10c0>
		int i;
		for (i = 0; i < 2000000u; i++);
    1830:	e3a03000 	mov	r3, #0, 0
    1834:	e50b3018 	str	r3, [fp, #-24]
    1838:	ea00002b 	b	18ec <main+0x1004>
    183c:	00001c74 	.word	0x00001c74
    1840:	00001144 	.word	0x00001144
    1844:	00001b48 	.word	0x00001b48
    1848:	00001654 	.word	0x00001654
    184c:	00001d7c 	.word	0x00001d7c
    1850:	00001740 	.word	0x00001740
    1854:	00001da8 	.word	0x00001da8
    1858:	00001e2c 	.word	0x00001e2c
    185c:	0000ffe0 	.word	0x0000ffe0
    1860:	00000d40 	.word	0x00000d40
    1864:	0000182c 	.word	0x0000182c
    1868:	000019bc 	.word	0x000019bc
    186c:	00000da4 	.word	0x00000da4
    1870:	00000e08 	.word	0x00000e08
    1874:	00000e6c 	.word	0x00000e6c
    1878:	00001b68 	.word	0x00001b68
    187c:	00001b98 	.word	0x00001b98
    1880:	00001d78 	.word	0x00001d78
    1884:	00001ba0 	.word	0x00001ba0
    1888:	00001bac 	.word	0x00001bac
    188c:	00001bb0 	.word	0x00001bb0
    1890:	00001bc0 	.word	0x00001bc0
    1894:	00001bcc 	.word	0x00001bcc
    1898:	00001bd8 	.word	0x00001bd8
    189c:	00001be4 	.word	0x00001be4
    18a0:	00001bf0 	.word	0x00001bf0
    18a4:	00001c04 	.word	0x00001c04
    18a8:	00001c10 	.word	0x00001c10
    18ac:	00001c14 	.word	0x00001c14
    18b0:	00001c30 	.word	0x00001c30
    18b4:	0000172c 	.word	0x0000172c
    18b8:	00001c40 	.word	0x00001c40
    18bc:	00001818 	.word	0x00001818
    18c0:	00001c50 	.word	0x00001c50
    18c4:	000019a8 	.word	0x000019a8
    18c8:	00001dd4 	.word	0x00001dd4
    18cc:	00001b9c 	.word	0x00001b9c
    18d0:	00001c64 	.word	0x00001c64
    18d4:	00001a94 	.word	0x00001a94
    18d8:	00001e00 	.word	0x00001e00
    18dc:	00001d79 	.word	0x00001d79
    18e0:	e51b3018 	ldr	r3, [fp, #-24]
    18e4:	e2833001 	add	r3, r3, #1, 0
    18e8:	e50b3018 	str	r3, [fp, #-24]
    18ec:	e51b2018 	ldr	r2, [fp, #-24]
    18f0:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    18f4:	e2833e47 	add	r3, r3, #1136	; 0x470
    18f8:	e283300f 	add	r3, r3, #15, 0
    18fc:	e1520003 	cmp	r2, r3
    1900:	9afffff6 	bls	18e0 <main+0xff8>

		PTARM_MUTEX_LOCK();
    1904:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(three.localScheduler->hwThreadId)); printf(":three pausing.\n");
    1908:	e51f0044 	ldr	r0, [pc, #-68]	; 18cc <main+0xfe4>
    190c:	ebfffabb 	bl	400 <ptarmUartOutputStr>
    1910:	e51f3050 	ldr	r3, [pc, #-80]	; 18c8 <main+0xfe0>
    1914:	e5933008 	ldr	r3, [r3, #8]
    1918:	e5933004 	ldr	r3, [r3, #4]
    191c:	e1a00003 	mov	r0, r3
    1920:	ebfffac9 	bl	44c <itoa>
    1924:	e1a03000 	mov	r3, r0
    1928:	e1a00003 	mov	r0, r3
    192c:	ebfffab3 	bl	400 <ptarmUartOutputStr>
    1930:	e51f0078 	ldr	r0, [pc, #-120]	; 18c0 <main+0xfd8>
    1934:	ebfffab1 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    1938:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(three, 1);
    193c:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    1940:	e51f3080 	ldr	r3, [pc, #-128]	; 18c8 <main+0xfe0>
    1944:	e3a02000 	mov	r2, #0, 0
    1948:	e5c3200c 	strb	r2, [r3, #12]
    194c:	e1a00000 	nop			; (mov r0, r0)
    1950:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    1954:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    1958:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    195c:	e51f30a0 	ldr	r3, [pc, #-160]	; 18c4 <main+0xfdc>
    1960:	e1a07003 	mov	r7, r3
    1964:	e58d7038 	str	r7, [sp, #56]	; 0x38
    1968:	e1a0300d 	mov	r3, sp
    196c:	e51f20ac 	ldr	r2, [pc, #-172]	; 18c8 <main+0xfe0>
    1970:	e5823010 	str	r3, [r2, #16]
    1974:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    1978:	e1a03007 	mov	r3, r7
    197c:	e51f20bc 	ldr	r2, [pc, #-188]	; 18c8 <main+0xfe0>
    1980:	e5823014 	str	r3, [r2, #20]
    1984:	e51f30c4 	ldr	r3, [pc, #-196]	; 18c8 <main+0xfe0>
    1988:	e5933008 	ldr	r3, [r3, #8]
    198c:	e593300c 	ldr	r3, [r3, #12]
    1990:	e51f20d0 	ldr	r2, [pc, #-208]	; 18c8 <main+0xfe0>
    1994:	e5922008 	ldr	r2, [r2, #8]
    1998:	e5922008 	ldr	r2, [r2, #8]
    199c:	e1a0d003 	mov	sp, r3
    19a0:	e1a0b002 	mov	fp, r2
    19a4:	eafffde6 	b	1144 <main+0x85c>
    19a8:	e51f30d4 	ldr	r3, [pc, #-212]	; 18dc <main+0xff4>
    19ac:	e5d33000 	ldrb	r3, [r3]
    19b0:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    19b4:	e3530000 	cmp	r3, #0, 0
    19b8:	1affff9c 	bne	1830 <main+0xf48>
	}
}

four: {
	while (loopForever) {
    19bc:	ea000034 	b	1a94 <main+0x11ac>
		int i;
		for (i = 0; i < 2000000u; i++);
    19c0:	e3a03000 	mov	r3, #0, 0
    19c4:	e50b301c 	str	r3, [fp, #-28]
    19c8:	ea000002 	b	19d8 <main+0x10f0>
    19cc:	e51b301c 	ldr	r3, [fp, #-28]
    19d0:	e2833001 	add	r3, r3, #1, 0
    19d4:	e50b301c 	str	r3, [fp, #-28]
    19d8:	e51b201c 	ldr	r2, [fp, #-28]
    19dc:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    19e0:	e2833e47 	add	r3, r3, #1136	; 0x470
    19e4:	e283300f 	add	r3, r3, #15, 0
    19e8:	e1520003 	cmp	r2, r3
    19ec:	9afffff6 	bls	19cc <main+0x10e4>

		PTARM_MUTEX_LOCK();
    19f0:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(four.localScheduler->hwThreadId)); printf(":four pausing.\n");
    19f4:	e51f0130 	ldr	r0, [pc, #-304]	; 18cc <main+0xfe4>
    19f8:	ebfffa80 	bl	400 <ptarmUartOutputStr>
    19fc:	e51f312c 	ldr	r3, [pc, #-300]	; 18d8 <main+0xff0>
    1a00:	e5933008 	ldr	r3, [r3, #8]
    1a04:	e5933004 	ldr	r3, [r3, #4]
    1a08:	e1a00003 	mov	r0, r3
    1a0c:	ebfffa8e 	bl	44c <itoa>
    1a10:	e1a03000 	mov	r3, r0
    1a14:	e1a00003 	mov	r0, r3
    1a18:	ebfffa78 	bl	400 <ptarmUartOutputStr>
    1a1c:	e51f0154 	ldr	r0, [pc, #-340]	; 18d0 <main+0xfe8>
    1a20:	ebfffa76 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    1a24:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(four, 1);
    1a28:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    1a2c:	e51f315c 	ldr	r3, [pc, #-348]	; 18d8 <main+0xff0>
    1a30:	e3a02000 	mov	r2, #0, 0
    1a34:	e5c3200c 	strb	r2, [r3, #12]
    1a38:	e1a00000 	nop			; (mov r0, r0)
    1a3c:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    1a40:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    1a44:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    1a48:	e51f317c 	ldr	r3, [pc, #-380]	; 18d4 <main+0xfec>
    1a4c:	e1a07003 	mov	r7, r3
    1a50:	e58d7038 	str	r7, [sp, #56]	; 0x38
    1a54:	e1a0300d 	mov	r3, sp
    1a58:	e51f2188 	ldr	r2, [pc, #-392]	; 18d8 <main+0xff0>
    1a5c:	e5823010 	str	r3, [r2, #16]
    1a60:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    1a64:	e1a03007 	mov	r3, r7
    1a68:	e51f2198 	ldr	r2, [pc, #-408]	; 18d8 <main+0xff0>
    1a6c:	e5823014 	str	r3, [r2, #20]
    1a70:	e51f31a0 	ldr	r3, [pc, #-416]	; 18d8 <main+0xff0>
    1a74:	e5933008 	ldr	r3, [r3, #8]
    1a78:	e593300c 	ldr	r3, [r3, #12]
    1a7c:	e51f21ac 	ldr	r2, [pc, #-428]	; 18d8 <main+0xff0>
    1a80:	e5922008 	ldr	r2, [r2, #8]
    1a84:	e5922008 	ldr	r2, [r2, #8]
    1a88:	e1a0d003 	mov	sp, r3
    1a8c:	e1a0b002 	mov	fp, r2
    1a90:	eafffdab 	b	1144 <main+0x85c>
    1a94:	e51f31c0 	ldr	r3, [pc, #-448]	; 18dc <main+0xff4>
    1a98:	e5d33000 	ldrb	r3, [r3]
    1a9c:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1aa0:	e3530000 	cmp	r3, #0, 0
    1aa4:	1affffc5 	bne	19c0 <main+0x10d8>
	}
}

	return 0;
    1aa8:	e3a03000 	mov	r3, #0, 0
}
    1aac:	e1a00003 	mov	r0, r3
    1ab0:	e24bd00c 	sub	sp, fp, #12, 0
    1ab4:	e8bd8980 	pop	{r7, r8, fp, pc}

Disassembly of section .text.memset:

00001c80 <memset>:
    1c80:	e3100003 	tst	r0, #3, 0
    1c84:	e92d4010 	push	{r4, lr}
    1c88:	0a000037 	beq	1d6c <memset+0xec>
    1c8c:	e3520000 	cmp	r2, #0, 0
    1c90:	e2422001 	sub	r2, r2, #1, 0
    1c94:	0a000032 	beq	1d64 <memset+0xe4>
    1c98:	e201c0ff 	and	ip, r1, #255, 0	; 0xff
    1c9c:	e1a03000 	mov	r3, r0
    1ca0:	ea000002 	b	1cb0 <memset+0x30>
    1ca4:	e3520000 	cmp	r2, #0, 0
    1ca8:	e2422001 	sub	r2, r2, #1, 0
    1cac:	0a00002c 	beq	1d64 <memset+0xe4>
    1cb0:	e4c3c001 	strb	ip, [r3], #1
    1cb4:	e3130003 	tst	r3, #3, 0
    1cb8:	1afffff9 	bne	1ca4 <memset+0x24>
    1cbc:	e3520003 	cmp	r2, #3, 0
    1cc0:	9a000020 	bls	1d48 <memset+0xc8>
    1cc4:	e201e0ff 	and	lr, r1, #255, 0	; 0xff
    1cc8:	e18ee40e 	orr	lr, lr, lr, lsl #8
    1ccc:	e352000f 	cmp	r2, #15, 0
    1cd0:	e18ee80e 	orr	lr, lr, lr, lsl #16
    1cd4:	9a000010 	bls	1d1c <memset+0x9c>
    1cd8:	e1a04002 	mov	r4, r2
    1cdc:	e283c010 	add	ip, r3, #16, 0
    1ce0:	e2444010 	sub	r4, r4, #16, 0
    1ce4:	e354000f 	cmp	r4, #15, 0
    1ce8:	e50ce010 	str	lr, [ip, #-16]
    1cec:	e50ce00c 	str	lr, [ip, #-12]
    1cf0:	e50ce008 	str	lr, [ip, #-8]
    1cf4:	e50ce004 	str	lr, [ip, #-4]
    1cf8:	e28cc010 	add	ip, ip, #16, 0
    1cfc:	8afffff7 	bhi	1ce0 <memset+0x60>
    1d00:	e242c010 	sub	ip, r2, #16, 0
    1d04:	e3ccc00f 	bic	ip, ip, #15, 0
    1d08:	e202200f 	and	r2, r2, #15, 0
    1d0c:	e28cc010 	add	ip, ip, #16, 0
    1d10:	e3520003 	cmp	r2, #3, 0
    1d14:	e083300c 	add	r3, r3, ip
    1d18:	9a00000a 	bls	1d48 <memset+0xc8>
    1d1c:	e1a04003 	mov	r4, r3
    1d20:	e1a0c002 	mov	ip, r2
    1d24:	e24cc004 	sub	ip, ip, #4, 0
    1d28:	e35c0003 	cmp	ip, #3, 0
    1d2c:	e484e004 	str	lr, [r4], #4
    1d30:	8afffffb 	bhi	1d24 <memset+0xa4>
    1d34:	e242c004 	sub	ip, r2, #4, 0
    1d38:	e3ccc003 	bic	ip, ip, #3, 0
    1d3c:	e28cc004 	add	ip, ip, #4, 0
    1d40:	e083300c 	add	r3, r3, ip
    1d44:	e2022003 	and	r2, r2, #3, 0
    1d48:	e3520000 	cmp	r2, #0, 0
    1d4c:	120110ff 	andne	r1, r1, #255, 0	; 0xff
    1d50:	10832002 	addne	r2, r3, r2
    1d54:	0a000002 	beq	1d64 <memset+0xe4>
    1d58:	e4c31001 	strb	r1, [r3], #1
    1d5c:	e1530002 	cmp	r3, r2
    1d60:	1afffffc 	bne	1d58 <memset+0xd8>
    1d64:	e8bd4010 	pop	{r4, lr}
    1d68:	e1a0f00e 	mov	pc, lr
    1d6c:	e1a03000 	mov	r3, r0
    1d70:	eaffffd1 	b	1cbc <memset+0x3c>
