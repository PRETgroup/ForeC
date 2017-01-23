	.file	"sync_fft_che_top_tb.c"
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.text
.Ltext0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d\n"
	.text
	.p2align 4,,15
	.type	main.omp_fn.7, @function
main.omp_fn.7:
.LFB29:
	.file 1 "../../test/perftest/dp_802_11a/sync_fft_che_top_tb.c"
	.loc 1 205 0
	.cfi_startproc
.LVL0:
	pushq	%r15
.LCFI0:
	.cfi_def_cfa_offset 16
	pushq	%r14
.LCFI1:
	.cfi_def_cfa_offset 24
	pushq	%r13
.LCFI2:
	.cfi_def_cfa_offset 32
	pushq	%r12
.LCFI3:
	.cfi_def_cfa_offset 40
	pushq	%rbp
.LCFI4:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.LCFI5:
	.cfi_def_cfa_offset 56
	movq	%rdi, %rbx
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	subq	$72, %rsp
.LCFI6:
	.cfi_def_cfa_offset 128
	.loc 1 205 0
	movq	(%rdi), %rax
	movq	40(%rdi), %r13
	movq	32(%rdi), %r12
	movq	24(%rdi), %rbp
	movq	%rax, %rdi
.LVL1:
	movq	%rax, 40(%rsp)
	call	GOMP_stream_task_add_instance
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_read_view
	movq	40(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r13, %rsi
	movq	%rax, 16(%rsp)
	call	GOMP_stream_connect_view
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_read_view
	movq	40(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r12, %rsi
	movq	%rax, 24(%rsp)
	call	GOMP_stream_connect_view
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_read_view
	movq	40(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbp, %rsi
	movq	%rax, 32(%rsp)
	call	GOMP_stream_connect_view
	movq	40(%rsp), %rdi
	call	GOMP_stream_wait_until_connected
	.p2align 4,,10
	.p2align 3
.L7:
	movq	40(%rsp), %rdi
	leaq	56(%rsp), %rsi
	call	GOMP_stream_get_available_work
	testq	%rax, %rax
	movq	%rax, %rcx
	je	.L2
	movq	56(%rsp), %rax
	movq	56(%rsp), %rsi
	xorl	%r14d, %r14d
	movq	16(%rsp), %rdi
	movq	%rcx, (%rsp)
	addq	%rcx, %rax
	movq	%rax, %rdx
	movq	%rax, 8(%rsp)
	call	GOMP_stream_update
	movq	8(%rsp), %rdx
	movq	56(%rsp), %rsi
	movq	%rax, %r13
	movq	24(%rsp), %rdi
	.loc 1 218 0
	movq	%r13, %r15
	.loc 1 205 0
	call	GOMP_stream_update
	movq	8(%rsp), %rdx
	movq	56(%rsp), %rsi
	movq	%rax, %rbp
	movq	32(%rsp), %rdi
	call	GOMP_stream_update
	movq	(%rsp), %rcx
	movq	%rax, %r12
	cmpq	$128, %rcx
	je	.L4
	movq	%rcx, %r13
	.p2align 4,,10
	.p2align 3
.L8:
	.loc 1 213 0
	movq	48(%rbx), %rax
	movl	(%r12,%r14,8), %edx
	movl	$.LC0, %esi
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 214 0
	movq	56(%rbx), %rax
	movl	4(%r12,%r14,8), %edx
	movl	$.LC0, %esi
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 215 0
	movq	64(%rbx), %rax
	movl	0(%rbp,%r14,8), %edx
	movl	$.LC0, %esi
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 216 0
	movq	72(%rbx), %rax
	movl	4(%rbp,%r14,8), %edx
	movl	$.LC0, %esi
	.loc 1 218 0
	addq	$1, %r14
	.loc 1 216 0
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 217 0
	movq	80(%rbx), %rax
	movl	(%r15), %edx
	movl	$.LC0, %esi
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 218 0
	movq	88(%rbx), %rax
	movl	4(%r15), %edx
	movl	$.LC0, %esi
	addq	$8, %r15
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	cmpq	%r14, %r13
	ja	.L8
.L5:
	movq	8(%rsp), %rsi
	movq	16(%rsp), %rdi
	call	GOMP_stream_release
	movq	8(%rsp), %rsi
	movq	24(%rsp), %rdi
	call	GOMP_stream_release
	movq	8(%rsp), %rsi
	movq	32(%rsp), %rdi
	call	GOMP_stream_release
	jmp	.L7
	.p2align 4,,10
	.p2align 3
.L4:
	.loc 1 213 0
	movq	48(%rbx), %rax
	movl	(%r12,%r14), %edx
	movl	$.LC0, %esi
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 214 0
	movq	56(%rbx), %rax
	movl	4(%r12,%r14), %edx
	movl	$.LC0, %esi
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 215 0
	movq	64(%rbx), %rax
	movl	0(%rbp,%r14), %edx
	movl	$.LC0, %esi
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 216 0
	movq	72(%rbx), %rax
	movl	4(%rbp,%r14), %edx
	movl	$.LC0, %esi
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 217 0
	movq	80(%rbx), %rax
	movl	0(%r13,%r14), %edx
	movl	$.LC0, %esi
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 218 0
	movq	88(%rbx), %rax
	movl	4(%r13,%r14), %edx
	movl	$.LC0, %esi
	addq	$8, %r14
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	cmpq	$1024, %r14
	jne	.L4
	jmp	.L5
.L2:
	movq	40(%rsp), %rdi
	call	GOMP_stream_task_exit
	.loc 1 205 0
	addq	$72, %rsp
.LCFI7:
	.cfi_def_cfa_offset 56
	popq	%rbx
.LCFI8:
	.cfi_def_cfa_offset 48
.LVL2:
	popq	%rbp
.LCFI9:
	.cfi_def_cfa_offset 40
	popq	%r12
.LCFI10:
	.cfi_def_cfa_offset 32
	popq	%r13
.LCFI11:
	.cfi_def_cfa_offset 24
	popq	%r14
.LCFI12:
	.cfi_def_cfa_offset 16
	popq	%r15
.LCFI13:
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE29:
	.size	main.omp_fn.7, .-main.omp_fn.7
	.section	.rodata.str1.1
.LC1:
	.string	"%12f\n"
.LC2:
	.string	"%d \n"
	.text
	.p2align 4,,15
	.type	main.omp_fn.8, @function
main.omp_fn.8:
.LFB30:
	.loc 1 222 0
	.cfi_startproc
.LVL3:
	pushq	%r15
.LCFI14:
	.cfi_def_cfa_offset 16
	pushq	%r14
.LCFI15:
	.cfi_def_cfa_offset 24
	pushq	%r13
.LCFI16:
	.cfi_def_cfa_offset 32
	pushq	%r12
.LCFI17:
	.cfi_def_cfa_offset 40
	pushq	%rbp
.LCFI18:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.LCFI19:
	.cfi_def_cfa_offset 56
	movq	%rdi, %rbx
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	subq	$88, %rsp
.LCFI20:
	.cfi_def_cfa_offset 144
	.loc 1 222 0
	movq	(%rdi), %rax
	movq	32(%rdi), %r12
	movq	24(%rdi), %rbp
	movq	%rax, %rdi
.LVL4:
	movq	%rax, 40(%rsp)
	call	GOMP_stream_task_add_instance
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_read_view
	movq	40(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r12, %rsi
	movq	%rax, 24(%rsp)
	call	GOMP_stream_connect_view
	movl	$16, %esi
	movl	$16, %edi
	call	GOMP_stream_create_read_view
	movq	40(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbp, %rsi
	movq	%rax, 32(%rsp)
	call	GOMP_stream_connect_view
	movq	40(%rsp), %rdi
	call	GOMP_stream_wait_until_connected
	.p2align 4,,10
	.p2align 3
.L28:
	movq	40(%rsp), %rdi
	leaq	72(%rsp), %rsi
	call	GOMP_stream_get_available_work
	testq	%rax, %rax
	movq	%rax, %r14
	je	.L14
	movq	%rax, %r15
	addq	72(%rsp), %r15
	movq	72(%rsp), %rsi
	movq	24(%rsp), %rdi
	xorl	%ebp, %ebp
	movq	%r15, %rdx
	call	GOMP_stream_update
	movq	72(%rsp), %rsi
	movq	32(%rsp), %rdi
	movq	%r15, %rdx
	movq	%rax, %r12
	call	GOMP_stream_update
	cmpq	$128, %r14
	.loc 1 240 0
	movq	%rax, %r13
	.loc 1 222 0
	jne	.L40
	jmp	.L17
	.p2align 4,,10
	.p2align 3
.L19:
.LBB10:
	.loc 1 310 0
	addq	$1, %rbp
	addq	$16, %r13
	cmpq	%rbp, %r14
	jbe	.L18
.L40:
.LBE10:
	.loc 1 240 0
	cmpl	$1, (%r12,%rbp,8)
	jne	.L19
	.loc 1 245 0
	movq	40(%rbx), %rax
	movq	176(%rbx), %rsi
	movl	(%rax), %edi
	call	mark_GI_data1
	.loc 1 248 0
	movq	176(%rbx), %rax
	movl	(%rax), %edx
	testl	%edx, %edx
	jne	.L19
	.loc 1 250 0
	movq	40(%rbx), %rax
	.loc 1 252 0
	movq	56(%rbx), %rdx
	movl	$1, %edi
	movq	48(%rbx), %rsi
	.loc 1 250 0
	movl	$1, (%rax)
	.loc 1 252 0
	cvtsi2ss	4(%r13), %xmm1
	cvtsi2ss	0(%r13), %xmm0
	call	fft641
	.loc 1 255 0
	movq	48(%rbx), %rax
	movl	$.LC1, %esi
	movss	(%rax), %xmm0
	movq	184(%rbx), %rax
	cvtps2pd	%xmm0, %xmm0
	movq	(%rax), %rdi
	movl	$1, %eax
	call	fprintf
	.loc 1 256 0
	movq	56(%rbx), %rax
	movl	$.LC1, %esi
	movss	(%rax), %xmm0
	movq	192(%rbx), %rax
	cvtps2pd	%xmm0, %xmm0
	movq	(%rax), %rdi
	movl	$1, %eax
	call	fprintf
	.loc 1 260 0
	movq	56(%rbx), %rdi
	movq	48(%rbx), %rax
	movq	80(%rbx), %rcx
	movq	72(%rbx), %rdx
	movq	64(%rbx), %rsi
	movss	(%rdi), %xmm1
	movl	$1, %edi
	movss	(%rax), %xmm0
	call	mstream_demux1
	.loc 1 262 0
	movq	168(%rbx), %rax
	xorl	%edx, %edx
	movl	(%rax), %ecx
	cmpl	$62, %ecx
	jg	.L52
.LBB11:
	.loc 1 310 0
	addq	$1, %rbp
.LBE11:
	.loc 1 263 0
	addl	$1, %ecx
.LBB12:
	.loc 1 310 0
	addq	$16, %r13
	cmpq	%rbp, %r14
.LBE12:
	.loc 1 263 0
	movl	%ecx, (%rax)
.LBB13:
	.loc 1 310 0
	ja	.L40
	.p2align 4,,10
	.p2align 3
.L18:
	movq	24(%rsp), %rdi
	movq	%r15, %rsi
	call	GOMP_stream_release
	movq	32(%rsp), %rdi
	movq	%r15, %rsi
	call	GOMP_stream_release
	jmp	.L28
.L55:
.LBE13:
	.loc 1 245 0
	movq	40(%rbx), %rax
	movq	176(%rbx), %rsi
	movl	(%rax), %edi
	call	mark_GI_data1
	.loc 1 248 0
	movq	176(%rbx), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L29
	.loc 1 250 0
	movq	40(%rbx), %rax
	.loc 1 252 0
	movq	56(%rbx), %rdx
	movl	$1, %edi
	movq	48(%rbx), %rsi
	.loc 1 250 0
	movl	$1, (%rax)
	.loc 1 252 0
	cvtsi2ss	4(%r13,%rbp,2), %xmm1
	cvtsi2ss	0(%r13,%rbp,2), %xmm0
	call	fft641
	.loc 1 255 0
	movq	48(%rbx), %rax
	movl	$.LC1, %esi
	movss	(%rax), %xmm0
	movq	184(%rbx), %rax
	cvtps2pd	%xmm0, %xmm0
	movq	(%rax), %rdi
	movl	$1, %eax
	call	fprintf
	.loc 1 256 0
	movq	56(%rbx), %rax
	movl	$.LC1, %esi
	movss	(%rax), %xmm0
	movq	192(%rbx), %rax
	cvtps2pd	%xmm0, %xmm0
	movq	(%rax), %rdi
	movl	$1, %eax
	call	fprintf
	.loc 1 260 0
	movq	56(%rbx), %rdi
	movq	48(%rbx), %rax
	movq	72(%rbx), %rdx
	movq	80(%rbx), %rcx
	movq	64(%rbx), %rsi
	movss	(%rdi), %xmm1
	movl	$1, %edi
	movss	(%rax), %xmm0
	call	mstream_demux1
	.loc 1 262 0
	movq	168(%rbx), %rax
	movl	(%rax), %edx
	cmpl	$62, %edx
	jle	.L30
	xorl	%r14d, %r14d
	movq	%rbp, 48(%rsp)
	.p2align 4,,10
	.p2align 3
.L38:
.LBB14:
	.loc 1 271 0 discriminator 2
	movq	72(%rbx), %rax
	movslq	%r14d, %rbp
	movl	$.LC1, %esi
	.loc 1 270 0 discriminator 2
	addl	$1, %r14d
	.loc 1 271 0 discriminator 2
	movss	(%rax,%rbp,4), %xmm0
	movq	200(%rbx), %rax
	cvtps2pd	%xmm0, %xmm0
	movq	(%rax), %rdi
	movl	$1, %eax
	call	fprintf
	.loc 1 272 0 discriminator 2
	movq	80(%rbx), %rax
	movl	$.LC1, %esi
	movss	(%rax,%rbp,4), %xmm0
	movq	208(%rbx), %rax
	cvtps2pd	%xmm0, %xmm0
	movq	(%rax), %rdi
	movl	$1, %eax
	call	fprintf
.LVL5:
	.loc 1 270 0 discriminator 2
	cmpl	$64, %r14d
	jne	.L38
	.loc 1 276 0
	movq	128(%rbx), %r10
	movq	88(%rbx), %rax
	movq	96(%rbx), %rdx
	movq	120(%rbx), %r9
	movq	112(%rbx), %r8
	movq	104(%rbx), %rcx
	movl	(%r10), %r10d
	movq	80(%rbx), %rsi
	movq	72(%rbx), %rdi
	movq	48(%rsp), %rbp
	movl	%r10d, (%rsp)
	movss	(%rax), %xmm0
	call	scale_reorder_removeGB
	.loc 1 279 0
	movq	128(%rbx), %rax
	movl	(%rax), %edx
	cmpl	$3, %edx
	je	.L32
.L37:
	.loc 1 292 0
	cmpl	$2, %edx
	jg	.L33
	movq	168(%rbx), %rdx
.L35:
	.loc 1 306 0
	movl	$0, (%rdx)
	.loc 1 309 0
	movl	(%rax), %edx
	cmpl	$4, %edx
	jg	.L29
.LVL6:
.L30:
.LBE14:
	.loc 1 263 0
	addl	$1, %edx
	movl	%edx, (%rax)
	.p2align 4,,10
	.p2align 3
.L29:
	.loc 1 240 0
	addq	$8, %rbp
	cmpq	$1024, %rbp
	je	.L18
.L17:
	cmpl	$1, (%r12,%rbp)
	jne	.L29
	jmp	.L55
.LVL7:
.L33:
.LBB15:
	.loc 1 294 0
	movq	144(%rbx), %rcx
	movq	136(%rbx), %rdx
	movq	120(%rbx), %rsi
	movq	112(%rbx), %rdi
	movq	160(%rbx), %r9
	movq	152(%rbx), %r8
	call	channel_correction
	.loc 1 298 0
	movq	168(%rbx), %rax
	movl	$0, (%rax)
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L34:
	.loc 1 299 0
	movq	152(%rbx), %rdx
	cltq
	movl	$.LC2, %esi
	movl	(%rdx,%rax,4), %edx
	movq	232(%rbx), %rax
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 300 0
	movq	168(%rbx), %rdx
	movq	160(%rbx), %rax
	movl	$.LC2, %esi
	movslq	(%rdx), %rdx
	movl	(%rax,%rdx,4), %edx
	movq	240(%rbx), %rax
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 298 0
	movq	168(%rbx), %rdx
	movl	(%rdx), %eax
	addl	$1, %eax
	cmpl	$51, %eax
	movl	%eax, (%rdx)
	jle	.L34
	movq	128(%rbx), %rax
	jmp	.L35
.LVL8:
.L52:
	movq	%rbp, 48(%rsp)
	movq	%r13, 56(%rsp)
	movq	%rbx, %rbp
	movq	%r12, %r13
	movl	%edx, %ebx
.LVL9:
	.p2align 4,,10
	.p2align 3
.L41:
	.loc 1 271 0
	movq	72(%rbp), %rax
	movslq	%ebx, %r12
	movl	$.LC1, %esi
	.loc 1 270 0
	addl	$1, %ebx
	.loc 1 271 0
	movss	(%rax,%r12,4), %xmm0
	movq	200(%rbp), %rax
	cvtps2pd	%xmm0, %xmm0
	movq	(%rax), %rdi
	movl	$1, %eax
	call	fprintf
	.loc 1 272 0
	movq	80(%rbp), %rax
	movl	$.LC1, %esi
	movss	(%rax,%r12,4), %xmm0
	movq	208(%rbp), %rax
	cvtps2pd	%xmm0, %xmm0
	movq	(%rax), %rdi
	movl	$1, %eax
	call	fprintf
.LVL10:
	.loc 1 270 0
	cmpl	$64, %ebx
	jne	.L41
	movq	%rbp, %rbx
.LVL11:
	movq	%r13, %r12
	movq	48(%rsp), %rbp
.LVL12:
	.loc 1 276 0
	movq	128(%rbx), %r10
	movq	88(%rbx), %rax
	movq	96(%rbx), %rdx
	movq	120(%rbx), %r9
	movq	112(%rbx), %r8
	movq	104(%rbx), %rcx
	movl	(%r10), %r10d
	movq	80(%rbx), %rsi
	movq	72(%rbx), %rdi
	movq	56(%rsp), %r13
	movl	%r10d, (%rsp)
	movss	(%rax), %xmm0
	call	scale_reorder_removeGB
	.loc 1 279 0
	movq	128(%rbx), %rax
	movl	(%rax), %edx
	cmpl	$3, %edx
	je	.L54
.L22:
	.loc 1 292 0
	cmpl	$2, %edx
	jg	.L24
	movq	168(%rbx), %rdx
.L25:
	.loc 1 306 0
	movl	$0, (%rdx)
	.loc 1 309 0
	movl	(%rax), %edx
	cmpl	$4, %edx
	jg	.L19
	.loc 1 310 0
	addl	$1, %edx
	movl	%edx, (%rax)
	jmp	.L19
.L14:
	movq	40(%rsp), %rdi
	call	GOMP_stream_task_exit
.LBE15:
	.loc 1 222 0
	addq	$88, %rsp
	.cfi_remember_state
.LCFI21:
	.cfi_def_cfa_offset 56
	popq	%rbx
.LCFI22:
	.cfi_def_cfa_offset 48
.LVL13:
	popq	%rbp
.LCFI23:
	.cfi_def_cfa_offset 40
	popq	%r12
.LCFI24:
	.cfi_def_cfa_offset 32
	popq	%r13
.LCFI25:
	.cfi_def_cfa_offset 24
	popq	%r14
.LCFI26:
	.cfi_def_cfa_offset 16
	popq	%r15
.LCFI27:
	.cfi_def_cfa_offset 8
	ret
.LVL14:
.L32:
.LCFI28:
	.cfi_restore_state
.LBB16:
	.loc 1 281 0
	movq	144(%rbx), %rcx
	movq	136(%rbx), %rdx
	movq	104(%rbx), %rsi
	movq	96(%rbx), %rdi
	call	channel_estimation
	.loc 1 285 0
	movq	168(%rbx), %rax
	movl	$0, (%rax)
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L36:
	.loc 1 286 0
	movq	136(%rbx), %rdx
	cltq
	movl	$.LC2, %esi
	movl	(%rdx,%rax,4), %edx
	movq	216(%rbx), %rax
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 287 0
	movq	168(%rbx), %rdx
	movq	144(%rbx), %rax
	movl	$.LC2, %esi
	movslq	(%rdx), %rdx
	movl	(%rax,%rdx,4), %edx
	movq	224(%rbx), %rax
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 285 0
	movq	168(%rbx), %rdx
	movl	(%rdx), %eax
	addl	$1, %eax
	cmpl	$51, %eax
	movl	%eax, (%rdx)
	jle	.L36
	movq	128(%rbx), %rax
	movl	(%rax), %edx
	jmp	.L37
.LVL15:
.L24:
	.loc 1 294 0
	movq	144(%rbx), %rcx
	movq	136(%rbx), %rdx
	movq	120(%rbx), %rsi
	movq	112(%rbx), %rdi
	movq	160(%rbx), %r9
	movq	152(%rbx), %r8
	call	channel_correction
	.loc 1 298 0
	movq	168(%rbx), %rax
	movl	$0, (%rax)
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L26:
	.loc 1 299 0
	movq	152(%rbx), %rdx
	cltq
	movl	$.LC2, %esi
	movl	(%rdx,%rax,4), %edx
	movq	232(%rbx), %rax
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 300 0
	movq	168(%rbx), %rdx
	movq	160(%rbx), %rax
	movl	$.LC2, %esi
	movslq	(%rdx), %rdx
	movl	(%rax,%rdx,4), %edx
	movq	240(%rbx), %rax
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 298 0
	movq	168(%rbx), %rdx
	movl	(%rdx), %eax
	addl	$1, %eax
	cmpl	$51, %eax
	movl	%eax, (%rdx)
	jle	.L26
	movq	128(%rbx), %rax
	jmp	.L25
.L54:
	.loc 1 281 0
	movq	144(%rbx), %rcx
	movq	136(%rbx), %rdx
	movq	104(%rbx), %rsi
	movq	96(%rbx), %rdi
	call	channel_estimation
	.loc 1 285 0
	movq	168(%rbx), %rax
	movl	$0, (%rax)
	xorl	%eax, %eax
.L23:
	.loc 1 286 0
	movq	136(%rbx), %rdx
	cltq
	movl	$.LC2, %esi
	movl	(%rdx,%rax,4), %edx
	movq	216(%rbx), %rax
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 287 0
	movq	168(%rbx), %rdx
	movq	144(%rbx), %rax
	movl	$.LC2, %esi
	movslq	(%rdx), %rdx
	movl	(%rax,%rdx,4), %edx
	movq	224(%rbx), %rax
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	fprintf
	.loc 1 285 0
	movq	168(%rbx), %rdx
	movl	(%rdx), %eax
	addl	$1, %eax
	cmpl	$51, %eax
	movl	%eax, (%rdx)
	jle	.L23
	movq	128(%rbx), %rax
	movl	(%rax), %edx
	jmp	.L22
.LBE16:
	.cfi_endproc
.LFE30:
	.size	main.omp_fn.8, .-main.omp_fn.8
	.p2align 4,,15
	.type	main.omp_fn.1, @function
main.omp_fn.1:
.LFB23:
	.loc 1 147 0
	.cfi_startproc
.LVL16:
	pushq	%r15
.LCFI29:
	.cfi_def_cfa_offset 16
	pushq	%r14
.LCFI30:
	.cfi_def_cfa_offset 24
	pushq	%r13
.LCFI31:
	.cfi_def_cfa_offset 32
	pushq	%r12
.LCFI32:
	.cfi_def_cfa_offset 40
	pushq	%rbp
.LCFI33:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.LCFI34:
	.cfi_def_cfa_offset 56
	subq	$104, %rsp
.LCFI35:
	.cfi_def_cfa_offset 160
	.loc 1 147 0
	movq	24(%rdi), %rax
	movq	80(%rdi), %rbp
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	72(%rdi), %rbx
	movq	64(%rdi), %r14
	movq	56(%rdi), %r13
	movq	48(%rdi), %r12
	movq	%rax, %rdi
.LVL17:
	movq	%rax, 72(%rsp)
	call	GOMP_stream_task_add_instance
	movl	$4, %esi
	movl	$4, %edi
	call	GOMP_stream_create_read_view
	movq	72(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r14, %rsi
	movq	%rax, 24(%rsp)
	call	GOMP_stream_connect_view
	movl	$20, %esi
	movl	$20, %edi
	call	GOMP_stream_create_read_view
	movq	72(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r13, %rsi
	movq	%rax, 32(%rsp)
	call	GOMP_stream_connect_view
	movl	$20, %esi
	movl	$20, %edi
	call	GOMP_stream_create_read_view
	movq	72(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r12, %rsi
	movq	%rax, 40(%rsp)
	call	GOMP_stream_connect_view
	movl	$4, %esi
	movl	$4, %edi
	call	GOMP_stream_create_write_view
	movq	72(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbp, %rsi
	movq	%rax, 48(%rsp)
	call	GOMP_stream_connect_view
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_write_view
	movq	72(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbx, %rsi
	movq	%rax, 56(%rsp)
	call	GOMP_stream_connect_view
	movq	72(%rsp), %rdi
	call	GOMP_stream_wait_until_connected
	.p2align 4,,10
	.p2align 3
.L62:
	movq	72(%rsp), %rdi
	leaq	88(%rsp), %rsi
	call	GOMP_stream_get_available_work
	testq	%rax, %rax
	movq	%rax, %r14
	je	.L57
	movq	%rax, %r15
	addq	88(%rsp), %r15
	movq	88(%rsp), %rsi
	movq	24(%rsp), %rdi
	movq	%r15, %rdx
	call	GOMP_stream_update
	movq	88(%rsp), %rsi
	movq	32(%rsp), %rdi
	movq	%r15, %rdx
	movq	%rax, %rbx
	call	GOMP_stream_update
	movq	88(%rsp), %rsi
	movq	40(%rsp), %rdi
	movq	%r15, %rdx
	movq	%rax, %r13
	call	GOMP_stream_update
	movq	88(%rsp), %rsi
	movq	48(%rsp), %rdi
	movq	%r15, %rdx
	movq	%rax, %r12
	call	GOMP_stream_stall
	movq	88(%rsp), %rsi
	movq	56(%rsp), %rdi
	movq	%r15, %rdx
	movq	%rax, %rbp
	call	GOMP_stream_stall
	cmpq	$128, %r14
	je	.L66
	.loc 1 150 0
	movq	%r13, %rcx
	movq	%r15, 64(%rsp)
	movq	%r12, %r13
	movq	%rbx, 8(%rsp)
	movq	%rbp, 16(%rsp)
	xorl	%r12d, %r12d
	movq	%r14, %r15
	movq	%rax, %rbp
	movq	%rcx, %rbx
	.p2align 4,,10
	.p2align 3
.L61:
	movq	8(%rsp), %rax
.LBB17:
.LBB18:
	.file 2 "/usr/include/stdlib.h"
	.loc 2 281 0
	xorl	%esi, %esi
	movq	%r13, %rdi
.LBE18:
.LBE17:
	.loc 1 150 0
	addq	$20, %r13
	movl	(%rax,%r12,4), %r14d
.LVL18:
.LBB20:
.LBB19:
	.loc 2 281 0
	call	strtod
.LBE19:
.LBE20:
	.loc 1 149 0
	unpcklpd	%xmm0, %xmm0
.LBB21:
.LBB22:
	.loc 2 281 0
	xorl	%esi, %esi
	movq	%rbx, %rdi
.LBE22:
.LBE21:
	.loc 1 150 0
	addq	$20, %rbx
	.loc 1 149 0
	cvtpd2ps	%xmm0, %xmm0
	movss	%xmm0, 0(%rbp,%r12,8)
.LBB24:
.LBB23:
	.loc 2 281 0
	call	strtod
.LBE23:
.LBE24:
	.loc 1 150 0
	movq	16(%rsp), %rax
	unpcklpd	%xmm0, %xmm0
	cvtpd2ps	%xmm0, %xmm0
	movss	%xmm0, 4(%rbp,%r12,8)
.LVL19:
	movl	%r14d, (%rax,%r12,4)
	addq	$1, %r12
	cmpq	%r12, %r15
	ja	.L61
.LVL20:
.L65:
	movq	64(%rsp), %r15
	movq	24(%rsp), %rdi
	movq	%r15, %rsi
	call	GOMP_stream_release
	movq	32(%rsp), %rdi
	movq	%r15, %rsi
	call	GOMP_stream_release
	movq	40(%rsp), %rdi
	movq	%r15, %rsi
	call	GOMP_stream_release
	movq	48(%rsp), %rdi
	movq	%r15, %rsi
	call	GOMP_stream_commit
	movq	56(%rsp), %rdi
	movq	%r15, %rsi
	call	GOMP_stream_commit
	jmp	.L62
	.p2align 4,,10
	.p2align 3
.L66:
	xorl	%ecx, %ecx
	movq	%r15, 64(%rsp)
	movq	%rbp, 16(%rsp)
	movq	%r13, %r15
	xorb	%r14b, %r14b
	movq	%rbx, %r13
	movq	%r12, 8(%rsp)
	movq	%rax, %rbp
	movq	%rcx, %rbx
	.p2align 4,,10
	.p2align 3
.L59:
.LBB25:
.LBB26:
	.loc 1 147 0
	movq	8(%rsp), %rdi
	.loc 2 281 0
	xorl	%esi, %esi
.LBE26:
.LBE25:
	.loc 1 147 0
	movl	0(%r13,%r14), %r12d
.LVL21:
.LBB28:
.LBB27:
	addq	%rbx, %rdi
	.loc 2 281 0
	call	strtod
.LVL22:
.LBE27:
.LBE28:
	.loc 1 149 0
	unpcklpd	%xmm0, %xmm0
.LBB29:
.LBB30:
	.loc 1 147 0
	leaq	(%r15,%rbx), %rdi
	.loc 2 281 0
	xorl	%esi, %esi
.LBE30:
.LBE29:
	.loc 1 150 0
	addq	$20, %rbx
.LVL23:
	.loc 1 149 0
	cvtpd2ps	%xmm0, %xmm0
	movss	%xmm0, 0(%rbp,%r14,2)
.LBB32:
.LBB31:
	.loc 2 281 0
	call	strtod
.LBE31:
.LBE32:
	.loc 1 150 0
	movq	16(%rsp), %rax
	unpcklpd	%xmm0, %xmm0
	cvtpd2ps	%xmm0, %xmm0
	movss	%xmm0, 4(%rbp,%r14,2)
.LVL24:
	movl	%r12d, (%rax,%r14)
	addq	$4, %r14
	cmpq	$512, %r14
	jne	.L59
	jmp	.L65
.LVL25:
.L57:
	movq	72(%rsp), %rdi
	call	GOMP_stream_task_exit
	.loc 1 147 0
	addq	$104, %rsp
.LCFI36:
	.cfi_def_cfa_offset 56
	popq	%rbx
.LCFI37:
	.cfi_def_cfa_offset 48
	popq	%rbp
.LCFI38:
	.cfi_def_cfa_offset 40
	popq	%r12
.LCFI39:
	.cfi_def_cfa_offset 32
	popq	%r13
.LCFI40:
	.cfi_def_cfa_offset 24
	popq	%r14
.LCFI41:
	.cfi_def_cfa_offset 16
	popq	%r15
.LCFI42:
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	main.omp_fn.1, .-main.omp_fn.1
	.p2align 4,,15
	.type	main.omp_fn.2, @function
main.omp_fn.2:
.LFB24:
	.loc 1 155 0
	.cfi_startproc
.LVL26:
	pushq	%r15
.LCFI43:
	.cfi_def_cfa_offset 16
	pushq	%r14
.LCFI44:
	.cfi_def_cfa_offset 24
	pushq	%r13
.LCFI45:
	.cfi_def_cfa_offset 32
	pushq	%r12
.LCFI46:
	.cfi_def_cfa_offset 40
	pushq	%rbp
.LCFI47:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.LCFI48:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.LCFI49:
	.cfi_def_cfa_offset 128
	.loc 1 155 0
	movq	(%rdi), %rax
	movq	40(%rdi), %rbp
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	32(%rdi), %rbx
	movq	24(%rdi), %r12
	movq	%rax, %rdi
.LVL27:
	movq	%rax, 40(%rsp)
	call	GOMP_stream_task_add_instance
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_read_view
	movq	40(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r12, %rsi
	movq	%rax, 16(%rsp)
	call	GOMP_stream_connect_view
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_write_view
	movq	40(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbp, %rsi
	movq	%rax, 24(%rsp)
	call	GOMP_stream_connect_view
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_write_view
	movq	40(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbx, %rsi
	movq	%rax, 32(%rsp)
	call	GOMP_stream_connect_view
	movq	40(%rsp), %rdi
	call	GOMP_stream_wait_until_connected
	.p2align 4,,10
	.p2align 3
.L73:
	movq	40(%rsp), %rdi
	leaq	56(%rsp), %rsi
	call	GOMP_stream_get_available_work
	testq	%rax, %rax
	movq	%rax, %r14
	je	.L68
	movq	%rax, %r15
	addq	56(%rsp), %r15
	movq	56(%rsp), %rsi
	movq	16(%rsp), %rdi
	xorl	%ebp, %ebp
	movq	%r15, %rdx
	call	GOMP_stream_update
	movq	56(%rsp), %rsi
	movq	24(%rsp), %rdi
	movq	%r15, %rdx
	movq	%rax, %rbx
	call	GOMP_stream_stall
	movq	56(%rsp), %rsi
	movq	32(%rsp), %rdi
	movq	%r15, %rdx
	movq	%rax, %r13
	call	GOMP_stream_stall
	cmpq	$128, %r14
	movq	%rax, %r12
	je	.L76
	.p2align 4,,10
	.p2align 3
.L72:
	.loc 1 159 0
	movss	4(%rbx,%rbp,8), %xmm1
	leaq	4(%r13), %rax
	movss	(%rbx,%rbp,8), %xmm0
	leaq	4(%r12), %r8
	cvttss2si	%xmm1, %edx
	movq	%r13, %r9
	cvttss2si	%xmm0, %esi
	movq	%r12, %rcx
	movl	$1, %edi
	addq	$1, %rbp
	movq	%rax, (%rsp)
	addq	$8, %r13
	addq	$8, %r12
	call	freq_sync_correl_2STS
	cmpq	%rbp, %r14
	ja	.L72
.L71:
	movq	16(%rsp), %rdi
	movq	%r15, %rsi
	call	GOMP_stream_release
	movq	24(%rsp), %rdi
	movq	%r15, %rsi
	call	GOMP_stream_commit
	movq	32(%rsp), %rdi
	movq	%r15, %rsi
	call	GOMP_stream_commit
	jmp	.L73
	.p2align 4,,10
	.p2align 3
.L76:
	xorl	%ebp, %ebp
	.p2align 4,,10
	.p2align 3
.L70:
	movss	4(%rbx,%rbp), %xmm3
	.loc 1 155 0
	leaq	0(%r13,%rbp), %r9
	.loc 1 159 0
	movss	(%rbx,%rbp), %xmm2
	.loc 1 155 0
	leaq	(%r12,%rbp), %rcx
	.loc 1 159 0
	cvttss2si	%xmm3, %edx
	leaq	4(%r9), %rax
	cvttss2si	%xmm2, %esi
	leaq	4(%rcx), %r8
	movl	$1, %edi
	addq	$8, %rbp
	movq	%rax, (%rsp)
	call	freq_sync_correl_2STS
	cmpq	$1024, %rbp
	jne	.L70
	jmp	.L71
.L68:
	movq	40(%rsp), %rdi
	call	GOMP_stream_task_exit
	.loc 1 155 0
	addq	$72, %rsp
.LCFI50:
	.cfi_def_cfa_offset 56
	popq	%rbx
.LCFI51:
	.cfi_def_cfa_offset 48
	popq	%rbp
.LCFI52:
	.cfi_def_cfa_offset 40
	popq	%r12
.LCFI53:
	.cfi_def_cfa_offset 32
	popq	%r13
.LCFI54:
	.cfi_def_cfa_offset 24
	popq	%r14
.LCFI55:
	.cfi_def_cfa_offset 16
	popq	%r15
.LCFI56:
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	main.omp_fn.2, .-main.omp_fn.2
	.p2align 4,,15
	.type	main.omp_fn.3, @function
main.omp_fn.3:
.LFB25:
	.loc 1 165 0
	.cfi_startproc
.LVL28:
	pushq	%r15
.LCFI57:
	.cfi_def_cfa_offset 16
	pushq	%r14
.LCFI58:
	.cfi_def_cfa_offset 24
	pushq	%r13
.LCFI59:
	.cfi_def_cfa_offset 32
	movq	%rdi, %r13
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	pushq	%r12
.LCFI60:
	.cfi_def_cfa_offset 40
	pushq	%rbp
.LCFI61:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.LCFI62:
	.cfi_def_cfa_offset 56
	subq	$168, %rsp
.LCFI63:
	.cfi_def_cfa_offset 224
	.loc 1 165 0
	movq	(%rdi), %rax
	movq	64(%rdi), %rbp
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	movq	56(%rdi), %rbx
	movq	48(%rdi), %r15
	movq	32(%rdi), %r14
	movq	24(%rdi), %r12
	movq	%rax, %rdi
.LVL29:
	movq	%rax, 120(%rsp)
	call	GOMP_stream_task_add_instance
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_read_view
	movq	120(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r14, %rsi
	movq	%rax, 80(%rsp)
	call	GOMP_stream_connect_view
	movl	$4, %esi
	movl	$4, %edi
	call	GOMP_stream_create_read_view
	movq	120(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r12, %rsi
	movq	%rax, 88(%rsp)
	call	GOMP_stream_connect_view
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_write_view
	movq	120(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbp, %rsi
	movq	%rax, 96(%rsp)
	call	GOMP_stream_connect_view
	movl	$4, %esi
	movl	$4, %edi
	call	GOMP_stream_create_write_view
	movq	120(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbx, %rsi
	movq	%rax, 104(%rsp)
	call	GOMP_stream_connect_view
	movl	$4, %esi
	movl	$4, %edi
	call	GOMP_stream_create_write_view
	movq	120(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r15, %rsi
	movq	%rax, 112(%rsp)
	call	GOMP_stream_connect_view
	movq	120(%rsp), %rdi
	call	GOMP_stream_wait_until_connected
.LVL30:
	.p2align 4,,10
	.p2align 3
.L83:
	movq	120(%rsp), %rdi
	leaq	128(%rsp), %rsi
	call	GOMP_stream_get_available_work
	testq	%rax, %rax
	movq	%rax, 56(%rsp)
	je	.L78
	addq	128(%rsp), %rax
	movq	128(%rsp), %rsi
	xorl	%ebp, %ebp
	movq	80(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rax, 64(%rsp)
	call	GOMP_stream_update
	movq	64(%rsp), %rdx
	movq	128(%rsp), %rsi
	movq	%rax, %rbx
	movq	88(%rsp), %rdi
	call	GOMP_stream_update
	movq	64(%rsp), %rdx
	movq	128(%rsp), %rsi
	movq	96(%rsp), %rdi
	movq	%rax, 48(%rsp)
	call	GOMP_stream_stall
	movq	64(%rsp), %rdx
	movq	128(%rsp), %rsi
	movq	104(%rsp), %rdi
	movq	%rax, 72(%rsp)
	call	GOMP_stream_stall
	movq	64(%rsp), %rdx
	movq	128(%rsp), %rsi
	movq	%rax, %r15
	movq	112(%rsp), %rdi
	call	GOMP_stream_stall
	cmpq	$128, 56(%rsp)
	movq	%rax, %r14
	.loc 1 171 0
	movq	72(%rsp), %r12
	.loc 1 165 0
	je	.L80
	.p2align 4,,10
	.p2align 3
.L82:
	.loc 1 171 0
	movq	48(%rsp), %rsi
	movl	4(%rbx,%rbp,8), %ecx
	leaq	152(%rsp), %r9
	movl	(%rbx,%rbp,8), %edx
	movq	40(%r13), %rax
	leaq	156(%rsp), %r8
	movl	(%rsi,%rbp,4), %edi
.LVL31:
	leaq	140(%rsp), %rsi
	movq	%r12, 8(%rsp)
	movq	%rsi, 32(%rsp)
	leaq	144(%rsp), %rsi
	movq	%rsi, 24(%rsp)
	leaq	4(%r12), %rsi
	addq	$8, %r12
	movq	%rsi, 16(%rsp)
	leaq	148(%rsp), %rsi
	movq	%rsi, (%rsp)
	movl	(%rax), %esi
	call	frequency_sync_slidsum
.LVL32:
	movl	148(%rsp), %eax
	movl	%eax, (%r15,%rbp,4)
	movl	152(%rsp), %eax
	movl	%eax, (%r14,%rbp,4)
	addq	$1, %rbp
	cmpq	%rbp, 56(%rsp)
	ja	.L82
.L81:
	movq	64(%rsp), %rsi
	movq	80(%rsp), %rdi
	call	GOMP_stream_release
	movq	64(%rsp), %rsi
	movq	88(%rsp), %rdi
	call	GOMP_stream_release
	movq	64(%rsp), %rsi
	movq	96(%rsp), %rdi
	call	GOMP_stream_commit
	movq	64(%rsp), %rsi
	movq	104(%rsp), %rdi
	call	GOMP_stream_commit
	movq	64(%rsp), %rsi
	movq	112(%rsp), %rdi
	call	GOMP_stream_commit
	jmp	.L83
	.p2align 4,,10
	.p2align 3
.L80:
	movq	48(%rsp), %rsi
	movl	4(%rbx,%rbp,2), %ecx
	leaq	152(%rsp), %r9
	movl	(%rbx,%rbp,2), %edx
	movq	40(%r13), %rax
	leaq	156(%rsp), %r8
	movl	(%rsi,%rbp), %edi
.LVL33:
	leaq	140(%rsp), %rsi
	movq	%r12, 8(%rsp)
	movq	%rsi, 32(%rsp)
	leaq	144(%rsp), %rsi
	movq	%rsi, 24(%rsp)
	leaq	4(%r12), %rsi
	addq	$8, %r12
	movq	%rsi, 16(%rsp)
	leaq	148(%rsp), %rsi
	movq	%rsi, (%rsp)
	movl	(%rax), %esi
	call	frequency_sync_slidsum
.LVL34:
	movl	148(%rsp), %eax
	movl	%eax, (%r15,%rbp)
	movl	152(%rsp), %eax
	movl	%eax, (%r14,%rbp)
	addq	$4, %rbp
	cmpq	$512, %rbp
	jne	.L80
	jmp	.L81
.L78:
	movq	120(%rsp), %rdi
	call	GOMP_stream_task_exit
	.loc 1 165 0
	addq	$168, %rsp
.LCFI64:
	.cfi_def_cfa_offset 56
	popq	%rbx
.LCFI65:
	.cfi_def_cfa_offset 48
	popq	%rbp
.LCFI66:
	.cfi_def_cfa_offset 40
	popq	%r12
.LCFI67:
	.cfi_def_cfa_offset 32
	popq	%r13
.LCFI68:
	.cfi_def_cfa_offset 24
.LVL35:
	popq	%r14
.LCFI69:
	.cfi_def_cfa_offset 16
	popq	%r15
.LCFI70:
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE25:
	.size	main.omp_fn.3, .-main.omp_fn.3
	.p2align 4,,15
	.type	main.omp_fn.4, @function
main.omp_fn.4:
.LFB26:
	.loc 1 178 0
	.cfi_startproc
.LVL36:
	pushq	%r15
.LCFI71:
	.cfi_def_cfa_offset 16
	pushq	%r14
.LCFI72:
	.cfi_def_cfa_offset 24
	pushq	%r13
.LCFI73:
	.cfi_def_cfa_offset 32
	pushq	%r12
.LCFI74:
	.cfi_def_cfa_offset 40
	pushq	%rbp
.LCFI75:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.LCFI76:
	.cfi_def_cfa_offset 56
	subq	$88, %rsp
.LCFI77:
	.cfi_def_cfa_offset 144
	.loc 1 178 0
	movq	(%rdi), %rax
	movq	48(%rdi), %rbx
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	40(%rdi), %r13
	movq	32(%rdi), %r12
	movq	24(%rdi), %rbp
	movq	%rax, %rdi
.LVL37:
	movq	%rax, 56(%rsp)
	call	GOMP_stream_task_add_instance
	movl	$4, %esi
	movl	$4, %edi
	call	GOMP_stream_create_read_view
	movq	56(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r13, %rsi
	movq	%rax, 24(%rsp)
	call	GOMP_stream_connect_view
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_read_view
	movq	56(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r12, %rsi
	movq	%rax, 32(%rsp)
	call	GOMP_stream_connect_view
	movl	$4, %esi
	movl	$4, %edi
	call	GOMP_stream_create_read_view
	movq	56(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbp, %rsi
	movq	%rax, 40(%rsp)
	call	GOMP_stream_connect_view
	movl	$4, %esi
	movl	$4, %edi
	call	GOMP_stream_create_write_view
	movq	56(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbx, %rsi
	movq	%rax, 48(%rsp)
	call	GOMP_stream_connect_view
	movq	56(%rsp), %rdi
	call	GOMP_stream_wait_until_connected
.LVL38:
	.p2align 4,,10
	.p2align 3
.L93:
	movq	56(%rsp), %rdi
	leaq	64(%rsp), %rsi
	call	GOMP_stream_get_available_work
	testq	%rax, %rax
	movq	%rax, %rcx
	je	.L88
	movq	64(%rsp), %rax
	movq	64(%rsp), %rsi
	xorl	%r13d, %r13d
	movq	24(%rsp), %rdi
	movq	%rcx, 8(%rsp)
	addq	%rcx, %rax
	movq	%rax, %rdx
	movq	%rax, 16(%rsp)
	call	GOMP_stream_update
	movq	16(%rsp), %rdx
	movq	64(%rsp), %rsi
	movq	%rax, %rbp
	movq	32(%rsp), %rdi
	call	GOMP_stream_update
	movq	16(%rsp), %rdx
	movq	64(%rsp), %rsi
	movq	%rax, %rbx
	movq	40(%rsp), %rdi
	.loc 1 182 0
	movq	%rbx, %r15
	.loc 1 178 0
	call	GOMP_stream_update
	movq	16(%rsp), %rdx
	movq	64(%rsp), %rsi
	movq	%rax, %r12
	movq	48(%rsp), %rdi
	call	GOMP_stream_stall
	movq	8(%rsp), %rcx
	movq	%rax, %r14
	cmpq	$128, %rcx
	je	.L90
	movq	%rcx, %rbx
	.p2align 4,,10
	.p2align 3
.L92:
.LVL39:
	.loc 1 182 0
	movl	0(%rbp,%r13,4), %ecx
	movl	4(%r15), %edx
	leaq	76(%rsp), %r8
	movl	(%r12,%r13,4), %edi
	movl	(%r15), %esi
	addq	$8, %r15
	call	arctan
.LVL40:
	movl	76(%rsp), %eax
	movl	%eax, (%r14,%r13,4)
	addq	$1, %r13
	cmpq	%r13, %rbx
	ja	.L92
.L91:
	movq	16(%rsp), %rsi
	movq	24(%rsp), %rdi
	call	GOMP_stream_release
	movq	16(%rsp), %rsi
	movq	32(%rsp), %rdi
	call	GOMP_stream_release
	movq	16(%rsp), %rsi
	movq	40(%rsp), %rdi
	call	GOMP_stream_release
	movq	16(%rsp), %rsi
	movq	48(%rsp), %rdi
	call	GOMP_stream_commit
	jmp	.L93
	.p2align 4,,10
	.p2align 3
.L90:
.LVL41:
	movl	0(%rbp,%r13), %ecx
	movl	4(%rbx,%r13,2), %edx
	leaq	76(%rsp), %r8
	movl	(%rbx,%r13,2), %esi
	movl	(%r12,%r13), %edi
	call	arctan
.LVL42:
	movl	76(%rsp), %eax
	movl	%eax, (%r14,%r13)
	addq	$4, %r13
	cmpq	$512, %r13
	jne	.L90
	jmp	.L91
.L88:
	movq	56(%rsp), %rdi
	call	GOMP_stream_task_exit
	.loc 1 178 0
	addq	$88, %rsp
.LCFI78:
	.cfi_def_cfa_offset 56
	popq	%rbx
.LCFI79:
	.cfi_def_cfa_offset 48
	popq	%rbp
.LCFI80:
	.cfi_def_cfa_offset 40
	popq	%r12
.LCFI81:
	.cfi_def_cfa_offset 32
	popq	%r13
.LCFI82:
	.cfi_def_cfa_offset 24
	popq	%r14
.LCFI83:
	.cfi_def_cfa_offset 16
	popq	%r15
.LCFI84:
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE26:
	.size	main.omp_fn.4, .-main.omp_fn.4
	.p2align 4,,15
	.type	main.omp_fn.5, @function
main.omp_fn.5:
.LFB27:
	.loc 1 186 0
	.cfi_startproc
.LVL43:
	pushq	%r15
.LCFI85:
	.cfi_def_cfa_offset 16
	pushq	%r14
.LCFI86:
	.cfi_def_cfa_offset 24
	pushq	%r13
.LCFI87:
	.cfi_def_cfa_offset 32
	pushq	%r12
.LCFI88:
	.cfi_def_cfa_offset 40
	pushq	%rbp
.LCFI89:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.LCFI90:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.LCFI91:
	.cfi_def_cfa_offset 128
	.loc 1 186 0
	movq	(%rdi), %rax
	movq	48(%rdi), %rbx
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	40(%rdi), %r13
	movq	32(%rdi), %r12
	movq	24(%rdi), %rbp
	movq	%rax, %rdi
.LVL44:
	movq	%rax, 40(%rsp)
	call	GOMP_stream_task_add_instance
	movl	$4, %esi
	movl	$4, %edi
	call	GOMP_stream_create_read_view
	movq	40(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r13, %rsi
	movq	%rax, 8(%rsp)
	call	GOMP_stream_connect_view
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_read_view
	movq	40(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r12, %rsi
	movq	%rax, 16(%rsp)
	call	GOMP_stream_connect_view
	movl	$4, %esi
	movl	$4, %edi
	call	GOMP_stream_create_read_view
	movq	40(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbp, %rsi
	movq	%rax, 24(%rsp)
	call	GOMP_stream_connect_view
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_write_view
	movq	40(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbx, %rsi
	movq	%rax, 32(%rsp)
	call	GOMP_stream_connect_view
	movq	40(%rsp), %rdi
	call	GOMP_stream_wait_until_connected
	.p2align 4,,10
	.p2align 3
.L103:
	movq	40(%rsp), %rdi
	leaq	56(%rsp), %rsi
	call	GOMP_stream_get_available_work
	testq	%rax, %rax
	movq	%rax, %r12
	je	.L98
	movq	56(%rsp), %rax
	movq	56(%rsp), %rsi
	xorl	%ebp, %ebp
	movq	8(%rsp), %rdi
	addq	%r12, %rax
	movq	%rax, %rdx
	movq	%rax, (%rsp)
	call	GOMP_stream_update
	movq	(%rsp), %rdx
	movq	56(%rsp), %rsi
	movq	%rax, %r14
	movq	16(%rsp), %rdi
	call	GOMP_stream_update
	movq	(%rsp), %rdx
	movq	56(%rsp), %rsi
	movq	%rax, %rbx
	movq	24(%rsp), %rdi
	call	GOMP_stream_update
	movq	(%rsp), %rdx
	movq	56(%rsp), %rsi
	movq	%rax, %r13
	movq	32(%rsp), %rdi
	call	GOMP_stream_stall
	cmpq	$128, %r12
	.loc 1 190 0
	movq	%rax, %r15
	.loc 1 186 0
	je	.L108
	.p2align 4,,10
	.p2align 3
.L104:
.LVL45:
	.loc 1 190 0
	movl	(%r14,%rbp,4), %ecx
	movl	4(%rbx,%rbp,8), %edx
	leaq	4(%r15), %r9
	movl	(%rbx,%rbp,8), %esi
	movl	0(%r13,%rbp,4), %edi
	movq	%r15, %r8
	addq	$1, %rbp
.LVL46:
	addq	$8, %r15
	call	cordic_turn
.LVL47:
	cmpq	%rbp, %r12
	ja	.L104
.L101:
	movq	(%rsp), %rsi
	movq	8(%rsp), %rdi
	call	GOMP_stream_release
	movq	(%rsp), %rsi
	movq	16(%rsp), %rdi
	call	GOMP_stream_release
	movq	(%rsp), %rsi
	movq	24(%rsp), %rdi
	call	GOMP_stream_release
	movq	(%rsp), %rsi
	movq	32(%rsp), %rdi
	call	GOMP_stream_commit
	jmp	.L103
	.p2align 4,,10
	.p2align 3
.L108:
	.loc 1 186 0
	movq	%rax, %r12
	.p2align 4,,10
	.p2align 3
.L100:
.LVL48:
	.loc 1 190 0
	movl	(%r14,%rbp), %ecx
	movl	4(%rbx,%rbp,2), %edx
	leaq	4(%r12), %r9
	movl	(%rbx,%rbp,2), %esi
	movl	0(%r13,%rbp), %edi
	movq	%r12, %r8
	addq	$4, %rbp
.LVL49:
	addq	$8, %r12
	call	cordic_turn
.LVL50:
	cmpq	$512, %rbp
	jne	.L100
	jmp	.L101
.L98:
	movq	40(%rsp), %rdi
	call	GOMP_stream_task_exit
	.loc 1 186 0
	addq	$72, %rsp
.LCFI92:
	.cfi_def_cfa_offset 56
	popq	%rbx
.LCFI93:
	.cfi_def_cfa_offset 48
	popq	%rbp
.LCFI94:
	.cfi_def_cfa_offset 40
	popq	%r12
.LCFI95:
	.cfi_def_cfa_offset 32
	popq	%r13
.LCFI96:
	.cfi_def_cfa_offset 24
	popq	%r14
.LCFI97:
	.cfi_def_cfa_offset 16
	popq	%r15
.LCFI98:
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE27:
	.size	main.omp_fn.5, .-main.omp_fn.5
	.p2align 4,,15
	.type	main.omp_fn.6, @function
main.omp_fn.6:
.LFB28:
	.loc 1 195 0
	.cfi_startproc
.LVL51:
	pushq	%r15
.LCFI99:
	.cfi_def_cfa_offset 16
	pushq	%r14
.LCFI100:
	.cfi_def_cfa_offset 24
	pushq	%r13
.LCFI101:
	.cfi_def_cfa_offset 32
	pushq	%r12
.LCFI102:
	.cfi_def_cfa_offset 40
	pushq	%rbp
.LCFI103:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.LCFI104:
	.cfi_def_cfa_offset 56
	subq	$104, %rsp
.LCFI105:
	.cfi_def_cfa_offset 160
	.loc 1 195 0
	movq	(%rdi), %rax
	movq	56(%rdi), %rbp
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	48(%rdi), %rbx
	movq	40(%rdi), %r14
	movq	32(%rdi), %r13
	movq	24(%rdi), %r12
	movq	%rax, %rdi
.LVL52:
	movq	%rax, 72(%rsp)
	call	GOMP_stream_task_add_instance
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_read_view
	movq	72(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r14, %rsi
	movq	%rax, 32(%rsp)
	call	GOMP_stream_connect_view
	movl	$4, %esi
	movl	$4, %edi
	call	GOMP_stream_create_read_view
	movq	72(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r13, %rsi
	movq	%rax, 40(%rsp)
	call	GOMP_stream_connect_view
	movl	$4, %esi
	movl	$4, %edi
	call	GOMP_stream_create_read_view
	movq	72(%rsp), %rdi
	movq	%rax, %rdx
	movq	%r12, %rsi
	movq	%rax, 48(%rsp)
	call	GOMP_stream_connect_view
	movl	$4, %esi
	movl	$4, %edi
	call	GOMP_stream_create_write_view
	movq	72(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbp, %rsi
	movq	%rax, 56(%rsp)
	call	GOMP_stream_connect_view
	movl	$8, %esi
	movl	$8, %edi
	call	GOMP_stream_create_write_view
	movq	72(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rbx, %rsi
	movq	%rax, 64(%rsp)
	call	GOMP_stream_connect_view
	movq	72(%rsp), %rdi
	call	GOMP_stream_wait_until_connected
.LVL53:
	.p2align 4,,10
	.p2align 3
.L115:
	movq	72(%rsp), %rdi
	leaq	80(%rsp), %rsi
	call	GOMP_stream_get_available_work
	testq	%rax, %rax
	movq	%rax, 16(%rsp)
	je	.L110
	addq	80(%rsp), %rax
	movq	80(%rsp), %rsi
	xorl	%ebp, %ebp
	movq	32(%rsp), %rdi
	movq	%rax, %rdx
	movq	%rax, 24(%rsp)
	call	GOMP_stream_update
	movq	24(%rsp), %rdx
	movq	80(%rsp), %rsi
	movq	%rax, %rbx
	movq	40(%rsp), %rdi
	call	GOMP_stream_update
	movq	24(%rsp), %rdx
	movq	80(%rsp), %rsi
	movq	%rax, %r15
	movq	48(%rsp), %rdi
	call	GOMP_stream_update
	movq	24(%rsp), %rdx
	movq	80(%rsp), %rsi
	movq	%rax, %r14
	movq	56(%rsp), %rdi
	call	GOMP_stream_stall
	movq	24(%rsp), %rdx
	movq	80(%rsp), %rsi
	movq	%rax, %r13
	movq	64(%rsp), %rdi
	call	GOMP_stream_stall
	cmpq	$128, 16(%rsp)
	.loc 1 199 0
	movq	%rax, %r12
	.loc 1 195 0
	je	.L112
	.p2align 4,,10
	.p2align 3
.L114:
.LVL54:
	.loc 1 199 0
	movl	4(%rbx,%rbp,8), %ecx
	movl	(%rbx,%rbp,8), %edx
	leaq	92(%rsp), %rax
	movl	(%r15,%rbp,4), %esi
	movl	(%r14,%rbp,4), %edi
	leaq	4(%r12), %r9
	movq	%r12, %r8
	movq	%rax, (%rsp)
	addq	$8, %r12
	call	fine_time_sync
.LVL55:
	movl	92(%rsp), %eax
	movl	%eax, 0(%r13,%rbp,4)
	addq	$1, %rbp
	cmpq	%rbp, 16(%rsp)
	ja	.L114
.L113:
	movq	24(%rsp), %rsi
	movq	32(%rsp), %rdi
	call	GOMP_stream_release
	movq	24(%rsp), %rsi
	movq	40(%rsp), %rdi
	call	GOMP_stream_release
	movq	24(%rsp), %rsi
	movq	48(%rsp), %rdi
	call	GOMP_stream_release
	movq	24(%rsp), %rsi
	movq	56(%rsp), %rdi
	call	GOMP_stream_commit
	movq	24(%rsp), %rsi
	movq	64(%rsp), %rdi
	call	GOMP_stream_commit
	jmp	.L115
	.p2align 4,,10
	.p2align 3
.L112:
.LVL56:
	movl	4(%rbx,%rbp,2), %ecx
	movl	(%rbx,%rbp,2), %edx
	leaq	92(%rsp), %rax
	movl	(%r15,%rbp), %esi
	movl	(%r14,%rbp), %edi
	leaq	4(%r12), %r9
	movq	%r12, %r8
	movq	%rax, (%rsp)
	addq	$8, %r12
	call	fine_time_sync
.LVL57:
	movl	92(%rsp), %eax
	movl	%eax, 0(%r13,%rbp)
	addq	$4, %rbp
	cmpq	$512, %rbp
	jne	.L112
	jmp	.L113
.L110:
	movq	72(%rsp), %rdi
	call	GOMP_stream_task_exit
	.loc 1 195 0
	addq	$104, %rsp
.LCFI106:
	.cfi_def_cfa_offset 56
	popq	%rbx
.LCFI107:
	.cfi_def_cfa_offset 48
	popq	%rbp
.LCFI108:
	.cfi_def_cfa_offset 40
	popq	%r12
.LCFI109:
	.cfi_def_cfa_offset 32
	popq	%r13
.LCFI110:
	.cfi_def_cfa_offset 24
	popq	%r14
.LCFI111:
	.cfi_def_cfa_offset 16
	popq	%r15
.LCFI112:
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE28:
	.size	main.omp_fn.6, .-main.omp_fn.6
	.p2align 4,,15
	.type	main.omp_fn.0, @function
main.omp_fn.0:
.LFB22:
	.loc 1 108 0
	.cfi_startproc
.LVL58:
	pushq	%r15
.LCFI113:
	.cfi_def_cfa_offset 16
	pushq	%r14
.LCFI114:
	.cfi_def_cfa_offset 24
	pushq	%r13
.LCFI115:
	.cfi_def_cfa_offset 32
	pushq	%r12
.LCFI116:
	.cfi_def_cfa_offset 40
	pushq	%rbp
.LCFI117:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.LCFI118:
	.cfi_def_cfa_offset 56
	movq	%rdi, %rbx
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	subq	$3720, %rsp
.LCFI119:
	.cfi_def_cfa_offset 3776
	.loc 1 108 0
	movq	8(%rdi), %rax
	movq	16(%rdi), %rdx
	movq	%rax, 88(%rsp)
	movq	%rdx, 184(%rsp)
	movq	32(%rdi), %rax
	movq	40(%rdi), %rdx
	movq	%rax, 96(%rsp)
	movq	%rdx, 192(%rsp)
	movq	56(%rdi), %rax
	movq	64(%rdi), %rdx
	movq	%rax, 104(%rsp)
	movq	%rdx, 200(%rsp)
	movq	80(%rdi), %rax
	movq	88(%rdi), %rdx
	movq	%rax, 112(%rsp)
	movq	%rdx, 208(%rsp)
	movq	104(%rdi), %rax
	movq	112(%rdi), %rdx
	movq	%rax, 120(%rsp)
	movq	%rdx, 216(%rsp)
	movq	128(%rdi), %rax
	movq	136(%rdi), %rdx
	movq	%rax, 128(%rsp)
	movq	%rdx, 224(%rsp)
	movq	152(%rdi), %rax
	movq	160(%rdi), %rdx
	movq	%rax, 136(%rsp)
	movq	%rdx, 232(%rsp)
	movq	168(%rdi), %rax
	movq	176(%rdi), %rdx
	movq	%rax, 160(%rsp)
	movq	184(%rdi), %rax
	movq	%rdx, 168(%rsp)
	movq	200(%rdi), %rdx
	movq	%rax, 176(%rsp)
	movq	208(%rdi), %rax
	movq	%rdx, 152(%rsp)
	movq	216(%rdi), %rdx
	movq	%rax, 240(%rsp)
	movl	384(%rdi), %eax
	movq	%rdx, 80(%rsp)
	movl	%eax, 3708(%rsp)
.LVL59:
	movl	380(%rdi), %eax
	movl	%eax, 3704(%rsp)
.LVL60:
	movl	368(%rdi), %eax
	movl	%eax, 68(%rsp)
.LVL61:
	movl	364(%rdi), %eax
	movl	%eax, 3700(%rsp)
.LVL62:
	movl	356(%rdi), %eax
	movl	%eax, 3696(%rsp)
.LVL63:
	movl	352(%rdi), %eax
	movq	%rdx, %rdi
.LVL64:
	movl	%eax, 3692(%rsp)
.LVL65:
	call	GOMP_stream_task_add_instance
.LVL66:
	call	GOMP_single_start
	cmpb	$1, %al
	je	.L134
	.loc 1 147 0
	.p2align 4,,6
	call	GOMP_barrier
	.p2align 4,,6
	call	GOMP_single_start
	cmpb	$1, %al
	.p2align 4,,3
	je	.L135
.LVL67:
.L121:
	.loc 1 136 0
	.p2align 4,,6
	call	GOMP_barrier
	.p2align 4,,6
	call	GOMP_barrier
	.p2align 4,,5
	call	GOMP_single_start
	cmpb	$1, %al
	.p2align 4,,3
	je	.L136
.L133:
	.p2align 4,,6
	call	GOMP_barrier
	.loc 1 108 0
	addq	$3720, %rsp
	.cfi_remember_state
.LCFI120:
	.cfi_def_cfa_offset 56
	popq	%rbx
.LCFI121:
	.cfi_def_cfa_offset 48
	popq	%rbp
.LCFI122:
	.cfi_def_cfa_offset 40
	popq	%r12
.LCFI123:
	.cfi_def_cfa_offset 32
	popq	%r13
.LCFI124:
	.cfi_def_cfa_offset 24
	popq	%r14
.LCFI125:
	.cfi_def_cfa_offset 16
	popq	%r15
.LCFI126:
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L136:
.LCFI127:
	.cfi_restore_state
	.loc 1 136 0
	movq	240(%rsp), %rdx
	movq	232(%rsp), %rax
	movq	80(%rsp), %rdi
	movb	$1, (%rdx)
	movb	$1, (%rax)
	movq	224(%rsp), %rdx
	movq	216(%rsp), %rax
	movb	$1, (%rdx)
	movb	$1, (%rax)
	movq	208(%rsp), %rdx
	movq	200(%rsp), %rax
	movb	$1, (%rdx)
	movb	$1, (%rax)
	movq	192(%rsp), %rdx
	movq	184(%rsp), %rax
	movb	$1, (%rdx)
	movb	$1, (%rax)
	call	GOMP_stream_task_exit
	call	GOMP_stream_exit
	jmp	.L133
.LVL68:
	.p2align 4,,10
	.p2align 3
.L134:
	.loc 1 108 0
	call	GOMP_stream_init
	movl	$262144, %esi
	movl	$4, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %r15
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	call	GOMP_stream_add_expected_views
	xorl	%ecx, %ecx
	movl	$1, %edx
	xorl	%esi, %esi
	movq	%r15, %rdi
	call	GOMP_stream_add_expected_views
	movl	$262144, %esi
	movl	$8, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	movq	%rax, 16(%rsp)
	call	GOMP_stream_add_expected_views
	movq	16(%rsp), %rdi
	xorl	%ecx, %ecx
	movl	$1, %edx
	xorl	%esi, %esi
	call	GOMP_stream_add_expected_views
	movl	$262144, %esi
	movl	$8, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %r12
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	call	GOMP_stream_add_expected_views
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	movl	$1, %esi
	movq	%r12, %rdi
	call	GOMP_stream_add_expected_views
	xorl	%ecx, %ecx
	movl	$1, %edx
	xorl	%esi, %esi
	movq	%r12, %rdi
	call	GOMP_stream_add_expected_views
	movl	$262144, %esi
	movl	$8, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %r13
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	call	GOMP_stream_add_expected_views
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	movl	$1, %esi
	movq	%r13, %rdi
	call	GOMP_stream_add_expected_views
	xorl	%ecx, %ecx
	movl	$1, %edx
	xorl	%esi, %esi
	movq	%r13, %rdi
	call	GOMP_stream_add_expected_views
	movl	$262144, %esi
	movl	$8, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %r14
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	call	GOMP_stream_add_expected_views
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	movl	$1, %esi
	movq	%r14, %rdi
	call	GOMP_stream_add_expected_views
	xorl	%ecx, %ecx
	movl	$1, %edx
	xorl	%esi, %esi
	movq	%r14, %rdi
	call	GOMP_stream_add_expected_views
	movl	$262144, %esi
	movl	$8, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	movq	%rax, 24(%rsp)
	call	GOMP_stream_add_expected_views
	movq	24(%rsp), %rdi
	xorl	%ecx, %ecx
	movl	$1, %edx
	xorl	%esi, %esi
	call	GOMP_stream_add_expected_views
	movl	$262144, %esi
	movl	$4, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	movq	%rax, 32(%rsp)
	call	GOMP_stream_add_expected_views
	movq	32(%rsp), %rdi
	xorl	%ecx, %ecx
	movl	$1, %edx
	xorl	%esi, %esi
	call	GOMP_stream_add_expected_views
	movl	$262144, %esi
	movl	$4, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %rbp
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	call	GOMP_stream_add_expected_views
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	movl	$1, %esi
	movq	%rbp, %rdi
	call	GOMP_stream_add_expected_views
	xorl	%ecx, %ecx
	movl	$1, %esi
	xorl	%edx, %edx
	movq	%rbp, %rdi
	call	GOMP_stream_add_expected_views
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	movl	$1, %esi
	movq	%rbp, %rdi
	call	GOMP_stream_add_expected_views
	xorl	%ecx, %ecx
	movl	$1, %edx
	xorl	%esi, %esi
	movq	%rbp, %rdi
	call	GOMP_stream_add_expected_views
	movl	$262144, %esi
	movl	$4, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	movq	%rax, 40(%rsp)
	call	GOMP_stream_add_expected_views
	movq	40(%rsp), %rdi
	xorl	%ecx, %ecx
	movl	$1, %edx
	xorl	%esi, %esi
	call	GOMP_stream_add_expected_views
	movl	$262144, %esi
	movl	$4, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	movq	%rax, 48(%rsp)
	call	GOMP_stream_add_expected_views
	movq	48(%rsp), %rdi
	xorl	%ecx, %ecx
	movl	$1, %edx
	xorl	%esi, %esi
	call	GOMP_stream_add_expected_views
	movl	$262144, %esi
	movl	$8, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	movq	%rax, 56(%rsp)
	call	GOMP_stream_add_expected_views
	movq	56(%rsp), %rdi
	xorl	%ecx, %ecx
	movl	$1, %edx
	xorl	%esi, %esi
	call	GOMP_stream_add_expected_views
	movl	$262144, %esi
	movl	$4, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	movq	%rax, 72(%rsp)
	call	GOMP_stream_add_expected_views
	movq	72(%rsp), %rdi
	xorl	%ecx, %ecx
	xorl	%esi, %esi
	movl	$1, %edx
	call	GOMP_stream_add_expected_views
	movq	176(%rsp), %rdx
	movq	72(%rsp), %rsi
	movq	80(%rsp), %rdi
	call	GOMP_stream_connect_view
	movl	$262144, %esi
	movl	$20, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	movq	%rax, 144(%rsp)
	call	GOMP_stream_add_expected_views
	movq	144(%rsp), %rdi
	xorl	%ecx, %ecx
	xorl	%esi, %esi
	movl	$1, %edx
	call	GOMP_stream_add_expected_views
	movq	168(%rsp), %rdx
	movq	144(%rsp), %rsi
	movq	80(%rsp), %rdi
	call	GOMP_stream_connect_view
	movl	$262144, %esi
	movl	$20, %edi
	call	GOMP_stream_create_stream
	xorl	%ecx, %ecx
	movq	%rax, %rdi
	xorl	%edx, %edx
	movl	$1, %esi
	movq	%rax, 248(%rsp)
	call	GOMP_stream_add_expected_views
	movq	248(%rsp), %rdi
	xorl	%ecx, %ecx
	xorl	%esi, %esi
	movl	$1, %edx
	call	GOMP_stream_add_expected_views
	movq	160(%rsp), %rdx
	movq	248(%rsp), %rsi
	movq	80(%rsp), %rdi
	call	GOMP_stream_connect_view
	movq	184(%rsp), %rsi
	movq	88(%rsp), %rdi
	call	GOMP_stream_create_task
	.loc 1 222 0
	movq	%rax, 1600(%rsp)
	movq	184(%rsp), %rax
	movq	88(%rsp), %rdx
	movq	%r15, 1632(%rsp)
	movl	$0, 3676(%rsp)
	movq	%rax, 1616(%rsp)
	leaq	3704(%rsp), %rax
	movq	%rdx, 1608(%rsp)
	movq	16(%rsp), %rdx
	movq	%rax, 1640(%rsp)
	leaq	3688(%rsp), %rax
	movq	%rax, 1648(%rsp)
	leaq	3684(%rsp), %rax
	movq	%rdx, 1624(%rsp)
	movq	%rax, 1656(%rsp)
	leaq	3680(%rsp), %rax
	movq	%rax, 1664(%rsp)
	leaq	1344(%rsp), %rax
	movq	%rax, 1672(%rsp)
	leaq	1088(%rsp), %rax
	movq	%rax, 1680(%rsp)
	leaq	3700(%rsp), %rax
	movq	%rax, 1688(%rsp)
	leaq	672(%rsp), %rax
	movq	%rax, 1696(%rsp)
	leaq	256(%rsp), %rax
	movq	%rax, 1704(%rsp)
	leaq	2896(%rsp), %rax
	movq	%rax, 1712(%rsp)
	leaq	2688(%rsp), %rax
	movq	%rax, 1720(%rsp)
	leaq	3676(%rsp), %rax
	movq	%rax, 1728(%rsp)
	leaq	2480(%rsp), %rax
	movq	%rax, 1736(%rsp)
	leaq	2272(%rsp), %rax
	movq	%rax, 1744(%rsp)
	leaq	2064(%rsp), %rax
	movq	%rax, 1752(%rsp)
	leaq	1856(%rsp), %rax
	movq	%rax, 1760(%rsp)
	leaq	3692(%rsp), %rax
	movq	%rax, 1768(%rsp)
	leaq	3708(%rsp), %rax
	movq	%rax, 1776(%rsp)
	leaq	272(%rbx), %rax
	movq	%rax, 1784(%rsp)
	leaq	280(%rbx), %rax
	movq	%rax, 1792(%rsp)
	leaq	336(%rbx), %rax
	movq	%rax, 1800(%rsp)
	leaq	344(%rbx), %rax
	movq	%rax, 1808(%rsp)
	leaq	304(%rbx), %rax
	movq	%rax, 1816(%rsp)
	leaq	312(%rbx), %rax
	movq	%rax, 1824(%rsp)
	leaq	320(%rbx), %rax
	movq	%rax, 1832(%rsp)
	movq	192(%rsp), %rsi
	leaq	328(%rbx), %rax
	movq	96(%rsp), %rdi
	movq	%rax, 1840(%rsp)
	call	GOMP_stream_create_task
	.loc 1 205 0
	movq	%rax, 3104(%rsp)
	movq	96(%rsp), %rax
	movq	192(%rsp), %rdx
	movq	200(%rsp), %rsi
	movq	104(%rsp), %rdi
	movq	%r12, 3144(%rsp)
	movq	%rax, 3112(%rsp)
	leaq	224(%rbx), %rax
	movq	%r13, 3136(%rsp)
	movq	%rdx, 3120(%rsp)
	movq	%r14, 3128(%rsp)
	movq	%rax, 3152(%rsp)
	leaq	232(%rbx), %rax
	movq	%rax, 3160(%rsp)
	leaq	256(%rbx), %rax
	movq	%rax, 3168(%rsp)
	leaq	264(%rbx), %rax
	movq	%rax, 3176(%rsp)
	leaq	288(%rbx), %rax
	movq	%rax, 3184(%rsp)
	leaq	296(%rbx), %rax
	movq	%rax, 3192(%rsp)
	call	GOMP_stream_create_task
	.loc 1 195 0
	movq	%rax, 3376(%rsp)
	movq	104(%rsp), %rax
	movq	200(%rsp), %rdx
	movq	208(%rsp), %rsi
	movq	112(%rsp), %rdi
	movq	%r15, 3432(%rsp)
	movq	%rax, 3384(%rsp)
	movq	16(%rsp), %rax
	movq	%rdx, 3392(%rsp)
	movq	24(%rsp), %rdx
	movq	%rbp, 3400(%rsp)
	movq	%rax, 3424(%rsp)
	movq	32(%rsp), %rax
	movq	%rdx, 3416(%rsp)
	movq	%rax, 3408(%rsp)
	call	GOMP_stream_create_task
	.loc 1 186 0
	movq	112(%rsp), %rdx
	movq	%rax, 3504(%rsp)
	movq	208(%rsp), %rax
	movq	216(%rsp), %rsi
	movq	120(%rsp), %rdi
	movq	%r14, 3536(%rsp)
	movq	%rdx, 3512(%rsp)
	movq	24(%rsp), %rdx
	movq	%rax, 3520(%rsp)
	movq	40(%rsp), %rax
	movq	%rbp, 3528(%rsp)
	movq	%rdx, 3552(%rsp)
	movq	%rax, 3544(%rsp)
	call	GOMP_stream_create_task
	.loc 1 178 0
	movq	120(%rsp), %rdx
	movq	%rax, 3440(%rsp)
	movq	216(%rsp), %rax
	movq	224(%rsp), %rsi
	movq	128(%rsp), %rdi
	movq	%r12, 3472(%rsp)
	movq	%rdx, 3448(%rsp)
	movq	40(%rsp), %rdx
	movq	%rax, 3456(%rsp)
	movq	48(%rsp), %rax
	movq	%rbp, 3464(%rsp)
	movq	%rdx, 3488(%rsp)
	movq	%rax, 3480(%rsp)
	call	GOMP_stream_create_task
	.loc 1 165 0
	movq	%rax, 3296(%rsp)
	movq	224(%rsp), %rax
	movq	128(%rsp), %rdx
	movq	232(%rsp), %rsi
	movq	136(%rsp), %rdi
	movq	%r12, 3360(%rsp)
	movq	%rax, 3312(%rsp)
	movq	48(%rsp), %rax
	movq	%rdx, 3304(%rsp)
	movq	32(%rsp), %rdx
	movq	%r13, 3328(%rsp)
	movq	%rbp, 3320(%rsp)
	movq	%rax, 3344(%rsp)
	leaq	3696(%rsp), %rax
	movq	%rdx, 3352(%rsp)
	movq	%rax, 3336(%rsp)
	call	GOMP_stream_create_task
	.loc 1 155 0
	movq	136(%rsp), %rdx
	movq	%rax, 3568(%rsp)
	movq	240(%rsp), %rsi
	movq	232(%rsp), %rax
	movq	152(%rsp), %rdi
	movq	%r13, 3608(%rsp)
	movq	%rdx, 3576(%rsp)
	movq	56(%rsp), %rdx
	movq	%rax, 3584(%rsp)
	movq	%r14, 3600(%rsp)
	movq	%rdx, 3592(%rsp)
	call	GOMP_stream_create_task
	.loc 1 147 0
	movq	160(%rsp), %rdx
	movq	%rax, 3224(%rsp)
	.loc 1 222 0
	leaq	1600(%rsp), %rsi
	.loc 1 147 0
	movq	152(%rsp), %rax
	.loc 1 222 0
	movl	$1, %r9d
	movl	$8, %r8d
	movl	$248, %ecx
	movl	$main.omp_fn.8, %edi
	.loc 1 147 0
	movq	%rbp, 3280(%rsp)
	movq	%rdx, 3200(%rsp)
	movq	168(%rsp), %rdx
	movq	%rax, 3232(%rsp)
	movq	56(%rsp), %rax
	.loc 1 222 0
	movb	$0, (%rsp)
	.loc 1 147 0
	movq	%rdx, 3208(%rsp)
	movq	176(%rsp), %rdx
	movq	%rax, 3272(%rsp)
	movq	144(%rsp), %rax
	movq	%rdx, 3216(%rsp)
	movq	240(%rsp), %rdx
	movq	%rax, 3256(%rsp)
	movq	%rdx, 3240(%rsp)
	movq	72(%rsp), %rdx
	movq	%rdx, 3264(%rsp)
	movq	248(%rsp), %rdx
	movq	%rdx, 3248(%rsp)
	.loc 1 222 0
	xorl	%edx, %edx
	call	GOMP_stream_task
	.loc 1 205 0
	leaq	3104(%rsp), %rsi
	movl	$1, %r9d
	movl	$8, %r8d
	movl	$96, %ecx
	xorl	%edx, %edx
	movl	$main.omp_fn.7, %edi
	movb	$0, (%rsp)
	call	GOMP_stream_task
	.loc 1 195 0
	leaq	3376(%rsp), %rsi
	xorl	%edx, %edx
	movl	$1, %r9d
	movl	$8, %r8d
	movl	$64, %ecx
	movl	$main.omp_fn.6, %edi
	movb	$0, (%rsp)
	call	GOMP_stream_task
	.loc 1 186 0
	leaq	3504(%rsp), %rsi
	xorl	%edx, %edx
	movl	$1, %r9d
	movl	$8, %r8d
	movl	$56, %ecx
	movl	$main.omp_fn.5, %edi
	movb	$0, (%rsp)
	call	GOMP_stream_task
	.loc 1 178 0
	leaq	3440(%rsp), %rsi
	xorl	%edx, %edx
	movl	$1, %r9d
	movl	$8, %r8d
	movl	$56, %ecx
	movl	$main.omp_fn.4, %edi
	movb	$0, (%rsp)
	call	GOMP_stream_task
	.loc 1 165 0
	leaq	3296(%rsp), %rsi
	xorl	%edx, %edx
	movl	$1, %r9d
	movl	$8, %r8d
	movl	$72, %ecx
	movl	$main.omp_fn.3, %edi
	movb	$0, (%rsp)
	call	GOMP_stream_task
	.loc 1 155 0
	leaq	3568(%rsp), %rsi
	xorl	%edx, %edx
	movl	$1, %r9d
	movl	$8, %r8d
	movl	$48, %ecx
	movl	$main.omp_fn.2, %edi
	movb	$0, (%rsp)
	call	GOMP_stream_task
	.loc 1 147 0
	leaq	3200(%rsp), %rsi
	movl	$1, %r9d
	movl	$8, %r8d
	xorl	%edx, %edx
	movl	$88, %ecx
	movl	$main.omp_fn.1, %edi
	movb	$0, (%rsp)
	call	GOMP_stream_task
	xorl	%edx, %edx
	xorl	%esi, %esi
	movl	$1, %ecx
	movq	%r15, %rdi
	call	GOMP_stream_add_expected_views
	movq	16(%rsp), %rdi
	xorl	%edx, %edx
	xorl	%esi, %esi
	movl	$1, %ecx
	call	GOMP_stream_add_expected_views
	xorl	%edx, %edx
	xorl	%esi, %esi
	movl	$1, %ecx
	movq	%r12, %rdi
	call	GOMP_stream_add_expected_views
	xorl	%edx, %edx
	xorl	%esi, %esi
	movl	$1, %ecx
	movq	%r13, %rdi
	call	GOMP_stream_add_expected_views
	xorl	%edx, %edx
	xorl	%esi, %esi
	movl	$1, %ecx
	movq	%r14, %rdi
	call	GOMP_stream_add_expected_views
	movq	24(%rsp), %rdi
	xorl	%edx, %edx
	xorl	%esi, %esi
	movl	$1, %ecx
	call	GOMP_stream_add_expected_views
	movq	32(%rsp), %rdi
	xorl	%esi, %esi
	movl	$1, %ecx
	xorl	%edx, %edx
	call	GOMP_stream_add_expected_views
	xorl	%edx, %edx
	movl	$1, %ecx
	xorl	%esi, %esi
	movq	%rbp, %rdi
	call	GOMP_stream_add_expected_views
	movq	40(%rsp), %rdi
	xorl	%edx, %edx
	xorl	%esi, %esi
	movl	$1, %ecx
	call	GOMP_stream_add_expected_views
	movq	48(%rsp), %rdi
	xorl	%edx, %edx
	xorl	%esi, %esi
	movl	$1, %ecx
	call	GOMP_stream_add_expected_views
	movq	56(%rsp), %rdi
	xorl	%edx, %edx
	xorl	%esi, %esi
	movl	$1, %ecx
	call	GOMP_stream_add_expected_views
	movq	72(%rsp), %rdi
	xorl	%edx, %edx
	xorl	%esi, %esi
	movl	$1, %ecx
	call	GOMP_stream_add_expected_views
	movq	144(%rsp), %rdi
	xorl	%edx, %edx
	xorl	%esi, %esi
	movl	$1, %ecx
	call	GOMP_stream_add_expected_views
	movq	248(%rsp), %rdi
	xorl	%edx, %edx
	xorl	%esi, %esi
	movl	$1, %ecx
	call	GOMP_stream_add_expected_views
	movq	80(%rsp), %rdi
	call	GOMP_stream_wait_until_connected
	call	GOMP_barrier
	call	GOMP_single_start
	cmpb	$1, %al
	.p2align 4,,3
	jne	.L121
	.p2align 4,,10
	.p2align 3
.L135:
	movq	152(%rsp), %rax
	movq	176(%rsp), %rdi
	xorl	%r13d, %r13d
	xorl	%r14d, %r14d
	xorl	%r15d, %r15d
	movq	(%rax), %rax
	movq	%rax, 72(%rsp)
	movq	72(%rsp), %rsi
	subq	$-128, %rax
	movq	%rax, %rdx
	movq	%rax, 144(%rsp)
	call	GOMP_stream_stall
	movq	144(%rsp), %rdx
	movq	72(%rsp), %rsi
	movq	168(%rsp), %rdi
	movq	%rax, 56(%rsp)
	call	GOMP_stream_stall
	movq	144(%rsp), %rdx
	movq	72(%rsp), %rsi
	movq	%rax, %r12
	movq	160(%rsp), %rdi
	call	GOMP_stream_stall
	movq	$0, 16(%rsp)
	movq	%rax, %rbp
	movq	$0, 48(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 32(%rsp)
	movq	$0, 24(%rsp)
	jmp	.L122
	.p2align 4,,10
	.p2align 3
.L126:
.LBB33:
.LBB38:
	.loc 1 146 0
	addq	$1, 40(%rsp)
	cmpq	$128, 40(%rsp)
	je	.L137
.L127:
	addq	$1, 32(%rsp)
	cmpq	$128, 32(%rsp)
	je	.L138
.L128:
	addq	$1, %r13
	cmpq	$128, %r13
	je	.L139
.L129:
	addq	$1, %r14
	cmpq	$128, %r14
	je	.L140
.L130:
	addq	$1, %r15
	cmpq	$128, %r15
	je	.L141
.L131:
	addq	$1, 24(%rsp)
	cmpq	$128, 24(%rsp)
	je	.L142
.L132:
.LBE38:
.LBE33:
	.loc 1 147 0 discriminator 1
	movl	$1, 68(%rsp)
.L122:
.LBB44:
.LBB39:
	.loc 1 142 0 discriminator 1
	movq	240(%rbx), %rdi
	call	feof
	testl	%eax, %eax
	jne	.L143
	.loc 1 142 0 is_stmt 0 discriminator 2
	movq	248(%rbx), %rdi
	call	feof
	testl	%eax, %eax
	jne	.L121
	.loc 1 145 0 is_stmt 1
	movq	240(%rbx), %rdx
	leaq	3648(%rsp), %rdi
	movl	$20, %esi
	call	fgets
	.loc 1 146 0
	movq	248(%rbx), %rdx
	leaq	3616(%rsp), %rdi
	movl	$20, %esi
	call	fgets
	movq	56(%rsp), %rax
	movl	68(%rsp), %edx
	addq	$1, 16(%rsp)
	cmpq	$128, 16(%rsp)
	movl	%edx, (%rax)
	movq	3616(%rsp), %rax
	movq	%rax, (%r12)
	movq	3624(%rsp), %rax
	movq	%rax, 8(%r12)
	movl	3632(%rsp), %eax
	movl	%eax, 16(%r12)
	movq	3648(%rsp), %rax
	movq	%rax, 0(%rbp)
	movq	3656(%rsp), %rax
	movq	%rax, 8(%rbp)
	movl	3664(%rsp), %eax
	movl	%eax, 16(%rbp)
	je	.L124
	addq	$4, 56(%rsp)
	addq	$20, %r12
	addq	$20, %rbp
.L125:
	addq	$1, 48(%rsp)
	cmpq	$128, 48(%rsp)
	jne	.L126
	movq	136(%rsp), %rax
.LBE39:
.LBE44:
	movq	$0, 48(%rsp)
.LBB45:
.LBB37:
	subq	$-128, (%rax)
	jmp	.L126
	.p2align 4,,10
	.p2align 3
.L142:
	movq	88(%rsp), %rax
.LBE37:
.LBE45:
	movq	$0, 24(%rsp)
.LBB46:
.LBB40:
	subq	$-128, (%rax)
	jmp	.L132
	.p2align 4,,10
	.p2align 3
.L141:
	movq	96(%rsp), %rdx
.LBE40:
.LBE46:
	xorb	%r15b, %r15b
.LBB47:
.LBB36:
	subq	$-128, (%rdx)
	jmp	.L131
	.p2align 4,,10
	.p2align 3
.L140:
	movq	104(%rsp), %rax
.LBE36:
.LBE47:
	xorb	%r14b, %r14b
.LBB48:
.LBB41:
	subq	$-128, (%rax)
	jmp	.L130
	.p2align 4,,10
	.p2align 3
.L139:
	movq	112(%rsp), %rdx
.LBE41:
.LBE48:
	xorb	%r13b, %r13b
.LBB49:
.LBB35:
	subq	$-128, (%rdx)
	jmp	.L129
	.p2align 4,,10
	.p2align 3
.L138:
	movq	120(%rsp), %rax
.LBE35:
.LBE49:
	movq	$0, 32(%rsp)
.LBB50:
.LBB42:
	subq	$-128, (%rax)
	jmp	.L128
	.p2align 4,,10
	.p2align 3
.L137:
	movq	128(%rsp), %rdx
.LBE42:
.LBE50:
	movq	$0, 40(%rsp)
.LBB51:
.LBB34:
	subq	$-128, (%rdx)
	jmp	.L127
	.p2align 4,,10
	.p2align 3
.L124:
	movq	152(%rsp), %rax
	movq	144(%rsp), %rsi
	movq	176(%rsp), %rdi
	subq	$-128, (%rax)
	call	GOMP_stream_commit
	movq	72(%rsp), %rbp
	movq	144(%rsp), %rsi
	movq	176(%rsp), %rdi
	addq	$256, %rbp
	movq	%rbp, %rdx
	call	GOMP_stream_stall
	movq	168(%rsp), %rdi
	movq	%rbp, %rsi
	movq	%rax, 56(%rsp)
	call	GOMP_stream_commit
	addq	$384, 72(%rsp)
	movq	168(%rsp), %rdi
	movq	%rbp, %rsi
	movq	72(%rsp), %rdx
	call	GOMP_stream_stall
	movq	72(%rsp), %rsi
	movq	160(%rsp), %rdi
	movq	%rax, %r12
	call	GOMP_stream_commit
	movq	72(%rsp), %rdx
	movq	72(%rsp), %rsi
	movq	160(%rsp), %rdi
	subq	$-128, %rdx
	movq	%rdx, 144(%rsp)
	call	GOMP_stream_stall
.LBE34:
.LBE51:
	movq	$0, 16(%rsp)
.LBB52:
.LBB43:
	movq	%rax, %rbp
	jmp	.L125
	.p2align 4,,10
	.p2align 3
.L143:
	.loc 1 142 0
	movq	88(%rsp), %rdx
	movq	24(%rsp), %rax
	movq	72(%rsp), %rbx
.LVL69:
	addq	16(%rsp), %rbx
	movq	176(%rsp), %rdi
	addq	%rax, (%rdx)
	movq	96(%rsp), %rdx
	movq	104(%rsp), %rax
	movq	%rbx, %rsi
	addq	%r15, (%rdx)
	movq	112(%rsp), %rdx
	addq	%r14, (%rax)
	movq	120(%rsp), %rax
	addq	%r13, (%rdx)
	movq	32(%rsp), %rdx
	addq	%rdx, (%rax)
	movq	128(%rsp), %rax
	movq	40(%rsp), %rdx
	addq	%rdx, (%rax)
	movq	136(%rsp), %rax
	movq	48(%rsp), %rdx
	addq	%rdx, (%rax)
	call	GOMP_stream_commit
	addq	16(%rsp), %rbx
	movq	168(%rsp), %rdi
	movq	%rbx, %rsi
	call	GOMP_stream_commit
	movq	16(%rsp), %rsi
	movq	160(%rsp), %rdi
	leaq	(%rbx,%rsi), %rsi
	call	GOMP_stream_commit
	movq	152(%rsp), %rax
	movq	16(%rsp), %rdx
	addq	%rdx, (%rax)
	jmp	.L121
.LBE43:
.LBE52:
	.cfi_endproc
.LFE22:
	.size	main.omp_fn.0, .-main.omp_fn.0
	.section	.rodata.str1.1
.LC3:
	.string	"r"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC4:
	.string	"./CCSS_ref_data/rx_real_data.am"
	.align 8
.LC5:
	.string	"./CCSS_ref_data/rx_imag_data.am"
	.section	.rodata.str1.1
.LC6:
	.string	"w"
	.section	.rodata.str1.8
	.align 8
.LC7:
	.string	"./plainC_SimOutput/freq_sync_correl_2STS_out_I.am"
	.align 8
.LC8:
	.string	"./plainC_SimOutput/freq_sync_correl_2STS_out_Q.am"
	.align 8
.LC9:
	.string	"./plainC_SimOutput/FS_single_correl_I.am"
	.align 8
.LC10:
	.string	"./plainC_SimOutput/FS_single_correl_Q.am"
	.align 8
.LC11:
	.string	"./plainC_SimOutput/fft_reversed_re_out.am"
	.align 8
.LC12:
	.string	"./plainC_SimOutput/fft_reversed_im_out.am"
	.align 8
.LC13:
	.string	"./plainC_SimOutput/freq_est_phase_out_I.am"
	.align 8
.LC14:
	.string	"./plainC_SimOutput/freq_est_phase_out_Q.am"
	.align 8
.LC15:
	.string	"./plainC_SimOutput/CHE_out_I.am"
	.align 8
.LC16:
	.string	"./plainC_SimOutput/CHE_out_Q.am"
	.align 8
.LC17:
	.string	"./plainC_SimOutput/CHC_out_I.am"
	.align 8
.LC18:
	.string	"./plainC_SimOutput/CHC_out_Q.am"
	.align 8
.LC19:
	.string	"./plainC_SimOutput/fft_re_out.am"
	.align 8
.LC20:
	.string	"./plainC_SimOutput/fft_im_out.am"
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
.LFB21:
	.loc 1 40 0
	.cfi_startproc
.LVL70:
	pushq	%r15
.LCFI128:
	.cfi_def_cfa_offset 16
	xorl	%esi, %esi
.LVL71:
	xorl	%edi, %edi
.LVL72:
	pushq	%r14
.LCFI129:
	.cfi_def_cfa_offset 24
	pushq	%r13
.LCFI130:
	.cfi_def_cfa_offset 32
	pushq	%r12
.LCFI131:
	.cfi_def_cfa_offset 40
	pushq	%rbp
.LCFI132:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.LCFI133:
	.cfi_def_cfa_offset 56
	subq	$616, %rsp
.LCFI134:
	.cfi_def_cfa_offset 672
	.loc 1 40 0
	movq	$0, 584(%rsp)
	movb	$0, 607(%rsp)
	movq	$0, 576(%rsp)
	movb	$0, 606(%rsp)
	movq	$0, 568(%rsp)
	movb	$0, 605(%rsp)
	movq	$0, 560(%rsp)
	movb	$0, 604(%rsp)
	movq	$0, 552(%rsp)
	movb	$0, 603(%rsp)
	movq	$0, 544(%rsp)
	movb	$0, 602(%rsp)
	movq	$0, 536(%rsp)
	movb	$0, 601(%rsp)
	movq	$0, 528(%rsp)
	movb	$0, 600(%rsp)
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	call	GOMP_stream_create_task
	movl	$4, %esi
	movl	$4, %edi
	movq	%rax, %r15
.LVL73:
	call	GOMP_stream_create_write_view
	movl	$20, %esi
	movl	$20, %edi
	movq	%rax, (%rsp)
	call	GOMP_stream_create_write_view
	movl	$20, %esi
	movl	$20, %edi
	movq	%rax, 8(%rsp)
	call	GOMP_stream_create_write_view
.LVL74:
	.loc 1 77 0
	movl	$.LC3, %esi
	movl	$.LC4, %edi
	movq	%rax, 16(%rsp)
	call	fopen
	.loc 1 78 0
	movl	$.LC3, %esi
	movl	$.LC5, %edi
	.loc 1 77 0
	movq	%rax, %r12
.LVL75:
	.loc 1 78 0
	call	fopen
.LVL76:
	.loc 1 90 0
	movl	$.LC6, %esi
	movl	$.LC7, %edi
	.loc 1 78 0
	movq	%rax, %rbp
.LVL77:
	.loc 1 90 0
	call	fopen
.LVL78:
	.loc 1 91 0
	movl	$.LC6, %esi
	movl	$.LC8, %edi
	.loc 1 90 0
	movq	%rax, %r14
.LVL79:
	.loc 1 91 0
	call	fopen
.LVL80:
	.loc 1 92 0
	movl	$.LC6, %esi
	movl	$.LC9, %edi
	.loc 1 91 0
	movq	%rax, %r13
.LVL81:
	.loc 1 92 0
	call	fopen
.LVL82:
	.loc 1 93 0
	movl	$.LC6, %esi
	movl	$.LC10, %edi
	.loc 1 92 0
	movq	%rax, %rbx
.LVL83:
	.loc 1 93 0
	call	fopen
.LVL84:
	.loc 1 94 0
	movl	$.LC6, %esi
	movl	$.LC11, %edi
	movq	%rax, 24(%rsp)
	call	fopen
	.loc 1 95 0
	movl	$.LC6, %esi
	movl	$.LC12, %edi
	movq	%rax, 32(%rsp)
	call	fopen
	.loc 1 96 0
	movl	$.LC6, %esi
	movl	$.LC13, %edi
	movq	%rax, 40(%rsp)
	call	fopen
	.loc 1 97 0
	movl	$.LC6, %esi
	movl	$.LC14, %edi
	.loc 1 96 0
	movq	%rax, 56(%rsp)
.LVL85:
	.loc 1 97 0
	call	fopen
.LVL86:
	.loc 1 98 0
	movl	$.LC6, %esi
	movl	$.LC15, %edi
	.loc 1 97 0
	movq	%rax, 64(%rsp)
.LVL87:
	.loc 1 98 0
	call	fopen
.LVL88:
	.loc 1 99 0
	movl	$.LC6, %esi
	movl	$.LC16, %edi
	.loc 1 98 0
	movq	%rax, 72(%rsp)
.LVL89:
	.loc 1 99 0
	call	fopen
.LVL90:
	.loc 1 100 0
	movl	$.LC6, %esi
	movl	$.LC17, %edi
	.loc 1 99 0
	movq	%rax, 80(%rsp)
.LVL91:
	.loc 1 100 0
	call	fopen
.LVL92:
	.loc 1 101 0
	movl	$.LC6, %esi
	movl	$.LC18, %edi
	.loc 1 100 0
	movq	%rax, 88(%rsp)
.LVL93:
	.loc 1 101 0
	call	fopen
.LVL94:
	.loc 1 102 0
	movl	$.LC6, %esi
	movl	$.LC19, %edi
	.loc 1 101 0
	movq	%rax, 96(%rsp)
.LVL95:
	.loc 1 102 0
	call	fopen
.LVL96:
	.loc 1 103 0
	movl	$.LC6, %esi
	movl	$.LC20, %edi
	.loc 1 102 0
	movq	%rax, 104(%rsp)
.LVL97:
	.loc 1 103 0
	call	fopen
.LVL98:
	.loc 1 106 0
	leaq	596(%rsp), %rdi
	movq	%rax, 48(%rsp)
	call	fine_time_sync_init
.LVL99:
	.loc 1 108 0
	leaq	584(%rsp), %rsi
	movq	(%rsp), %rdx
	movq	16(%rsp), %r8
	movq	8(%rsp), %rcx
	movq	%r15, 344(%rsp)
	movl	$main.omp_fn.0, %edi
	movq	%rsi, 136(%rsp)
	leaq	607(%rsp), %rsi
	movq	$0, 128(%rsp)
	movq	%rdx, 312(%rsp)
	leaq	528(%rsp), %rdx
	movq	%r8, 296(%rsp)
	movq	%rsi, 144(%rsp)
	leaq	576(%rsp), %rsi
	movq	%rcx, 304(%rsp)
	movq	%rdx, 328(%rsp)
	leaq	600(%rsp), %rdx
	movq	$0, 152(%rsp)
	movq	%rsi, 160(%rsp)
	leaq	606(%rsp), %rsi
	movq	$0, 176(%rsp)
	movq	%rdx, 336(%rsp)
	movq	$0, 200(%rsp)
	movq	%rsi, 168(%rsp)
	leaq	568(%rsp), %rsi
	movq	$0, 224(%rsp)
	movq	$0, 248(%rsp)
	movq	$0, 272(%rsp)
	movq	%rsi, 184(%rsp)
	leaq	605(%rsp), %rsi
	movq	$0, 320(%rsp)
	movl	$0, 512(%rsp)
	movl	$0, 508(%rsp)
	movq	%rsi, 192(%rsp)
	leaq	560(%rsp), %rsi
	movq	%rsi, 208(%rsp)
	leaq	604(%rsp), %rsi
	movq	%rsi, 216(%rsp)
	leaq	552(%rsp), %rsi
	movq	%rsi, 232(%rsp)
	leaq	603(%rsp), %rsi
	movq	%rsi, 240(%rsp)
	leaq	544(%rsp), %rsi
	movq	%rsi, 256(%rsp)
	leaq	602(%rsp), %rsi
	movq	%rsi, 264(%rsp)
	leaq	536(%rsp), %rsi
	movq	%rsi, 280(%rsp)
	leaq	601(%rsp), %rsi
	movq	%rsi, 288(%rsp)
	movl	$0, 504(%rsp)
.LVL100:
	movl	596(%rsp), %edx
	movq	24(%rsp), %r9
	movq	32(%rsp), %r10
	movq	40(%rsp), %r11
	movq	48(%rsp), %rax
	movq	%rbx, 384(%rsp)
	leaq	128(%rsp), %rbx
.LVL101:
	movl	%edx, 488(%rsp)
	movq	56(%rsp), %rdx
	movq	%rbx, %rsi
	movq	%r9, 392(%rsp)
	movq	%r10, 400(%rsp)
	movq	%r11, 408(%rsp)
	movq	%r14, 352(%rsp)
	movq	%rdx, 416(%rsp)
	movq	64(%rsp), %rdx
	movq	%r13, 360(%rsp)
	movq	%r12, 368(%rsp)
	movq	%rbp, 376(%rsp)
	movl	$0, 500(%rsp)
	movq	%rdx, 424(%rsp)
	movq	72(%rsp), %rdx
	movl	$0, 496(%rsp)
	movl	$0x3fb00000, 492(%rsp)
	movl	$0, 484(%rsp)
	movl	$0, 480(%rsp)
	movq	%rdx, 432(%rsp)
	movq	80(%rsp), %rdx
	movq	%rdx, 440(%rsp)
	movq	88(%rsp), %rdx
	movq	%rdx, 448(%rsp)
	movq	96(%rsp), %rdx
	movq	%rdx, 456(%rsp)
	movq	104(%rsp), %rdx
	movq	%rdx, 464(%rsp)
	movl	$8, %edx
	movq	%rax, 472(%rsp)
	call	GOMP_parallel_start
.LVL102:
	movq	%rbx, %rdi
	call	main.omp_fn.0
	call	GOMP_parallel_end
	movq	352(%rsp), %rax
	movq	360(%rsp), %rdx
	.loc 1 324 0
	movq	368(%rsp), %rdi
	.loc 1 108 0
	movq	400(%rsp), %r15
	movq	408(%rsp), %r14
.LVL103:
	movq	416(%rsp), %rbp
.LVL104:
	movq	%rax, 56(%rsp)
.LVL105:
	movq	376(%rsp), %rax
	movq	%rdx, 64(%rsp)
.LVL106:
	movq	384(%rsp), %rdx
	movq	424(%rsp), %rbx
	movq	464(%rsp), %r13
	movq	%rax, 72(%rsp)
.LVL107:
	movq	392(%rsp), %rax
	movq	%rdx, 80(%rsp)
.LVL108:
	movq	432(%rsp), %rdx
	movq	472(%rsp), %r12
	movq	%rax, 88(%rsp)
.LVL109:
	movq	440(%rsp), %rax
	movq	%rdx, 96(%rsp)
.LVL110:
	movq	448(%rsp), %rdx
	movq	%rax, 104(%rsp)
.LVL111:
	movq	456(%rsp), %rax
	movq	%rdx, 112(%rsp)
.LVL112:
	movq	%rax, 120(%rsp)
.LVL113:
	.loc 1 324 0
	call	fclose
.LVL114:
	.loc 1 325 0
	movq	72(%rsp), %rdi
	call	fclose
	.loc 1 327 0
	movq	56(%rsp), %rdi
	call	fclose
	.loc 1 328 0
	movq	64(%rsp), %rdi
	call	fclose
	.loc 1 329 0
	movq	80(%rsp), %rdi
	call	fclose
	.loc 1 330 0
	movq	88(%rsp), %rdi
	call	fclose
	.loc 1 331 0
	movq	%r15, %rdi
	call	fclose
	.loc 1 332 0
	movq	%r14, %rdi
	call	fclose
	.loc 1 333 0
	movq	%r13, %rdi
	call	fclose
	.loc 1 334 0
	movq	%r12, %rdi
	call	fclose
	.loc 1 335 0
	movq	%rbp, %rdi
	call	fclose
	.loc 1 336 0
	movq	%rbx, %rdi
	call	fclose
	.loc 1 337 0
	movq	112(%rsp), %rdi
	call	fclose
	.loc 1 338 0
	movq	120(%rsp), %rdi
	call	fclose
	.loc 1 340 0
	movq	96(%rsp), %rdi
	call	fclose
	.loc 1 341 0
	movq	104(%rsp), %rdi
	call	fclose
	.loc 1 344 0
	addq	$616, %rsp
.LCFI135:
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
.LCFI136:
	.cfi_def_cfa_offset 48
.LVL115:
	popq	%rbp
.LCFI137:
	.cfi_def_cfa_offset 40
.LVL116:
	popq	%r12
.LCFI138:
	.cfi_def_cfa_offset 32
.LVL117:
	popq	%r13
.LCFI139:
	.cfi_def_cfa_offset 24
.LVL118:
	popq	%r14
.LCFI140:
	.cfi_def_cfa_offset 16
.LVL119:
	popq	%r15
.LCFI141:
	.cfi_def_cfa_offset 8
.LVL120:
	ret
	.cfi_endproc
.LFE21:
	.size	main, .-main
.Letext0:
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.quad	.LFB29-.Ltext0
	.quad	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI0-.Ltext0
	.quad	.LCFI1-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI1-.Ltext0
	.quad	.LCFI2-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI2-.Ltext0
	.quad	.LCFI3-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI3-.Ltext0
	.quad	.LCFI4-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI4-.Ltext0
	.quad	.LCFI5-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI5-.Ltext0
	.quad	.LCFI6-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI6-.Ltext0
	.quad	.LCFI7-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 128
	.quad	.LCFI7-.Ltext0
	.quad	.LCFI8-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI8-.Ltext0
	.quad	.LCFI9-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI9-.Ltext0
	.quad	.LCFI10-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI10-.Ltext0
	.quad	.LCFI11-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI11-.Ltext0
	.quad	.LCFI12-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI12-.Ltext0
	.quad	.LCFI13-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI13-.Ltext0
	.quad	.LFE29-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST1:
	.quad	.LVL0-.Ltext0
	.quad	.LVL1-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL1-.Ltext0
	.quad	.LVL2-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	0
	.quad	0
.LLST2:
	.quad	.LVL0-.Ltext0
	.quad	.LVL1-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x58
	.byte	0x6
	.quad	.LVL1-.Ltext0
	.quad	.LVL2-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x58
	.byte	0x6
	.quad	0
	.quad	0
.LLST3:
	.quad	.LVL0-.Ltext0
	.quad	.LVL1-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x50
	.byte	0x6
	.quad	.LVL1-.Ltext0
	.quad	.LVL2-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x50
	.byte	0x6
	.quad	0
	.quad	0
.LLST4:
	.quad	.LVL0-.Ltext0
	.quad	.LVL1-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x48
	.byte	0x6
	.quad	.LVL1-.Ltext0
	.quad	.LVL2-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x48
	.byte	0x6
	.quad	0
	.quad	0
.LLST5:
	.quad	.LVL0-.Ltext0
	.quad	.LVL1-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x40
	.byte	0x6
	.quad	.LVL1-.Ltext0
	.quad	.LVL2-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x40
	.byte	0x6
	.quad	0
	.quad	0
.LLST6:
	.quad	.LVL0-.Ltext0
	.quad	.LVL1-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x38
	.byte	0x6
	.quad	.LVL1-.Ltext0
	.quad	.LVL2-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x38
	.byte	0x6
	.quad	0
	.quad	0
.LLST7:
	.quad	.LVL0-.Ltext0
	.quad	.LVL1-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x30
	.byte	0x6
	.quad	.LVL1-.Ltext0
	.quad	.LVL2-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x30
	.byte	0x6
	.quad	0
	.quad	0
.LLST8:
	.quad	.LFB30-.Ltext0
	.quad	.LCFI14-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI14-.Ltext0
	.quad	.LCFI15-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI15-.Ltext0
	.quad	.LCFI16-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI16-.Ltext0
	.quad	.LCFI17-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI17-.Ltext0
	.quad	.LCFI18-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI18-.Ltext0
	.quad	.LCFI19-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI19-.Ltext0
	.quad	.LCFI20-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI20-.Ltext0
	.quad	.LCFI21-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 144
	.quad	.LCFI21-.Ltext0
	.quad	.LCFI22-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI22-.Ltext0
	.quad	.LCFI23-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI23-.Ltext0
	.quad	.LCFI24-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI24-.Ltext0
	.quad	.LCFI25-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI25-.Ltext0
	.quad	.LCFI26-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI26-.Ltext0
	.quad	.LCFI27-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI27-.Ltext0
	.quad	.LCFI28-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI28-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 144
	.quad	0
	.quad	0
.LLST9:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x1
	.byte	0x56
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	0
	.quad	0
.LLST10:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xf0
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xf0
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0xf0
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xf0
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xf0
	.byte	0x6
	.quad	0
	.quad	0
.LLST11:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xe8
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xe8
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0xe8
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xe8
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xe8
	.byte	0x6
	.quad	0
	.quad	0
.LLST12:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xe0
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xe0
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0xe0
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xe0
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xe0
	.byte	0x6
	.quad	0
	.quad	0
.LLST13:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xd8
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xd8
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0xd8
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xd8
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xd8
	.byte	0x6
	.quad	0
	.quad	0
.LLST14:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xd0
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xd0
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0xd0
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xd0
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xd0
	.byte	0x6
	.quad	0
	.quad	0
.LLST15:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xc8
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xc8
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0xc8
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xc8
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xc8
	.byte	0x6
	.quad	0
	.quad	0
.LLST16:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xc0
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xc0
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0xc0
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xc0
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xc0
	.byte	0x6
	.quad	0
	.quad	0
.LLST17:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xb8
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xb8
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0xb8
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xb8
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xb8
	.byte	0x6
	.quad	0
	.quad	0
.LLST18:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xb0
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xb0
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0xb0
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xb0
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xb0
	.byte	0x6
	.quad	0
	.quad	0
.LLST19:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xa8
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xa8
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0xa8
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xa8
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xa8
	.byte	0x6
	.quad	0
	.quad	0
.LLST20:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xa0
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xa0
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0xa0
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xa0
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xa0
	.byte	0x6
	.quad	0
	.quad	0
.LLST21:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x98
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x98
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x98
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x98
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x98
	.byte	0x6
	.quad	0
	.quad	0
.LLST22:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x90
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x90
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x90
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x90
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x90
	.byte	0x6
	.quad	0
	.quad	0
.LLST23:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x88
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x88
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x88
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x88
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x88
	.byte	0x6
	.quad	0
	.quad	0
.LLST24:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x80
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x80
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x80
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x80
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x6
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x80
	.byte	0x6
	.quad	0
	.quad	0
.LLST25:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x78
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x78
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x5
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x78
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x78
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x78
	.byte	0x6
	.quad	0
	.quad	0
.LLST26:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x70
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x70
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x5
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x70
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x70
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x70
	.byte	0x6
	.quad	0
	.quad	0
.LLST27:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x68
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x68
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x5
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x68
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x68
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x68
	.byte	0x6
	.quad	0
	.quad	0
.LLST28:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x60
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x60
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x5
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x60
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x60
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x60
	.byte	0x6
	.quad	0
	.quad	0
.LLST29:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x58
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x58
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x5
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x58
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x58
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x58
	.byte	0x6
	.quad	0
	.quad	0
.LLST30:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x50
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x50
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x5
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x50
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x50
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x50
	.byte	0x6
	.quad	0
	.quad	0
.LLST31:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x48
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x48
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x5
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x48
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x48
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x48
	.byte	0x6
	.quad	0
	.quad	0
.LLST32:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x40
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x40
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x5
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x40
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x40
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x40
	.byte	0x6
	.quad	0
	.quad	0
.LLST33:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x38
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x38
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x5
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x38
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x38
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x38
	.byte	0x6
	.quad	0
	.quad	0
.LLST34:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x30
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x30
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x5
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x30
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x30
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x30
	.byte	0x6
	.quad	0
	.quad	0
.LLST35:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x28
	.byte	0x6
	.quad	.LVL4-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x28
	.byte	0x6
	.quad	.LVL9-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x5
	.byte	0x76
	.sleb128 0
	.byte	0x23
	.uleb128 0x28
	.byte	0x6
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x28
	.byte	0x6
	.quad	.LVL14-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x28
	.byte	0x6
	.quad	0
	.quad	0
.LLST36:
	.quad	.LVL5-.Ltext0
	.quad	.LVL6-.Ltext0
	.value	0x1
	.byte	0x5e
	.quad	.LVL7-.Ltext0
	.quad	.LVL8-.Ltext0
	.value	0x1
	.byte	0x5e
	.quad	.LVL10-.Ltext0
	.quad	.LVL11-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	.LVL14-.Ltext0
	.quad	.LVL15-.Ltext0
	.value	0x1
	.byte	0x5e
	.quad	0
	.quad	0
.LLST37:
	.quad	.LFB23-.Ltext0
	.quad	.LCFI29-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI29-.Ltext0
	.quad	.LCFI30-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI30-.Ltext0
	.quad	.LCFI31-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI31-.Ltext0
	.quad	.LCFI32-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI32-.Ltext0
	.quad	.LCFI33-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI33-.Ltext0
	.quad	.LCFI34-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI34-.Ltext0
	.quad	.LCFI35-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI35-.Ltext0
	.quad	.LCFI36-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 160
	.quad	.LCFI36-.Ltext0
	.quad	.LCFI37-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI37-.Ltext0
	.quad	.LCFI38-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI38-.Ltext0
	.quad	.LCFI39-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI39-.Ltext0
	.quad	.LCFI40-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI40-.Ltext0
	.quad	.LCFI41-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI41-.Ltext0
	.quad	.LCFI42-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI42-.Ltext0
	.quad	.LFE23-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST38:
	.quad	.LVL16-.Ltext0
	.quad	.LVL17-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	0
	.quad	0
.LLST39:
	.quad	.LVL19-.Ltext0
	.quad	.LVL20-.Ltext0
	.value	0x1
	.byte	0x5e
	.quad	.LVL24-.Ltext0
	.quad	.LVL25-.Ltext0
	.value	0x1
	.byte	0x5c
	.quad	0
	.quad	0
.LLST40:
	.quad	.LVL18-.Ltext0
	.quad	.LVL20-.Ltext0
	.value	0x1
	.byte	0x5e
	.quad	.LVL21-.Ltext0
	.quad	.LVL22-1-.Ltext0
	.value	0x5
	.byte	0x7d
	.sleb128 0
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.quad	.LVL22-1-.Ltext0
	.quad	.LVL25-.Ltext0
	.value	0x1
	.byte	0x5c
	.quad	0
	.quad	0
.LLST41:
	.quad	.LVL21-.Ltext0
	.quad	.LVL23-.Ltext0
	.value	0x8
	.byte	0x73
	.sleb128 0
	.byte	0x91
	.sleb128 -152
	.byte	0x6
	.byte	0x22
	.byte	0x9f
	.quad	.LVL23-.Ltext0
	.quad	.LVL25-.Ltext0
	.value	0xb
	.byte	0x73
	.sleb128 0
	.byte	0x91
	.sleb128 -152
	.byte	0x6
	.byte	0x22
	.byte	0x9
	.byte	0xec
	.byte	0x22
	.byte	0x9f
	.quad	0
	.quad	0
.LLST42:
	.quad	.LFB24-.Ltext0
	.quad	.LCFI43-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI43-.Ltext0
	.quad	.LCFI44-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI44-.Ltext0
	.quad	.LCFI45-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI45-.Ltext0
	.quad	.LCFI46-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI46-.Ltext0
	.quad	.LCFI47-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI47-.Ltext0
	.quad	.LCFI48-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI48-.Ltext0
	.quad	.LCFI49-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI49-.Ltext0
	.quad	.LCFI50-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 128
	.quad	.LCFI50-.Ltext0
	.quad	.LCFI51-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI51-.Ltext0
	.quad	.LCFI52-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI52-.Ltext0
	.quad	.LCFI53-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI53-.Ltext0
	.quad	.LCFI54-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI54-.Ltext0
	.quad	.LCFI55-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI55-.Ltext0
	.quad	.LCFI56-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI56-.Ltext0
	.quad	.LFE24-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST43:
	.quad	.LVL26-.Ltext0
	.quad	.LVL27-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	0
	.quad	0
.LLST44:
	.quad	.LFB25-.Ltext0
	.quad	.LCFI57-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI57-.Ltext0
	.quad	.LCFI58-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI58-.Ltext0
	.quad	.LCFI59-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI59-.Ltext0
	.quad	.LCFI60-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI60-.Ltext0
	.quad	.LCFI61-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI61-.Ltext0
	.quad	.LCFI62-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI62-.Ltext0
	.quad	.LCFI63-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI63-.Ltext0
	.quad	.LCFI64-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 224
	.quad	.LCFI64-.Ltext0
	.quad	.LCFI65-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI65-.Ltext0
	.quad	.LCFI66-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI66-.Ltext0
	.quad	.LCFI67-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI67-.Ltext0
	.quad	.LCFI68-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI68-.Ltext0
	.quad	.LCFI69-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI69-.Ltext0
	.quad	.LCFI70-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI70-.Ltext0
	.quad	.LFE25-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST45:
	.quad	.LVL28-.Ltext0
	.quad	.LVL29-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL29-.Ltext0
	.quad	.LVL35-.Ltext0
	.value	0x1
	.byte	0x5d
	.quad	0
	.quad	0
.LLST46:
	.quad	.LVL28-.Ltext0
	.quad	.LVL29-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x28
	.byte	0x6
	.quad	.LVL29-.Ltext0
	.quad	.LVL35-.Ltext0
	.value	0x5
	.byte	0x7d
	.sleb128 0
	.byte	0x23
	.uleb128 0x28
	.byte	0x6
	.quad	0
	.quad	0
.LLST47:
	.quad	.LVL31-.Ltext0
	.quad	.LVL32-1-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL33-.Ltext0
	.quad	.LVL34-1-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	0
	.quad	0
.LLST48:
	.quad	.LFB26-.Ltext0
	.quad	.LCFI71-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI71-.Ltext0
	.quad	.LCFI72-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI72-.Ltext0
	.quad	.LCFI73-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI73-.Ltext0
	.quad	.LCFI74-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI74-.Ltext0
	.quad	.LCFI75-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI75-.Ltext0
	.quad	.LCFI76-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI76-.Ltext0
	.quad	.LCFI77-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI77-.Ltext0
	.quad	.LCFI78-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 144
	.quad	.LCFI78-.Ltext0
	.quad	.LCFI79-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI79-.Ltext0
	.quad	.LCFI80-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI80-.Ltext0
	.quad	.LCFI81-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI81-.Ltext0
	.quad	.LCFI82-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI82-.Ltext0
	.quad	.LCFI83-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI83-.Ltext0
	.quad	.LCFI84-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI84-.Ltext0
	.quad	.LFE26-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST49:
	.quad	.LVL36-.Ltext0
	.quad	.LVL37-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	0
	.quad	0
.LLST50:
	.quad	.LVL39-.Ltext0
	.quad	.LVL40-1-.Ltext0
	.value	0x7
	.byte	0x7d
	.sleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x76
	.sleb128 0
	.byte	0x22
	.quad	.LVL41-.Ltext0
	.quad	.LVL42-1-.Ltext0
	.value	0x5
	.byte	0x76
	.sleb128 0
	.byte	0x7d
	.sleb128 0
	.byte	0x22
	.quad	0
	.quad	0
.LLST51:
	.quad	.LVL39-.Ltext0
	.quad	.LVL40-1-.Ltext0
	.value	0x7
	.byte	0x7d
	.sleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x7c
	.sleb128 0
	.byte	0x22
	.quad	.LVL41-.Ltext0
	.quad	.LVL42-1-.Ltext0
	.value	0x5
	.byte	0x7c
	.sleb128 0
	.byte	0x7d
	.sleb128 0
	.byte	0x22
	.quad	0
	.quad	0
.LLST52:
	.quad	.LFB27-.Ltext0
	.quad	.LCFI85-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI85-.Ltext0
	.quad	.LCFI86-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI86-.Ltext0
	.quad	.LCFI87-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI87-.Ltext0
	.quad	.LCFI88-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI88-.Ltext0
	.quad	.LCFI89-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI89-.Ltext0
	.quad	.LCFI90-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI90-.Ltext0
	.quad	.LCFI91-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI91-.Ltext0
	.quad	.LCFI92-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 128
	.quad	.LCFI92-.Ltext0
	.quad	.LCFI93-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI93-.Ltext0
	.quad	.LCFI94-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI94-.Ltext0
	.quad	.LCFI95-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI95-.Ltext0
	.quad	.LCFI96-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI96-.Ltext0
	.quad	.LCFI97-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI97-.Ltext0
	.quad	.LCFI98-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI98-.Ltext0
	.quad	.LFE27-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST53:
	.quad	.LVL43-.Ltext0
	.quad	.LVL44-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	0
	.quad	0
.LLST54:
	.quad	.LVL45-.Ltext0
	.quad	.LVL46-.Ltext0
	.value	0x7
	.byte	0x76
	.sleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.quad	.LVL46-.Ltext0
	.quad	.LVL47-1-.Ltext0
	.value	0x7
	.byte	0x76
	.sleb128 -1
	.byte	0x32
	.byte	0x24
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.quad	.LVL48-.Ltext0
	.quad	.LVL49-.Ltext0
	.value	0x5
	.byte	0x7e
	.sleb128 0
	.byte	0x76
	.sleb128 0
	.byte	0x22
	.quad	.LVL49-.Ltext0
	.quad	.LVL50-1-.Ltext0
	.value	0x8
	.byte	0x7e
	.sleb128 0
	.byte	0x76
	.sleb128 0
	.byte	0x22
	.byte	0x9
	.byte	0xfc
	.byte	0x22
	.quad	0
	.quad	0
.LLST55:
	.quad	.LVL45-.Ltext0
	.quad	.LVL46-.Ltext0
	.value	0x7
	.byte	0x76
	.sleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x7d
	.sleb128 0
	.byte	0x22
	.quad	.LVL46-.Ltext0
	.quad	.LVL47-1-.Ltext0
	.value	0x7
	.byte	0x76
	.sleb128 -1
	.byte	0x32
	.byte	0x24
	.byte	0x7d
	.sleb128 0
	.byte	0x22
	.quad	.LVL48-.Ltext0
	.quad	.LVL49-.Ltext0
	.value	0x5
	.byte	0x7d
	.sleb128 0
	.byte	0x76
	.sleb128 0
	.byte	0x22
	.quad	.LVL49-.Ltext0
	.quad	.LVL50-1-.Ltext0
	.value	0x8
	.byte	0x7d
	.sleb128 0
	.byte	0x76
	.sleb128 0
	.byte	0x22
	.byte	0x9
	.byte	0xfc
	.byte	0x22
	.quad	0
	.quad	0
.LLST56:
	.quad	.LFB28-.Ltext0
	.quad	.LCFI99-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI99-.Ltext0
	.quad	.LCFI100-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI100-.Ltext0
	.quad	.LCFI101-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI101-.Ltext0
	.quad	.LCFI102-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI102-.Ltext0
	.quad	.LCFI103-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI103-.Ltext0
	.quad	.LCFI104-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI104-.Ltext0
	.quad	.LCFI105-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI105-.Ltext0
	.quad	.LCFI106-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 160
	.quad	.LCFI106-.Ltext0
	.quad	.LCFI107-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI107-.Ltext0
	.quad	.LCFI108-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI108-.Ltext0
	.quad	.LCFI109-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI109-.Ltext0
	.quad	.LCFI110-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI110-.Ltext0
	.quad	.LCFI111-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI111-.Ltext0
	.quad	.LCFI112-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI112-.Ltext0
	.quad	.LFE28-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST57:
	.quad	.LVL51-.Ltext0
	.quad	.LVL52-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	0
	.quad	0
.LLST58:
	.quad	.LVL54-.Ltext0
	.quad	.LVL55-1-.Ltext0
	.value	0x7
	.byte	0x76
	.sleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x7f
	.sleb128 0
	.byte	0x22
	.quad	.LVL56-.Ltext0
	.quad	.LVL57-1-.Ltext0
	.value	0x5
	.byte	0x7f
	.sleb128 0
	.byte	0x76
	.sleb128 0
	.byte	0x22
	.quad	0
	.quad	0
.LLST59:
	.quad	.LVL54-.Ltext0
	.quad	.LVL55-1-.Ltext0
	.value	0x7
	.byte	0x76
	.sleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.quad	.LVL56-.Ltext0
	.quad	.LVL57-1-.Ltext0
	.value	0x5
	.byte	0x7e
	.sleb128 0
	.byte	0x76
	.sleb128 0
	.byte	0x22
	.quad	0
	.quad	0
.LLST60:
	.quad	.LFB22-.Ltext0
	.quad	.LCFI113-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI113-.Ltext0
	.quad	.LCFI114-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI114-.Ltext0
	.quad	.LCFI115-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI115-.Ltext0
	.quad	.LCFI116-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI116-.Ltext0
	.quad	.LCFI117-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI117-.Ltext0
	.quad	.LCFI118-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI118-.Ltext0
	.quad	.LCFI119-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI119-.Ltext0
	.quad	.LCFI120-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 3776
	.quad	.LCFI120-.Ltext0
	.quad	.LCFI121-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI121-.Ltext0
	.quad	.LCFI122-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI122-.Ltext0
	.quad	.LCFI123-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI123-.Ltext0
	.quad	.LCFI124-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI124-.Ltext0
	.quad	.LCFI125-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI125-.Ltext0
	.quad	.LCFI126-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI126-.Ltext0
	.quad	.LCFI127-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI127-.Ltext0
	.quad	.LFE22-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 3776
	.quad	0
	.quad	0
.LLST61:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	0
	.quad	0
.LLST62:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x158
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x158
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x158
	.quad	0
	.quad	0
.LLST63:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x150
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x150
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x150
	.quad	0
	.quad	0
.LLST64:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x148
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x148
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x148
	.quad	0
	.quad	0
.LLST65:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x140
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x140
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x140
	.quad	0
	.quad	0
.LLST66:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x138
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x138
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x138
	.quad	0
	.quad	0
.LLST67:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x130
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x130
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x130
	.quad	0
	.quad	0
.LLST68:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x128
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x128
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x128
	.quad	0
	.quad	0
.LLST69:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x120
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x120
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x120
	.quad	0
	.quad	0
.LLST70:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x118
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x118
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x118
	.quad	0
	.quad	0
.LLST71:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x110
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x110
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x110
	.quad	0
	.quad	0
.LLST72:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x108
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x108
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x108
	.quad	0
	.quad	0
.LLST73:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0x100
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x100
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0x100
	.quad	0
	.quad	0
.LLST74:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xf8
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xf8
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xf8
	.quad	0
	.quad	0
.LLST75:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xf0
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xf0
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xf0
	.quad	0
	.quad	0
.LLST76:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xe8
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xe8
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xe8
	.quad	0
	.quad	0
.LLST77:
	.quad	.LVL58-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x23
	.uleb128 0xe0
	.quad	.LVL64-.Ltext0
	.quad	.LVL67-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xe0
	.quad	.LVL68-.Ltext0
	.quad	.LVL69-.Ltext0
	.value	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x23
	.uleb128 0xe0
	.quad	0
	.quad	0
.LLST78:
	.quad	.LVL60-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x3
	.byte	0x75
	.sleb128 376
	.quad	.LVL64-.Ltext0
	.quad	.LVL66-1-.Ltext0
	.value	0x3
	.byte	0x73
	.sleb128 376
	.quad	0
	.quad	0
.LLST79:
	.quad	.LVL60-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x3
	.byte	0x75
	.sleb128 372
	.quad	.LVL64-.Ltext0
	.quad	.LVL66-1-.Ltext0
	.value	0x3
	.byte	0x73
	.sleb128 372
	.quad	0
	.quad	0
.LLST80:
	.quad	.LVL61-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x3
	.byte	0x75
	.sleb128 368
	.quad	.LVL64-.Ltext0
	.quad	.LVL66-1-.Ltext0
	.value	0x3
	.byte	0x73
	.sleb128 368
	.quad	.LVL66-1-.Ltext0
	.quad	.LFE22-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -3708
	.quad	0
	.quad	0
.LLST81:
	.quad	.LVL62-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x3
	.byte	0x75
	.sleb128 360
	.quad	.LVL64-.Ltext0
	.quad	.LVL66-1-.Ltext0
	.value	0x3
	.byte	0x73
	.sleb128 360
	.quad	0
	.quad	0
.LLST82:
	.quad	.LFB21-.Ltext0
	.quad	.LCFI128-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI128-.Ltext0
	.quad	.LCFI129-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI129-.Ltext0
	.quad	.LCFI130-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI130-.Ltext0
	.quad	.LCFI131-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI131-.Ltext0
	.quad	.LCFI132-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI132-.Ltext0
	.quad	.LCFI133-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI133-.Ltext0
	.quad	.LCFI134-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI134-.Ltext0
	.quad	.LCFI135-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 672
	.quad	.LCFI135-.Ltext0
	.quad	.LCFI136-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI136-.Ltext0
	.quad	.LCFI137-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI137-.Ltext0
	.quad	.LCFI138-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI138-.Ltext0
	.quad	.LCFI139-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI139-.Ltext0
	.quad	.LCFI140-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI140-.Ltext0
	.quad	.LCFI141-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI141-.Ltext0
	.quad	.LFE21-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST83:
	.quad	.LVL70-.Ltext0
	.quad	.LVL72-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	0
	.quad	0
.LLST84:
	.quad	.LVL70-.Ltext0
	.quad	.LVL71-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	0
	.quad	0
.LLST85:
	.quad	.LVL75-.Ltext0
	.quad	.LVL76-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL76-1-.Ltext0
	.quad	.LVL106-.Ltext0
	.value	0x1
	.byte	0x5c
	.quad	.LVL106-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -304
	.quad	0
	.quad	0
.LLST86:
	.quad	.LVL77-.Ltext0
	.quad	.LVL78-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL78-1-.Ltext0
	.quad	.LVL104-.Ltext0
	.value	0x1
	.byte	0x56
	.quad	.LVL107-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -296
	.quad	.LVL114-1-.Ltext0
	.quad	.LFE21-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -600
	.quad	0
	.quad	0
.LLST87:
	.quad	.LVL79-.Ltext0
	.quad	.LVL80-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL80-1-.Ltext0
	.quad	.LVL103-.Ltext0
	.value	0x1
	.byte	0x5e
	.quad	.LVL105-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -320
	.quad	.LVL114-1-.Ltext0
	.quad	.LFE21-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -616
	.quad	0
	.quad	0
.LLST88:
	.quad	.LVL81-.Ltext0
	.quad	.LVL82-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL82-1-.Ltext0
	.quad	.LVL106-.Ltext0
	.value	0x1
	.byte	0x5d
	.quad	.LVL106-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -312
	.quad	.LVL114-1-.Ltext0
	.quad	.LFE21-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -608
	.quad	0
	.quad	0
.LLST89:
	.quad	.LVL83-.Ltext0
	.quad	.LVL84-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL84-1-.Ltext0
	.quad	.LVL101-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	.LVL101-.Ltext0
	.quad	.LVL102-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -288
	.quad	.LVL108-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -288
	.quad	.LVL114-1-.Ltext0
	.quad	.LFE21-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -592
	.quad	0
	.quad	0
.LLST90:
	.quad	.LVL109-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -280
	.quad	.LVL114-1-.Ltext0
	.quad	.LFE21-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -584
	.quad	0
	.quad	0
.LLST91:
	.quad	.LVL109-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -272
	.quad	.LVL114-1-.Ltext0
	.quad	.LVL120-.Ltext0
	.value	0x1
	.byte	0x5f
	.quad	0
	.quad	0
.LLST92:
	.quad	.LVL109-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -264
	.quad	.LVL114-1-.Ltext0
	.quad	.LVL119-.Ltext0
	.value	0x1
	.byte	0x5e
	.quad	0
	.quad	0
.LLST93:
	.quad	.LVL85-.Ltext0
	.quad	.LVL86-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL86-1-.Ltext0
	.quad	.LVL109-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -616
	.quad	.LVL109-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -256
	.quad	.LVL114-1-.Ltext0
	.quad	.LVL116-.Ltext0
	.value	0x1
	.byte	0x56
	.quad	0
	.quad	0
.LLST94:
	.quad	.LVL87-.Ltext0
	.quad	.LVL88-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL88-1-.Ltext0
	.quad	.LVL109-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -608
	.quad	.LVL109-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -248
	.quad	.LVL114-1-.Ltext0
	.quad	.LVL115-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	0
	.quad	0
.LLST95:
	.quad	.LVL89-.Ltext0
	.quad	.LVL90-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL90-1-.Ltext0
	.quad	.LVL110-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -600
	.quad	.LVL110-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -240
	.quad	.LVL114-1-.Ltext0
	.quad	.LFE21-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -576
	.quad	0
	.quad	0
.LLST96:
	.quad	.LVL91-.Ltext0
	.quad	.LVL92-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL92-1-.Ltext0
	.quad	.LVL111-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -592
	.quad	.LVL111-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -232
	.quad	.LVL114-1-.Ltext0
	.quad	.LFE21-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -568
	.quad	0
	.quad	0
.LLST97:
	.quad	.LVL93-.Ltext0
	.quad	.LVL94-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL94-1-.Ltext0
	.quad	.LVL112-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -584
	.quad	.LVL112-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -224
	.quad	.LVL114-1-.Ltext0
	.quad	.LFE21-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -560
	.quad	0
	.quad	0
.LLST98:
	.quad	.LVL95-.Ltext0
	.quad	.LVL96-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL96-1-.Ltext0
	.quad	.LVL113-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -576
	.quad	.LVL113-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -216
	.quad	.LVL114-1-.Ltext0
	.quad	.LFE21-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -552
	.quad	0
	.quad	0
.LLST99:
	.quad	.LVL97-.Ltext0
	.quad	.LVL98-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL98-1-.Ltext0
	.quad	.LVL113-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -568
	.quad	.LVL113-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -208
	.quad	.LVL114-1-.Ltext0
	.quad	.LVL118-.Ltext0
	.value	0x1
	.byte	0x5d
	.quad	0
	.quad	0
.LLST100:
	.quad	.LVL98-.Ltext0
	.quad	.LVL99-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL113-.Ltext0
	.quad	.LVL114-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -200
	.quad	.LVL114-1-.Ltext0
	.quad	.LVL117-.Ltext0
	.value	0x1
	.byte	0x5c
	.quad	0
	.quad	0
	.file 3 "/media/disk/local/dev/omp-stream/install/lib/gcc/x86_64-unknown-linux-gnu/4.6.0/include/stddef.h"
	.file 4 "/usr/include/bits/types.h"
	.file 5 "/usr/include/stdio.h"
	.file 6 "/usr/include/libio.h"
	.section	.debug_info
	.long	0x1897
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF173
	.byte	0x1
	.long	.LASF174
	.long	.LASF175
	.quad	.Ltext0
	.quad	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF7
	.byte	0x3
	.byte	0xd3
	.long	0x38
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x2
	.long	.LASF8
	.byte	0x4
	.byte	0x8d
	.long	0x69
	.uleb128 0x2
	.long	.LASF9
	.byte	0x4
	.byte	0x8e
	.long	0x69
	.uleb128 0x5
	.long	0x62
	.long	0x96
	.uleb128 0x6
	.long	0x96
	.byte	0x1
	.byte	0
	.uleb128 0x7
	.byte	0x8
	.byte	0x7
	.uleb128 0x8
	.byte	0x8
	.uleb128 0x9
	.byte	0x8
	.long	0xa1
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF10
	.uleb128 0x2
	.long	.LASF11
	.byte	0x5
	.byte	0x31
	.long	0xb3
	.uleb128 0xa
	.long	.LASF41
	.byte	0xd8
	.byte	0x6
	.value	0x10f
	.long	0x280
	.uleb128 0xb
	.long	.LASF12
	.byte	0x6
	.value	0x110
	.long	0x62
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xb
	.long	.LASF13
	.byte	0x6
	.value	0x115
	.long	0x9b
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xb
	.long	.LASF14
	.byte	0x6
	.value	0x116
	.long	0x9b
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xb
	.long	.LASF15
	.byte	0x6
	.value	0x117
	.long	0x9b
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xb
	.long	.LASF16
	.byte	0x6
	.value	0x118
	.long	0x9b
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xb
	.long	.LASF17
	.byte	0x6
	.value	0x119
	.long	0x9b
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xb
	.long	.LASF18
	.byte	0x6
	.value	0x11a
	.long	0x9b
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xb
	.long	.LASF19
	.byte	0x6
	.value	0x11b
	.long	0x9b
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0xb
	.long	.LASF20
	.byte	0x6
	.value	0x11c
	.long	0x9b
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0xb
	.long	.LASF21
	.byte	0x6
	.value	0x11e
	.long	0x9b
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0xb
	.long	.LASF22
	.byte	0x6
	.value	0x11f
	.long	0x9b
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0xb
	.long	.LASF23
	.byte	0x6
	.value	0x120
	.long	0x9b
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0xb
	.long	.LASF24
	.byte	0x6
	.value	0x122
	.long	0x2be
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0xb
	.long	.LASF25
	.byte	0x6
	.value	0x124
	.long	0x2c4
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0xb
	.long	.LASF26
	.byte	0x6
	.value	0x126
	.long	0x62
	.byte	0x2
	.byte	0x23
	.uleb128 0x70
	.uleb128 0xb
	.long	.LASF27
	.byte	0x6
	.value	0x12a
	.long	0x62
	.byte	0x2
	.byte	0x23
	.uleb128 0x74
	.uleb128 0xb
	.long	.LASF28
	.byte	0x6
	.value	0x12c
	.long	0x70
	.byte	0x2
	.byte	0x23
	.uleb128 0x78
	.uleb128 0xb
	.long	.LASF29
	.byte	0x6
	.value	0x130
	.long	0x46
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0xb
	.long	.LASF30
	.byte	0x6
	.value	0x131
	.long	0x54
	.byte	0x3
	.byte	0x23
	.uleb128 0x82
	.uleb128 0xb
	.long	.LASF31
	.byte	0x6
	.value	0x132
	.long	0x2ca
	.byte	0x3
	.byte	0x23
	.uleb128 0x83
	.uleb128 0xb
	.long	.LASF32
	.byte	0x6
	.value	0x136
	.long	0x2da
	.byte	0x3
	.byte	0x23
	.uleb128 0x88
	.uleb128 0xb
	.long	.LASF33
	.byte	0x6
	.value	0x13f
	.long	0x7b
	.byte	0x3
	.byte	0x23
	.uleb128 0x90
	.uleb128 0xb
	.long	.LASF34
	.byte	0x6
	.value	0x148
	.long	0x99
	.byte	0x3
	.byte	0x23
	.uleb128 0x98
	.uleb128 0xb
	.long	.LASF35
	.byte	0x6
	.value	0x149
	.long	0x99
	.byte	0x3
	.byte	0x23
	.uleb128 0xa0
	.uleb128 0xb
	.long	.LASF36
	.byte	0x6
	.value	0x14a
	.long	0x99
	.byte	0x3
	.byte	0x23
	.uleb128 0xa8
	.uleb128 0xb
	.long	.LASF37
	.byte	0x6
	.value	0x14b
	.long	0x99
	.byte	0x3
	.byte	0x23
	.uleb128 0xb0
	.uleb128 0xb
	.long	.LASF38
	.byte	0x6
	.value	0x14c
	.long	0x2d
	.byte	0x3
	.byte	0x23
	.uleb128 0xb8
	.uleb128 0xb
	.long	.LASF39
	.byte	0x6
	.value	0x14e
	.long	0x62
	.byte	0x3
	.byte	0x23
	.uleb128 0xc0
	.uleb128 0xb
	.long	.LASF40
	.byte	0x6
	.value	0x150
	.long	0x2e0
	.byte	0x3
	.byte	0x23
	.uleb128 0xc4
	.byte	0
	.uleb128 0xc
	.long	.LASF176
	.byte	0x6
	.byte	0xb4
	.uleb128 0xd
	.long	.LASF42
	.byte	0x18
	.byte	0x6
	.byte	0xba
	.long	0x2be
	.uleb128 0xe
	.long	.LASF43
	.byte	0x6
	.byte	0xbb
	.long	0x2be
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xe
	.long	.LASF44
	.byte	0x6
	.byte	0xbc
	.long	0x2c4
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xe
	.long	.LASF45
	.byte	0x6
	.byte	0xc0
	.long	0x62
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0x287
	.uleb128 0x9
	.byte	0x8
	.long	0xb3
	.uleb128 0x5
	.long	0xa1
	.long	0x2da
	.uleb128 0x6
	.long	0x96
	.byte	0
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0x280
	.uleb128 0x5
	.long	0xa1
	.long	0x2f0
	.uleb128 0x6
	.long	0x96
	.byte	0x13
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0x2f6
	.uleb128 0xf
	.long	0xa1
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF46
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF47
	.uleb128 0x3
	.byte	0x4
	.byte	0x4
	.long	.LASF48
	.uleb128 0x3
	.byte	0x8
	.byte	0x4
	.long	.LASF49
	.uleb128 0xd
	.long	.LASF50
	.byte	0x8
	.byte	0x1
	.byte	0x1a
	.long	0x33e
	.uleb128 0x10
	.string	"re"
	.byte	0x1
	.byte	0x1c
	.long	0x62
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x10
	.string	"im"
	.byte	0x1
	.byte	0x1d
	.long	0x62
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0x2
	.long	.LASF50
	.byte	0x1
	.byte	0x1e
	.long	0x317
	.uleb128 0xd
	.long	.LASF51
	.byte	0x8
	.byte	0x1
	.byte	0x20
	.long	0x370
	.uleb128 0x10
	.string	"re"
	.byte	0x1
	.byte	0x22
	.long	0x309
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x10
	.string	"im"
	.byte	0x1
	.byte	0x23
	.long	0x309
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0x2
	.long	.LASF51
	.byte	0x1
	.byte	0x24
	.long	0x349
	.uleb128 0x11
	.byte	0x1
	.long	.LASF177
	.byte	0x2
	.value	0x117
	.byte	0x1
	.long	0x310
	.byte	0x3
	.long	0x39b
	.uleb128 0x12
	.long	.LASF52
	.byte	0x2
	.value	0x117
	.long	0x2f0
	.byte	0
	.uleb128 0x13
	.long	.LASF70
	.byte	0x1
	.byte	0x1
	.quad	.LFB29
	.quad	.LFE29
	.long	.LLST0
	.long	0x444
	.uleb128 0x14
	.long	.LASF53
	.long	0x516
	.byte	0x1
	.long	.LLST1
	.uleb128 0x15
	.long	.LASF54
	.byte	0x1
	.byte	0x56
	.long	0x510
	.long	.LLST2
	.uleb128 0x15
	.long	.LASF55
	.byte	0x1
	.byte	0x56
	.long	0x510
	.long	.LLST3
	.uleb128 0x15
	.long	.LASF56
	.byte	0x1
	.byte	0x54
	.long	0x510
	.long	.LLST4
	.uleb128 0x15
	.long	.LASF57
	.byte	0x1
	.byte	0x54
	.long	0x510
	.long	.LLST5
	.uleb128 0x15
	.long	.LASF58
	.byte	0x1
	.byte	0x53
	.long	0x510
	.long	.LLST6
	.uleb128 0x15
	.long	.LASF59
	.byte	0x1
	.byte	0x53
	.long	0x510
	.long	.LLST7
	.uleb128 0x16
	.long	.LASF60
	.byte	0x1
	.byte	0x31
	.long	0x33e
	.uleb128 0x16
	.long	.LASF61
	.byte	0x1
	.byte	0x2e
	.long	0x33e
	.uleb128 0x16
	.long	.LASF62
	.byte	0x1
	.byte	0x2d
	.long	0x33e
	.byte	0
	.uleb128 0x17
	.long	.LASF101
	.byte	0x60
	.long	0x4f7
	.uleb128 0xe
	.long	.LASF63
	.byte	0x1
	.byte	0xcd
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xe
	.long	.LASF64
	.byte	0x1
	.byte	0xcd
	.long	0x4f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xe
	.long	.LASF65
	.byte	0x1
	.byte	0xcd
	.long	0x4fd
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xe
	.long	.LASF66
	.byte	0x1
	.byte	0x9b
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xe
	.long	.LASF67
	.byte	0x1
	.byte	0x9b
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xe
	.long	.LASF68
	.byte	0x1
	.byte	0xa5
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xe
	.long	.LASF59
	.byte	0x1
	.byte	0x53
	.long	0x50a
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xe
	.long	.LASF58
	.byte	0x1
	.byte	0x53
	.long	0x50a
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0xe
	.long	.LASF57
	.byte	0x1
	.byte	0x54
	.long	0x50a
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0xe
	.long	.LASF56
	.byte	0x1
	.byte	0x54
	.long	0x50a
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0xe
	.long	.LASF55
	.byte	0x1
	.byte	0x56
	.long	0x50a
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0xe
	.long	.LASF54
	.byte	0x1
	.byte	0x56
	.long	0x50a
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0x302
	.uleb128 0x9
	.byte	0x8
	.long	0x503
	.uleb128 0x3
	.byte	0x1
	.byte	0x2
	.long	.LASF69
	.uleb128 0x9
	.byte	0x8
	.long	0x510
	.uleb128 0x9
	.byte	0x8
	.long	0xa8
	.uleb128 0x9
	.byte	0x8
	.long	0x444
	.uleb128 0x13
	.long	.LASF71
	.byte	0x1
	.byte	0x1
	.quad	.LFB30
	.quad	.LFE30
	.long	.LLST8
	.long	0x70e
	.uleb128 0x14
	.long	.LASF53
	.long	0x926
	.byte	0x1
	.long	.LLST9
	.uleb128 0x15
	.long	.LASF72
	.byte	0x1
	.byte	0x58
	.long	0x510
	.long	.LLST10
	.uleb128 0x15
	.long	.LASF73
	.byte	0x1
	.byte	0x58
	.long	0x510
	.long	.LLST11
	.uleb128 0x15
	.long	.LASF74
	.byte	0x1
	.byte	0x57
	.long	0x510
	.long	.LLST12
	.uleb128 0x15
	.long	.LASF75
	.byte	0x1
	.byte	0x57
	.long	0x510
	.long	.LLST13
	.uleb128 0x15
	.long	.LASF76
	.byte	0x1
	.byte	0x59
	.long	0x510
	.long	.LLST14
	.uleb128 0x15
	.long	.LASF77
	.byte	0x1
	.byte	0x59
	.long	0x510
	.long	.LLST15
	.uleb128 0x15
	.long	.LASF78
	.byte	0x1
	.byte	0x55
	.long	0x510
	.long	.LLST16
	.uleb128 0x15
	.long	.LASF79
	.byte	0x1
	.byte	0x55
	.long	0x510
	.long	.LLST17
	.uleb128 0x15
	.long	.LASF80
	.byte	0x1
	.byte	0x48
	.long	0x62
	.long	.LLST18
	.uleb128 0x18
	.string	"i"
	.byte	0x1
	.byte	0x3d
	.long	0x62
	.long	.LLST19
	.uleb128 0x15
	.long	.LASF81
	.byte	0x1
	.byte	0x45
	.long	0x910
	.long	.LLST20
	.uleb128 0x15
	.long	.LASF82
	.byte	0x1
	.byte	0x44
	.long	0x910
	.long	.LLST21
	.uleb128 0x15
	.long	.LASF83
	.byte	0x1
	.byte	0x43
	.long	0x910
	.long	.LLST22
	.uleb128 0x15
	.long	.LASF84
	.byte	0x1
	.byte	0x42
	.long	0x910
	.long	.LLST23
	.uleb128 0x15
	.long	.LASF85
	.byte	0x1
	.byte	0x46
	.long	0x62
	.long	.LLST24
	.uleb128 0x15
	.long	.LASF86
	.byte	0x1
	.byte	0x3f
	.long	0x910
	.long	.LLST25
	.uleb128 0x15
	.long	.LASF87
	.byte	0x1
	.byte	0x3f
	.long	0x910
	.long	.LLST26
	.uleb128 0x15
	.long	.LASF88
	.byte	0x1
	.byte	0x41
	.long	0x8fa
	.long	.LLST27
	.uleb128 0x15
	.long	.LASF89
	.byte	0x1
	.byte	0x40
	.long	0x8fa
	.long	.LLST28
	.uleb128 0x15
	.long	.LASF90
	.byte	0x1
	.byte	0x3e
	.long	0x309
	.long	.LLST29
	.uleb128 0x15
	.long	.LASF91
	.byte	0x1
	.byte	0x3c
	.long	0x8e4
	.long	.LLST30
	.uleb128 0x15
	.long	.LASF92
	.byte	0x1
	.byte	0x3c
	.long	0x8e4
	.long	.LLST31
	.uleb128 0x15
	.long	.LASF93
	.byte	0x1
	.byte	0x3b
	.long	0x62
	.long	.LLST32
	.uleb128 0x15
	.long	.LASF94
	.byte	0x1
	.byte	0x3a
	.long	0x309
	.long	.LLST33
	.uleb128 0x15
	.long	.LASF95
	.byte	0x1
	.byte	0x39
	.long	0x309
	.long	.LLST34
	.uleb128 0x15
	.long	.LASF96
	.byte	0x1
	.byte	0x47
	.long	0x62
	.long	.LLST35
	.uleb128 0x16
	.long	.LASF97
	.byte	0x1
	.byte	0x38
	.long	0x62
	.uleb128 0x16
	.long	.LASF98
	.byte	0x1
	.byte	0x8b
	.long	0x86
	.uleb128 0x16
	.long	.LASF99
	.byte	0x1
	.byte	0x37
	.long	0x33e
	.uleb128 0x16
	.long	.LASF100
	.byte	0x1
	.byte	0x8a
	.long	0x92c
	.uleb128 0x19
	.long	.Ldebug_ranges0+0
	.uleb128 0x1a
	.string	"j"
	.byte	0x1
	.value	0x10a
	.long	0x62
	.long	.LLST36
	.byte	0
	.byte	0
	.uleb128 0x17
	.long	.LASF102
	.byte	0xf8
	.long	0x8d8
	.uleb128 0xe
	.long	.LASF103
	.byte	0x1
	.byte	0xde
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xe
	.long	.LASF104
	.byte	0x1
	.byte	0xde
	.long	0x4f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xe
	.long	.LASF105
	.byte	0x1
	.byte	0xde
	.long	0x4fd
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xe
	.long	.LASF106
	.byte	0x1
	.byte	0xc3
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xe
	.long	.LASF107
	.byte	0x1
	.byte	0xc3
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xe
	.long	.LASF96
	.byte	0x1
	.byte	0x47
	.long	0x8d8
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xe
	.long	.LASF95
	.byte	0x1
	.byte	0x39
	.long	0x8de
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xe
	.long	.LASF94
	.byte	0x1
	.byte	0x3a
	.long	0x8de
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0xe
	.long	.LASF93
	.byte	0x1
	.byte	0x3b
	.long	0x8d8
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0xe
	.long	.LASF92
	.byte	0x1
	.byte	0x3c
	.long	0x8f4
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0xe
	.long	.LASF91
	.byte	0x1
	.byte	0x3c
	.long	0x8f4
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0xe
	.long	.LASF90
	.byte	0x1
	.byte	0x3e
	.long	0x8de
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0xe
	.long	.LASF89
	.byte	0x1
	.byte	0x40
	.long	0x90a
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0xe
	.long	.LASF88
	.byte	0x1
	.byte	0x41
	.long	0x90a
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0xe
	.long	.LASF87
	.byte	0x1
	.byte	0x3f
	.long	0x920
	.byte	0x2
	.byte	0x23
	.uleb128 0x70
	.uleb128 0xe
	.long	.LASF86
	.byte	0x1
	.byte	0x3f
	.long	0x920
	.byte	0x2
	.byte	0x23
	.uleb128 0x78
	.uleb128 0xe
	.long	.LASF85
	.byte	0x1
	.byte	0x46
	.long	0x8d8
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0xe
	.long	.LASF84
	.byte	0x1
	.byte	0x42
	.long	0x920
	.byte	0x3
	.byte	0x23
	.uleb128 0x88
	.uleb128 0xe
	.long	.LASF83
	.byte	0x1
	.byte	0x43
	.long	0x920
	.byte	0x3
	.byte	0x23
	.uleb128 0x90
	.uleb128 0xe
	.long	.LASF82
	.byte	0x1
	.byte	0x44
	.long	0x920
	.byte	0x3
	.byte	0x23
	.uleb128 0x98
	.uleb128 0xe
	.long	.LASF81
	.byte	0x1
	.byte	0x45
	.long	0x920
	.byte	0x3
	.byte	0x23
	.uleb128 0xa0
	.uleb128 0x10
	.string	"i"
	.byte	0x1
	.byte	0x3d
	.long	0x8d8
	.byte	0x3
	.byte	0x23
	.uleb128 0xa8
	.uleb128 0xe
	.long	.LASF80
	.byte	0x1
	.byte	0x48
	.long	0x8d8
	.byte	0x3
	.byte	0x23
	.uleb128 0xb0
	.uleb128 0xe
	.long	.LASF79
	.byte	0x1
	.byte	0x55
	.long	0x50a
	.byte	0x3
	.byte	0x23
	.uleb128 0xb8
	.uleb128 0xe
	.long	.LASF78
	.byte	0x1
	.byte	0x55
	.long	0x50a
	.byte	0x3
	.byte	0x23
	.uleb128 0xc0
	.uleb128 0xe
	.long	.LASF77
	.byte	0x1
	.byte	0x59
	.long	0x50a
	.byte	0x3
	.byte	0x23
	.uleb128 0xc8
	.uleb128 0xe
	.long	.LASF76
	.byte	0x1
	.byte	0x59
	.long	0x50a
	.byte	0x3
	.byte	0x23
	.uleb128 0xd0
	.uleb128 0xe
	.long	.LASF75
	.byte	0x1
	.byte	0x57
	.long	0x50a
	.byte	0x3
	.byte	0x23
	.uleb128 0xd8
	.uleb128 0xe
	.long	.LASF74
	.byte	0x1
	.byte	0x57
	.long	0x50a
	.byte	0x3
	.byte	0x23
	.uleb128 0xe0
	.uleb128 0xe
	.long	.LASF73
	.byte	0x1
	.byte	0x58
	.long	0x50a
	.byte	0x3
	.byte	0x23
	.uleb128 0xe8
	.uleb128 0xe
	.long	.LASF72
	.byte	0x1
	.byte	0x58
	.long	0x50a
	.byte	0x3
	.byte	0x23
	.uleb128 0xf0
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0x62
	.uleb128 0x9
	.byte	0x8
	.long	0x309
	.uleb128 0x5
	.long	0x309
	.long	0x8f4
	.uleb128 0x6
	.long	0x96
	.byte	0x3f
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0x8e4
	.uleb128 0x5
	.long	0x62
	.long	0x90a
	.uleb128 0x6
	.long	0x96
	.byte	0x67
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0x8fa
	.uleb128 0x5
	.long	0x62
	.long	0x920
	.uleb128 0x6
	.long	0x96
	.byte	0x33
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0x910
	.uleb128 0x9
	.byte	0x8
	.long	0x70e
	.uleb128 0x5
	.long	0x33e
	.long	0x93c
	.uleb128 0x6
	.long	0x96
	.byte	0x1
	.byte	0
	.uleb128 0x13
	.long	.LASF108
	.byte	0x1
	.byte	0x1
	.quad	.LFB23
	.quad	.LFE23
	.long	.LLST37
	.long	0xa1d
	.uleb128 0x14
	.long	.LASF53
	.long	0xac2
	.byte	0x1
	.long	.LLST38
	.uleb128 0x15
	.long	.LASF109
	.byte	0x1
	.byte	0x2a
	.long	0x62
	.long	.LLST39
	.uleb128 0x16
	.long	.LASF110
	.byte	0x1
	.byte	0x2c
	.long	0x370
	.uleb128 0x15
	.long	.LASF111
	.byte	0x1
	.byte	0x29
	.long	0x62
	.long	.LLST40
	.uleb128 0x16
	.long	.LASF112
	.byte	0x1
	.byte	0x50
	.long	0x2e0
	.uleb128 0x16
	.long	.LASF113
	.byte	0x1
	.byte	0x4f
	.long	0x2e0
	.uleb128 0x1b
	.long	0x37b
	.quad	.LBB17
	.long	.Ldebug_ranges0+0x80
	.byte	0x1
	.byte	0x95
	.long	0x9c5
	.uleb128 0x1c
	.long	0x38e
	.byte	0
	.uleb128 0x1b
	.long	0x37b
	.quad	.LBB21
	.long	.Ldebug_ranges0+0xb0
	.byte	0x1
	.byte	0x96
	.long	0x9e2
	.uleb128 0x1c
	.long	0x38e
	.byte	0
	.uleb128 0x1b
	.long	0x37b
	.quad	.LBB25
	.long	.Ldebug_ranges0+0xe0
	.byte	0x1
	.byte	0x95
	.long	0xa03
	.uleb128 0x1d
	.long	0x38e
	.long	.LLST41
	.byte	0
	.uleb128 0x1e
	.long	0x37b
	.quad	.LBB29
	.long	.Ldebug_ranges0+0x110
	.byte	0x1
	.byte	0x96
	.uleb128 0x1c
	.long	0x38e
	.byte	0
	.byte	0
	.uleb128 0x17
	.long	.LASF114
	.byte	0x58
	.long	0xac2
	.uleb128 0xe
	.long	.LASF115
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xe
	.long	.LASF116
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xe
	.long	.LASF117
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xe
	.long	.LASF118
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xe
	.long	.LASF119
	.byte	0x1
	.byte	0x93
	.long	0x4f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xe
	.long	.LASF120
	.byte	0x1
	.byte	0x93
	.long	0x4fd
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xe
	.long	.LASF121
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xe
	.long	.LASF122
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0xe
	.long	.LASF123
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0xe
	.long	.LASF124
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0xe
	.long	.LASF125
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0xa1d
	.uleb128 0x13
	.long	.LASF126
	.byte	0x1
	.byte	0x1
	.quad	.LFB24
	.quad	.LFE24
	.long	.LLST42
	.long	0xb17
	.uleb128 0x14
	.long	.LASF53
	.long	0xb76
	.byte	0x1
	.long	.LLST43
	.uleb128 0x16
	.long	.LASF61
	.byte	0x1
	.byte	0x2e
	.long	0x33e
	.uleb128 0x16
	.long	.LASF62
	.byte	0x1
	.byte	0x2d
	.long	0x33e
	.uleb128 0x16
	.long	.LASF110
	.byte	0x1
	.byte	0x2c
	.long	0x370
	.byte	0
	.uleb128 0x17
	.long	.LASF127
	.byte	0x30
	.long	0xb76
	.uleb128 0xe
	.long	.LASF128
	.byte	0x1
	.byte	0x9b
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xe
	.long	.LASF129
	.byte	0x1
	.byte	0x9b
	.long	0x4f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xe
	.long	.LASF130
	.byte	0x1
	.byte	0x9b
	.long	0x4fd
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xe
	.long	.LASF124
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xe
	.long	.LASF66
	.byte	0x1
	.byte	0x9b
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xe
	.long	.LASF67
	.byte	0x1
	.byte	0x9b
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0xb17
	.uleb128 0x13
	.long	.LASF131
	.byte	0x1
	.byte	0x1
	.quad	.LFB25
	.quad	.LFE25
	.long	.LLST44
	.long	0xc29
	.uleb128 0x14
	.long	.LASF53
	.long	0xcb2
	.byte	0x1
	.long	.LLST45
	.uleb128 0x1f
	.long	.LASF132
	.byte	0x1
	.byte	0x33
	.long	0x62
	.byte	0x3
	.byte	0x91
	.sleb128 -84
	.uleb128 0x1f
	.long	.LASF133
	.byte	0x1
	.byte	0x32
	.long	0x62
	.byte	0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x1f
	.long	.LASF134
	.byte	0x1
	.byte	0x2f
	.long	0x62
	.byte	0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x16
	.long	.LASF60
	.byte	0x1
	.byte	0x31
	.long	0x33e
	.uleb128 0x1f
	.long	.LASF135
	.byte	0x1
	.byte	0x36
	.long	0x62
	.byte	0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0x1f
	.long	.LASF136
	.byte	0x1
	.byte	0x30
	.long	0x62
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x15
	.long	.LASF137
	.byte	0x1
	.byte	0x2b
	.long	0x62
	.long	.LLST46
	.uleb128 0x16
	.long	.LASF61
	.byte	0x1
	.byte	0x2e
	.long	0x33e
	.uleb128 0x15
	.long	.LASF109
	.byte	0x1
	.byte	0x2a
	.long	0x62
	.long	.LLST47
	.byte	0
	.uleb128 0x17
	.long	.LASF138
	.byte	0x48
	.long	0xcb2
	.uleb128 0xe
	.long	.LASF139
	.byte	0x1
	.byte	0xa5
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xe
	.long	.LASF140
	.byte	0x1
	.byte	0xa5
	.long	0x4f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xe
	.long	.LASF141
	.byte	0x1
	.byte	0xa5
	.long	0x4fd
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xe
	.long	.LASF125
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xe
	.long	.LASF67
	.byte	0x1
	.byte	0x9b
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xe
	.long	.LASF137
	.byte	0x1
	.byte	0x2b
	.long	0x8d8
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xe
	.long	.LASF142
	.byte	0x1
	.byte	0xa5
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xe
	.long	.LASF143
	.byte	0x1
	.byte	0xa5
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0xe
	.long	.LASF68
	.byte	0x1
	.byte	0xa5
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0xc29
	.uleb128 0x13
	.long	.LASF144
	.byte	0x1
	.byte	0x1
	.quad	.LFB26
	.quad	.LFE26
	.long	.LLST48
	.long	0xd1e
	.uleb128 0x14
	.long	.LASF53
	.long	0xd8b
	.byte	0x1
	.long	.LLST49
	.uleb128 0x1f
	.long	.LASF145
	.byte	0x1
	.byte	0x34
	.long	0x62
	.byte	0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x15
	.long	.LASF136
	.byte	0x1
	.byte	0x30
	.long	0x62
	.long	.LLST50
	.uleb128 0x16
	.long	.LASF60
	.byte	0x1
	.byte	0x31
	.long	0x33e
	.uleb128 0x15
	.long	.LASF109
	.byte	0x1
	.byte	0x2a
	.long	0x62
	.long	.LLST51
	.byte	0
	.uleb128 0x17
	.long	.LASF146
	.byte	0x38
	.long	0xd8b
	.uleb128 0xe
	.long	.LASF147
	.byte	0x1
	.byte	0xb2
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xe
	.long	.LASF148
	.byte	0x1
	.byte	0xb2
	.long	0x4f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xe
	.long	.LASF149
	.byte	0x1
	.byte	0xb2
	.long	0x4fd
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xe
	.long	.LASF125
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xe
	.long	.LASF68
	.byte	0x1
	.byte	0xa5
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xe
	.long	.LASF142
	.byte	0x1
	.byte	0xa5
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xe
	.long	.LASF150
	.byte	0x1
	.byte	0xb2
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0xd1e
	.uleb128 0x13
	.long	.LASF151
	.byte	0x1
	.byte	0x1
	.quad	.LFB27
	.quad	.LFE27
	.long	.LLST52
	.long	0xdf3
	.uleb128 0x14
	.long	.LASF53
	.long	0xe60
	.byte	0x1
	.long	.LLST53
	.uleb128 0x16
	.long	.LASF152
	.byte	0x1
	.byte	0x35
	.long	0x33e
	.uleb128 0x15
	.long	.LASF145
	.byte	0x1
	.byte	0x34
	.long	0x62
	.long	.LLST54
	.uleb128 0x16
	.long	.LASF62
	.byte	0x1
	.byte	0x2d
	.long	0x33e
	.uleb128 0x15
	.long	.LASF109
	.byte	0x1
	.byte	0x2a
	.long	0x62
	.long	.LLST55
	.byte	0
	.uleb128 0x17
	.long	.LASF153
	.byte	0x38
	.long	0xe60
	.uleb128 0xe
	.long	.LASF154
	.byte	0x1
	.byte	0xba
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xe
	.long	.LASF155
	.byte	0x1
	.byte	0xba
	.long	0x4f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xe
	.long	.LASF156
	.byte	0x1
	.byte	0xba
	.long	0x4fd
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xe
	.long	.LASF125
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xe
	.long	.LASF66
	.byte	0x1
	.byte	0x9b
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xe
	.long	.LASF150
	.byte	0x1
	.byte	0xb2
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xe
	.long	.LASF157
	.byte	0x1
	.byte	0xba
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0xdf3
	.uleb128 0x13
	.long	.LASF158
	.byte	0x1
	.byte	0x1
	.quad	.LFB28
	.quad	.LFE28
	.long	.LLST56
	.long	0xed7
	.uleb128 0x14
	.long	.LASF53
	.long	0xf52
	.byte	0x1
	.long	.LLST57
	.uleb128 0x1f
	.long	.LASF97
	.byte	0x1
	.byte	0x38
	.long	0x62
	.byte	0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x16
	.long	.LASF99
	.byte	0x1
	.byte	0x37
	.long	0x33e
	.uleb128 0x16
	.long	.LASF152
	.byte	0x1
	.byte	0x35
	.long	0x33e
	.uleb128 0x15
	.long	.LASF135
	.byte	0x1
	.byte	0x36
	.long	0x62
	.long	.LLST58
	.uleb128 0x15
	.long	.LASF109
	.byte	0x1
	.byte	0x2a
	.long	0x62
	.long	.LLST59
	.byte	0
	.uleb128 0x17
	.long	.LASF159
	.byte	0x40
	.long	0xf52
	.uleb128 0xe
	.long	.LASF160
	.byte	0x1
	.byte	0xc3
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xe
	.long	.LASF161
	.byte	0x1
	.byte	0xc3
	.long	0x4f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xe
	.long	.LASF162
	.byte	0x1
	.byte	0xc3
	.long	0x4fd
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xe
	.long	.LASF125
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xe
	.long	.LASF143
	.byte	0x1
	.byte	0xa5
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xe
	.long	.LASF157
	.byte	0x1
	.byte	0xba
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xe
	.long	.LASF106
	.byte	0x1
	.byte	0xc3
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xe
	.long	.LASF107
	.byte	0x1
	.byte	0xc3
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0xed7
	.uleb128 0x13
	.long	.LASF163
	.byte	0x1
	.byte	0x1
	.quad	.LFB22
	.quad	.LFE22
	.long	.LLST60
	.long	0x1267
	.uleb128 0x14
	.long	.LASF53
	.long	0x157c
	.byte	0x1
	.long	.LLST61
	.uleb128 0x15
	.long	.LASF76
	.byte	0x1
	.byte	0x59
	.long	0x510
	.long	.LLST62
	.uleb128 0x15
	.long	.LASF77
	.byte	0x1
	.byte	0x59
	.long	0x510
	.long	.LLST63
	.uleb128 0x15
	.long	.LASF72
	.byte	0x1
	.byte	0x58
	.long	0x510
	.long	.LLST64
	.uleb128 0x15
	.long	.LASF73
	.byte	0x1
	.byte	0x58
	.long	0x510
	.long	.LLST65
	.uleb128 0x15
	.long	.LASF74
	.byte	0x1
	.byte	0x57
	.long	0x510
	.long	.LLST66
	.uleb128 0x15
	.long	.LASF75
	.byte	0x1
	.byte	0x57
	.long	0x510
	.long	.LLST67
	.uleb128 0x15
	.long	.LASF54
	.byte	0x1
	.byte	0x56
	.long	0x510
	.long	.LLST68
	.uleb128 0x15
	.long	.LASF55
	.byte	0x1
	.byte	0x56
	.long	0x510
	.long	.LLST69
	.uleb128 0x15
	.long	.LASF78
	.byte	0x1
	.byte	0x55
	.long	0x510
	.long	.LLST70
	.uleb128 0x15
	.long	.LASF79
	.byte	0x1
	.byte	0x55
	.long	0x510
	.long	.LLST71
	.uleb128 0x15
	.long	.LASF56
	.byte	0x1
	.byte	0x54
	.long	0x510
	.long	.LLST72
	.uleb128 0x15
	.long	.LASF57
	.byte	0x1
	.byte	0x54
	.long	0x510
	.long	.LLST73
	.uleb128 0x15
	.long	.LASF164
	.byte	0x1
	.byte	0x4c
	.long	0x510
	.long	.LLST74
	.uleb128 0x15
	.long	.LASF165
	.byte	0x1
	.byte	0x4c
	.long	0x510
	.long	.LLST75
	.uleb128 0x15
	.long	.LASF58
	.byte	0x1
	.byte	0x53
	.long	0x510
	.long	.LLST76
	.uleb128 0x15
	.long	.LASF59
	.byte	0x1
	.byte	0x53
	.long	0x510
	.long	.LLST77
	.uleb128 0x1f
	.long	.LASF80
	.byte	0x1
	.byte	0x48
	.long	0x62
	.byte	0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x1f
	.long	.LASF96
	.byte	0x1
	.byte	0x47
	.long	0x62
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x20
	.long	.LASF85
	.byte	0x1
	.byte	0x46
	.long	0x62
	.byte	0
	.uleb128 0x15
	.long	.LASF166
	.byte	0x1
	.byte	0x69
	.long	0x62
	.long	.LLST78
	.uleb128 0x15
	.long	.LASF109
	.byte	0x1
	.byte	0x2a
	.long	0x62
	.long	.LLST79
	.uleb128 0x15
	.long	.LASF111
	.byte	0x1
	.byte	0x29
	.long	0x62
	.long	.LLST80
	.uleb128 0x1f
	.long	.LASF90
	.byte	0x1
	.byte	0x3e
	.long	0x309
	.byte	0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0x15
	.long	.LASF97
	.byte	0x1
	.byte	0x38
	.long	0x62
	.long	.LLST81
	.uleb128 0x1f
	.long	.LASF137
	.byte	0x1
	.byte	0x2b
	.long	0x62
	.byte	0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x21
	.string	"i"
	.byte	0x1
	.byte	0x3d
	.long	0x62
	.byte	0x3
	.byte	0x91
	.sleb128 -84
	.uleb128 0x1f
	.long	.LASF91
	.byte	0x1
	.byte	0x3c
	.long	0x8e4
	.byte	0x3
	.byte	0x91
	.sleb128 -2688
	.uleb128 0x1f
	.long	.LASF92
	.byte	0x1
	.byte	0x3c
	.long	0x8e4
	.byte	0x3
	.byte	0x91
	.sleb128 -2432
	.uleb128 0x1f
	.long	.LASF81
	.byte	0x1
	.byte	0x45
	.long	0x910
	.byte	0x3
	.byte	0x91
	.sleb128 -1920
	.uleb128 0x1f
	.long	.LASF82
	.byte	0x1
	.byte	0x44
	.long	0x910
	.byte	0x3
	.byte	0x91
	.sleb128 -1712
	.uleb128 0x1f
	.long	.LASF83
	.byte	0x1
	.byte	0x43
	.long	0x910
	.byte	0x3
	.byte	0x91
	.sleb128 -1504
	.uleb128 0x1f
	.long	.LASF84
	.byte	0x1
	.byte	0x42
	.long	0x910
	.byte	0x3
	.byte	0x91
	.sleb128 -1296
	.uleb128 0x1f
	.long	.LASF88
	.byte	0x1
	.byte	0x41
	.long	0x8fa
	.byte	0x3
	.byte	0x91
	.sleb128 -3520
	.uleb128 0x1f
	.long	.LASF89
	.byte	0x1
	.byte	0x40
	.long	0x8fa
	.byte	0x3
	.byte	0x91
	.sleb128 -3104
	.uleb128 0x1f
	.long	.LASF86
	.byte	0x1
	.byte	0x3f
	.long	0x910
	.byte	0x3
	.byte	0x91
	.sleb128 -1088
	.uleb128 0x1f
	.long	.LASF87
	.byte	0x1
	.byte	0x3f
	.long	0x910
	.byte	0x3
	.byte	0x91
	.sleb128 -880
	.uleb128 0x16
	.long	.LASF99
	.byte	0x1
	.byte	0x37
	.long	0x33e
	.uleb128 0x16
	.long	.LASF152
	.byte	0x1
	.byte	0x35
	.long	0x33e
	.uleb128 0x16
	.long	.LASF145
	.byte	0x1
	.byte	0x34
	.long	0x62
	.uleb128 0x16
	.long	.LASF136
	.byte	0x1
	.byte	0x30
	.long	0x62
	.uleb128 0x16
	.long	.LASF135
	.byte	0x1
	.byte	0x36
	.long	0x62
	.uleb128 0x16
	.long	.LASF60
	.byte	0x1
	.byte	0x31
	.long	0x33e
	.uleb128 0x16
	.long	.LASF62
	.byte	0x1
	.byte	0x2d
	.long	0x33e
	.uleb128 0x16
	.long	.LASF61
	.byte	0x1
	.byte	0x2e
	.long	0x33e
	.uleb128 0x1f
	.long	.LASF93
	.byte	0x1
	.byte	0x3b
	.long	0x62
	.byte	0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x1f
	.long	.LASF94
	.byte	0x1
	.byte	0x3a
	.long	0x309
	.byte	0x3
	.byte	0x91
	.sleb128 -92
	.uleb128 0x1f
	.long	.LASF95
	.byte	0x1
	.byte	0x39
	.long	0x309
	.byte	0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x1f
	.long	.LASF112
	.byte	0x1
	.byte	0x50
	.long	0x2e0
	.byte	0x3
	.byte	0x91
	.sleb128 -160
	.uleb128 0x1f
	.long	.LASF113
	.byte	0x1
	.byte	0x4f
	.long	0x2e0
	.byte	0x3
	.byte	0x91
	.sleb128 -128
	.uleb128 0x16
	.long	.LASF110
	.byte	0x1
	.byte	0x2c
	.long	0x370
	.uleb128 0x19
	.long	.Ldebug_ranges0+0x140
	.uleb128 0x16
	.long	.LASF100
	.byte	0x1
	.byte	0x8a
	.long	0x92c
	.uleb128 0x16
	.long	.LASF98
	.byte	0x1
	.byte	0x8b
	.long	0x86
	.byte	0
	.byte	0
	.uleb128 0x22
	.long	.LASF167
	.value	0x188
	.long	0x157c
	.uleb128 0xe
	.long	.LASF103
	.byte	0x1
	.byte	0xde
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xe
	.long	.LASF104
	.byte	0x1
	.byte	0xde
	.long	0x4f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xe
	.long	.LASF105
	.byte	0x1
	.byte	0xde
	.long	0x4fd
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xe
	.long	.LASF63
	.byte	0x1
	.byte	0xcd
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xe
	.long	.LASF64
	.byte	0x1
	.byte	0xcd
	.long	0x4f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xe
	.long	.LASF65
	.byte	0x1
	.byte	0xcd
	.long	0x4fd
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xe
	.long	.LASF160
	.byte	0x1
	.byte	0xc3
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xe
	.long	.LASF161
	.byte	0x1
	.byte	0xc3
	.long	0x4f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0xe
	.long	.LASF162
	.byte	0x1
	.byte	0xc3
	.long	0x4fd
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0xe
	.long	.LASF154
	.byte	0x1
	.byte	0xba
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0xe
	.long	.LASF155
	.byte	0x1
	.byte	0xba
	.long	0x4f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0xe
	.long	.LASF156
	.byte	0x1
	.byte	0xba
	.long	0x4fd
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0xe
	.long	.LASF147
	.byte	0x1
	.byte	0xb2
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0xe
	.long	.LASF148
	.byte	0x1
	.byte	0xb2
	.long	0x4f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0xe
	.long	.LASF149
	.byte	0x1
	.byte	0xb2
	.long	0x4fd
	.byte	0x2
	.byte	0x23
	.uleb128 0x70
	.uleb128 0xe
	.long	.LASF139
	.byte	0x1
	.byte	0xa5
	.long	0x99
	.byte	0x2
	.byte	0x23
	.uleb128 0x78
	.uleb128 0xe
	.long	.LASF140
	.byte	0x1
	.byte	0xa5
	.long	0x4f7
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0xe
	.long	.LASF141
	.byte	0x1
	.byte	0xa5
	.long	0x4fd
	.byte	0x3
	.byte	0x23
	.uleb128 0x88
	.uleb128 0xe
	.long	.LASF128
	.byte	0x1
	.byte	0x9b
	.long	0x99
	.byte	0x3
	.byte	0x23
	.uleb128 0x90
	.uleb128 0xe
	.long	.LASF129
	.byte	0x1
	.byte	0x9b
	.long	0x4f7
	.byte	0x3
	.byte	0x23
	.uleb128 0x98
	.uleb128 0xe
	.long	.LASF130
	.byte	0x1
	.byte	0x9b
	.long	0x4fd
	.byte	0x3
	.byte	0x23
	.uleb128 0xa0
	.uleb128 0xe
	.long	.LASF115
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x3
	.byte	0x23
	.uleb128 0xa8
	.uleb128 0xe
	.long	.LASF116
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x3
	.byte	0x23
	.uleb128 0xb0
	.uleb128 0xe
	.long	.LASF117
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x3
	.byte	0x23
	.uleb128 0xb8
	.uleb128 0xe
	.long	.LASF118
	.byte	0x1
	.byte	0x93
	.long	0x99
	.byte	0x3
	.byte	0x23
	.uleb128 0xc0
	.uleb128 0xe
	.long	.LASF119
	.byte	0x1
	.byte	0x93
	.long	0x4f7
	.byte	0x3
	.byte	0x23
	.uleb128 0xc8
	.uleb128 0xe
	.long	.LASF120
	.byte	0x1
	.byte	0x93
	.long	0x4fd
	.byte	0x3
	.byte	0x23
	.uleb128 0xd0
	.uleb128 0xe
	.long	.LASF168
	.byte	0x1
	.byte	0x6c
	.long	0x99
	.byte	0x3
	.byte	0x23
	.uleb128 0xd8
	.uleb128 0xe
	.long	.LASF59
	.byte	0x1
	.byte	0x53
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0xe0
	.uleb128 0xe
	.long	.LASF58
	.byte	0x1
	.byte	0x53
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0xe8
	.uleb128 0xe
	.long	.LASF165
	.byte	0x1
	.byte	0x4c
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0xf0
	.uleb128 0xe
	.long	.LASF164
	.byte	0x1
	.byte	0x4c
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0xf8
	.uleb128 0xe
	.long	.LASF57
	.byte	0x1
	.byte	0x54
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0x100
	.uleb128 0xe
	.long	.LASF56
	.byte	0x1
	.byte	0x54
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0x108
	.uleb128 0xe
	.long	.LASF79
	.byte	0x1
	.byte	0x55
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0x110
	.uleb128 0xe
	.long	.LASF78
	.byte	0x1
	.byte	0x55
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0x118
	.uleb128 0xe
	.long	.LASF55
	.byte	0x1
	.byte	0x56
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0x120
	.uleb128 0xe
	.long	.LASF54
	.byte	0x1
	.byte	0x56
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0x128
	.uleb128 0xe
	.long	.LASF75
	.byte	0x1
	.byte	0x57
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0x130
	.uleb128 0xe
	.long	.LASF74
	.byte	0x1
	.byte	0x57
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0x138
	.uleb128 0xe
	.long	.LASF73
	.byte	0x1
	.byte	0x58
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0x140
	.uleb128 0xe
	.long	.LASF72
	.byte	0x1
	.byte	0x58
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0x148
	.uleb128 0xe
	.long	.LASF77
	.byte	0x1
	.byte	0x59
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0x150
	.uleb128 0xe
	.long	.LASF76
	.byte	0x1
	.byte	0x59
	.long	0x510
	.byte	0x3
	.byte	0x23
	.uleb128 0x158
	.uleb128 0x10
	.string	"i"
	.byte	0x1
	.byte	0x3d
	.long	0x62
	.byte	0x3
	.byte	0x23
	.uleb128 0x160
	.uleb128 0xe
	.long	.LASF137
	.byte	0x1
	.byte	0x2b
	.long	0x62
	.byte	0x3
	.byte	0x23
	.uleb128 0x164
	.uleb128 0xe
	.long	.LASF97
	.byte	0x1
	.byte	0x38
	.long	0x62
	.byte	0x3
	.byte	0x23
	.uleb128 0x168
	.uleb128 0xe
	.long	.LASF90
	.byte	0x1
	.byte	0x3e
	.long	0x309
	.byte	0x3
	.byte	0x23
	.uleb128 0x16c
	.uleb128 0xe
	.long	.LASF111
	.byte	0x1
	.byte	0x29
	.long	0x62
	.byte	0x3
	.byte	0x23
	.uleb128 0x170
	.uleb128 0xe
	.long	.LASF109
	.byte	0x1
	.byte	0x2a
	.long	0x62
	.byte	0x3
	.byte	0x23
	.uleb128 0x174
	.uleb128 0xe
	.long	.LASF166
	.byte	0x1
	.byte	0x69
	.long	0x62
	.byte	0x3
	.byte	0x23
	.uleb128 0x178
	.uleb128 0xe
	.long	.LASF96
	.byte	0x1
	.byte	0x47
	.long	0x62
	.byte	0x3
	.byte	0x23
	.uleb128 0x17c
	.uleb128 0xe
	.long	.LASF80
	.byte	0x1
	.byte	0x48
	.long	0x62
	.byte	0x3
	.byte	0x23
	.uleb128 0x180
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0x1267
	.uleb128 0x23
	.byte	0x1
	.long	.LASF178
	.byte	0x1
	.byte	0x26
	.byte	0x1
	.long	0x62
	.quad	.LFB21
	.quad	.LFE21
	.long	.LLST82
	.long	0x185b
	.uleb128 0x24
	.long	.LASF169
	.byte	0x1
	.byte	0x26
	.long	0x62
	.long	.LLST83
	.uleb128 0x24
	.long	.LASF170
	.byte	0x1
	.byte	0x26
	.long	0x185b
	.long	.LLST84
	.uleb128 0x20
	.long	.LASF111
	.byte	0x1
	.byte	0x29
	.long	0x62
	.byte	0
	.uleb128 0x16
	.long	.LASF109
	.byte	0x1
	.byte	0x2a
	.long	0x62
	.uleb128 0x20
	.long	.LASF137
	.byte	0x1
	.byte	0x2b
	.long	0x62
	.byte	0
	.uleb128 0x16
	.long	.LASF110
	.byte	0x1
	.byte	0x2c
	.long	0x370
	.uleb128 0x16
	.long	.LASF62
	.byte	0x1
	.byte	0x2d
	.long	0x33e
	.uleb128 0x16
	.long	.LASF61
	.byte	0x1
	.byte	0x2e
	.long	0x33e
	.uleb128 0x16
	.long	.LASF134
	.byte	0x1
	.byte	0x2f
	.long	0x62
	.uleb128 0x16
	.long	.LASF136
	.byte	0x1
	.byte	0x30
	.long	0x62
	.uleb128 0x16
	.long	.LASF60
	.byte	0x1
	.byte	0x31
	.long	0x33e
	.uleb128 0x16
	.long	.LASF133
	.byte	0x1
	.byte	0x32
	.long	0x62
	.uleb128 0x16
	.long	.LASF132
	.byte	0x1
	.byte	0x33
	.long	0x62
	.uleb128 0x16
	.long	.LASF145
	.byte	0x1
	.byte	0x34
	.long	0x62
	.uleb128 0x16
	.long	.LASF152
	.byte	0x1
	.byte	0x35
	.long	0x33e
	.uleb128 0x16
	.long	.LASF135
	.byte	0x1
	.byte	0x36
	.long	0x62
	.uleb128 0x16
	.long	.LASF99
	.byte	0x1
	.byte	0x37
	.long	0x33e
	.uleb128 0x1f
	.long	.LASF97
	.byte	0x1
	.byte	0x38
	.long	0x62
	.byte	0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0x16
	.long	.LASF95
	.byte	0x1
	.byte	0x39
	.long	0x309
	.uleb128 0x16
	.long	.LASF94
	.byte	0x1
	.byte	0x3a
	.long	0x309
	.uleb128 0x16
	.long	.LASF93
	.byte	0x1
	.byte	0x3b
	.long	0x62
	.uleb128 0x16
	.long	.LASF92
	.byte	0x1
	.byte	0x3c
	.long	0x8e4
	.uleb128 0x16
	.long	.LASF91
	.byte	0x1
	.byte	0x3c
	.long	0x8e4
	.uleb128 0x25
	.string	"i"
	.byte	0x1
	.byte	0x3d
	.long	0x62
	.byte	0
	.uleb128 0x26
	.long	.LASF90
	.byte	0x1
	.byte	0x3e
	.long	0x309
	.byte	0x4
	.long	0x3fb00000
	.uleb128 0x16
	.long	.LASF87
	.byte	0x1
	.byte	0x3f
	.long	0x910
	.uleb128 0x16
	.long	.LASF86
	.byte	0x1
	.byte	0x3f
	.long	0x910
	.uleb128 0x16
	.long	.LASF89
	.byte	0x1
	.byte	0x40
	.long	0x8fa
	.uleb128 0x16
	.long	.LASF88
	.byte	0x1
	.byte	0x41
	.long	0x8fa
	.uleb128 0x16
	.long	.LASF84
	.byte	0x1
	.byte	0x42
	.long	0x910
	.uleb128 0x16
	.long	.LASF83
	.byte	0x1
	.byte	0x43
	.long	0x910
	.uleb128 0x16
	.long	.LASF82
	.byte	0x1
	.byte	0x44
	.long	0x910
	.uleb128 0x16
	.long	.LASF81
	.byte	0x1
	.byte	0x45
	.long	0x910
	.uleb128 0x20
	.long	.LASF85
	.byte	0x1
	.byte	0x46
	.long	0x1861
	.byte	0
	.uleb128 0x20
	.long	.LASF96
	.byte	0x1
	.byte	0x47
	.long	0x62
	.byte	0
	.uleb128 0x20
	.long	.LASF80
	.byte	0x1
	.byte	0x48
	.long	0x62
	.byte	0
	.uleb128 0x15
	.long	.LASF165
	.byte	0x1
	.byte	0x4c
	.long	0x510
	.long	.LLST85
	.uleb128 0x15
	.long	.LASF164
	.byte	0x1
	.byte	0x4c
	.long	0x510
	.long	.LLST86
	.uleb128 0x16
	.long	.LASF113
	.byte	0x1
	.byte	0x4f
	.long	0x2e0
	.uleb128 0x16
	.long	.LASF112
	.byte	0x1
	.byte	0x50
	.long	0x2e0
	.uleb128 0x15
	.long	.LASF59
	.byte	0x1
	.byte	0x53
	.long	0x510
	.long	.LLST87
	.uleb128 0x15
	.long	.LASF58
	.byte	0x1
	.byte	0x53
	.long	0x510
	.long	.LLST88
	.uleb128 0x15
	.long	.LASF57
	.byte	0x1
	.byte	0x54
	.long	0x510
	.long	.LLST89
	.uleb128 0x15
	.long	.LASF56
	.byte	0x1
	.byte	0x54
	.long	0x510
	.long	.LLST90
	.uleb128 0x15
	.long	.LASF79
	.byte	0x1
	.byte	0x55
	.long	0x510
	.long	.LLST91
	.uleb128 0x15
	.long	.LASF78
	.byte	0x1
	.byte	0x55
	.long	0x510
	.long	.LLST92
	.uleb128 0x15
	.long	.LASF55
	.byte	0x1
	.byte	0x56
	.long	0x510
	.long	.LLST93
	.uleb128 0x15
	.long	.LASF54
	.byte	0x1
	.byte	0x56
	.long	0x510
	.long	.LLST94
	.uleb128 0x15
	.long	.LASF75
	.byte	0x1
	.byte	0x57
	.long	0x510
	.long	.LLST95
	.uleb128 0x15
	.long	.LASF74
	.byte	0x1
	.byte	0x57
	.long	0x510
	.long	.LLST96
	.uleb128 0x15
	.long	.LASF73
	.byte	0x1
	.byte	0x58
	.long	0x510
	.long	.LLST97
	.uleb128 0x15
	.long	.LASF72
	.byte	0x1
	.byte	0x58
	.long	0x510
	.long	.LLST98
	.uleb128 0x15
	.long	.LASF77
	.byte	0x1
	.byte	0x59
	.long	0x510
	.long	.LLST99
	.uleb128 0x15
	.long	.LASF76
	.byte	0x1
	.byte	0x59
	.long	0x510
	.long	.LLST100
	.uleb128 0x20
	.long	.LASF166
	.byte	0x1
	.byte	0x69
	.long	0x62
	.byte	0
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0x9b
	.uleb128 0xf
	.long	0x62
	.uleb128 0x27
	.long	.LASF171
	.byte	0x5
	.byte	0x91
	.long	0x2c4
	.byte	0x1
	.byte	0x1
	.uleb128 0x27
	.long	.LASF172
	.byte	0x5
	.byte	0x92
	.long	0x2c4
	.byte	0x1
	.byte	0x1
	.uleb128 0x27
	.long	.LASF171
	.byte	0x5
	.byte	0x91
	.long	0x2c4
	.byte	0x1
	.byte	0x1
	.uleb128 0x27
	.long	.LASF172
	.byte	0x5
	.byte	0x92
	.long	0x2c4
	.byte	0x1
	.byte	0x1
	.byte	0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x34
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_pubnames,"",@progbits
	.long	0x17
	.value	0x2
	.long	.Ldebug_info0
	.long	0x189b
	.long	0x1582
	.string	"main"
	.long	0
	.section	.debug_pubtypes,"",@progbits
	.long	0x145
	.value	0x2
	.long	.Ldebug_info0
	.long	0x189b
	.long	0x2d
	.string	"size_t"
	.long	0x70
	.string	"__off_t"
	.long	0x7b
	.string	"__off64_t"
	.long	0xa8
	.string	"FILE"
	.long	0x280
	.string	"_IO_lock_t"
	.long	0x287
	.string	"_IO_marker"
	.long	0xb3
	.string	"_IO_FILE"
	.long	0x317
	.string	"icomplex"
	.long	0x33e
	.string	"icomplex"
	.long	0x349
	.string	"fcomplex"
	.long	0x370
	.string	"fcomplex"
	.long	0x444
	.string	".omp_data_s.52"
	.long	0x70e
	.string	".omp_data_s.56"
	.long	0xa1d
	.string	".omp_data_s.11"
	.long	0xb17
	.string	".omp_data_s.23"
	.long	0xc29
	.string	".omp_data_s.29"
	.long	0xd1e
	.string	".omp_data_s.36"
	.long	0xdf3
	.string	".omp_data_s.41"
	.long	0xed7
	.string	".omp_data_s.46"
	.long	0x1267
	.string	".omp_data_s.8"
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.quad	.LBB10-.Ltext0
	.quad	.LBE10-.Ltext0
	.quad	.LBB16-.Ltext0
	.quad	.LBE16-.Ltext0
	.quad	.LBB15-.Ltext0
	.quad	.LBE15-.Ltext0
	.quad	.LBB14-.Ltext0
	.quad	.LBE14-.Ltext0
	.quad	.LBB13-.Ltext0
	.quad	.LBE13-.Ltext0
	.quad	.LBB12-.Ltext0
	.quad	.LBE12-.Ltext0
	.quad	.LBB11-.Ltext0
	.quad	.LBE11-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB17-.Ltext0
	.quad	.LBE17-.Ltext0
	.quad	.LBB20-.Ltext0
	.quad	.LBE20-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB21-.Ltext0
	.quad	.LBE21-.Ltext0
	.quad	.LBB24-.Ltext0
	.quad	.LBE24-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB25-.Ltext0
	.quad	.LBE25-.Ltext0
	.quad	.LBB28-.Ltext0
	.quad	.LBE28-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB29-.Ltext0
	.quad	.LBE29-.Ltext0
	.quad	.LBB32-.Ltext0
	.quad	.LBE32-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB38-.Ltext0
	.quad	.LBE38-.Ltext0
	.quad	.LBB43-.Ltext0
	.quad	.LBE43-.Ltext0
	.quad	.LBB34-.Ltext0
	.quad	.LBE34-.Ltext0
	.quad	.LBB42-.Ltext0
	.quad	.LBE42-.Ltext0
	.quad	.LBB35-.Ltext0
	.quad	.LBE35-.Ltext0
	.quad	.LBB41-.Ltext0
	.quad	.LBE41-.Ltext0
	.quad	.LBB36-.Ltext0
	.quad	.LBE36-.Ltext0
	.quad	.LBB40-.Ltext0
	.quad	.LBE40-.Ltext0
	.quad	.LBB37-.Ltext0
	.quad	.LBE37-.Ltext0
	.quad	.LBB39-.Ltext0
	.quad	.LBE39-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_str,"MS",@progbits,1
.LASF76:
	.string	"fft_im_out"
.LASF118:
	.string	"task.19"
.LASF31:
	.string	"_shortbuf"
.LASF176:
	.string	"_IO_lock_t"
.LASF20:
	.string	"_IO_buf_end"
.LASF141:
	.string	"gomp_termination_flag_p.33"
.LASF149:
	.string	"gomp_termination_flag_p.38"
.LASF113:
	.string	"re_in"
.LASF117:
	.string	"gomp_firstprivate_view_p.20"
.LASF116:
	.string	"gomp_firstprivate_view_p.21"
.LASF115:
	.string	"gomp_firstprivate_view_p.22"
.LASF136:
	.string	"burst_found_pulse_out"
.LASF51:
	.string	"fcomplex"
.LASF91:
	.string	"imag_out_demux"
.LASF18:
	.string	"_IO_write_end"
.LASF3:
	.string	"unsigned int"
.LASF128:
	.string	"task.28"
.LASF88:
	.string	"input_CHE_imag"
.LASF12:
	.string	"_flags"
.LASF140:
	.string	"gomp_activation_counter_p.34"
.LASF132:
	.string	"freq_est_norm_max_out"
.LASF148:
	.string	"gomp_activation_counter_p.39"
.LASF89:
	.string	"input_CHE_real"
.LASF92:
	.string	"real_out_demux"
.LASF156:
	.string	"gomp_termination_flag_p.43"
.LASF24:
	.string	"_markers"
.LASF162:
	.string	"gomp_termination_flag_p.49"
.LASF139:
	.string	"task.35"
.LASF170:
	.string	"argv"
.LASF65:
	.string	"gomp_termination_flag_p.53"
.LASF105:
	.string	"gomp_termination_flag_p.57"
.LASF125:
	.string	"gomp_stream.12"
.LASF124:
	.string	"gomp_stream.13"
.LASF123:
	.string	"gomp_stream.14"
.LASF122:
	.string	"gomp_stream.15"
.LASF121:
	.string	"gomp_stream.16"
.LASF50:
	.string	"icomplex"
.LASF45:
	.string	"_pos"
.LASF147:
	.string	"task.40"
.LASF172:
	.string	"stdout"
.LASF154:
	.string	"task.45"
.LASF23:
	.string	"_IO_save_end"
.LASF48:
	.string	"float"
.LASF137:
	.string	"rx_start"
.LASF77:
	.string	"fft_re_out"
.LASF174:
	.string	"../../test/perftest/dp_802_11a/sync_fft_che_top_tb.c"
.LASF47:
	.string	"long long unsigned int"
.LASF167:
	.string	".omp_data_s.8"
.LASF67:
	.string	"gomp_stream.24"
.LASF66:
	.string	"gomp_stream.25"
.LASF160:
	.string	"task.51"
.LASF133:
	.string	"freq_est_norm_out"
.LASF63:
	.string	"task.55"
.LASF22:
	.string	"_IO_backup_base"
.LASF103:
	.string	"task.59"
.LASF33:
	.string	"_offset"
.LASF26:
	.string	"_fileno"
.LASF79:
	.string	"fft_re_reversed"
.LASF166:
	.string	"counter"
.LASF68:
	.string	"gomp_stream.30"
.LASF143:
	.string	"gomp_stream.31"
.LASF142:
	.string	"gomp_stream.32"
.LASF7:
	.string	"size_t"
.LASF150:
	.string	"gomp_stream.37"
.LASF15:
	.string	"_IO_read_base"
.LASF69:
	.string	"_Bool"
.LASF169:
	.string	"argc"
.LASF171:
	.string	"stdin"
.LASF43:
	.string	"_next"
.LASF110:
	.string	"freq_sync_correl_2STS_input"
.LASF157:
	.string	"gomp_stream.42"
.LASF107:
	.string	"gomp_stream.47"
.LASF106:
	.string	"gomp_stream.48"
.LASF168:
	.string	"parallel_region_task.9"
.LASF57:
	.string	"FS_single_correl_I"
.LASF59:
	.string	"freq_sync_correl_2STS_out_I"
.LASF134:
	.string	"burst_found_out"
.LASF55:
	.string	"freq_est_phase_out_I"
.LASF10:
	.string	"char"
.LASF56:
	.string	"FS_single_correl_Q"
.LASF58:
	.string	"freq_sync_correl_2STS_out_Q"
.LASF39:
	.string	"_mode"
.LASF42:
	.string	"_IO_marker"
.LASF73:
	.string	"CHC_out_I"
.LASF13:
	.string	"_IO_read_ptr"
.LASF72:
	.string	"CHC_out_Q"
.LASF93:
	.string	"start_out"
.LASF152:
	.string	"cordic_out"
.LASF16:
	.string	"_IO_write_base"
.LASF52:
	.string	"__nptr"
.LASF46:
	.string	"long long int"
.LASF21:
	.string	"_IO_save_base"
.LASF119:
	.string	"gomp_activation_counter_p.18"
.LASF75:
	.string	"CHE_out_I"
.LASF111:
	.string	"init_modules"
.LASF74:
	.string	"CHE_out_Q"
.LASF97:
	.string	"maximum_found"
.LASF34:
	.string	"__pad1"
.LASF35:
	.string	"__pad2"
.LASF36:
	.string	"__pad3"
.LASF37:
	.string	"__pad4"
.LASF38:
	.string	"__pad5"
.LASF54:
	.string	"freq_est_phase_out_Q"
.LASF30:
	.string	"_vtable_offset"
.LASF96:
	.string	"mk_test"
.LASF164:
	.string	"file_im_in"
.LASF129:
	.string	"gomp_activation_counter_p.27"
.LASF178:
	.string	"main"
.LASF53:
	.string	".omp_data_i"
.LASF145:
	.string	"angle"
.LASF98:
	.string	"v_maximum_found"
.LASF114:
	.string	".omp_data_s.11"
.LASF14:
	.string	"_IO_read_end"
.LASF146:
	.string	".omp_data_s.36"
.LASF81:
	.string	"output_CHC_imag"
.LASF5:
	.string	"short int"
.LASF163:
	.string	"main.omp_fn.0"
.LASF108:
	.string	"main.omp_fn.1"
.LASF126:
	.string	"main.omp_fn.2"
.LASF6:
	.string	"long int"
.LASF144:
	.string	"main.omp_fn.4"
.LASF151:
	.string	"main.omp_fn.5"
.LASF158:
	.string	"main.omp_fn.6"
.LASF70:
	.string	"main.omp_fn.7"
.LASF71:
	.string	"main.omp_fn.8"
.LASF94:
	.string	"im_out"
.LASF82:
	.string	"output_CHC_real"
.LASF120:
	.string	"gomp_termination_flag_p.17"
.LASF99:
	.string	"data_out_FT"
.LASF78:
	.string	"fft_im_reversed"
.LASF127:
	.string	".omp_data_s.23"
.LASF138:
	.string	".omp_data_s.29"
.LASF85:
	.string	"CHE_flag"
.LASF61:
	.string	"correlation_1ST"
.LASF155:
	.string	"gomp_activation_counter_p.44"
.LASF90:
	.string	"FFT_output_scale"
.LASF175:
	.string	"/media/disk/local/dev/omp-stream/build/gcc"
.LASF62:
	.string	"freq_sync_correl_2STS_output"
.LASF32:
	.string	"_lock"
.LASF0:
	.string	"long unsigned int"
.LASF28:
	.string	"_old_offset"
.LASF41:
	.string	"_IO_FILE"
.LASF159:
	.string	".omp_data_s.46"
.LASF100:
	.string	"v_data_out_FT"
.LASF161:
	.string	"gomp_activation_counter_p.50"
.LASF64:
	.string	"gomp_activation_counter_p.54"
.LASF104:
	.string	"gomp_activation_counter_p.58"
.LASF1:
	.string	"unsigned char"
.LASF44:
	.string	"_sbuf"
.LASF17:
	.string	"_IO_write_ptr"
.LASF153:
	.string	".omp_data_s.41"
.LASF60:
	.string	"freq_est_phase_out"
.LASF165:
	.string	"file_re_in"
.LASF80:
	.string	"GI_Flag"
.LASF86:
	.string	"data_remove_GI_reorder_imag"
.LASF109:
	.string	"init_modules_s"
.LASF8:
	.string	"__off_t"
.LASF87:
	.string	"data_remove_GI_reorder_real"
.LASF4:
	.string	"signed char"
.LASF95:
	.string	"re_out"
.LASF2:
	.string	"short unsigned int"
.LASF101:
	.string	".omp_data_s.52"
.LASF112:
	.string	"im_in"
.LASF102:
	.string	".omp_data_s.56"
.LASF177:
	.string	"atof"
.LASF49:
	.string	"double"
.LASF83:
	.string	"output_CHE_imag"
.LASF25:
	.string	"_chain"
.LASF173:
	.string	"GNU C 4.6.0 20100511 (experimental)"
.LASF11:
	.string	"FILE"
.LASF27:
	.string	"_flags2"
.LASF131:
	.string	"main.omp_fn.3"
.LASF84:
	.string	"output_CHE_real"
.LASF135:
	.string	"burst_found_pulse_for_FT"
.LASF29:
	.string	"_cur_column"
.LASF130:
	.string	"gomp_termination_flag_p.26"
.LASF9:
	.string	"__off64_t"
.LASF40:
	.string	"_unused2"
.LASF19:
	.string	"_IO_buf_base"
	.ident	"GCC: (GNU) 4.6.0 20100511 (experimental)"
	.section	.note.GNU-stack,"",@progbits
