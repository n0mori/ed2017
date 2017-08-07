#include "Semaforo.h"

Semaforo *new_semaforo(double x, double y, char *id, char *fill, char *stroke) {
  Semaforo *s = malloc(sizeof(Semaforo));
  s->x = x;
  s->y = y;
  strcpy(s->id, id);
  strcpy(s->fill, fill);
  strcpy(s->stroke, stroke);
  return s;
}
