/*Includes para o AES*/
#include <openssl/evp.h>
#include <openssl/rand.h>

/*Includes para buscar o tamanho do arquivo*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*Includes comuns*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aes.h"

void gera_bytes_aleat(unsigned char *buffer, int len)
{
    if (!RAND_bytes(buffer, len))
    {
        fprintf(stderr, "Erro ao gerar bytes aleatórios\n");
        exit(1);
    }
}

//Consulta os metadados do arquivos por meio de uma syscall
long tamanho_arquivo(char *arquivo)
{
    struct stat st;

    if (stat(arquivo, &st) == 0)
        return st.st_size;          //tamanho do arquivo em bytes
}

void cifra_aes(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext)
{
    //Cria o contexto de criptografia
    EVP_CIPHER_CTX *ctx;
    int len, ciphertext_len = 0;

    //Aloca memória para o contexo de criptografia
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
    {
        fprintf(stderr, "Erro ao alocar memória para o contexto de criptografia\n");
    }

    //Inicializa o contexto de criptografia com AES-256-CBC
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    //Processa o arquivo em blocos
    int offset = 0;
    while (offset < plaintext_len)
    {
        int chunk = (plaintext_len - offset > BLOCK_SIZE) ? BLOCK_SIZE : (plaintext_len - offset);

        if (!EVP_EncryptUpdate(ctx, ciphertext + ciphertext_len, &len, plaintext + offset, chunk))
        {
            fprintf(stderr, "Erro no EncryptUpdate - dentro de cifra_aes\n");
            
            //Libera memória
            EVP_CIPHER_TEXT_CTX_free(ctx);
            return;
        }

        ciphertext_len += len;
        offset += chunk;
    }

    //Trata o último bloco
    if (!EVP_EncryptFinal_ex(ctx, ciphertext + ciphertext_len, &len))
    {
        fprintf(stderr, "Erro no EncryptFinal\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }

    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return;

    /*OBSERVAÇÃO!!!!!
     *AINDA PRECISO FAZER COM QUE A FUNÇÃO CIFRA ESCREVA
     *O TEXTO CIFRADO DENTRO DE UM ARQUIVO!!!!!!*/
}