#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "playfair.h"

int main()
{
    char *chave;
    char *arquivo;
    struct texto_t *texto;
    struct playfair_t *playfair;
    struct alfabeto_t *alfabeto;

    //Inicializações -----------------------------------------------------
    inicializa_estruturas(&playfair, &texto, &alfabeto, &arquivo, &chave);
    //--------------------------------------------------------------------

    printf("Este código cifra um texto utilizando a Cifra Playfair.\n");
    printf("Caminho do arquivo a ser cifrado: ");
    scanf("%255s", arquivo);
    printf("Digite alguma palavra: ");
    scanf("%255s", chave);

    //Trata a chave
    le_chave(playfair, alfabeto, chave);

    //Trata o texto
    trata_texto(arquivo, texto);

    //Monta a matriz
    monta_matriz(playfair, alfabeto);
    cifra(texto, playfair);

    //Liberações de memória
    free(alfabeto);
    free(arquivo);
    free(chave);
    libera_texto(texto);
    free(texto);
    libera_playfair(playfair);
}