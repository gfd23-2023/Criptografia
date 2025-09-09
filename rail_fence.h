/*ESTRUTURAS - MACROS - PROTÓTIPOS*/

struct rail_fence_t {
    unsigned char **matriz;                  //Matriz que vai conter todos os caracteres
    unsigned char *texto_limpo;              //Texto base livre de espaços e acentuações
    unsigned int num_linhas;                 //Chave
    unsigned int num_colunas;                //Inicialmente fixo, mas pode mudar se houver muitos caracteres
};