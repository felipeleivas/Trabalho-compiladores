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
	movl	_x(%rip), %esi
	movb	$0, %al
	callq	_printf
##TAC_PRINT_STRING
	leaq	.LC1(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_LE
	movl _2(%rip), %eax
	cmp %eax, _2(%rip)
	jl TrUE0
	movl $1, _Variable1(%rip)
	jmp FAlSE0
TrUE0:
	movl $0, _Variable1(%rip)
FAlSE0:
 ##TAC_IFZ
	movl _Variable1(%rip), %eax
	cmp $0, %eax
	jz Label0
##TAC_PRINT_STRING
	leaq	.LC2(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_JUMP
	jmp Label1## TAC_LABEL
Label0:
##TAC_PRINT_STRING
	leaq	.LC3(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label1:
##TAC_LT
	movl _1(%rip), %eax
	cmp %eax, _2(%rip)
	jle TrUE1
	movl $1, _Variable2(%rip)
	jmp FAlSE1
TrUE1:
	movl $0, _Variable2(%rip)
FAlSE1:
 ##TAC_IFZ
	movl _Variable2(%rip), %eax
	cmp $0, %eax
	jz Label2
##TAC_PRINT_STRING
	leaq	.LC4(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_JUMP
	jmp Label3## TAC_LABEL
Label2:
##TAC_PRINT_STRING
	leaq	.LC5(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label3:
##TAC_EQ
	movl _2(%rip), %eax
	cmp %eax, _2(%rip)
	jne TrUE2
	movl $1, _Variable3(%rip)
	jmp FAlSE2
TrUE2:
	movl $0, _Variable3(%rip)
FAlSE2:
 ##TAC_IFZ
	movl _Variable3(%rip), %eax
	cmp $0, %eax
	jz Label4
##TAC_PRINT_STRING
	leaq	.LC6(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_JUMP
	jmp Label5## TAC_LABEL
Label4:
##TAC_PRINT_STRING
	leaq	.LC7(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label5:
##TAC_GE
	movl _1(%rip), %eax
	cmp %eax, _0(%rip)
	jg TrUE3
	movl $1, _Variable4(%rip)
	jmp FAlSE3
TrUE3:
	movl $0, _Variable4(%rip)
FAlSE3:
 ##TAC_IFZ
	movl _Variable4(%rip), %eax
	cmp $0, %eax
	jz Label6
##TAC_PRINT_STRING
	leaq	.LC8(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_JUMP
	jmp Label7## TAC_LABEL
Label6:
##TAC_PRINT_STRING
	leaq	.LC9(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label7:
##TAC_G
	movl _1(%rip), %eax
	cmp %eax, _0(%rip)
	jge TrUE4
	movl $1, _Variable5(%rip)
	jmp FAlSE4
TrUE4:
	movl $0, _Variable5(%rip)
FAlSE4:
 ##TAC_IFZ
	movl _Variable5(%rip), %eax
	cmp $0, %eax
	jz Label8
##TAC_PRINT_STRING
	leaq	.LC10(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_JUMP
	jmp Label9## TAC_LABEL
Label8:
##TAC_PRINT_STRING
	leaq	.LC11(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label9:
##TAC_LE
	movl _1(%rip), %eax
	cmp %eax, _0(%rip)
	jl TrUE5
	movl $1, _Variable6(%rip)
	jmp FAlSE5
TrUE5:
	movl $0, _Variable6(%rip)
FAlSE5:
 ##TAC_IFZ
	movl _Variable6(%rip), %eax
	cmp $0, %eax
	jz Label10
##TAC_PRINT_STRING
	leaq	.LC12(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_JUMP
	jmp Label11## TAC_LABEL
Label10:
##TAC_PRINT_STRING
	leaq	.LC13(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label11:
##TAC_LE
	movl _1(%rip), %eax
	cmp %eax, _0(%rip)
	jl TrUE6
	movl $1, _Variable7(%rip)
	jmp FAlSE6
TrUE6:
	movl $0, _Variable7(%rip)
FAlSE6:
 ##TAC_IFZ
	movl _Variable7(%rip), %eax
	cmp $0, %eax
	jz Label12
##TAC_PRINT_STRING
	leaq	.LC14(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_JUMP
	jmp Label13## TAC_LABEL
Label12:
##TAC_PRINT_STRING
	leaq	.LC15(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label13:
##TAC_EQ
	movl _1(%rip), %eax
	cmp %eax, _2(%rip)
	jne TrUE7
	movl $1, _Variable8(%rip)
	jmp FAlSE7
TrUE7:
	movl $0, _Variable8(%rip)
FAlSE7:
 ##TAC_IFZ
	movl _Variable8(%rip), %eax
	cmp $0, %eax
	jz Label14
##TAC_PRINT_STRING
	leaq	.LC16(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_JUMP
	jmp Label15## TAC_LABEL
Label14:
##TAC_PRINT_STRING
	leaq	.LC17(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label15:
##TAC_GE
	movl _1(%rip), %eax
	cmp %eax, _2(%rip)
	jg TrUE8
	movl $1, _Variable9(%rip)
	jmp FAlSE8
TrUE8:
	movl $0, _Variable9(%rip)
FAlSE8:
 ##TAC_IFZ
	movl _Variable9(%rip), %eax
	cmp $0, %eax
	jz Label16
##TAC_PRINT_STRING
	leaq	.LC18(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_JUMP
	jmp Label17## TAC_LABEL
Label16:
##TAC_PRINT_STRING
	leaq	.LC19(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label17:
##TAC_G
	movl _1(%rip), %eax
	cmp %eax, _2(%rip)
	jge TrUE9
	movl $1, _Variable10(%rip)
	jmp FAlSE9
TrUE9:
	movl $0, _Variable10(%rip)
FAlSE9:
 ##TAC_IFZ
	movl _Variable10(%rip), %eax
	cmp $0, %eax
	jz Label18
##TAC_PRINT_STRING
	leaq	.LC20(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_JUMP
	jmp Label19## TAC_LABEL
Label18:
##TAC_PRINT_STRING
	leaq	.LC21(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label19:
##TAC_EQ
	movl _2(%rip), %eax
	cmp %eax, _2(%rip)
	jne TrUE10
	movl $1, _Variable11(%rip)
	jmp FAlSE10
TrUE10:
	movl $0, _Variable11(%rip)
FAlSE10:
 ##TAC_IFZ
	movl _Variable11(%rip), %eax
	cmp $0, %eax
	jz Label20
##TAC_PRINT_STRING
	leaq	.LC22(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label20:
##TAC_EQ
	movl _2(%rip), %eax
	cmp %eax, _1(%rip)
	jne TrUE11
	movl $1, _Variable12(%rip)
	jmp FAlSE11
TrUE11:
	movl $0, _Variable12(%rip)
FAlSE11:
 ##TAC_IFZ
	movl _Variable12(%rip), %eax
	cmp $0, %eax
	jz Label21
##TAC_PRINT_STRING
	leaq	.LC23(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label21:
##TAC_GE
	movl _2(%rip), %eax
	cmp %eax, _2(%rip)
	jg TrUE12
	movl $1, _Variable13(%rip)
	jmp FAlSE12
TrUE12:
	movl $0, _Variable13(%rip)
FAlSE12:
 ##TAC_IFZ
	movl _Variable13(%rip), %eax
	cmp $0, %eax
	jz Label22
##TAC_PRINT_STRING
	leaq	.LC24(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label22:
##TAC_GE
	movl _2(%rip), %eax
	cmp %eax, _8(%rip)
	jg TrUE13
	movl $1, _Variable14(%rip)
	jmp FAlSE13
TrUE13:
	movl $0, _Variable14(%rip)
FAlSE13:
 ##TAC_IFZ
	movl _Variable14(%rip), %eax
	cmp $0, %eax
	jz Label23
##TAC_PRINT_STRING
	leaq	.LC25(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label23:
##TAC_LE
	movl _2(%rip), %eax
	cmp %eax, _2(%rip)
	jl TrUE14
	movl $1, _Variable15(%rip)
	jmp FAlSE14
TrUE14:
	movl $0, _Variable15(%rip)
FAlSE14:
 ##TAC_IFZ
	movl _Variable15(%rip), %eax
	cmp $0, %eax
	jz Label24
##TAC_PRINT_STRING
	leaq	.LC26(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label24:
##TAC_LE
	movl _2(%rip), %eax
	cmp %eax, _0(%rip)
	jl TrUE15
	movl $1, _Variable16(%rip)
	jmp FAlSE15
TrUE15:
	movl $0, _Variable16(%rip)
FAlSE15:
 ##TAC_IFZ
	movl _Variable16(%rip), %eax
	cmp $0, %eax
	jz Label25
##TAC_PRINT_STRING
	leaq	.LC27(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label25:
##TAC_LT
	movl _2(%rip), %eax
	cmp %eax, _3(%rip)
	jle TrUE16
	movl $1, _Variable17(%rip)
	jmp FAlSE16
TrUE16:
	movl $0, _Variable17(%rip)
FAlSE16:
 ##TAC_IFZ
	movl _Variable17(%rip), %eax
	cmp $0, %eax
	jz Label26
##TAC_PRINT_STRING
	leaq	.LC28(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label26:
##TAC_LT
	movl _2(%rip), %eax
	cmp %eax, _2(%rip)
	jle TrUE17
	movl $1, _Variable18(%rip)
	jmp FAlSE17
TrUE17:
	movl $0, _Variable18(%rip)
FAlSE17:
 ##TAC_IFZ
	movl _Variable18(%rip), %eax
	cmp $0, %eax
	jz Label27
##TAC_PRINT_STRING
	leaq	.LC29(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label27:
##TAC_G
	movl _2(%rip), %eax
	cmp %eax, _1(%rip)
	jge TrUE18
	movl $1, _Variable19(%rip)
	jmp FAlSE18
TrUE18:
	movl $0, _Variable19(%rip)
FAlSE18:
 ##TAC_IFZ
	movl _Variable19(%rip), %eax
	cmp $0, %eax
	jz Label28
##TAC_PRINT_STRING
	leaq	.LC30(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label28:
##TAC_G
	movl _2(%rip), %eax
	cmp %eax, _2(%rip)
	jge TrUE19
	movl $1, _Variable20(%rip)
	jmp FAlSE19
TrUE19:
	movl $0, _Variable20(%rip)
FAlSE19:
 ##TAC_IFZ
	movl _Variable20(%rip), %eax
	cmp $0, %eax
	jz Label29
##TAC_PRINT_STRING
	leaq	.LC31(%rip), %rdi
	movb	$0, %al
	callq	_printf
## TAC_LABEL
Label29:
## TAC_LABEL
Label31:
##TAC_LE
	movl _i(%rip), %eax
	cmp %eax, _10(%rip)
	jl TrUE20
	movl $1, _Variable21(%rip)
	jmp FAlSE20
TrUE20:
	movl $0, _Variable21(%rip)
FAlSE20:
 ##TAC_IFZ
	movl _Variable21(%rip), %eax
	cmp $0, %eax
	jz Label30
##TAC_PRINT_EXPRESSION
	leaq	.LC32(%rip), %rdi
	movl	_i(%rip), %esi
	movb	$0, %al
	callq	_printf
##TAC_PRINT_STRING
	leaq	.LC33(%rip), %rdi
	movb	$0, %al
	callq	_printf
##TAC_ADD
	movl	_i(%rip), %eax
	addl	_1(%rip), %eax
	movl	%eax, _Variable22(%rip)
#TAC_ATRI
movl _Variable22(%rip), %eax
movl %eax, _i(%rip)
##TAC_JUMP
	jmp Label31## TAC_LABEL
Label30:
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
	.globl 	_i
	.data
_i:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable0
	.data
_Variable0:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable1
	.data
_Variable1:
	.long 	0
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
##TAC_VAR_DECL
	.globl 	_Variable4
	.data
_Variable4:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable5
	.data
_Variable5:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable6
	.data
_Variable6:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable7
	.data
_Variable7:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable8
	.data
_Variable8:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable9
	.data
_Variable9:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable10
	.data
_Variable10:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable11
	.data
_Variable11:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable12
	.data
_Variable12:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable13
	.data
_Variable13:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable14
	.data
_Variable14:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable15
	.data
_Variable15:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable16
	.data
_Variable16:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable17
	.data
_Variable17:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable18
	.data
_Variable18:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable19
	.data
_Variable19:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable20
	.data
_Variable20:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable21
	.data
_Variable21:
	.long 	0
##TAC_VAR_DECL
	.globl 	_Variable22
	.data
_Variable22:
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
	.globl 	_3
	.data
_3:
	.long 	3
##DECL_LITERAL
	.globl 	_4
	.data
_4:
	.long 	4
##DECL_LITERAL
	.globl 	_8
	.data
_8:
	.long 	8
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
.LC0:
	.string "%d"
.LC1:
	.string " OI PRI\n"
.LC2:
	.string "certo\n"
.LC3:
	.string "errado\n"
.LC4:
	.string "certo\n"
.LC5:
	.string "errado\n"
.LC6:
	.string "certo\n"
.LC7:
	.string "errado\n"
.LC8:
	.string "certo\n"
.LC9:
	.string "errado\n"
.LC10:
	.string "certo\n"
.LC11:
	.string "errado\n"
.LC12:
	.string "errado\n"
.LC13:
	.string "certo\n"
.LC14:
	.string "errado\n"
.LC15:
	.string "certo\n"
.LC16:
	.string "errado\n"
.LC17:
	.string "certo\n"
.LC18:
	.string "errado\n"
.LC19:
	.string "certo\n"
.LC20:
	.string "errado\n"
.LC21:
	.string "certo\n"
.LC22:
	.string "1\n"
.LC23:
	.string "N devia printar 1\n"
.LC24:
	.string "2\n"
.LC25:
	.string "N devia printar 2\n"
.LC26:
	.string "3\n"
.LC27:
	.string "N devia printar 3\n"
.LC28:
	.string "4\n"
.LC29:
	.string "N devia printar 4\n"
.LC30:
	.string "5\n"
.LC31:
	.string "N devia printar 5\n"
.LC32:
	.string "%d"
.LC33:
	.string "\n"
