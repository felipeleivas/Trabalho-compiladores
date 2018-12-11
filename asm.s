	.section	__TEXT,__text,regular,pure_instructions
##TAC_BEGINFUN
	.globl _main
_main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
#TAC_ATRI
movl _a(%rip), %eax
movl %eax, _x(%rip)
##TAC_PRINT_STRING
	leaq	.LC0(%rip), %rdi
	movb	$0, %al
	callq	_printf
	callq _aa
	movl %eax, _Variable0(%rip)
##TAC_PRINT_EXPRESSION
	leaq	.LC1(%rip), %rdi
	movl	_Variable0(%rip), %esi
	movb	$0, %al
	callq	_printf
##TAC_PRINT_STRING
	leaq	.LC2(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_ENDFUN
	popq	 %rbp
	retq 
	.cfi_endproc
##TAC_BEGINFUN
	.globl _aaasaala
_aaasaala:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
##TAC_FUNCTION_PARAM
	movl _aaasaala0(%rip), %eax
	movl %eax, _tre(%rip)
##TAC_FUNCTION_PARAM
	movl _aaasaala1(%rip), %eax
	movl %eax, _tr(%rip)
##TAC_ADD
	movl	_tre(%rip), %eax
	addl	_1(%rip), %eax
	movl	%eax, _Variable1(%rip)
#TAC_ATRI
movl _Variable1(%rip), %eax
movl %eax, _tr(%rip)
##TAC_RETURN
	movl	_tr(%rip), %eax
##TAC_ENDFUN
	popq	 %rbp
	retq 
	.cfi_endproc
##TAC_BEGINFUN
	.globl _aa
_aa:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
##TAC_FUNCTION_PARAM
	movl _aa0(%rip), %eax
	movl %eax, _ate(%rip)
##TAC_FUNCTION_PARAM
	movl _aa1(%rip), %eax
	movl %eax, _k(%rip)
##TAC_ADD
	movl	_k(%rip), %eax
	addl	_1(%rip), %eax
	movl	%eax, _Variable2(%rip)
##TAC_PRINT_EXPRESSION
	leaq	.LC3(%rip), %rdi
	movl	_Variable2(%rip), %esi
	movb	$0, %al
	callq	_printf
##TAC_PRINT_STRING
	leaq	.LC4(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_MULT
	movl _k(%rip), %eax
	imull _ate(%rip), %eax
	movl %eax, _Variable3(%rip)
##TAC_RETURN
	movl	_Variable3(%rip), %eax
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
	.long 	21
##TAC_VAR_DECL
	.globl 	_Variable0
	.data
_Variable0:
	.long 	0
##TAC_FUNCTION_PARAM
	.comm _tre,4,4
	.comm _aaasaala0,4,4
##TAC_FUNCTION_PARAM
	.comm _tr,4,4
	.comm _aaasaala1,4,4
##TAC_VAR_DECL
	.globl 	_Variable1
	.data
_Variable1:
	.long 	0
##TAC_FUNCTION_PARAM
	.comm _ate,4,4
	.comm _aa0,4,4
##TAC_FUNCTION_PARAM
	.comm _k,4,4
	.comm _aa1,4,4
##TAC_VAR_DECL
	.globl 	_Variable2
	.data
_Variable2:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable3
	.data
_Variable3:
	.long 	0
##TAC_ARG
_aa1:
	.long 123
##TAC_ARG
_aa0:
	.long 423
##DECL_LITERAL
	.globl 	_21
	.data
_21:
	.long 	21
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
	.globl 	_123
	.data
_123:
	.long 	123
##DECL_LITERAL
	.globl 	_423
	.data
_423:
	.long 	423
.zerofill __DATA,__common,_zero,4,2
	.comm	_tempConvertStringToInt,50,4
.LC0:
	.string "\n"
.LC1:
	.string "%d"
.LC2:
	.string " OI PRI\n"
.LC3:
	.string "%d"
.LC4:
	.string "Aqiou"
