CC=gcc
CFLAGS=-I.

all: main.c struct.h
	gcc -o arquivo main.c $(CFLAGS)
	

run: 
	./arquivo


