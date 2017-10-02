#include "Hidrante.h"

typedef struct hidrante {
  double x, y, vazao;
  char id[100], fill[100], stroke[100];
} *StHidrante;

Hidrante new_hidrante(double x, double y, char *id, char *fill, char *stroke) {
  StHidrante h = malloc(sizeof(struct hidrante));
  Hidrante hidrante = h;
  h->x = x;
  h->y = y;
  h->vazao = 0;
  strcpy(h->id, id);
  strcpy(h->fill, fill);
  strcpy(h->stroke, stroke);
  return hidrante;
}

double hidrante_get_x(Hidrante h) {
  StHidrante hidrante = (StHidrante) h;
  return hidrante->x;
}

double hidrante_get_y(Hidrante h) {
  StHidrante hidrante = (StHidrante) h;
  return hidrante->y;
}

double hidrante_get_vazao(Hidrante h) {
  StHidrante hidrante = (StHidrante) h;
  return hidrante->vazao;
}
char* hidrante_get_id(Hidrante h) {
  StHidrante hidrante = (StHidrante) h;
  return hidrante->id;
}

char* hidrante_get_fill(Hidrante h) {
  StHidrante hidrante = (StHidrante) h;
  return hidrante->fill;
}

char* hidrante_get_stroke(Hidrante h) {
  StHidrante hidrante = (StHidrante) h;
  return hidrante->stroke;
}

void hidrante_set_vazao(Hidrante h, double vazao) {
  StHidrante hidrante = (StHidrante) h;
  hidrante->vazao = vazao;
}
