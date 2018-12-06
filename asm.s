	.section	__TEXT,__text,regular,pure_instructions
##TAC_BEGINFUN
	.globl _main
_main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
##TAC_ADD
	movl	_a(%rip), %eax
	cvtsi2ssl	%eax, %xmm0
	addss	_r(%rip), %xmm0
	cvttss2si	%xmm0, %eax
	movl	%eax, _Variable0(%rip)
##TAC_PRINT_EXPRESSION
	leaq	.LC0(%rip), %rdi
	movl	_x(%rip), %esi
	movb	$0, %al
	callq	_printf
##TAC_PRINT_STRING
	leaq	.LC1(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_ENDFUN
	popq	 %rbp
	retq 
	.cfi_endproc


	.section	__DATA,__data
##TAC_VAR_DECL
	.globl 	_x
	.data
_x:
	.long 	92
##TAC_VAR_DECL
	.globl 	_a
	.data
_a:
	.long 	2
##TAC_VAR_DECL
	.globl 	_r
	.data
_r:
	.long 	4
##TAC_VAR_DECL
	.globl 	_Variable0
	.data
_Variable0:
	.long 	0
.LC0:
	.string "%d"
.LC1:
	.string " OI PRI\n"
