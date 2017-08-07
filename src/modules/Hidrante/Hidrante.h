#ifndef HIDRANTE__H
#define HIDRANTE__H

/*
Um hidrante é uma estrutura de uma cidade. Um hidrante possui uma posição (x,y)
no plano cartesiano.
*/

#include <stdlib.h>
#include <string.h>

typedef struct hidrante {
  double x, y;
  char id[100], fill[100], stroke[100];
} Hidrante;

Hidrante *new_hidrante(double x, double y, char *id, char *fill, char *stroke);

#endif
