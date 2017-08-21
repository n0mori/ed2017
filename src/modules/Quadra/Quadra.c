#include "Quadra.h"

Quadra *new_quadra(double x, double y, double width, double height, char *cep, char *fill, char *stroke) {
  Quadra *q = malloc(sizeof(Quadra));
  q->x = x;
  q->y = y;
  q->width = width;
  q->height = height;
  strcpy(q->cep, cep);
  strcpy(q->fill, fill);
  strcpy(q->stroke, stroke);
  return q;
}
