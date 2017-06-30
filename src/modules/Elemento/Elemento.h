#ifndef ELEMENTO__H
#define ELEMENTO__H

/*
Um Elemento é uma estrutura que guarda um ponteiro nulo, para o armazenamento de
um Elemento de qualquer tipo, e um tipo, que identifica o tipo de Elemento.
*/

#include <stdlib.h>

typedef struct e {
  int id;
  char tipo;
  void *dado;
} Elemento;

Elemento *busca_id(Elemento *elementos, int n, int buscado);
void limpa_vetor(Elemento *elementos, int n);
void inicializa_elemento(Elemento *e);

#endif
