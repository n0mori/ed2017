#include "Comercio.h"

typedef struct comercio {
  char codt[100];
  char cep[100];
  char face;
  int num;
  char cnpj[100];
  char nome[100];
}* StComercio;

Comercio new_comercio(char *codt, char *cep, char face, int num, char *cnpj, char *nome) {
  StComercio c = malloc(sizeof(struct comercio));
  strcpy(c->codt, codt);
  strcpy(c->cep, cep);
  c->face = face;
  c->num = num;
  strcpy(c->cnpj, cnpj);
  strcpy(c->nome, nome);
  return c;
}

char *comercio_get_codt(Comercio c) {
  StComercio comercio = (StComercio) c;
  return comercio->codt;
}

char *comercio_get_cep(Comercio c) {
  StComercio comercio = (StComercio) c;
  return comercio->cep;
}

char comercio_get_face(Comercio c) {
  StComercio comercio = (StComercio) c;
  return comercio->face;
}

int comercio_get_num(Comercio c) {
  StComercio comercio = (StComercio) c;
  return comercio->num;
}

char *comercio_get_cnpj(Comercio c) {
  StComercio comercio = (StComercio) c;
  return comercio->cnpj;
}

char *comercio_get_nome(Comercio c) {
  StComercio comercio = (StComercio) c;
  return comercio->nome;
}

int cmp_comercio_cnpj(Comercio c, void *key) {
  return strcmp(comercio_get_cnpj(c), key) == 0;
}

void free_comercio(Comercio c) {
  free(c);
}