#include "Address.h"

typedef struct address {
  char cep[100];
  char face;
  int numero;
  char complemento[100];
}* StAddr;

Address new_address(char *cep, char face, int numero, char *complemento) {
  StAddr a = malloc(sizeof(struct address));
  strcpy(a->cep, cep);
  a->face = face;
  a->numero = numero;
  strcpy(a->complemento, complemento);
  return a;    
}

char *address_get_cep(Address a) {
  StAddr addr = (StAddr) a;
  return addr->cep;
}

char address_get_face(Address a) {
  StAddr addr = (StAddr) a;
  return addr->face;
}

int  address_get_numero(Address a) {
  StAddr addr = (StAddr) a;
  return addr->numero;
}

char *address_get_complemento(Address a) {
  StAddr addr = (StAddr) a;
  return addr->complemento;
}