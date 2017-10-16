#include "Elemento.h"

void inicializa_elemento(Elemento *e) {
  e->id = -1;
  e->tipo = 0;
  e->dado = NULL;
}

void *get_elemento_dado(Elemento e) {
  return e.dado;
}

int get_elemento_id(Elemento e) {
  return e.id;
}

char get_elemento_tipo(Elemento e) {
  return e.tipo;
}

Elemento *new_elemento(int id, char tipo, void *dado) {
  Elemento *e = malloc(sizeof(Elemento));
  e->id = id;
  e->tipo = tipo;
  e->dado = dado;
  return e;
}

double elemento_get_x(void *elemento) {
  Elemento *e = (Elemento*) elemento;
  if (e->tipo == 'c') {
    Circ *c = (Circ*) e->dado;
    return c->x;
  } else if (e->tipo == 'r') {
    Rect *r = (Rect*) e->dado;
    return r->x;
  }
  return 0;
}

double elemento_get_y(void *elemento) {
  Elemento *e = (Elemento*) elemento;
  if (e->tipo == 'c') {
    Circ *c = (Circ*) e->dado;
    return c->y;
  } else if (e->tipo == 'r' || e->tipo == 'e') {
    Rect *r = (Rect*) e->dado;
    return r->y;
  }
  return 0;
}

void destroy_dado_elemento(void *elemento) {
  Elemento *e = (Elemento*) elemento;
  if (elemento != NULL) {
    free(e->dado);
  }
}
