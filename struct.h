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
    double nota;
    char data[10]; //TODO FAZER MÁSCARA PARA DATA
    //int tamanho_cidade;
    char cidade[30]; //variável
    //int tamanho_nomEscola;
    char nomeEscola[30];
} TregistroDados;
