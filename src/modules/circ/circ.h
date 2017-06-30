#ifndef CIRC__H
#define CIRC__H

#include <stdlib.h>
#include <string.h>

struct ci {
  int id;
  double x, y, raio;
  char cor[100];
};

typedef struct ci circ;

circ *new_circ(double raio, double x, double y, char *cor);
int circ_interno(circ c, double x, double y);
double circ_upmost(circ c);
double circ_leftmost(circ c);
double circ_botmost(circ c);
double circ_rightmost(circ c);

#endif /* CIRC__H */
