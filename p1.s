	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14
	.section	__TEXT,__literal4,4byte_literals
	.p2align	2               ## -- Begin function main
LCPI0_0:
	.long	1082130432              ## float 4
LCPI0_1:
	.long	1086324736              ## float 6
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	leaq	L_.str(%rip), %rdi
	movss	LCPI0_0(%rip), %xmm0    ## xmm0 = mem[0],zero,zero,zero
	movss	LCPI0_1(%rip), %xmm1    ## xmm1 = mem[0],zero,zero,zero
	movl	$2, -4(%rbp)
	movl	_a(%rip), %eax
	cvtsi2ssl	%eax, %xmm2
	addss	_b(%rip), %xmm2
	addss	%xmm1, %xmm2
	addss	%xmm0, %xmm2
	cvttss2si	%xmm2, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %esi
	movss	_b(%rip), %xmm0         ## xmm0 = mem[0],zero,zero,zero
	cvtss2sd	%xmm0, %xmm0
	movb	$1, %al
	callq	_printf
	xorl	%esi, %esi
	movl	%eax, -8(%rbp)          ## 4-byte Spill
	movl	%esi, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__DATA,__data
	.globl	_a                      ## @a
	.p2align	2
_a:
	.long	91                      ## 0x5b

	.globl	_b                      ## @b
	.p2align	2
_b:
	.long	1072902963              ## float 1.89999998

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d %f\n"


.subsections_via_symbols
