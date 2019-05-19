//7163822 Thais Lima de Oliveira Nobre
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

//função auxiliar que irá ler UMA CADA LINHA do csv e gravar os dados na struct  separação por ','
//utiliza-se memcpy para alocar corretamente o numero de bytes nos campos char.
void lerRegistroTexto(TregistroDados *reg, char *buffer) { //OK
    int start = 0, end = 0, count = 0;
    char *tok;

    for(end = start; buffer[end] != '\0'; ++end) {
        if(buffer[end] == ',' || buffer[end] == '\n' || buffer[end] == '\r') {
            buffer[end] = '\0';
            tok = &buffer[start];
            int isNull = (start == end); //nulo se o start for igual ao end, ou seja,não andou nenhum campo a mais
            memcpy(reg->removido, "-", 1);
            reg->encadeamento = -1;
            if (count == 0) reg->nroInscricao = atoi(tok);    
            else if(count == 1) reg->nota = isNull ? -1 : atof(tok);  // se é nulo -1, se não transforma para double
            else if(count == 2) {
                if(isNull) {
                    memcpy(reg->data, "\0@@@@@@@@@", 10); //preenche campos varios com \0@ até 10 bytes
                } else {
                    memcpy(reg->data, tok, 10);
                }
            } 
            else if(count == 3) reg->tamanho_cidade = alocarCamposVariaveis(tok, &reg->cidade);
            else if(count == 4) reg->tamanho_nomeEscola = alocarCamposVariaveis(tok, &reg->nomeEscola);
            
            count++;    
            start = end + 1;
        }
    }
}

//função auxiliar da  funcao "lerRegistroTexto" que irá alocar os campos variáveis. ele irá receber um ponteiro para a struct
//nos campos cidade e nomeEscola e alocar 2 bytes  mais para o campo da tag
int alocarCamposVariaveis(char *tok, char **campo) { //OK
    int len = strlen(tok);
    if(len > 0) { //se não for campo nulo
        *campo = malloc(len+1); //aloca cidade
        if(*campo == NULL) exit(0);
        strcpy(*campo, tok); //copia registro - irá para as primeiras posições    
        return len + 2; //para alocar os 2 bytes
    } else {
        *campo = NULL;
        return 0;
    }
}

//função auxiliar para gravar para binário os dados que estão na struct TregistroDados
//fwrites são realizados a fim de escrever no arquivo binário recebido como parâmetro
//os campos variáveis também têm de alocar 1 byte a mais para a tag '4' ou '5' e outro para ' '
//@'s para preencher o restante até o registro ter tamanho fixo de 80 bytes
int gravarDadosBinario(TregistroDados *reg, FILE *bin, int size) { 
                
    size = sizeof(char)        * fwrite(&reg->removido, sizeof(char), 1, bin);
    size += sizeof(int)        * fwrite(&reg->encadeamento, sizeof(int), 1, bin);
    size += sizeof(int)        * fwrite(&reg->nroInscricao, sizeof(int), 1, bin); 
    size += sizeof(double)     * fwrite(&reg->nota, sizeof(reg->nota), 1, bin);
    size += sizeof(reg->data)  * fwrite(&reg->data, sizeof(reg->data), 1, bin);

    if(reg ->tamanho_cidade != 0) {
        size += sizeof(int)         * fwrite(&reg->tamanho_cidade, sizeof(int), 1, bin);
        fputc('4',bin);
        size += reg->tamanho_cidade * fwrite(reg->cidade, reg->tamanho_cidade-1 , 1, bin);
    } 
    if(reg->tamanho_nomeEscola != 0) {
        size += sizeof(int)             * fwrite(&reg->tamanho_nomeEscola, sizeof(int), 1, bin);
        fputc('5',bin);
        size += reg->tamanho_nomeEscola * fwrite(reg->nomeEscola, reg->tamanho_nomeEscola-1, 1, bin);
    }
    //printf("size: %d", size);
    while (size < 80) { // preenche com @ até size==80
        fputc('@', bin);
        size++;
    }
    //printf("insc: %d + nota: %.2lf + data: %s + tamanho_cidade: %d, cidade: %s + tamanho_nomeEscola: %d, reg-nomeEscola: %s (size: %d)\n", 
    //    reg->nroInscricao, reg->nota, reg->data, reg->tamanho_cidade, reg->cidade, reg->tamanho_nomeEscola, reg->nomeEscola, size);
    return size;
}

//função que engloba as funções anteriores "lerRegistroTexto" e "gravarDadosBinario" lendo 
// em um loop linha a linha do csv lendo para struct e gravando binário.
void lerRegistroTextoGravaBinario(char csv_nome[], TregistroCabecalho *cabecalho, TregistroDados *dados, char bin_file[]) { //OK
        char buffer[80];
        
        FILE *csv_file = fopen(csv_nome, "r"); 
        int size = 0, i = 0;
        if (csv_file == NULL) {
            printf("Falha no carregamento do arquivo.\n");
            exit(0);
        }
               
        FILE *bin  = fopen(bin_file, "wb"); //lê da struct e passa para arquivo binário
        memcpy(cabecalho->status, "1", 1); 
        if(bin == NULL) {
            memcpy(cabecalho->status, "0", 1); 
            printf("Falha no carregamento do arquivo.");
            exit(0);
        }
        insertCabecalho(cabecalho);
        size = gravarCabecalhoBinario(bin, cabecalho);
        fgets(buffer, sizeof(buffer), csv_file); //le a primeira linha com indices
        while(fgets(buffer, sizeof(buffer), csv_file) != NULL) {
            lerRegistroTexto(&dados[i], buffer);
            size += gravarDadosBinario(&dados[i], bin, size);
           // printRegistroDados(&dados[i]);
            i++;
        }
       // debug("total size: %d\n", size);
        fclose(csv_file);
        fclose(bin);
        memcpy(cabecalho->status, "1", 1); 
        printf("%s", bin_file);
}

//função auxiliar da funcionalidade 2/3/4 que lê o binário já gravado e o transforma de volta para texto
//para isso ele lê o binário e grava na struct de acordo a quantidade de bytes do campo anterior
//para os campos variáveis é realizada uma lógica se a tag existente é 4 ou 5 e alocá-los de acordo
TregistroDados* binarioParaTexto(char buffer[], TregistroDados *reg) { //OK
    memcpy(&reg->removido, &buffer[0], sizeof(char));
    memcpy(&reg->encadeamento, &buffer[1], sizeof(int));
    memcpy(&reg->nroInscricao, &buffer[5], sizeof(int));
    memcpy(&reg->nota, &buffer[9], sizeof(double));
    memcpy(&reg->data, &buffer[17], sizeof(char)*10);
    //debug("read fields: %c %d %d %lf %s\n", reg->removido[0], reg->encadeamento, reg->nroInscricao, reg->nota, reg->data);

    int i = 27; // 27, pois a data é no byte 17 e ela ocupa 10 bytes
    while (i<80 && buffer[i] != '@') {
        char tag = buffer[i+4];  //tamanho int e a tag
        if (tag == '4') {
            memcpy(&reg->tamanho_cidade, &buffer[i], sizeof(int));
            reg->cidade = malloc(sizeof(char) * (reg->tamanho_cidade));
            memcpy(reg->cidade, &buffer[i+5], reg->tamanho_cidade-1);
            i += 4 + reg->tamanho_cidade;
//             debug("tam: %d, str: %s\n", reg->tamanho_cidade, reg->cidade);
        }
        else if (tag == '5') {
            memcpy(&reg->tamanho_nomeEscola, &buffer[i], sizeof(int));
            reg->nomeEscola = malloc(sizeof(char) * reg->tamanho_nomeEscola);
            memcpy(reg->nomeEscola, &buffer[i+5], reg->tamanho_nomeEscola-1);
            i += 4 + reg->tamanho_nomeEscola;
    //           debug("tam: %d, str: %s\n", reg->tamanho_nomeEscola, reg->nomeEscola);
        }
    }
    return reg; 
}

//funcão que imprime os registros de dados na tela a partir do arquivo binário, foi utilizado snprintf 
//1 para maior controle dos bytes que estão sendo impressos
//2 nos campos possivelmente nulos é feita uma checagem se o próximo byte é um '\0' (data)
// ou se existe o registro (cidade e nomeEscola)
void printRegistroDados(TregistroDados *reg) {
    char buffer[1000];
    int end = snprintf(buffer, sizeof(buffer), "%d", reg->nroInscricao);
    int bufferSize = sizeof(buffer);
    if(reg->nota != -1) {
        end += snprintf(&buffer[end], bufferSize-end, " %.1lf", reg->nota);
    }
    if(reg->data[0] != '\0') { // tem alguma data (nulo é \0@@@)
        buffer[end++] = ' '; //após salvar o espaço inicial, incrementa o end
        memcpy(&buffer[end], reg->data, sizeof(reg->data)); //end está na posição que a data deve ser gravada
        end += sizeof(reg->data); //pega  posição até o registro.nota com o end, para entar usar o memcpy e armazenar o restante, pois a dat possui apenas 10 char
    }
    if(reg->cidade) {
        end += snprintf(&buffer[end], bufferSize-end, " %d", reg->tamanho_cidade-2); //-2 para desalocar os bytes a mais para a tag
        end += snprintf(&buffer[end], bufferSize-end, " %s", reg->cidade);
    }
    if(reg->nomeEscola) {
        end += snprintf(&buffer[end], bufferSize-end, " %d", reg->tamanho_nomeEscola-2);
        end += snprintf(&buffer[end], bufferSize-end, " %s", reg->nomeEscola);
    }
    buffer[end] = '\0';
    printf("%s\n", buffer);
 
}

//funcao centralizadora referente à funcionalidade 2. Ele irá iterar sobre o arquivo binário e printar na tela
//o texto referente. Ao fim irá printar quantas páginas de disco foram acessadas
TregistroDados* iteradorBinarioTexto(TregistroDados *dados, char *fileIn) {
        char buff[80];
        FILE *fin = fopen(fileIn, "rb");
        int i = 0;

        if(fin == NULL) {
            puts("Falha no processamento do arquivo.");
            exit(0);
        }
        fseek(fin, 0, SEEK_END);

        if(ftell(fin) == 0) {
            puts("Registro inexistente.");
            exit(0);
        }
        fseek(fin, 16000, SEEK_SET); //pulando os 16k primeiros bytes do cabeçalho
        while(fread(buff, 80, 1, fin)) {
            binarioParaTexto(buff, &dados[i]);
            printRegistroDados(&dados[i]);
            if(dados->cidade != NULL) {
                free(dados->cidade);
                dados->cidade = NULL;
            }
            if(dados->nomeEscola != NULL) {
                free(dados->nomeEscola);
                dados->nomeEscola = NULL;
            }
            i++;
        }
        fclose(fin);         
        printf("Número de páginas de disco acessadas: %d\n", 1+((i*80)/16000));  //+1 da primeira página de disco
        return dados;
}
