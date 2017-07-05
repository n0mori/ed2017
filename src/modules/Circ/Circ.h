#ifndef CIRC__H
#define CIRC__H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

struct ci {
  double x, y, raio;
  char cor[100];
};

typedef struct ci Circ;

Circ *new_circ(double raio, double x, double y, char *cor);
double circ_upmost(Circ c);
double circ_leftmost(Circ c);
double circ_botmost(Circ c);
double circ_rightmost(Circ c);

#endif /* CIRC__H */
