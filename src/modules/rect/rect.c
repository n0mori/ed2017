#include "rect.h"

rect *alloc_rect() {
  rect *r = malloc(sizeof(rect));
  return r;
}
