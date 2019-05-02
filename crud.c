#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

TregistroCabecalho* removeReg(char *filein, TregistroDados *reg, char *campo, char *valor_campo, TregistroCabecalho *cab) {
    char buffer[80];
    FILE *fin = fopen(filein, "rb");
    if(fin == NULL) {
        puts("Falha no processamento do arquivo.");
        exit(0);
    }
    int rrn = buscaCampo(fin, reg, campo, valor_campo, cab);
    printf("rrn: %d", rrn);
    rrn = rrn+16000;
    fseek(fin, rrn, SEEK_SET); //irá retornar o rrn do registro buscado pulando as páginas de disco iniciais
    
    fread(buffer, 80, 1, fin); // lê o registro onde está o campo procurado
    int size = 0; 
    fputc('*', fin); //escreve no binário correspondente ao primeiro byte do campo buscado *
    fwrite(&cab->topoPilha, sizeof(int), 1, fin); // grava o valor anteriormente do topo da pilha
    
    while (size < 80) { // preenche com @ o restante
        fputc('@', fin);
        size++;
    }
    cab->topoPilha = rrn; // topo da pilha assume o valor do rrn
    fclose(fin);

    return cab;
}

void insert(TregistroDados *dados, TregistroCabecalho *cabecalho) {
    
}

void update(TregistroDados *dados, TregistroCabecalho *cabecalho) {
    
}