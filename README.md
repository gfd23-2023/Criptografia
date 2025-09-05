# Criptografia 🌐📱

## Cifra Gi-Playfair-Fence
### Sumário:
1. Processo de implementação
2. Funcionamento da cifra

### Linguagem: C

> ### 1. Processo de Implementação
A implementação do trabalho teve início pela cifra playfair. Antes de tudo, era um código para testes e, quando foi ficando grande demais, foi separado em arquivos e modularizado.
#### 1.1 Playfair
Arquivos: 
```
├── playfair.h  --> Protóptipos das funções de manipulação do texto e cifra/decifra da playfair.
├──── playfair.c  --> Implementação do .h.
├────── cifra.c    --> Utiliza o .c e o .h para cifrar um texto com as regras da playfair (Rail Fence também).
├─────── decifra.c  --> Utiliza o .c e o .h para decifrar um texto com as regras da playfair (Rail Fence também).
```
#### Estruturas:
```C
struct playfair_t {
    char matriz[5][5];              //matriz que será preenchida
    char *chave;                    //chave que preenche a matriz (não repete letras)
    char *chave_recebida;           //registro da chave passada pelo usuário
    char *texto_cifrado;            //texto cifrado e formatado
    char *texto_decifrado;          //texto decifrado e formatado
    unsigned int tamanho_chave;     //tamanho da chave para facilitar as contas
    char linha;                     //linha alvo para codificação/decodifucação
    char coluna;                    //coluna alvo para codificação/decodificação
};

struct texto_t{
    unsigned int tamanho;           //número de caracteres do texto com espaços
    unsigned int num_pares;         //quantidade de parzinhos formados -> não utilizei
    char *texto_base;               //texto base sem espaços e com letras de complemento (x)
    char *pares_originais;          //pares de indexação para codificar o texto
};

struct alfabeto_t {
    char maiusculas[25];            //contém todas as letras do alfabeto para facilitar a vida (0 ~ 25)
};
```

O arquivo principal da playfair é `playfair.c` no qual a implementação de cada funão é feita. O Projeto foi sofrendo diversas mudanças ao longo da implementação, por exemplo:
- Antes, o alfabeto também guardava as letras minúsculas. Depois eu decidi que seria mais fácil trabalhar somente com um tipo de letra, para melhorar a insersão delas na matriz.
- Depois de algumas experiências não muito boas, optei por utilizar uma espécie de "bitmap" para mapear as letras na matriz. Seu funcionamento é simples: cria-se um vetor auxiliar inicializado com zeros. Conforme lemos a chave, marcamos com 1 a posição correspondente ao índice da letra. O índice é encontrado subtraindo o valor do caractere do valor de A (65). Então, as letras da chave e as demais são colocadas ao mesmo tempo na matriz.
- Pensei em usar um `switch case` para implementar as regras da matriz, mas não consegui desenvolver muito bem. Então, mantive a estrutura de `else if`.