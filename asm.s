	.section	__TEXT,__text,regular,pure_instructions
##TAC_BEGINFUN
	.globl _main
_main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
##TAC_DIV
	.comm _Variable0,4,4
	movl _20(%rip), %eax
	cltd
	idivl _10(%rip)
	movl %eax, _Variable0(%rip)
#TAC_ATRI
movl _Variable0(%rip), %eax
movl %eax, _x(%rip)
##TAC_PRINT_EXPRESSION
	leaq	.LC0(%rip), %rdi
	movl	_Variable1(%rip), %esi
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
##TAC_BEGINFUN
	.globl _icila
_icila:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
##TAC_ADD
	movl	_ici(%rip), %eax
	addl	_1(%rip), %eax
	movl	%eax, _Variable2(%rip)
#TAC_ATRI
movl _Variable2(%rip), %eax
movl %eax, _ici(%rip)
## TAC_RETURN
	movl _ici(%rip), %eax
	leave
	ret 
##TAC_ENDFUN
	retq 
	.cfi_endproc


	.section	__DATA,__data
##TAC_VAR_DECL
	.globl 	_x
	.data
_x:
	.long 	92
##TAC_VAR_DECL
	.globl 	_Variable0
	.data
_Variable0:
	.long 	0
##TAC_FUNCTION_PARAM
	.comm _ici,4,4
##TAC_VAR_DECL
	.globl 	_Variable2
	.data
_Variable2:
	.long 	0
##DECL_LITERAL
	.globl 	_92
	.data
_92:
	.long 	92
##DECL_LITERAL
	.globl 	_0
	.data
_0:
	.long 	0
##DECL_LITERAL
	.globl 	_1
	.data
_1:
	.long 	1
##DECL_LITERAL
	.globl 	_2
	.data
_2:
	.long 	2
##DECL_LITERAL
	.globl 	_10
	.data
_10:
	.long 	10
##DECL_LITERAL
	.globl 	_20
	.data
_20:
	.long 	20
.zerofill __DATA,__common,_zero,4,2
	.comm	_tempConvertStringToInt,50,4
.LC0:
	.string "%d"
.LC1:
	.string " OI PRI\n"
