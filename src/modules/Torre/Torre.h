#ifndef TORRE__H
#define TORRE__H

/*
Uma torre é uma estrutura de uma cidade. Uma torre possui uma posição (x, y) no
plano cartesiano
*/

#include <stdlib.h>
#include <string.h>
#include "../Ponto/Ponto.h"
#include "../Lista/Lista.h"
#include "../Geo/Geo.h"

typedef void* Torre;

Torre new_torre(double x, double y, char *id, char *fill, char *stroke);
double torre_get_x(Torre t);
double torre_get_y(Torre t);
double torre_get_range(Torre t);
char* torre_get_id(Torre t);
char* torre_get_fill(Torre t);
char* torre_get_stroke(Torre t);
void torre_set_range(Torre t, double range);
void torre_range_pontos(Torre t, Lista *l);
void torre_set_operadora(Torre t, char codigo);
int torre_inside_circ(Torre t, void *c);
int torre_inside_rect(Torre t, void *r);
int cmp_torre_operadora(Torre t, void *op);

#endif
