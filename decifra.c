#define _POSIX_C_SOURCE 199309L     //para não acusar declaração implícita de clock_gettime

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tempo.h"
#include "playfair.h"
#include "rail_fence.h"
#include "aes.h"

int main()
{
    /*Playfair ----------------------------------------------------------------------------*/
    char *chave;
    char *arquivo_cifrado;
    struct texto_t *texto;
    struct alfabeto_t *alfabeto;
    struct playfair_t *playfair;
    /*-------------------------------------------------------------------------------------*/

    /*Rail Fence --------------------------------------------------------------------------*/
    struct rail_fence_t *rf;
    long int linhas, colunas;
    /*-------------------------------------------------------------------------------------*/

    /*Tempo*/
    struct timespec inicio, fim;
    struct timespec inicio_aes, fim_aes;

    inicializa_estruturas(&playfair, &texto, &alfabeto, &arquivo_cifrado, &chave);

    //Rail Fence
    rf = malloc(sizeof(struct rail_fence_t));
    if (!rf)
    {
        printf("Erro ao alocar memória para a Rail Fence.\n");
        return -1;
    }
    
    /*Leitura das Chaves*/
    printf("Digite a quantidade de linhas da matriz: ");
    scanf("%ld", &linhas);
    printf("Digite a quantidade de colunas da matriz: ");
    scanf("%ld", &colunas);
    printf("Digite a palavra chave para decofidicação: ");
    scanf("%255s", chave);

    /*Rail Fence -------------------------------------------------------------------------*/
    inicializa_rf(rf);

    //Começa a medir o tempo
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    monta_matriz_decifra_rf(rf, "arquivo_cifrado.txt", linhas, colunas);
    preenche_matriz_decifra_rf(rf);

    decifra_rf(rf, "arquivo_cifrado.txt");
    /*------------------------------------------------------------------------------------*/

    /*Playfair ---------------------------------------------------------------------------*/
    //Trata a chave
    le_chave(playfair, alfabeto, chave);
    monta_matriz(playfair, alfabeto);

    //Decifra
    decifra(playfair, "arquivo_decifrado_rf.txt");

    //Termina de medir o tempo
    clock_gettime(CLOCK_MONOTONIC, &fim);
    /*------------------------------------------------------------------------------------*/

    /*AES --------------------------------------------------------------------------------*/
    unsigned char chave_aes[kEY_SIZE];
    unsigned char iv[IV_SIZE];

    //Transforma de hexadecimal para binário - para ficar no formato de decifra()
    printf("Digite a chave AES (32 bytes) em hexadecimal, separados por espaço: ");
    for (int i = 0; i < 32; i++)
    {
        unsigned int byte;  // scanf precisa de int para %x
        if (scanf("%x", &byte) != 1)
        {
            fprintf(stderr, "Erro ao ler byte %d da chave\n", i);
            exit(1);
        }
        chave_aes[i] = (unsigned char)byte;
    }

    //Transforma de hexadecimal para binário - para ficar no formato de decifra()
    printf("Digite o IV AES (16 bytes) em hexadecimal, separados por espaço: ");
    for (int i = 0; i < 16; i++)
    {
        unsigned int byte;
        if (scanf("%x", &byte) != 1)
        {
            fprintf(stderr, "Erro ao ler byte %d do IV\n", i);
            exit(1);
        }
        iv[i] = (unsigned char)byte;
    }

    clock_gettime(CLOCK_MONOTONIC, &inicio_aes);        //começa a marcar o tempo
    decifra_aes("saida_aes.txt", "arquivo_decifrado_aes.txt", chave_aes, iv);
    clock_gettime(CLOCK_MONOTONIC, &fim_aes);           //termina de marcar o tempo
    /*------------------------------------------------------------------------------------*/

    //Imprime os dados do tempo
    printf("---------------------------------------------\n");
    printf("DECIFRA GI-PLAYFAIR-FENCE:\n");
    imprime_tempo(&inicio, &fim);
    printf("---------------------------------------------\n");

    printf("\n---------------------------------------------\n");
    printf("AES:\n");
    imprime_tempo(&inicio_aes, &fim_aes);
    printf("---------------------------------------------\n");

    free(alfabeto);
    free(arquivo_cifrado);
    free(chave);
    libera_texto(texto);
    free(texto);
    libera_playfair(playfair);
    libera_rf(rf);
}