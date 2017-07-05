#include "Rect.h"

Rect *new_rect(double width, double height, double x, double y, char *cor) {
  Rect *r = (Rect*) malloc(sizeof(Rect));
  r->width = width;
  r->height = height;
  r->x = x;
  r->y = y;
  strcpy(r->cor, cor);
  return r;
}
