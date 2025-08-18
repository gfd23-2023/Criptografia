/*CIFRA PLAYFAIR:
 * Baseado em uma matriz 5x5 preenchida de acordo com uma chave.
 * Regras:
 * 	1) As letras da palavra chave não podem se repetir
 * 	2) As letras 'i' e 'j' ficam no mesmo quadrado
 * 	3) Letras do texto original, caso fiquem sem par devem ser separadas por X
 * 	4) Duas letras na mesma coluna devem ser substituídas pela debaixo
 * 	5) Duas letras na mesma linha devem ser substituídas pela que estiver à esquerda
 * 	6) A letra original é cifrada e decifrada pela indexação do par de letras.*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct texto_t{
    unsigned int tamanho;           //número de caracteres do texto
    unsigned int num_pares;         //quantidade de parzinhos formados
    char *texto_base;               //texto base com espaços e letras de separação/complemento (x)
};

struct playfair_t {
    unsigned int matriz[5][5];      //matriz que será preenchida
    char *chave;                    //chave que preenche a matriz (não repete letras)
    char *chave_recebida;           //registro da chave passada pelo usuário
};

void trata_texto(char *arquivo, struct texto_t *texto)
{
    //Remove os espaços
    //Conta a quantidade de carateres do arquivo

    FILE *arquivo_original;
    char linha[256];

    arquivo_original = fopen(arquivo, "r");
    if (!arquivo_original) 
        printf("Falha ao abrir arquivo.\n\n");
    
    rewind(arquivo_original);

    //Remove os espaços
    while (fgets((linha), sizeof(linha), arquivo_original))
    {
        if (linha[i] != ' ')
            texto->texto_base[i] = 
    }
}

void forma_pares(struct texto_t texto)
{
    //Forma os pares
    //Se uma letra repetir, coloca um 'x' no meio
    //Se uma letra ficar sozinha, coloca um X como par 
}

void le_chave(struct playfair_t playfair)
{
    //Lê a chave do teclado e opera para que não repita letras 
}

void cifra(struct texto_t texto, struct playfair_t playfair)
{
    //Cifra o texto com base nas regras da playfair
}

void decifra(struct playfair_t playfair)
{
    //Decifra o texto usando as regras da playfair
}

int main()
{
    char *arquivo;
    struct texto_t *texto;

    //Inicializações
    texto = malloc(sizeof(texto));

    printf("Este código cifra um texto utilizando a Cifra Playfair.\n\n");
    printf("Arquivo a ser cifrado: %s\n", arquivo);

    //Trata o texto
    trata_texto(arquivo, texto);

    //Desacolações
    free(texto);
}