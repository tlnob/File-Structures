//7163822 Thais Lima de Oliveira Nobre
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"


/**Essa função remove os registros da funcionalidade 5
 * Nela é realizada uma busca e consequente remoção
 * **/
void removeReg(char *filein, TregistroDados *reg, char *campo, char *valor_campo, TregistroCabecalho *cab) {
    int i = 0, count = 0, nro;
    char buffer[80];

    FILE *fin = fopen(filein, "r+b");
    if(fin == NULL) {
        puts("Falha no processamento do arquivo.");
        exit(0);
    }

    fseek(fin, 16000, SEEK_SET); //setando apos os 16k primeiros bytes
    while(fread(buffer, 80, 1, fin)) { 
        if(feof(fin)) break;
        binarioParaTexto(buffer, &reg[i]);
        if(strcmp(campo, "nroInscricao") == 0) {
            nro = atoi(valor_campo);
            if(nro == reg[i].nroInscricao) {
                handleRemove(i, fin);
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
            if(reg[i].tamanho_cidade != 0 && strcmp(valor_campo, reg[i].cidade) == 0) {
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
        i++;
        count++;
    }    
    fclose(fin);
}

/**
 * Função responsável por toda a lógica de pilha para remoção dos arquivos binários. 
 * Ela é utilizada na função removereg.
 * **/
void handleRemove(int rrn, FILE *fin) {
    int topo;
    unsigned long int flag;
    flag = ftell(fin);
    if(fin == NULL) printf("Falha no processamento do arquivo.");

    /*Lendo o topoPilha do cabeçalho*/
    fseek(fin, 1, SEEK_SET);  
    fread(&topo, sizeof(int), 1, fin); //lê o topo na variável "topo"
    
    /*Alterando o registro buscado */
    fseek(fin, (rrn*80)+16000, SEEK_SET); //retorna o rrn do registro buscado pulando as páginas de disco iniciais
    fputc('*', fin); //grava * no campo removido
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
    fseek(fin, flag, SEEK_SET);
}

/**
 * Função utilizada na funcionalidade 5 para checar se o número de linhas do stdin é maior
 * do que o número de linhas do arquivo.
 * **/
int regExists(char *file_in, int len) {
	FILE *fin;
	unsigned long int seek;
	int reg;
	fin = fopen(file_in, "rb");
	
	fseek(fin, 0, SEEK_END);
	seek = ftell(fin);

	reg = (seek-16000)/80;

	if(len > reg) return 0;
	else return 1;
    fclose(fin);
}

/**
 * Função responsável por inserir os registros de acordo com o valor do topoPilha
 * **/
void insertReg(char *filein, TregistroDados *reg, TregistroCabecalho *cab, char *nroInscricao, char *nota, char *data, char *cidade, char *nomeEscola, int rrn) {
  
    int topo, encadeamento = -1, count = 1;
    char buffer[80];

    FILE *fin = fopen(filein, "r+b");
    if(fin == NULL) {
        puts("Falha no processamento do arquivo.");
        exit(0);
    }

    memcpy(reg->removido,"-",1); 
    reg->encadeamento = -1;
    reg->nroInscricao = atoi(nroInscricao);
    if(strcmp("NULO", nota) == 0) {
        reg->nota = -1;    
    } else  reg->nota = atof(nota);
    
    if (strcmp("", data) == 0) {
        char datanull[10];
        datanull[0] = '\0';
        while(count <= 9){
            datanull[count] = '@';
            count++;
        }
        memcpy(reg->data, datanull, 10);
    } else {
        memcpy(reg->data, data, 10); 
    }

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

       
    gravarDadosBinario(reg, fin, 0); // Grava no arquivo binário

    //* volta para o campo topo da pilha para gravar o encadeamento do registro que foi sobrescrito*//
    fseek(fin, 1, SEEK_SET);
    fwrite(&encadeamento, sizeof(int), 1, fin);    

    fclose(fin);
   
}

/**
 * Função responsável por atualizar os registros
 * **/
void updateReg(char *filein, TregistroDados *reg, TregistroCabecalho *cab, int rrn, char *field, char* valor) {
    
    char buffer[80];
    int i = 0, match = 0, bytesSize = 0;

    FILE *fin = fopen(filein, "r+b");
    if(fin == NULL) {
        puts("Falha no processamento do arquivo.");
        exit(0);
    }

    //buscaCampoPorRRN(fin, rrn, reg);


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

            if(strcmp(field, "nroInscricao") == 0) {
                reg->nroInscricao = atoi(valor);
            } else if(strcmp(field, "nota")) {
                reg->nota = atof(valor);
            } else if(strcmp(field, "data")) {
                strcpy(reg->data, field);
            } else if(strcmp(field, "cidade")) {
                reg->tamanho_cidade = alocarCamposVariaveis(field, &reg->cidade);
            } else if(strcmp(field, "nomeEscola")) {
                reg->tamanho_nomeEscola = alocarCamposVariaveis(field, &reg->nomeEscola);
            }
            gravarDadosBinario(reg, fin, 0);
            
            printRegistroDados(reg);
            break;
        }
        printf("Número de páginas de disco acessadas: %d\n", 2+((i*80)/16000));
    }
    

    fclose(fin);
}