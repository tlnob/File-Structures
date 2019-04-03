//7163822 Thais Lima de Oliveira Nobre
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//http://wiki.icmc.usp.br/images/c/c8/SCC0503012019trabalho1.pdf


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
    //char removido[1]; //campos adicionais
    //int encadeamento;
    int nroInscricao; //3 PRIMEIROS FIXO
    float nota;
    char data[10]; //TODO FAZER MÁSCARA PARA DATA
    //int tamanho_cidade;
    char cidade[30]; //variável
    //int tamanho_nomEscola;
    char nomeEscola[30];
} TregistroDados;
//CRIAR ARQUIVO BINÁRIO


/*void insertDados(TregistroDados) {
/*Deve  ser  feita  a  diferenciação  entre  o  espaço  utilizado  e  o  lixo.  Para  tanto, todas  as stringsdevem  ser  finalizadas  com  ‘\0’  e  o  lixo  deve  ser  identificado pelo  caractere  ‘@’.Ou  seja,  quando  sobra-se  espaço  no  final  do  registro,  o registro deve ser completado com lixo até o seu final.*/
//O campo nroInscricaonão aceita valores repetidos e nem valores nulos. •Os  campos nota, data, cidadee nomeEscolaaceitam  valores  repetidos  e valores nulos.
//CAMPOS NULOS:
//campos de tam fixo: \0@@@@@@@@@ ou inteiro -1
//variavel: não  devem  ser  armazenados  os  campos  referentes:  (i)ao  indicador  de tamanho; (ii)à tagque representa o dado;e (iii) ao valor do dado.
//(i) removidodeve  ser  inicializado  com  o  valor ‘-’;  e  (ii) encadeamentodeve ser inicializado com o valor -1. 


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


/*void  insertregistroDados(TregistroDados dados, FILE *f) {
    int i = 0;if(to)
    while(fread(&dados, sizeof(dadoif(to)s), 1, f) != 0) {
//        printf("reg #%d\n");if(to)
        printf("reg #%d\n", i++);if(to)
        printf("inscricao %d\n", daif(to)dos.nroInscricao);
        printf("nota %.1f\n", dadosif(to).nota);
        printf("cidade %s\n", dadosif(to).cidade);
        printf("nomeEscola %s\n", dados.nomeEscola);
    }
    // @todo tratar nulos na inserção do csv
        // dados[0].nroInscricao = 1; //MOCKS
        // dados[0].nota = 1.2;
        // dados[0].data = "1234567894";
        // dados[0].cidade = malloc(sizeof(char*2));
        // dados[0].cidade = "12";
        // dados[0].nomeEscola = malloc(sizeof(char*2));
        // dados[0].nomeEscola = "xe";
        // dados[0].removido = "s";
        // dados[0].encadeamento = 2;
}*/

int main () { 
    char paginaDisco[16000], *tok;
    TregistroCabecalho cabecalho, cab;
    TregistroDados dados[100000];
    cab = insertCabecalho(cabecalho); // TODO  . O registro de cabeçalho deve ocupar uma página de disco. 
    char buffer[10000];
    FILE *f = fopen("SCC0503012019trabalho1csv.csv", "r");
//    insertregistroDados(dados, f);
    if (f == NULL) {
//        memcpy(reg.status, "0", 1); //todo conferir se é zero msm
        printf("Falha no carregamento do arquivo\n");
    } else {
        char *tok;
        int i = 0, j = 0, count = 0, w = 0;
        while(fgets(buffer, 500, f) != NULL) {
   //         printf("toks: %s\n", buffer);
            for(w = 0; buffer[w] == '/0'; ++w) {
                for(j = 0; buffer[j] != ','; ++j) {
                    if (count == 0) dados[i].nroInscricao = atoi(tok);    
                    else if(count == 1) dados[i].nota = atof(tok);
                    else if(count == 2) strcpy(dados[i].data, tok);
                    else if(count == 3) strcpy(dados[i].cidade, tok);
                    else if(count == 4) strcpy(dados[i].nomeEscola, tok);
                    count++;    
                }
                printf("inscricao: %d\n",  dados[i].nroInscricao);                
                count = 0;
            }
        }
    }
            // while(tok != NULL) {
            //     printf("toks: %s\n", tok);
            //   for(i=0; tok = strtok(NULL, ",");i++) {
            
            //     dados[i].nota = atof(tok);
            // //    dados[i].cidade = malloc(sizeof(tok));
            //       strcpy(dados[i].cidade, tok);
            //       strcpy(dados[i].nomeEscola, tok);
            // //    dados[i].nomeEscola = malloc(sizeof(tok));
            //     // printf("inscricao: %d\n",  dados[i].nroInscricao);
            //     // printf("nota: %.2f,\n", dados[i].nota);
            //     // printf("cidade: %s,\n", dados[i].cidade);
            //     // printf("nome escola: %s\n\n", dados[i].nomeEscola);
            // }
                
                
// 
//                printf("dados[0] %.2f\n", &(dados->nota));
    
    
//        printf("inscricao %d\n", dados->nroInscricao);
        // printf("nota %.1f\n", dados->nota);
        // printf("cidade %s\n", dados->cidade);
        // printf("nomeEscola %s\n", dados->nomeEscola);
 
    fclose(f);
    return 0;
}