#include "Celular.h"

typedef struct celular {
  char dono[100];
  char numero[100];
  char operadora;
  char torre[100];
}* StCelular;

Celular new_celular(char *dono, char *numero, char operadora) {
  StCelular c = malloc(sizeof (struct celular));
  strcpy(c->dono, dono);
  strcpy(c->numero, numero);
  c->operadora = operadora;
  c->torre[0] = 0;
  return c;
}

char* celular_get_dono(Celular c) {
  StCelular celular = (StCelular) c;
  return celular->dono;
}

char* celular_get_numero(Celular c) {
  StCelular celular = (StCelular) c;
  return celular->numero;
}

char celular_get_operadora(Celular c) {
  StCelular celular = (StCelular) c;
  return celular->operadora;
}

void celular_set_operadora(Celular c, char opdest) {
  StCelular celular = (StCelular) c;
  celular->operadora = opdest;
}

char* celular_get_torre(Celular c) {
  StCelular celular = (StCelular) c;
  return celular->torre;
}

void celular_conecta(Celular c, char *id_torre) {
  StCelular celular = (StCelular) c;
  strcpy(celular->torre, id_torre);
}

void celular_disconecta(Celular c) {
  StCelular celular = (StCelular) c;
  celular->torre[0] = 0;
}

int cmp_celular_torre(Celular c, void *id) {
  return(strcmp(celular_get_torre(c), id) == 0);
}