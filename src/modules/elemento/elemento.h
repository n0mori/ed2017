#ifndef ELEMENTO__H
#define ELEMENTO__H

/*
Um elemento é uma estrutura que guarda um ponteiro nulo, para o armazenamento de
um elemento de qualquer tipo, e um tipo, que identifica o tipo de elemento.
*/

#include <stdlib.h>

typedef struct e {
  int id;
  char tipo;
  void *dado;
} elemento;

elemento *busca_id(elemento *elementos, int n, int buscado);
void limpa_vetor(elemento *elementos, int n);
void inicializa_elemento(elemento *e);

#endif
