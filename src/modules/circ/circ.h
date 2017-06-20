#ifndef CIRC__H
#define CIRC__H value

#include "../coord/coord.h"
#include <stdlib.h>

struct ci {
  int id;
  double raio;
  coord ancora;
  char cor[100];
};

typedef struct ci circ;

circ *alloc_circ();

#endif /* CIRC__H */
