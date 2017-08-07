#ifndef TORRE__H
#define TORRE__H

/*
Uma torre é uma estrutura de uma cidade. Uma torre possui uma posição (x, y) no
plano cartesiano
*/

#include <stdlib.h>
#include <string.h>

typedef struct torre {
  double x, y;
  char id[100], fill[100], stroke[100];
} Torre;

Torre *new_torre(double x, double y, char *id, char *fill, char *stroke);

#endif
