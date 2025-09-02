/*CIFRA PLAYFAIR:
 * Baseado em uma matriz 5x5 preenchida de acordo com uma chave.
 * Regras:
 * 	1) As letras da palavra chave não podem se repetir
 * 	2) As letras 'i' e 'j' ficam no mesmo quadrado
 * 	3) Letras do texto original, caso fiquem sem par devem ser separadas por X
 * 	4) Duas letras na mesma coluna devem ser substituídas pela debaixo
 * 	5) Duas letras na mesma linha devem ser substituídas pela que estiver à esquerda
 * 	6) A letra original é cifrada e decifrada pela indexação do par de letras.*/

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
    //Minúsculas
    for (int i = 97, j = 0; j < 25; j++, i++)
        alfabeto->minusculas[j] = i;
}

void inicializa_texto(struct texto_t *texto)
{
    texto->tamanho = 0;
    texto->num_pares = 0;
    texto->texto_base = NULL;
}

void inicializa_playfair(struct playfair_t *playfair)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            playfair->matriz[i][j] = 0;
    
    playfair->chave = NULL;                 //alocar memória depois que tiver a chave
    playfair->chave_recebida = NULL;        //alocar memória depois que tiver a chave
}

//Remove caracteres e símbolos especiais do texto
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
}

void forma_pares(struct texto_t *texto)
{
    //Forma os pares partindo do texto base
    //Se uma letra repetir, coloca um 'x' no meio
    //Se uma letra ficar sozinha, coloca um X como par
    
    //Calcula a quantidade de pares que serão necessários
    texto->num_pares = (texto->tamanho / 2);

    if (texto->tamanho % 2)
        texto->num_pares++;

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
}


void monta_matriz(struct playfair_t *playfair, struct alfabeto_t *alfabeto)
{
    //Monta a matriz que será usada na codificação

    char i = 0;     //linha
    char j = 0;     //coluna
    char igual = 0;
    char k = 0;
    long int letra = 1;
    char usados[26] = {0};

    //Coloca a chave processada na matriz
    for (int k = 0; playfair->chave[k] != '\0'; k++) {
        char c = playfair->chave[k];
        if (c == 'J') c = 'I'; // trata J como I

        int idx = c - 'A';
        if (!usados[idx]) {
            playfair->matriz[i][j] = c;
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
    int aux = 0;
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
        {
            printf("%c ", playfair->matriz[a][b]);
        }

        printf("\n");
    }
    #endif

}

//Pega os pares de letras para fazer as correspondências
void cifra(struct texto_t *texto, struct playfair_t *playfair)
{
    #ifdef DEBUG
    int j = 0; 
    while (texto->texto_base[j] != '\0')
    {
        printf("%c", texto->texto_base[j]);
        j++;
    }
    printf("\n");
    #endif

    texto->tamanho = strlen(texto->texto_base);
    printf("texto->tamanho = %d\n", texto->tamanho);
    //Confere se a quantidade de caracteres é par para formar os pares
    if (texto->tamanho % 2)
    {
        printf("ENTREI AQUI\n");
        texto->texto_base[texto->tamanho] = 'X';
        texto->texto_base[texto->tamanho + 1] = '\0';
        texto->tamanho++;
        
    }

    //Inicializa o campo do texto cifrado
    playfair->texto_cifrado = malloc(texto->tamanho * sizeof(char));

    //Codifica
    printf("tamanho texto atualizado: %d\n", texto->tamanho);
    int teste = 0;
    for (int i = 0; i < (texto->tamanho - 1); i++)
    {
        //PRECISA PROCURAR DIRETO NA MATRIZ - É POR ISSO QUE DÁ ERRO -------
        playfair->texto_cifrado[i] = playfair->matriz[i][i + 1];        //linha i coluna i + 1
        playfair->texto_cifrado[i + 1] = playfair->matriz[i + 1][i];    //linha i + 1 coluna i
        teste = i;
        //------------------------------------------------------------------
    }

    printf("\n\nTESTE + 1 = %d\n", teste + 1);
    #ifdef DEBUG
    for (int i = 0; i < texto->tamanho; i ++)
        printf("%c", playfair->texto_cifrado[i]);
    #endif
}

void decifra(struct playfair_t *playfair)
{
    //Decifra o texto usando as regras da playfair
}

void libera_texto(struct texto_t *texto)
{
    free(texto->texto_base);
}

void libera_playfair(struct playfair_t *playfair)
{
    free(playfair->texto_cifrado);
    free(playfair->chave);
    free(playfair);
}
