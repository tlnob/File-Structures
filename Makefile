CC=gcc
CFLAGS=-I.

all: main.c struct.h
	gcc -o arquivo main.c $(CFLAGS) 

debug: main.c struct.h
	gcc -o arquivo main.c $(CFLAGS) -D_DEBUG
	
run: 
	./arquivo

