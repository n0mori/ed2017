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

int rect_interno(Rect r, double x, double y) {
  if (x >= r.x && x <= r.x + r.width && y >= r.y && y <= r.y + r.height) {
    return 1;
  }
  return 0;
}
