/*Funções para cifrar e decifrar do AES*/

#ifndef __AES_H__
#define __AES_H__

#define BLOCK_SIZE 4096     //Tamanho do bloco a ser processado
#define kEY_SIZE 32         //256 bits
#define IV_SIZE 16          //128 bits

//Função auxiliar para gerar as chaves aleatŕoias
void gera_bytes_aleat(unsigned char *buffer, int len);

//Devolve o tamanho do arquivo
long tamanho_arquivo(char *arquivo);

//Função para cifrar
void cifra_aes(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);

//Função para decifrar
void decifra_aes(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext);


#endif