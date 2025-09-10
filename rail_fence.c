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
    //Conta o número de caracteres
    rf->num_caracteres = strlen(texto);

    if (rf->num_caracteres > 1000000)               //se o número de caracteres for maior que 1 milhão
        rf->num_colunas += 2;
    else if (rf->num_caracteres > 5000000)          //se o número de caracteres for maior do que 5 milhões
        rf->num_colunas += 3;
    else if (rf->num_caracteres > 10000000)        //se o número de caracteres for maior do que 10 milhões
        rf->num_colunas += 4; 

}

//Cifra o texto
void cifra_rf(struct rail_fence_t *rf)
{

}

//Preenche os campos da rail_fence para DECIFRAR
void preenche_rf(unsigned int num_linhas, unsigned int num_colunas)
{

}

//Decifra o texto
void decifra_rf(struct rail_fence_t *rf)
{

}

//Libera rail_fence
void libera_rf(struct rail_fence_t *rf)
{

}