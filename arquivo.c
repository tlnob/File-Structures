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


void *fileHandler(TregistroCabecalho reg) {
  char paginaDisco[16000];
  FILE *f = fopen("SCC0503012019trabalho1csv.csv", "r");
    if (f == NULL) {
        //reg.status = '0';
        printf("Error\n");
    } else {
        //reg.status = '1';
   //     fread(paginaDisco, f);
        fclose(f);
    }
}
//le csv e gera arquivo binário

// utilizando memcpy para armazenar os chars na struct
void insertCabecalho(TregistroCabecalho cabecalho) { 

    memcpy(cabecalho.status,"x", 2); 
    cabecalho.topoPilha = -1;
    
    char charcampo1[] = "numero de inscricao do participante do ENEM";
    memcpy(cabecalho.tagCampo1, "1" , 2);
    memcpy(cabecalho.desCampo1, charcampo1, strlen(charcampo1)+1);
    
    char charcampo2[] = "nota do participante do ENEM na prova de matematica";
    memcpy(cabecalho.tagCampo2, "2", 2);
    memcpy(cabecalho.desCampo2, charcampo2, strlen(charcampo2)+1);

    char charcampo3[] = "data";
    memcpy(cabecalho.tagCampo3, "3", 2);
    memcpy(cabecalho.desCampo3, charcampo3, strlen(charcampo3)+1);

    char charcampo4[] = "cidade";
    memcpy(cabecalho.tagCampo4, "4", 2);
    memcpy(cabecalho.desCampo4, charcampo4, strlen(charcampo4)+1);
    
    char charcampo5[] = "nome da escola de ensino medio";
    memcpy(cabecalho.tagCampo5, "5", 2);
    memcpy(cabecalho.desCampo5, charcampo5, strlen(charcampo5)+1);
}

int main () { 
    char paginaDisco[16000];
    TregistroCabecalho cabecalho;
    
    insertCabecalho(cabecalho);
 //   fileHandler(cabecalho);


//    TregistroDados *dados = malloc(sizeof(TregistroDados)*n); //n é a qde de linhas lidas no fread.
  
// @todo tratar nulos na inserção do csv
 /*   dados[0].nroInscricao = 1; //MOCKS
    dados[0].nota = 1.2;
    dados[0].data = "1234567894";
    dados[0].cidade = malloc(sizeof(char*2));
    dados[0].cidade = "12";
    dados[0].nomeEscola = malloc(sizeof(char*2));
    dados[0].nomeEscola = "xe";
    dados[0].removido = "s";
    dados[0].encadeamento = 2;
 */      
    char file_name;
  
    return 0;
}