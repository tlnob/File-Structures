//7163822 Thais Lima de Oliveira Nobre
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

//funcao referente à funcionalidade 3 do trabalho. Ela recebe a funçao binarioParaTexto em um loop lendo
//o arquivo binário já gravado anteriormente e checa pela string passada como parâmetro via stdin qual o campo
//será buscado. Caso seja buscado nroInscricao a busca para (break), caso seja outro campo, a busca é realizada
//até o final do arquivo.
 int buscaCampo(FILE *fin, TregistroDados *reg, char *campo, char *valor_campo, TregistroCabecalho *cab) {

    char buffer[80];
    int i = 0;
    int nro, j = 0;
    double nota;
    int match = 0;
    int vector[100];
    fseek(fin, 16000, SEEK_SET); //setando apos os 16k primeiros bytes
    while(fread(buffer, 80, 1, fin)) {
        binarioParaTexto(buffer, &reg[i]);
        if(strcmp(campo, "nroInscricao") == 0) {
            nro = atoi(valor_campo);
            if(nro == reg[i].nroInscricao) {
                match = 1;
                printRegistroDados(&reg[i]);
                break; //id único, não há necessidade de procurar mais
            } else {
                i++;
                continue;
            }
        } else if(strcmp(campo, "nota") == 0) {
            nota = atof(valor_campo);
            if(nota == reg[i].nota) {
                match = 1;
                printRegistroDados(&reg[i]);
            } else {
                i++;
                continue;
            }
        } else if(strcmp(campo, "data") == 0) {
            if(strcmp(valor_campo, reg[i].data) == 0) {
                match = 1;
                printRegistroDados(&reg[i]);
            } else {
                i++;
                continue;
            }
        } else if(strcmp(campo, "cidade") == 0) {
            if(reg[i].tamanho_cidade != 0 && strcmp(valor_campo, reg[i].cidade) == 0) {
                match = 1;
                printRegistroDados(&reg[i]);
            } else {
                i++;
                continue;
            }
        } else if (strcmp(campo, "nomeEscola") == 0) {
            if(reg[i].tamanho_nomeEscola != 0 && strcmp(valor_campo, reg[i].nomeEscola) == 0) {
                match = 1;
                printRegistroDados(&reg[i]);
            } else {
                i++;
                continue;
            } 
        } else {
            puts("Registro inexistente.");
            exit(0);
        }
        if(reg->cidade != NULL) {
           free(reg->cidade);
            reg->cidade = NULL;
        }
        if(reg->nomeEscola != NULL) {
            free(reg->nomeEscola);
            reg->nomeEscola = NULL;
        }
        i++;
    }
    if(match == 0) {
        puts("Registro inexistente.");
        return -1;
    } else {
        if(i*80 < 16000) { //se acessou menos de 16k são 2 páginas, 1: cabeçalho 2: 1ª página.
            puts("Número de páginas de disco acessadas: 2");  //2 para pular a página de cabeçalho 
            return i;   
        } else {
            double total = 1+((i*80)/16000); // i*80 é a quantidade de registros visitada vezes seu tamanho, divide-se por 16000 que é o tamanho da página de disco
            if(total >= 0) { //arredondamento para cima
                total= (int)(total + 0.5);
            }
            printf("Número de páginas de disco acessadas: %.0lf\n", total); 
            puts("a");
            return i;
        }
    }
}

//referente à funcionalidade 4 a função lê do binário, passa pra texto com "binarioParaTexto"
//e dá um fseek exatamente na posição onde o RRN do registro se encontra, multplicando-o por 80
// que é o tamanho do registro, printando-o na tela
void buscaCampoPorRRN(char *arquivo, int rrn, TregistroDados *reg) {
    FILE *fin = fopen(arquivo, "rb");
    char buffer[80];
    int i = 0, match = 0, bytesSize = 0;
    if(fin == NULL) {
        puts("Falha no carregamento do arquivo.");
        exit(0);
    }
    fseek(fin, -16000, SEEK_END);   //fazendo a conta excluindo os 16000 primeiros bytes da página de cabeçalho
    bytesSize = ftell(fin);
    if (rrn*80 > bytesSize) { //se o RRN do stdin for maior que o tamanho de bytes do arquivo ele nao existe
        puts("Registro inexistente.");
    } else {
        fseek(fin, 16000-80, SEEK_SET); //setando apos os 16k primeiros bytes     
        fseek(fin, rrn*80, SEEK_CUR);  
        while(fread(buffer, 80, 1, fin)) {
            fread(buffer, 80, 1, fin);
            binarioParaTexto(buffer, reg);
            printRegistroDados(reg);
            i++;
            break;
        }
        printf("Número de páginas de disco acessadas: %d\n", 2+((i*80)/16000));
    }
    fclose(fin);
}
