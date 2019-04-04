//7163822 Thais Lima de Oliveira Nobre
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

//http://wiki.icmc.usp.br/images/c/c8/SCC0503012019trabalho1.pdf

/*Deve  ser  feita  a  diferenciação  entre  o  espaço  utilizado  e  o  lixo.  Para  tanto, todas  as stringsdevem  ser  finalizadas  com  ‘\0’  e  o  lixo  deve  ser  identificado pelo  caractere  ‘@’.Ou  seja,  quando  sobra-se  espaço  no  final  do  registro,  o registro deve ser completado com lixo até o seu final.*/
//O campo nroInscricaonão aceita valores repetidos e nem valores nulos. •Os  campos nota, data, cidadee nomeEscolaaceitam  valores  repetidos  e valores nulos.
//CAMPOS NULOS:
//campos de tam fixo: \0@@@@@@@@@ ou inteiro -1
//variavel: não  devem  ser  armazenados  os  campos  referentes:  (i)ao  indicador  de tamanho; (ii)à tagque representa o dado;e (iii) ao valor do dado.
//(i) removidodeve  ser  inicializado  com  o  valor ‘-’;  e  (ii) encadeamentodeve ser inicializado com o valor -1. 


// utilizando memcpy para armazenar os chars na struct
void insertCabecalho(TregistroCabecalho *cabecalho) { 

    memcpy(cabecalho->status, "x", 1);     
    cabecalho->topoPilha = -1;
    
    char charcampo1[] = "numero de inscricao do participante do ENEM";
    strcpy(cabecalho->tagCampo1, "1");
    strcpy(cabecalho->desCampo1, charcampo1);
    //memcpy(cabecalho.tagCampo1, "1", 1);
    //memcpy(cabecalho.desCampo1, charcampo1, 55);

    char charcampo2[] = "nota do participante do ENEM na prova de matematica";
    memcpy(cabecalho->tagCampo2, "2", 1);
    memcpy(cabecalho->desCampo2, charcampo2, strlen(charcampo2)+1);
    
    char charcampo3[] = "data";
    memcpy(cabecalho->tagCampo3, "3", 1);
    memcpy(cabecalho->desCampo3, charcampo3, strlen(charcampo3)+1);

    char charcampo4[] = "cidade";
    memcpy(cabecalho->tagCampo4, "4", 1);
    memcpy(cabecalho->desCampo4, charcampo4, strlen(charcampo4)+1);
    
    char charcampo5[] = "nome da escola de ensino medio";
    memcpy(cabecalho->tagCampo5, "5", 1);
    memcpy(cabecalho->desCampo5, charcampo5, strlen(charcampo5)+1);
  
    printf("\n status: %s\n", cabecalho->status);
    printf("\n TOPO: %d  \n", cabecalho->topoPilha);
    printf("\n Tag campo 1: %s \n", cabecalho->tagCampo1);
    printf("\n Desc campo 1: %s \n", cabecalho->desCampo1);
    printf("\n T2 : %s \n", cabecalho->tagCampo2);
    printf("\n D2: %s \n", cabecalho->desCampo2);
    printf("\n T3: %s \n", cabecalho->tagCampo3);
    printf("\n D3: %s \n", cabecalho->desCampo3);
    printf("\n T4: %s \n", cabecalho->tagCampo4);
    printf("\n D4: %s \n", cabecalho->desCampo4);
    printf("\n T5: %s \n", cabecalho->tagCampo5);
    printf("\n D5: %s \n", cabecalho->desCampo5);
}


void printRegistro(TregistroDados *reg) {
    char buffer[1000];
    int end = snprintf(buffer, sizeof(buffer), "%d", reg->nroInscricao);
    int n = sizeof(buffer);
    if(reg->nota != -1) {
        end += snprintf(&buffer[end], n-end, " %.1lf ", reg->nota);
        //TODO: tratar null e checar end
    }
    if(reg->data[0] != '\0') { // tem alguma data (nulo é \0@@@)
        buffer[end++] = ' '; //após salvar o espaço inicial, incrementa o end
        memcpy(&buffer[end], reg->data, sizeof(reg->data)); //end está na posição que a data deve ser gravada
        end += sizeof(reg->data); //pega  posição até o registro.nota com o end, para entar usar o memcpy e armazenar o restante, pois a dat possui apenas 10 char
    }
    if(reg->cidade[0] != '\0') {
        end += snprintf(&buffer[end], n-end, " %s", reg->cidade);
        //TODO: tratar null e checar end
    }
    if(reg->nomeEscola[0] != '\0') {
        end += snprintf(&buffer[end], n-end, " %s", reg->nomeEscola);
        //TODO: tratar null e checar end
    }
    buffer[end] = '\0';
    printf("%s\n", buffer);
}

void lerRegistroBinario(TregistroDados *reg, char *buffer) {
}

void lerRegistroTexto(TregistroDados *reg, char *buffer) {
        int start = 0, end = 0, count = 0;
        char *tok;
        for(end = start; buffer[end] != '\0'; ++end) {
            if(buffer[end] == ',' || buffer[end] == '\n' || buffer[end] == '\r') {
                char field[80]; //string temporária
                buffer[end] = '\0';
                tok = &buffer[start];
                int isNull = (start == end);
                if (count == 0) reg->nroInscricao = atoi(tok);    
                else if(count == 1) reg->nota = isNull ? -1 : atof(tok);  // se é nulo -1, se não transforma para double
                else if(count == 2){
                    if(isNull) {
                        memcpy(reg->data, "\0@@@@@@@@@", 10); //preenche campos varios com @
                    } else {
                        memcpy(reg->data, tok, 10); //data[10] nao dá espaço para o \0
                    }
                } 
                else if(count == 3) {
                    memset(reg->cidade, '@', sizeof(reg->cidade)); //@ em todos os campos
                    reg->cidade[0] = '\0'; // \0 no primeiro campo
                    strcpy(reg->cidade, tok); //copia registro - irá para as primeiras posições
                } 
                else if(count == 4) {
                    memset(reg->nomeEscola, '@', sizeof(reg->nomeEscola)); //@ em todos os campos
                    reg->nomeEscola[0] = '\0';
                    strcpy(reg->nomeEscola, tok);
                }
                count++;    
                start = end + 1;
            }
        }
}

void menu () {
    int option;                
    char *csv;
    do {
        puts("Selecione uma opção");
        puts("1 - Gravação  desses  registros de csv em  um  arquivo  de  dados de saída");
        puts("2 - Permita a recuperação dos dados, de todos os registros");
        puts("3 -Permita  a  recuperação  dos  dados  de  todos  os  registros  que  satisfaçam  um  critério de  busca  determinado  pelo  usuário.");
        puts("4 -Permita a recuperação dos dados de um registro, a partir da identificação do RRN (número relativo do registro) do registro desejado pelo usuário.");
        puts("0 - para sair");
        scanf("%d", &option);
        switch (option) {
            case 1:
                puts("Entrada csv do programapara a funcionalidade [1]");
                //scanf("%s", &csv);
                csv = "SCC0503012019trabalho1csv.csv"; //TODO: ler via scanf
                char buffer[1000];
                TregistroDados dados[10000]; //
                FILE *f = fopen(csv, "r"); //TODO: Passar como arg[0] o csv?
                if (f == NULL) {
            //        memcpy(reg.status, "0", 1); //todo conferir se é zero msm
                    printf("Falha no carregamento do arquivo\n");
                    break;
                } 
                int i = 0;
                while(fgets(buffer, sizeof(buffer), f) != NULL) {
                   lerRegistroTexto(&dados[i], buffer);
                   printRegistro(&dados[i]);
                    i++;             
                }
                fclose(f);
                menu();
                break;
            case 2:
                break;
            case 3:
                
                break;
            case 4:
                break;
            default:
                break;
        }
    } while (option=0);
    

}

int main () { 
    char paginaDisco[16000];
    TregistroCabecalho cabecalho;
    
    insertCabecalho(&cabecalho); // TODO  . O registro de cabeçalho deve ocupar uma página de disco. 

    menu();
    
    return 0;
}