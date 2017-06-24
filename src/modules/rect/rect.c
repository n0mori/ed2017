#include "rect.h"

rect *alloc_rect() {
  rect *r = malloc(sizeof(rect));
  return r;
}

int rect_interno(rect r, double x, double y) {
  if (x >= r.ancora.x && x <= r.ancora.x + r.width && y >= r.ancora.y && y <= r.ancora.y + r.height) {
    return 1;
  }
  return 0;
}
