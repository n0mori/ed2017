#include "circ.c"

circ *alloc_circ() {
  circ *c = (circ *) malloc(sizeof(circ));
  return c;
}
