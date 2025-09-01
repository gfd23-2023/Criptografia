/*ESTRUTURAS - MACROS - PROTÓTIPOS*/

#ifndef __PLAYFAIR_H__
#define __PLAYFAIR_H__

struct texto_t{
    unsigned int tamanho;           //número de caracteres do texto com espaços
    unsigned int num_pares;         //quantidade de parzinhos formados
    char *texto_base;               //texto base com espaços e letras de separação/complemento (x)
    char *pares_originais;          //pares de indexação para codificar o texto
};

struct playfair_t {
    char matriz[5][5];              //matriz que será preenchida
    char *chave;                    //chave que preenche a matriz (não repete letras)
    char *chave_recebida;           //registro da chave passada pelo usuário
    unsigned int tamanho_chave;     //tamanho da chave para facilitar as contas
};

struct alfabeto_t {
    char maiusculas[25];            //contém todas as letras do alfabeto para facilitar a vida (0 ~ 25)
    char minusculas[25];
};

#define TAM_ALFABETO 26
#define NUM_COLUNAS 5
#define NUM_LINHAS 5

void inicializa_alfabeto(struct alfabeto_t *alfabeto);

void inicializa_texto(struct texto_t *texto);

void inicializa_playfair(struct playfair_t *playfair);

void trata_texto(char *arquivo, struct texto_t *texto);

void forma_pares(struct texto_t *texto);

void le_chave(struct playfair_t *playfair, struct alfabeto_t *alfabeto, char *chave);

void limpa_alfabeto(struct alfabeto_t *alfabeto, struct playfair_t *playfair);

void monta_matriz(struct playfair_t *playfair, struct alfabeto_t *alfabeto);

void cifra(struct texto_t *texto, struct playfair_t *playfair);

void decifra(struct playfair_t *playfair);

void libera_texto(struct texto_t *texto);

void libera_playfair(struct playfair_t *playfair);

void inicializa_estruturas(struct playfair_t p, struct texto_t t, struct alfabeto_t a);

#endif