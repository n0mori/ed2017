#include "circ.h"

circ *new_circ(int id, double raio, double x, double y, char *cor) {
  circ *c = (circ*) malloc(sizeof(circ));
  c->id = id;
  c->raio = raio;
  c->x = x;
  c->y = y;
  strcpy(c->cor, cor);
  return c;
}

int circ_interno(circ c, double x, double y) {
  if (dist(c.x, c.y, x, y) <= c.raio) {
    return 1;
  }
  return 0;
}

double circ_leftmost(circ c) {
  return c.x - c.raio;
}

double circ_upmost(circ c) {
  return c.y - c.raio;
}

double circ_botmost(circ c) {
  return c.y + c.raio;
}

double circ_rightmost(circ c) {
  return c.x + c.raio;
}
