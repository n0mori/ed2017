#include "Torre.h"

Torre *new_torre(double x, double y, char *id, char *fill, char *stroke) {
  Torre *t = malloc(sizeof(Torre));
  t->x = x;
  t->y = y;
  strcpy(t->id, id);
  strcpy(t->fill, fill);
  strcpy(t->stroke, stroke);
  return t;
}
