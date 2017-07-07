#ifndef ELEMENTO__H
#define ELEMENTO__H

/*
Um Elemento é uma estrutura que guarda um ponteiro nulo, para o armazenamento de
um objeto de qualquer tipo, e um tipo, que identifica o tipo do objeto.
*/

#include <stdlib.h>

typedef struct e {
  int id;
  char tipo;
  void *dado;
} Elemento;

void inicializa_elemento(Elemento *e);
int get_elemento_id(Elemento e);
char get_elemento_tipo(Elemento e);
void *get_elemento_dado(Elemento e);
Elemento novo_elemento(int id, char tipo, void *p);

#endif
