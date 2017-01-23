
_build/foremc.elf:     file format elf32-littlearm

SYMBOL TABLE:
00000000 l    d  .text	00000000 .text
000028dc l    d  .rodata	00000000 .rodata
00002b30 l    d  .text.memset	00000000 .text.memset
00002c24 l    d  .data	00000000 .data
00003058 l    d  .bss	00000000 .bss
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
00000000 l    df *ABS*	00000000 foremc.c
00000000 l    df *ABS*	00000000 memset.c
000006ec g     F .text	000001a8 ptarmCreateTask
00003058 g     O .bss	00000002 ptarmLcdCharCount
00000894 g     F .text	00000054 foreMcGetIndex
00002d28 g     O .data	00000054 l4
00000278 g     F .text	0000013c ptarmLcdOutputStr
000030fc g     O .bss	00000050 priorityQueueLife
000003b4 g     F .text	0000004c ptarmUartOutputChar
000032fc g       .bss	00000000 addr_stack_limit
00002f20 g     O .data	00000054 n2
000030ac g     O .bss	00000050 priorityQueueMission
0000301c g     O .data	0000003c globalScheduler
00000400 g     F .text	0000004c ptarmUartOutputStr
0000305c g     O .bss	00000050 priorityQueueNonCritical
00002c24 g     O .data	00000004 ptarmPreviousTaskStackEnd
0000044c g     F .text	00000114 itoa
00002e78 g     O .data	00000054 m4
00002dd0 g     O .data	00000054 m2
0000008c g     F .text	0000003c ptarmLedOutput
00002c80 g     O .data	00000054 l2
00000560 g     F .text	000000e4 utoa
0000314c g     O .bss	000001a4 bufferOne
000032fc g       .bss	00000000 bss_end
00002ecc g     O .data	00000054 n1
00002fc8 g     O .data	00000054 n4
000002a4 g       *ABS*	00000000 bss_size
00003058 g       .data	00000000 bss_start
000000c8 g     F .text	0000004c ptarmSevenSegOutput
00002b30 g     F .text.memset	000000f4 memset
000008e8 g     F .text	00001ff4 main
000032f0 g     O .bss	0000000c ptarmStringBuffer
000001a8 g     F .text	00000084 ptarmLcdOutput
00002cd4 g     O .data	00000054 l3
00002c29 g     O .data	00000001 loopForever
00002c2c g     O .data	00000054 l1
0000efdc g       *ABS*	00000000 addr_stack_end
000028dc g     O .rodata	00000010 hexMap
00002d7c g     O .data	00000054 m1
0000ffe0 g       *ABS*	00000000 eoe_table
00002c28 g     O .data	00000001 halt
00000644 g     F .text	000000a8 hex
00002f74 g     O .data	00000054 n3
0000022c g     F .text	0000004c ptarmLcdInit
00002e24 g     O .data	00000054 m3
00000114 g     F .text	00000094 ptarmSevenSegChar
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
      7c:	00003058 	.word	0x00003058
      80:	000032fc 	.word	0x000032fc
      84:	000002a4 	.word	0x000002a4
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
     1a4:	000028dc 	.word	0x000028dc

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
     274:	00003058 	.word	0x00003058

00000278 <ptarmLcdOutputStr>:


// Outputs a string to the LCD display. Not a thread-safe function.
void ptarmLcdOutputStr(const char *str) {
     278:	e92d4800 	push	{fp, lr}
     27c:	e28db004 	add	fp, sp, #4, 0
     280:	e24dd008 	sub	sp, sp, #8, 0
     284:	e50b0008 	str	r0, [fp, #-8]
	while (*str != NULL) {
     288:	ea000041 	b	394 <bss_size+0xf0>
		// Check for the newline character
		if (*str == '\n') {
     28c:	e51b3008 	ldr	r3, [fp, #-8]
     290:	e5d33000 	ldrb	r3, [r3]
     294:	e353000a 	cmp	r3, #10, 0
     298:	1a00000d 	bne	2d4 <bss_size+0x30>
			ptarmLcdCharCount = (1 + (ptarmLcdCharCount > LCD_LEN)) * LCD_LEN;
     29c:	e59f310c 	ldr	r3, [pc, #268]	; 3b0 <bss_size+0x10c>
     2a0:	e5d32000 	ldrb	r2, [r3]
     2a4:	e5d33001 	ldrb	r3, [r3, #1]
     2a8:	e1823403 	orr	r3, r2, r3, lsl #8
     2ac:	e353000f 	cmp	r3, #15, 0
     2b0:	9a000001 	bls	2bc <bss_size+0x18>
     2b4:	e3a0301e 	mov	r3, #30, 0
     2b8:	ea000000 	b	2c0 <bss_size+0x1c>
     2bc:	e3a0300f 	mov	r3, #15, 0
     2c0:	e59f20e8 	ldr	r2, [pc, #232]	; 3b0 <bss_size+0x10c>
     2c4:	e5c23000 	strb	r3, [r2]
     2c8:	e1a03443 	asr	r3, r3, #8
     2cc:	e5c23001 	strb	r3, [r2, #1]
     2d0:	ea000010 	b	318 <bss_size+0x74>
		} else {
			ptarmLcdChar(*str);
     2d4:	e51b3008 	ldr	r3, [fp, #-8]
     2d8:	e5d33000 	ldrb	r3, [r3]
     2dc:	e3a02050 	mov	r2, #80, 0	; 0x50
     2e0:	e3a01b01 	mov	r1, #1024	; 0x400
     2e4:	e1a00003 	mov	r0, r3
     2e8:	ebffffae 	bl	1a8 <ptarmLcdOutput>
			ptarmLcdCharCount++;
     2ec:	e59f30bc 	ldr	r3, [pc, #188]	; 3b0 <bss_size+0x10c>
     2f0:	e5d32000 	ldrb	r2, [r3]
     2f4:	e5d33001 	ldrb	r3, [r3, #1]
     2f8:	e1823403 	orr	r3, r2, r3, lsl #8
     2fc:	e2833001 	add	r3, r3, #1, 0
     300:	e1a03803 	lsl	r3, r3, #16
     304:	e1a03823 	lsr	r3, r3, #16
     308:	e59f20a0 	ldr	r2, [pc, #160]	; 3b0 <bss_size+0x10c>
     30c:	e5c23000 	strb	r3, [r2]
     310:	e1a03443 	asr	r3, r3, #8
     314:	e5c23001 	strb	r3, [r2, #1]
		}
		str++;
     318:	e51b3008 	ldr	r3, [fp, #-8]
     31c:	e2833001 	add	r3, r3, #1, 0
     320:	e50b3008 	str	r3, [fp, #-8]
		
		if (ptarmLcdCharCount == LCD_LEN) {
     324:	e59f3084 	ldr	r3, [pc, #132]	; 3b0 <bss_size+0x10c>
     328:	e5d32000 	ldrb	r2, [r3]
     32c:	e5d33001 	ldrb	r3, [r3, #1]
     330:	e1823403 	orr	r3, r2, r3, lsl #8
     334:	e353000f 	cmp	r3, #15, 0
     338:	1a000005 	bne	354 <bss_size+0xb0>
			// Go to the second line.
			ptarmLcdGotoLineTwo();
     33c:	e3a02c65 	mov	r2, #25856	; 0x6500
     340:	e2822090 	add	r2, r2, #144, 0	; 0x90
     344:	e3a01000 	mov	r1, #0, 0
     348:	e3a000c0 	mov	r0, #192, 0	; 0xc0
     34c:	ebffff95 	bl	1a8 <ptarmLcdOutput>
     350:	ea00000f 	b	394 <bss_size+0xf0>
		} else if (ptarmLcdCharCount == (LCD_LEN * 2)) {
     354:	e59f3054 	ldr	r3, [pc, #84]	; 3b0 <bss_size+0x10c>
     358:	e5d32000 	ldrb	r2, [r3]
     35c:	e5d33001 	ldrb	r3, [r3, #1]
     360:	e1823403 	orr	r3, r2, r3, lsl #8
     364:	e353001e 	cmp	r3, #30, 0
     368:	1a000009 	bne	394 <bss_size+0xf0>
			// Go back to the first line and don't output the remaining string.
			ptarmLcdGotoLineOne();
     36c:	e3a02c65 	mov	r2, #25856	; 0x6500
     370:	e2822090 	add	r2, r2, #144, 0	; 0x90
     374:	e3a01000 	mov	r1, #0, 0
     378:	e3a00080 	mov	r0, #128, 0	; 0x80
     37c:	ebffff89 	bl	1a8 <ptarmLcdOutput>
			ptarmLcdCharCount = 0;
     380:	e59f3028 	ldr	r3, [pc, #40]	; 3b0 <bss_size+0x10c>
     384:	e3a02000 	mov	r2, #0, 0
     388:	e5c32000 	strb	r2, [r3]
     38c:	e5c32001 	strb	r2, [r3, #1]
			break;
     390:	ea000003 	b	3a4 <bss_size+0x100>
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
     3b0:	00003058 	.word	0x00003058

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
     55c:	000032f0 	.word	0x000032f0

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
     640:	000032f0 	.word	0x000032f0

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
     6e8:	000032f0 	.word	0x000032f0

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
     87c:	00002c24 	.word	0x00002c24
     880:	000032fc 	.word	0x000032fc
     884:	000028ec 	.word	0x000028ec
     888:	00002918 	.word	0x00002918
     88c:	00002930 	.word	0x00002930
     890:	0000293c 	.word	0x0000293c

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
     8e8:	e92d49f0 	push	{r4, r5, r6, r7, r8, fp, lr}
     8ec:	e28db018 	add	fp, sp, #24, 0
     8f0:	e24dd0d4 	sub	sp, sp, #212, 0	; 0xd4
	// Create a local scheduler that uses the hardware thread's stack.
	ptarmCreateLocalScheduler(localScheduler, &&localScheduler);
     8f4:	ee007d00 	cdp	13, 0, cr7, cr0, cr0, {0}
     8f8:	e1a03007 	mov	r3, r7
     8fc:	e50b305c 	str	r3, [fp, #-92]	; 0x5c
     900:	e24b3074 	sub	r3, fp, #116, 0	; 0x74
     904:	e3a02000 	mov	r2, #0, 0
     908:	e5832000 	str	r2, [r3]
     90c:	e5832004 	str	r2, [r3, #4]
     910:	e5832008 	str	r2, [r3, #8]
     914:	e583200c 	str	r2, [r3, #12]
     918:	e5832010 	str	r2, [r3, #16]
     91c:	e59f2fa4 	ldr	r2, [pc, #4004]	; 18c8 <main+0xfe0>
     920:	e24b3080 	sub	r3, fp, #128, 0	; 0x80
     924:	e8920007 	ldm	r2, {r0, r1, r2}
     928:	e8a30003 	stmia	r3!, {r0, r1}
     92c:	e5c32000 	strb	r2, [r3]
     930:	e1a01442 	asr	r1, r2, #8
     934:	e5c31001 	strb	r1, [r3, #1]
     938:	e2833002 	add	r3, r3, #2, 0
     93c:	e1a02822 	lsr	r2, r2, #16
     940:	e5c32000 	strb	r2, [r3]
     944:	e51b305c 	ldr	r3, [fp, #-92]	; 0x5c
     948:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     94c:	e2833030 	add	r3, r3, #48, 0	; 0x30
     950:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     954:	e54b3077 	strb	r3, [fp, #-119]	; 0x77
     958:	e24b30e8 	sub	r3, fp, #232, 0	; 0xe8
     95c:	e3a02068 	mov	r2, #104, 0	; 0x68
     960:	e3a01000 	mov	r1, #0, 0
     964:	e1a00003 	mov	r0, r3
     968:	eb000870 	bl	2b30 <memset>
     96c:	e24b3080 	sub	r3, fp, #128, 0	; 0x80
     970:	e50b30e8 	str	r3, [fp, #-232]	; 0xe8
     974:	e51b305c 	ldr	r3, [fp, #-92]	; 0x5c
     978:	e50b30e4 	str	r3, [fp, #-228]	; 0xe4
     97c:	e24b3074 	sub	r3, fp, #116, 0	; 0x74
     980:	e50b30cc 	str	r3, [fp, #-204]	; 0xcc
     984:	e51b3074 	ldr	r3, [fp, #-116]	; 0x74
     988:	e50b30c8 	str	r3, [fp, #-200]	; 0xc8
     98c:	e24b3074 	sub	r3, fp, #116, 0	; 0x74
     990:	e50b30c4 	str	r3, [fp, #-196]	; 0xc4
     994:	e1a0200d 	mov	r2, sp
     998:	e1a0300b 	mov	r3, fp
     99c:	e50b20dc 	str	r2, [fp, #-220]	; 0xdc
     9a0:	e50b30e0 	str	r3, [fp, #-224]	; 0xe0
     9a4:	e59f3f20 	ldr	r3, [pc, #3872]	; 18cc <main+0xfe4>
     9a8:	e50b30d8 	str	r3, [fp, #-216]	; 0xd8
	
	// Each hardware thread performs some type of start up work.
	switch (localScheduler.hwThreadId) {
     9ac:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
     9b0:	e3530003 	cmp	r3, #3, 0
     9b4:	979ff103 	ldrls	pc, [pc, r3, lsl #2]
     9b8:	ea0000f0 	b	d80 <main+0x498>
     9bc:	000009cc 	.word	0x000009cc
     9c0:	00000b1c 	.word	0x00000b1c
     9c4:	00000bf0 	.word	0x00000bf0
     9c8:	00000cb8 	.word	0x00000cb8
		case (0):;	// Hardware thread 0.

					safe_printf("ForeMC example.\n\n");
     9cc:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
     9d0:	e59f0ef8 	ldr	r0, [pc, #3832]	; 18d0 <main+0xfe8>
     9d4:	ebfffe89 	bl	400 <ptarmUartOutputStr>
     9d8:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

					// Create the non-critical tasks.
					ptarmCreateTask(&n1, &&n1, NULL);
     9dc:	e59f3ef0 	ldr	r3, [pc, #3824]	; 18d4 <main+0xfec>
     9e0:	e3a02000 	mov	r2, #0, 0
     9e4:	e1a01003 	mov	r1, r3
     9e8:	e59f0fd4 	ldr	r0, [pc, #4052]	; 19c4 <main+0x10dc>
     9ec:	ebffff3e 	bl	6ec <ptarmCreateTask>
					ptarmCreateTask(&n2, &&n2, NULL);
     9f0:	e59f3ee0 	ldr	r3, [pc, #3808]	; 18d8 <main+0xff0>
     9f4:	e3a02000 	mov	r2, #0, 0
     9f8:	e1a01003 	mov	r1, r3
     9fc:	e59f0fcc 	ldr	r0, [pc, #4044]	; 19d0 <main+0x10e8>
     a00:	ebffff39 	bl	6ec <ptarmCreateTask>
					ptarmCreateTask(&n3, &&n3, NULL);
     a04:	e59f3ed0 	ldr	r3, [pc, #3792]	; 18dc <main+0xff4>
     a08:	e3a02000 	mov	r2, #0, 0
     a0c:	e1a01003 	mov	r1, r3
     a10:	e59f0fc4 	ldr	r0, [pc, #4036]	; 19dc <main+0x10f4>
     a14:	ebffff34 	bl	6ec <ptarmCreateTask>
					ptarmCreateTask(&n4, &&n4, NULL);
     a18:	e59f3ec0 	ldr	r3, [pc, #3776]	; 18e0 <main+0xff8>
     a1c:	e3a02000 	mov	r2, #0, 0
     a20:	e1a01003 	mov	r1, r3
     a24:	e59f0fc0 	ldr	r0, [pc, #4032]	; 19ec <main+0x1104>
     a28:	ebffff2f 	bl	6ec <ptarmCreateTask>

					// Create a static schedule for hardware thread 0.
					// [m1 -> l1]
					ptarmCreateTask(&m1, &&m1, &localScheduler);
     a2c:	e24b20e8 	sub	r2, fp, #232, 0	; 0xe8
     a30:	e59f3eac 	ldr	r3, [pc, #3756]	; 18e4 <main+0xffc>
     a34:	e1a01003 	mov	r1, r3
     a38:	e59f0f48 	ldr	r0, [pc, #3912]	; 1988 <main+0x10a0>
     a3c:	ebffff2a 	bl	6ec <ptarmCreateTask>
					ptarmCreateTask(&l1, &&l1, &localScheduler);
     a40:	e24b20e8 	sub	r2, fp, #232, 0	; 0xe8
     a44:	e59f3e9c 	ldr	r3, [pc, #3740]	; 18e8 <main+0x1000>
     a48:	e1a01003 	mov	r1, r3
     a4c:	e59f0f04 	ldr	r0, [pc, #3844]	; 1958 <main+0x1070>
     a50:	ebffff25 	bl	6ec <ptarmCreateTask>
					staticSchedule[0] = &m1;
     a54:	e59f3f2c 	ldr	r3, [pc, #3884]	; 1988 <main+0x10a0>
     a58:	e50b3074 	str	r3, [fp, #-116]	; 0x74
					staticSchedule[1] = &l1;
     a5c:	e59f3ef4 	ldr	r3, [pc, #3828]	; 1958 <main+0x1070>
     a60:	e50b3070 	str	r3, [fp, #-112]	; 0x70

					// Calculate the duration of the base period that can be used to execute tasks.
					localScheduler.basePeriodStartOverhead.msb = 0;
     a64:	e3a03000 	mov	r3, #0, 0
     a68:	e50b30b0 	str	r3, [fp, #-176]	; 0xb0
					localScheduler.basePeriodStartOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
     a6c:	e3a0365f 	mov	r3, #99614720	; 0x5f00000
     a70:	e2833a5e 	add	r3, r3, #385024	; 0x5e000
     a74:	e2833c01 	add	r3, r3, #256	; 0x100
     a78:	e50b30ac 	str	r3, [fp, #-172]	; 0xac
					localScheduler.basePeriodEndOverhead.msb = 0;
     a7c:	e3a03000 	mov	r3, #0, 0
     a80:	e50b30a8 	str	r3, [fp, #-168]	; 0xa8
					localScheduler.basePeriodEndOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
     a84:	e3a0365f 	mov	r3, #99614720	; 0x5f00000
     a88:	e2833a5e 	add	r3, r3, #385024	; 0x5e000
     a8c:	e2833c01 	add	r3, r3, #256	; 0x100
     a90:	e50b30a4 	str	r3, [fp, #-164]	; 0xa4
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);
     a94:	e59f3e9c 	ldr	r3, [pc, #3740]	; 1938 <main+0x1050>
     a98:	e5933004 	ldr	r3, [r3, #4]
     a9c:	e59f2e94 	ldr	r2, [pc, #3732]	; 1938 <main+0x1050>
     aa0:	e5922008 	ldr	r2, [r2, #8]
     aa4:	e51b10a8 	ldr	r1, [fp, #-168]	; 0xa8
     aa8:	e51b00a4 	ldr	r0, [fp, #-164]	; 0xa4
     aac:	e1a07003 	mov	r7, r3
     ab0:	e1a08002 	mov	r8, r2
     ab4:	e0588000 	subs	r8, r8, r0
     ab8:	e0c77001 	sbc	r7, r7, r1
     abc:	e1a02007 	mov	r2, r7
     ac0:	e1a03008 	mov	r3, r8
     ac4:	e50b2098 	str	r2, [fp, #-152]	; 0x98
     ac8:	e50b3094 	str	r3, [fp, #-148]	; 0x94

					globalScheduler.localScheduler0 = &localScheduler;					// Set the global reference to the local scheduler.
     acc:	e59f2e64 	ldr	r2, [pc, #3684]	; 1938 <main+0x1050>
     ad0:	e24b30e8 	sub	r3, fp, #232, 0	; 0xe8
     ad4:	e5823014 	str	r3, [r2, #20]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler0);	// Register the EOE handler.
     ad8:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
     adc:	e1a03103 	lsl	r3, r3, #2
     ae0:	e59f2e04 	ldr	r2, [pc, #3588]	; 18ec <main+0x1004>
     ae4:	e0833002 	add	r3, r3, r2
     ae8:	e59f2e00 	ldr	r2, [pc, #3584]	; 18f0 <main+0x1008>
     aec:	e5832000 	str	r2, [r3]

					PTARM_TIME_GET(globalScheduler.basePeriodFirstStart);				// Save the time stamp of the first base period.
     af0:	ee870d08 	cdp	13, 8, cr0, cr7, cr8, {0}
     af4:	e1a02007 	mov	r2, r7
     af8:	e1a03008 	mov	r3, r8
     afc:	e59f1e34 	ldr	r1, [pc, #3636]	; 1938 <main+0x1050>
     b00:	e581200c 	str	r2, [r1, #12]
     b04:	e59f2e2c 	ldr	r2, [pc, #3628]	; 1938 <main+0x1050>
     b08:	e5823010 	str	r3, [r2, #16]
					globalScheduler.isInitialised = true;								// Initialisation complete.
     b0c:	e59f3e24 	ldr	r3, [pc, #3620]	; 1938 <main+0x1050>
     b10:	e3a02001 	mov	r2, #1, 0
     b14:	e5c32000 	strb	r2, [r3]
					break;
     b18:	ea0000ab 	b	dcc <main+0x4e4>

		case (1):	// Hardware thread 1.

					// Create a static schedule for hardware thread 1.
					// [m2 -> l2]
					ptarmCreateTask(&m2, &&m2, &localScheduler);
     b1c:	e24b20e8 	sub	r2, fp, #232, 0	; 0xe8
     b20:	e59f3dcc 	ldr	r3, [pc, #3532]	; 18f4 <main+0x100c>
     b24:	e1a01003 	mov	r1, r3
     b28:	e59f0e70 	ldr	r0, [pc, #3696]	; 19a0 <main+0x10b8>
     b2c:	ebfffeee 	bl	6ec <ptarmCreateTask>
					ptarmCreateTask(&l2, &&l2, &localScheduler);
     b30:	e24b20e8 	sub	r2, fp, #232, 0	; 0xe8
     b34:	e59f3dbc 	ldr	r3, [pc, #3516]	; 18f8 <main+0x1010>
     b38:	e1a01003 	mov	r1, r3
     b3c:	e59f0e20 	ldr	r0, [pc, #3616]	; 1964 <main+0x107c>
     b40:	ebfffee9 	bl	6ec <ptarmCreateTask>
					staticSchedule[0] = &m2;
     b44:	e59f3e54 	ldr	r3, [pc, #3668]	; 19a0 <main+0x10b8>
     b48:	e50b3074 	str	r3, [fp, #-116]	; 0x74
					staticSchedule[1] = &l2;
     b4c:	e59f3e10 	ldr	r3, [pc, #3600]	; 1964 <main+0x107c>
     b50:	e50b3070 	str	r3, [fp, #-112]	; 0x70
			
					// Associate tasks with receive buffers.
					m2.receiveBuffers[0] = &bufferOne;
     b54:	e59f3e44 	ldr	r3, [pc, #3652]	; 19a0 <main+0x10b8>
     b58:	e59f2e34 	ldr	r2, [pc, #3636]	; 1994 <main+0x10ac>
     b5c:	e583202c 	str	r2, [r3, #44]	; 0x2c

					// Calculate the duration of the base period that can be used to execute tasks.
					localScheduler.basePeriodStartOverhead.msb = 0;
     b60:	e3a03000 	mov	r3, #0, 0
     b64:	e50b30b0 	str	r3, [fp, #-176]	; 0xb0
					localScheduler.basePeriodStartOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
     b68:	e3a0365f 	mov	r3, #99614720	; 0x5f00000
     b6c:	e2833a5e 	add	r3, r3, #385024	; 0x5e000
     b70:	e2833c01 	add	r3, r3, #256	; 0x100
     b74:	e50b30ac 	str	r3, [fp, #-172]	; 0xac
					localScheduler.basePeriodEndOverhead.msb = 0;
     b78:	e3a03000 	mov	r3, #0, 0
     b7c:	e50b30a8 	str	r3, [fp, #-168]	; 0xa8
					localScheduler.basePeriodEndOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
     b80:	e3a0365f 	mov	r3, #99614720	; 0x5f00000
     b84:	e2833a5e 	add	r3, r3, #385024	; 0x5e000
     b88:	e2833c01 	add	r3, r3, #256	; 0x100
     b8c:	e50b30a4 	str	r3, [fp, #-164]	; 0xa4
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);
     b90:	e59f3da0 	ldr	r3, [pc, #3488]	; 1938 <main+0x1050>
     b94:	e5933004 	ldr	r3, [r3, #4]
     b98:	e59f2d98 	ldr	r2, [pc, #3480]	; 1938 <main+0x1050>
     b9c:	e5922008 	ldr	r2, [r2, #8]
     ba0:	e51b10a8 	ldr	r1, [fp, #-168]	; 0xa8
     ba4:	e51b00a4 	ldr	r0, [fp, #-164]	; 0xa4
     ba8:	e1a07003 	mov	r7, r3
     bac:	e1a08002 	mov	r8, r2
     bb0:	e0588000 	subs	r8, r8, r0
     bb4:	e0c77001 	sbc	r7, r7, r1
     bb8:	e1a02007 	mov	r2, r7
     bbc:	e1a03008 	mov	r3, r8
     bc0:	e50b2098 	str	r2, [fp, #-152]	; 0x98
     bc4:	e50b3094 	str	r3, [fp, #-148]	; 0x94

					globalScheduler.localScheduler1 = &localScheduler;					// Set the global reference to the local scheduler.
     bc8:	e59f2d68 	ldr	r2, [pc, #3432]	; 1938 <main+0x1050>
     bcc:	e24b30e8 	sub	r3, fp, #232, 0	; 0xe8
     bd0:	e5823018 	str	r3, [r2, #24]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler1);	// Register the EOE handler.
     bd4:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
     bd8:	e1a03103 	lsl	r3, r3, #2
     bdc:	e59f2d08 	ldr	r2, [pc, #3336]	; 18ec <main+0x1004>
     be0:	e0833002 	add	r3, r3, r2
     be4:	e59f2d10 	ldr	r2, [pc, #3344]	; 18fc <main+0x1014>
     be8:	e5832000 	str	r2, [r3]
					break;
     bec:	ea000076 	b	dcc <main+0x4e4>

		case (2):	// Hardware thread 2.

					ptarmCreateTask(&l3, &&l3, &localScheduler);
     bf0:	e24b20e8 	sub	r2, fp, #232, 0	; 0xe8
     bf4:	e59f3d04 	ldr	r3, [pc, #3332]	; 1900 <main+0x1018>
     bf8:	e1a01003 	mov	r1, r3
     bfc:	e59f0d6c 	ldr	r0, [pc, #3436]	; 1970 <main+0x1088>
     c00:	ebfffeb9 	bl	6ec <ptarmCreateTask>
					ptarmCreateTask(&l4, &&l4, &localScheduler);
     c04:	e24b20e8 	sub	r2, fp, #232, 0	; 0xe8
     c08:	e59f3cf4 	ldr	r3, [pc, #3316]	; 1904 <main+0x101c>
     c0c:	e1a01003 	mov	r1, r3
     c10:	e59f0d64 	ldr	r0, [pc, #3428]	; 197c <main+0x1094>
     c14:	ebfffeb4 	bl	6ec <ptarmCreateTask>
					staticSchedule[0] = &l3;
     c18:	e59f3d50 	ldr	r3, [pc, #3408]	; 1970 <main+0x1088>
     c1c:	e50b3074 	str	r3, [fp, #-116]	; 0x74
					staticSchedule[1] = &l4;
     c20:	e59f3d54 	ldr	r3, [pc, #3412]	; 197c <main+0x1094>
     c24:	e50b3070 	str	r3, [fp, #-112]	; 0x70

					localScheduler.basePeriodStartOverhead.msb = 0;
     c28:	e3a03000 	mov	r3, #0, 0
     c2c:	e50b30b0 	str	r3, [fp, #-176]	; 0xb0
					localScheduler.basePeriodStartOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
     c30:	e3a0365f 	mov	r3, #99614720	; 0x5f00000
     c34:	e2833a5e 	add	r3, r3, #385024	; 0x5e000
     c38:	e2833c01 	add	r3, r3, #256	; 0x100
     c3c:	e50b30ac 	str	r3, [fp, #-172]	; 0xac
					localScheduler.basePeriodEndOverhead.msb = 0;
     c40:	e3a03000 	mov	r3, #0, 0
     c44:	e50b30a8 	str	r3, [fp, #-168]	; 0xa8
					localScheduler.basePeriodEndOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
     c48:	e3a0365f 	mov	r3, #99614720	; 0x5f00000
     c4c:	e2833a5e 	add	r3, r3, #385024	; 0x5e000
     c50:	e2833c01 	add	r3, r3, #256	; 0x100
     c54:	e50b30a4 	str	r3, [fp, #-164]	; 0xa4
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);
     c58:	e59f3cd8 	ldr	r3, [pc, #3288]	; 1938 <main+0x1050>
     c5c:	e5933004 	ldr	r3, [r3, #4]
     c60:	e59f2cd0 	ldr	r2, [pc, #3280]	; 1938 <main+0x1050>
     c64:	e5922008 	ldr	r2, [r2, #8]
     c68:	e51b10a8 	ldr	r1, [fp, #-168]	; 0xa8
     c6c:	e51b00a4 	ldr	r0, [fp, #-164]	; 0xa4
     c70:	e1a07003 	mov	r7, r3
     c74:	e1a08002 	mov	r8, r2
     c78:	e0588000 	subs	r8, r8, r0
     c7c:	e0c77001 	sbc	r7, r7, r1
     c80:	e1a02007 	mov	r2, r7
     c84:	e1a03008 	mov	r3, r8
     c88:	e50b2098 	str	r2, [fp, #-152]	; 0x98
     c8c:	e50b3094 	str	r3, [fp, #-148]	; 0x94

					globalScheduler.localScheduler2 = &localScheduler;
     c90:	e59f2ca0 	ldr	r2, [pc, #3232]	; 1938 <main+0x1050>
     c94:	e24b30e8 	sub	r3, fp, #232, 0	; 0xe8
     c98:	e582301c 	str	r3, [r2, #28]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler2);
     c9c:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
     ca0:	e1a03103 	lsl	r3, r3, #2
     ca4:	e59f2c40 	ldr	r2, [pc, #3136]	; 18ec <main+0x1004>
     ca8:	e0833002 	add	r3, r3, r2
     cac:	e59f2c54 	ldr	r2, [pc, #3156]	; 1908 <main+0x1020>
     cb0:	e5832000 	str	r2, [r3]
					break;
     cb4:	ea000044 	b	dcc <main+0x4e4>

		case (3):	// Hardware thread 3.

					ptarmCreateTask(&m3, &&m3, &localScheduler);
     cb8:	e24b20e8 	sub	r2, fp, #232, 0	; 0xe8
     cbc:	e59f3c48 	ldr	r3, [pc, #3144]	; 190c <main+0x1024>
     cc0:	e1a01003 	mov	r1, r3
     cc4:	e59f0ce0 	ldr	r0, [pc, #3296]	; 19ac <main+0x10c4>
     cc8:	ebfffe87 	bl	6ec <ptarmCreateTask>
					ptarmCreateTask(&m4, &&m4, &localScheduler);
     ccc:	e24b20e8 	sub	r2, fp, #232, 0	; 0xe8
     cd0:	e59f3c38 	ldr	r3, [pc, #3128]	; 1910 <main+0x1028>
     cd4:	e1a01003 	mov	r1, r3
     cd8:	e59f0cd8 	ldr	r0, [pc, #3288]	; 19b8 <main+0x10d0>
     cdc:	ebfffe82 	bl	6ec <ptarmCreateTask>
					staticSchedule[0] = &m3;
     ce0:	e59f3cc4 	ldr	r3, [pc, #3268]	; 19ac <main+0x10c4>
     ce4:	e50b3074 	str	r3, [fp, #-116]	; 0x74
					staticSchedule[1] = &m4;
     ce8:	e59f3cc8 	ldr	r3, [pc, #3272]	; 19b8 <main+0x10d0>
     cec:	e50b3070 	str	r3, [fp, #-112]	; 0x70

					localScheduler.basePeriodStartOverhead.msb = 0;
     cf0:	e3a03000 	mov	r3, #0, 0
     cf4:	e50b30b0 	str	r3, [fp, #-176]	; 0xb0
					localScheduler.basePeriodStartOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
     cf8:	e3a0365f 	mov	r3, #99614720	; 0x5f00000
     cfc:	e2833a5e 	add	r3, r3, #385024	; 0x5e000
     d00:	e2833c01 	add	r3, r3, #256	; 0x100
     d04:	e50b30ac 	str	r3, [fp, #-172]	; 0xac
					localScheduler.basePeriodEndOverhead.msb = 0;
     d08:	e3a03000 	mov	r3, #0, 0
     d0c:	e50b30a8 	str	r3, [fp, #-168]	; 0xa8
					localScheduler.basePeriodEndOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
     d10:	e3a0365f 	mov	r3, #99614720	; 0x5f00000
     d14:	e2833a5e 	add	r3, r3, #385024	; 0x5e000
     d18:	e2833c01 	add	r3, r3, #256	; 0x100
     d1c:	e50b30a4 	str	r3, [fp, #-164]	; 0xa4
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);
     d20:	e59f3c10 	ldr	r3, [pc, #3088]	; 1938 <main+0x1050>
     d24:	e5933004 	ldr	r3, [r3, #4]
     d28:	e59f2c08 	ldr	r2, [pc, #3080]	; 1938 <main+0x1050>
     d2c:	e5922008 	ldr	r2, [r2, #8]
     d30:	e51b10a8 	ldr	r1, [fp, #-168]	; 0xa8
     d34:	e51b00a4 	ldr	r0, [fp, #-164]	; 0xa4
     d38:	e1a07003 	mov	r7, r3
     d3c:	e1a08002 	mov	r8, r2
     d40:	e0588000 	subs	r8, r8, r0
     d44:	e0c77001 	sbc	r7, r7, r1
     d48:	e1a02007 	mov	r2, r7
     d4c:	e1a03008 	mov	r3, r8
     d50:	e50b2098 	str	r2, [fp, #-152]	; 0x98
     d54:	e50b3094 	str	r3, [fp, #-148]	; 0x94

					globalScheduler.localScheduler3 = &localScheduler;
     d58:	e59f2bd8 	ldr	r2, [pc, #3032]	; 1938 <main+0x1050>
     d5c:	e24b30e8 	sub	r3, fp, #232, 0	; 0xe8
     d60:	e5823020 	str	r3, [r2, #32]
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler3);
     d64:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
     d68:	e1a03103 	lsl	r3, r3, #2
     d6c:	e59f2b78 	ldr	r2, [pc, #2936]	; 18ec <main+0x1004>
     d70:	e0833002 	add	r3, r3, r2
     d74:	e59f2b98 	ldr	r2, [pc, #2968]	; 1914 <main+0x102c>
     d78:	e5832000 	str	r2, [r3]
					break;
     d7c:	ea000012 	b	dcc <main+0x4e4>

		default:	// Unknown hardware thread ID.

					PTARM_MUTEX_LOCK();
     d80:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
					printf("!! Initialisation error: Unknown hwThreadId = "); printf(utoa(localScheduler.hwThreadId)); printf("\n");
     d84:	e59f0b8c 	ldr	r0, [pc, #2956]	; 1918 <main+0x1030>
     d88:	ebfffd9c 	bl	400 <ptarmUartOutputStr>
     d8c:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
     d90:	e1a00003 	mov	r0, r3
     d94:	ebfffdf1 	bl	560 <utoa>
     d98:	e1a03000 	mov	r3, r0
     d9c:	e1a00003 	mov	r0, r3
     da0:	ebfffd96 	bl	400 <ptarmUartOutputStr>
     da4:	e59f0be4 	ldr	r0, [pc, #3044]	; 1990 <main+0x10a8>
     da8:	ebfffd94 	bl	400 <ptarmUartOutputStr>
					PTARM_MUTEX_UNLOCK();
     dac:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
					while (halt);
     db0:	e1a00000 	nop			; (mov r0, r0)
     db4:	e59f3b90 	ldr	r3, [pc, #2960]	; 194c <main+0x1064>
     db8:	e5d33000 	ldrb	r3, [r3]
     dbc:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     dc0:	e3530000 	cmp	r3, #0, 0
     dc4:	1afffffa 	bne	db4 <main+0x4cc>
					break;
     dc8:	e1a00000 	nop			; (mov r0, r0)
	}

	// All hardware threads execute this.
	while(globalScheduler.isInitialised == false);
     dcc:	e1a00000 	nop			; (mov r0, r0)
     dd0:	e59f3b60 	ldr	r3, [pc, #2912]	; 1938 <main+0x1050>
     dd4:	e5d33000 	ldrb	r3, [r3]
     dd8:	e20330ff 	and	r3, r3, #255, 0	; 0xff
     ddc:	e3530000 	cmp	r3, #0, 0
     de0:	0afffffa 	beq	dd0 <main+0x4e8>
	localScheduler.basePeriodStart = globalScheduler.basePeriodFirstStart;
     de4:	e59f2b4c 	ldr	r2, [pc, #2892]	; 1938 <main+0x1050>
     de8:	e24b30bc 	sub	r3, fp, #188, 0	; 0xbc
     dec:	e282200c 	add	r2, r2, #12, 0
     df0:	e8920003 	ldm	r2, {r0, r1}
     df4:	e8830003 	stm	r3, {r0, r1}
	PTARM_GOTO(localScheduler);
     df8:	ea000100 	b	1200 <main+0x918>


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
     dfc:	e1a00000 	nop			; (mov r0, r0)
     e00:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     e04:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     e08:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     e0c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     e10:	e59f3b20 	ldr	r3, [pc, #2848]	; 1938 <main+0x1050>
     e14:	e5933014 	ldr	r3, [r3, #20]
     e18:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     e1c:	e58d7038 	str	r7, [sp, #56]	; 0x38
     e20:	e1a0200d 	mov	r2, sp
     e24:	e5832014 	str	r2, [r3, #20]
     e28:	e59f3b08 	ldr	r3, [pc, #2824]	; 1938 <main+0x1050>
     e2c:	e5933014 	ldr	r3, [r3, #20]
     e30:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     e34:	e1a02007 	mov	r2, r7
     e38:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler0);
     e3c:	e59f3af4 	ldr	r3, [pc, #2804]	; 1938 <main+0x1050>
     e40:	e5933014 	ldr	r3, [r3, #20]
     e44:	e593300c 	ldr	r3, [r3, #12]
     e48:	e59f2ae8 	ldr	r2, [pc, #2792]	; 1938 <main+0x1050>
     e4c:	e5922014 	ldr	r2, [r2, #20]
     e50:	e5922008 	ldr	r2, [r2, #8]
     e54:	e1a0d003 	mov	sp, r3
     e58:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     e5c:	ea00004a 	b	f8c <main+0x6a4>
}

// For hardware thread 1.
eoeHandler1: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler1);
     e60:	e1a00000 	nop			; (mov r0, r0)
     e64:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     e68:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     e6c:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     e70:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     e74:	e59f3abc 	ldr	r3, [pc, #2748]	; 1938 <main+0x1050>
     e78:	e5933018 	ldr	r3, [r3, #24]
     e7c:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     e80:	e58d7038 	str	r7, [sp, #56]	; 0x38
     e84:	e1a0200d 	mov	r2, sp
     e88:	e5832014 	str	r2, [r3, #20]
     e8c:	e59f3aa4 	ldr	r3, [pc, #2724]	; 1938 <main+0x1050>
     e90:	e5933018 	ldr	r3, [r3, #24]
     e94:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     e98:	e1a02007 	mov	r2, r7
     e9c:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler1);
     ea0:	e59f3a90 	ldr	r3, [pc, #2704]	; 1938 <main+0x1050>
     ea4:	e5933018 	ldr	r3, [r3, #24]
     ea8:	e593300c 	ldr	r3, [r3, #12]
     eac:	e59f2a84 	ldr	r2, [pc, #2692]	; 1938 <main+0x1050>
     eb0:	e5922018 	ldr	r2, [r2, #24]
     eb4:	e5922008 	ldr	r2, [r2, #8]
     eb8:	e1a0d003 	mov	sp, r3
     ebc:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     ec0:	ea000031 	b	f8c <main+0x6a4>
}

// For hardware thread 2.
eoeHandler2: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler2);
     ec4:	e1a00000 	nop			; (mov r0, r0)
     ec8:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     ecc:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     ed0:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     ed4:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     ed8:	e59f3a58 	ldr	r3, [pc, #2648]	; 1938 <main+0x1050>
     edc:	e593301c 	ldr	r3, [r3, #28]
     ee0:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     ee4:	e58d7038 	str	r7, [sp, #56]	; 0x38
     ee8:	e1a0200d 	mov	r2, sp
     eec:	e5832014 	str	r2, [r3, #20]
     ef0:	e59f3a40 	ldr	r3, [pc, #2624]	; 1938 <main+0x1050>
     ef4:	e593301c 	ldr	r3, [r3, #28]
     ef8:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     efc:	e1a02007 	mov	r2, r7
     f00:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler2);
     f04:	e59f3a2c 	ldr	r3, [pc, #2604]	; 1938 <main+0x1050>
     f08:	e593301c 	ldr	r3, [r3, #28]
     f0c:	e593300c 	ldr	r3, [r3, #12]
     f10:	e59f2a20 	ldr	r2, [pc, #2592]	; 1938 <main+0x1050>
     f14:	e592201c 	ldr	r2, [r2, #28]
     f18:	e5922008 	ldr	r2, [r2, #8]
     f1c:	e1a0d003 	mov	sp, r3
     f20:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     f24:	ea000018 	b	f8c <main+0x6a4>
}

// For hardware thread 3.
eoeHandler3: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler3);
     f28:	e1a00000 	nop			; (mov r0, r0)
     f2c:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
     f30:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
     f34:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     f38:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
     f3c:	e59f39f4 	ldr	r3, [pc, #2548]	; 1938 <main+0x1050>
     f40:	e5933020 	ldr	r3, [r3, #32]
     f44:	ee907d00 	cdp	13, 9, cr7, cr0, cr0, {0}
     f48:	e58d7038 	str	r7, [sp, #56]	; 0x38
     f4c:	e1a0200d 	mov	r2, sp
     f50:	e5832014 	str	r2, [r3, #20]
     f54:	e59f39dc 	ldr	r3, [pc, #2524]	; 1938 <main+0x1050>
     f58:	e5933020 	ldr	r3, [r3, #32]
     f5c:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
     f60:	e1a02007 	mov	r2, r7
     f64:	e5832018 	str	r2, [r3, #24]
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler3);
     f68:	e59f39c8 	ldr	r3, [pc, #2504]	; 1938 <main+0x1050>
     f6c:	e5933020 	ldr	r3, [r3, #32]
     f70:	e593300c 	ldr	r3, [r3, #12]
     f74:	e59f29bc 	ldr	r2, [pc, #2492]	; 1938 <main+0x1050>
     f78:	e5922020 	ldr	r2, [r2, #32]
     f7c:	e5922008 	ldr	r2, [r2, #8]
     f80:	e1a0d003 	mov	sp, r3
     f84:	e1a0b002 	mov	fp, r2
	PTARM_GOTO(eoeHandler);
     f88:	eaffffff 	b	f8c <main+0x6a4>
}

eoeHandler: {
	// Assign the saved context to the preempted task.
	if (localScheduler.currentTask != NULL) {
     f8c:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
     f90:	e3530000 	cmp	r3, #0, 0
     f94:	0a00001b 	beq	1008 <main+0x720>
	
		// "Preempted xxx."
		PTARM_MUTEX_LOCK();
     f98:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Preempted "); printf(localScheduler.currentTask->name); printf(".\n");
     f9c:	e59f0a3c 	ldr	r0, [pc, #2620]	; 19e0 <main+0x10f8>
     fa0:	ebfffd16 	bl	400 <ptarmUartOutputStr>
     fa4:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
     fa8:	e1a00003 	mov	r0, r3
     fac:	ebfffd26 	bl	44c <itoa>
     fb0:	e1a03000 	mov	r3, r0
     fb4:	e1a00003 	mov	r0, r3
     fb8:	ebfffd10 	bl	400 <ptarmUartOutputStr>
     fbc:	e59f0958 	ldr	r0, [pc, #2392]	; 191c <main+0x1034>
     fc0:	ebfffd0e 	bl	400 <ptarmUartOutputStr>
     fc4:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
     fc8:	e5933000 	ldr	r3, [r3]
     fcc:	e1a00003 	mov	r0, r3
     fd0:	ebfffd0a 	bl	400 <ptarmUartOutputStr>
     fd4:	e59f096c 	ldr	r0, [pc, #2412]	; 1948 <main+0x1060>
     fd8:	ebfffd08 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
     fdc:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		
		PTARM_EOE_TASK_ASSIGN_CONTEXT(localScheduler);
     fe0:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
     fe4:	e3a02001 	mov	r2, #1, 0
     fe8:	e5c3200c 	strb	r2, [r3, #12]
     fec:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
     ff0:	e51b20d4 	ldr	r2, [fp, #-212]	; 0xd4
     ff4:	e5832010 	str	r2, [r3, #16]
     ff8:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
     ffc:	e51b20d0 	ldr	r2, [fp, #-208]	; 0xd0
    1000:	e5832014 	str	r2, [r3, #20]
    1004:	ea000010 	b	104c <main+0x764>
	} else {
		// A null task is only possible when the scheduler is preempted during the
		// dynamic scheduling phase.
	
		// "Preempted scheduler x."
		PTARM_MUTEX_LOCK();
    1008:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Preempted "); printf(localScheduler.name); printf(".\n");
    100c:	e59f09cc 	ldr	r0, [pc, #2508]	; 19e0 <main+0x10f8>
    1010:	ebfffcfa 	bl	400 <ptarmUartOutputStr>
    1014:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
    1018:	e1a00003 	mov	r0, r3
    101c:	ebfffd0a 	bl	44c <itoa>
    1020:	e1a03000 	mov	r3, r0
    1024:	e1a00003 	mov	r0, r3
    1028:	ebfffcf4 	bl	400 <ptarmUartOutputStr>
    102c:	e59f08e8 	ldr	r0, [pc, #2280]	; 191c <main+0x1034>
    1030:	ebfffcf2 	bl	400 <ptarmUartOutputStr>
    1034:	e51b30e8 	ldr	r3, [fp, #-232]	; 0xe8
    1038:	e1a00003 	mov	r0, r3
    103c:	ebfffcef 	bl	400 <ptarmUartOutputStr>
    1040:	e59f0900 	ldr	r0, [pc, #2304]	; 1948 <main+0x1060>
    1044:	ebfffced 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    1048:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
	}

	// If the preemption occured during the dynamic scheduling phase, then we know
	// that the base period has ended.
	if (localScheduler.phase == PTARM_SCHEDULER_DYNAMIC) {
    104c:	e55b30c0 	ldrb	r3, [fp, #-192]	; 0xc0
    1050:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1054:	e3530002 	cmp	r3, #2, 0
    1058:	1a000030 	bne	1120 <main+0x838>
		// Prepare to resume the static scheduling phase.

		// Return back to the static scheduling phase.
		localScheduler.phase = PTARM_SCHEDULER_RELEASE;
    105c:	e3a03000 	mov	r3, #0, 0
    1060:	e54b30c0 	strb	r3, [fp, #-192]	; 0xc0

		if (localScheduler.hwThreadId == 0) {
    1064:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
    1068:	e3530000 	cmp	r3, #0, 0
    106c:	1a000014 	bne	10c4 <main+0x7dc>
		
			// Reset the dynamic scheduling lists.
			PTARM_SCHEDULER_DYNAMIC_LIST_RESET(globalScheduler);
    1070:	e59f38c0 	ldr	r3, [pc, #2240]	; 1938 <main+0x1050>
    1074:	e3e02000 	mvn	r2, #0, 0
    1078:	e5832030 	str	r2, [r3, #48]	; 0x30
    107c:	e59f38b4 	ldr	r3, [pc, #2228]	; 1938 <main+0x1050>
    1080:	e3e02000 	mvn	r2, #0, 0
    1084:	e5832034 	str	r2, [r3, #52]	; 0x34
    1088:	e59f38a8 	ldr	r3, [pc, #2216]	; 1938 <main+0x1050>
    108c:	e3e02000 	mvn	r2, #0, 0
    1090:	e5832038 	str	r2, [r3, #56]	; 0x38

			// "Base period xxx ended."
			PTARM_MUTEX_LOCK();
    1094:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
			printf("Base period "); printf(utoa(localScheduler.basePeriodCounter)); printf(" ended.\n");
    1098:	e59f0880 	ldr	r0, [pc, #2176]	; 1920 <main+0x1038>
    109c:	ebfffcd7 	bl	400 <ptarmUartOutputStr>
    10a0:	e51b30b4 	ldr	r3, [fp, #-180]	; 0xb4
    10a4:	e1a00003 	mov	r0, r3
    10a8:	ebfffd2c 	bl	560 <utoa>
    10ac:	e1a03000 	mov	r3, r0
    10b0:	e1a00003 	mov	r0, r3
    10b4:	ebfffcd1 	bl	400 <ptarmUartOutputStr>
    10b8:	e59f0864 	ldr	r0, [pc, #2148]	; 1924 <main+0x103c>
    10bc:	ebfffccf 	bl	400 <ptarmUartOutputStr>
			PTARM_MUTEX_UNLOCK();
    10c0:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		}

		// Update the timestamp of the start of the next base period.
		localScheduler.basePeriodCounter++;
    10c4:	e51b30b4 	ldr	r3, [fp, #-180]	; 0xb4
    10c8:	e2833001 	add	r3, r3, #1, 0
    10cc:	e50b30b4 	str	r3, [fp, #-180]	; 0xb4
		PTARM_ADD(localScheduler.basePeriodStart, localScheduler.basePeriodStart, globalScheduler.basePeriodDuration);
    10d0:	e51b30bc 	ldr	r3, [fp, #-188]	; 0xbc
    10d4:	e51b20b8 	ldr	r2, [fp, #-184]	; 0xb8
    10d8:	e59f1858 	ldr	r1, [pc, #2136]	; 1938 <main+0x1050>
    10dc:	e5911004 	ldr	r1, [r1, #4]
    10e0:	e59f0850 	ldr	r0, [pc, #2128]	; 1938 <main+0x1050>
    10e4:	e5900008 	ldr	r0, [r0, #8]
    10e8:	e1a07003 	mov	r7, r3
    10ec:	e1a08002 	mov	r8, r2
    10f0:	e0988000 	adds	r8, r8, r0
    10f4:	e0a77001 	adc	r7, r7, r1
    10f8:	e1a02007 	mov	r2, r7
    10fc:	e1a03008 	mov	r3, r8
    1100:	e50b20bc 	str	r2, [fp, #-188]	; 0xbc
    1104:	e50b30b8 	str	r3, [fp, #-184]	; 0xb8

		// Wait until the next base period starts. This synchronises the start of the base period with other hardware threads to minimise jitter.
		PTARM_DELAY(localScheduler.basePeriodStart);
    1108:	e51b30bc 	ldr	r3, [fp, #-188]	; 0xbc
    110c:	e51b20b8 	ldr	r2, [fp, #-184]	; 0xb8
    1110:	e1a07003 	mov	r7, r3
    1114:	e1a08002 	mov	r8, r2
    1118:	ee470d08 	cdp	13, 4, cr0, cr7, cr8, {0}
    111c:	ea000036 	b	11fc <main+0x914>
	} else {
	
		// Insert the task to the dynamic scheduling list.
		PTARM_MUTEX_LOCK();
    1120:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		// "Queuing xxx."
		printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Queuing "); printf(localScheduler.currentTask->name); printf(".\n");
    1124:	e59f08b4 	ldr	r0, [pc, #2228]	; 19e0 <main+0x10f8>
    1128:	ebfffcb4 	bl	400 <ptarmUartOutputStr>
    112c:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
    1130:	e1a00003 	mov	r0, r3
    1134:	ebfffcc4 	bl	44c <itoa>
    1138:	e1a03000 	mov	r3, r0
    113c:	e1a00003 	mov	r0, r3
    1140:	ebfffcae 	bl	400 <ptarmUartOutputStr>
    1144:	e59f07dc 	ldr	r0, [pc, #2012]	; 1928 <main+0x1040>
    1148:	ebfffcac 	bl	400 <ptarmUartOutputStr>
    114c:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    1150:	e5933000 	ldr	r3, [r3]
    1154:	e1a00003 	mov	r0, r3
    1158:	ebfffca8 	bl	400 <ptarmUartOutputStr>
    115c:	e59f07e4 	ldr	r0, [pc, #2020]	; 1948 <main+0x1060>
    1160:	ebfffca6 	bl	400 <ptarmUartOutputStr>
		PTARM_SCHEDULER_DYNAMIC_LIST_PUSH_LIFE_MISSION(globalScheduler, localScheduler.currentTask);
    1164:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    1168:	e5d33004 	ldrb	r3, [r3, #4]
    116c:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1170:	e3530000 	cmp	r3, #0, 0
    1174:	1a00000d 	bne	11b0 <main+0x8c8>
    1178:	e59f37b8 	ldr	r3, [pc, #1976]	; 1938 <main+0x1050>
    117c:	e5933038 	ldr	r3, [r3, #56]	; 0x38
    1180:	e2833001 	add	r3, r3, #1, 0
    1184:	e59f27ac 	ldr	r2, [pc, #1964]	; 1938 <main+0x1050>
    1188:	e5823038 	str	r3, [r2, #56]	; 0x38
    118c:	e59f37a4 	ldr	r3, [pc, #1956]	; 1938 <main+0x1050>
    1190:	e593202c 	ldr	r2, [r3, #44]	; 0x2c
    1194:	e59f379c 	ldr	r3, [pc, #1948]	; 1938 <main+0x1050>
    1198:	e5933038 	ldr	r3, [r3, #56]	; 0x38
    119c:	e1a03103 	lsl	r3, r3, #2
    11a0:	e0823003 	add	r3, r2, r3
    11a4:	e51b20c8 	ldr	r2, [fp, #-200]	; 0xc8
    11a8:	e5832000 	str	r2, [r3]
    11ac:	ea000011 	b	11f8 <main+0x910>
    11b0:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    11b4:	e5d33004 	ldrb	r3, [r3, #4]
    11b8:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    11bc:	e3530001 	cmp	r3, #1, 0
    11c0:	1a00000c 	bne	11f8 <main+0x910>
    11c4:	e59f376c 	ldr	r3, [pc, #1900]	; 1938 <main+0x1050>
    11c8:	e5933034 	ldr	r3, [r3, #52]	; 0x34
    11cc:	e2833001 	add	r3, r3, #1, 0
    11d0:	e59f2760 	ldr	r2, [pc, #1888]	; 1938 <main+0x1050>
    11d4:	e5823034 	str	r3, [r2, #52]	; 0x34
    11d8:	e59f3758 	ldr	r3, [pc, #1880]	; 1938 <main+0x1050>
    11dc:	e5932028 	ldr	r2, [r3, #40]	; 0x28
    11e0:	e59f3750 	ldr	r3, [pc, #1872]	; 1938 <main+0x1050>
    11e4:	e5933034 	ldr	r3, [r3, #52]	; 0x34
    11e8:	e1a03103 	lsl	r3, r3, #2
    11ec:	e0823003 	add	r3, r2, r3
    11f0:	e51b20c8 	ldr	r2, [fp, #-200]	; 0xc8
    11f4:	e5832000 	str	r2, [r3]
		PTARM_MUTEX_UNLOCK();
    11f8:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
	}

	PTARM_GOTO(localScheduler);
    11fc:	eaffffff 	b	1200 <main+0x918>
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
    1200:	e55b30c0 	ldrb	r3, [fp, #-192]	; 0xc0
    1204:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1208:	e3530001 	cmp	r3, #1, 0
    120c:	0a00016a 	beq	17bc <main+0xed4>
    1210:	e3530002 	cmp	r3, #2, 0
    1214:	0a000204 	beq	1a2c <main+0x1144>
    1218:	e3530000 	cmp	r3, #0, 0
    121c:	1a000287 	bne	1c40 <main+0x1358>
	
		case (PTARM_SCHEDULER_RELEASE):
		
			if (localScheduler.hwThreadId == 0) {
    1220:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
    1224:	e3530000 	cmp	r3, #0, 0
    1228:	1a0000d3 	bne	157c <main+0xc94>
				// Go through the non-critical tasks and release eligible tasks.
				PTARM_SCHEDULER_DYNAMIC_LIST_RELEASE_NON_CRITICAL(globalScheduler, localScheduler, &n1);
    122c:	e59f3790 	ldr	r3, [pc, #1936]	; 19c4 <main+0x10dc>
    1230:	e5d3300c 	ldrb	r3, [r3, #12]
    1234:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1238:	e3530000 	cmp	r3, #0, 0
    123c:	1a00002f 	bne	1300 <main+0xa18>
    1240:	e59f377c 	ldr	r3, [pc, #1916]	; 19c4 <main+0x10dc>
    1244:	e5932028 	ldr	r2, [r3, #40]	; 0x28
    1248:	e51b30b4 	ldr	r3, [fp, #-180]	; 0xb4
    124c:	e1520003 	cmp	r2, r3
    1250:	8a00002a 	bhi	1300 <main+0xa18>
    1254:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
    1258:	e59f0780 	ldr	r0, [pc, #1920]	; 19e0 <main+0x10f8>
    125c:	ebfffc67 	bl	400 <ptarmUartOutputStr>
    1260:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
    1264:	e1a00003 	mov	r0, r3
    1268:	ebfffc77 	bl	44c <itoa>
    126c:	e1a03000 	mov	r3, r0
    1270:	e1a00003 	mov	r0, r3
    1274:	ebfffc61 	bl	400 <ptarmUartOutputStr>
    1278:	e59f06ac 	ldr	r0, [pc, #1708]	; 192c <main+0x1044>
    127c:	ebfffc5f 	bl	400 <ptarmUartOutputStr>
    1280:	e59f373c 	ldr	r3, [pc, #1852]	; 19c4 <main+0x10dc>
    1284:	e5933000 	ldr	r3, [r3]
    1288:	e1a00003 	mov	r0, r3
    128c:	ebfffc5b 	bl	400 <ptarmUartOutputStr>
    1290:	e59f06b0 	ldr	r0, [pc, #1712]	; 1948 <main+0x1060>
    1294:	ebfffc59 	bl	400 <ptarmUartOutputStr>
    1298:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
    129c:	e59f3720 	ldr	r3, [pc, #1824]	; 19c4 <main+0x10dc>
    12a0:	e3a02002 	mov	r2, #2, 0
    12a4:	e5c3200c 	strb	r2, [r3, #12]
    12a8:	e51b30b4 	ldr	r3, [fp, #-180]	; 0xb4
    12ac:	e59f2710 	ldr	r2, [pc, #1808]	; 19c4 <main+0x10dc>
    12b0:	e5823024 	str	r3, [r2, #36]	; 0x24
    12b4:	e51b20b4 	ldr	r2, [fp, #-180]	; 0xb4
    12b8:	e59f3704 	ldr	r3, [pc, #1796]	; 19c4 <main+0x10dc>
    12bc:	e5933020 	ldr	r3, [r3, #32]
    12c0:	e0823003 	add	r3, r2, r3
    12c4:	e59f26f8 	ldr	r2, [pc, #1784]	; 19c4 <main+0x10dc>
    12c8:	e5823028 	str	r3, [r2, #40]	; 0x28
    12cc:	e59f3664 	ldr	r3, [pc, #1636]	; 1938 <main+0x1050>
    12d0:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    12d4:	e2833001 	add	r3, r3, #1, 0
    12d8:	e59f2658 	ldr	r2, [pc, #1624]	; 1938 <main+0x1050>
    12dc:	e5823030 	str	r3, [r2, #48]	; 0x30
    12e0:	e59f3650 	ldr	r3, [pc, #1616]	; 1938 <main+0x1050>
    12e4:	e5932024 	ldr	r2, [r3, #36]	; 0x24
    12e8:	e59f3648 	ldr	r3, [pc, #1608]	; 1938 <main+0x1050>
    12ec:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    12f0:	e1a03103 	lsl	r3, r3, #2
    12f4:	e0823003 	add	r3, r2, r3
    12f8:	e59f26c4 	ldr	r2, [pc, #1732]	; 19c4 <main+0x10dc>
    12fc:	e5832000 	str	r2, [r3]
				PTARM_SCHEDULER_DYNAMIC_LIST_RELEASE_NON_CRITICAL(globalScheduler, localScheduler, &n2);
    1300:	e59f36c8 	ldr	r3, [pc, #1736]	; 19d0 <main+0x10e8>
    1304:	e5d3300c 	ldrb	r3, [r3, #12]
    1308:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    130c:	e3530000 	cmp	r3, #0, 0
    1310:	1a00002f 	bne	13d4 <main+0xaec>
    1314:	e59f36b4 	ldr	r3, [pc, #1716]	; 19d0 <main+0x10e8>
    1318:	e5932028 	ldr	r2, [r3, #40]	; 0x28
    131c:	e51b30b4 	ldr	r3, [fp, #-180]	; 0xb4
    1320:	e1520003 	cmp	r2, r3
    1324:	8a00002a 	bhi	13d4 <main+0xaec>
    1328:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
    132c:	e59f06ac 	ldr	r0, [pc, #1708]	; 19e0 <main+0x10f8>
    1330:	ebfffc32 	bl	400 <ptarmUartOutputStr>
    1334:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
    1338:	e1a00003 	mov	r0, r3
    133c:	ebfffc42 	bl	44c <itoa>
    1340:	e1a03000 	mov	r3, r0
    1344:	e1a00003 	mov	r0, r3
    1348:	ebfffc2c 	bl	400 <ptarmUartOutputStr>
    134c:	e59f05d8 	ldr	r0, [pc, #1496]	; 192c <main+0x1044>
    1350:	ebfffc2a 	bl	400 <ptarmUartOutputStr>
    1354:	e59f3674 	ldr	r3, [pc, #1652]	; 19d0 <main+0x10e8>
    1358:	e5933000 	ldr	r3, [r3]
    135c:	e1a00003 	mov	r0, r3
    1360:	ebfffc26 	bl	400 <ptarmUartOutputStr>
    1364:	e59f05dc 	ldr	r0, [pc, #1500]	; 1948 <main+0x1060>
    1368:	ebfffc24 	bl	400 <ptarmUartOutputStr>
    136c:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
    1370:	e59f3658 	ldr	r3, [pc, #1624]	; 19d0 <main+0x10e8>
    1374:	e3a02002 	mov	r2, #2, 0
    1378:	e5c3200c 	strb	r2, [r3, #12]
    137c:	e51b30b4 	ldr	r3, [fp, #-180]	; 0xb4
    1380:	e59f2648 	ldr	r2, [pc, #1608]	; 19d0 <main+0x10e8>
    1384:	e5823024 	str	r3, [r2, #36]	; 0x24
    1388:	e51b20b4 	ldr	r2, [fp, #-180]	; 0xb4
    138c:	e59f363c 	ldr	r3, [pc, #1596]	; 19d0 <main+0x10e8>
    1390:	e5933020 	ldr	r3, [r3, #32]
    1394:	e0823003 	add	r3, r2, r3
    1398:	e59f2630 	ldr	r2, [pc, #1584]	; 19d0 <main+0x10e8>
    139c:	e5823028 	str	r3, [r2, #40]	; 0x28
    13a0:	e59f3590 	ldr	r3, [pc, #1424]	; 1938 <main+0x1050>
    13a4:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    13a8:	e2833001 	add	r3, r3, #1, 0
    13ac:	e59f2584 	ldr	r2, [pc, #1412]	; 1938 <main+0x1050>
    13b0:	e5823030 	str	r3, [r2, #48]	; 0x30
    13b4:	e59f357c 	ldr	r3, [pc, #1404]	; 1938 <main+0x1050>
    13b8:	e5932024 	ldr	r2, [r3, #36]	; 0x24
    13bc:	e59f3574 	ldr	r3, [pc, #1396]	; 1938 <main+0x1050>
    13c0:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    13c4:	e1a03103 	lsl	r3, r3, #2
    13c8:	e0823003 	add	r3, r2, r3
    13cc:	e59f25fc 	ldr	r2, [pc, #1532]	; 19d0 <main+0x10e8>
    13d0:	e5832000 	str	r2, [r3]
				PTARM_SCHEDULER_DYNAMIC_LIST_RELEASE_NON_CRITICAL(globalScheduler, localScheduler, &n3);
    13d4:	e59f3600 	ldr	r3, [pc, #1536]	; 19dc <main+0x10f4>
    13d8:	e5d3300c 	ldrb	r3, [r3, #12]
    13dc:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    13e0:	e3530000 	cmp	r3, #0, 0
    13e4:	1a00002f 	bne	14a8 <main+0xbc0>
    13e8:	e59f35ec 	ldr	r3, [pc, #1516]	; 19dc <main+0x10f4>
    13ec:	e5932028 	ldr	r2, [r3, #40]	; 0x28
    13f0:	e51b30b4 	ldr	r3, [fp, #-180]	; 0xb4
    13f4:	e1520003 	cmp	r2, r3
    13f8:	8a00002a 	bhi	14a8 <main+0xbc0>
    13fc:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
    1400:	e59f05d8 	ldr	r0, [pc, #1496]	; 19e0 <main+0x10f8>
    1404:	ebfffbfd 	bl	400 <ptarmUartOutputStr>
    1408:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
    140c:	e1a00003 	mov	r0, r3
    1410:	ebfffc0d 	bl	44c <itoa>
    1414:	e1a03000 	mov	r3, r0
    1418:	e1a00003 	mov	r0, r3
    141c:	ebfffbf7 	bl	400 <ptarmUartOutputStr>
    1420:	e59f0504 	ldr	r0, [pc, #1284]	; 192c <main+0x1044>
    1424:	ebfffbf5 	bl	400 <ptarmUartOutputStr>
    1428:	e59f35ac 	ldr	r3, [pc, #1452]	; 19dc <main+0x10f4>
    142c:	e5933000 	ldr	r3, [r3]
    1430:	e1a00003 	mov	r0, r3
    1434:	ebfffbf1 	bl	400 <ptarmUartOutputStr>
    1438:	e59f0508 	ldr	r0, [pc, #1288]	; 1948 <main+0x1060>
    143c:	ebfffbef 	bl	400 <ptarmUartOutputStr>
    1440:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
    1444:	e59f3590 	ldr	r3, [pc, #1424]	; 19dc <main+0x10f4>
    1448:	e3a02002 	mov	r2, #2, 0
    144c:	e5c3200c 	strb	r2, [r3, #12]
    1450:	e51b30b4 	ldr	r3, [fp, #-180]	; 0xb4
    1454:	e59f2580 	ldr	r2, [pc, #1408]	; 19dc <main+0x10f4>
    1458:	e5823024 	str	r3, [r2, #36]	; 0x24
    145c:	e51b20b4 	ldr	r2, [fp, #-180]	; 0xb4
    1460:	e59f3574 	ldr	r3, [pc, #1396]	; 19dc <main+0x10f4>
    1464:	e5933020 	ldr	r3, [r3, #32]
    1468:	e0823003 	add	r3, r2, r3
    146c:	e59f2568 	ldr	r2, [pc, #1384]	; 19dc <main+0x10f4>
    1470:	e5823028 	str	r3, [r2, #40]	; 0x28
    1474:	e59f34bc 	ldr	r3, [pc, #1212]	; 1938 <main+0x1050>
    1478:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    147c:	e2833001 	add	r3, r3, #1, 0
    1480:	e59f24b0 	ldr	r2, [pc, #1200]	; 1938 <main+0x1050>
    1484:	e5823030 	str	r3, [r2, #48]	; 0x30
    1488:	e59f34a8 	ldr	r3, [pc, #1192]	; 1938 <main+0x1050>
    148c:	e5932024 	ldr	r2, [r3, #36]	; 0x24
    1490:	e59f34a0 	ldr	r3, [pc, #1184]	; 1938 <main+0x1050>
    1494:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    1498:	e1a03103 	lsl	r3, r3, #2
    149c:	e0823003 	add	r3, r2, r3
    14a0:	e59f2534 	ldr	r2, [pc, #1332]	; 19dc <main+0x10f4>
    14a4:	e5832000 	str	r2, [r3]
				PTARM_SCHEDULER_DYNAMIC_LIST_RELEASE_NON_CRITICAL(globalScheduler, localScheduler, &n4);
    14a8:	e59f353c 	ldr	r3, [pc, #1340]	; 19ec <main+0x1104>
    14ac:	e5d3300c 	ldrb	r3, [r3, #12]
    14b0:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    14b4:	e3530000 	cmp	r3, #0, 0
    14b8:	1a00002f 	bne	157c <main+0xc94>
    14bc:	e59f3528 	ldr	r3, [pc, #1320]	; 19ec <main+0x1104>
    14c0:	e5932028 	ldr	r2, [r3, #40]	; 0x28
    14c4:	e51b30b4 	ldr	r3, [fp, #-180]	; 0xb4
    14c8:	e1520003 	cmp	r2, r3
    14cc:	8a00002a 	bhi	157c <main+0xc94>
    14d0:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
    14d4:	e59f0504 	ldr	r0, [pc, #1284]	; 19e0 <main+0x10f8>
    14d8:	ebfffbc8 	bl	400 <ptarmUartOutputStr>
    14dc:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
    14e0:	e1a00003 	mov	r0, r3
    14e4:	ebfffbd8 	bl	44c <itoa>
    14e8:	e1a03000 	mov	r3, r0
    14ec:	e1a00003 	mov	r0, r3
    14f0:	ebfffbc2 	bl	400 <ptarmUartOutputStr>
    14f4:	e59f0430 	ldr	r0, [pc, #1072]	; 192c <main+0x1044>
    14f8:	ebfffbc0 	bl	400 <ptarmUartOutputStr>
    14fc:	e59f34e8 	ldr	r3, [pc, #1256]	; 19ec <main+0x1104>
    1500:	e5933000 	ldr	r3, [r3]
    1504:	e1a00003 	mov	r0, r3
    1508:	ebfffbbc 	bl	400 <ptarmUartOutputStr>
    150c:	e59f0434 	ldr	r0, [pc, #1076]	; 1948 <main+0x1060>
    1510:	ebfffbba 	bl	400 <ptarmUartOutputStr>
    1514:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
    1518:	e59f34cc 	ldr	r3, [pc, #1228]	; 19ec <main+0x1104>
    151c:	e3a02002 	mov	r2, #2, 0
    1520:	e5c3200c 	strb	r2, [r3, #12]
    1524:	e51b30b4 	ldr	r3, [fp, #-180]	; 0xb4
    1528:	e59f24bc 	ldr	r2, [pc, #1212]	; 19ec <main+0x1104>
    152c:	e5823024 	str	r3, [r2, #36]	; 0x24
    1530:	e51b20b4 	ldr	r2, [fp, #-180]	; 0xb4
    1534:	e59f34b0 	ldr	r3, [pc, #1200]	; 19ec <main+0x1104>
    1538:	e5933020 	ldr	r3, [r3, #32]
    153c:	e0823003 	add	r3, r2, r3
    1540:	e59f24a4 	ldr	r2, [pc, #1188]	; 19ec <main+0x1104>
    1544:	e5823028 	str	r3, [r2, #40]	; 0x28
    1548:	e59f33e8 	ldr	r3, [pc, #1000]	; 1938 <main+0x1050>
    154c:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    1550:	e2833001 	add	r3, r3, #1, 0
    1554:	e59f23dc 	ldr	r2, [pc, #988]	; 1938 <main+0x1050>
    1558:	e5823030 	str	r3, [r2, #48]	; 0x30
    155c:	e59f33d4 	ldr	r3, [pc, #980]	; 1938 <main+0x1050>
    1560:	e5932024 	ldr	r2, [r3, #36]	; 0x24
    1564:	e59f33cc 	ldr	r3, [pc, #972]	; 1938 <main+0x1050>
    1568:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    156c:	e1a03103 	lsl	r3, r3, #2
    1570:	e0823003 	add	r3, r2, r3
    1574:	e59f2470 	ldr	r2, [pc, #1136]	; 19ec <main+0x1104>
    1578:	e5832000 	str	r2, [r3]
			}
			
			// Go through the static schedule and release any eligible tasks.
			for (localScheduler.nextStaticTask = localScheduler.staticSchedule; (*localScheduler.nextStaticTask) != NULL; localScheduler.nextStaticTask++) {
    157c:	e51b30cc 	ldr	r3, [fp, #-204]	; 0xcc
    1580:	e50b30c4 	str	r3, [fp, #-196]	; 0xc4
    1584:	ea000073 	b	1758 <main+0xe70>
				
				volatile Task *currentTask = *localScheduler.nextStaticTask;
    1588:	e51b30c4 	ldr	r3, [fp, #-196]	; 0xc4
    158c:	e5933000 	ldr	r3, [r3]
    1590:	e50b3060 	str	r3, [fp, #-96]	; 0x60
				
				// If the task is paused, check if it can be released for execution (i.e., the minimum number of base periods has elapsed).
				if (currentTask->state == PTARM_TASK_PAUSED && (currentTask->earliestRelease <= localScheduler.basePeriodCounter)) {
    1594:	e51b3060 	ldr	r3, [fp, #-96]	; 0x60
    1598:	e5d3300c 	ldrb	r3, [r3, #12]
    159c:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    15a0:	e3530000 	cmp	r3, #0, 0
    15a4:	1a000068 	bne	174c <main+0xe64>
    15a8:	e51b3060 	ldr	r3, [fp, #-96]	; 0x60
    15ac:	e5932028 	ldr	r2, [r3, #40]	; 0x28
    15b0:	e51b30b4 	ldr	r3, [fp, #-180]	; 0xb4
    15b4:	e1520003 	cmp	r2, r3
    15b8:	8a000063 	bhi	174c <main+0xe64>
					
					// "Releasing xxx."
					PTARM_MUTEX_LOCK();
    15bc:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
					printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Releasing "); printf(currentTask->name); printf(".\n");
    15c0:	e59f0418 	ldr	r0, [pc, #1048]	; 19e0 <main+0x10f8>
    15c4:	ebfffb8d 	bl	400 <ptarmUartOutputStr>
    15c8:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
    15cc:	e1a00003 	mov	r0, r3
    15d0:	ebfffb9d 	bl	44c <itoa>
    15d4:	e1a03000 	mov	r3, r0
    15d8:	e1a00003 	mov	r0, r3
    15dc:	ebfffb87 	bl	400 <ptarmUartOutputStr>
    15e0:	e59f0344 	ldr	r0, [pc, #836]	; 192c <main+0x1044>
    15e4:	ebfffb85 	bl	400 <ptarmUartOutputStr>
    15e8:	e51b3060 	ldr	r3, [fp, #-96]	; 0x60
    15ec:	e5933000 	ldr	r3, [r3]
    15f0:	e1a00003 	mov	r0, r3
    15f4:	ebfffb81 	bl	400 <ptarmUartOutputStr>
    15f8:	e59f0348 	ldr	r0, [pc, #840]	; 1948 <main+0x1060>
    15fc:	ebfffb7f 	bl	400 <ptarmUartOutputStr>
					PTARM_MUTEX_UNLOCK();
    1600:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
					
					// The minimum number of base periods has elapsed, so release the task.
					currentTask->state = PTARM_TASK_RELEASED;
    1604:	e51b3060 	ldr	r3, [fp, #-96]	; 0x60
    1608:	e3a02002 	mov	r2, #2, 0
    160c:	e5c3200c 	strb	r2, [r3, #12]
					
					// Update its last released timestamp.
					currentTask->lastRelease = localScheduler.basePeriodCounter;
    1610:	e51b20b4 	ldr	r2, [fp, #-180]	; 0xb4
    1614:	e51b3060 	ldr	r3, [fp, #-96]	; 0x60
    1618:	e5832024 	str	r2, [r3, #36]	; 0x24
					
					// Update its next earliest release timestamp.
					currentTask->earliestRelease = (localScheduler.basePeriodCounter + currentTask->basePeriodsMin);
    161c:	e51b20b4 	ldr	r2, [fp, #-180]	; 0xb4
    1620:	e51b3060 	ldr	r3, [fp, #-96]	; 0x60
    1624:	e5933020 	ldr	r3, [r3, #32]
    1628:	e0822003 	add	r2, r2, r3
    162c:	e51b3060 	ldr	r3, [fp, #-96]	; 0x60
    1630:	e5832028 	str	r2, [r3, #40]	; 0x28

					// Release all the receive buffers associated with the task.
					volatile struct _ForeMc_100int *volatile *receiveBuffer;
					for (receiveBuffer = currentTask->receiveBuffers; *receiveBuffer != NULL; receiveBuffer++) {
    1634:	e51b3060 	ldr	r3, [fp, #-96]	; 0x60
    1638:	e283302c 	add	r3, r3, #44, 0	; 0x2c
    163c:	e50b3020 	str	r3, [fp, #-32]
    1640:	ea00003d 	b	173c <main+0xe54>
						FOREMC_BUFFER_RELEASE(*receiveBuffer);
    1644:	e51b3020 	ldr	r3, [fp, #-32]
    1648:	e5933000 	ldr	r3, [r3]
    164c:	e51b2020 	ldr	r2, [fp, #-32]
    1650:	e5922000 	ldr	r2, [r2]
    1654:	e5922198 	ldr	r2, [r2, #408]	; 0x198
    1658:	e5832190 	str	r2, [r3, #400]	; 0x190
    165c:	e51b3020 	ldr	r3, [fp, #-32]
    1660:	e5933000 	ldr	r3, [r3]
    1664:	e51b2020 	ldr	r2, [fp, #-32]
    1668:	e5922000 	ldr	r2, [r2]
    166c:	e592219c 	ldr	r2, [r2, #412]	; 0x19c
    1670:	e5832194 	str	r2, [r3, #404]	; 0x194
    1674:	e51b3020 	ldr	r3, [fp, #-32]
    1678:	e5934000 	ldr	r4, [r3]
    167c:	e51b3020 	ldr	r3, [fp, #-32]
    1680:	e5933000 	ldr	r3, [r3]
    1684:	e593219c 	ldr	r2, [r3, #412]	; 0x19c
    1688:	e51b3020 	ldr	r3, [fp, #-32]
    168c:	e5933000 	ldr	r3, [r3]
    1690:	e5933198 	ldr	r3, [r3, #408]	; 0x198
    1694:	e0823003 	add	r3, r2, r3
    1698:	e1a02003 	mov	r2, r3
    169c:	e51b3020 	ldr	r3, [fp, #-32]
    16a0:	e5933000 	ldr	r3, [r3]
    16a4:	e59331a0 	ldr	r3, [r3, #416]	; 0x1a0
    16a8:	e1a01003 	mov	r1, r3
    16ac:	e1a00002 	mov	r0, r2
    16b0:	ebfffc77 	bl	894 <foreMcGetIndex>
    16b4:	e1a03000 	mov	r3, r0
    16b8:	e5843198 	str	r3, [r4, #408]	; 0x198
    16bc:	e51b3020 	ldr	r3, [fp, #-32]
    16c0:	e5933000 	ldr	r3, [r3]
    16c4:	e3a02000 	mov	r2, #0, 0
    16c8:	e583219c 	str	r2, [r3, #412]	; 0x19c
    16cc:	e51b3020 	ldr	r3, [fp, #-32]
    16d0:	e5934000 	ldr	r4, [r3]
    16d4:	e51b3020 	ldr	r3, [fp, #-32]
    16d8:	e5933000 	ldr	r3, [r3]
    16dc:	e5935198 	ldr	r5, [r3, #408]	; 0x198
    16e0:	e51b3020 	ldr	r3, [fp, #-32]
    16e4:	e5936000 	ldr	r6, [r3]
    16e8:	e51b3020 	ldr	r3, [fp, #-32]
    16ec:	e5933000 	ldr	r3, [r3]
    16f0:	e5933194 	ldr	r3, [r3, #404]	; 0x194
    16f4:	e2432001 	sub	r2, r3, #1, 0
    16f8:	e51b3020 	ldr	r3, [fp, #-32]
    16fc:	e5933000 	ldr	r3, [r3]
    1700:	e5933190 	ldr	r3, [r3, #400]	; 0x190
    1704:	e0823003 	add	r3, r2, r3
    1708:	e1a02003 	mov	r2, r3
    170c:	e51b3020 	ldr	r3, [fp, #-32]
    1710:	e5933000 	ldr	r3, [r3]
    1714:	e59331a0 	ldr	r3, [r3, #416]	; 0x1a0
    1718:	e1a01003 	mov	r1, r3
    171c:	e1a00002 	mov	r0, r2
    1720:	ebfffc5b 	bl	894 <foreMcGetIndex>
    1724:	e1a03000 	mov	r3, r0
    1728:	e7963103 	ldr	r3, [r6, r3, lsl #2]
    172c:	e7843105 	str	r3, [r4, r5, lsl #2]
    1730:	e51b3020 	ldr	r3, [fp, #-32]
    1734:	e2833004 	add	r3, r3, #4, 0
    1738:	e50b3020 	str	r3, [fp, #-32]
    173c:	e51b3020 	ldr	r3, [fp, #-32]
    1740:	e5933000 	ldr	r3, [r3]
    1744:	e3530000 	cmp	r3, #0, 0
    1748:	1affffbd 	bne	1644 <main+0xd5c>
    174c:	e51b30c4 	ldr	r3, [fp, #-196]	; 0xc4
    1750:	e2833004 	add	r3, r3, #4, 0
    1754:	e50b30c4 	str	r3, [fp, #-196]	; 0xc4
    1758:	e51b30c4 	ldr	r3, [fp, #-196]	; 0xc4
    175c:	e5933000 	ldr	r3, [r3]
    1760:	e3530000 	cmp	r3, #0, 0
    1764:	1affff87 	bne	1588 <main+0xca0>
					}
				}
			}
			
			// Reset the static schedule (to the first task).
			localScheduler.nextStaticTask = localScheduler.staticSchedule;
    1768:	e51b30cc 	ldr	r3, [fp, #-204]	; 0xcc
    176c:	e50b30c4 	str	r3, [fp, #-196]	; 0xc4
			
			// Continue through to the next case statement for the static scheduling phase.
			// Start time = basePeriodStartOverhead + basePeriodStart.
			localScheduler.phase = PTARM_SCHEDULER_STATIC;
    1770:	e3a03001 	mov	r3, #1, 0
    1774:	e54b30c0 	strb	r3, [fp, #-192]	; 0xc0
			PTARM_ADD(localScheduler.basePeriodStartAfterOverhead, localScheduler.basePeriodStartOverhead, localScheduler.basePeriodStart);
    1778:	e51b30b0 	ldr	r3, [fp, #-176]	; 0xb0
    177c:	e51b20ac 	ldr	r2, [fp, #-172]	; 0xac
    1780:	e51b10bc 	ldr	r1, [fp, #-188]	; 0xbc
    1784:	e51b00b8 	ldr	r0, [fp, #-184]	; 0xb8
    1788:	e1a07003 	mov	r7, r3
    178c:	e1a08002 	mov	r8, r2
    1790:	e0988000 	adds	r8, r8, r0
    1794:	e0a77001 	adc	r7, r7, r1
    1798:	e1a02007 	mov	r2, r7
    179c:	e1a03008 	mov	r3, r8
    17a0:	e50b20a0 	str	r2, [fp, #-160]	; 0xa0
    17a4:	e50b309c 	str	r3, [fp, #-156]	; 0x9c
			PTARM_DELAY(localScheduler.basePeriodStartAfterOverhead);
    17a8:	e51b30a0 	ldr	r3, [fp, #-160]	; 0xa0
    17ac:	e51b209c 	ldr	r2, [fp, #-156]	; 0x9c
    17b0:	e1a07003 	mov	r7, r3
    17b4:	e1a08002 	mov	r8, r2
    17b8:	ee470d08 	cdp	13, 4, cr0, cr7, cr8, {0}

		case (PTARM_SCHEDULER_STATIC):;
			// Static scheduling phase.
			// Schedule all the tasks in its static schedule before going into the dynamic scheduling phase.

			// Get the next statically scheduled task.
			localScheduler.currentTask = *localScheduler.nextStaticTask;
    17bc:	e51b30c4 	ldr	r3, [fp, #-196]	; 0xc4
    17c0:	e5933000 	ldr	r3, [r3]
    17c4:	e50b30c8 	str	r3, [fp, #-200]	; 0xc8

			// Check if we have reached the end of the static schedule.
			if (localScheduler.currentTask != NULL) {
    17c8:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    17cc:	e3530000 	cmp	r3, #0, 0
    17d0:	0a000087 	beq	19f4 <main+0x110c>
				// The end of the static schedule has not been reached.

				// Update the next statically scheduled task.
				localScheduler.nextStaticTask++;
    17d4:	e51b30c4 	ldr	r3, [fp, #-196]	; 0xc4
    17d8:	e2833004 	add	r3, r3, #4, 0
    17dc:	e50b30c4 	str	r3, [fp, #-196]	; 0xc4

				// Execute the task if it has been preempted or released.
				if (localScheduler.currentTask->state == PTARM_TASK_PREEMPTED || localScheduler.currentTask->state == PTARM_TASK_RELEASED) {
    17e0:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    17e4:	e5d3300c 	ldrb	r3, [r3, #12]
    17e8:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    17ec:	e3530001 	cmp	r3, #1, 0
    17f0:	0a000004 	beq	1808 <main+0xf20>
    17f4:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    17f8:	e5d3300c 	ldrb	r3, [r3, #12]
    17fc:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1800:	e3530002 	cmp	r3, #2, 0
    1804:	1afffe7d 	bne	1200 <main+0x918>
					
					// "Executing xxx."
					PTARM_MUTEX_LOCK();
    1808:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
					printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Executing "); printf(localScheduler.currentTask->name); printf(".\n");
    180c:	e59f01cc 	ldr	r0, [pc, #460]	; 19e0 <main+0x10f8>
    1810:	ebfffafa 	bl	400 <ptarmUartOutputStr>
    1814:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
    1818:	e1a00003 	mov	r0, r3
    181c:	ebfffb0a 	bl	44c <itoa>
    1820:	e1a03000 	mov	r3, r0
    1824:	e1a00003 	mov	r0, r3
    1828:	ebfffaf4 	bl	400 <ptarmUartOutputStr>
    182c:	e59f00fc 	ldr	r0, [pc, #252]	; 1930 <main+0x1048>
    1830:	ebfffaf2 	bl	400 <ptarmUartOutputStr>
    1834:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    1838:	e5933000 	ldr	r3, [r3]
    183c:	e1a00003 	mov	r0, r3
    1840:	ebfffaee 	bl	400 <ptarmUartOutputStr>
    1844:	e59f00fc 	ldr	r0, [pc, #252]	; 1948 <main+0x1060>
    1848:	ebfffaec 	bl	400 <ptarmUartOutputStr>
					PTARM_MUTEX_UNLOCK();
    184c:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

					// Set the task's deadline in this base period to be the end of its statically allocated execution time.
					PTARM_TIME_GET(localScheduler.currentTime);
    1850:	ee870d08 	cdp	13, 8, cr0, cr7, cr8, {0}
    1854:	e1a02007 	mov	r2, r7
    1858:	e1a03008 	mov	r3, r8
    185c:	e50b2090 	str	r2, [fp, #-144]	; 0x90
    1860:	e50b308c 	str	r3, [fp, #-140]	; 0x8c
					PTARM_EOE_ENABLE(localScheduler.currentTask->allocatedTime, localScheduler.currentTime);
    1864:	e51b3090 	ldr	r3, [fp, #-144]	; 0x90
    1868:	e51b208c 	ldr	r2, [fp, #-140]	; 0x8c
    186c:	e51b10c8 	ldr	r1, [fp, #-200]	; 0xc8
    1870:	e5911018 	ldr	r1, [r1, #24]
    1874:	e51b00c8 	ldr	r0, [fp, #-200]	; 0xc8
    1878:	e590001c 	ldr	r0, [r0, #28]
    187c:	e1a07003 	mov	r7, r3
    1880:	e1a08002 	mov	r8, r2
    1884:	e0988000 	adds	r8, r8, r0
    1888:	e0a77001 	adc	r7, r7, r1
    188c:	ee270d08 	cdp	13, 2, cr0, cr7, cr8, {0}
					
					// (Re)set the task's local scheduler to this static local scheduler.
					PTARM_TASK_SET_SCHEDULER(localScheduler.currentTask, &localScheduler);
    1890:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    1894:	e24b20e8 	sub	r2, fp, #232, 0	; 0xe8
    1898:	e5832008 	str	r2, [r3, #8]

					// Context switch to the current task.
					PTARM_TASK_RESTORE_CONTEXT(localScheduler.currentTask);
    189c:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    18a0:	e5933014 	ldr	r3, [r3, #20]
    18a4:	e1a08003 	mov	r8, r3
    18a8:	ee200c08 	cdp	12, 2, cr0, cr0, cr8, {0}
    18ac:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    18b0:	e5933010 	ldr	r3, [r3, #16]
    18b4:	e1a0d003 	mov	sp, r3
    18b8:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
    18bc:	e8bd1fff 	pop	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    18c0:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)
    18c4:	ea000058 	b	1a2c <main+0x1144>
    18c8:	00002b24 	.word	0x00002b24
    18cc:	00001200 	.word	0x00001200
    18d0:	00002984 	.word	0x00002984
    18d4:	0000251c 	.word	0x0000251c
    18d8:	00002608 	.word	0x00002608
    18dc:	000026f4 	.word	0x000026f4
    18e0:	000027e0 	.word	0x000027e0
    18e4:	000020c4 	.word	0x000020c4
    18e8:	00001cb0 	.word	0x00001cb0
    18ec:	0000ffe0 	.word	0x0000ffe0
    18f0:	00000dfc 	.word	0x00000dfc
    18f4:	000021b0 	.word	0x000021b0
    18f8:	00001e00 	.word	0x00001e00
    18fc:	00000e60 	.word	0x00000e60
    1900:	00001eec 	.word	0x00001eec
    1904:	00001fd8 	.word	0x00001fd8
    1908:	00000ec4 	.word	0x00000ec4
    190c:	00002344 	.word	0x00002344
    1910:	00002430 	.word	0x00002430
    1914:	00000f28 	.word	0x00000f28
    1918:	00002998 	.word	0x00002998
    191c:	000029d0 	.word	0x000029d0
    1920:	000029e0 	.word	0x000029e0
    1924:	000029f0 	.word	0x000029f0
    1928:	000029fc 	.word	0x000029fc
    192c:	00002a08 	.word	0x00002a08
    1930:	00002a14 	.word	0x00002a14
    1934:	00002a20 	.word	0x00002a20
    1938:	0000301c 	.word	0x0000301c
    193c:	00002a34 	.word	0x00002a34
    1940:	00002a40 	.word	0x00002a40
    1944:	00002a44 	.word	0x00002a44
    1948:	000029dc 	.word	0x000029dc
    194c:	00002c28 	.word	0x00002c28
    1950:	00002a60 	.word	0x00002a60
    1954:	00001dec 	.word	0x00001dec
    1958:	00002c2c 	.word	0x00002c2c
    195c:	00002a70 	.word	0x00002a70
    1960:	00001ed8 	.word	0x00001ed8
    1964:	00002c80 	.word	0x00002c80
    1968:	00002a80 	.word	0x00002a80
    196c:	00001fc4 	.word	0x00001fc4
    1970:	00002cd4 	.word	0x00002cd4
    1974:	00002a90 	.word	0x00002a90
    1978:	000020b0 	.word	0x000020b0
    197c:	00002d28 	.word	0x00002d28
    1980:	00002aa0 	.word	0x00002aa0
    1984:	0000219c 	.word	0x0000219c
    1988:	00002d7c 	.word	0x00002d7c
    198c:	00002ab0 	.word	0x00002ab0
    1990:	000029c8 	.word	0x000029c8
    1994:	0000314c 	.word	0x0000314c
    1998:	00002ab4 	.word	0x00002ab4
    199c:	00002330 	.word	0x00002330
    19a0:	00002dd0 	.word	0x00002dd0
    19a4:	00002ac4 	.word	0x00002ac4
    19a8:	0000241c 	.word	0x0000241c
    19ac:	00002e24 	.word	0x00002e24
    19b0:	00002ad4 	.word	0x00002ad4
    19b4:	00002508 	.word	0x00002508
    19b8:	00002e78 	.word	0x00002e78
    19bc:	00002ae4 	.word	0x00002ae4
    19c0:	000025f4 	.word	0x000025f4
    19c4:	00002ecc 	.word	0x00002ecc
    19c8:	00002af4 	.word	0x00002af4
    19cc:	000026e0 	.word	0x000026e0
    19d0:	00002f20 	.word	0x00002f20
    19d4:	00002b04 	.word	0x00002b04
    19d8:	000027cc 	.word	0x000027cc
    19dc:	00002f74 	.word	0x00002f74
    19e0:	000029cc 	.word	0x000029cc
    19e4:	00002b14 	.word	0x00002b14
    19e8:	000028b8 	.word	0x000028b8
    19ec:	00002fc8 	.word	0x00002fc8
    19f0:	00002c29 	.word	0x00002c29
				} else {
					// Pick the next task to execute instead.
					goto localScheduler;
				}
			} else {
				// The end of the static schedule has been reached. Prepare for the dynamic scheduling phase.
				
				// "Dynamic phase."
				PTARM_MUTEX_LOCK();
    19f4:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
				printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Dynamic phase.\n");
    19f8:	e51f0020 	ldr	r0, [pc, #-32]	; 19e0 <main+0x10f8>
    19fc:	ebfffa7f 	bl	400 <ptarmUartOutputStr>
    1a00:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
    1a04:	e1a00003 	mov	r0, r3
    1a08:	ebfffa8f 	bl	44c <itoa>
    1a0c:	e1a03000 	mov	r3, r0
    1a10:	e1a00003 	mov	r0, r3
    1a14:	ebfffa79 	bl	400 <ptarmUartOutputStr>
    1a18:	e51f00ec 	ldr	r0, [pc, #-236]	; 1934 <main+0x104c>
    1a1c:	ebfffa77 	bl	400 <ptarmUartOutputStr>
				PTARM_MUTEX_UNLOCK();
    1a20:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

				// We are now entering the dynamic scheduling phase.
				localScheduler.phase = PTARM_SCHEDULER_DYNAMIC;
    1a24:	e3a03002 	mov	r3, #2, 0
    1a28:	e54b30c0 	strb	r3, [fp, #-192]	; 0xc0

				// Continue through to the next case statement for the dynamic scheduling phase.
			}
		case (PTARM_SCHEDULER_DYNAMIC):;
			// Dynamic scheduling phase.
			
			// (Re)set the current task in case a timing exception occurs when the scheduler is executing.
			localScheduler.currentTask = NULL;
    1a2c:	e3a03000 	mov	r3, #0, 0
    1a30:	e50b30c8 	str	r3, [fp, #-200]	; 0xc8

			// Set the dynamic execution deadline to be the end of the base period, minus the expected scheduling overhead.
			PTARM_EOE_ENABLE(localScheduler.basePeriodMinusEndingOverhead, localScheduler.basePeriodStart);
    1a34:	e51b30bc 	ldr	r3, [fp, #-188]	; 0xbc
    1a38:	e51b20b8 	ldr	r2, [fp, #-184]	; 0xb8
    1a3c:	e51b1098 	ldr	r1, [fp, #-152]	; 0x98
    1a40:	e51b0094 	ldr	r0, [fp, #-148]	; 0x94
    1a44:	e1a07003 	mov	r7, r3
    1a48:	e1a08002 	mov	r8, r2
    1a4c:	e0988000 	adds	r8, r8, r0
    1a50:	e0a77001 	adc	r7, r7, r1
    1a54:	ee270d08 	cdp	13, 2, cr0, cr7, cr8, {0}

			// Check if there is enough time to execute a task.
			// elapsedTime = currentTime - basePeriodStart.
			PTARM_TIME_GET(localScheduler.currentTime);
    1a58:	ee870d08 	cdp	13, 8, cr0, cr7, cr8, {0}
    1a5c:	e1a02007 	mov	r2, r7
    1a60:	e1a03008 	mov	r3, r8
    1a64:	e50b2090 	str	r2, [fp, #-144]	; 0x90
    1a68:	e50b308c 	str	r3, [fp, #-140]	; 0x8c
			PTARM_MINUS(localScheduler.elapsedTime, localScheduler.currentTime, localScheduler.basePeriodStart);
    1a6c:	e51b3090 	ldr	r3, [fp, #-144]	; 0x90
    1a70:	e51b208c 	ldr	r2, [fp, #-140]	; 0x8c
    1a74:	e51b10bc 	ldr	r1, [fp, #-188]	; 0xbc
    1a78:	e51b00b8 	ldr	r0, [fp, #-184]	; 0xb8
    1a7c:	e1a07003 	mov	r7, r3
    1a80:	e1a08002 	mov	r8, r2
    1a84:	e0588000 	subs	r8, r8, r0
    1a88:	e0c77001 	sbc	r7, r7, r1
    1a8c:	e1a02007 	mov	r2, r7
    1a90:	e1a03008 	mov	r3, r8
    1a94:	e50b2088 	str	r2, [fp, #-136]	; 0x88
    1a98:	e50b3084 	str	r3, [fp, #-132]	; 0x84

			if ((localScheduler.basePeriodMinusEndingOverhead.msb > localScheduler.elapsedTime.msb) ||
    1a9c:	e51b2098 	ldr	r2, [fp, #-152]	; 0x98
    1aa0:	e51b3088 	ldr	r3, [fp, #-136]	; 0x88
    1aa4:	e1520003 	cmp	r2, r3
    1aa8:	ca000007 	bgt	1acc <main+0x11e4>
				((localScheduler.basePeriodMinusEndingOverhead.msb == localScheduler.elapsedTime.msb) && (localScheduler.basePeriodMinusEndingOverhead.lsb >= localScheduler.elapsedTime.lsb))) {
    1aac:	e51b2098 	ldr	r2, [fp, #-152]	; 0x98
    1ab0:	e51b3088 	ldr	r3, [fp, #-136]	; 0x88
    1ab4:	e1520003 	cmp	r2, r3
    1ab8:	1afffdd0 	bne	1200 <main+0x918>
    1abc:	e51b2094 	ldr	r2, [fp, #-148]	; 0x94
    1ac0:	e51b3084 	ldr	r3, [fp, #-132]	; 0x84
    1ac4:	e1520003 	cmp	r2, r3
    1ac8:	3afffdcc 	bcc	1200 <main+0x918>
				// Enough time to execute a task. Find a task to execute.

				// Find a task from the dynamic scheduling lists to execute.
				PTARM_MUTEX_LOCK();
    1acc:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
				PTARM_SCHEDULER_DYNAMIC_LIST_POP(globalScheduler, localScheduler.currentTask);
    1ad0:	e51f31a0 	ldr	r3, [pc, #-416]	; 1938 <main+0x1050>
    1ad4:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    1ad8:	e3530000 	cmp	r3, #0, 0
    1adc:	ba00000d 	blt	1b18 <main+0x1230>
    1ae0:	e51f31b0 	ldr	r3, [pc, #-432]	; 1938 <main+0x1050>
    1ae4:	e5932024 	ldr	r2, [r3, #36]	; 0x24
    1ae8:	e51f31b8 	ldr	r3, [pc, #-440]	; 1938 <main+0x1050>
    1aec:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    1af0:	e1a03103 	lsl	r3, r3, #2
    1af4:	e0823003 	add	r3, r2, r3
    1af8:	e5933000 	ldr	r3, [r3]
    1afc:	e50b30c8 	str	r3, [fp, #-200]	; 0xc8
    1b00:	e51f31d0 	ldr	r3, [pc, #-464]	; 1938 <main+0x1050>
    1b04:	e5933030 	ldr	r3, [r3, #48]	; 0x30
    1b08:	e2433001 	sub	r3, r3, #1, 0
    1b0c:	e51f21dc 	ldr	r2, [pc, #-476]	; 1938 <main+0x1050>
    1b10:	e5823030 	str	r3, [r2, #48]	; 0x30
    1b14:	ea000025 	b	1bb0 <main+0x12c8>
    1b18:	e51f31e8 	ldr	r3, [pc, #-488]	; 1938 <main+0x1050>
    1b1c:	e5933034 	ldr	r3, [r3, #52]	; 0x34
    1b20:	e3530000 	cmp	r3, #0, 0
    1b24:	ba00000d 	blt	1b60 <main+0x1278>
    1b28:	e51f31f8 	ldr	r3, [pc, #-504]	; 1938 <main+0x1050>
    1b2c:	e5932028 	ldr	r2, [r3, #40]	; 0x28
    1b30:	e51f3200 	ldr	r3, [pc, #-512]	; 1938 <main+0x1050>
    1b34:	e5933034 	ldr	r3, [r3, #52]	; 0x34
    1b38:	e1a03103 	lsl	r3, r3, #2
    1b3c:	e0823003 	add	r3, r2, r3
    1b40:	e5933000 	ldr	r3, [r3]
    1b44:	e50b30c8 	str	r3, [fp, #-200]	; 0xc8
    1b48:	e51f3218 	ldr	r3, [pc, #-536]	; 1938 <main+0x1050>
    1b4c:	e5933034 	ldr	r3, [r3, #52]	; 0x34
    1b50:	e2433001 	sub	r3, r3, #1, 0
    1b54:	e51f2224 	ldr	r2, [pc, #-548]	; 1938 <main+0x1050>
    1b58:	e5823034 	str	r3, [r2, #52]	; 0x34
    1b5c:	ea000013 	b	1bb0 <main+0x12c8>
    1b60:	e51f3230 	ldr	r3, [pc, #-560]	; 1938 <main+0x1050>
    1b64:	e5933038 	ldr	r3, [r3, #56]	; 0x38
    1b68:	e3530000 	cmp	r3, #0, 0
    1b6c:	ba00000d 	blt	1ba8 <main+0x12c0>
    1b70:	e51f3240 	ldr	r3, [pc, #-576]	; 1938 <main+0x1050>
    1b74:	e593202c 	ldr	r2, [r3, #44]	; 0x2c
    1b78:	e51f3248 	ldr	r3, [pc, #-584]	; 1938 <main+0x1050>
    1b7c:	e5933038 	ldr	r3, [r3, #56]	; 0x38
    1b80:	e1a03103 	lsl	r3, r3, #2
    1b84:	e0823003 	add	r3, r2, r3
    1b88:	e5933000 	ldr	r3, [r3]
    1b8c:	e50b30c8 	str	r3, [fp, #-200]	; 0xc8
    1b90:	e51f3260 	ldr	r3, [pc, #-608]	; 1938 <main+0x1050>
    1b94:	e5933038 	ldr	r3, [r3, #56]	; 0x38
    1b98:	e2433001 	sub	r3, r3, #1, 0
    1b9c:	e51f226c 	ldr	r2, [pc, #-620]	; 1938 <main+0x1050>
    1ba0:	e5823038 	str	r3, [r2, #56]	; 0x38
    1ba4:	ea000001 	b	1bb0 <main+0x12c8>
    1ba8:	e3a03000 	mov	r3, #0, 0
    1bac:	e50b30c8 	str	r3, [fp, #-200]	; 0xc8
				PTARM_MUTEX_UNLOCK();
    1bb0:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

				// Check if it is an available task.
				if (localScheduler.currentTask != NULL) {
    1bb4:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    1bb8:	e3530000 	cmp	r3, #0, 0
    1bbc:	0afffd8f 	beq	1200 <main+0x918>

					// "Picking xxx."
					PTARM_MUTEX_LOCK();
    1bc0:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
					printf(" "); printf(utoa(localScheduler.hwThreadId)); printf(":Picking "); printf(localScheduler.currentTask->name); printf(".\n");
    1bc4:	e51f01ec 	ldr	r0, [pc, #-492]	; 19e0 <main+0x10f8>
    1bc8:	ebfffa0c 	bl	400 <ptarmUartOutputStr>
    1bcc:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
    1bd0:	e1a00003 	mov	r0, r3
    1bd4:	ebfffa61 	bl	560 <utoa>
    1bd8:	e1a03000 	mov	r3, r0
    1bdc:	e1a00003 	mov	r0, r3
    1be0:	ebfffa06 	bl	400 <ptarmUartOutputStr>
    1be4:	e51f02b0 	ldr	r0, [pc, #-688]	; 193c <main+0x1054>
    1be8:	ebfffa04 	bl	400 <ptarmUartOutputStr>
    1bec:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    1bf0:	e5933000 	ldr	r3, [r3]
    1bf4:	e1a00003 	mov	r0, r3
    1bf8:	ebfffa00 	bl	400 <ptarmUartOutputStr>
    1bfc:	e51f02bc 	ldr	r0, [pc, #-700]	; 1948 <main+0x1060>
    1c00:	ebfff9fe 	bl	400 <ptarmUartOutputStr>
					PTARM_MUTEX_UNLOCK();
    1c04:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

					// Set the task's local scheduler to this dynamic local scheduler.
					PTARM_TASK_SET_SCHEDULER(localScheduler.currentTask, &localScheduler);
    1c08:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    1c0c:	e24b20e8 	sub	r2, fp, #232, 0	; 0xe8
    1c10:	e5832008 	str	r2, [r3, #8]

					// The task is available, so context switch to it.
					PTARM_TASK_RESTORE_CONTEXT(localScheduler.currentTask);
    1c14:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    1c18:	e5933014 	ldr	r3, [r3, #20]
    1c1c:	e1a08003 	mov	r8, r3
    1c20:	ee200c08 	cdp	12, 2, cr0, cr0, cr8, {0}
    1c24:	e51b30c8 	ldr	r3, [fp, #-200]	; 0xc8
    1c28:	e5933010 	ldr	r3, [r3, #16]
    1c2c:	e1a0d003 	mov	sp, r3
    1c30:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
    1c34:	e8bd1fff 	pop	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    1c38:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)
				}
			}

			// Wait for a task to become available, or until the base period ends.
			goto localScheduler;
    1c3c:	eafffd6f 	b	1200 <main+0x918>
			break;

		default:;
			// Undefined scheduling phase.
			PTARM_MUTEX_LOCK();
    1c40:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
			printf("!!"); printf(utoa(localScheduler.hwThreadId)); printf(" Scheduling error. Phase = "); printf(utoa(localScheduler.phase)); printf(".\n");
    1c44:	e51f030c 	ldr	r0, [pc, #-780]	; 1940 <main+0x1058>
    1c48:	ebfff9ec 	bl	400 <ptarmUartOutputStr>
    1c4c:	e51b30e4 	ldr	r3, [fp, #-228]	; 0xe4
    1c50:	e1a00003 	mov	r0, r3
    1c54:	ebfffa41 	bl	560 <utoa>
    1c58:	e1a03000 	mov	r3, r0
    1c5c:	e1a00003 	mov	r0, r3
    1c60:	ebfff9e6 	bl	400 <ptarmUartOutputStr>
    1c64:	e51f0328 	ldr	r0, [pc, #-808]	; 1944 <main+0x105c>
    1c68:	ebfff9e4 	bl	400 <ptarmUartOutputStr>
    1c6c:	e55b30c0 	ldrb	r3, [fp, #-192]	; 0xc0
    1c70:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1c74:	e1a00003 	mov	r0, r3
    1c78:	ebfffa38 	bl	560 <utoa>
    1c7c:	e1a03000 	mov	r3, r0
    1c80:	e1a00003 	mov	r0, r3
    1c84:	ebfff9dd 	bl	400 <ptarmUartOutputStr>
    1c88:	e51f0348 	ldr	r0, [pc, #-840]	; 1948 <main+0x1060>
    1c8c:	ebfff9db 	bl	400 <ptarmUartOutputStr>
			PTARM_MUTEX_UNLOCK();
    1c90:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}

			while (halt);
    1c94:	e1a00000 	nop			; (mov r0, r0)
    1c98:	e51f3354 	ldr	r3, [pc, #-852]	; 194c <main+0x1064>
    1c9c:	e5d33000 	ldrb	r3, [r3]
    1ca0:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1ca4:	e3530000 	cmp	r3, #0, 0
    1ca8:	1afffffa 	bne	1c98 <main+0x13b0>
			break;
    1cac:	e1a00000 	nop			; (mov r0, r0)
	}
}

// The tasks. Note that they are defined within the main function.

// Life critical tasks
l1: {
	int j = 0;
    1cb0:	e3a03000 	mov	r3, #0, 0
    1cb4:	e50b3024 	str	r3, [fp, #-36]	; 0x24
	while (loopForever) {
    1cb8:	ea00004b 	b	1dec <main+0x1504>
		int i;
		for (i = 0; i < 2000000u; i++);
    1cbc:	e3a03000 	mov	r3, #0, 0
    1cc0:	e50b3028 	str	r3, [fp, #-40]	; 0x28
    1cc4:	ea000002 	b	1cd4 <main+0x13ec>
    1cc8:	e51b3028 	ldr	r3, [fp, #-40]	; 0x28
    1ccc:	e2833001 	add	r3, r3, #1, 0
    1cd0:	e50b3028 	str	r3, [fp, #-40]	; 0x28
    1cd4:	e51b2028 	ldr	r2, [fp, #-40]	; 0x28
    1cd8:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    1cdc:	e2833e47 	add	r3, r3, #1136	; 0x470
    1ce0:	e283300f 	add	r3, r3, #15, 0
    1ce4:	e1520003 	cmp	r2, r3
    1ce8:	9afffff6 	bls	1cc8 <main+0x13e0>
		
		j++;
    1cec:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    1cf0:	e2833001 	add	r3, r3, #1, 0
    1cf4:	e50b3024 	str	r3, [fp, #-36]	; 0x24

		PTARM_MUTEX_LOCK();
    1cf8:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(l1.localScheduler->hwThreadId)); printf(":l1 pausing.\n");
    1cfc:	e51f0324 	ldr	r0, [pc, #-804]	; 19e0 <main+0x10f8>
    1d00:	ebfff9be 	bl	400 <ptarmUartOutputStr>
    1d04:	e51f33b4 	ldr	r3, [pc, #-948]	; 1958 <main+0x1070>
    1d08:	e5933008 	ldr	r3, [r3, #8]
    1d0c:	e5933004 	ldr	r3, [r3, #4]
    1d10:	e1a00003 	mov	r0, r3
    1d14:	ebfff9cc 	bl	44c <itoa>
    1d18:	e1a03000 	mov	r3, r0
    1d1c:	e1a00003 	mov	r0, r3
    1d20:	ebfff9b6 	bl	400 <ptarmUartOutputStr>
    1d24:	e51f03dc 	ldr	r0, [pc, #-988]	; 1950 <main+0x1068>
    1d28:	ebfff9b4 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    1d2c:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE_AND_BUFFER(l1, continuationId, bufferOne, j);
    1d30:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    1d34:	e51f33e4 	ldr	r3, [pc, #-996]	; 1958 <main+0x1070>
    1d38:	e3a02000 	mov	r2, #0, 0
    1d3c:	e5c3200c 	strb	r2, [r3, #12]
    1d40:	e51f33b4 	ldr	r3, [pc, #-948]	; 1994 <main+0x10ac>
    1d44:	e593219c 	ldr	r2, [r3, #412]	; 0x19c
    1d48:	e51f33bc 	ldr	r3, [pc, #-956]	; 1994 <main+0x10ac>
    1d4c:	e5933198 	ldr	r3, [r3, #408]	; 0x198
    1d50:	e0823003 	add	r3, r2, r3
    1d54:	e1a02003 	mov	r2, r3
    1d58:	e51f33cc 	ldr	r3, [pc, #-972]	; 1994 <main+0x10ac>
    1d5c:	e59331a0 	ldr	r3, [r3, #416]	; 0x1a0
    1d60:	e1a01003 	mov	r1, r3
    1d64:	e1a00002 	mov	r0, r2
    1d68:	ebfffac9 	bl	894 <foreMcGetIndex>
    1d6c:	e1a01000 	mov	r1, r0
    1d70:	e51f23e4 	ldr	r2, [pc, #-996]	; 1994 <main+0x10ac>
    1d74:	e51b3024 	ldr	r3, [fp, #-36]	; 0x24
    1d78:	e7823101 	str	r3, [r2, r1, lsl #2]
    1d7c:	e51f33f0 	ldr	r3, [pc, #-1008]	; 1994 <main+0x10ac>
    1d80:	e593319c 	ldr	r3, [r3, #412]	; 0x19c
    1d84:	e2833001 	add	r3, r3, #1, 0
    1d88:	e51f23fc 	ldr	r2, [pc, #-1020]	; 1994 <main+0x10ac>
    1d8c:	e582319c 	str	r3, [r2, #412]	; 0x19c
    1d90:	e1a00000 	nop			; (mov r0, r0)
    1d94:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    1d98:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    1d9c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    1da0:	e51f3454 	ldr	r3, [pc, #-1108]	; 1954 <main+0x106c>
    1da4:	e1a07003 	mov	r7, r3
    1da8:	e58d7038 	str	r7, [sp, #56]	; 0x38
    1dac:	e1a0300d 	mov	r3, sp
    1db0:	e51f2460 	ldr	r2, [pc, #-1120]	; 1958 <main+0x1070>
    1db4:	e5823010 	str	r3, [r2, #16]
    1db8:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    1dbc:	e1a03007 	mov	r3, r7
    1dc0:	e51f2470 	ldr	r2, [pc, #-1136]	; 1958 <main+0x1070>
    1dc4:	e5823014 	str	r3, [r2, #20]
    1dc8:	e51f3478 	ldr	r3, [pc, #-1144]	; 1958 <main+0x1070>
    1dcc:	e5933008 	ldr	r3, [r3, #8]
    1dd0:	e593300c 	ldr	r3, [r3, #12]
    1dd4:	e51f2484 	ldr	r2, [pc, #-1156]	; 1958 <main+0x1070>
    1dd8:	e5922008 	ldr	r2, [r2, #8]
    1ddc:	e5922008 	ldr	r2, [r2, #8]
    1de0:	e1a0d003 	mov	sp, r3
    1de4:	e1a0b002 	mov	fp, r2
    1de8:	eafffd04 	b	1200 <main+0x918>
    1dec:	e51f3404 	ldr	r3, [pc, #-1028]	; 19f0 <main+0x1108>
    1df0:	e5d33000 	ldrb	r3, [r3]
    1df4:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1df8:	e3530000 	cmp	r3, #0, 0
    1dfc:	1affffae 	bne	1cbc <main+0x13d4>
	}
}

l2: {
	while (loopForever) {
    1e00:	ea000034 	b	1ed8 <main+0x15f0>
		int i;
		for (i = 0; i < 2000000u; i++);
    1e04:	e3a03000 	mov	r3, #0, 0
    1e08:	e50b302c 	str	r3, [fp, #-44]	; 0x2c
    1e0c:	ea000002 	b	1e1c <main+0x1534>
    1e10:	e51b302c 	ldr	r3, [fp, #-44]	; 0x2c
    1e14:	e2833001 	add	r3, r3, #1, 0
    1e18:	e50b302c 	str	r3, [fp, #-44]	; 0x2c
    1e1c:	e51b202c 	ldr	r2, [fp, #-44]	; 0x2c
    1e20:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    1e24:	e2833e47 	add	r3, r3, #1136	; 0x470
    1e28:	e283300f 	add	r3, r3, #15, 0
    1e2c:	e1520003 	cmp	r2, r3
    1e30:	9afffff6 	bls	1e10 <main+0x1528>

		PTARM_MUTEX_LOCK();
    1e34:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(l2.localScheduler->hwThreadId)); printf(":l2 pausing.\n");
    1e38:	e51f0460 	ldr	r0, [pc, #-1120]	; 19e0 <main+0x10f8>
    1e3c:	ebfff96f 	bl	400 <ptarmUartOutputStr>
    1e40:	e51f34e4 	ldr	r3, [pc, #-1252]	; 1964 <main+0x107c>
    1e44:	e5933008 	ldr	r3, [r3, #8]
    1e48:	e5933004 	ldr	r3, [r3, #4]
    1e4c:	e1a00003 	mov	r0, r3
    1e50:	ebfff97d 	bl	44c <itoa>
    1e54:	e1a03000 	mov	r3, r0
    1e58:	e1a00003 	mov	r0, r3
    1e5c:	ebfff967 	bl	400 <ptarmUartOutputStr>
    1e60:	e51f050c 	ldr	r0, [pc, #-1292]	; 195c <main+0x1074>
    1e64:	ebfff965 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    1e68:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(l2, 1);
    1e6c:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    1e70:	e51f3514 	ldr	r3, [pc, #-1300]	; 1964 <main+0x107c>
    1e74:	e3a02000 	mov	r2, #0, 0
    1e78:	e5c3200c 	strb	r2, [r3, #12]
    1e7c:	e1a00000 	nop			; (mov r0, r0)
    1e80:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    1e84:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    1e88:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    1e8c:	e51f3534 	ldr	r3, [pc, #-1332]	; 1960 <main+0x1078>
    1e90:	e1a07003 	mov	r7, r3
    1e94:	e58d7038 	str	r7, [sp, #56]	; 0x38
    1e98:	e1a0300d 	mov	r3, sp
    1e9c:	e51f2540 	ldr	r2, [pc, #-1344]	; 1964 <main+0x107c>
    1ea0:	e5823010 	str	r3, [r2, #16]
    1ea4:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    1ea8:	e1a03007 	mov	r3, r7
    1eac:	e51f2550 	ldr	r2, [pc, #-1360]	; 1964 <main+0x107c>
    1eb0:	e5823014 	str	r3, [r2, #20]
    1eb4:	e51f3558 	ldr	r3, [pc, #-1368]	; 1964 <main+0x107c>
    1eb8:	e5933008 	ldr	r3, [r3, #8]
    1ebc:	e593300c 	ldr	r3, [r3, #12]
    1ec0:	e51f2564 	ldr	r2, [pc, #-1380]	; 1964 <main+0x107c>
    1ec4:	e5922008 	ldr	r2, [r2, #8]
    1ec8:	e5922008 	ldr	r2, [r2, #8]
    1ecc:	e1a0d003 	mov	sp, r3
    1ed0:	e1a0b002 	mov	fp, r2
    1ed4:	eafffcc9 	b	1200 <main+0x918>
    1ed8:	e51f34f0 	ldr	r3, [pc, #-1264]	; 19f0 <main+0x1108>
    1edc:	e5d33000 	ldrb	r3, [r3]
    1ee0:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1ee4:	e3530000 	cmp	r3, #0, 0
    1ee8:	1affffc5 	bne	1e04 <main+0x151c>
	}
}

l3: {
	while (loopForever) {
    1eec:	ea000034 	b	1fc4 <main+0x16dc>
		int i;
		for (i = 0; i < 2000000u; i++);
    1ef0:	e3a03000 	mov	r3, #0, 0
    1ef4:	e50b3030 	str	r3, [fp, #-48]	; 0x30
    1ef8:	ea000002 	b	1f08 <main+0x1620>
    1efc:	e51b3030 	ldr	r3, [fp, #-48]	; 0x30
    1f00:	e2833001 	add	r3, r3, #1, 0
    1f04:	e50b3030 	str	r3, [fp, #-48]	; 0x30
    1f08:	e51b2030 	ldr	r2, [fp, #-48]	; 0x30
    1f0c:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    1f10:	e2833e47 	add	r3, r3, #1136	; 0x470
    1f14:	e283300f 	add	r3, r3, #15, 0
    1f18:	e1520003 	cmp	r2, r3
    1f1c:	9afffff6 	bls	1efc <main+0x1614>

		PTARM_MUTEX_LOCK();
    1f20:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(l3.localScheduler->hwThreadId)); printf(":l3 pausing.\n");
    1f24:	e51f054c 	ldr	r0, [pc, #-1356]	; 19e0 <main+0x10f8>
    1f28:	ebfff934 	bl	400 <ptarmUartOutputStr>
    1f2c:	e51f35c4 	ldr	r3, [pc, #-1476]	; 1970 <main+0x1088>
    1f30:	e5933008 	ldr	r3, [r3, #8]
    1f34:	e5933004 	ldr	r3, [r3, #4]
    1f38:	e1a00003 	mov	r0, r3
    1f3c:	ebfff942 	bl	44c <itoa>
    1f40:	e1a03000 	mov	r3, r0
    1f44:	e1a00003 	mov	r0, r3
    1f48:	ebfff92c 	bl	400 <ptarmUartOutputStr>
    1f4c:	e51f05ec 	ldr	r0, [pc, #-1516]	; 1968 <main+0x1080>
    1f50:	ebfff92a 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    1f54:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(l3, 1);
    1f58:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    1f5c:	e51f35f4 	ldr	r3, [pc, #-1524]	; 1970 <main+0x1088>
    1f60:	e3a02000 	mov	r2, #0, 0
    1f64:	e5c3200c 	strb	r2, [r3, #12]
    1f68:	e1a00000 	nop			; (mov r0, r0)
    1f6c:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    1f70:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    1f74:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    1f78:	e51f3614 	ldr	r3, [pc, #-1556]	; 196c <main+0x1084>
    1f7c:	e1a07003 	mov	r7, r3
    1f80:	e58d7038 	str	r7, [sp, #56]	; 0x38
    1f84:	e1a0300d 	mov	r3, sp
    1f88:	e51f2620 	ldr	r2, [pc, #-1568]	; 1970 <main+0x1088>
    1f8c:	e5823010 	str	r3, [r2, #16]
    1f90:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    1f94:	e1a03007 	mov	r3, r7
    1f98:	e51f2630 	ldr	r2, [pc, #-1584]	; 1970 <main+0x1088>
    1f9c:	e5823014 	str	r3, [r2, #20]
    1fa0:	e51f3638 	ldr	r3, [pc, #-1592]	; 1970 <main+0x1088>
    1fa4:	e5933008 	ldr	r3, [r3, #8]
    1fa8:	e593300c 	ldr	r3, [r3, #12]
    1fac:	e51f2644 	ldr	r2, [pc, #-1604]	; 1970 <main+0x1088>
    1fb0:	e5922008 	ldr	r2, [r2, #8]
    1fb4:	e5922008 	ldr	r2, [r2, #8]
    1fb8:	e1a0d003 	mov	sp, r3
    1fbc:	e1a0b002 	mov	fp, r2
    1fc0:	eafffc8e 	b	1200 <main+0x918>
    1fc4:	e51f35dc 	ldr	r3, [pc, #-1500]	; 19f0 <main+0x1108>
    1fc8:	e5d33000 	ldrb	r3, [r3]
    1fcc:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    1fd0:	e3530000 	cmp	r3, #0, 0
    1fd4:	1affffc5 	bne	1ef0 <main+0x1608>
	}
}

l4: {
	while (loopForever) {
    1fd8:	ea000034 	b	20b0 <main+0x17c8>
		int i;
		for (i = 0; i < 2000000u; i++);
    1fdc:	e3a03000 	mov	r3, #0, 0
    1fe0:	e50b3034 	str	r3, [fp, #-52]	; 0x34
    1fe4:	ea000002 	b	1ff4 <main+0x170c>
    1fe8:	e51b3034 	ldr	r3, [fp, #-52]	; 0x34
    1fec:	e2833001 	add	r3, r3, #1, 0
    1ff0:	e50b3034 	str	r3, [fp, #-52]	; 0x34
    1ff4:	e51b2034 	ldr	r2, [fp, #-52]	; 0x34
    1ff8:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    1ffc:	e2833e47 	add	r3, r3, #1136	; 0x470
    2000:	e283300f 	add	r3, r3, #15, 0
    2004:	e1520003 	cmp	r2, r3
    2008:	9afffff6 	bls	1fe8 <main+0x1700>

		PTARM_MUTEX_LOCK();
    200c:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(l4.localScheduler->hwThreadId)); printf(":l4 pausing.\n");
    2010:	e51f0638 	ldr	r0, [pc, #-1592]	; 19e0 <main+0x10f8>
    2014:	ebfff8f9 	bl	400 <ptarmUartOutputStr>
    2018:	e51f36a4 	ldr	r3, [pc, #-1700]	; 197c <main+0x1094>
    201c:	e5933008 	ldr	r3, [r3, #8]
    2020:	e5933004 	ldr	r3, [r3, #4]
    2024:	e1a00003 	mov	r0, r3
    2028:	ebfff907 	bl	44c <itoa>
    202c:	e1a03000 	mov	r3, r0
    2030:	e1a00003 	mov	r0, r3
    2034:	ebfff8f1 	bl	400 <ptarmUartOutputStr>
    2038:	e51f06cc 	ldr	r0, [pc, #-1740]	; 1974 <main+0x108c>
    203c:	ebfff8ef 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    2040:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(l4, 1);
    2044:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    2048:	e51f36d4 	ldr	r3, [pc, #-1748]	; 197c <main+0x1094>
    204c:	e3a02000 	mov	r2, #0, 0
    2050:	e5c3200c 	strb	r2, [r3, #12]
    2054:	e1a00000 	nop			; (mov r0, r0)
    2058:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    205c:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    2060:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    2064:	e51f36f4 	ldr	r3, [pc, #-1780]	; 1978 <main+0x1090>
    2068:	e1a07003 	mov	r7, r3
    206c:	e58d7038 	str	r7, [sp, #56]	; 0x38
    2070:	e1a0300d 	mov	r3, sp
    2074:	e51f2700 	ldr	r2, [pc, #-1792]	; 197c <main+0x1094>
    2078:	e5823010 	str	r3, [r2, #16]
    207c:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    2080:	e1a03007 	mov	r3, r7
    2084:	e51f2710 	ldr	r2, [pc, #-1808]	; 197c <main+0x1094>
    2088:	e5823014 	str	r3, [r2, #20]
    208c:	e51f3718 	ldr	r3, [pc, #-1816]	; 197c <main+0x1094>
    2090:	e5933008 	ldr	r3, [r3, #8]
    2094:	e593300c 	ldr	r3, [r3, #12]
    2098:	e51f2724 	ldr	r2, [pc, #-1828]	; 197c <main+0x1094>
    209c:	e5922008 	ldr	r2, [r2, #8]
    20a0:	e5922008 	ldr	r2, [r2, #8]
    20a4:	e1a0d003 	mov	sp, r3
    20a8:	e1a0b002 	mov	fp, r2
    20ac:	eafffc53 	b	1200 <main+0x918>
    20b0:	e51f36c8 	ldr	r3, [pc, #-1736]	; 19f0 <main+0x1108>
    20b4:	e5d33000 	ldrb	r3, [r3]
    20b8:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    20bc:	e3530000 	cmp	r3, #0, 0
    20c0:	1affffc5 	bne	1fdc <main+0x16f4>
	}
}

// Mission critical
m1: {
	while (loopForever) {
    20c4:	ea000034 	b	219c <main+0x18b4>
		int i;
		for (i = 0; i < 2000000u; i++);
    20c8:	e3a03000 	mov	r3, #0, 0
    20cc:	e50b3038 	str	r3, [fp, #-56]	; 0x38
    20d0:	ea000002 	b	20e0 <main+0x17f8>
    20d4:	e51b3038 	ldr	r3, [fp, #-56]	; 0x38
    20d8:	e2833001 	add	r3, r3, #1, 0
    20dc:	e50b3038 	str	r3, [fp, #-56]	; 0x38
    20e0:	e51b2038 	ldr	r2, [fp, #-56]	; 0x38
    20e4:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    20e8:	e2833e47 	add	r3, r3, #1136	; 0x470
    20ec:	e283300f 	add	r3, r3, #15, 0
    20f0:	e1520003 	cmp	r2, r3
    20f4:	9afffff6 	bls	20d4 <main+0x17ec>
		
		PTARM_MUTEX_LOCK();
    20f8:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(m1.localScheduler->hwThreadId)); printf(":m1 pausing.\n");
    20fc:	e51f0724 	ldr	r0, [pc, #-1828]	; 19e0 <main+0x10f8>
    2100:	ebfff8be 	bl	400 <ptarmUartOutputStr>
    2104:	e51f3784 	ldr	r3, [pc, #-1924]	; 1988 <main+0x10a0>
    2108:	e5933008 	ldr	r3, [r3, #8]
    210c:	e5933004 	ldr	r3, [r3, #4]
    2110:	e1a00003 	mov	r0, r3
    2114:	ebfff8cc 	bl	44c <itoa>
    2118:	e1a03000 	mov	r3, r0
    211c:	e1a00003 	mov	r0, r3
    2120:	ebfff8b6 	bl	400 <ptarmUartOutputStr>
    2124:	e51f07ac 	ldr	r0, [pc, #-1964]	; 1980 <main+0x1098>
    2128:	ebfff8b4 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    212c:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(m1, 1);
    2130:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    2134:	e51f37b4 	ldr	r3, [pc, #-1972]	; 1988 <main+0x10a0>
    2138:	e3a02000 	mov	r2, #0, 0
    213c:	e5c3200c 	strb	r2, [r3, #12]
    2140:	e1a00000 	nop			; (mov r0, r0)
    2144:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    2148:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    214c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    2150:	e51f37d4 	ldr	r3, [pc, #-2004]	; 1984 <main+0x109c>
    2154:	e1a07003 	mov	r7, r3
    2158:	e58d7038 	str	r7, [sp, #56]	; 0x38
    215c:	e1a0300d 	mov	r3, sp
    2160:	e51f27e0 	ldr	r2, [pc, #-2016]	; 1988 <main+0x10a0>
    2164:	e5823010 	str	r3, [r2, #16]
    2168:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    216c:	e1a03007 	mov	r3, r7
    2170:	e51f27f0 	ldr	r2, [pc, #-2032]	; 1988 <main+0x10a0>
    2174:	e5823014 	str	r3, [r2, #20]
    2178:	e51f37f8 	ldr	r3, [pc, #-2040]	; 1988 <main+0x10a0>
    217c:	e5933008 	ldr	r3, [r3, #8]
    2180:	e593300c 	ldr	r3, [r3, #12]
    2184:	e51f2804 	ldr	r2, [pc, #-2052]	; 1988 <main+0x10a0>
    2188:	e5922008 	ldr	r2, [r2, #8]
    218c:	e5922008 	ldr	r2, [r2, #8]
    2190:	e1a0d003 	mov	sp, r3
    2194:	e1a0b002 	mov	fp, r2
    2198:	eafffc18 	b	1200 <main+0x918>
    219c:	e51f37b4 	ldr	r3, [pc, #-1972]	; 19f0 <main+0x1108>
    21a0:	e5d33000 	ldrb	r3, [r3]
    21a4:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    21a8:	e3530000 	cmp	r3, #0, 0
    21ac:	1affffc5 	bne	20c8 <main+0x17e0>
	}
}
	
m2: {
	while (loopForever) {
    21b0:	ea00005e 	b	2330 <main+0x1a48>
		int index;
		for (index = 0; index < FOREMC_BUFFER_READ_COUNT(bufferOne); index++) {
    21b4:	e3a03000 	mov	r3, #0, 0
    21b8:	e50b303c 	str	r3, [fp, #-60]	; 0x3c
    21bc:	ea000021 	b	2248 <main+0x1960>
			PTARM_MUTEX_LOCK();
    21c0:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
			printf(utoa(FOREMC_BUFFER_READ_COUNT(bufferOne))); printf(","); printf(utoa(FOREMC_BUFFER_AT_INDEX(bufferOne, index))); printf("\n");
    21c4:	e51f3838 	ldr	r3, [pc, #-2104]	; 1994 <main+0x10ac>
    21c8:	e5933194 	ldr	r3, [r3, #404]	; 0x194
    21cc:	e1a00003 	mov	r0, r3
    21d0:	ebfff8e2 	bl	560 <utoa>
    21d4:	e1a03000 	mov	r3, r0
    21d8:	e1a00003 	mov	r0, r3
    21dc:	ebfff887 	bl	400 <ptarmUartOutputStr>
    21e0:	e51f085c 	ldr	r0, [pc, #-2140]	; 198c <main+0x10a4>
    21e4:	ebfff885 	bl	400 <ptarmUartOutputStr>
    21e8:	e51f385c 	ldr	r3, [pc, #-2140]	; 1994 <main+0x10ac>
    21ec:	e5932190 	ldr	r2, [r3, #400]	; 0x190
    21f0:	e51b303c 	ldr	r3, [fp, #-60]	; 0x3c
    21f4:	e0823003 	add	r3, r2, r3
    21f8:	e1a02003 	mov	r2, r3
    21fc:	e51f3870 	ldr	r3, [pc, #-2160]	; 1994 <main+0x10ac>
    2200:	e59331a0 	ldr	r3, [r3, #416]	; 0x1a0
    2204:	e1a01003 	mov	r1, r3
    2208:	e1a00002 	mov	r0, r2
    220c:	ebfff9a0 	bl	894 <foreMcGetIndex>
    2210:	e1a02000 	mov	r2, r0
    2214:	e51f3888 	ldr	r3, [pc, #-2184]	; 1994 <main+0x10ac>
    2218:	e7933102 	ldr	r3, [r3, r2, lsl #2]
    221c:	e1a00003 	mov	r0, r3
    2220:	ebfff8ce 	bl	560 <utoa>
    2224:	e1a03000 	mov	r3, r0
    2228:	e1a00003 	mov	r0, r3
    222c:	ebfff873 	bl	400 <ptarmUartOutputStr>
    2230:	e51f08a8 	ldr	r0, [pc, #-2216]	; 1990 <main+0x10a8>
    2234:	ebfff871 	bl	400 <ptarmUartOutputStr>
			PTARM_MUTEX_UNLOCK();
    2238:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
    223c:	e51b303c 	ldr	r3, [fp, #-60]	; 0x3c
    2240:	e2833001 	add	r3, r3, #1, 0
    2244:	e50b303c 	str	r3, [fp, #-60]	; 0x3c
    2248:	e51f38bc 	ldr	r3, [pc, #-2236]	; 1994 <main+0x10ac>
    224c:	e5932194 	ldr	r2, [r3, #404]	; 0x194
    2250:	e51b303c 	ldr	r3, [fp, #-60]	; 0x3c
    2254:	e1520003 	cmp	r2, r3
    2258:	caffffd8 	bgt	21c0 <main+0x18d8>
		}
		
		int i;
		for (i = 0; i < 2000000u; i++);
    225c:	e3a03000 	mov	r3, #0, 0
    2260:	e50b3040 	str	r3, [fp, #-64]	; 0x40
    2264:	ea000002 	b	2274 <main+0x198c>
    2268:	e51b3040 	ldr	r3, [fp, #-64]	; 0x40
    226c:	e2833001 	add	r3, r3, #1, 0
    2270:	e50b3040 	str	r3, [fp, #-64]	; 0x40
    2274:	e51b2040 	ldr	r2, [fp, #-64]	; 0x40
    2278:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    227c:	e2833e47 	add	r3, r3, #1136	; 0x470
    2280:	e283300f 	add	r3, r3, #15, 0
    2284:	e1520003 	cmp	r2, r3
    2288:	9afffff6 	bls	2268 <main+0x1980>
		
		PTARM_MUTEX_LOCK();
    228c:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(m2.localScheduler->hwThreadId)); printf(":m2 pausing.\n");
    2290:	e51f08b8 	ldr	r0, [pc, #-2232]	; 19e0 <main+0x10f8>
    2294:	ebfff859 	bl	400 <ptarmUartOutputStr>
    2298:	e51f3900 	ldr	r3, [pc, #-2304]	; 19a0 <main+0x10b8>
    229c:	e5933008 	ldr	r3, [r3, #8]
    22a0:	e5933004 	ldr	r3, [r3, #4]
    22a4:	e1a00003 	mov	r0, r3
    22a8:	ebfff867 	bl	44c <itoa>
    22ac:	e1a03000 	mov	r3, r0
    22b0:	e1a00003 	mov	r0, r3
    22b4:	ebfff851 	bl	400 <ptarmUartOutputStr>
    22b8:	e51f0928 	ldr	r0, [pc, #-2344]	; 1998 <main+0x10b0>
    22bc:	ebfff84f 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    22c0:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(m2, 1);
    22c4:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    22c8:	e51f3930 	ldr	r3, [pc, #-2352]	; 19a0 <main+0x10b8>
    22cc:	e3a02000 	mov	r2, #0, 0
    22d0:	e5c3200c 	strb	r2, [r3, #12]
    22d4:	e1a00000 	nop			; (mov r0, r0)
    22d8:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    22dc:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    22e0:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    22e4:	e51f3950 	ldr	r3, [pc, #-2384]	; 199c <main+0x10b4>
    22e8:	e1a07003 	mov	r7, r3
    22ec:	e58d7038 	str	r7, [sp, #56]	; 0x38
    22f0:	e1a0300d 	mov	r3, sp
    22f4:	e51f295c 	ldr	r2, [pc, #-2396]	; 19a0 <main+0x10b8>
    22f8:	e5823010 	str	r3, [r2, #16]
    22fc:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    2300:	e1a03007 	mov	r3, r7
    2304:	e51f296c 	ldr	r2, [pc, #-2412]	; 19a0 <main+0x10b8>
    2308:	e5823014 	str	r3, [r2, #20]
    230c:	e51f3974 	ldr	r3, [pc, #-2420]	; 19a0 <main+0x10b8>
    2310:	e5933008 	ldr	r3, [r3, #8]
    2314:	e593300c 	ldr	r3, [r3, #12]
    2318:	e51f2980 	ldr	r2, [pc, #-2432]	; 19a0 <main+0x10b8>
    231c:	e5922008 	ldr	r2, [r2, #8]
    2320:	e5922008 	ldr	r2, [r2, #8]
    2324:	e1a0d003 	mov	sp, r3
    2328:	e1a0b002 	mov	fp, r2
    232c:	eafffbb3 	b	1200 <main+0x918>
    2330:	e51f3948 	ldr	r3, [pc, #-2376]	; 19f0 <main+0x1108>
    2334:	e5d33000 	ldrb	r3, [r3]
    2338:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    233c:	e3530000 	cmp	r3, #0, 0
    2340:	1affff9b 	bne	21b4 <main+0x18cc>
	}
}
	
m3: {
	while (loopForever) {
    2344:	ea000034 	b	241c <main+0x1b34>
		int i;
		for (i = 0; i < 2000000u; i++);
    2348:	e3a03000 	mov	r3, #0, 0
    234c:	e50b3044 	str	r3, [fp, #-68]	; 0x44
    2350:	ea000002 	b	2360 <main+0x1a78>
    2354:	e51b3044 	ldr	r3, [fp, #-68]	; 0x44
    2358:	e2833001 	add	r3, r3, #1, 0
    235c:	e50b3044 	str	r3, [fp, #-68]	; 0x44
    2360:	e51b2044 	ldr	r2, [fp, #-68]	; 0x44
    2364:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    2368:	e2833e47 	add	r3, r3, #1136	; 0x470
    236c:	e283300f 	add	r3, r3, #15, 0
    2370:	e1520003 	cmp	r2, r3
    2374:	9afffff6 	bls	2354 <main+0x1a6c>
		
		PTARM_MUTEX_LOCK();
    2378:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(m3.localScheduler->hwThreadId)); printf(":m3 pausing.\n");
    237c:	e51f09a4 	ldr	r0, [pc, #-2468]	; 19e0 <main+0x10f8>
    2380:	ebfff81e 	bl	400 <ptarmUartOutputStr>
    2384:	e51f39e0 	ldr	r3, [pc, #-2528]	; 19ac <main+0x10c4>
    2388:	e5933008 	ldr	r3, [r3, #8]
    238c:	e5933004 	ldr	r3, [r3, #4]
    2390:	e1a00003 	mov	r0, r3
    2394:	ebfff82c 	bl	44c <itoa>
    2398:	e1a03000 	mov	r3, r0
    239c:	e1a00003 	mov	r0, r3
    23a0:	ebfff816 	bl	400 <ptarmUartOutputStr>
    23a4:	e51f0a08 	ldr	r0, [pc, #-2568]	; 19a4 <main+0x10bc>
    23a8:	ebfff814 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    23ac:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(m3, 1);
    23b0:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    23b4:	e51f3a10 	ldr	r3, [pc, #-2576]	; 19ac <main+0x10c4>
    23b8:	e3a02000 	mov	r2, #0, 0
    23bc:	e5c3200c 	strb	r2, [r3, #12]
    23c0:	e1a00000 	nop			; (mov r0, r0)
    23c4:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    23c8:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    23cc:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    23d0:	e51f3a30 	ldr	r3, [pc, #-2608]	; 19a8 <main+0x10c0>
    23d4:	e1a07003 	mov	r7, r3
    23d8:	e58d7038 	str	r7, [sp, #56]	; 0x38
    23dc:	e1a0300d 	mov	r3, sp
    23e0:	e51f2a3c 	ldr	r2, [pc, #-2620]	; 19ac <main+0x10c4>
    23e4:	e5823010 	str	r3, [r2, #16]
    23e8:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    23ec:	e1a03007 	mov	r3, r7
    23f0:	e51f2a4c 	ldr	r2, [pc, #-2636]	; 19ac <main+0x10c4>
    23f4:	e5823014 	str	r3, [r2, #20]
    23f8:	e51f3a54 	ldr	r3, [pc, #-2644]	; 19ac <main+0x10c4>
    23fc:	e5933008 	ldr	r3, [r3, #8]
    2400:	e593300c 	ldr	r3, [r3, #12]
    2404:	e51f2a60 	ldr	r2, [pc, #-2656]	; 19ac <main+0x10c4>
    2408:	e5922008 	ldr	r2, [r2, #8]
    240c:	e5922008 	ldr	r2, [r2, #8]
    2410:	e1a0d003 	mov	sp, r3
    2414:	e1a0b002 	mov	fp, r2
    2418:	eafffb78 	b	1200 <main+0x918>
    241c:	e51f3a34 	ldr	r3, [pc, #-2612]	; 19f0 <main+0x1108>
    2420:	e5d33000 	ldrb	r3, [r3]
    2424:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    2428:	e3530000 	cmp	r3, #0, 0
    242c:	1affffc5 	bne	2348 <main+0x1a60>
	}
}
	
m4: {
	while (loopForever) {
    2430:	ea000034 	b	2508 <main+0x1c20>
		int i;
		for (i = 0; i < 2000000u; i++);
    2434:	e3a03000 	mov	r3, #0, 0
    2438:	e50b3048 	str	r3, [fp, #-72]	; 0x48
    243c:	ea000002 	b	244c <main+0x1b64>
    2440:	e51b3048 	ldr	r3, [fp, #-72]	; 0x48
    2444:	e2833001 	add	r3, r3, #1, 0
    2448:	e50b3048 	str	r3, [fp, #-72]	; 0x48
    244c:	e51b2048 	ldr	r2, [fp, #-72]	; 0x48
    2450:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    2454:	e2833e47 	add	r3, r3, #1136	; 0x470
    2458:	e283300f 	add	r3, r3, #15, 0
    245c:	e1520003 	cmp	r2, r3
    2460:	9afffff6 	bls	2440 <main+0x1b58>
		
		PTARM_MUTEX_LOCK();
    2464:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(m4.localScheduler->hwThreadId)); printf(":m4 pausing.\n");
    2468:	e51f0a90 	ldr	r0, [pc, #-2704]	; 19e0 <main+0x10f8>
    246c:	ebfff7e3 	bl	400 <ptarmUartOutputStr>
    2470:	e51f3ac0 	ldr	r3, [pc, #-2752]	; 19b8 <main+0x10d0>
    2474:	e5933008 	ldr	r3, [r3, #8]
    2478:	e5933004 	ldr	r3, [r3, #4]
    247c:	e1a00003 	mov	r0, r3
    2480:	ebfff7f1 	bl	44c <itoa>
    2484:	e1a03000 	mov	r3, r0
    2488:	e1a00003 	mov	r0, r3
    248c:	ebfff7db 	bl	400 <ptarmUartOutputStr>
    2490:	e51f0ae8 	ldr	r0, [pc, #-2792]	; 19b0 <main+0x10c8>
    2494:	ebfff7d9 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    2498:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(m4, 1);
    249c:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    24a0:	e51f3af0 	ldr	r3, [pc, #-2800]	; 19b8 <main+0x10d0>
    24a4:	e3a02000 	mov	r2, #0, 0
    24a8:	e5c3200c 	strb	r2, [r3, #12]
    24ac:	e1a00000 	nop			; (mov r0, r0)
    24b0:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    24b4:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    24b8:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    24bc:	e51f3b10 	ldr	r3, [pc, #-2832]	; 19b4 <main+0x10cc>
    24c0:	e1a07003 	mov	r7, r3
    24c4:	e58d7038 	str	r7, [sp, #56]	; 0x38
    24c8:	e1a0300d 	mov	r3, sp
    24cc:	e51f2b1c 	ldr	r2, [pc, #-2844]	; 19b8 <main+0x10d0>
    24d0:	e5823010 	str	r3, [r2, #16]
    24d4:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    24d8:	e1a03007 	mov	r3, r7
    24dc:	e51f2b2c 	ldr	r2, [pc, #-2860]	; 19b8 <main+0x10d0>
    24e0:	e5823014 	str	r3, [r2, #20]
    24e4:	e51f3b34 	ldr	r3, [pc, #-2868]	; 19b8 <main+0x10d0>
    24e8:	e5933008 	ldr	r3, [r3, #8]
    24ec:	e593300c 	ldr	r3, [r3, #12]
    24f0:	e51f2b40 	ldr	r2, [pc, #-2880]	; 19b8 <main+0x10d0>
    24f4:	e5922008 	ldr	r2, [r2, #8]
    24f8:	e5922008 	ldr	r2, [r2, #8]
    24fc:	e1a0d003 	mov	sp, r3
    2500:	e1a0b002 	mov	fp, r2
    2504:	eafffb3d 	b	1200 <main+0x918>
    2508:	e51f3b20 	ldr	r3, [pc, #-2848]	; 19f0 <main+0x1108>
    250c:	e5d33000 	ldrb	r3, [r3]
    2510:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    2514:	e3530000 	cmp	r3, #0, 0
    2518:	1affffc5 	bne	2434 <main+0x1b4c>
	}
}

// Non-critical
n1: {
	while (loopForever) {
    251c:	ea000034 	b	25f4 <main+0x1d0c>
		int i;
		for (i = 0; i < 2000000u; i++);
    2520:	e3a03000 	mov	r3, #0, 0
    2524:	e50b304c 	str	r3, [fp, #-76]	; 0x4c
    2528:	ea000002 	b	2538 <main+0x1c50>
    252c:	e51b304c 	ldr	r3, [fp, #-76]	; 0x4c
    2530:	e2833001 	add	r3, r3, #1, 0
    2534:	e50b304c 	str	r3, [fp, #-76]	; 0x4c
    2538:	e51b204c 	ldr	r2, [fp, #-76]	; 0x4c
    253c:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    2540:	e2833e47 	add	r3, r3, #1136	; 0x470
    2544:	e283300f 	add	r3, r3, #15, 0
    2548:	e1520003 	cmp	r2, r3
    254c:	9afffff6 	bls	252c <main+0x1c44>
		
		PTARM_MUTEX_LOCK();
    2550:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(n1.localScheduler->hwThreadId)); printf(":n1 pausing.\n");
    2554:	e51f0b7c 	ldr	r0, [pc, #-2940]	; 19e0 <main+0x10f8>
    2558:	ebfff7a8 	bl	400 <ptarmUartOutputStr>
    255c:	e51f3ba0 	ldr	r3, [pc, #-2976]	; 19c4 <main+0x10dc>
    2560:	e5933008 	ldr	r3, [r3, #8]
    2564:	e5933004 	ldr	r3, [r3, #4]
    2568:	e1a00003 	mov	r0, r3
    256c:	ebfff7b6 	bl	44c <itoa>
    2570:	e1a03000 	mov	r3, r0
    2574:	e1a00003 	mov	r0, r3
    2578:	ebfff7a0 	bl	400 <ptarmUartOutputStr>
    257c:	e51f0bc8 	ldr	r0, [pc, #-3016]	; 19bc <main+0x10d4>
    2580:	ebfff79e 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    2584:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(n1, 1);
    2588:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    258c:	e51f3bd0 	ldr	r3, [pc, #-3024]	; 19c4 <main+0x10dc>
    2590:	e3a02000 	mov	r2, #0, 0
    2594:	e5c3200c 	strb	r2, [r3, #12]
    2598:	e1a00000 	nop			; (mov r0, r0)
    259c:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    25a0:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    25a4:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    25a8:	e51f3bf0 	ldr	r3, [pc, #-3056]	; 19c0 <main+0x10d8>
    25ac:	e1a07003 	mov	r7, r3
    25b0:	e58d7038 	str	r7, [sp, #56]	; 0x38
    25b4:	e1a0300d 	mov	r3, sp
    25b8:	e51f2bfc 	ldr	r2, [pc, #-3068]	; 19c4 <main+0x10dc>
    25bc:	e5823010 	str	r3, [r2, #16]
    25c0:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    25c4:	e1a03007 	mov	r3, r7
    25c8:	e51f2c0c 	ldr	r2, [pc, #-3084]	; 19c4 <main+0x10dc>
    25cc:	e5823014 	str	r3, [r2, #20]
    25d0:	e51f3c14 	ldr	r3, [pc, #-3092]	; 19c4 <main+0x10dc>
    25d4:	e5933008 	ldr	r3, [r3, #8]
    25d8:	e593300c 	ldr	r3, [r3, #12]
    25dc:	e51f2c20 	ldr	r2, [pc, #-3104]	; 19c4 <main+0x10dc>
    25e0:	e5922008 	ldr	r2, [r2, #8]
    25e4:	e5922008 	ldr	r2, [r2, #8]
    25e8:	e1a0d003 	mov	sp, r3
    25ec:	e1a0b002 	mov	fp, r2
    25f0:	eafffb02 	b	1200 <main+0x918>
    25f4:	e51f3c0c 	ldr	r3, [pc, #-3084]	; 19f0 <main+0x1108>
    25f8:	e5d33000 	ldrb	r3, [r3]
    25fc:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    2600:	e3530000 	cmp	r3, #0, 0
    2604:	1affffc5 	bne	2520 <main+0x1c38>
	}
}
	
n2: {
	while (loopForever) {
    2608:	ea000034 	b	26e0 <main+0x1df8>
		int i;
		for (i = 0; i < 2000000u; i++);
    260c:	e3a03000 	mov	r3, #0, 0
    2610:	e50b3050 	str	r3, [fp, #-80]	; 0x50
    2614:	ea000002 	b	2624 <main+0x1d3c>
    2618:	e51b3050 	ldr	r3, [fp, #-80]	; 0x50
    261c:	e2833001 	add	r3, r3, #1, 0
    2620:	e50b3050 	str	r3, [fp, #-80]	; 0x50
    2624:	e51b2050 	ldr	r2, [fp, #-80]	; 0x50
    2628:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    262c:	e2833e47 	add	r3, r3, #1136	; 0x470
    2630:	e283300f 	add	r3, r3, #15, 0
    2634:	e1520003 	cmp	r2, r3
    2638:	9afffff6 	bls	2618 <main+0x1d30>
		
		PTARM_MUTEX_LOCK();
    263c:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(n2.localScheduler->hwThreadId)); printf(":n2 pausing.\n");
    2640:	e51f0c68 	ldr	r0, [pc, #-3176]	; 19e0 <main+0x10f8>
    2644:	ebfff76d 	bl	400 <ptarmUartOutputStr>
    2648:	e51f3c80 	ldr	r3, [pc, #-3200]	; 19d0 <main+0x10e8>
    264c:	e5933008 	ldr	r3, [r3, #8]
    2650:	e5933004 	ldr	r3, [r3, #4]
    2654:	e1a00003 	mov	r0, r3
    2658:	ebfff77b 	bl	44c <itoa>
    265c:	e1a03000 	mov	r3, r0
    2660:	e1a00003 	mov	r0, r3
    2664:	ebfff765 	bl	400 <ptarmUartOutputStr>
    2668:	e51f0ca8 	ldr	r0, [pc, #-3240]	; 19c8 <main+0x10e0>
    266c:	ebfff763 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    2670:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(n2, 1);
    2674:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    2678:	e51f3cb0 	ldr	r3, [pc, #-3248]	; 19d0 <main+0x10e8>
    267c:	e3a02000 	mov	r2, #0, 0
    2680:	e5c3200c 	strb	r2, [r3, #12]
    2684:	e1a00000 	nop			; (mov r0, r0)
    2688:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    268c:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    2690:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    2694:	e51f3cd0 	ldr	r3, [pc, #-3280]	; 19cc <main+0x10e4>
    2698:	e1a07003 	mov	r7, r3
    269c:	e58d7038 	str	r7, [sp, #56]	; 0x38
    26a0:	e1a0300d 	mov	r3, sp
    26a4:	e51f2cdc 	ldr	r2, [pc, #-3292]	; 19d0 <main+0x10e8>
    26a8:	e5823010 	str	r3, [r2, #16]
    26ac:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    26b0:	e1a03007 	mov	r3, r7
    26b4:	e51f2cec 	ldr	r2, [pc, #-3308]	; 19d0 <main+0x10e8>
    26b8:	e5823014 	str	r3, [r2, #20]
    26bc:	e51f3cf4 	ldr	r3, [pc, #-3316]	; 19d0 <main+0x10e8>
    26c0:	e5933008 	ldr	r3, [r3, #8]
    26c4:	e593300c 	ldr	r3, [r3, #12]
    26c8:	e51f2d00 	ldr	r2, [pc, #-3328]	; 19d0 <main+0x10e8>
    26cc:	e5922008 	ldr	r2, [r2, #8]
    26d0:	e5922008 	ldr	r2, [r2, #8]
    26d4:	e1a0d003 	mov	sp, r3
    26d8:	e1a0b002 	mov	fp, r2
    26dc:	eafffac7 	b	1200 <main+0x918>
    26e0:	e51f3cf8 	ldr	r3, [pc, #-3320]	; 19f0 <main+0x1108>
    26e4:	e5d33000 	ldrb	r3, [r3]
    26e8:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    26ec:	e3530000 	cmp	r3, #0, 0
    26f0:	1affffc5 	bne	260c <main+0x1d24>
	}
}
	
n3: {
	while (loopForever) {
    26f4:	ea000034 	b	27cc <main+0x1ee4>
		int i;
		for (i = 0; i < 2000000u; i++);
    26f8:	e3a03000 	mov	r3, #0, 0
    26fc:	e50b3054 	str	r3, [fp, #-84]	; 0x54
    2700:	ea000002 	b	2710 <main+0x1e28>
    2704:	e51b3054 	ldr	r3, [fp, #-84]	; 0x54
    2708:	e2833001 	add	r3, r3, #1, 0
    270c:	e50b3054 	str	r3, [fp, #-84]	; 0x54
    2710:	e51b2054 	ldr	r2, [fp, #-84]	; 0x54
    2714:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    2718:	e2833e47 	add	r3, r3, #1136	; 0x470
    271c:	e283300f 	add	r3, r3, #15, 0
    2720:	e1520003 	cmp	r2, r3
    2724:	9afffff6 	bls	2704 <main+0x1e1c>
		
		PTARM_MUTEX_LOCK();
    2728:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(n3.localScheduler->hwThreadId)); printf(":n3 pausing.\n");
    272c:	e51f0d54 	ldr	r0, [pc, #-3412]	; 19e0 <main+0x10f8>
    2730:	ebfff732 	bl	400 <ptarmUartOutputStr>
    2734:	e51f3d60 	ldr	r3, [pc, #-3424]	; 19dc <main+0x10f4>
    2738:	e5933008 	ldr	r3, [r3, #8]
    273c:	e5933004 	ldr	r3, [r3, #4]
    2740:	e1a00003 	mov	r0, r3
    2744:	ebfff740 	bl	44c <itoa>
    2748:	e1a03000 	mov	r3, r0
    274c:	e1a00003 	mov	r0, r3
    2750:	ebfff72a 	bl	400 <ptarmUartOutputStr>
    2754:	e51f0d88 	ldr	r0, [pc, #-3464]	; 19d4 <main+0x10ec>
    2758:	ebfff728 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    275c:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(n3, 1);
    2760:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    2764:	e51f3d90 	ldr	r3, [pc, #-3472]	; 19dc <main+0x10f4>
    2768:	e3a02000 	mov	r2, #0, 0
    276c:	e5c3200c 	strb	r2, [r3, #12]
    2770:	e1a00000 	nop			; (mov r0, r0)
    2774:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    2778:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    277c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    2780:	e51f3db0 	ldr	r3, [pc, #-3504]	; 19d8 <main+0x10f0>
    2784:	e1a07003 	mov	r7, r3
    2788:	e58d7038 	str	r7, [sp, #56]	; 0x38
    278c:	e1a0300d 	mov	r3, sp
    2790:	e51f2dbc 	ldr	r2, [pc, #-3516]	; 19dc <main+0x10f4>
    2794:	e5823010 	str	r3, [r2, #16]
    2798:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    279c:	e1a03007 	mov	r3, r7
    27a0:	e51f2dcc 	ldr	r2, [pc, #-3532]	; 19dc <main+0x10f4>
    27a4:	e5823014 	str	r3, [r2, #20]
    27a8:	e51f3dd4 	ldr	r3, [pc, #-3540]	; 19dc <main+0x10f4>
    27ac:	e5933008 	ldr	r3, [r3, #8]
    27b0:	e593300c 	ldr	r3, [r3, #12]
    27b4:	e51f2de0 	ldr	r2, [pc, #-3552]	; 19dc <main+0x10f4>
    27b8:	e5922008 	ldr	r2, [r2, #8]
    27bc:	e5922008 	ldr	r2, [r2, #8]
    27c0:	e1a0d003 	mov	sp, r3
    27c4:	e1a0b002 	mov	fp, r2
    27c8:	eafffa8c 	b	1200 <main+0x918>
    27cc:	e51f3de4 	ldr	r3, [pc, #-3556]	; 19f0 <main+0x1108>
    27d0:	e5d33000 	ldrb	r3, [r3]
    27d4:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    27d8:	e3530000 	cmp	r3, #0, 0
    27dc:	1affffc5 	bne	26f8 <main+0x1e10>
	}
}
	
n4: {
	while (loopForever) {
    27e0:	ea000034 	b	28b8 <main+0x1fd0>
		int i;
		for (i = 0; i < 2000000u; i++);
    27e4:	e3a03000 	mov	r3, #0, 0
    27e8:	e50b3058 	str	r3, [fp, #-88]	; 0x58
    27ec:	ea000002 	b	27fc <main+0x1f14>
    27f0:	e51b3058 	ldr	r3, [fp, #-88]	; 0x58
    27f4:	e2833001 	add	r3, r3, #1, 0
    27f8:	e50b3058 	str	r3, [fp, #-88]	; 0x58
    27fc:	e51b2058 	ldr	r2, [fp, #-88]	; 0x58
    2800:	e3a0397a 	mov	r3, #1998848	; 0x1e8000
    2804:	e2833e47 	add	r3, r3, #1136	; 0x470
    2808:	e283300f 	add	r3, r3, #15, 0
    280c:	e1520003 	cmp	r2, r3
    2810:	9afffff6 	bls	27f0 <main+0x1f08>
		
		PTARM_MUTEX_LOCK();
    2814:	ee170d20 	cdp	13, 1, cr0, cr7, cr0, {1}
		printf(" "); printf(itoa(n4.localScheduler->hwThreadId)); printf(":n4 pausing.\n");
    2818:	e51f0e40 	ldr	r0, [pc, #-3648]	; 19e0 <main+0x10f8>
    281c:	ebfff6f7 	bl	400 <ptarmUartOutputStr>
    2820:	e51f3e3c 	ldr	r3, [pc, #-3644]	; 19ec <main+0x1104>
    2824:	e5933008 	ldr	r3, [r3, #8]
    2828:	e5933004 	ldr	r3, [r3, #4]
    282c:	e1a00003 	mov	r0, r3
    2830:	ebfff705 	bl	44c <itoa>
    2834:	e1a03000 	mov	r3, r0
    2838:	e1a00003 	mov	r0, r3
    283c:	ebfff6ef 	bl	400 <ptarmUartOutputStr>
    2840:	e51f0e64 	ldr	r0, [pc, #-3684]	; 19e4 <main+0x10fc>
    2844:	ebfff6ed 	bl	400 <ptarmUartOutputStr>
		PTARM_MUTEX_UNLOCK();
    2848:	ee170d00 	cdp	13, 1, cr0, cr7, cr0, {0}
		PAUSE(n4, 1);
    284c:	ee300d00 	cdp	13, 3, cr0, cr0, cr0, {0}
    2850:	e51f3e6c 	ldr	r3, [pc, #-3692]	; 19ec <main+0x1104>
    2854:	e3a02000 	mov	r2, #0, 0
    2858:	e5c3200c 	strb	r2, [r3, #12]
    285c:	e1a00000 	nop			; (mov r0, r0)
    2860:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    2864:	e92d1fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
    2868:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    286c:	e51f3e8c 	ldr	r3, [pc, #-3724]	; 19e8 <main+0x1100>
    2870:	e1a07003 	mov	r7, r3
    2874:	e58d7038 	str	r7, [sp, #56]	; 0x38
    2878:	e1a0300d 	mov	r3, sp
    287c:	e51f2e98 	ldr	r2, [pc, #-3736]	; 19ec <main+0x1104>
    2880:	e5823010 	str	r3, [r2, #16]
    2884:	ee007c00 	cdp	12, 0, cr7, cr0, cr0, {0}
    2888:	e1a03007 	mov	r3, r7
    288c:	e51f2ea8 	ldr	r2, [pc, #-3752]	; 19ec <main+0x1104>
    2890:	e5823014 	str	r3, [r2, #20]
    2894:	e51f3eb0 	ldr	r3, [pc, #-3760]	; 19ec <main+0x1104>
    2898:	e5933008 	ldr	r3, [r3, #8]
    289c:	e593300c 	ldr	r3, [r3, #12]
    28a0:	e51f2ebc 	ldr	r2, [pc, #-3772]	; 19ec <main+0x1104>
    28a4:	e5922008 	ldr	r2, [r2, #8]
    28a8:	e5922008 	ldr	r2, [r2, #8]
    28ac:	e1a0d003 	mov	sp, r3
    28b0:	e1a0b002 	mov	fp, r2
    28b4:	eafffa51 	b	1200 <main+0x918>
    28b8:	e51f3ed0 	ldr	r3, [pc, #-3792]	; 19f0 <main+0x1108>
    28bc:	e5d33000 	ldrb	r3, [r3]
    28c0:	e20330ff 	and	r3, r3, #255, 0	; 0xff
    28c4:	e3530000 	cmp	r3, #0, 0
    28c8:	1affffc5 	bne	27e4 <main+0x1efc>
	}
}

	return 0;
    28cc:	e3a03000 	mov	r3, #0, 0
}
    28d0:	e1a00003 	mov	r0, r3
    28d4:	e24bd018 	sub	sp, fp, #24, 0
    28d8:	e8bd89f0 	pop	{r4, r5, r6, r7, r8, fp, pc}

Disassembly of section .text.memset:

00002b30 <memset>:
    2b30:	e3100003 	tst	r0, #3, 0
    2b34:	e92d4010 	push	{r4, lr}
    2b38:	0a000037 	beq	2c1c <memset+0xec>
    2b3c:	e3520000 	cmp	r2, #0, 0
    2b40:	e2422001 	sub	r2, r2, #1, 0
    2b44:	0a000032 	beq	2c14 <memset+0xe4>
    2b48:	e201c0ff 	and	ip, r1, #255, 0	; 0xff
    2b4c:	e1a03000 	mov	r3, r0
    2b50:	ea000002 	b	2b60 <memset+0x30>
    2b54:	e3520000 	cmp	r2, #0, 0
    2b58:	e2422001 	sub	r2, r2, #1, 0
    2b5c:	0a00002c 	beq	2c14 <memset+0xe4>
    2b60:	e4c3c001 	strb	ip, [r3], #1
    2b64:	e3130003 	tst	r3, #3, 0
    2b68:	1afffff9 	bne	2b54 <memset+0x24>
    2b6c:	e3520003 	cmp	r2, #3, 0
    2b70:	9a000020 	bls	2bf8 <memset+0xc8>
    2b74:	e201e0ff 	and	lr, r1, #255, 0	; 0xff
    2b78:	e18ee40e 	orr	lr, lr, lr, lsl #8
    2b7c:	e352000f 	cmp	r2, #15, 0
    2b80:	e18ee80e 	orr	lr, lr, lr, lsl #16
    2b84:	9a000010 	bls	2bcc <memset+0x9c>
    2b88:	e1a04002 	mov	r4, r2
    2b8c:	e283c010 	add	ip, r3, #16, 0
    2b90:	e2444010 	sub	r4, r4, #16, 0
    2b94:	e354000f 	cmp	r4, #15, 0
    2b98:	e50ce010 	str	lr, [ip, #-16]
    2b9c:	e50ce00c 	str	lr, [ip, #-12]
    2ba0:	e50ce008 	str	lr, [ip, #-8]
    2ba4:	e50ce004 	str	lr, [ip, #-4]
    2ba8:	e28cc010 	add	ip, ip, #16, 0
    2bac:	8afffff7 	bhi	2b90 <memset+0x60>
    2bb0:	e242c010 	sub	ip, r2, #16, 0
    2bb4:	e3ccc00f 	bic	ip, ip, #15, 0
    2bb8:	e202200f 	and	r2, r2, #15, 0
    2bbc:	e28cc010 	add	ip, ip, #16, 0
    2bc0:	e3520003 	cmp	r2, #3, 0
    2bc4:	e083300c 	add	r3, r3, ip
    2bc8:	9a00000a 	bls	2bf8 <memset+0xc8>
    2bcc:	e1a04003 	mov	r4, r3
    2bd0:	e1a0c002 	mov	ip, r2
    2bd4:	e24cc004 	sub	ip, ip, #4, 0
    2bd8:	e35c0003 	cmp	ip, #3, 0
    2bdc:	e484e004 	str	lr, [r4], #4
    2be0:	8afffffb 	bhi	2bd4 <memset+0xa4>
    2be4:	e242c004 	sub	ip, r2, #4, 0
    2be8:	e3ccc003 	bic	ip, ip, #3, 0
    2bec:	e28cc004 	add	ip, ip, #4, 0
    2bf0:	e083300c 	add	r3, r3, ip
    2bf4:	e2022003 	and	r2, r2, #3, 0
    2bf8:	e3520000 	cmp	r2, #0, 0
    2bfc:	120110ff 	andne	r1, r1, #255, 0	; 0xff
    2c00:	10832002 	addne	r2, r3, r2
    2c04:	0a000002 	beq	2c14 <memset+0xe4>
    2c08:	e4c31001 	strb	r1, [r3], #1
    2c0c:	e1530002 	cmp	r3, r2
    2c10:	1afffffc 	bne	2c08 <memset+0xd8>
    2c14:	e8bd4010 	pop	{r4, lr}
    2c18:	e1a0f00e 	mov	pc, lr
    2c1c:	e1a03000 	mov	r3, r0
    2c20:	eaffffd1 	b	2b6c <memset+0x3c>
