rm asm.s
rm a.out
make clean 
make 
./etapa6 text.file 
gcc asm.s 
./a.out
# yacc parser.y -v