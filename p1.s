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
	movq	_a@GOTPCREL(%rip), %rax
	movl	$0, -4(%rbp)
	movl	$1, (%rax)
	movl	(%rax), %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_pri                    ## -- Begin function pri
	.p2align	4, 0x90
_pri:                                   ## @pri
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	_a@GOTPCREL(%rip), %rax
	movl	%edi, -4(%rbp)
	movl	$2, (%rax)
	movl	(%rax), %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.comm	_a,4,2                  ## @a

.subsections_via_symbols
