#ifndef RECT__H
#define RECT__H value

#include "../coord/coord.h"
#include <stdlib.h>

typedef struct r {
  int id;
  coord ancora;
  double width, height;
  char cor[100];
} rect;

rect *alloc_rect();

#endif
