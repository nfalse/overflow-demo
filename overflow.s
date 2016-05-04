	.file	"overflow.c"
	.section	.rodata
.LC0:
	.string	"\346\255\243\345\270\270\344\273\243\347\240\201\350\260\203\347\224\250"
	.text
	.globl	funcA
	.type	funcA, @function
funcA:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$.LC0, %edi
	call	puts
	movq	-24(%rbp), %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	funcA, .-funcA
	.section	.rodata
.LC1:
	.string	"\346\201\266\346\204\217\344\273\243\347\240\201\350\242\253\350\260\203\347\224\250"
	.text
	.globl	funcB
	.type	funcB, @function
funcB:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	$.LC1, %edi
	call	puts
	movl	$0, %edi
	call	exit
	.cfi_endproc
.LFE3:
	.size	funcB, .-funcB
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	leaq	-32(%rbp), %rax
	movl	$32, %edx
	movl	$70, %esi
	movq	%rax, %rdi
	call	memset
	leaq	-32(%rbp), %rax
	addq	$24, %rax
	movl	$funcB, %edx
	movq	%rdx, (%rax)
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	funcA
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	main, .-main
	.ident	"GCC: (Debian 5.3.1-8) 5.3.1 20160205"
	.section	.note.GNU-stack,"",@progbits
