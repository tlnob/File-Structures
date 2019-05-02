//7163822 Thais Lima de Oliveira Nobre
//http://wiki.icmc.usp.br/images/2/20/SCC0503012019trabalho1b.pdf
//http://wiki.icmc.usp.br/index.php/SCC0503012019(cdac)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"


int main () { 
    TregistroCabecalho *cabecalho;
    TregistroDados dados[10000]; 
  
    char option[4], *file;                
    char *csv; 
    char buffer[80], buff[80];
    //csv = "teste.csv";
    char *bin = "arquivoTrab1si.bin";
    int nro;    
    FILE *fbin;
    int size = 0, i = 0;
    FILE* fin;
    fflush(stdout);
    scanf("%[^\n]", option); 

    char *tok = strtok(option, " ");
    nro = atoi(tok); //primeiro valor antes de espaco "1 "
    if(nro == 1) { //funcionalidade 1
        cabecalho = malloc(sizeof(TregistroCabecalho));
        tok = strtok(0, " ");
        csv = tok;
        lerRegistroTextoGravaBinario(csv, cabecalho, dados, bin); // lê do csv para struct
        if(cabecalho != NULL) {
            free(cabecalho);
            cabecalho = NULL;
        }   
    }
    else if(nro == 2) { //funcionalidade 2
        tok = strtok(0, " ");
        iteradorBinarioTexto(dados, tok);
    } else if(nro == 3) { //funcionalidade 3 
        char *arquivo = strtok(0, " ");
        tok = strtok(0, " ");
        char *valor = strtok(0, "");
        FILE *fin = fopen(arquivo, "rb"); 
        if(arquivo == NULL) {
            puts("Falha no processamento do arquivo.");
            exit(0);
        }
        buscaCampo(fin, dados, tok, valor, cabecalho);
        fclose(fin);
    } else if(nro == 4){ //funcionalidade 4 
        char *arquivo = strtok(0, " ");
        tok = strtok(0, " "); //rrn
        buscaCampoPorRRN(arquivo, tok, dados);
    } else if(nro == 5) { //funcionalidade 5
        char *arquivo = strtok(0, " ");
        tok = strtok(0, " "); //n vezes
        int len = atoi(tok);
        for(int i = 0; i < len; i++) {
            char *file = strtok(0, " ");
            char *field = strtok(0, " ");
            char *valor = strtok(0, "");
            removeReg(arquivo, dados, tok, valor, cabecalho);
        }
    }

    return 0;
}