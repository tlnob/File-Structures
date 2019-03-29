#include <stdio.h>
#include <stdlib.h>

typedef struct registroCabecalho {
    char status[1]; 
    int topoPilha;
    char tagnroInscricao[1];
    char nroInscricao[55];
    char tagNota[1];
    char nota[55];
    char tagData[1];
    char data[55];
    char tagCidade[1];
    char cidade[55];
    char tagNomeescola[1];
    char nomeEscola[55];
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



FILE *fileHandler() {
  char store[10000];
  FILE *f = fopen("SCC0503012019trabalho1csv.csv", "r");
    if (f == NULL) {
        printf("Error\n");
        return NULL;
    } else {
        fread(store, sizeof(f), f);
    }
}
//le csv e gera arquivo binário

int main () {
    TregistroDados *dados = NULL;
    TregistroCabecalho *cabecalho = NULL;

    fileHandler();

   /* dados[0].nroInscricao = 1; //MOCKS
    dados[0].nota = 1.2;
    dados[0].data = "1234567894";
    dados[0].cidade = malloc(sizeof(char*2));
    dados[0].cidade = "12";
    dados[0].nomeEscola = malloc(sizeof(char*2));
    dados[0].removido = "s";
    dados[0].encadeamento = 2;
    
    printf("dados[0]);
    
    
    char file_name;
  
    FILE *f = fileHandler();

    if (f !== NULL)
*/

    

    return 0;
}
