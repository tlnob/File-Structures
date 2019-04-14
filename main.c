//7163822 Thais Lima de Oliveira Nobre
//http://wiki.icmc.usp.br/images/2/20/SCC0503012019trabalho1b.pdf
//http://wiki.icmc.usp.br/index.php/SCC0503012019(cdac)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <struct.h>

#ifdef _DEBUG
#define debug(...) fdebug(stderr, ##__VA_ARGS__)
#else
#define debug(...)
#endif

void printCabecalho(TregistroCabecalho *cabecalho) {
    debug("\n status: %s\n", cabecalho->status);
    debug("\n TOPO: %d  \n", cabecalho->topoPilha);
    debug("\n Tag campo 1: %s \n", cabecalho->tagCampo1);
    debug("\n Desc campo 1: %s \n", cabecalho->desCampo1);
    debug("\n T2 : %s \n", cabecalho->tagCampo2);
    debug("\n D2: %s \n", cabecalho->desCampo2);
    debug("\n T3: %s \n", cabecalho->tagCampo3);
    debug("\n D3: %s \n", cabecalho->desCampo3);
    debug("\n T4: %s \n", cabecalho->tagCampo4);
    debug("\n D4: %s \n", cabecalho->desCampo4);
    debug("\n T5: %s \n", cabecalho->tagCampo5);
    debug("\n D5: %s \n", cabecalho->desCampo5);
}

void preencheFimDaString(char *charCampo) {
    int i = strlen(charCampo)+1; // preenche com @ até campo 55 (fim da string)
    while(i < 55){
        charCampo[i] = '@';
        i++;
    }
}

// função para inserir dados no cabeçalho na struct, inicializando os campos com @ e depois alocando os valores.
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

int gravarCabecalhoBinario(FILE *bin, TregistroCabecalho *cabecalho) {
    int size = 0;
    
    size =                fwrite(&cabecalho->status, 1, 1, bin); // gravando primeiro o cabeçalho
    size += sizeof(int) * fwrite(&cabecalho->topoPilha, sizeof(int), 1, bin);
    size +=               fwrite(&cabecalho->tagCampo1, sizeof(cabecalho->tagCampo1), 1, bin);
    size += 55 *          fwrite(&cabecalho->desCampo1, sizeof(cabecalho->desCampo1), 1, bin); //começa no 6 byte
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

void printRegistro(TregistroDados *reg) {
    char buffer[1000];
    int end = snprintf(buffer, sizeof(buffer), "%d", reg->nroInscricao);
    int bufferSize = sizeof(buffer);
    if(reg->nota != -1) {
        end += snprintf(&buffer[end], bufferSize-end, " %.1lf", reg->nota);

        //TODO: tratar null e checar end
    }
    if(reg->data[0] != '\0') { // tem alguma data (nulo é \0@@@)
        buffer[end++] = ' '; //após salvar o espaço inicial, incrementa o end
        memcpy(&buffer[end], reg->data, sizeof(reg->data)); //end está na posição que a data deve ser gravada
        end += sizeof(reg->data); //pega  posição até o registro.nota com o end, para entar usar o memcpy e armazenar o restante, pois a dat possui apenas 10 char
    }
    if(reg->cidade) {
        end += snprintf(&buffer[end], bufferSize-end, " %d", reg->tamanho_cidade);
        end += snprintf(&buffer[end], bufferSize-end, " %s", reg->cidade);
        //TODO: tratar null e checar end
    }
    if(reg->nomeEscola) {
        end += snprintf(&buffer[end], bufferSize-end, " %d", reg->tamanho_nomeEscola);
        end += snprintf(&buffer[end], bufferSize-end, " %s", reg->nomeEscola);
        //TODO: tratar null e checar end
    }
    buffer[end] = '\0';
    printf("%s\n", buffer);
 
}

int gravarDadosBinario(TregistroDados *reg, FILE *bin, int size) { //OK
                
    size = sizeof(char)       * fwrite(&reg->removido, sizeof(char), 1, bin);
    size = sizeof(int)        * fwrite(&reg->encadeamento, sizeof(int), 1, bin);
    size = sizeof(int)        * fwrite(&reg->nroInscricao, sizeof(int), 1, bin); // gravando os registros
    size += sizeof(double)    * fwrite(&reg->nota, sizeof(reg->nota), 1, bin);
    size += sizeof(reg->data) * fwrite(&reg->data, sizeof(reg->data), 1, bin);
    
    if(reg->tamanho_cidade != 0) {
        size += sizeof(int)         * fwrite(&reg->tamanho_cidade, sizeof(int), 1, bin);
        size += reg->tamanho_cidade * fwrite(reg->cidade, reg->tamanho_cidade, 1, bin);
    } 
    if(reg->tamanho_nomeEscola != 0) {
        size += sizeof(int)             * fwrite(&reg->tamanho_nomeEscola, sizeof(int), 1, bin);
        size += reg->tamanho_nomeEscola * fwrite(reg->nomeEscola, reg->tamanho_nomeEscola, 1, bin);
    }
    
    while (size < 80) { // preenche com @ até size==80
        fputc('@', bin);
        size++;
    }
    //debug("insc: %d + nota: %.2lf + data: %s + tamanho_cidade: %d, cidade: %s + tamanho_nomeEscola: %d, reg-nomeEscola: %s (size: %d)\n", 
    //    reg->nroInscricao, reg->nota, reg->data, reg->tamanho_cidade, reg->cidade, reg->tamanho_nomeEscola, reg->nomeEscola, size);
    return size;
}

int alocarCamposVariaveis(char *tok, char **campo) { //OK
    int len = strlen(tok);
    if(len > 0) { //se não for campo nulo
        *campo = malloc(len+1); //aloca cidade
        if(*campo == NULL) exit(0);
        strcpy(*campo, tok); //copia registro - irá para as primeiras posições    
        return len;
    } else {
        *campo = NULL;
        return 0;
    }
}

void lerRegistroTexto(TregistroDados *reg, char *buffer) { //OK
    int start = 0, end = 0, count = 0;
    char *tok;

    for(end = start; buffer[end] != '\0'; ++end) {
        if(buffer[end] == ',' || buffer[end] == '\n' || buffer[end] == '\r') {
            buffer[end] = '\0';
            tok = &buffer[start];
            int isNull = (start == end); //nulo se o star for igual ao end, ou seja,não andou nenhum char a mais
            memcpy(reg->removido, "-", 1);
            reg->encadeamento = -1;
            if (count == 0) reg->nroInscricao = atoi(tok);    
            else if(count == 1) reg->nota = isNull ? -1 : atof(tok);  // se é nulo -1, se não transforma para double
            else if(count == 2) {
                if(isNull) {
                    memcpy(reg->data, "\0@@@@@@@@@", 10); //preenche campos varios com @
                } else {
                    memcpy(reg->data, tok, 10); //data[10] nao dá espaço para o \0, portanto não é possível usar strcpy
                }
            } 
            /*Para os campos de tamanho variável, os valores nulos devem ser representados da seguinte forma:o
            não  devem  ser  armazenados  os  campos  referentes:  
            (ii) TODO: à tag que representa o dado;*/
            else if(count == 3) reg->tamanho_cidade = alocarCamposVariaveis(tok, &reg->cidade);
            else if(count == 4) reg->tamanho_nomeEscola = alocarCamposVariaveis(tok, &reg->nomeEscola);
            
            count++;    
            start = end + 1;
        }
    }
}

void lerArquivoTextoGravaBinario(char csv_nome[], TregistroCabecalho *cabecalho, TregistroDados *dados, char bin_file[]) { //OK
        char buffer[80];
        FILE *csv_file = fopen(csv_nome, "r"); 
        int size = 0, i = 0;
        if (csv_file == NULL) {
    //      memcpy(reg.status, "0", 1); //TODO conferir se é zero msm
            printf("Falha no carregamento do arquivo\n");
            exit(0);
        }        
        FILE *bin  = fopen(bin_file, "wb"); //lê da struct e passa para arquivo binário
        if(bin == NULL) {
            printf("Falha no carregamento do arquivo");
            exit(0);
        }
        insertCabecalho(cabecalho);
        size = gravarCabecalhoBinario(bin, cabecalho);
        fgets(buffer, sizeof(buffer), csv_file); //le a primeira linha com indices
        while(fgets(buffer, sizeof(buffer), csv_file) != NULL) {
            lerRegistroTexto(&dados[i], buffer);
            size += gravarDadosBinario(&dados[i], bin, size);
            printRegistro(&dados[i]);
            i++;
        }
        debug("total size: %d\n", size);
        fclose(csv_file);
        fclose(bin);
        debug("%s\n", bin_file);
}

TregistroDados* binarioParaTexto(char buffer[], TregistroDados *reg) { //OK
    int size = 0, i = 0;

    reg->cidade = malloc(sizeof(char)*55);
    reg->nomeEscola = malloc(sizeof(char)*55);

    memcpy(&reg->nroInscricao, buffer, sizeof(int));
    memcpy(&reg->nota, &buffer[4], sizeof(double));
    memcpy(&reg->data, &buffer[12], sizeof(char)*10);
    if(buffer[22] != '@') {
        memcpy(&reg->tamanho_cidade, &buffer[22], sizeof(int));
        memcpy(reg->cidade, &buffer[26], reg->tamanho_cidade);
        reg->cidade[reg->tamanho_cidade] = '\0';
    }
    if(buffer[26+reg->tamanho_cidade] != '@') {
        memcpy(&reg->tamanho_nomeEscola, &buffer[26+reg->tamanho_cidade], sizeof(int));
        memcpy(reg->nomeEscola, &buffer[26+reg->tamanho_cidade+4], reg->tamanho_nomeEscola);
        reg->nomeEscola[reg->tamanho_nomeEscola] = '\0';
    }
    return reg; 
}

 void buscaCampo(char *filein, TregistroDados *reg, char *campo, char *valor_campo) {
    FILE *fin = fopen(filein, "rb");
    if(fin == NULL) {
        puts("erro file\n");
        exit(0);
    }
    char buffer[80];
    int i = 0, has_value = 0;
    int nro;
    double nota;
    
    while(fread(buffer, 80, 1, fin)) {
        binarioParaTexto(buffer, &reg[i]);
        if(campo == "nroInscricao") {
            nro = atoi(valor_campo);
            if(nro == reg[i].nroInscricao) {
                printRegistro(&reg[i]);
                break; //id único, não há necessidade de procurar mais
            } 
        } else if(campo == "nota") {
            nota = atof(valor_campo);
            if(nro == reg[i].nota) {
                printRegistro(&reg[i]);
            }
        } else if(campo == "data") {
            if(strcmp(valor_campo, reg[i].data) == 0) {
                printRegistro(&reg[i]);
            }
        } else if(campo == "cidade") {
            if(reg[i].tamanho_cidade != 0 && strcmp(valor_campo, reg[i].cidade) == 0) {
                printRegistro(&reg[i]);
            }
        } else if (campo == "nomeEscola") {
            if(reg[i].tamanho_nomeEscola != 0 && strcmp(valor_campo, reg[i].nomeEscola) == 0) {
                printRegistro(&reg[i]);
            }
        } else {
            puts("Campo inexistente");
            exit(0);
        }
        free(reg->cidade);
        free(reg->nomeEscola);
        i++;
    }
    debug("Número de páginas de disco acessadas: %d\n", (i*80)/16000); 
    fclose(fin);
}

TregistroDados* iteradorBinarioTexto(TregistroDados *dados, char *fileIn) {
        char buff[80];
        FILE *fin = fopen(fileIn, "rb");
        int i = 0;
        TregistroDados *dados1;

        if(fin == NULL) {
            debug("Falha no processamento do arquivo.");
            exit(0);
        }
        int seek = fseek(fin, 0, SEEK_END);
        //debug("seek: %d\n", seek);
        debug("offset: %d\n", ftell(fin));
        if(ftell(fin) == 0) {
            debug("Registro inexistente.");
            exit(0);
        }//  TODO tratar arquivos vazios */
        while(fread(buff, 80, 1, fin)) {
            dados1 = binarioParaTexto(buff, &dados[i]);
            printRegistro(&dados[i]);
            free(dados->cidade);
            free(dados->nomeEscola);
            i++;
        }
        fclose(fin);         
        debug("Número de páginas de disco acessadas: %d\n", (i*80)/16000); 
        return dados;
}

int main () { 
    TregistroCabecalho *cabecalho;
    TregistroDados dados[10000]; 
  
    char option[4], *file;                
    char *csv = "SCC0503012019trabalho1csv.csv"; 
    char buffer[80], buff[80];
    //csv = "teste.csv";
    char *bin = "arquivoTrab1si.bin";
    int nro;    
    FILE *fbin;
    char *campoDados;
    int size = 0, i = 0;
    FILE* fin;
    fflush(stdout);
    scanf("%[^\n]", option); //TODO: passar o csv para ser lido aqui

    char *tok = strtok(option, " ");
    nro = atoi(tok); //primeiro valor antes de espaco "1 "
    if(nro == 1) {
            cabecalho = malloc(sizeof(TregistroCabecalho));
            tok = strtok(0, " ");
            csv = tok;
            csv = "projeto_si_atualizado.csv";
            debug("tok: %s\n", tok);  
            lerArquivoTextoGravaBinario(csv, cabecalho, dados, bin); // lê do csv para struct
            free(cabecalho);
    }
    else if(nro == 2) { //funcionalidade 2
        tok = strtok(0, " ");
        //debug("tok: %s\n", tok);  
        iteradorBinarioTexto(dados, tok);
    } else if(nro == 3){ //funcionalidade 3 
        tok = strtok(0, " ");
        char *valor = strtok(0, " ");
        buscaCampo(bin, dados, tok, valor);// TODO: testar
    } else if(nro == 4){ //funcionalidade 4 

    }
    return 0;
}