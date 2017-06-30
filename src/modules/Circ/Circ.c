#include "Circ.h"

Circ *new_circ(double raio, double x, double y, char *cor) {
  Circ *c = (Circ*) malloc(sizeof(Circ));
  c->raio = raio;
  c->x = x;
  c->y = y;
  strcpy(c->cor, cor);
  return c;
}

int circ_interno(Circ c, double x, double y) {
  if (dist(c.x, c.y, x, y) <= c.raio) {
    return 1;
  }
  return 0;
}

double circ_leftmost(Circ c) {
  return c.x - c.raio;
}

double circ_upmost(Circ c) {
  return c.y - c.raio;
}

double circ_botmost(Circ c) {
  return c.y + c.raio;
}

double circ_rightmost(Circ c) {
  return c.x + c.raio;
}
