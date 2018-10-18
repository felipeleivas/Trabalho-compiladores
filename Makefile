#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in scanner.l
#

etapa4: hash.o semantic.o lex.yy.o main.o y.tab.o ast.o
	gcc -o etapa4 hash.o semantic.o lex.yy.o main.o y.tab.o ast.o
main.o: main.c
	gcc -c main.c
ast.o: ast.c
	gcc -c ast.c
hash.o: hash.c
	gcc -c hash.c
semantic.o: semantic.c
	gcc -c semantic.c
lex.yy.o: lex.yy.c hash.o
	gcc -c lex.yy.c
y.tab.o: y.tab.c
	gcc -c y.tab.c
lex.yy.c: y.tab.c scanner.l 
	lex scanner.l 
y.tab.c: parser.y
	yacc -d parser.y
clean:
	rm *.o lex.yy.c y.tab.c etapa4
