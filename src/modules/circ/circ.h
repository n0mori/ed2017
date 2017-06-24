#ifndef CIRC__H
#define CIRC__H value

#include "../coord/coord.h"
#include <stdlib.h>

struct ci {
  int id;
  coord ancora;
  double raio;
  char cor[100];
};

typedef struct ci circ;

circ *alloc_circ();
int circ_interno(circ c, double x, double y);
double circ_upmost(circ c);
double circ_leftmost(circ c);
double circ_botmost(circ c);
double circ_rightmost(circ c);

#endif /* CIRC__H */
