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
    char maiusculas[25];                //contém todas as letras do alfabeto para facilitar a vida (0 ~ 25)
    char minusculas[25];
};

void inicializa_alfabeto(struct alfabeto_t *alfabeto)
{
    //Coloca todas as letras do alfabeto em um vetor

    //Maiúsculas
    for (int i = 65, j = 0; j < 25; j++, i++)
        alfabeto->maiusculas[j] = i;

    //Minúsculas
    for (int i = 97, j = 0; j < 25; j++, i++)
        alfabeto->minusculas[j] = i;
}

void inicializa_texto(struct texto_t *texto)
{
    texto->tamanho = 0;
    texto->num_pares = 0;
    texto->texto_base = NULL;
}

void inicializa_playfair(struct playfair_t *playfair)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            playfair->matriz[i][j] = 0;
    
    playfair->chave = NULL;                 //alocar memória depois que tiver a chave
    playfair->chave_recebida = NULL;        //alocar memória depois que tiver a chave
}

void trata_texto(char *arquivo, struct texto_t *texto)
{
    //Remove os espaços
    //Conta a quantidade de carateres do arquivo

    FILE *arquivo_original;
    char letra;

    arquivo_original = fopen(arquivo, "r");
    if (!arquivo_original) 
        printf("Falha ao abrir arquivo.\n\n");
    
    rewind(arquivo_original);

    //Conta o número de caracteres
    int i = 0;
    while ((letra = fgetc(arquivo_original)) != EOF)
    {
        texto->tamanho++;
        i++;
    }

    //Aloca memória para texto_base com base no número de carcteres
    texto->texto_base = malloc(texto->tamanho * sizeof(char));

    //Remove os espaços
    i = 0;
    while ((letra = fgetc(arquivo_original)) != EOF)
    {
        if (letra != ' ')                           //se não for um espaço
            texto->texto_base[i] = letra;           //guarda a letra
        
        i++;                                        //avança para o próximo campo do vetor
    }

    fclose(arquivo_original);
    printf("Número de caracteres com espaços: %d\n", texto->tamanho);
}

void forma_pares(struct texto_t *texto)
{
    //Forma os pares partindo do texto base
    //Se uma letra repetir, coloca um 'x' no meio
    //Se uma letra ficar sozinha, coloca um X como par
    
    //Calcula a quantidade de pares que serão necessários
    texto->num_pares = (texto->tamanho / 2);

    if (texto->tamanho % 2)
        texto->num_pares++;

}

void le_chave(struct playfair_t *playfair, struct alfabeto_t *alfabeto, char *chave)
{
    //Opera a chave recebida do teclado para que não repita letras

    playfair->chave_recebida = chave;
    playfair->tamanho_chave = strlen(chave);

    playfair->chave = malloc(playfair->tamanho_chave * sizeof(char));
    if (!playfair->chave)
    {
        printf("Não foi possível alocar memória para a chave.\n");
        return;
    }

    char igual = 0;
    char atual;
    
    //Remove letras repetidas da chave
    playfair->chave[0] = playfair->chave_recebida[0];
    playfair->chave[1] = '\0';
    printf("Tamanho playfair->chave = %ld\n", strlen(playfair->chave));
    int i = 0;
    while (playfair->chave_recebida[i] != '\0')
    {
        atual = playfair->chave_recebida[i];

        for (int j = 0; j < strlen(playfair->chave); j++)
        {
            if (playfair->chave[j] == atual)
                igual = 1;
        }

        if (!igual)
            playfair->chave[strlen(playfair->chave)] = playfair->chave_recebida[i];
        
        playfair->chave[strlen(playfair->chave) + 1] = '\0';

        igual = 0;          //Reseta o estado do controlador
        i++;                //avança para a próxima letra
    }

    printf("Tamanho da chave sem repetir: %ld\n", strlen(playfair->chave));
    for (int i = 0; i < strlen(playfair->chave); i++)
        printf("%c", playfair->chave[i]);
    printf("\n");
}

void monta_matriz(struct playfair_t *playfair, struct alfabeto_t *alfabeto)
{
    //Monta a matriz que será usada na codificação
    char letra;

    char i = 0;
    char j = 0;
    char k = playfair->tamanho_chave;

    //Coloca a chave processada na matriz
    while ((playfair->chave[k] != '\0') && (i < 5) && (k < playfair->tamanho_chave))
    {
        while (j < 5)
        {
            playfair->matriz[i][j] = playfair->chave[k];
            j++;
        }

        i++;
        k++;
    }
}

void cifra(struct texto_t *texto, struct playfair_t *playfair)
{
    //Cifra o texto com base nas regras da playfair
}

void decifra(struct playfair_t *playfair)
{
    //Decifra o texto usando as regras da playfair
}

void libera_texto(struct texto_t *texto)
{
    free(texto->texto_base);
}

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

    //Liberações de memória
    free(alfabeto);
    free(arquivo);
    free(chave);
    libera_texto(texto);
    free(texto);
    free(playfair);
}