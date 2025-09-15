/*ESTRUTURAS - MACROS - PROTÓTIPOS*/

#ifndef __RAIL_FENCE_H__
#define __RAIL_FENCE_H__

struct rail_fence_t {
    unsigned char **matriz;                  //Matriz que vai conter todos os caracteres
    unsigned char *texto_limpo;              //Texto base livre de espaços e acentuações
    unsigned char *texto_cifrado;            //Texto cifrado
    unsigned int num_linhas;                 //Chave
    unsigned int num_colunas;                //Inicialmente fixo, mas pode mudar se houver muitos caracteres
    unsigned long int num_caracteres;             //Número de caracteres do TEXTO LIMPO
};

#define NUM_COLUNAS 5

//inicializa os campos da rail_fence
void inicializa_rf(struct rail_fence_t *rf);

//O Texto já está sem os espaços e caracteres estranhos porque já foi
//tratado na playfair

//Aloca espaço e monta a matriz da rail_fence
void monta_matriz_rf(struct rail_fence_t *rf, char *texto);

//Preenche a matriz para CIFRAR
void preenche_cifra_rf(struct rail_fence_t *rf);

//Cifra o texto
void cifra_rf(struct rail_fence_t *rf);

//Preenche os campos da rail_fence para DECIFRAR
void preenche_decifra_rf(unsigned int num_linhas, unsigned int num_colunas);

//Decifra o texto
void decifra_rf(struct rail_fence_t *rf);

//Libera rail_fence
void libera_rf(struct rail_fence_t *rf);

#endif