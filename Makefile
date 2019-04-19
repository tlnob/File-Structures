CC=gcc

all: 
	gcc -o arquivo *.c -I.

debug: 
	gcc -o arquivo *.c -I. -D_DEBUG
	
run: 
	./arquivo
