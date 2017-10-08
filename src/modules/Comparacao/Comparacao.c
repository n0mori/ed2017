#include "Comparacao.h"

int cmp_quadra_string(void *a, void *b) {
  Quadra q = (Quadra) a;
  char *s = (char*) b;
  return strcmp(quadra_get_cep(q), s);
}

int cmp_hidrante_string(void *a, void *b) {
  Hidrante h = (Hidrante) a;
  char *s = (char*) b;
  return strcmp(hidrante_get_id(h), s);
}

int cmp_semaforo_string(void *a, void *b) {
  Semaforo semaforo = (Semaforo) a;
  char *s = (char*) b;
  return strcmp(semaforo_get_id(semaforo), s);
}

int cmp_torre_string(void *a, void *b) {
  Torre t = (Torre) a;
  char *s = (char*) a;
  return strcmp(torre_get_id(t), s);
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

int cmp_hidrante_hidrante_y0(void *a, void *b) {
  double y1 = hidrante_get_y((Hidrante) a);
  double y2 = hidrante_get_y((Hidrante) b);
  if (y1 < y2) {
    return -1;
  } else if (y1 == y2) {
    return 0;
  } else {
    return 1;
  }
}

int cmp_semaforo_semaforo_y0(void *a, void *b) {
  double y1 = semaforo_get_y((Semaforo) a);
  double y2 = semaforo_get_y((Semaforo) b);
  if (y1 < y2) {
    return -1;
  } else if (y1 == y2) {
    return 0;
  } else {
    return 1;
  }
}

int cmp_torre_torre_y0(void *a, void *b) {
  double y1 = torre_get_y((Torre) a);
  double y2 = torre_get_y((Torre) b);
  if (y1 < y2) {
    return -1;
  } else if (y1 == y2) {
    return 0;
  } else {
    return 1;
  }
}

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
