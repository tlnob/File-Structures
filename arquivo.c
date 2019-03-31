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
    int nroInscricao; //3 PRIMEIROS FIXO
    float nota[8];
    char data[10]; //TODO FAZER MÁSCARA PARA DATA
    char *cidade; //variável
    char *nomeEscola;
    char removido[1]; //campos adicionais
    int encadeamento;
} TregistroDados;

//está lendo os valores TODO arrumar nulos e atrelar à struct
void *fileHandler(TregistroCabecalho reg) {
  char buffer[32000];
  int i = 0;
  FILE *f = fopen("SCC0503012019trabalho1csv.csv", "r");
    if (f == NULL) {
        memcpy(reg.status, "0", 1); //todo conferir se é zero msm
        printf("Error\n");
    } else {
        while(getc(f)!= EOF) {
            memcpy(reg.status, "1", 1);    //TODO ver se é 1 msm
            fgets(buffer, sizeof(buffer), f); 
            char *tok = strtok(buffer, ",");
            while(tok != NULL) {
                if (tok == "") tok = "aaa"; 
                i++;
                printf("Tok: %s\n", tok);
                tok = strtok(NULL, ",");
            }
        }
        fclose(f);
    }
}
//le csv e gera arquivo binário

// utilizando memcpy para armazenar os chars na struct
TregistroCabecalho insertCabecalho(TregistroCabecalho cabecalho) { 

    memcpy(cabecalho.status, "x", 1);     
    cabecalho.topoPilha = -1;
    
    char charcampo1[] = "numero de inscricao do participante do ENEM";
    strcpy(cabecalho.tagCampo1, "1");
    strcpy(cabecalho.desCampo1, charcampo1);


    //memcpy(cabecalho.tagCampo1, "1", 1);
    //memcpy(cabecalho.desCampo1, charcampo1, 55);
    


    char charcampo2[] = "nota do participante do ENEM na prova de matematica";
    memcpy(cabecalho.tagCampo2, "2", 1);
    memcpy(cabecalho.desCampo2, charcampo2, strlen(charcampo2)+1);
    
    char charcampo3[] = "data";
    memcpy(cabecalho.tagCampo3, "3", 1);
    memcpy(cabecalho.desCampo3, charcampo3, strlen(charcampo3)+1);

    char charcampo4[] = "cidade";
    memcpy(cabecalho.tagCampo4, "4", 1);
    memcpy(cabecalho.desCampo4, charcampo4, strlen(charcampo4)+1);
    
    char charcampo5[] = "nome da escola de ensino medio";
    memcpy(cabecalho.tagCampo5, "5", 1);
    memcpy(cabecalho.desCampo5, charcampo5, strlen(charcampo5)+1);
  
    printf("\n status: %s\n", cabecalho.status);
    printf("\n TOPO: %d  \n", cabecalho.topoPilha);
    printf("\n Tag campo 1: %s \n", cabecalho.tagCampo1);
    printf("\n Desc campo 1: %s \n", cabecalho.desCampo1);
    printf("\n T2 : %s \n", cabecalho.tagCampo2);
    printf("\n D2: %s \n", cabecalho.desCampo2);
    printf("\n T3: %s \n", cabecalho.tagCampo3);
    printf("\n D3: %s \n", cabecalho.desCampo3);
    printf("\n T4: %s \n", cabecalho.tagCampo4);
    printf("\n D4: %s \n", cabecalho.desCampo4);
    printf("\n T5: %s \n", cabecalho.tagCampo5);
    printf("\n D5: %s \n", cabecalho.desCampo5);
}

/*
void  insertregistroDados(TregistroDados dados) {
    // @todo tratar nulos na inserção do csv
        dados[0].nroInscricao = 1; //MOCKS
        dados[0].nota = 1.2;
        dados[0].data = "1234567894";
        dados[0].cidade = malloc(sizeof(char*2));
        dados[0].cidade = "12";
        dados[0].nomeEscola = malloc(sizeof(char*2));
        dados[0].nomeEscola = "xe";
        dados[0].removido = "s";
        dados[0].encadeamento = 2;
}*/

int main () { 
    char paginaDisco[16000];
    TregistroCabecalho cabecalho, cab;
    cab = insertCabecalho(cabecalho); // TODO  . O registro de cabeçalho deve ocupar uma página de disco. 
    printf("\n%d\n", cab.topoPilha);
    fileHandler(cabecalho);
//    TregistroDados *dados = malloc(sizeof(TregistroDados)*n); //n é a qde de linhas lidas no fread.
  
    return 0;
}