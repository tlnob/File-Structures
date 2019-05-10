#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

TregistroCabecalho* removeReg(char *filein, TregistroDados *reg, char *campo, char *valor_campo, TregistroCabecalho *cab) {
    char buffer[80];
    filein = "arquivoTrab1si.bin"; // TODO : delete line after fix in main
    FILE *fin = fopen(filein, "r+b");
    if(fin == NULL) {
        puts("Falha no processamento do arquivo.");
        exit(0);
    }

    int byte = buscaCampo(fin, reg, campo, valor_campo, cab);
    printf("rrn: %d\n", byte);
    byte = byte+16000; // retorna 80 OK
    fseek(fin, byte, SEEK_SET); //irá retornar o rrn do registro buscado pulando as páginas de disco iniciais
    fwrite("*", sizeof(char), 1, fin); 
    fwrite(&cab->topoPilha, sizeof(int), 1, fin);
    
    printf("topo pilha1: %d\n", &cab->topoPilha);
    
    int size = 5; //  1 char e 4 bytes de int 
    while (size < 80) { // preenche com @ o restante
        fputc('@', fin);
        size++;
    }


    fwrite(&cab->topoPilha, sizeof(int), 1, fin); // grava o valor anteriormente do topo da pilha


    printf("topoPilha %d\n", cab->topoPilha);     

    cab->topoPilha = byte; // topo da pilha assume o valor do rrn
    printf("topoPilha 2 %d\n", cab->topoPilha);     

    fclose(fin);
    return cab;
}

void insert(TregistroDados *dados, TregistroCabecalho *cabecalho) {
    
}

void update(TregistroDados *dados, TregistroCabecalho *cabecalho) {
    
}