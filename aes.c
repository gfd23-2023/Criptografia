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
//long tamanho_arquivo(char *arquivo)
//{
//    struct stat st;

//    if (stat(arquivo, &st) == 0)
//        return st.st_size;          //tamanho do arquivo em bytes
//}

void cifra_aes(const char *input_file, const char *output_file, unsigned char *key, unsigned char *iv)
{
    FILE *in = fopen(input_file, "rb");
    if (!in) {
        fprintf(stderr, "Erro ao abrir arquivo de entrada\n");
        return;
    }

    FILE *out = fopen(output_file, "wb");
    if (!out) {
        fprintf(stderr, "Erro ao abrir arquivo de saída\n");
        fclose(in);
        return;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Erro ao criar contexto AES\n");
        fclose(in);
        fclose(out);
        return;
    }

    // Inicializa com AES-256-CBC
    if (!EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        fprintf(stderr, "Erro no EncryptInit\n");
        EVP_CIPHER_CTX_free(ctx);
        fclose(in);
        fclose(out);
        return;
    }

    unsigned char inbuf[BLOCK_SIZE];
    unsigned char outbuf[BLOCK_SIZE + EVP_MAX_BLOCK_LENGTH];
    memset(outbuf, 0, sizeof(outbuf));      //zera o buffer para não ter lixo de memória
    int inlen, outlen;

    // Lê e processa blocos do arquivo
    while ((inlen = fread(inbuf, 1, BLOCK_SIZE, in)) > 0)
    {
        memset(outbuf, 0, sizeof(outbuf));  // zera antes de cada uso
        if (!EVP_EncryptUpdate(ctx, outbuf, &outlen, inbuf, inlen)) {
            fprintf(stderr, "Erro no EncryptUpdate\n");
            EVP_CIPHER_CTX_free(ctx);
            fclose(in);
            fclose(out);
            return;
        }
        fwrite(outbuf, 1, outlen, out);
    }

    // Finaliza (padding)
    memset(outbuf, 0, sizeof(outbuf));  // zera antes de cada uso
    if (!EVP_EncryptFinal_ex(ctx, outbuf, &outlen))
    {
        fprintf(stderr, "Erro no EncryptFinal\n");
        EVP_CIPHER_CTX_free(ctx);
        fclose(in);
        fclose(out);
        return;
    }
    
    fwrite(outbuf, 1, outlen, out);

    EVP_CIPHER_CTX_free(ctx);
    fclose(in);
    fclose(out);

}

void decifra_aes(const char *input_file, const char *output_file, unsigned char *key, unsigned char *iv)
{
    FILE *in = fopen(input_file, "rb");
    if (!in) {
        fprintf(stderr, "Erro ao abrir arquivo de entrada\n");
        return;
    }

    FILE *out = fopen(output_file, "wb");
    if (!out) {
        fprintf(stderr, "Erro ao abrir arquivo de saída\n");
        fclose(in);
        return;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Erro ao criar contexto AES\n");
        fclose(in);
        fclose(out);
        return;
    }

    // Inicializa com AES-256-CBC para decriptar
    if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        fprintf(stderr, "Erro no DecryptInit\n");
        EVP_CIPHER_CTX_free(ctx);
        fclose(in);
        fclose(out);
        return;
    }

    unsigned char inbuf[BLOCK_SIZE];
    unsigned char outbuf[BLOCK_SIZE + EVP_MAX_BLOCK_LENGTH];
    memset(outbuf, 0, sizeof(outbuf)); // zera o buffer
    int inlen, outlen;

    // Lê e processa blocos do arquivo cifrado
    while ((inlen = fread(inbuf, 1, BLOCK_SIZE, in)) > 0)
    {
        memset(outbuf, 0, sizeof(outbuf)); // zera antes de cada uso
        if (!EVP_DecryptUpdate(ctx, outbuf, &outlen, inbuf, inlen)) {
            fprintf(stderr, "Erro no DecryptUpdate\n");
            EVP_CIPHER_CTX_free(ctx);
            fclose(in);
            fclose(out);
            return;
        }
        fwrite(outbuf, 1, outlen, out);
    }

    // Finaliza (trata padding)
    memset(outbuf, 0, sizeof(outbuf)); // zera antes de cada uso
    if (!EVP_DecryptFinal_ex(ctx, outbuf, &outlen)) {
        fprintf(stderr, "Erro no DecryptFinal: possivelmente chave ou IV incorretos\n");
        EVP_CIPHER_CTX_free(ctx);
        fclose(in);
        fclose(out);
        return;
    }

    fwrite(outbuf, 1, outlen, out);

    EVP_CIPHER_CTX_free(ctx);
    fclose(in);
    fclose(out);

}
