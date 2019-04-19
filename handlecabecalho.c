//7163822 Thais Lima de Oliveira Nobre
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

// função para inserir dados no cabeçalho na struct, inicializando os campos com @ e 
// depois alocando os valores.
void insertCabecalho(TregistroCabecalho *cabecalho) { //ok
    memcpy(cabecalho->status, "1", 1);
    cabecalho->topoPilha = -1;

    strcpy(cabecalho->tagCampo1, "1");

    char charcampo1[55] = "numero de inscricao do participante do ENEM";
    preencheFimDaString(charcampo1);
    memcpy(cabecalho->desCampo1, charcampo1, 55);
    
    strcpy(cabecalho->tagCampo2, "2");

    char charcampo2[55] = "nota do participante do ENEM na prova de matematica";
    preencheFimDaString(charcampo2);
    memcpy(cabecalho->desCampo2, charcampo2, 55);
        
    strcpy(cabecalho->tagCampo3, "3");
    char charcampo3[55] = "data";
    preencheFimDaString(charcampo3);
    memcpy(cabecalho->desCampo3, charcampo3, 55);

    strcpy(cabecalho->tagCampo4, "4");
    char charcampo4[55] = "cidade na qual o participante do ENEM mora";
    preencheFimDaString(charcampo4);
    memcpy(cabecalho->desCampo4, charcampo4, 55);
    
    memcpy(cabecalho->tagCampo5, "5", 1);
    char charcampo5[55] = "nome da escola de ensino medio";
    preencheFimDaString(charcampo5);
    memcpy(cabecalho->desCampo5, charcampo5, 55);
 // printCabecalho(cabecalho);
}

//função que preenche com @'s até os 55 bytes do do cabeçalho
void preencheFimDaString(char *charCampo) {
    int i = strlen(charCampo)+1; // preenche com @ até campo 55 (fim da string)
    while(i < 55){
        charCampo[i] = '@';
        i++;
    }
}

//função para gravar para binário os dados que estão na struct TregistroCabecalho
//fwrites são realizados a fim de escrever no arquivo binário recebio como parâmetro
//e é preenchido com @'s o restante da página de disco até os 16000 primeiros bytes
//O size vai retornar quantos bytes foram gravados
int gravarCabecalhoBinario(FILE *bin, TregistroCabecalho *cabecalho) {
    int size = 0;
    
    size =                fwrite(&cabecalho->status, 1, 1, bin); 
    size += sizeof(int) * fwrite(&cabecalho->topoPilha, sizeof(int), 1, bin);
    size +=               fwrite(&cabecalho->tagCampo1, sizeof(cabecalho->tagCampo1), 1, bin);
    size += 55 *          fwrite(&cabecalho->desCampo1, sizeof(cabecalho->desCampo1), 1, bin); 
    size +=               fwrite(&cabecalho->tagCampo2, sizeof(cabecalho->tagCampo2), 1, bin);
    size += 55 *          fwrite(&cabecalho->desCampo2, sizeof(cabecalho->desCampo2), 1, bin);
    size +=               fwrite(&cabecalho->tagCampo3, sizeof(cabecalho->tagCampo3), 1, bin);
    size += 55 *          fwrite(&cabecalho->desCampo3, sizeof(cabecalho->desCampo3), 1, bin);
    size +=               fwrite(&cabecalho->tagCampo4, sizeof(cabecalho->tagCampo4), 1, bin);
    size += 55 *          fwrite(&cabecalho->desCampo4, sizeof(cabecalho->desCampo4), 1, bin);
    size +=               fwrite(&cabecalho->tagCampo5, sizeof(cabecalho->tagCampo5), 1, bin);
    size += 55 *          fwrite(&cabecalho->desCampo5, sizeof(cabecalho->desCampo5), 1, bin);
    
    while (size < 16000) { // preenche com @ 
        fputc('@', bin);
        size++;
    }
    
    return size;
}
