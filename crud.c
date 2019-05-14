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

// 5 arquivo1.bin 11
// nroInscricao 13893
// nota 477.5
// data "08/07/2005"
// nomeEscola "JOAO ALVARES DE SIQUEIR"
// cidade "Sao Carlos"
// cidade "Coimbra"
// nomeEscola "JOSE CELESTINO ARANHA"
// nota 667.5
// data "26/10/2005"
// nroInscricao 13595
// nroInscricao 2125
    int i = 0;
    
    char buffer[80];
    int nro;
    
    fseek(fin, 16000, SEEK_SET); //setando apos os 16k primeiros bytes

    while(fread(buffer, 80, 1, fin)) { //TODO ele nao funciona para o primeiro registro
        binarioParaTexto(buffer, &reg[i]);
        if(strcmp(campo, "nroInscricao") == 0) {
            nro = atoi(valor_campo);
            if(nro == reg[i].nroInscricao) {
                printf("reg[i].nroInscricao %d\n", reg[i].nroInscricao); 
                printRegistroDados(&reg[i]);
                handleRemove(i, fin);
                printf("i %d\n", i);
                break;
            } else {
                i++;
                continue;
            }
        } else if(strcmp(campo, "data") == 0) {
            if(strcmp(valor_campo, reg[i].data) == 0) {
                handleRemove(i, fin);                
            } else {
                i++;
                continue;
            }
        }  else if(strcmp(campo, "nota") == 0) {
            double nota = atof(valor_campo);
            if(nota == reg[i].nota) {
                handleRemove(i, fin);
            } else {
                i++;
                continue;
            }
        } else if(strcmp(campo, "cidade") == 0) {
            puts("regiii");
            if(reg[i].tamanho_cidade != 0 && strcmp(valor_campo, reg[i].cidade) == 0) {
                printRegistroDados(&reg[i]);
                handleRemove(i, fin);
            } else {
                i++;
                continue;
            } 
        } else if (strcmp(campo, "nomeEscola") == 0) {
            if(reg[i].tamanho_nomeEscola != 0 && strcmp(valor_campo, reg[i].nomeEscola) == 0) {
                handleRemove(i, fin);
            } else {
                i++;
                continue;
            } 
        } else {
            puts("Registro inexistente.");
            exit(0);
        }
        
    }

     //   binarioNaTela1(fin);
    fclose(fin);
}

void handleRemove(int rrn, FILE *fin) {
    int topo;
    rrn = rrn*80;
    /*Lendo o topoPilha do cabeçalho*/
    fseek(fin, 1, SEEK_SET);  // inicialmente -1
    fread(&topo, sizeof(int), 1, fin); //lê o topo na variável "topo"
    
    /*Alterando o registro buscado */
    fseek(fin, rrn+16000, SEEK_SET); //retorna o rrn do registro buscado pulando as páginas de disco iniciais
    fwrite("*", sizeof(char), 1, fin); //grava * no campo removido
    fwrite(&topo, sizeof(int), 1, fin); // grava topoPilha no campo encadeamento
    
    /* @ no restante dos campos */
    int size = 5; //  1 char e 4 bytes de int 
    while (size < 80) { // preenche com @ o restante
        fputc('@', fin);
        size++;
    }

    /*Atualizando o topoPilha no cabeçalho*/
    fseek(fin, 1, SEEK_SET); //para voltar para o cabeçalho e gravar o novo dado do topo da pilha
    fwrite(&rrn, sizeof(int), 1, fin); // gravando no topoPilha rrn do registro
    
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