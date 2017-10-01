#include "Quadra.h"

typedef struct quadra {
  double x, y, width, height;
  char cep[100], fill[100], stroke[100];
} StQuadra;

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

double quadra_get_y(Quadra *q) {
  return q->y;
}
