#include "Comparacao.h"

int cmp_quadra_string(void *a, void *b) {
  Quadra *q = (Quadra*) a;
  char *s = (char*) b;
  return strcmp(q->cep, s);
}

int cmp_hidrante_string(void *a, void *b) {
  Hidrante *h = (Hidrante*) a;
  char *s = (char*) b;
  return strcmp(h->id, s);
}

int cmp_semaforo_string(void *a, void *b) {
  Semaforo *semaforo = (Semaforo*) a;
  char *s = (char*) b;
  return strcmp(semaforo->id, s);
}

int cmp_torre_string(void *a, void *b) {
  Torre *t = (Torre*) a;
  char *s = (char*) a;
  return strcmp(t->id, s);
}

int cmp_quadra_quadra_y0(void *a, void *b) {
  double y1 = quadra_get_y((Quadra*) a);
  double y2 = quadra_get_y((Quadra*) b);
  if (y1 < y2) {
    return -1;
  } else if (y1 == y2) {
    return 0;
  } else {
    return 1;
  }
}

int cmp_quadra_quadra_theta(void *a, void *b);

int cmp_int_int(void *a, void *b) {
  int *x = (int*) a;
  int *y = (int*) b;
  if (*x < *y) {
    return -1;
  } else if (*x == *y) {
    return 0;
  } else {
    return 1;
  }
}

int cmp_double_double(void *a, void *b) {
  double *x = (double*) a;
  double *y = (double*) b;
  if (*x < *y) {
    return -1;
  } else if (*x == *y) {
    return 0;
  } else {
    return 1;
  }
}
