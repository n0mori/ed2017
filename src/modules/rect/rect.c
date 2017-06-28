#include "rect.h"

rect *new_rect(int id, double width, double height, double x, double y, char *cor) {
  rect *r = (rect*) malloc(sizeof(rect));
  r->id = id;
  r->width = width;
  r->height = height;
  r->x = x;
  r->y = y;
  strcpy(r->cor, cor);
  return r;
}

int rect_interno(rect r, double x, double y) {
  if (x >= r.x && x <= r.x + r.width && y >= r.y && y <= r.y + r.height) {
    return 1;
  }
  return 0;
}
