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
	callq	_pri
	movq	_a@GOTPCREL(%rip), %rcx
	movl	%eax, (%rcx)
	callq	_pri
	leaq	L_.str(%rip), %rdi
	movl	%eax, %esi
	movb	$0, %al
	callq	_printf
	xorl	%esi, %esi
	movl	%eax, -4(%rbp)          ## 4-byte Spill
	movl	%esi, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_pri                    ## -- Begin function pri
	.p2align	4, 0x90
_pri:                                   ## @pri
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
	movl	_ll(%rip), %eax
	addl 	$1,%eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__DATA,__data
	.globl	_ll                     ## @ll
	.p2align	2
_ll:
	.long	23                      ## 0x17

	.comm	_a,4,2                  ## @a
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d\n"


.subsections_via_symbols
