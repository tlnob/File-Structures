#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void removeReg(char *filein, TregistroDados *reg, char *campo, char *valor_campo, TregistroCabecalho *cab) {
    filein = "arquivoTrab1si.bin"; // TODO : delete line after fix in main
    FILE *fin = fopen(filein, "r+b");
    if(fin == NULL) {
        puts("Falha no processamento do arquivo.");
        exit(0);
    }

    int rrn = buscaCampo(fin, reg, campo, valor_campo, cab);
    printf("rrn: %d\n", rrn);
    int byte = rrn+16000; // retorna 80 OK

    int topo;
    fseek(fin, 1, SEEK_SET); 
    fread(&topo, sizeof(int), 1, fin);
    printf("topo %d\n", topo);     

    fseek(fin, byte, SEEK_SET); //irá retornar o rrn do registro buscado pulando as páginas de disco iniciais
    fwrite("*", sizeof(char), 1, fin); 
    fwrite(&topo, sizeof(int), 1, fin); 
    
    int size = 5; //  1 char e 4 bytes de int 
    while (size < 80) { // preenche com @ o restante
        fputc('@', fin);
        size++;
    }

    cab->topoPilha = rrn; // topo da pilha assume o valor do rrn
    
    fseek(fin, 1, SEEK_SET); //para voltar para o cabeçalho e gravar o novo dado do topo da pilha
    fwrite(&rrn, sizeof(int), 1, fin);

    fclose(fin);
}

void insert(char *filein, TregistroDados *dados, TregistroCabecalho *cabecalho) {
 //se topo for -1 tem que adicionar com seek_end e escrever no fim do registro
    filein = "arquivoTrab1si.bin"; // TODO : delete line after fix in main
    FILE *fin = fopen(filein, "r+b");
    if(fin == NULL) {
        puts("Falha no processamento do arquivo.");
        exit(0);
    }

    fclose(fin);


    
}

void update(char *filein, TregistroDados *dados, TregistroCabecalho *cabecalho) {
    
}