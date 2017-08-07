#ifndef SEMAFORO__H
#define SEMAFORO__H

/*
Um semáforo é uma estrutura de uma cidade. Um semáforo possui uma posição (x,y)
no plano cartesiano e uma cor
*/

#include <stdlib.h>
#include <string.h>

typedef struct semaforo {
  double x, y;
  char id[100], fill[100], stroke[100];
} Semaforo;

Semaforo *new_semaforo(double x, double y, char *id, char *fill, char *stroke);

#endif
