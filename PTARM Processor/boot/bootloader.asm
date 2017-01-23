
bootloader.elf:     file format elf32-littlearm


Disassembly of section .text:

00000000 <reset>:
   0:	ea000013 	b	54 <boot>

00000004 <undef>:
   4:	ea00001e 	b	84 <infloop>

00000008 <swi>:
   8:	ea00001d 	b	84 <infloop>

0000000c <pabt>:
   c:	ea00001c 	b	84 <infloop>

00000010 <dabt>:
  10:	ea00001b 	b	84 <infloop>
  14:	e1a00000 	nop			; (mov r0, r0)

00000018 <irq>:
  18:	ea000019 	b	84 <infloop>

0000001c <fiq>:
  1c:	ea000018 	b	84 <infloop>

00000020 <eoe>:
  20:	e1a00000 	nop			; (mov r0, r0)
  24:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
  28:	e52d1004 	push	{r1}		; (str r1, [sp, #-4]!)
  2c:	e52d2004 	push	{r2}		; (str r2, [sp, #-4]!)
  30:	ee001d00 	cdp	13, 0, cr1, cr0, cr0, {0}
  34:	e3a02004 	mov	r2, #4
  38:	e0010192 	mul	r1, r2, r1
  3c:	e59f200c 	ldr	r2, [pc, #12]	; 50 <eoe+0x30>
  40:	e081e002 	add	lr, r1, r2
  44:	e49d2004 	pop	{r2}		; (ldr r2, [sp], #4)
  48:	e49d1004 	pop	{r1}		; (ldr r1, [sp], #4)
  4c:	e59ef000 	ldr	pc, [lr]
  50:	0001ffe0 	andeq	pc, r1, r0, ror #31

00000054 <boot>:
  54:	e59f224c 	ldr	r2, [pc, #588]	; 2a8 <turn_off_leds+0x68>
  58:	e3a03000 	mov	r3, #0
  5c:	e5c23000 	strb	r3, [r2]
  60:	ee005d00 	cdp	13, 0, cr5, cr0, cr0, {0}
  64:	e3550000 	cmp	r5, #0
  68:	0a000010 	beq	b0 <uart_loader_start>

0000006c <wait_until_loaded>:
  6c:	e5d24000 	ldrb	r4, [r2]
  70:	e3540000 	cmp	r4, #0
  74:	0afffffc 	beq	6c <wait_until_loaded>
  78:	e1a0e00f 	mov	lr, pc
  7c:	e3a0f000 	mov	pc, #0
  80:	eafffff3 	b	54 <boot>

00000084 <infloop>:
  84:	eafffffe 	b	84 <infloop>

00000088 <start_msg>:
  88:	52415450 	subpl	r5, r1, #80, 8	; 0x50000000
  8c:	3035204d 	eorscc	r2, r5, sp, asr #32
  90:	207a684d 	rsbscs	r6, sl, sp, asr #16
  94:	65677545 	strbvs	r7, [r7, #-1349]!	; 0xfffffabb
  98:	3220656e 	eorcc	r6, r0, #461373440	; 0x1b800000
  9c:	754a2034 	strbvc	r2, [sl, #-52]	; 0xffffffcc
  a0:	3220656e 	eorcc	r6, r0, #461373440	; 0x1b800000
  a4:	0d363130 	ldfeqs	f3, [r6, #-192]!	; 0xffffff40
  a8:	07ff000a 	ldrbeq	r0, [pc, sl]!

000000aa <end_msg>:
  aa:	73a107ff 			; <UNDEFINED> instruction: 0x73a107ff
	...

000000b0 <uart_loader_start>:
  b0:	eb00004f 	bl	1f4 <uart_setup>
  b4:	e3a02021 	mov	r2, #33	; 0x21
  b8:	e59f31ec 	ldr	r3, [pc, #492]	; 2ac <turn_off_leds+0x6c>
  bc:	eb000038 	bl	1a4 <uart_send_seq>
  c0:	eb00005e 	bl	240 <turn_off_leds>

000000c4 <restart_loader>:
  c4:	e3e020f6 	mvn	r2, #246	; 0xf6
  c8:	e3a03001 	mov	r3, #1

000000cc <wait_command_loop>:
  cc:	e5823000 	str	r3, [r2]
  d0:	e1a03083 	lsl	r3, r3, #1
  d4:	e3130010 	tst	r3, #16
  d8:	13a03001 	movne	r3, #1
  dc:	e59f11cc 	ldr	r1, [pc, #460]	; 2b0 <turn_off_leds+0x70>
  e0:	eb00004f 	bl	224 <uart_receive_byte>
  e4:	e3510000 	cmp	r1, #0
  e8:	0afffff7 	beq	cc <wait_command_loop>
  ec:	e35000ff 	cmp	r0, #255	; 0xff
  f0:	0a000002 	beq	100 <send_ready_command>
  f4:	e59f11b4 	ldr	r1, [pc, #436]	; 2b0 <turn_off_leds+0x70>
  f8:	eb000042 	bl	208 <uart_send_byte>
  fc:	eafffff0 	b	c4 <restart_loader>

00000100 <send_ready_command>:
 100:	e3a000fe 	mov	r0, #254	; 0xfe
 104:	e59f11a4 	ldr	r1, [pc, #420]	; 2b0 <turn_off_leds+0x70>
 108:	eb00003e 	bl	208 <uart_send_byte>
 10c:	e3510000 	cmp	r1, #0
 110:	0affffeb 	beq	c4 <restart_loader>
 114:	e3a02000 	mov	r2, #0
 118:	e3a03018 	mov	r3, #24

0000011c <receive_size_loop>:
 11c:	e59f118c 	ldr	r1, [pc, #396]	; 2b0 <turn_off_leds+0x70>
 120:	eb00003f 	bl	224 <uart_receive_byte>
 124:	e3510000 	cmp	r1, #0
 128:	0affffe5 	beq	c4 <restart_loader>
 12c:	e1822310 	orr	r2, r2, r0, lsl r3
 130:	e2533008 	subs	r3, r3, #8
 134:	5afffff8 	bpl	11c <receive_size_loop>
 138:	e3a03000 	mov	r3, #0

0000013c <receive_prog_loop>:
 13c:	e59f116c 	ldr	r1, [pc, #364]	; 2b0 <turn_off_leds+0x70>
 140:	eb000037 	bl	224 <uart_receive_byte>
 144:	e3510000 	cmp	r1, #0
 148:	0affffdd 	beq	c4 <restart_loader>
 14c:	e4c30001 	strb	r0, [r3], #1
 150:	e2522001 	subs	r2, r2, #1
 154:	1afffff8 	bne	13c <receive_prog_loop>
 158:	eb000038 	bl	240 <turn_off_leds>
 15c:	e59f5144 	ldr	r5, [pc, #324]	; 2a8 <turn_off_leds+0x68>
 160:	e3a06001 	mov	r6, #1
 164:	e5c56000 	strb	r6, [r5]
 168:	eef00d00 	cdp	13, 15, cr0, cr0, cr0, {0}
 16c:	e1a0e00f 	mov	lr, pc
 170:	e3a0f000 	mov	pc, #0
 174:	eef40d25 	cdp	13, 15, cr0, cr4, cr5, {1}
 178:	e2444002 	sub	r4, r4, #2
 17c:	e2455002 	sub	r5, r5, #2
 180:	eb00001b 	bl	1f4 <uart_setup>
 184:	e3a02004 	mov	r2, #4
 188:	e59f3124 	ldr	r3, [pc, #292]	; 2b4 <turn_off_leds+0x74>
 18c:	eb000004 	bl	1a4 <uart_send_seq>
 190:	e1a02004 	mov	r2, r4
 194:	eb00000b 	bl	1c8 <uart_send_word>
 198:	e1a02005 	mov	r2, r5
 19c:	eb000009 	bl	1c8 <uart_send_word>
 1a0:	eaffffc7 	b	c4 <restart_loader>

000001a4 <uart_send_seq>:
 1a4:	e1a0600e 	mov	r6, lr

000001a8 <send_loop>:
 1a8:	e4d30001 	ldrb	r0, [r3], #1
 1ac:	e59f10fc 	ldr	r1, [pc, #252]	; 2b0 <turn_off_leds+0x70>
 1b0:	eb000014 	bl	208 <uart_send_byte>
 1b4:	e3510000 	cmp	r1, #0
 1b8:	0affffc1 	beq	c4 <restart_loader>
 1bc:	e2522001 	subs	r2, r2, #1
 1c0:	1afffff8 	bne	1a8 <send_loop>
 1c4:	e1a0f006 	mov	pc, r6

000001c8 <uart_send_word>:
 1c8:	e1a0600e 	mov	r6, lr
 1cc:	e3a03018 	mov	r3, #24

000001d0 <send_word_loop>:
 1d0:	e1a00332 	lsr	r0, r2, r3
 1d4:	e20000ff 	and	r0, r0, #255	; 0xff
 1d8:	e59f10d0 	ldr	r1, [pc, #208]	; 2b0 <turn_off_leds+0x70>
 1dc:	eb000009 	bl	208 <uart_send_byte>
 1e0:	e3510000 	cmp	r1, #0
 1e4:	0affffb6 	beq	c4 <restart_loader>
 1e8:	e2533008 	subs	r3, r3, #8
 1ec:	5afffff7 	bpl	1d0 <send_word_loop>
 1f0:	e1a0f006 	mov	pc, r6

000001f4 <uart_setup>:
 1f4:	e59f80bc 	ldr	r8, [pc, #188]	; 2b8 <turn_off_leds+0x78>
 1f8:	e59f90bc 	ldr	r9, [pc, #188]	; 2bc <turn_off_leds+0x7c>
 1fc:	e59fa0bc 	ldr	sl, [pc, #188]	; 2c0 <turn_off_leds+0x80>
 200:	e59fb0bc 	ldr	fp, [pc, #188]	; 2c4 <turn_off_leds+0x84>
 204:	e1a0f00e 	mov	pc, lr

00000208 <uart_send_byte>:
 208:	e5da7000 	ldrb	r7, [sl]
 20c:	e3570000 	cmp	r7, #0
 210:	05cb0000 	strbeq	r0, [fp]
 214:	01a0f00e 	moveq	pc, lr
 218:	e2511001 	subs	r1, r1, #1
 21c:	1afffff9 	bne	208 <uart_send_byte>
 220:	e1a0f00e 	mov	pc, lr

00000224 <uart_receive_byte>:
 224:	e5d87000 	ldrb	r7, [r8]
 228:	e3570001 	cmp	r7, #1
 22c:	05d90000 	ldrbeq	r0, [r9]
 230:	01a0f00e 	moveq	pc, lr
 234:	e2511001 	subs	r1, r1, #1
 238:	1afffff9 	bne	224 <uart_receive_byte>
 23c:	e1a0f00e 	mov	pc, lr

00000240 <turn_off_leds>:
 240:	e3a00000 	mov	r0, #0
 244:	e3e010f6 	mvn	r1, #246	; 0xf6
 248:	e5c10000 	strb	r0, [r1]
 24c:	e3e010ff 	mvn	r1, #255	; 0xff
 250:	e5c10000 	strb	r0, [r1]
 254:	e3e00000 	mvn	r0, #0
 258:	e3e010df 	mvn	r1, #223	; 0xdf
 25c:	e5c10000 	strb	r0, [r1]
 260:	e3e010d7 	mvn	r1, #215	; 0xd7
 264:	e5c10000 	strb	r0, [r1]
 268:	e3e010cf 	mvn	r1, #207	; 0xcf
 26c:	e5c10000 	strb	r0, [r1]
 270:	e3e010c7 	mvn	r1, #199	; 0xc7
 274:	e5c10000 	strb	r0, [r1]
 278:	e3e010bf 	mvn	r1, #191	; 0xbf
 27c:	e5c10000 	strb	r0, [r1]
 280:	e3e010b7 	mvn	r1, #183	; 0xb7
 284:	e5c10000 	strb	r0, [r1]
 288:	e3e010af 	mvn	r1, #175	; 0xaf
 28c:	e5c10000 	strb	r0, [r1]
 290:	e3e010a7 	mvn	r1, #167	; 0xa7
 294:	e5c10000 	strb	r0, [r1]
 298:	e3a00000 	mov	r0, #0
 29c:	e3e0109f 	mvn	r1, #159	; 0x9f
 2a0:	e5c10000 	strb	r0, [r1]
 2a4:	e1a0f00e 	mov	pc, lr
 2a8:	0001ffe0 	andeq	pc, r1, r0, ror #31
 2ac:	fffe0088 			; <UNDEFINED> instruction: 0xfffe0088
 2b0:	000d9fb9 			; <UNDEFINED> instruction: 0x000d9fb9
 2b4:	fffe00aa 			; <UNDEFINED> instruction: 0xfffe00aa
 2b8:	ffff0000 			; <UNDEFINED> instruction: 0xffff0000
 2bc:	ffff0004 			; <UNDEFINED> instruction: 0xffff0004
 2c0:	ffff0008 			; <UNDEFINED> instruction: 0xffff0008
 2c4:	ffff000c 			; <UNDEFINED> instruction: 0xffff000c

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00001641 	andeq	r1, r0, r1, asr #12
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	0000000c 	andeq	r0, r0, ip
  10:	06003405 	streq	r3, [r0], -r5, lsl #8
  14:	Address 0x00000014 is out of bounds.

