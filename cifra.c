#define _POSIX_C_SOURCE 199309L     //para não acusar declaração implícita de clock_gettime

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "tempo.h"
#include "playfair.h"
#include "rail_fence.h"
#include "aes.h"


int main()
{
    char *chave;
    char *arquivo;
    struct texto_t *texto;
    struct playfair_t *playfair;
    struct alfabeto_t *alfabeto;
    struct rail_fence_t *rf;

    //Estrutura para medir o tempo
    struct timespec inicio, fim;
    struct timespec inicio_aes, fim_aes;

    //Inicializações -----------------------------------------------------
    //Playfair
    inicializa_estruturas(&playfair, &texto, &alfabeto, &arquivo, &chave);

    //Rail Fence
    rf = malloc(sizeof(struct rail_fence_t));
    if (!rf)
    {
        printf("Erro ao alocar memória para a Rail Fence.\n");
        return -1;
    }

    inicializa_rf(rf);
    //--------------------------------------------------------------------

    printf("Este código cifra um texto utilizando a Cifra Gi-Playfair-Fence.\n");
    printf("Caminho do arquivo a ser cifrado: ");
    scanf("%255s", arquivo);
    printf("Digite alguma palavra: ");
    scanf("%255s", chave);

    //Playfair
    /*--------------------------------------------------------------------------*/

    //Começa a medir o tempo
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    //Trata a chave
    le_chave(playfair, alfabeto, chave);

    //Trata o texto
    trata_texto(arquivo, texto);

    //Monta a matriz
    monta_matriz(playfair, alfabeto);
    cifra(texto, playfair);
    /*--------------------------------------------------------------------------*/

    //Rail Fence
    /*--------------------------------------------------------------------------*/
    monta_matriz_rf(rf, "arquivo_cifrado_playfair.txt");
    preenche_matriz(rf);
    cifra_rf(rf);

    //Termina de medir o tempo
    clock_gettime(CLOCK_MONOTONIC, &fim);
    /*--------------------------------------------------------------------------*/

    /*AES ----------------------------------------------------------------------*/
    //Gera bytes aleatórios para a chave e para o iv
    unsigned char chave_aes[kEY_SIZE];
    unsigned char iv[IV_SIZE];

    gera_bytes_aleat(chave_aes, sizeof(chave_aes));
    gera_bytes_aleat(iv, sizeof(iv));

    //Começa a marcar o tempo
    clock_gettime(CLOCK_MONOTONIC, &inicio_aes);
    
    cifra_aes(arquivo, "saida_aes.txt", (unsigned char *) chave_aes, iv);

    //Termina de marcar o tempo
    clock_gettime(CLOCK_MONOTONIC, &fim_aes);
    
    //Chave do AES
    printf("Chave do AES: ");
    for (int i = 0; i < 32; i++)
        printf("%02X ", chave_aes[i]);
    printf("\n");

    printf("IV AES: ");
    for (int i = 0; i < 16; i++)
        printf("%02X ", iv[i]);
    printf("\n");
    /*--------------------------------------------------------------------------*/

    //Imprime dados do tempo:
    printf("\n---------------------------------------------\n");
    printf("CIFRA GI-PLAYFAIR-FENCE:\n");
    imprime_tempo(&inicio, &fim);
    printf("---------------------------------------------\n");

    printf("\n---------------------------------------------\n");
    printf("AES:\n");
    imprime_tempo(&inicio_aes, &fim_aes);
    printf("---------------------------------------------\n");

    //Liberações de memória
    free(alfabeto);
    free(arquivo);
    free(chave);
    libera_texto(texto);
    free(texto);
    libera_playfair(playfair);
    libera_rf(rf);
}