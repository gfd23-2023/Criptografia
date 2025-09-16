#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playfair.h"
#include "rail_fence.h"

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
    /*-------------------------------------------------------------------------------------*/

    inicializa_estruturas(&playfair, &texto, &alfabeto, &arquivo_cifrado, &chave);

    //Rail Fence
    rf = malloc(sizeof(struct rail_fence_t));
    if (!rf)
    {
        printf("Erro ao alocar memória para a Rail Fence.\n");
        return -1;
    }
    inicializa_rf(rf);

    printf("Digite a chave para decofidicação: ");
    scanf("%255s", chave);

    //Trata a chave
    le_chave(playfair, alfabeto, chave);
    monta_matriz(playfair, alfabeto);

    //Decifra
    decifra(playfair, "arquivo_cifrado_playfair.txt");

    free(alfabeto);
    free(arquivo_cifrado);
    free(chave);
    libera_texto(texto);
    free(texto);
    libera_playfair(playfair);
    libera_rf(rf);
}