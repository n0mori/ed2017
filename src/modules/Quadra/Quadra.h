#ifndef QUADRA__H
#define QUADRA__H

/*
Uma quadra é uma estrutura da cidade. Uma quadra tem sua posição (x,y) no plano
cartesiano, altura, largura, cor e um CEP alfanumérico.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../Geo/Geo.h"

typedef void * Quadra;

Quadra new_quadra(double x, double y, double width, double height, char *cep, char *fill, char *stroke);
double quadra_get_y(Quadra q);
double quadra_get_x(Quadra q);
double quadra_get_width(Quadra q);
double quadra_get_height(Quadra q);
char* quadra_get_cep(Quadra q);
char* quadra_get_fill(Quadra q);
char* quadra_get_stroke(Quadra q);
int quadra_inside_circ(Quadra q, void *circ);
int quadra_inside_rect(Quadra q, void *rect);
void quadra_print_xy(FILE *f, Quadra q);

#endif
