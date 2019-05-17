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
  
    char *file, *csv; 
    char buffer[80], buff[80], arquivo[30], field[20], valor[40];
    char *bin = "arquivo1.bin", *tok;
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
        buscaCampoPorRRN(arquivo, rrn, dados);
    } else if(option == 5) { //funcionalidade 5s
        scanf("%d", &len);
        for(int i = 0; i <= len; i++) { 
            scanf(" %s", field); //lê as linhas seguintes
            scan_quote_string(valor);
            trim(field);
            trim(valor);
            removeReg(arquivo, dados, field, valor, cabecalho); //todo arquivo vem com valor errado
        }
        binarioNaTela2(arquivo);
    }
    if(cabecalho != NULL) {
        free(cabecalho);
        cabecalho = NULL;
    }

    return 0;
}

