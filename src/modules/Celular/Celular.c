#include "Celular.h"

typedef struct celular {
  char numero[100];
  char cpf[100];
}* StCelular;

Celular new_celular(char *numero, char *cpf) {
  StCelular c = malloc(sizeof(struct celular));
  strcpy(c->numero, numero);
  strcpy(c->cpf, cpf);
  return c;
}

char *celular_get_numero(Celular c) {
  StCelular celular = (StCelular) c;
  return celular->numero;
}

char *celular_get_cpf(Celular c) {
  StCelular celular = (StCelular) c;
  return celular->cpf;
}

int cmp_celular_numero(Celular c, void *numero) {
  return strcmp(celular_get_numero(c), numero) == 0;
}