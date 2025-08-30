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
    texto = malloc(sizeof(struct texto_t));
    playfair = malloc(sizeof(struct playfair_t));
    if (!texto)
    {
        printf("Erro ao alocar memória para texto.\n");
        return(-1);
    }
    if(!playfair)
    {
        printf("Erro ao alocar memória para playfair.\n");
        return(-1);
    }

    arquivo = malloc(256 * sizeof(char));
    if (!arquivo)
    {
        printf("Erro ao alocar memória para o caminho do arquivo.\n");
        return(-1);
    }
    chave = malloc(256 * sizeof(char));
    if (!chave)
    {
        printf("Erro ao alocar memória para a chave.\n");
        return(-1);
    }

    alfabeto = malloc(sizeof(struct alfabeto_t));
    if (!alfabeto)
    {
        printf("Erro ao alocar memória para o alfabeto.\n");
        return (-1);
    }

    inicializa_texto(texto);
    inicializa_playfair(playfair);
    inicializa_alfabeto(alfabeto);
    //--------------------------------------------------------------------

    printf("Este código cifra um texto utilizando a Cifra Playfair.\n");
    printf("Caminho do arquivo a ser cifrado: ");
    scanf("%255s", arquivo);
    printf("Digite sua chave: ");
    scanf("%255s", chave);

    //Trata a chave
    le_chave(playfair, alfabeto, chave);

    //Trata o texto
    trata_texto(arquivo, texto);

    //Monta a matriz
    monta_matriz(playfair, alfabeto);

    //Liberações de memória
    free(alfabeto);
    free(arquivo);
    free(chave);
    libera_texto(texto);
    free(texto);
    libera_playfair(playfair);
}