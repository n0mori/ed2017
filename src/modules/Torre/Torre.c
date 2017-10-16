#include "Torre.h"

typedef struct torre {
  double x, y, range;
  char id[100], fill[100], stroke[100];
}* StTorre;

Torre new_torre(double x, double y, char *id, char *fill, char *stroke) {
  StTorre t = malloc(sizeof(struct torre));
  Torre torre = t;
  t->x = x;
  t->y = y;
  t->range = 0;
  strcpy(t->id, id);
  strcpy(t->fill, fill);
  strcpy(t->stroke, stroke);
  return torre;
}

double torre_get_x(Torre t) {
  StTorre torre = (StTorre) t;
  return torre->x;
}

double torre_get_y(Torre t) {
  StTorre torre = (StTorre) t;
  return torre->y;
}

double torre_get_range(Torre t) {
  StTorre torre = (StTorre) t;
  return torre->range;
}

char* torre_get_id(Torre t) {
  StTorre torre = (StTorre) t;
  return torre->id;
}

char* torre_get_fill(Torre t) {
  StTorre torre = (StTorre) t;
  return torre->fill;
}

char* torre_get_stroke(Torre t) {
  StTorre torre = (StTorre) t;
  return torre->stroke;
}

void torre_set_range(Torre t, double range) {
  StTorre torre = (StTorre) t;
  torre->range = range;
}

void torre_range_pontos(Torre t, Lista *l) {
  double sen_45 = 0.7071;
  double x = torre_get_x(t);
  double y = torre_get_y(t);
  double range = torre_get_range(t);
  double r_sen = sen_45 * range;
  insert_last(l, new_ponto(x - range, y));
  insert_last(l, new_ponto(x - r_sen, y - r_sen));
  insert_last(l, new_ponto(x, y - range));
  insert_last(l, new_ponto(x + r_sen, y - r_sen));
  insert_last(l, new_ponto(x + range, y));
  insert_last(l, new_ponto(x + r_sen, y + r_sen));
  insert_last(l, new_ponto(x, y + range));
  insert_last(l, new_ponto(x - r_sen, y + r_sen));
}

int torre_inside_circ(Torre t, void *c) {
  Circ *circ = (Circ*) c;
  return circ_interno(*circ, torre_get_x(t), torre_get_y(t));
}

int torre_inside_rect(Torre t, void *r) {
  Rect *rect = (Rect*) r;
  return rect_interno(*rect, torre_get_x(t), torre_get_y(t));
}
