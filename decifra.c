#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playfair.h"

int main()
{
    char *chave;
    char *arquivo_cifrado;
    struct texto_t *texto;
    struct alfabeto_t *alfabeto;
    struct playfair_t *playfair;

    inicializa_estruturas(&playfair, &texto, &alfabeto, &arquivo_cifrado, &chave);

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
}