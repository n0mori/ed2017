#ifndef QUADRA__H
#define QUADRA__H

/*
Uma quadra é uma estrutura da cidade. Uma quadra tem sua posição (x,y) no plano
cartesiano, altura, largura, cor e um CEP alfanumérico.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef void * Quadra;

Quadra *new_quadra(double x, double y, double width, double height, char *cep, char *fill, char *stroke);
double quadra_get_y(Quadra *q);

#endif
