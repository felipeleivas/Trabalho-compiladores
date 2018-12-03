##TAC_VAR_DECL
	.globl 	_a
	.data
_a:
	.long 	3
.LC0:
	.string "%d"
.LC0:
	.string "%d"
##TAC_VAR_VEC_DECL
	.comm _s,12,4
.LC0:
	.string "%d"
.LC0:
	.string "%d"
##TAC_VECTOR_INIT
	.globl 	_21
	.data
_21:
##TAC_VECTOR_INIT
	.globl 	_21
	.data
_21:
##TAC_VECTOR_INIT
	.globl 	_21
	.data
_21:
.LC0:
	.string "%d"
##TAC_FUNCTION_PARAM
	.comm _sooooo,4,4
.LC0:
	.string "%d"
##TAC_FUNCTION_PARAM
	.comm _riririr,4,4
.LC0:
	.string "%d"
##TAC_BEGINFUN
	.globl main
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
##TAC_SUB
	.comm _Variable--0,4,4
	movl _8(%rip), %edx
	movl _9(%rip), %eax
	subl %eax, %edx
	movl %edx, %eax
	movl %eax, _Variable--0(%rip)
.LC0:
	.string "%d"
.LC0:
	.string "%d"
## TAC_LABEL
Label--1:
.LC0:
	.string "%d"
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
##TAC_LT
	.comm _Variable--1,4,4
	movl _a(%rip), %eax
	cmp %eax, _10(%rip)
	jl HUE0
	movl $0, _Variable--1(%rip)
	jmp FIMHUE0
HUE0:
	movl $1, _Variable--1(%rip)
FIMHUE0:
 .LC0:
	.string "%d"
##TAC_IFZ
	movl _Variable--1(%rip), %eax
	jz Label--0
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
.LC0:
	.string "%d"
##TAC_JUMP
	jmp Label--1.LC0:
	.string "%d"
## TAC_LABEL
Label--0:
.LC0:
	.string "%d"
.LC0:
	.string "%d"
## TAC_RETURN
	movl _sooooo(%rip), %eax
	leave
	ret 
.LC0:
	.string "%d"
##TAC_ENDFUN
	leave
	ret 
	.cfi_endproc
.LC0:
	.string "%d"
.LC0:
	.string "%d"
##TAC_FUNCTION_PARAM
	.comm _ri,4,4
.LC0:
	.string "%d"
##TAC_BEGINFUN
	.globl felie
felie:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
## TAC_VEC_READ
	.comm _Variable--2,4,4
	movl _1(%rip), %eax 
	movl _s(,%eax,4), %eax 
	movl %eax, _Variable--2(%rip) 
.LC0:
	.string "%d"
.LC0:
	.string "%d"
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
##TAC_ADD
	.comm _Variable--4,4,4
	movl _2(%rip), %eax
	addl _2(%rip), %eax
	movl %eax, _Variable--4(%rip)
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
##TAC_ADD
	.comm _Variable--5,4,4
	movl _Variable--4(%rip), %eax
	addl _3(%rip), %eax
	movl %eax, _Variable--5(%rip)
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
##TAC_ADD
	.comm _Variable--6,4,4
	movl _Variable--5(%rip), %eax
	addl _2(%rip), %eax
	movl %eax, _Variable--6(%rip)
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
##TAC_ADD
	.comm _Variable--7,4,4
	movl _Variable--6(%rip), %eax
	addl _1(%rip), %eax
	movl %eax, _Variable--7(%rip)
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
##TAC_ADD
	.comm _Variable--8,4,4
	movl _Variable--7(%rip), %eax
	addl _4(%rip), %eax
	movl %eax, _Variable--8(%rip)
.LC0:
	.string "%d"
.LC0:
	.string "%d"
##TAC_READ
	movl $_a, %edi
	call gets
	movl $_a, %edi
	call atoi
	movl %eax, _a(%rip)
.LC0:
	.string "%d"
.LC0:
	.string "%d"
## TAC_SYMBOL
.LC0:
	.string "%d"
##TAC_EQ
	.comm _Variable--9,4,4
	movl _a(%rip), %eax
	cmp %eax, _11(%rip)
	je HUE1
	movl $1, _Variable--9(%rip)
	jmp FIMHUE1
HUE1:
	movl $0, _Variable--9(%rip)
FIMHUE1:
 .LC0:
	.string "%d"
##TAC_IFZ
	movl _Variable--9(%rip), %eax
	jz Label--2
.LC0:
	.string "%d"
##TAC_PRINT
	.comm _"felipe",4,4 ##278
	movl	_"felipe"(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
.LC0:
	.string "%d"
##TAC_PRINT
	.comm _"12",4,4 ##278
	movl	_"12"(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
.LC0:
	.string "%d"
##TAC_PRINT
	.comm _"2",4,4 ##278
	movl	_"2"(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
.LC0:
	.string "%d"
##TAC_JUMP
	jmp Label--3.LC0:
	.string "%d"
## TAC_LABEL
Label--2:
.LC0:
	.string "%d"
##TAC_PRINT
	.comm _"eeeee",4,4 ##278
	movl	_"eeeee"(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
.LC0:
	.string "%d"
## TAC_LABEL
Label--3:
.LC0:
	.string "%d"
##TAC_ENDFUN
	popq	 %rbp
	leave
	ret 
	.cfi_endproc
.LC0:
	.string "%d"
