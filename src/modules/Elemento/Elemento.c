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
