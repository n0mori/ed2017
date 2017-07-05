#include "Elemento.h"

Elemento *busca_id(Elemento *elementos, int n, int buscado) {
  int i, id_atual;
  for (i = 0; i < n; i++) {
    id_atual = elementos[i].id;
    if (id_atual == buscado) {
      return elementos + i;
    }
  }
  return NULL;
}

void limpa_vetor(Elemento *elementos, int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (elementos[i].dado != NULL) {
      free(elementos[i].dado);
      elementos[i].tipo = 0;
    }
  }
}

void inicializa_elemento(Elemento *e) {
  e->id = -1;
  e->tipo = 0;
  e->dado = NULL;
}
