#ifndef __TEMPO_H__
#define __TEMPO_H__

double imprime_tempo(struct timespec *inicio, struct timespec *fim);

void tempo_arquivo(FILE *arquivo, double segundos);

#endif