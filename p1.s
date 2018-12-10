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
	leaq	_str(%rip), %rsi
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%eax, -4(%rbp)          ## 4-byte Spill
	movl	%ecx, %eax
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

	.globl	_one                    ## @one
	.p2align	2
_one:
	.long	1                       ## 0x1

	.globl	_zero                   ## @zero
.zerofill __DATA,__common,_zero,4,2
	.globl	_str                    ## @str

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%s\n"

_str:
	.ascii	"23"

.subsections_via_symbols
