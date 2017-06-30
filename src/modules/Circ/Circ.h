#ifndef CIRC__H
#define CIRC__H

#include <stdlib.h>
#include <string.h>

struct ci {
  int id;
  double x, y, raio;
  char cor[100];
};

typedef struct ci Circ;

Circ *new_circ(double raio, double x, double y, char *cor);
int circ_interno(Circ c, double x, double y);
double circ_upmost(Circ c);
double circ_leftmost(Circ c);
double circ_botmost(Circ c);
double circ_rightmost(Circ c);

#endif /* CIRC__H */
