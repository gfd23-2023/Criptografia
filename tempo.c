#define _POSIX_C_SOURCE 199309L     //para não acusar declaração implícita de clock_gettime

#include <stdio.h>
#include <time.h>

#include "tempo.h"

void imprime_tempo(struct timespec *inicio, struct timespec *fim)
{
    printf("inicio: %ld segundos, %ld nanossegundos\n", inicio->tv_sec, inicio->tv_nsec);
    printf("fim:    %ld segundos, %ld nanossegundos\n", fim->tv_sec, fim->tv_nsec);
}