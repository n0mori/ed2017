#include "Morador.h"

typedef struct morador {
  char cpf[100];
  char cep[100];
  char face;
  int  numero;
}* StMorador;

Morador new_morador(char *cpf, char *cep, char face, int numero) {
  StMorador m = malloc(sizeof(struct morador));
  strcpy(m->cpf, cpf);
  strcpy(m->cep, cep);
  m->face = face;
  m->numero = numero;
  return m;
}

char *morador_get_cpf(Morador m) {
  StMorador morador = (StMorador) m;
  return morador->cpf;
}

char *morador_get_cep(Morador m) {
  StMorador morador = (StMorador) m;
  return morador->cep;
}

char morador_get_face(Morador m) {
  StMorador morador = (StMorador) m;
  return morador->face;
}

int morador_get_numero(Morador m) {
  StMorador morador = (StMorador) m;
  return morador->numero;
}

int cmp_morador_cpf(Morador m, void *cpf) {
  return strcmp(morador_get_cpf(m), cpf) == 0;
}