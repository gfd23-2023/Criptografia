#define _POSIX_C_SOURCE 199309L     //para não acusar declaração implícita de clock_gettime

#include <stdio.h>
#include <time.h>

#include "tempo.h"

double imprime_tempo(struct timespec *inicio, struct timespec *fim)
{
    #ifdef DEBUG
    printf("inicio: %ld segundos, %ld nanossegundos\n", inicio->tv_sec, inicio->tv_nsec);
    printf("fim: %ld segundos, %ld nanossegundos\n", fim->tv_sec, fim->tv_nsec);
    printf("Duração: %ld segundos, %ld nanosegundos\n", fim->tv_sec - inicio->tv_sec, fim->tv_nsec - inicio->tv_nsec);
    #endif

    double sec;

    sec = (double) (fim->tv_nsec - inicio->tv_nsec)/1000000000.0;

    printf("Duração: %.10f segundos\n", sec);
    
    return sec;
}

void tempo_arquivo(FILE *arquivo, double segundos)
{
    //Confere se está aberto
    if (!arquivo)
    {
        printf("Erro ao abrir arquivo para gravar o tempo.\n");
        return;
    }

    //Escreve
    fprintf(arquivo, "%.10f\n", segundos);
}