#include "Cidade.h"

Cidade new_cidade() {
  Cidade c;
  c.quadras = create_lista();
  c.hidrantes = create_lista();
  c.semaforos = create_lista();
  c.torres = create_lista();
  return c;
}

void insere_quadra(Cidade c, Quadra *q, int *cmp, int *insercoes) {
  *cmp += insert_last(c.quadras, q);
  *insercoes++;
}

void insere_hidrante(Cidade c, Hidrante *h) {
  insert_last(c.hidrantes, h);
}

void insere_semaforo(Cidade c, Semaforo *s) {
  insert_last(c.semaforos, s);
}

void insere_torre(Cidade c, Torre *t) {
  insert_last(c.torres, t);
}

int remove_quadra(Cidade c, Quadra *q, int *cmp);
int remove_hidrante(Cidade c, Hidrante *h);
int remove_semaforo(Cidade c, Semaforo *s);
int remove_torre(Cidade c, Torre *t);
