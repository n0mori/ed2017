#include "Hidrante.h"

Hidrante *new_hidrante(double x, double y, char *id, char *fill, char *stroke) {
  Hidrante *h = malloc(sizeof(Hidrante));
  h->x = x;
  h->y = y;
  strcpy(h->id, id);
  strcpy(h->fill, fill);
  strcpy(h->stroke, stroke);
  return h;
}
