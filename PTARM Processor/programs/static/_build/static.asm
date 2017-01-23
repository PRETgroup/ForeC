
_build/static.elf:     file format elf32-littlearm

SYMBOL TABLE:
00000000 l    d  .text	00000000 .text
000015c4 l    d  .rodata	00000000 .rodata
00001758 l    d  .text.memset	00000000 .text.memset
0000184c l    d  .data	00000000 .data
000019e0 l    d  .bss	00000000 .bss
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
00000000 l    df *ABS*	00000000 static.c
00000000 l    df *ABS*	00000000 memset.c
00000740 g     F .text	000001a8 ptarmCreateTask
000019e0 g     O .bss	00000002 ptarmLcdCharCount
000006ec g     F .text	00000054 foreMcGetIndex
00000278 g     F .text	0000013c ptarmLcdOutputStr
000018a8 g     O .data	00000054 two
00001a0c g     O .bss	00000014 priorityQueueLife
00001851 g     O .data	00000001 foreverTrue
000003b4 g     F .text	0000004c ptarmUartOutputChar
00001a2c g       .bss	00000000 addr_stack_limit
000019f8 g     O .bss	00000014 priorityQueueMission
000019a4 g     O .data	0000003c globalScheduler
00000400 g     F .text	0000004c ptarmUartOutputStr
000019e4 g     O .bss	00000014 priorityQueueNonCritical
0000184c g     O .data	00000004 ptarmPreviousTaskStackEnd
0000044c g     F .text	00000114 itoa
0000008c g     F .text	0000003c ptarmLedOutput
00000560 g     F .text	000000e4 utoa
00001a2c g       .bss	00000000 bss_end
0000004c g       *ABS*	00000000 bss_size
000019e0 g       .data	00000000 bss_start
000000c8 g     F .text	0000004c ptarmSevenSegOutput
00001758 g     F .text.memset	000000f4 memset
000008e8 g     F .text	00000cdc main
00001a20 g     O .bss	0000000c ptarmStringBuffer
000001a8 g     F .text	00000084 ptarmLcdOutput
0001efdc g       *ABS*	00000000 addr_stack_end
000015c4 g     O .rodata	00000010 hexMap
00001854 g     O .data	00000054 one
0001ffe0 g       *ABS*	00000000 eoe_table
00001850 g     O .data	00000001 halt
00000644 g     F .text	000000a8 hex
0000022c g     F .text	0000004c ptarmLcdInit
000018fc g     O .data	00000054 three
00000114 g     F .text	00000094 ptarmSevenSegChar
00001950 g     O .data	00000054 four
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
      7c:	000019e0 	.word	0x000019e0
      80:	00001a2c 	.word	0x00001a2c
      84:	0000004c 	.word	0x0000004c
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
     1a4:	000015c4 	.word	0x000015c4

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
     274:	000019e0 	.word	0x000019e0

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
     3b0:	000019e0 	.word	0x000019e0

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
     55c:	00001a20 	.word	0x00001a20

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
     640:	00001a20 	.word	0x00001a20

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
     6e8:	00001a20 	.word	0x00001a20

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
     8d0:	0000184c 	.word	0x0000184c
     8d4:	00001a2c 	.word	0x00001a2c
     8d8:	000015d4 	.word	0x000015d4
     8dc:	00001600 	.word	0x00001600
     8e0:	00001618 	.word	0x00001618
     8e4:	00001624 	.word	0x00001624

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
     91c:	e59f2c14 	ldr	r2, [pc, #3092]	; 1538 <main+0xc50>
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
     968:	eb00037a 	bl	1758 <memset>
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
     9a4:	e59f3b90 	ldr	r3, [pc, #2960]	; 153c <main+0xc54>
     9a8:	e50b309c 	str	r3, [fp, #-156]	; 0x9c

	// Each hardware thread performs some type of start up work.
	switch (localScheduler.hwThreadId) {
     9ac:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     9b0:	e3530003 	cmp	r3, #3, 0
     9b4:	979ff103 	ldrls	pc, [pc, r3, lsl #2]
     9b8:	ea0000bd 	b	cb4 <main+0x3cc>
     9bc:	000009cc 	.word	0x000009cc
     9c0:	00000ab0 	.word	0x00000ab0
     9c4:	00000b5c 	.word	0x00000b5c
     9c8:	00000c08 	.word	0x00000c08
		case (0):	// Hardware thread 0.

					safe_printf("Static scheduling example.\n\n");
     9cc:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
     9d0:	e59f0b68 	ldr	r0, [pc, #2920]	; 1540 <main+0xc58>
     9d4:	ebfffe89 	bl	400 <ptarmUartOutputStr>
     9d8:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

					// Create a static schedule for hardware thread 0.
					// [one]
					ptarmCreateTask(&one, &&one, &localScheduler);
     9dc:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
     9e0:	e59f3b5c 	ldr	r3, [pc, #2908]	; 1544 <main+0xc5c>
     9e4:	e1a01003 	mov	r1, r3
     9e8:	e59f0b58 	ldr	r0, [pc, #2904]	; 1548 <main+0xc60>
     9ec:	ebffff53 	bl	740 <ptarmCreateTask>
					staticSchedule[0] = &one;
     9f0:	e59f3b50 	ldr	r3, [pc, #2896]	; 1548 <main+0xc60>
     9f4:	e50b3038 	str	r3, [fp, #-56]	; 0x38

					// Calculate the duration of the base period that can be used to execute tasks.
					localScheduler.basePeriodStartOverhead.msb = 0;
     9f8:	e3a03000 	mov	r3, #0, 0
     9fc:	e50b3074 	str	r3, [fp, #-116]	; 0x74
					localScheduler.basePeriodStartOverhead.lsb = 10000000;	// 0.1s
     a00:	e3a03726 	mov	r3, #9961472	; 0x980000
     a04:	e2833c96 	add	r3, r3, #38400	; 0x9600
     a08:	e2833080 	add	r3, r3, #128, 0	; 0x80
     a0c:	e50b3070 	str	r3, [fp, #-112]	; 0x70
					localScheduler.basePeriodEndOverhead.msb = 0;
     a10:	e3a03000 	mov	r3, #0, 0
     a14:	e50b306c 	str	r3, [fp, #-108]	; 0x6c
					localScheduler.basePeriodEndOverhead.lsb = 10000000;	// 0.1s
     a18:	e3a03726 	mov	r3, #9961472	; 0x980000
     a1c:	e2833c96 	add	r3, r3, #38400	; 0x9600
     a20:	e2833080 	add	r3, r3, #128, 0	; 0x80
     a24:	e50b3068 	str	r3, [fp, #-104]	; 0x68
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);
     a28:	e59f3b1c 	ldr	r3, [pc, #2844]	; 154c <main+0xc64>
     a2c:	e5933004 	ldr	r3, [r3, #4]
     a30:	e59f2b14 	ldr	r2, [pc, #2836]	; 154c <main+0xc64>
     a34:	e5922008 	ldr	r2, [r2, #8]
     a38:	e51b106c 	ldr	r1, [fp, #-108]	; 0x6c
     a3c:	e51b0068 	ldr	r0, [fp, #-104]	; 0x68
     a40:	e1a07003 	mov	r7, r3
     a44:	e1a08002 	mov	r8, r2
     a48:	e0588000 	subs	r8, r8, r0
     a4c:	e0c77001 	sbc	r7, r7, r1
     a50:	e1a02007 	mov	r2, r7
     a54:	e1a03008 	mov	r3, r8
     a58:	e50b205c 	str	r2, [fp, #-92]	; 0x5c
     a5c:	e50b3058 	str	r3, [fp, #-88]	; 0x58

					globalScheduler.localScheduler0 = &localScheduler;					// Set the global reference to the local scheduler.
     a60:	e59f2ae4 	ldr	r2, [pc, #2788]	; 154c <main+0xc64>
     a64:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     a68:	e5823014 	str	r3, [r2, #20]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler0);	// Register the EOE handler.
     a6c:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     a70:	e1a03103 	lsl	r3, r3, #2
     a74:	e59f2ad4 	ldr	r2, [pc, #2772]	; 1550 <main+0xc68>
     a78:	e0833002 	add	r3, r3, r2
     a7c:	e59f2ad0 	ldr	r2, [pc, #2768]	; 1554 <main+0xc6c>
     a80:	e5832000 	str	r2, [r3]

					PTARM_TIME_GET(globalScheduler.basePeriodFirstStart);				// Save the time stamp of the first base period.
     a84:	ee870d08 	cdp	13, 8, cr0, cr7, cr8, {0}
     a88:	e1a02007 	mov	r2, r7
     a8c:	e1a03008 	mov	r3, r8
     a90:	e59f1ab4 	ldr	r1, [pc, #2740]	; 154c <main+0xc64>
     a94:	e581200c 	str	r2, [r1, #12]
     a98:	e59f2aac 	ldr	r2, [pc, #2732]	; 154c <main+0xc64>
     a9c:	e5823010 	str	r3, [r2, #16]
					globalScheduler.isInitialised = true;								// Initialisation complete.
     aa0:	e59f3aa4 	ldr	r3, [pc, #2724]	; 154c <main+0xc64>
     aa4:	e3a02001 	mov	r2, #1, 0
     aa8:	e5c32000 	strb	r2, [r3]
					break;
     aac:	ea000093 	b	d00 <main+0x418>

		case (1):	// Hardware thread 1.

					// Create a static schedule for hardware thread 1.
					// [two]
					ptarmCreateTask(&two, &&two, &localScheduler);
     ab0:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
     ab4:	e59f3a9c 	ldr	r3, [pc, #2716]	; 1558 <main+0xc70>
     ab8:	e1a01003 	mov	r1, r3
     abc:	e59f0a98 	ldr	r0, [pc, #2712]	; 155c <main+0xc74>
     ac0:	ebffff1e 	bl	740 <ptarmCreateTask>
					staticSchedule[0] = &two;
     ac4:	e59f3a90 	ldr	r3, [pc, #2704]	; 155c <main+0xc74>
     ac8:	e50b3038 	str	r3, [fp, #-56]	; 0x38

					// Calculate the duration of the base period that can be used to execute tasks.
					localScheduler.basePeriodStartOverhead.msb = 0;
     acc:	e3a03000 	mov	r3, #0, 0
     ad0:	e50b3074 	str	r3, [fp, #-116]	; 0x74
					localScheduler.basePeriodStartOverhead.lsb = 10000000;	// 0.1s
     ad4:	e3a03726 	mov	r3, #9961472	; 0x980000
     ad8:	e2833c96 	add	r3, r3, #38400	; 0x9600
     adc:	e2833080 	add	r3, r3, #128, 0	; 0x80
     ae0:	e50b3070 	str	r3, [fp, #-112]	; 0x70
					localScheduler.basePeriodEndOverhead.msb = 0;
     ae4:	e3a03000 	mov	r3, #0, 0
     ae8:	e50b306c 	str	r3, [fp, #-108]	; 0x6c
					localScheduler.basePeriodEndOverhead.lsb = 10000000;	// 0.1s
     aec:	e3a03726 	mov	r3, #9961472	; 0x980000
     af0:	e2833c96 	add	r3, r3, #38400	; 0x9600
     af4:	e2833080 	add	r3, r3, #128, 0	; 0x80
     af8:	e50b3068 	str	r3, [fp, #-104]	; 0x68
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);
     afc:	e59f3a48 	ldr	r3, [pc, #2632]	; 154c <main+0xc64>
     b00:	e5933004 	ldr	r3, [r3, #4]
     b04:	e59f2a40 	ldr	r2, [pc, #2624]	; 154c <main+0xc64>
     b08:	e5922008 	ldr	r2, [r2, #8]
     b0c:	e51b106c 	ldr	r1, [fp, #-108]	; 0x6c
     b10:	e51b0068 	ldr	r0, [fp, #-104]	; 0x68
     b14:	e1a07003 	mov	r7, r3
     b18:	e1a08002 	mov	r8, r2
     b1c:	e0588000 	subs	r8, r8, r0
     b20:	e0c77001 	sbc	r7, r7, r1
     b24:	e1a02007 	mov	r2, r7
     b28:	e1a03008 	mov	r3, r8
     b2c:	e50b205c 	str	r2, [fp, #-92]	; 0x5c
     b30:	e50b3058 	str	r3, [fp, #-88]	; 0x58

					globalScheduler.localScheduler1 = &localScheduler;					// Set the global reference to the local scheduler.
     b34:	e59f2a10 	ldr	r2, [pc, #2576]	; 154c <main+0xc64>
     b38:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     b3c:	e5823018 	str	r3, [r2, #24]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler1);	// Register the EOE handler.
     b40:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     b44:	e1a03103 	lsl	r3, r3, #2
     b48:	e59f2a00 	ldr	r2, [pc, #2560]	; 1550 <main+0xc68>
     b4c:	e0833002 	add	r3, r3, r2
     b50:	e59f2a08 	ldr	r2, [pc, #2568]	; 1560 <main+0xc78>
     b54:	e5832000 	str	r2, [r3]
					break;
     b58:	ea000068 	b	d00 <main+0x418>

		case (2):	// Hardware thread 2.

					// Create a static schedule for hardware thread 2.
					// [three]
					ptarmCreateTask(&three, &&three, &localScheduler);
     b5c:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
     b60:	e59f39fc 	ldr	r3, [pc, #2556]	; 1564 <main+0xc7c>
     b64:	e1a01003 	mov	r1, r3
     b68:	e59f09f8 	ldr	r0, [pc, #2552]	; 1568 <main+0xc80>
     b6c:	ebfffef3 	bl	740 <ptarmCreateTask>
					staticSchedule[0] = &three;
     b70:	e59f39f0 	ldr	r3, [pc, #2544]	; 1568 <main+0xc80>
     b74:	e50b3038 	str	r3, [fp, #-56]	; 0x38

					localScheduler.basePeriodStartOverhead.msb = 0;
     b78:	e3a03000 	mov	r3, #0, 0
     b7c:	e50b3074 	str	r3, [fp, #-116]	; 0x74
					localScheduler.basePeriodStartOverhead.lsb = 10000000;	// 0.1s
     b80:	e3a03726 	mov	r3, #9961472	; 0x980000
     b84:	e2833c96 	add	r3, r3, #38400	; 0x9600
     b88:	e2833080 	add	r3, r3, #128, 0	; 0x80
     b8c:	e50b3070 	str	r3, [fp, #-112]	; 0x70
					localScheduler.basePeriodEndOverhead.msb = 0;
     b90:	e3a03000 	mov	r3, #0, 0
     b94:	e50b306c 	str	r3, [fp, #-108]	; 0x6c
					localScheduler.basePeriodEndOverhead.lsb = 10000000;	// 0.1s
     b98:	e3a03726 	mov	r3, #9961472	; 0x980000
     b9c:	e2833c96 	add	r3, r3, #38400	; 0x9600
     ba0:	e2833080 	add	r3, r3, #128, 0	; 0x80
     ba4:	e50b3068 	str	r3, [fp, #-104]	; 0x68
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);
     ba8:	e59f399c 	ldr	r3, [pc, #2460]	; 154c <main+0xc64>
     bac:	e5933004 	ldr	r3, [r3, #4]
     bb0:	e59f2994 	ldr	r2, [pc, #2452]	; 154c <main+0xc64>
     bb4:	e5922008 	ldr	r2, [r2, #8]
     bb8:	e51b106c 	ldr	r1, [fp, #-108]	; 0x6c
     bbc:	e51b0068 	ldr	r0, [fp, #-104]	; 0x68
     bc0:	e1a07003 	mov	r7, r3
     bc4:	e1a08002 	mov	r8, r2
     bc8:	e0588000 	subs	r8, r8, r0
     bcc:	e0c77001 	sbc	r7, r7, r1
     bd0:	e1a02007 	mov	r2, r7
     bd4:	e1a03008 	mov	r3, r8
     bd8:	e50b205c 	str	r2, [fp, #-92]	; 0x5c
     bdc:	e50b3058 	str	r3, [fp, #-88]	; 0x58

					globalScheduler.localScheduler2 = &localScheduler;
     be0:	e59f2964 	ldr	r2, [pc, #2404]	; 154c <main+0xc64>
     be4:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     be8:	e582301c 	str	r3, [r2, #28]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler2);
     bec:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     bf0:	e1a03103 	lsl	r3, r3, #2
     bf4:	e59f2954 	ldr	r2, [pc, #2388]	; 1550 <main+0xc68>
     bf8:	e0833002 	add	r3, r3, r2
     bfc:	e59f2968 	ldr	r2, [pc, #2408]	; 156c <main+0xc84>
     c00:	e5832000 	str	r2, [r3]
					break;
     c04:	ea00003d 	b	d00 <main+0x418>

		case (3):	// Hardware thread 3.

					// Create a static schedule for hardware thread 3.
					// [four]
					ptarmCreateTask(&four, &&four, &localScheduler);
     c08:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
     c0c:	e59f395c 	ldr	r3, [pc, #2396]	; 1570 <main+0xc88>
     c10:	e1a01003 	mov	r1, r3
     c14:	e59f0958 	ldr	r0, [pc, #2392]	; 1574 <main+0xc8c>
     c18:	ebfffec8 	bl	740 <ptarmCreateTask>
					staticSchedule[0] = &four;
     c1c:	e59f3950 	ldr	r3, [pc, #2384]	; 1574 <main+0xc8c>
     c20:	e50b3038 	str	r3, [fp, #-56]	; 0x38
			
					// Calculate the duration of the base period that can be used to execute tasks.
					localScheduler.basePeriodStartOverhead.msb = 0;
     c24:	e3a03000 	mov	r3, #0, 0
     c28:	e50b3074 	str	r3, [fp, #-116]	; 0x74
					localScheduler.basePeriodStartOverhead.lsb = 10000000;	// 0.1s
     c2c:	e3a03726 	mov	r3, #9961472	; 0x980000
     c30:	e2833c96 	add	r3, r3, #38400	; 0x9600
     c34:	e2833080 	add	r3, r3, #128, 0	; 0x80
     c38:	e50b3070 	str	r3, [fp, #-112]	; 0x70
					localScheduler.basePeriodEndOverhead.msb = 0;
     c3c:	e3a03000 	mov	r3, #0, 0
     c40:	e50b306c 	str	r3, [fp, #-108]	; 0x6c
					localScheduler.basePeriodEndOverhead.lsb = 10000000;	// 0.1s
     c44:	e3a03726 	mov	r3, #9961472	; 0x980000
     c48:	e2833c96 	add	r3, r3, #38400	; 0x9600
     c4c:	e2833080 	add	r3, r3, #128, 0	; 0x80
     c50:	e50b3068 	str	r3, [fp, #-104]	; 0x68
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);
     c54:	e59f38f0 	ldr	r3, [pc, #2288]	; 154c <main+0xc64>
     c58:	e5933004 	ldr	r3, [r3, #4]
     c5c:	e59f28e8 	ldr	r2, [pc, #2280]	; 154c <main+0xc64>
     c60:	e5922008 	ldr	r2, [r2, #8]
     c64:	e51b106c 	ldr	r1, [fp, #-108]	; 0x6c
     c68:	e51b0068 	ldr	r0, [fp, #-104]	; 0x68
     c6c:	e1a07003 	mov	r7, r3
     c70:	e1a08002 	mov	r8, r2
     c74:	e0588000 	subs	r8, r8, r0
     c78:	e0c77001 	sbc	r7, r7, r1
     c7c:	e1a02007 	mov	r2, r7
     c80:	e1a03008 	mov	r3, r8
     c84:	e50b205c 	str	r2, [fp, #-92]	; 0x5c
     c88:	e50b3058 	str	r3, [fp, #-88]	; 0x58

					globalScheduler.localScheduler3 = &localScheduler;
     c8c:	e59f28b8 	ldr	r2, [pc, #2232]	; 154c <main+0xc64>
     c90:	e24b30ac 	sub	r3, fp, #172, 0	; 0xac
     c94:	e5823020 	str	r3, [r2, #32]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler3);
     c98:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     c9c:	e1a03103 	lsl	r3, r3, #2
     ca0:	e59f28a8 	ldr	r2, [pc, #2216]	; 1550 <main+0xc68>
     ca4:	e0833002 	add	r3, r3, r2
     ca8:	e59f28c8 	ldr	r2, [pc, #2248]	; 1578 <main+0xc90>
     cac:	e5832000 	str	r2, [r3]
					break;
     cb0:	ea000012 	b	d00 <main+0x418>

		default:	// Unknown hardware thread ID.

					PTARM_MUTEX_LOCK();
     cb4:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
					printf("!! Initialisation error: Unknown hwThreadId = "); printf(utoa(localScheduler.hwThreadId)); printf("\n");
     cb8:	e59f08bc 	ldr	r0, [pc, #2236]	; 157c <main+0xc94>
     cbc:	ebfffdcf 	bl	400 <ptarmUartOutputStr>
     cc0:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     cc4:	e1a00003 	mov	r0, r3
     cc8:	ebfffe24 	bl	560 <utoa>
     ccc:	e1a03000 	mov	r3, r0
     cd0:	e1a00003 	mov	r0, r3
     cd4:	ebfffdc9 	bl	400 <ptarmUartOutputStr>
     cd8:	e59f08a0 	ldr	r0, [pc, #2208]	; 1580 <main+0xc98>
     cdc:	ebfffdc7 	bl	400 <ptarmUartOutputStr>
					PTARM_MUTEX_UNLOCK();
     ce0:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
					while (halt);
     ce4:	e1a00000 	nop			; (mov r0, r0)
     ce8:	e59f3894 	ldr	r3, [pc, #2196]	; 1584 <main+0xc9c>
     cec:	e5d33000 	ldrb	r3, [r3]
     cf0:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     cf4:	e3530000 	cmp	r3, #0, 0
     cf8:	1afffffa 	bne	ce8 <main+0x400>
					break;
     cfc:	e1a00000 	nop			; (mov r0, r0)
	}

	// All hardware threads execute this.
	while(globalScheduler.isInitialised == false);
     d00:	e1a00000 	nop			; (mov r0, r0)
     d04:	e59f3840 	ldr	r3, [pc, #2112]	; 154c <main+0xc64>
     d08:	e5d33000 	ldrb	r3, [r3]
     d0c:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     d10:	e3530000 	cmp	r3, #0, 0
     d14:	0afffffa 	beq	d04 <main+0x41c>
	localScheduler.basePeriodStart = globalScheduler.basePeriodFirstStart;
     d18:	e59f282c 	ldr	r2, [pc, #2092]	; 154c <main+0xc64>
     d1c:	e24b3080 	sub	r3, fp, #128, 0	; 0x80
     d20:	e282200c 	add	r2, r2, #12, 0
     d24:	e8920003 	ldm	r2, {r0, r1}
     d28:	e8830003 	stm	r3, {r0, r1}
	PTARM_GOTO(localScheduler);
     d2c:	ea0000a5 	b	fc8 <main+0x6e0>


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
     d30:	e1a00000 	nop			; (mov r0, r0)
     d34:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     d38:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     d3c:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     d40:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     d44:	e59f3800 	ldr	r3, [pc, #2048]	; 154c <main+0xc64>
     d48:	e5933014 	ldr	r3, [r3, #20]
     d4c:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     d50:	e58d7038 	str	r7, [sp, #56]	; 0x38
     d54:	e1a0200d 	mov	r2, sp
     d58:	e5832014 	str	r2, [r3, #20]
     d5c:	e59f37e8 	ldr	r3, [pc, #2024]	; 154c <main+0xc64>
     d60:	e5933014 	ldr	r3, [r3, #20]
     d64:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     d68:	e1a02007 	mov	r2, r7
     d6c:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler0);
     d70:	e59f37d4 	ldr	r3, [pc, #2004]	; 154c <main+0xc64>
     d74:	e5933014 	ldr	r3, [r3, #20]
     d78:	e593300c 	ldr	r3, [r3, #12]
     d7c:	e59f27c8 	ldr	r2, [pc, #1992]	; 154c <main+0xc64>
     d80:	e5922014 	ldr	r2, [r2, #20]
     d84:	e5922008 	ldr	r2, [r2, #8]
     d88:	e1a0d003 	mov	sp, r3
     d8c:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     d90:	ea00004a 	b	ec0 <main+0x5d8>
}

// For hardware thread 1.
eoeHandler1: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler1);
     d94:	e1a00000 	nop			; (mov r0, r0)
     d98:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     d9c:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     da0:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     da4:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     da8:	e59f379c 	ldr	r3, [pc, #1948]	; 154c <main+0xc64>
     dac:	e5933018 	ldr	r3, [r3, #24]
     db0:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     db4:	e58d7038 	str	r7, [sp, #56]	; 0x38
     db8:	e1a0200d 	mov	r2, sp
     dbc:	e5832014 	str	r2, [r3, #20]
     dc0:	e59f3784 	ldr	r3, [pc, #1924]	; 154c <main+0xc64>
     dc4:	e5933018 	ldr	r3, [r3, #24]
     dc8:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     dcc:	e1a02007 	mov	r2, r7
     dd0:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler1);
     dd4:	e59f3770 	ldr	r3, [pc, #1904]	; 154c <main+0xc64>
     dd8:	e5933018 	ldr	r3, [r3, #24]
     ddc:	e593300c 	ldr	r3, [r3, #12]
     de0:	e59f2764 	ldr	r2, [pc, #1892]	; 154c <main+0xc64>
     de4:	e5922018 	ldr	r2, [r2, #24]
     de8:	e5922008 	ldr	r2, [r2, #8]
     dec:	e1a0d003 	mov	sp, r3
     df0:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     df4:	ea000031 	b	ec0 <main+0x5d8>
}

// For hardware thread 2.
eoeHandler2: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler2);
     df8:	e1a00000 	nop			; (mov r0, r0)
     dfc:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     e00:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     e04:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     e08:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     e0c:	e59f3738 	ldr	r3, [pc, #1848]	; 154c <main+0xc64>
     e10:	e593301c 	ldr	r3, [r3, #28]
     e14:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     e18:	e58d7038 	str	r7, [sp, #56]	; 0x38
     e1c:	e1a0200d 	mov	r2, sp
     e20:	e5832014 	str	r2, [r3, #20]
     e24:	e59f3720 	ldr	r3, [pc, #1824]	; 154c <main+0xc64>
     e28:	e593301c 	ldr	r3, [r3, #28]
     e2c:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     e30:	e1a02007 	mov	r2, r7
     e34:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler2);
     e38:	e59f370c 	ldr	r3, [pc, #1804]	; 154c <main+0xc64>
     e3c:	e593301c 	ldr	r3, [r3, #28]
     e40:	e593300c 	ldr	r3, [r3, #12]
     e44:	e59f2700 	ldr	r2, [pc, #1792]	; 154c <main+0xc64>
     e48:	e592201c 	ldr	r2, [r2, #28]
     e4c:	e5922008 	ldr	r2, [r2, #8]
     e50:	e1a0d003 	mov	sp, r3
     e54:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     e58:	ea000018 	b	ec0 <main+0x5d8>
}

// For hardware thread 3.
eoeHandler3: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler3);
     e5c:	e1a00000 	nop			; (mov r0, r0)
     e60:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     e64:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     e68:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     e6c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     e70:	e59f36d4 	ldr	r3, [pc, #1748]	; 154c <main+0xc64>
     e74:	e5933020 	ldr	r3, [r3, #32]
     e78:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     e7c:	e58d7038 	str	r7, [sp, #56]	; 0x38
     e80:	e1a0200d 	mov	r2, sp
     e84:	e5832014 	str	r2, [r3, #20]
     e88:	e59f36bc 	ldr	r3, [pc, #1724]	; 154c <main+0xc64>
     e8c:	e5933020 	ldr	r3, [r3, #32]
     e90:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     e94:	e1a02007 	mov	r2, r7
     e98:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler3);
     e9c:	e59f36a8 	ldr	r3, [pc, #1704]	; 154c <main+0xc64>
     ea0:	e5933020 	ldr	r3, [r3, #32]
     ea4:	e593300c 	ldr	r3, [r3, #12]
     ea8:	e59f269c 	ldr	r2, [pc, #1692]	; 154c <main+0xc64>
     eac:	e5922020 	ldr	r2, [r2, #32]
     eb0:	e5922008 	ldr	r2, [r2, #8]
     eb4:	e1a0d003 	mov	sp, r3
     eb8:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     ebc:	eaffffff 	b	ec0 <main+0x5d8>
}

eoeHandler: {
	// Assign the saved context to the preempted task.
	if (localScheduler.currentTask != NULL) {
     ec0:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     ec4:	e3530000 	cmp	r3, #0, 0
     ec8:	0a000012 	beq	f18 <main+0x630>

		// "Preempted xxx."
		PTARM_MUTEX_LOCK();
     ecc:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf("  Preempted "); printf(localScheduler.currentTask->name); printf(".\n");
     ed0:	e59f06b0 	ldr	r0, [pc, #1712]	; 1588 <main+0xca0>
     ed4:	ebfffd49 	bl	400 <ptarmUartOutputStr>
     ed8:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     edc:	e5933000 	ldr	r3, [r3]
     ee0:	e1a00003 	mov	r0, r3
     ee4:	ebfffd45 	bl	400 <ptarmUartOutputStr>
     ee8:	e59f069c 	ldr	r0, [pc, #1692]	; 158c <main+0xca4>
     eec:	ebfffd43 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
     ef0:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

		localScheduler.currentTask->state = PTARM_TASK_PREEMPTED;
     ef4:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     ef8:	e3a02001 	mov	r2, #1, 0
     efc:	e5c3200c 	strb	r2, [r3, #12]
		localScheduler.currentTask->sp = localScheduler.preemptedSp;
     f00:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     f04:	e51b2098 	ldr	r2, [fp, #-152]	; 0x98
     f08:	e5832010 	str	r2, [r3, #16]
		localScheduler.currentTask->spsr = localScheduler.preemptedSpsr;
     f0c:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
     f10:	e51b2094 	ldr	r2, [fp, #-148]	; 0x94
     f14:	e5832014 	str	r2, [r3, #20]
	} else {
		// A null task is only possible when the scheduler is preempted during the
		// dynamic scheduling phase.

		// "Preempted scheduler x."
	//	PTARM_MUTEX_LOCK();
	//	printf("  Preempted scheduler "); printf(utoa(localScheduler.hwThreadId)); printf(".\n");
	//	PTARM_MUTEX_UNLOCK();
	}

	// If the preemption occured during the dynamic scheduling phase, then we know
	// that the base period has ended.
	if (localScheduler.phase == PTARM_SCHEDULER_DYNAMIC) {
     f18:	e55b3084 	ldrb	r3, [fp, #-132]	; 0x84
     f1c:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     f20:	e3530002 	cmp	r3, #2, 0
     f24:	1a000026 	bne	fc4 <main+0x6dc>
		// Prepare to resume the static scheduling phase.

		// Return back to the release phase.
		localScheduler.phase = PTARM_SCHEDULER_RELEASE;
     f28:	e3a03000 	mov	r3, #0, 0
     f2c:	e54b3084 	strb	r3, [fp, #-132]	; 0x84

		if (localScheduler.hwThreadId == 0) {
     f30:	e51b30a8 	ldr	r3, [fp, #-168]	; 0xa8
     f34:	e3530000 	cmp	r3, #0, 0
     f38:	1a00000b 	bne	f6c <main+0x684>
			
			// "Base period xxx ended."
			PTARM_MUTEX_LOCK();
     f3c:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
			printf("Base period "); printf(utoa(localScheduler.basePeriodCounter)); printf(" ended.\n");
     f40:	e59f0648 	ldr	r0, [pc, #1608]	; 1590 <main+0xca8>
     f44:	ebfffd2d 	bl	400 <ptarmUartOutputStr>
     f48:	e51b3078 	ldr	r3, [fp, #-120]	; 0x78
     f4c:	e1a00003 	mov	r0, r3
     f50:	ebfffd82 	bl	560 <utoa>
     f54:	e1a03000 	mov	r3, r0
     f58:	e1a00003 	mov	r0, r3
     f5c:	ebfffd27 	bl	400 <ptarmUartOutputStr>
     f60:	e59f062c 	ldr	r0, [pc, #1580]	; 1594 <main+0xcac>
     f64:	ebfffd25 	bl	400 <ptarmUartOutputStr>
			PTARM_MUTEX_UNLOCK();
     f68:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		}

		// Update the timestamp of the start of the next base period.
		localScheduler.basePeriodCounter++;
     f6c:	e51b3078 	ldr	r3, [fp, #-120]	; 0x78
     f70:	e2833001 	add	r3, r3, #1, 0
     f74:	e50b3078 	str	r3, [fp, #-120]	; 0x78
		PTARM_ADD(localScheduler.basePeriodStart, localScheduler.basePeriodStart, globalScheduler.basePeriodDuration);
     f78:	e51b3080 	ldr	r3, [fp, #-128]	; 0x80
     f7c:	e51b207c 	ldr	r2, [fp, #-124]	; 0x7c
     f80:	e59f15c4 	ldr	r1, [pc, #1476]	; 154c <main+0xc64>
     f84:	e5911004 	ldr	r1, [r1, #4]
     f88:	e59f05bc 	ldr	r0, [pc, #1468]	; 154c <main+0xc64>
     f8c:	e5900008 	ldr	r0, [r0, #8]
     f90:	e1a07003 	mov	r7, r3
     f94:	e1a08002 	mov	r8, r2
     f98:	e0988000 	adds	r8, r8, r0
     f9c:	e0a77001 	adc	r7, r7, r1
     fa0:	e1a02007 	mov	r2, r7
     fa4:	e1a03008 	mov	r3, r8
     fa8:	e50b2080 	str	r2, [fp, #-128]	; 0x80
     fac:	e50b307c 	str	r3, [fp, #-124]	; 0x7c

		// Wait until the base period ends. This synchronises the start of the base period with other hardware threads to minimise jitter.
		PTARM_DELAY(localScheduler.basePeriodStart);
     fb0:	e51b3080 	ldr	r3, [fp, #-128]	; 0x80
     fb4:	e51b207c 	ldr	r2, [fp, #-124]	; 0x7c
     fb8:	e1a07003 	mov	r7, r3
     fbc:	e1a08002 	mov	r8, r2
     fc0:	ee470d08 	cdp	13, 4, cr0, cr7, cr8, {0}
	}

	PTARM_GOTO(localScheduler);
     fc4:	eaffffff 	b	fc8 <main+0x6e0>
}


// Local scheduler for each hardware thread.
// It always begins each base period with the static scheduling phase, followed by the dynamic scheduling phase.
localScheduler: {
	/*
	// "Scheduler = xxx, Current Task = xxx."
	PTARM_MUTEX_LOCK();
	printf("Scheduler = "); printf(localScheduler.name); printf(", Current task = "); printf(localScheduler.currentTask->name); printf(".\n");
	PTARM_MUTEX_UNLOCK();
	*/

	switch (localScheduler.phase) {
     fc8:	e55b3084 	ldrb	r3, [fp, #-132]	; 0x84
     fcc:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     fd0:	e3530001 	cmp	r3, #1, 0
     fd4:	0a000045 	beq	10f0 <main+0x808>
     fd8:	e3530002 	cmp	r3, #2, 0
     fdc:	0a000076 	beq	11bc <main+0x8d4>
     fe0:	e3530000 	cmp	r3, #0, 0
     fe4:	1a000080 	bne	11ec <main+0x904>
		case (PTARM_SCHEDULER_RELEASE):
		
			// Go through the static schedule and release any eligible tasks.
			for (localScheduler.nextStaticTask = localScheduler.staticSchedule; (*localScheduler.nextStaticTask) != NULL; localScheduler.nextStaticTask++) {
     fe8:	e51b3090 	ldr	r3, [fp, #-144]	; 0x90
     fec:	e50b3088 	str	r3, [fp, #-136]	; 0x88
     ff0:	ea000025 	b	108c <main+0x7a4>
				
				volatile Task *currentTask = *localScheduler.nextStaticTask;
     ff4:	e51b3088 	ldr	r3, [fp, #-136]	; 0x88
     ff8:	e5933000 	ldr	r3, [r3]
     ffc:	e50b3024 	str	r3, [fp, #-36]	; 0x24
				
				// If the task is paused, check if it can be released for execution (i.e., the minimum number of base periods has elapsed).
				if (currentTask->state == PTARM_TASK_PAUSED && (currentTask->earliestRelease <= localScheduler.basePeriodCounter)) {
    1000:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    1004:	e5d3300c 	ldrb	r3, [r3, #12]
    1008:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    100c:	e3530000 	cmp	r3, #0, 0
    1010:	1a00001a 	bne	1080 <main+0x798>
    1014:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    1018:	e5932028 	ldr	r2, [r3, #40]	; 0x28
    101c:	e51b3078 	ldr	r3, [fp, #-120]	; 0x78
    1020:	e1520003 	cmp	r2, r3
    1024:	8a000015 	bhi	1080 <main+0x798>
					
					// "Released xxx."
					PTARM_MUTEX_LOCK();
    1028:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
					printf("  Releasing "); printf(currentTask->name); printf(".\n");
    102c:	e59f0564 	ldr	r0, [pc, #1380]	; 1598 <main+0xcb0>
    1030:	ebfffcf2 	bl	400 <ptarmUartOutputStr>
    1034:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    1038:	e5933000 	ldr	r3, [r3]
    103c:	e1a00003 	mov	r0, r3
    1040:	ebfffcee 	bl	400 <ptarmUartOutputStr>
    1044:	e59f0540 	ldr	r0, [pc, #1344]	; 158c <main+0xca4>
    1048:	ebfffcec 	bl	400 <ptarmUartOutputStr>
					PTARM_MUTEX_UNLOCK();
    104c:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
					
					// The minimum number of base periods has elapsed, so release the task.
					currentTask->state = PTARM_TASK_RELEASED;
    1050:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    1054:	e3a02002 	mov	r2, #2, 0
    1058:	e5c3200c 	strb	r2, [r3, #12]
					
					// Update its last released timestamp.
					currentTask->lastRelease = localScheduler.basePeriodCounter;
    105c:	e51b2078 	ldr	r2, [fp, #-120]	; 0x78
    1060:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    1064:	e5832024 	str	r2, [r3, #36]	; 0x24
					
					// Update its next earliest release timestamp.
					currentTask->earliestRelease = (localScheduler.basePeriodCounter + currentTask->basePeriodsMin);
    1068:	e51b2078 	ldr	r2, [fp, #-120]	; 0x78
    106c:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    1070:	e5933020 	ldr	r3, [r3, #32]
    1074:	e0822003 	add	r2, r2, r3
    1078:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    107c:	e5832028 	str	r2, [r3, #40]	; 0x28
    1080:	e51b3088 	ldr	r3, [fp, #-136]	; 0x88
    1084:	e2833004 	add	r3, r3, #4, 0
    1088:	e50b3088 	str	r3, [fp, #-136]	; 0x88
    108c:	e51b3088 	ldr	r3, [fp, #-136]	; 0x88
    1090:	e5933000 	ldr	r3, [r3]
    1094:	e3530000 	cmp	r3, #0, 0
    1098:	1affffd5 	bne	ff4 <main+0x70c>
				}
			}
		
			// Reset the static schedule (to the first task).
			localScheduler.nextStaticTask = localScheduler.staticSchedule;
    109c:	e51b3090 	ldr	r3, [fp, #-144]	; 0x90
    10a0:	e50b3088 	str	r3, [fp, #-136]	; 0x88
			
			// Continue through to the next case statement for the static scheduling phase.
			localScheduler.phase = PTARM_SCHEDULER_STATIC;
    10a4:	e3a03001 	mov	r3, #1, 0
    10a8:	e54b3084 	strb	r3, [fp, #-132]	; 0x84
			
			PTARM_ADD(localScheduler.basePeriodStartAfterOverhead, localScheduler.basePeriodStartOverhead, localScheduler.basePeriodStart);
    10ac:	e51b3074 	ldr	r3, [fp, #-116]	; 0x74
    10b0:	e51b2070 	ldr	r2, [fp, #-112]	; 0x70
    10b4:	e51b1080 	ldr	r1, [fp, #-128]	; 0x80
    10b8:	e51b007c 	ldr	r0, [fp, #-124]	; 0x7c
    10bc:	e1a07003 	mov	r7, r3
    10c0:	e1a08002 	mov	r8, r2
    10c4:	e0988000 	adds	r8, r8, r0
    10c8:	e0a77001 	adc	r7, r7, r1
    10cc:	e1a02007 	mov	r2, r7
    10d0:	e1a03008 	mov	r3, r8
    10d4:	e50b2064 	str	r2, [fp, #-100]	; 0x64
    10d8:	e50b3060 	str	r3, [fp, #-96]	; 0x60
			PTARM_DELAY(localScheduler.basePeriodStartAfterOverhead);
    10dc:	e51b3064 	ldr	r3, [fp, #-100]	; 0x64
    10e0:	e51b2060 	ldr	r2, [fp, #-96]	; 0x60
    10e4:	e1a07003 	mov	r7, r3
    10e8:	e1a08002 	mov	r8, r2
    10ec:	ee470d08 	cdp	13, 4, cr0, cr7, cr8, {0}
	
		case (PTARM_SCHEDULER_STATIC):
			// Static scheduling phase.
			// Schedule all the tasks in its static schedule before going into the dynamic scheduling phase.

			// Get the next statically scheduled task.
			localScheduler.currentTask = *localScheduler.nextStaticTask;
    10f0:	e51b3088 	ldr	r3, [fp, #-136]	; 0x88
    10f4:	e5933000 	ldr	r3, [r3]
    10f8:	e50b308c 	str	r3, [fp, #-140]	; 0x8c

			// Check if we have reached the end of the static schedule.
			if (localScheduler.currentTask != NULL) {
    10fc:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    1100:	e3530000 	cmp	r3, #0, 0
    1104:	0a00002a 	beq	11b4 <main+0x8cc>
				// The end of the static schedule has not been reached.

				// Update the next statically scheduled task.
				localScheduler.nextStaticTask++;
    1108:	e51b3088 	ldr	r3, [fp, #-136]	; 0x88
    110c:	e2833004 	add	r3, r3, #4, 0
    1110:	e50b3088 	str	r3, [fp, #-136]	; 0x88

				// Execute the task if it has been preempted or released.
				if (localScheduler.currentTask->state == PTARM_TASK_PREEMPTED || localScheduler.currentTask->state == PTARM_TASK_RELEASED) {
    1114:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    1118:	e5d3300c 	ldrb	r3, [r3, #12]
    111c:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1120:	e3530001 	cmp	r3, #1, 0
    1124:	0a000004 	beq	113c <main+0x854>
    1128:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    112c:	e5d3300c 	ldrb	r3, [r3, #12]
    1130:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1134:	e3530002 	cmp	r3, #2, 0
    1138:	1affffa2 	bne	fc8 <main+0x6e0>

					// Set the task's deadline in this base period to be the end of its statically allocated execution time.
					PTARM_TIME_GET(localScheduler.currentTime);
    113c:	ee870d08 	cdp	13, 8, cr0, cr7, cr8, {0}
    1140:	e1a02007 	mov	r2, r7
    1144:	e1a03008 	mov	r3, r8
    1148:	e50b2054 	str	r2, [fp, #-84]	; 0x54
    114c:	e50b3050 	str	r3, [fp, #-80]	; 0x50
					PTARM_EOE_ENABLE(localScheduler.currentTask->allocatedTime, localScheduler.currentTime);
    1150:	e51b3054 	ldr	r3, [fp, #-84]	; 0x54
    1154:	e51b2050 	ldr	r2, [fp, #-80]	; 0x50
    1158:	e51b108c 	ldr	r1, [fp, #-140]	; 0x8c
    115c:	e5911018 	ldr	r1, [r1, #24]
    1160:	e51b008c 	ldr	r0, [fp, #-140]	; 0x8c
    1164:	e590001c 	ldr	r0, [r0, #28]
    1168:	e1a07003 	mov	r7, r3
    116c:	e1a08002 	mov	r8, r2
    1170:	e0988000 	adds	r8, r8, r0
    1174:	e0a77001 	adc	r7, r7, r1
    1178:	ee270d08 	cdp	13, 2, cr0, cr7, cr8, {0}

					// (Re)set the task's local scheduler to this static local scheduler.
					PTARM_TASK_SET_SCHEDULER(localScheduler.currentTask, &localScheduler);
    117c:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    1180:	e24b20ac 	sub	r2, fp, #172, 0	; 0xac
    1184:	e5832008 	str	r2, [r3, #8]

					// Context switch to the current task.
					PTARM_TASK_RESTORE_CONTEXT(localScheduler.currentTask);
    1188:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    118c:	e5933014 	ldr	r3, [r3, #20]
    1190:	e1a08003 	mov	r8, r3
    1194:	ee200c08 	cdp	12, 2, cr0, cr0, cr8, {0}
    1198:	e51b308c 	ldr	r3, [fp, #-140]	; 0x8c
    119c:	e5933010 	ldr	r3, [r3, #16]
    11a0:	e1a0d003 	mov	sp, r3
    11a4:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
    11a8:	e8bd1fff 	pop	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    11ac:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)
    11b0:	ea000001 	b	11bc <main+0x8d4>
				} else {
					// Pick the next task to execute instead.
					goto localScheduler;
				}
			} else {
				// The end of the static schedule has been reached. Prepare for the dynamic scheduling phase.

				// We are now entering the dynamic scheduling phase.
				localScheduler.phase = PTARM_SCHEDULER_DYNAMIC;
    11b4:	e3a03002 	mov	r3, #2, 0
    11b8:	e54b3084 	strb	r3, [fp, #-132]	; 0x84

				// Continue through to the next case statement for the dynamic scheduling phase.
			}
			
		case (PTARM_SCHEDULER_DYNAMIC):;
			// Dynamic scheduling phase.
			
			// (Re)set the current task in case a timing exception occurs when the scheduler is executing.
			localScheduler.currentTask = NULL;
    11bc:	e3a03000 	mov	r3, #0, 0
    11c0:	e50b308c 	str	r3, [fp, #-140]	; 0x8c

			// Set the dynamic execution deadline to be the end of the base period, minus the expected scheduling overhead.
			PTARM_EOE_ENABLE(localScheduler.basePeriodMinusEndingOverhead, localScheduler.basePeriodStart);
    11c4:	e51b3080 	ldr	r3, [fp, #-128]	; 0x80
    11c8:	e51b207c 	ldr	r2, [fp, #-124]	; 0x7c
    11cc:	e51b105c 	ldr	r1, [fp, #-92]	; 0x5c
    11d0:	e51b0058 	ldr	r0, [fp, #-88]	; 0x58
    11d4:	e1a07003 	mov	r7, r3
    11d8:	e1a08002 	mov	r8, r2
    11dc:	e0988000 	adds	r8, r8, r0
    11e0:	e0a77001 	adc	r7, r7, r1
    11e4:	ee270d08 	cdp	13, 2, cr0, cr7, cr8, {0}

			// Wait for the base period to end.
			goto localScheduler;
    11e8:	eaffff76 	b	fc8 <main+0x6e0>
			break;

		default:
			// Undefined scheduling phase.

			safe_printf("!! Scheduling error: Oops!\n");
    11ec:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
    11f0:	e59f03a4 	ldr	r0, [pc, #932]	; 159c <main+0xcb4>
    11f4:	ebfffc81 	bl	400 <ptarmUartOutputStr>
    11f8:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
			while (halt);
    11fc:	e1a00000 	nop			; (mov r0, r0)
    1200:	e59f337c 	ldr	r3, [pc, #892]	; 1584 <main+0xc9c>
    1204:	e5d33000 	ldrb	r3, [r3]
    1208:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    120c:	e3530000 	cmp	r3, #0, 0
    1210:	1afffffa 	bne	1200 <main+0x918>
			break;
    1214:	e1a00000 	nop			; (mov r0, r0)
	}
}

// The tasks.
// Note that they are defined within the main function.

one: {
	while (foreverTrue) {
    1218:	ea00002a 	b	12c8 <main+0x9e0>
		int i;
		for (i = 0; i < 2500000u; i++);
    121c:	e3a03000 	mov	r3, #0, 0
    1220:	e50b3010 	str	r3, [fp, #-16]
    1224:	ea000002 	b	1234 <main+0x94c>
    1228:	e51b3010 	ldr	r3, [fp, #-16]
    122c:	e2833001 	add	r3, r3, #1, 0
    1230:	e50b3010 	str	r3, [fp, #-16]
    1234:	e51b2010 	ldr	r2, [fp, #-16]
    1238:	e3a03826 	mov	r3, #2490368	; 0x260000
    123c:	e2833d96 	add	r3, r3, #9600	; 0x2580
    1240:	e283301f 	add	r3, r3, #31, 0
    1244:	e1520003 	cmp	r2, r3
    1248:	9afffff6 	bls	1228 <main+0x940>

		PTARM_MUTEX_LOCK();
    124c:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf("  one pausing.\n");
    1250:	e59f0348 	ldr	r0, [pc, #840]	; 15a0 <main+0xcb8>
    1254:	ebfffc69 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    1258:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(one, 1);
    125c:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    1260:	e59f32e0 	ldr	r3, [pc, #736]	; 1548 <main+0xc60>
    1264:	e3a02000 	mov	r2, #0, 0
    1268:	e5c3200c 	strb	r2, [r3, #12]
    126c:	e1a00000 	nop			; (mov r0, r0)
    1270:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    1274:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    1278:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    127c:	e59f3320 	ldr	r3, [pc, #800]	; 15a4 <main+0xcbc>
    1280:	e1a07003 	mov	r7, r3
    1284:	e58d7038 	str	r7, [sp, #56]	; 0x38
    1288:	e1a0300d 	mov	r3, sp
    128c:	e59f22b4 	ldr	r2, [pc, #692]	; 1548 <main+0xc60>
    1290:	e5823010 	str	r3, [r2, #16]
    1294:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    1298:	e1a03007 	mov	r3, r7
    129c:	e59f22a4 	ldr	r2, [pc, #676]	; 1548 <main+0xc60>
    12a0:	e5823014 	str	r3, [r2, #20]
    12a4:	e59f329c 	ldr	r3, [pc, #668]	; 1548 <main+0xc60>
    12a8:	e5933008 	ldr	r3, [r3, #8]
    12ac:	e593300c 	ldr	r3, [r3, #12]
    12b0:	e59f2290 	ldr	r2, [pc, #656]	; 1548 <main+0xc60>
    12b4:	e5922008 	ldr	r2, [r2, #8]
    12b8:	e5922008 	ldr	r2, [r2, #8]
    12bc:	e1a0d003 	mov	sp, r3
    12c0:	e1a0b002 	mov	fp, r2
    12c4:	eaffff3f 	b	fc8 <main+0x6e0>
    12c8:	e59f32d8 	ldr	r3, [pc, #728]	; 15a8 <main+0xcc0>
    12cc:	e5d33000 	ldrb	r3, [r3]
    12d0:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    12d4:	e3530000 	cmp	r3, #0, 0
    12d8:	1affffcf 	bne	121c <main+0x934>
	}
}

two: {
	while (foreverTrue) {
    12dc:	ea00002a 	b	138c <main+0xaa4>
		int i;
		for (i = 0; i < 3000000u; i++);
    12e0:	e3a03000 	mov	r3, #0, 0
    12e4:	e50b3014 	str	r3, [fp, #-20]
    12e8:	ea000002 	b	12f8 <main+0xa10>
    12ec:	e51b3014 	ldr	r3, [fp, #-20]
    12f0:	e2833001 	add	r3, r3, #1, 0
    12f4:	e50b3014 	str	r3, [fp, #-20]
    12f8:	e51b2014 	ldr	r2, [fp, #-20]
    12fc:	e3a039b7 	mov	r3, #2998272	; 0x2dc000
    1300:	e2833e6b 	add	r3, r3, #1712	; 0x6b0
    1304:	e283300f 	add	r3, r3, #15, 0
    1308:	e1520003 	cmp	r2, r3
    130c:	9afffff6 	bls	12ec <main+0xa04>

		PTARM_MUTEX_LOCK();
    1310:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf("  two pausing.\n");
    1314:	e59f0290 	ldr	r0, [pc, #656]	; 15ac <main+0xcc4>
    1318:	ebfffc38 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    131c:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(two, 1);
    1320:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    1324:	e59f3230 	ldr	r3, [pc, #560]	; 155c <main+0xc74>
    1328:	e3a02000 	mov	r2, #0, 0
    132c:	e5c3200c 	strb	r2, [r3, #12]
    1330:	e1a00000 	nop			; (mov r0, r0)
    1334:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    1338:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    133c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    1340:	e59f3268 	ldr	r3, [pc, #616]	; 15b0 <main+0xcc8>
    1344:	e1a07003 	mov	r7, r3
    1348:	e58d7038 	str	r7, [sp, #56]	; 0x38
    134c:	e1a0300d 	mov	r3, sp
    1350:	e59f2204 	ldr	r2, [pc, #516]	; 155c <main+0xc74>
    1354:	e5823010 	str	r3, [r2, #16]
    1358:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    135c:	e1a03007 	mov	r3, r7
    1360:	e59f21f4 	ldr	r2, [pc, #500]	; 155c <main+0xc74>
    1364:	e5823014 	str	r3, [r2, #20]
    1368:	e59f31ec 	ldr	r3, [pc, #492]	; 155c <main+0xc74>
    136c:	e5933008 	ldr	r3, [r3, #8]
    1370:	e593300c 	ldr	r3, [r3, #12]
    1374:	e59f21e0 	ldr	r2, [pc, #480]	; 155c <main+0xc74>
    1378:	e5922008 	ldr	r2, [r2, #8]
    137c:	e5922008 	ldr	r2, [r2, #8]
    1380:	e1a0d003 	mov	sp, r3
    1384:	e1a0b002 	mov	fp, r2
    1388:	eaffff0e 	b	fc8 <main+0x6e0>
    138c:	e59f3214 	ldr	r3, [pc, #532]	; 15a8 <main+0xcc0>
    1390:	e5d33000 	ldrb	r3, [r3]
    1394:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1398:	e3530000 	cmp	r3, #0, 0
    139c:	1affffcf 	bne	12e0 <main+0x9f8>
	}
}

three: {
	while (foreverTrue) {
    13a0:	ea00002a 	b	1450 <main+0xb68>
		int i;
		for (i = 0; i < 2500000u; i++);
    13a4:	e3a03000 	mov	r3, #0, 0
    13a8:	e50b3018 	str	r3, [fp, #-24]
    13ac:	ea000002 	b	13bc <main+0xad4>
    13b0:	e51b3018 	ldr	r3, [fp, #-24]
    13b4:	e2833001 	add	r3, r3, #1, 0
    13b8:	e50b3018 	str	r3, [fp, #-24]
    13bc:	e51b2018 	ldr	r2, [fp, #-24]
    13c0:	e3a03826 	mov	r3, #2490368	; 0x260000
    13c4:	e2833d96 	add	r3, r3, #9600	; 0x2580
    13c8:	e283301f 	add	r3, r3, #31, 0
    13cc:	e1520003 	cmp	r2, r3
    13d0:	9afffff6 	bls	13b0 <main+0xac8>

		PTARM_MUTEX_LOCK();
    13d4:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf("  three pausing.\n");
    13d8:	e59f01d4 	ldr	r0, [pc, #468]	; 15b4 <main+0xccc>
    13dc:	ebfffc07 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    13e0:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(three, 1);
    13e4:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    13e8:	e59f3178 	ldr	r3, [pc, #376]	; 1568 <main+0xc80>
    13ec:	e3a02000 	mov	r2, #0, 0
    13f0:	e5c3200c 	strb	r2, [r3, #12]
    13f4:	e1a00000 	nop			; (mov r0, r0)
    13f8:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    13fc:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    1400:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    1404:	e59f31ac 	ldr	r3, [pc, #428]	; 15b8 <main+0xcd0>
    1408:	e1a07003 	mov	r7, r3
    140c:	e58d7038 	str	r7, [sp, #56]	; 0x38
    1410:	e1a0300d 	mov	r3, sp
    1414:	e59f214c 	ldr	r2, [pc, #332]	; 1568 <main+0xc80>
    1418:	e5823010 	str	r3, [r2, #16]
    141c:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    1420:	e1a03007 	mov	r3, r7
    1424:	e59f213c 	ldr	r2, [pc, #316]	; 1568 <main+0xc80>
    1428:	e5823014 	str	r3, [r2, #20]
    142c:	e59f3134 	ldr	r3, [pc, #308]	; 1568 <main+0xc80>
    1430:	e5933008 	ldr	r3, [r3, #8]
    1434:	e593300c 	ldr	r3, [r3, #12]
    1438:	e59f2128 	ldr	r2, [pc, #296]	; 1568 <main+0xc80>
    143c:	e5922008 	ldr	r2, [r2, #8]
    1440:	e5922008 	ldr	r2, [r2, #8]
    1444:	e1a0d003 	mov	sp, r3
    1448:	e1a0b002 	mov	fp, r2
    144c:	eafffedd 	b	fc8 <main+0x6e0>
    1450:	e59f3150 	ldr	r3, [pc, #336]	; 15a8 <main+0xcc0>
    1454:	e5d33000 	ldrb	r3, [r3]
    1458:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    145c:	e3530000 	cmp	r3, #0, 0
    1460:	1affffcf 	bne	13a4 <main+0xabc>
	}
}

four: {
	while (foreverTrue) {
    1464:	ea00002a 	b	1514 <main+0xc2c>
		int i;
		for (i = 0; i < 2500000u; i++);
    1468:	e3a03000 	mov	r3, #0, 0
    146c:	e50b301c 	str	r3, [fp, #-28]
    1470:	ea000002 	b	1480 <main+0xb98>
    1474:	e51b301c 	ldr	r3, [fp, #-28]
    1478:	e2833001 	add	r3, r3, #1, 0
    147c:	e50b301c 	str	r3, [fp, #-28]
    1480:	e51b201c 	ldr	r2, [fp, #-28]
    1484:	e3a03826 	mov	r3, #2490368	; 0x260000
    1488:	e2833d96 	add	r3, r3, #9600	; 0x2580
    148c:	e283301f 	add	r3, r3, #31, 0
    1490:	e1520003 	cmp	r2, r3
    1494:	9afffff6 	bls	1474 <main+0xb8c>

		PTARM_MUTEX_LOCK();
    1498:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf("  four pausing.\n");
    149c:	e59f0118 	ldr	r0, [pc, #280]	; 15bc <main+0xcd4>
    14a0:	ebfffbd6 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    14a4:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(four, 1);
    14a8:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    14ac:	e59f30c0 	ldr	r3, [pc, #192]	; 1574 <main+0xc8c>
    14b0:	e3a02000 	mov	r2, #0, 0
    14b4:	e5c3200c 	strb	r2, [r3, #12]
    14b8:	e1a00000 	nop			; (mov r0, r0)
    14bc:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    14c0:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    14c4:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    14c8:	e59f30f0 	ldr	r3, [pc, #240]	; 15c0 <main+0xcd8>
    14cc:	e1a07003 	mov	r7, r3
    14d0:	e58d7038 	str	r7, [sp, #56]	; 0x38
    14d4:	e1a0300d 	mov	r3, sp
    14d8:	e59f2094 	ldr	r2, [pc, #148]	; 1574 <main+0xc8c>
    14dc:	e5823010 	str	r3, [r2, #16]
    14e0:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    14e4:	e1a03007 	mov	r3, r7
    14e8:	e59f2084 	ldr	r2, [pc, #132]	; 1574 <main+0xc8c>
    14ec:	e5823014 	str	r3, [r2, #20]
    14f0:	e59f307c 	ldr	r3, [pc, #124]	; 1574 <main+0xc8c>
    14f4:	e5933008 	ldr	r3, [r3, #8]
    14f8:	e593300c 	ldr	r3, [r3, #12]
    14fc:	e59f2070 	ldr	r2, [pc, #112]	; 1574 <main+0xc8c>
    1500:	e5922008 	ldr	r2, [r2, #8]
    1504:	e5922008 	ldr	r2, [r2, #8]
    1508:	e1a0d003 	mov	sp, r3
    150c:	e1a0b002 	mov	fp, r2
    1510:	eafffeac 	b	fc8 <main+0x6e0>
    1514:	e59f308c 	ldr	r3, [pc, #140]	; 15a8 <main+0xcc0>
    1518:	e5d33000 	ldrb	r3, [r3]
    151c:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1520:	e3530000 	cmp	r3, #0, 0
    1524:	1affffcf 	bne	1468 <main+0xb80>
	}
}

	return 0;
    1528:	e3a03000 	mov	r3, #0, 0
}
    152c:	e1a00003 	mov	r0, r3
    1530:	e24bd00c 	sub	sp, fp, #12, 0
    1534:	e8bd8980 	pop	{r7, r8, fp, pc}
    1538:	0000174c 	.word	0x0000174c
    153c:	00000fc8 	.word	0x00000fc8
    1540:	00001654 	.word	0x00001654
    1544:	00001218 	.word	0x00001218
    1548:	00001854 	.word	0x00001854
    154c:	000019a4 	.word	0x000019a4
    1550:	0001ffe0 	.word	0x0001ffe0
    1554:	00000d30 	.word	0x00000d30
    1558:	000012dc 	.word	0x000012dc
    155c:	000018a8 	.word	0x000018a8
    1560:	00000d94 	.word	0x00000d94
    1564:	000013a0 	.word	0x000013a0
    1568:	000018fc 	.word	0x000018fc
    156c:	00000df8 	.word	0x00000df8
    1570:	00001464 	.word	0x00001464
    1574:	00001950 	.word	0x00001950
    1578:	00000e5c 	.word	0x00000e5c
    157c:	00001674 	.word	0x00001674
    1580:	000016a4 	.word	0x000016a4
    1584:	00001850 	.word	0x00001850
    1588:	000016a8 	.word	0x000016a8
    158c:	000016b8 	.word	0x000016b8
    1590:	000016bc 	.word	0x000016bc
    1594:	000016cc 	.word	0x000016cc
    1598:	000016d8 	.word	0x000016d8
    159c:	000016e8 	.word	0x000016e8
    15a0:	00001704 	.word	0x00001704
    15a4:	000012c8 	.word	0x000012c8
    15a8:	00001851 	.word	0x00001851
    15ac:	00001714 	.word	0x00001714
    15b0:	0000138c 	.word	0x0000138c
    15b4:	00001724 	.word	0x00001724
    15b8:	00001450 	.word	0x00001450
    15bc:	00001738 	.word	0x00001738
    15c0:	00001514 	.word	0x00001514

Disassembly of section .text.memset:

00001758 <memset>:
    1758:	e3100003 	tst	r0, #3, 0
    175c:	e92d4010 	push	{r4, lr}
    1760:	0a000037 	beq	1844 <memset+0xec>
    1764:	e3520000 	cmp	r2, #0, 0
    1768:	e2422001 	sub	r2, r2, #1, 0
    176c:	0a000032 	beq	183c <memset+0xe4>
    1770:	e201c0ff 	and	ip, r1, #255, 0	; 0xff
    1774:	e1a03000 	mov	r3, r0
    1778:	ea000002 	b	1788 <memset+0x30>
    177c:	e3520000 	cmp	r2, #0, 0
    1780:	e2422001 	sub	r2, r2, #1, 0
    1784:	0a00002c 	beq	183c <memset+0xe4>
    1788:	e4c3c001 	strb	ip, [r3], #1
    178c:	e3130003 	tst	r3, #3, 0
    1790:	1afffff9 	bne	177c <memset+0x24>
    1794:	e3520003 	cmp	r2, #3, 0
    1798:	9a000020 	bls	1820 <memset+0xc8>
    179c:	e201e0ff 	and	lr, r1, #255, 0	; 0xff
    17a0:	e18ee40e 	orr	lr, lr, lr, lsl #8
    17a4:	e352000f 	cmp	r2, #15, 0
    17a8:	e18ee80e 	orr	lr, lr, lr, lsl #16
    17ac:	9a000010 	bls	17f4 <memset+0x9c>
    17b0:	e1a04002 	mov	r4, r2
    17b4:	e283c010 	add	ip, r3, #16, 0
    17b8:	e2444010 	sub	r4, r4, #16, 0
    17bc:	e354000f 	cmp	r4, #15, 0
    17c0:	e50ce010 	str	lr, [ip, #-16]
    17c4:	e50ce00c 	str	lr, [ip, #-12]
    17c8:	e50ce008 	str	lr, [ip, #-8]
    17cc:	e50ce004 	str	lr, [ip, #-4]
    17d0:	e28cc010 	add	ip, ip, #16, 0
    17d4:	8afffff7 	bhi	17b8 <memset+0x60>
    17d8:	e242c010 	sub	ip, r2, #16, 0
    17dc:	e3ccc00f 	bic	ip, ip, #15, 0
    17e0:	e202200f 	and	r2, r2, #15, 0
    17e4:	e28cc010 	add	ip, ip, #16, 0
    17e8:	e3520003 	cmp	r2, #3, 0
    17ec:	e083300c 	add	r3, r3, ip
    17f0:	9a00000a 	bls	1820 <memset+0xc8>
    17f4:	e1a04003 	mov	r4, r3
    17f8:	e1a0c002 	mov	ip, r2
    17fc:	e24cc004 	sub	ip, ip, #4, 0
    1800:	e35c0003 	cmp	ip, #3, 0
    1804:	e484e004 	str	lr, [r4], #4
    1808:	8afffffb 	bhi	17fc <memset+0xa4>
    180c:	e242c004 	sub	ip, r2, #4, 0
    1810:	e3ccc003 	bic	ip, ip, #3, 0
    1814:	e28cc004 	add	ip, ip, #4, 0
    1818:	e083300c 	add	r3, r3, ip
    181c:	e2022003 	and	r2, r2, #3, 0
    1820:	e3520000 	cmp	r2, #0, 0
    1824:	120110ff 	andne	r1, r1, #255, 0	; 0xff
    1828:	10832002 	addne	r2, r3, r2
    182c:	0a000002 	beq	183c <memset+0xe4>
    1830:	e4c31001 	strb	r1, [r3], #1
    1834:	e1530002 	cmp	r3, r2
    1838:	1afffffc 	bne	1830 <memset+0xd8>
    183c:	e8bd4010 	pop	{r4, lr}
    1840:	e1a0f00e 	mov	pc, lr
    1844:	e1a03000 	mov	r3, r0
    1848:	eaffffd1 	b	1794 <memset+0x3c>
