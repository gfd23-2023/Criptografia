#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "playfair.h"
#include "rail_fence.h"

int main()
{
    char *chave;
    char *arquivo;
    struct texto_t *texto;
    struct playfair_t *playfair;
    struct alfabeto_t *alfabeto;
    struct rail_fence_t *rf;

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
    /*--------------------------------------------------------------------------*/

    //Liberações de memória
    free(alfabeto);
    free(arquivo);
    free(chave);
    libera_texto(texto);
    free(texto);
    libera_playfair(playfair);
    libera_rf(rf);
}