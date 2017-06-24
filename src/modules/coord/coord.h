#ifndef COORD__H
#define COORD__H

/*
Esse arquivo define os metodos e atributos de uma coordenada cartesiana (coord).
Uma coordenada cartesiana eh um par ordenado de dois valores reais, que represen-
tam um espaco em um plano cartesiano. x e y se referem, respectivamente a posicao
no eixo x e y.
*/

#include <math.h>

typedef struct c {
  double x, y;
} coord;

double dist(double xa, double ya, double xb, double yb);
double dist_coords(coord a, coord b);
double dist_ponto(coord a, double x, double y);

#endif /* COORD__H */
