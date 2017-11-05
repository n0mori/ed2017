#include "TipoCom.h"

typedef struct tipocom {
  char codt[100];
  char desc[100];
}* StTipoCom;

TipoCom new_tipocom(char *codt, char *desc) {
  StTipoCom t = malloc(sizeof(struct tipocom));
  strcpy(t->codt, codt);
  strcpy(t->desc, desc);
  return t;
}

char *tipocom_get_codt(TipoCom t) {
  StTipoCom tipo = (StTipoCom) t;
  return tipo->codt;
}

char *tipocom_get_desc(TipoCom t) {
  StTipoCom tipo = (StTipoCom) t;
  return tipo->desc;
}

int cmp_tipocom_codt(TipoCom t, void *codt) {
  return strcmp(tipocom_get_codt(t), codt) == 0;
}

void free_tipocom(TipoCom t) {
  free(t);
}