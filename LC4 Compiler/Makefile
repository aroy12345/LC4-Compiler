all: trace

trace: LC4.o loader.o trace.c
	clang -g LC4.o loader.o trace.c -o trace

LC4.o:
	clang -g -c LC4.c -o LC4.o

loader.o: loader.c
	clang -g -c loader.c -o loader.o

	
clean:
	rm -rf *.o

clobber: clean
	rm -rf trace
