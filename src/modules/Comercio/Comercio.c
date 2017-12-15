#include "Comercio.h"

typedef struct comercio {
  char codt[100];
  Address address;
  char cnpj[100];
  char nome[100];
}* StComercio;

Comercio new_comercio(char *codt, char *cep, char face, int num, char *cnpj, char *nome) {
  StComercio c = malloc(sizeof(struct comercio));
  strcpy(c->codt, codt);
  c->address = new_address(cep, face, num, "");
  strcpy(c->cnpj, cnpj);
  strcpy(c->nome, nome);
  return c;
}

char *comercio_get_codt(Comercio c) {
  StComercio comercio = (StComercio) c;
  return comercio->codt;
}

Address comercio_get_address(Comercio c) {
  StComercio comercio = (StComercio) c;
  return comercio->address;
}

char *comercio_get_cep(Comercio c) {
  return address_get_cep(comercio_get_address(c));
}

char comercio_get_face(Comercio c) {
  return address_get_face(comercio_get_address(c));
}

int comercio_get_num(Comercio c) {
  return address_get_numero(comercio_get_address(c));
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

int cmp_comercio_codt(Comercio c, void *key) {
  return strcmp(comercio_get_codt(c), key) == 0;
}

int cmp_comercio_cep(Comercio c, void *key) {
  return strcmp(comercio_get_cep(c), key) == 0;
}

void free_comercio(Comercio c) {
  free(comercio_get_address(c));
  free(c);
}