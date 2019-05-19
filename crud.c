#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void removeReg(char *filein, TregistroDados *reg, char *campo, char *valor_campo, TregistroCabecalho *cab) {
    FILE *fin = fopen(filein, "r+b");
    if(fin == NULL) {
        puts("Falha no processamento do arquivo.");
        exit(0);
    }
    //TODO: Caso de teste 11: só 1 registro, remove o registro e depois pede para remover de novo
    int i = 0, count = 0, nro;
    char buffer[80];
    
    fseek(fin, 16000, SEEK_SET); //setando apos os 16k primeiros bytes
    while(fread(buffer, 80, 1, fin)) { //TODO ele nao funciona para o primeiro registro
        if(feof(fin)) break;
        binarioParaTexto(buffer, &reg[i]);
        if(strcmp(campo, "nroInscricao") == 0) {
            nro = atoi(valor_campo);
            if(nro == reg[i].nroInscricao) {
                //printf("reg[i].nroInscricao %d\n", reg[i].nroInscricao); 
                //printRegistroDados(&reg[i]);
                handleRemove(i, fin);
                //printf("i %d\n", i);
                break;
             } else {
                i++;
                continue;
            }
        } else if(strcmp(campo, "data") == 0) {
            if(strcmp(valor_campo, reg[i].data) == 0) {//comparaçao entra
                handleRemove(i, fin);                
               // printf("data i: %d\n", i);
            } else {
                i++;
                continue;
            } 
        }  else if(strcmp(campo, "nota") == 0) {
            double nota = atof(valor_campo);
            if(nota == reg[i].nota) {
                handleRemove(i, fin);
               // printf("nota i: %d\n", i);
            } else {
                i++;
                continue;
            }
        } else if(strcmp(campo, "cidade") == 0) {
            if(reg[i].tamanho_cidade != 0 && strcmp(valor_campo, reg[i].cidade) == 0) {
               // printRegistroDados(&reg[i]);
                handleRemove(i, fin);
              //  printf("cidade i: %d\n", i);
            } else {
                i++;
                continue;
            } 
        } else if (strcmp(campo, "nomeEscola") == 0) {
            if(reg[i].tamanho_nomeEscola != 0 && strcmp(valor_campo, reg[i].nomeEscola) == 0) {
                handleRemove(i, fin);
               // printf("nomeEscola: %d\n", i);
            } else {
                i++;
                continue;
            } 
        } else {
            puts("Registro inexistente.");
            exit(0);
        }
        i++;
        count++;
    }    
    fclose(fin);
}

void handleRemove(int rrn, FILE *fin) {
    int topo;
    unsigned long int flag;
    flag = ftell(fin);
    if(fin == NULL) printf("Falha no processamento do arquivo.");

    /*Lendo o topoPilha do cabeçalho*/
    fseek(fin, 1, SEEK_SET);  // inicialmente -1
    fread(&topo, sizeof(int), 1, fin); //lê o topo na variável "topo"
    
    /*Alterando o registro buscado */
    fseek(fin, (rrn*80)+16000, SEEK_SET); //retorna o rrn do registro buscado pulando as páginas de disco iniciais
    fputc('*', fin); //grava * no campo removido
    fwrite(&topo, sizeof(int), 1, fin); // grava topoPilha no campo encadeamento --TODO Nao pega certo
    
    /* @ no restante dos campos */
    int size = 5; //  1 char e 4 bytes de int 
    while (size < 80) { // preenche com @ o restante
        fputc('@', fin);
        size++;
    }
    
    /*Atualizando o topoPilha no cabeçalho*/
    
    fseek(fin, 1, SEEK_SET); //para voltar para o cabeçalho e gravar o novo dado do topo da pilha
    fwrite(&rrn, sizeof(int), 1, fin); // gravando no topoPilha rrn do registro
    fseek(fin, flag, SEEK_SET);
}

void insertReg(char *filein, TregistroDados *reg, TregistroCabecalho *cab, char *nroInscricao, char *nota, char *data, char *cidade, char *nomeEscola, int rrn) {

    FILE *fin = fopen(filein, "r+b");
    if(fin == NULL) {
        puts("Falha no processamento do arquivo.");
        exit(0);
    }

    int topo, encadeamento = -1, count = 1;
    char buffer[80];

    memcpy(reg->removido,"-",1); 
    reg->encadeamento = -1;
    reg->nroInscricao = atoi(nroInscricao);
    if(strcmp("NULO", nota) == 0) {
        reg->nota = -1;    
    } else  reg->nota = atof(nota);
    
    // printf("data %s\n", data);
    // printf("cidade %s\n", cidade);
    // printf("nomeEscola %s\n\n", nomeEscola);
    
    if (strcmp("", data) == 0) {
        char datanull[10];
        datanull[0] = '\0';
        while(count <= 9){
            datanull[count] = '@';
            count++;
        }
        memcpy(reg->data, datanull, 10);
    } else {
        // puts("entrou no else");
        memcpy(reg->data, data, 10); 
    }

    //printf("reg data %s\n\n", reg->data);

    if (strcmp("", cidade) == 0) {
        reg->tamanho_cidade = alocarCamposVariaveis("", &reg->cidade);
    } else reg->tamanho_cidade = alocarCamposVariaveis(cidade, &reg->cidade);
    
    if (strcmp("", nomeEscola) == 0) {
        reg->tamanho_nomeEscola = alocarCamposVariaveis("", &reg->nomeEscola);
    } else reg->tamanho_nomeEscola = alocarCamposVariaveis(nomeEscola, &reg->nomeEscola);


    //*lê o topo da pilha no cabeçalho *//
    fseek(fin, 1, SEEK_SET); 
    fread(&topo, sizeof(int), 1, fin);
    
    /** PONTEIRO vai para o fim do arquivo caso topoPilha seja -1 **/
    if(topo != -1) {
        fseek(fin, (topo*80)+16000+1, SEEK_SET); //vai pegar o valor do int encadeamento
        fread(&encadeamento, sizeof(int), 1, fin); 
        fseek(fin, (topo*80)+16000, SEEK_SET); //volta para o início do registro do topo
    }
    else fseek(fin, 0, SEEK_END); 

       
    gravarDadosBinario(reg, fin, 0);

    //* volta para o campo topo da pilha para gravar o encadeamento do registro que foi sobrescrito*//
    fseek(fin, 1, SEEK_SET);
    fwrite(&encadeamento, sizeof(int), 1, fin);    

    //printf("topo: %s %s %s %s %s \n", nroInscricao, nota, data, cidade, nomeEscola);
    fclose(fin);
   
}

void updateReg(char *filein, TregistroDados *reg, char *campo, char *valor_campo, TregistroCabecalho *cab) {
    
}