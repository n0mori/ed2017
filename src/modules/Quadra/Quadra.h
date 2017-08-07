#ifndef QUADRA__H
#define QUADRA__H

/*
Uma quadra é uma estrutura da cidade. Uma quadra tem sua posição (x,y) no plano
cartesiano, altura, largura, cor e um CEP alfanumérico.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct quadra {
  double x, y, width, height;
  char cep[100], fill[100], stroke[100];
} Quadra;

Quadra *new_quadra(double x, double y, double width, double height, char *cep, char *fill, char *stroke);

#endif
