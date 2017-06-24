#include "circ.h"

circ *alloc_circ() {
  circ *c = (circ*) malloc(sizeof(circ));
  return c;
}

int circ_interno(circ c, double x, double y) {
  if (dist_cp(c.ancora, x, y) <= c.raio) {
    return 1;
  }
  return 0;
}

double circ_leftmost(circ c) {
  return c.ancora.x - c.raio;
}

double circ_upmost(circ c) {
  return c.ancora.y - c.raio;
}

double circ_botmost(circ c) {
  return c.ancora.y + c.raio;
}

double circ_rightmost(circ c) {
  return c.ancora.x + c.raio;
}
