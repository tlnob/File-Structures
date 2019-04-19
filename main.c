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
        buscaCampo(arquivo, dados, tok, valor, cabecalho);
    } else if(nro == 4){ //funcionalidade 4 
        char *arquivo = strtok(0, " ");
        tok = strtok(0, " "); //rrn
        buscaCampoPorRRN(arquivo, tok, dados);
    }
    return 0;
}