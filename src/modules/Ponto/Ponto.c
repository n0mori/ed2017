#include "Ponto.h"

typedef struct st_ponto {
  double x, y;
}* StPonto;

Ponto new_ponto(double x, double y) {
  StPonto p = malloc(sizeof(struct st_ponto));
  Ponto ponto = p;
  p->x = x;
  p->y = y;
  return ponto;
}

double get_x(Ponto p) {
  StPonto ponto = (StPonto) p;
  return ponto->x;
}

double get_y(Ponto p) {
  StPonto ponto = (StPonto) p;
  return ponto->y;
}
