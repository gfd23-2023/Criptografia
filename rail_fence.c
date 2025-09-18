/*IMPLEMENTAÇÃO CA CIFRA RAIL FENCE
 *Pontos importantes:
 * - O texto vai ficar inteiro em uma única matriz. Se a quantidade de caracteres
 * dividida por 5 (número de colunas) for maior do que 500.000, deve-se aumentar o número de colunas em 2.
 * - Para cifrar uma linha, deve-se fixar uma coluna e percorrer todas as linhas da matriz.
 * - Para decifrar uma linha é preciso saber a quantidade de linhas da matriz e pular esse mesmo número
 * de caracteres para encontrar a pŕoxima letra do texto cifrado.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "rail_fence.h"

//inicializa os campos da rail_fence
void inicializa_rf(struct rail_fence_t *rf)
{
    rf->matriz = NULL;
    rf->texto_limpo = NULL;
    rf->texto_cifrado = NULL;
    rf->num_linhas = 0;
    rf->num_colunas = NUM_COLUNAS;           //Valor inicial que pode mudar se o número de caracteres for muito grande
    rf->num_caracteres = 0;                  //Caracteres do TEXTO LIMPO

}

//O texto já está sem espaços e caracteres estranhos, porque ele pega o texto da playfair

//Aloca espaço e monta a matriz da rail_fence
void monta_matriz_rf(struct rail_fence_t *rf, char *texto)
{
    FILE *arquivo = fopen(texto, "r");
    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo cifrado pela cifra Playfair\n.");
        return;
    }

    //Conta o número de caracteres
    int c;
    rf->num_caracteres = 0;
    while (((c = fgetc(arquivo)) != EOF) && (c != '\0'))
        rf->num_caracteres++;

    //Volta para o início
    rewind(arquivo);

    //Aloca espaço para o vetor com o texto recebido
    rf->texto_limpo = malloc((rf->num_caracteres + 1) * sizeof(char));
    if (!rf->texto_limpo)
    {
        printf("Erro ao alocar memória para o texto base (Rail Fence).\n");
        return;
    }

    //Copia o texto recebido para dentro do vetor
    int letra;
    int i = 0;
    while ((letra = fgetc(arquivo)) !=  EOF)
    {
        rf->texto_limpo[i] = letra;
        i++;
    }
    //printf("i = %d\n", i);
    //rf->texto_limpo[i] = '\0';

    #ifdef DEBUG
    printf("\nNúmero de caracteres do texto (Rail Fence) = %ld\n", rf->num_caracteres);
    #endif

    //Define a quantidade de colunas
    if (rf->num_caracteres > 1000000)               //se o número de caracteres for maior que 1 milhão
        rf->num_colunas += 2;
    else if (rf->num_caracteres > 5000000)          //se o número de caracteres for maior do que 5 milhões
        rf->num_colunas += 3;
    else if (rf->num_caracteres > 10000000)        //se o número de caracteres for maior do que 10 milhões
        rf->num_colunas += 4;
    
    #ifdef DEBUG
    printf("Número de colunas (Rail Fence) = %ld\n", rf->num_colunas);
    #endif

    //Descobre a quantidade de linhas
    rf->num_linhas = rf->num_caracteres / rf->num_colunas;

    //Adicionar uma linha a mais caso haja resto
    if (rf->num_caracteres % rf->num_colunas)
        rf->num_linhas++;

    #ifdef DEBUG
    printf("Número de linhas (Rail Fence) = %ld\n", rf->num_linhas);
    #endif

    //Aloca espaço para a matriz
    rf->matriz = malloc(rf->num_linhas * sizeof(unsigned char*));           //vetor de ponteiros
    for (long int i = 0; i < rf->num_linhas; i++)
        rf->matriz[i] = malloc(rf->num_colunas * sizeof(unsigned char));


    #ifdef DEBUG
    for (long int i = 0; i < rf->num_caracteres; i++)
        printf("%c", rf->texto_limpo[i]);
    printf("\n");
    #endif

    fclose(arquivo);
    return;
}

void preenche_matriz(struct rail_fence_t *rf)
{
    //Preenche a matriz (Sem o '\0')
    unsigned long int k = 0;
    for (long int i = 0; i < rf->num_linhas; i++)
    {
        for (long int j = 0; j < rf->num_colunas; j++)
        {
            if (rf->texto_limpo[k] != '\0')
            {
                rf->matriz[i][j] = rf->texto_limpo[k];
                k++;
            }

            //Caso sobrem campos vazios na matriz
            if (((i * rf->num_colunas) + j) >= rf->num_caracteres)
                rf->matriz[i][j] = 'A';
        }
    }

    #ifdef DEBUG
    //Imprime a matriz
    for (long int i = 0; i < rf->num_linhas; i++)
    {
        for (long int j = 0; j < rf->num_colunas; j++)
            printf("%c ", rf->matriz[i][j]);
        printf("\n");
    }
        
    printf("\n");
    #endif
}

//Cifra o texto
void cifra_rf(struct rail_fence_t *rf)
{
    //Aloca espaço para o texto cifrado - não tem espaço para o \0
    rf->texto_cifrado = malloc((rf->num_colunas * rf->num_linhas) * sizeof(char));
    if (!rf->texto_cifrado)
    {
        printf("Não foi possível alocar memória para o texto cifrado (Rail Fence).\n");
        return;
    }

    //Arquivo final
    FILE *arquivo;

    arquivo = fopen("arquivo_cifrado.txt", "w");
    if (!arquivo)
    {
        printf("Erro ao abrir arquivo para o texto cifrado final.\n");
        return;
    }

    //Transforma as colunas em linhas
    long int k = 0;
    for (long int i = 0; i < rf->num_colunas; i++)
    {
        for (long int j = 0; j < rf->num_linhas; j++)
        {
            fprintf(arquivo, "%c", (char) rf->matriz[j][i]);
            rf->texto_cifrado[k] = rf->matriz[j][i];
            k++;

            #ifdef DEBUG
            printf("k = %ld\n", k);
            #endif
        }
    }

    #ifdef DEBUG
    printf("Conteúdo de rf->texto_cifrado:\n");
    for (long int i = 0; i < rf->num_caracteres; i++)
        printf("%c", rf->texto_cifrado[i]);
    printf("\n");
    #endif

    printf("Chave: \nNúmero de Linhas = %ld\nNúmero de Colunas = %ld\n", rf->num_linhas, rf->num_colunas);

    fflush(arquivo);
    fclose(arquivo);
}

void monta_matriz_decifra_rf(struct rail_fence_t *rf, char *texto, long int num_linhas, int num_colunas)
{

    rf->num_linhas = num_colunas;
    rf->num_colunas = num_linhas;

    FILE *arquivo = fopen(texto, "r");
    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo cifrado pela cifra Playfair\n.");
        return;
    }

    //Conta o número de caracteres
    long int c;
    rf->num_caracteres = 0;
    while (((c = fgetc(arquivo)) != EOF) && (c != '\0'))
        rf->num_caracteres++;

    //Volta para o início
    rewind(arquivo);

    //Aloca espaço para o vetor com o texto recebido
    rf->texto_cifrado = malloc((rf->num_caracteres + 1) * sizeof(char));
    if (!rf->texto_cifrado)
    {
        printf("Erro ao alocar memória para o texto base (Rail Fence).\n");
        return;
    }

    //Copia o texto recebido para dentro do vetor
    int letra;
    int i = 0;
    while ((letra = fgetc(arquivo)) !=  EOF)
    {
        rf->texto_cifrado[i] = letra;
        i++;
    }

    #ifdef DEBUG
    printf("\nNúmero de caracteres do texto (Rail Fence) = %ld\n", rf->num_caracteres);
    #endif

    //Aloca espaço para a matriz
    rf->matriz = malloc(rf->num_linhas * sizeof(unsigned char*));           //vetor de ponteiros
    for (long int i = 0; i < rf->num_linhas; i++)
        rf->matriz[i] = malloc(rf->num_colunas * sizeof(unsigned char));


    #ifdef DEBUG
    for (long int i = 0; i < rf->num_caracteres; i++)
        printf("%c", rf->texto_cifrado[i]);
    printf("\n");
    #endif
}

void preenche_matriz_decifra_rf(struct rail_fence_t *rf)
{
    //Preenche a matriz (Sem o '\0')
    unsigned long int k = 0;
    for (long int i = 0; i < rf->num_linhas; i++)
    {
        for (long int j = 0; j < rf->num_colunas; j++)
        {
            if (rf->texto_cifrado[k] != '\0')
            {
                rf->matriz[i][j] = rf->texto_cifrado[k];
                k++;
            }

            //Caso sobrem campos vazios na matriz
            if (((i * rf->num_colunas) + j) >= rf->num_caracteres)
                rf->matriz[i][j] = 'A';
        }
    }

    #ifdef DEBUG
    printf("======= Dentro da preenche_matriz_decifra_rf =======\n");
    //Imprime a matriz
    for (long int i = 0; i < rf->num_linhas; i++)
    {
        for (int j = 0; j < rf->num_colunas; j++)
            printf("%c ", rf->matriz[i][j]);
        printf("\n");
    }
        
    printf("\n");
    #endif
}

//Decifra o texto
void decifra_rf(struct rail_fence_t *rf, char *arquivo)
{
    FILE *arq_cifrado;

    arq_cifrado = fopen(arquivo, "r");
    if (!arq_cifrado)
    {
        printf("Não foi possível abrir o arquivo cifrado pela Rail Fence para decifrar.\n");
        return;
    }

    //Arquivo final
    FILE *arq_decifrado;

    arq_decifrado = fopen("arquivo_decifrado_rf.txt", "w");
    if (!arq_decifrado)
    {
        printf("Erro ao abrir arq_decifrado_rf.txt\n");
        return;
    }

    
    //Fixar a coluna e percorrer todas as linhas
    for (long int i = 0; i < rf->num_colunas; i++)
        for (long int j = 0; j < rf->num_linhas; j++)
            fprintf(arq_decifrado, "%c", rf->matriz[j][i]);

    #ifdef DEBUG
    printf("========== Dentro da decifra_rf ==========\n");
    for (long int i = 0; i < rf->num_linhas; i++)
    {
        for (long int j = 0; j < rf->num_colunas; j++)
            printf("%c ", rf->matriz[i][j]);
        printf("\n");
    }
    #endif

    fflush(arq_decifrado);
    fclose(arq_decifrado);
    
}

//Libera rail_fence
void libera_rf(struct rail_fence_t *rf)
{
    //Libera a matriz
    for (int i = 0; i < rf->num_linhas; i++)
        free(rf->matriz[i]);                        //dentro da matriz tem char, por isso não é rf->matriz[i][j]

    free(rf->matriz);
    free(rf->texto_limpo);
    free(rf->texto_cifrado);

    free(rf);
}