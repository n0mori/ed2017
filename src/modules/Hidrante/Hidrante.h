#ifndef HIDRANTE__H
#define HIDRANTE__H

/*
Um hidrante é uma estrutura de uma cidade. Um hidrante possui uma posição (x,y)
no plano cartesiano.
*/

#include <stdlib.h>
#include <string.h>
#include "../Geo/Geo.h"

typedef void* Hidrante;

Hidrante new_hidrante(double x, double y, char *id, char *fill, char *stroke);
double hidrante_get_x(Hidrante h);
double hidrante_get_y(Hidrante h);
double hidrante_get_vazao(Hidrante h);
char* hidrante_get_id(Hidrante h);
char* hidrante_get_fill(Hidrante h);
char* hidrante_get_stroke(Hidrante h);
void hidrante_set_vazao(Hidrante h, double vazao);
int hidrante_inside_circ(Hidrante h, void *circ);
int hidrante_inside_rect(Hidrante h, void *rect);

#endif
