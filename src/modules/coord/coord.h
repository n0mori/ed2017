#ifndef COORD__H
#define COORD__H

/*
Esse arquivo define os métodos e atributos de uma coordenada cartesiana (coord).
Uma coordenada cartesiana é um par ordenado de dois valores reais, que represen-
tam um espaço em um plano cartesiano. x e y se referem, respectivamente à posição
no eixo x e y.
*/

#include <math.h>

typedef struct c {
  double x, y;
} coord;

double dist_coords(coord a, coord b);
double dist_ponto(coord a, double x, double y);

#endif /* COORD__H */
