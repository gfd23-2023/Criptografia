/*CIFRA PLAYFAIR:
 * Baseado em uma matriz 5x5 preenchida de acordo com uma chave.
 * Regras:
 * 	1) As letras da palavra chave não podem se repetir
 * 	2) As letras 'i' e 'j' ficam no mesmo quadrado
 * 	3) Letras do texto original, caso fiquem sem par devem ser separadas por X
 * 	4) Duas letras na mesma coluna devem ser substituídas pela debaixo
 * 	5) Duas letras na mesma linha devem ser substituídas pela que estiver à direta
 * 	6) A letra original é cifrada e decifrada pela indexação do par de letras.*/

/*O QUE FOI IMPLEMENTADO:
 *1) As letras 'i' e 'j' são tratadas como a mesma;
 *2) Completa o texto com X caso o número de caracteres seja ímpar;
 *3) Rotação para baixo;
 *4) Rotação para a direita;
 *4) Letra original cifrada pela indexação dos pares na matriz.*/

 /*OBSERVAÇÃO: Quando caem duas letras repetidas, o código simplesmente pega a da direita duas vezes.*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>       //tratamento do texto
#include"playfair.h"


void inicializa_alfabeto(struct alfabeto_t *alfabeto)
{
    //Coloca todas as letras do alfabeto em um vetor

    //Maiúsculas
    int idx = 0;
    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (c == 'J')
            continue;       //trata o J como I
        
        alfabeto->maiusculas[idx++] = c;
    }

    return;
}

void inicializa_texto(struct texto_t *texto)
{
    texto->tamanho = 0;
    texto->num_pares = 0;
    texto->texto_base = NULL;

    return;
}

void inicializa_playfair(struct playfair_t *playfair)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            playfair->matriz[i][j] = 0;
    
    playfair->chave = NULL;                 //alocar memória depois que tiver a chave
    playfair->chave_recebida = NULL;        //alocar memória depois que tiver a chave
    playfair->linha = 0;
    playfair->coluna = 0;

    return;
}

//Passa os ponteiros originais
void inicializa_estruturas(struct playfair_t **playfair, struct texto_t **texto, struct alfabeto_t **alfabeto, char **arquivo, char **chave)
{
    *texto = malloc(sizeof(struct texto_t));
    *playfair = malloc(sizeof(struct playfair_t));
    if (!*texto)
    {
        printf("Erro ao alocar memória para texto.\n");
        return;
    }
    if(!*playfair)
    {
        printf("Erro ao alocar memória para playfair.\n");
        return;
    }

    *arquivo = malloc(256 * sizeof(char));
    if (!*arquivo)
    {
        printf("Erro ao alocar memória para o caminho do arquivo.\n");
        return;
    }
    *chave = malloc(256 * sizeof(char));
    if (!*chave)
    {
        printf("Erro ao alocar memória para a chave.\n");
        return;
    }

    *alfabeto = malloc(sizeof(struct alfabeto_t));
    if (!*alfabeto)
    {
        printf("Erro ao alocar memória para o alfabeto.\n");
        return;
    }

    inicializa_texto(*texto);
    inicializa_playfair(*playfair);
    inicializa_alfabeto(*alfabeto);

    return;
}

//Remove caracteres e símbolos especiais do texto -- Talvez não precise
void limpa_texto(struct texto_t *texto)
{
    
}

void trata_texto(char *arquivo, struct texto_t *texto)
{
    //Remove os espaços
    //Conta a quantidade de carateres do arquivo

    FILE *arquivo_original;
    char letra;

    arquivo_original = fopen(arquivo, "r");
    if (!arquivo_original) 
        printf("Falha ao abrir arquivo.\n\n");
    
    rewind(arquivo_original);

    //Conta o número de caracteres
    int i = 0;
    while ((letra = fgetc(arquivo_original)) != EOF)
    {
        texto->tamanho++;
        i++;
    }

    //Aloca memória para texto_base com base no número de carcteres
    texto->texto_base = malloc(texto->tamanho * sizeof(char));

    //Remove os espaços
    rewind(arquivo_original);
    i = 0;
    int j = 0;
    while ((letra = fgetc(arquivo_original)) != EOF)
    {
        if ((letra != ' ') && isalnum(letra))       //se não for um espaço nem um caractere especial
        {
            texto->texto_base[j] = toupper(letra);  //guarda a letra
            j++;
        }
        i++;                                        //avança para o próximo campo do vetor
    }

    //A posição do último j é o EOF
    texto->texto_base[j] = '\0';

    fclose(arquivo_original);
    printf("Número de caracteres com espaços: %d\n", texto->tamanho);

    return;
}

void le_chave(struct playfair_t *playfair, struct alfabeto_t *alfabeto, char *chave)
{
    //Opera a chave recebida do teclado para que não repita letras

    //Transforma todas as letras em maiusculas
    playfair->chave_recebida = chave;
    playfair->tamanho_chave = strlen(chave);

    for (int i = 0; i < playfair->tamanho_chave; i++)
        playfair->chave_recebida[i] = toupper(chave[i]);

    playfair->chave = malloc(26 * sizeof(char));
    if (!playfair->chave)
    {
        printf("Não foi possível alocar memória para a chave.\n");
        return;
    }

    char igual = 0;
    char atual;
    
    //Remove letras repetidas da chave
    playfair->chave[0] = playfair->chave_recebida[0];
    playfair->chave[1] = '\0';

    int i = 0;
    while (playfair->chave_recebida[i] != '\0')
    {
        atual = playfair->chave_recebida[i];

        for (int j = 0; j < strlen(playfair->chave); j++)
        {
            if (playfair->chave[j] == atual)
                igual = 1;
        }

        if (!igual)
            playfair->chave[strlen(playfair->chave)] = playfair->chave_recebida[i];
        
        playfair->chave[strlen(playfair->chave) + 1] = '\0';

        igual = 0;          //Reseta o estado do controlador
        i++;                //avança para a próxima letra
    }

    #ifdef DEBUG
    printf("Tamanho da chave sem repetir: %ld\n", strlen(playfair->chave));
    for (int i = 0; i < strlen(playfair->chave); i++)
        printf("%c", playfair->chave[i]);
    printf("\n");
    #endif

    return;
}


void monta_matriz(struct playfair_t *playfair, struct alfabeto_t *alfabeto)
{
    //Monta a matriz que será usada na codificação

    char i = 0;     //linha
    char j = 0;     //coluna
    char usados[26] = {0};

    //Coloca a chave processada na matriz
    for (int k = 0; playfair->chave[k] != '\0'; k++) {
        char c = playfair->chave[k];
        if (c == 'J') c = 'I'; // trata J como I

        int idx = c - 'A';
        if (!usados[idx]) {
            playfair->matriz[i][j] = (char) c;
            usados[idx] = 1;

            j++;
            if (j == NUM_COLUNAS) {
                j = 0;
                i++;
            }
        }
    }

    if (j == NUM_COLUNAS)
        j = 0;

    //Depois que colocou a chave, coloca o restante do alfabeto
    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (c == 'J')
            continue;       //trata os dois como a mesma letra

        int indice = c - 'A';

        if (!usados[indice])
        {
            playfair->matriz[i][j] = c;
            usados[indice] = 1;

            j++;
            if (j == NUM_COLUNAS)
            {
                j = 0;          //reseta a coluna
                i++;            //avança para a próxima linha
            }
        }
    }


    #ifdef DEBUG
    //Imprime a matriz
    for (int a = 0; a < 5; a++)
    {
        for (int b = 0; b < 5; b++)
            printf("%c ", playfair->matriz[a][b]);

        printf("\n");
    }
    #endif

    return;

}

void procura_na_matriz(struct playfair_t *playfair, char letra)
{
   for (int i = 0; i < NUM_LINHAS; i++)
   {
        for (int j = 0; j < NUM_COLUNAS; j++)
        {
            if (playfair->matriz[i][j] == letra)
            {
                playfair->linha = i;
                playfair->coluna = j;
                return;
            }
        }
    }
}

int verifica_linha(struct playfair_t *playfair, char letra1, char letra2)
{
    char linha1 = 0;

    procura_na_matriz(playfair, letra1);
    linha1 = playfair->linha;

    procura_na_matriz(playfair, letra2);

    if (linha1 == playfair->linha)
        return 1;
    
    return 0;
}

int verifica_coluna(struct playfair_t *playfair, char letra1, char letra2)
{
    char coluna1 = 0;

    procura_na_matriz(playfair, letra1);
    coluna1 = playfair->coluna;

    procura_na_matriz(playfair, letra2);

    if (coluna1 == playfair->coluna)
        return 1;
    
        return 0;
}

//Pega os pares de letras para fazer as correspondências
void cifra(struct texto_t *texto, struct playfair_t *playfair)
{
    texto->tamanho = strlen(texto->texto_base);
    printf("Tamanho inicial do texto: %d\n", texto->tamanho);
    //Confere se a quantidade de caracteres é par para formar os pares
    if (texto->tamanho % 2)
    {
        texto->texto_base[texto->tamanho] = 'X';
        texto->texto_base[texto->tamanho + 1] = '\0';
        texto->tamanho++;
        
    }

    //Inicializa o campo do texto cifrado
    playfair->texto_cifrado = malloc((texto->tamanho + 1)* sizeof(char));

    //Codifica
    printf("Tamanho do texto atualizado: %d\n", texto->tamanho);
    #ifdef DEBUG
    int j = 0; 
    while (texto->texto_base[j] != '\0')
    {
        printf("%c", texto->texto_base[j]);
        j++;
    }
    printf("\n");
    #endif

    int fim;
    for (int i = 0; i < (texto->tamanho - 1); i+=2)
    {
        procura_na_matriz(playfair, texto->texto_base[i]);        //acha a linha e a coluna
        char linha1 = playfair->linha;
        char coluna1 = playfair->coluna;
        procura_na_matriz(playfair, texto->texto_base[i + 1]);
        char linha2 = playfair->linha;
        char coluna2 = playfair->coluna;

        //verifica se as letras estão na mesma linha
        if (verifica_linha(playfair, texto->texto_base[i], texto->texto_base[i +1]))
        {
            playfair->texto_cifrado[i] = (char) playfair->matriz[linha1][(coluna1 + 1) % NUM_COLUNAS];      //rotaciona à direita
            playfair->texto_cifrado[i + 1] = (char) playfair->matriz[linha2][(coluna2 + 1) % NUM_COLUNAS];  //rotaciona à direita
        }    
        else if (verifica_coluna(playfair, texto->texto_base[i], texto->texto_base[i + 1]))          //Verifica se estão na mesma coluna
        {
            playfair->texto_cifrado[i] = (char) playfair->matriz[(linha1 + 1) % NUM_LINHAS][coluna1];     //rotaciona para baixo
            playfair->texto_cifrado[i + 1] = (char) playfair->matriz[(linha2 + 1) % NUM_LINHAS][coluna2]; //rotaciona para baixo
        }
        else
        {
            playfair->texto_cifrado[i] = (char) playfair->matriz[linha1][coluna2];
            playfair->texto_cifrado[i + 1] = (char) playfair->matriz[linha2][coluna1];
        }

        fim = i;
    }

    fim += 2;

    //Finaliza com '\0'
    playfair->texto_cifrado[fim] = '\0';

    //Grava o texto cifrado em um arquivo------------------------------------------------
    FILE *arquivo_cifrado;

    arquivo_cifrado = fopen("arquivo_cifrado.txt", "w");
    if (!arquivo_cifrado)
    {
        printf("Não foi possível abrir o arquivo para guardar o texto cifrado.\n");
        return;
    }

    for (int i = 0; i < strlen(playfair->texto_cifrado) + 1; i++)           //o + 1 é para incluir o \0
        fprintf(arquivo_cifrado, "%c", (char) playfair->texto_cifrado[i]);

    //Salva e fecha
    fflush(arquivo_cifrado);
    fclose(arquivo_cifrado);
    //-----------------------------------------------------------------------------------

    #ifdef DEBUG
    printf("\nTEXTO CIFRADO:\n");
    int num_letras = 0;
    for (int i = 0; i < texto->tamanho; i ++)
    {
        printf("%c", playfair->texto_cifrado[i]);
        num_letras = i;
    }
    printf("\n");

    
    printf("Número de caracteres do texto cifrado: %ld\n", strlen(playfair->texto_cifrado));
    #endif

    return;
}

void decifra(struct playfair_t *playfair, char *arquivo_cifrado)
{
    //Decifra o texto usando as regras da playfair
    int fim = 0;
    int tamanho = 0;

    //Pega o texto cifrado do arquivo ------------------------------------
    FILE *arquivo = fopen(arquivo_cifrado, "r");
    if (!arquivo)
    {
        printf("Não foi possível abrir o arquivo cifrado.\n");
        return;
    }
    
    rewind(arquivo);

    char letra = 0;
    while ((letra = fgetc(arquivo)) != EOF)
        tamanho++;

    //Aloca memória para o texto cifrado --------------------------------
    playfair->texto_cifrado = malloc(tamanho * sizeof(char));
    if (!playfair->texto_cifrado)
    {
        printf("Não foi possível alocar memória para o texto cifrado.\n");
        return;
    }
    //-------------------------------------------------------------------
    //Aloca memória para o texto decifrado -------------------------------
    playfair->texto_decifrado = malloc((tamanho) * sizeof(char));
    if (!playfair->texto_decifrado)
    {
        printf("Não foi possível alocar memória para o texto decifrado.\n");
        return;
    }
    //--------------------------------------------------------------------

    rewind(arquivo);
    int i = 0;
    while ((letra = fgetc(arquivo)) != EOF)
    {
        playfair->texto_cifrado[i] = letra;
        i++;
    }
    //--------------------------------------------------------------------

    //Decifra ------------------------------------------------------------
    for (int i = 0; i < tamanho - 2; i+=2)      //Tira o '\0' e o último caractere
    {
        procura_na_matriz(playfair, playfair->texto_cifrado[i]);
        char linha1 = playfair->linha;
        char coluna1 = playfair->coluna;
        procura_na_matriz(playfair, playfair->texto_cifrado[i + 1]);
        char linha2 = playfair->linha;
        char coluna2 = playfair->coluna;

        //Verifica se as letras obtidas estão na mesma linha ou coluna
        if (verifica_linha(playfair, playfair->texto_cifrado[i], playfair->texto_cifrado[i + 1]))
        {
            playfair->texto_decifrado[i] = (char) playfair->matriz[linha1][(coluna1 + NUM_COLUNAS - 1) % NUM_COLUNAS];
            playfair->texto_decifrado[i + 1] = (char) playfair->matriz[linha2][(coluna2 + NUM_COLUNAS - 1) % NUM_COLUNAS];
        }
        else if (verifica_coluna(playfair, playfair->texto_cifrado[i], playfair->texto_cifrado[i + 1]))
        {
            playfair->texto_decifrado[i] = (char) playfair->matriz[(linha1 + NUM_LINHAS - 1) % NUM_LINHAS][coluna1];
            playfair->texto_decifrado[i + 1] = (char) playfair->matriz[(linha2 + NUM_LINHAS - 1) % NUM_LINHAS][coluna2];
        }
        else
        {
            playfair->texto_decifrado[i] = (char) playfair->matriz[linha1][coluna2];
            playfair->texto_decifrado[i + 1] = (char) playfair->matriz[linha2][coluna1];
        }

        fim = i;
    }
    fim += 2;
    //--------------------------------------------------------------------

    //Coloca o texto decifrado em um arquivo -----------------------------
    FILE *arquivo_decifrado = fopen("arquivo_decifrado.txt", "w");
    if (!arquivo_decifrado)
    {
        printf("Não foi possível abrir o arquivo para guardar o texto decifrado.\n");
        return;
    }

    for (int i = 0; i < fim; i++)
        fprintf(arquivo_decifrado, "%c", playfair->texto_decifrado[i]);

    fflush(arquivo_decifrado);
    fclose(arquivo_decifrado);
    //--------------------------------------------------------------------

    #ifdef DEBUG
    printf("\n\nTEXTO DECIFRADO:\n");
    for (int i = 0; i < fim; i++)
        printf("%c", playfair->texto_decifrado[i]);
    printf("\n");
    #endif

    return;
}

void libera_texto(struct texto_t *texto)
{
    free(texto->texto_base);
}

void libera_playfair(struct playfair_t *playfair)
{
    free(playfair->texto_decifrado);
    free(playfair->texto_cifrado);
    free(playfair->chave);
    free(playfair);
}
