#include "Morador.h"

typedef struct morador {
  char cpf[100];
  Address address;
}* StMorador;

Morador new_morador(char *cpf, char *cep, char face, int numero, char *complemento) {
  StMorador m = malloc(sizeof(struct morador));
  strcpy(m->cpf, cpf);
  m->address = new_address(cep, face, numero, complemento);
  return m;
}

Address morador_get_address(Morador m) {
  StMorador morador = (StMorador) m;
  return morador->address;
}

char *morador_get_cpf(Morador m) {
  StMorador morador = (StMorador) m;
  return morador->cpf;
}

char *morador_get_cep(Morador m) {
  return address_get_cep(morador_get_address(m));
}

char morador_get_face(Morador m) {
  return address_get_face(morador_get_address(m));
}

int morador_get_numero(Morador m) {
  return address_get_numero(morador_get_address(m));
}

int cmp_morador_cpf(Morador m, void *cpf) {
  return strcmp(morador_get_cpf(m), cpf) == 0;
}

int cmp_morador_cep(Morador m, void *cep) {
  return strcmp(morador_get_cep(m), cep) == 0;
}

void free_morador(Morador m) {
  free(morador_get_address(m));
  free(m);
}

void morador_imprime_dados(Morador m, Pessoa p, FILE *out) {
  /* nome, sobrenome, cep, face, numero, celular, operadora */
  fprintf(out, "%s %s %s %c %d %s %c\n", 
          pessoa_get_nome(p), 
          pessoa_get_sobrenome(p), 
          morador_get_cep(m), 
          morador_get_face(m), 
          morador_get_numero(m),
          celular_get_numero(pessoa_get_celular(p)),
          celular_get_operadora(pessoa_get_celular(p)));
}