	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14
	.globl	_main                   ## -- Begin function main
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
	movl	$0, -4(%rbp)
	movl	$1, _b(%rip)
	movl	_b(%rip), %esi
	movb	$0, %al
	callq	_printf
	leaq	L_.str(%rip), %rdi
	movl	$0, _b(%rip)
	movl	_b(%rip), %esi
	movl	%eax, -8(%rbp)          ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	_b(%rip), %esi
	cmpl	_c(%rip), %esi
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	jne	LBB0_2
## %bb.1:
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -16(%rbp)         ## 4-byte Spill
LBB0_2:
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__DATA,__data
	.globl	_a                      ## @a
	.p2align	2
_a:
	.long	24                      ## 0x18

	.globl	_c                      ## @c
	.p2align	2
_c:
	.long	2                       ## 0x2

	.globl	_b                      ## @b
	.p2align	2
_b:
	.long	2                       ## 0x2

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d\n"

L_.str.1:                               ## @.str.1
	.asciz	"a"


.subsections_via_symbols
