# Makefile for par-shell, version 1
# Sistemas Operativos, DEI/IST/ULisboa 2015-16

CFLAGS=-g -Wall -pedantic

all: par-shell par-shell-terminal fibonacci div0

par-shell: par-shell.o commandlinereader.o list.o listterminal.o
	gcc -o par-shell par-shell.o list.o listterminal.o commandlinereader.o -pthread

par-shell.o: par-shell.c commandlinereader.h
	gcc $(CFLAGS) -c par-shell.c

commandlinereader.o: commandlinereader.c commandlinereader.h
	gcc $(CFLAGS) -c commandlinereader.c

list.o: list.c list.h
	gcc $(CFLAGS) -c list.c

listterminal.o: listterminal.c listterminal.h
	gcc $(CFLAGS) -c listterminal.c

par-shell-terminal: par-shell-terminal.o 	
	gcc $(CFLAGS) -o par-shell-terminal par-shell-terminal.o 

par-shell-terminal.o: par-shell-terminal.c 
	gcc $(CFLAGS) -c par-shell-terminal.c

fibonacci: fibonacci.c
	gcc $(CFLAGS) -o fibonacci fibonacci.c

div0: div.c
	gcc $(CFLAGS) -o div0 div.c

run:
	clear
	./par-shell < i2.txt

clean:
	rm -f *.o par-shell fibonacci div0 core par-shell-terminal
