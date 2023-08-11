all:  assembler

asm_parser.o: asm_parser.h asm_parser.c
	clang -c asm_parser.c -o asm_parser.o

assembler: asm_parser.o
	clang assembler.c asm_parser.o -o assembler

clobber:
	rm -f *.o assembler 
