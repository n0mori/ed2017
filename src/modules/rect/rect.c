#include "rect.h"

rect *new_rect(int id, double width, double height, double x, double y, char *cor) {
  rect *r = (rect*) malloc(sizeof(rect));
  r->id = id;
  r->width = width;
  r->height = height;
  r->ancora.x = x;
  r->ancora.y = y;
  strcpy(r->cor, cor);
  return r;
}

int rect_interno(rect r, double x, double y) {
  if (x >= r.ancora.x && x <= r.ancora.x + r.width && y >= r.ancora.y && y <= r.ancora.y + r.height) {
    return 1;
  }
  return 0;
}
