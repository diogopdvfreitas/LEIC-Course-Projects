all: par-shell fibonacci

par-shell: commandlinereader.o par-shell.o 
	gcc -o par-shell par-shell.o commandlinereader.o

commandlinereader.o: commandlinereader.c commandlinereader.h
	gcc -g -c commandlinereader.c

par-shell.o: par-shell.c commandlinereader.h
	gcc -g -c par-shell.c

fibonacci.o: fibonacci.c
	gcc -g -c fibonacci.c -o fibonacci.o

fibonacci: fibonacci.o
	gcc fibonacci.o -o fibonacci
	
	





