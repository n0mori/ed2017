#include "Quadra.h"

typedef struct quadra {
  double x, y, width, height;
  char cep[100], fill[100], stroke[100];
}* StQuadra;

Quadra new_quadra(double x, double y, double width, double height, char *cep, char *fill, char *stroke) {
  StQuadra q = malloc(sizeof(struct quadra));
  Quadra quadra = q;
  q->x = x;
  q->y = y;
  q->width = width;
  q->height = height;
  strcpy(q->cep, cep);
  strcpy(q->fill, fill);
  strcpy(q->stroke, stroke);
  return quadra;
}

double quadra_get_y(Quadra q) {
  StQuadra quadra = (StQuadra) q;
  return quadra->y;
}

double quadra_get_x(Quadra q) {
  StQuadra quadra = (StQuadra) q;
  return quadra->x;
}

double quadra_get_height(Quadra q) {
  StQuadra quadra = (StQuadra) q;
  return quadra->height;
}

double quadra_get_width(Quadra q) {
  StQuadra quadra = (StQuadra) q;
  return quadra->width;
}

char* quadra_get_cep(Quadra q) {
  StQuadra quadra = (StQuadra) q;
  return quadra->cep;
}

char* quadra_get_fill(Quadra q) {
  StQuadra quadra = (StQuadra) q;
  return quadra->fill;
}

char* quadra_get_stroke(Quadra q) {
  StQuadra quadra = (StQuadra) q;
  return quadra->stroke;
}

int quadra_inside_circ(Quadra q, void *circ) {
  Circ *c = (Circ*) circ;
  Rect *r = new_rect(quadra_get_width(q), quadra_get_height(q), quadra_get_x(q), quadra_get_y(q), "");
  int val = rect_inside_circ(*r, *c);
  free(r);
  return val;
}

int quadra_inside_rect(Quadra q, void *rect) {
  Rect *r = (Rect*) rect;
  Rect *rect1 = new_rect(quadra_get_width(q), quadra_get_height(q), quadra_get_x(q), quadra_get_y(q), "");
  int val = rect_inside_rect(*rect1, *r);
  free(rect1);
  return val;
}

void quadra_print_xy(FILE *f, Quadra q) {
  fprintf(f, "Quadra - x: %f y: %f\n", quadra_get_x(q), quadra_get_y(q));
}
