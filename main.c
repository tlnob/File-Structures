//7163822 Thais Lima de Oliveira Nobre
//http://wiki.icmc.usp.br/images/2/20/SCC0503012019trabalho1b.pdf
//http://wiki.icmc.usp.br/images/a/a6/SCC0503012019trabalho2.pdf
//http://wiki.icmc.usp.br/index.php/SCC0503012019(cdac)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"


int main () { 
    TregistroCabecalho *cabecalho;
    TregistroDados dados[10000]; 
  
    char *file; 
    char buffer[80], buff[80], arquivo[100], field[20], valor[40];    
    char *tok, *bin = "arquivo1.bin";
    int size = 0, i = 0, option = 0, len;
    FILE* fin;
    fflush(stdout);
   	scanf("%d %s", &option, arquivo);

    cabecalho = malloc(sizeof(TregistroCabecalho));
    
    if(option == 1) { //funcionalidade 1
        lerRegistroTextoGravaBinario(arquivo, cabecalho, dados, bin); // lê do csv para struct
    }
    else if(option == 2) { //funcionalidade 2
        iteradorBinarioTexto(dados, arquivo);
    } else if(option == 3) { //funcionalidade 3 
        scanf("%s %[^\n]s", field, valor);
        FILE *fin = fopen(arquivo, "rb"); 
        if(arquivo == NULL) {
            puts("Falha no processamento do arquivo.");
            exit(0);
        }
        buscaCampo(fin, dados, field, valor, cabecalho);
        fclose(fin);
    } else if(option == 4){ //funcionalidade 4 
        int rrn;
        scanf("%d", &rrn);
        FILE *fin = fopen(arquivo, "rb"); 
        if(arquivo == NULL) {
            puts("Falha no processamento do arquivo.");
            exit(0);
        }
        buscaCampoPorRRN(fin, rrn, dados);
        fclose(fin);
    } else if(option == 5) { //funcionalidade 5
        scanf("%d", &len);
        if(regExists(arquivo, len) != 0){ //checagem se o len é maior do que as linhas do arquivo
            for(int i = 0; i <= len; i++) {
                scanf("%s", field); 
                scan_quote_string(valor);
                trim(field);
                trim(valor);
                removeReg(arquivo, dados, field, valor, cabecalho); 
            }
            binarioNaTela2(arquivo);
        } else printf("Falha no processamento do arquivo.");
        
    } else if(option == 6) {
        scanf("%d", &len);
        char buffer[80];
        char nroInscricao[6], nota[8], data[30], cidade[30], nomeEscola[30];
        for(int i = 0; i < len; i++) {            
            scanf("%s %s", nroInscricao, nota);
            
            scan_quote_string(data);
            fflush(stdin);
            scan_quote_string(cidade);
            scan_quote_string(nomeEscola);
           
            trim(data);
            trim(cidade);
            trim(nomeEscola);
            insertReg(arquivo, dados, cabecalho, nroInscricao, nota, data, cidade, nomeEscola, i); 
        }
        binarioNaTela2(arquivo);
    } else if(option == 7) {
        // 7 arquivo.bin n RRN nomeCampo1 valorCampo1
        scanf("%d", &len);
        int rrn;
        for(int i = 0; i < len; i++) {          
            scanf("%d", &rrn);
            scanf("%s", field); //lê as linhas seguintes
            scan_quote_string(valor);
            //printf("rrn: %d field:\n", rrn);
            
            trim(field);
            trim(valor);
            fflush(stdin);
            printf("rrn: %d\n field: %s\n valor: %s\n\n", rrn, field, valor);
            
            updateReg(arquivo, dados, cabecalho, rrn, field, valor); 
            
        }
    //binarioNaTela2(arquivo);


    }
    if(cabecalho != NULL) {
        free(cabecalho);
        cabecalho = NULL;
    }

    return 0;
}


