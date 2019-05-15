//7163822 Thais Lima de Oliveira Nobre
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registroCabecalho {
    char status[1]; 
    int  topoPilha;
    char tagCampo1[1];
    char desCampo1[55];
    char tagCampo2[1];
    char desCampo2[55];
    char tagCampo3[1];
    char desCampo3[55];
    char tagCampo4[1];
    char desCampo4[55];
    char tagCampo5[1];
    char desCampo5[55];
} TregistroCabecalho;

typedef struct registroDados {
    char removido[1]; //campos adicionais
    int encadeamento;
    int nroInscricao; //3 PRIMEIROS FIXO
    double nota;
    char data[10]; //TODO FAZER MÁSCARA PARA DATA
    int tamanho_cidade;
    char *cidade; //variável
    int tamanho_nomeEscola;
    char *nomeEscola;
} TregistroDados;

void            preencheFimDaString(char*);
void            insertCabecalho(TregistroCabecalho *);
int             gravarCabecalhoBinario(FILE *, TregistroCabecalho *);
void            printRegistroDados(TregistroDados *);
int             gravarDadosBinario(TregistroDados *, FILE *, int);
int             alocarCamposVariaveis(char *, char **);
void            lerRegistroTexto(TregistroDados *, char *);
void            lerRegistroTextoGravaBinario(char *, TregistroCabecalho *, TregistroDados *, char *);
TregistroDados* binarioParaTexto(char *, TregistroDados *);
int             buscaCampo(FILE *, TregistroDados *, char *, char *, TregistroCabecalho *);
TregistroDados* iteradorBinarioTexto(TregistroDados *, char *);
void            buscaCampoPorRRN(char *, int, TregistroDados *);

void            removeReg(char *filein, TregistroDados *reg, char *campo, char *valor_campo, TregistroCabecalho *cab);
void            insert(char *, TregistroDados *, TregistroCabecalho *);
void            update(char *, TregistroDados *, TregistroCabecalho *);
void            handleRemove(int, FILE *);
void            scan_quote_string(char *);
void            trim(char *);
void            binarioNaTela2(char *);