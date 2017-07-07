#include "ListaEstatica.h"

Elemento *busca_id(ListaEstatica l, int n, int buscado) {
  int i, id_atual;
  for (i = 0; i < n; i++) {
    id_atual = l[i].id;
    if (id_atual == buscado) {
      return l + i;
    }
  }
  return NULL;
}

void limpa_vetor(ListaEstatica l, int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (l[i].dado != NULL) {
      free(l[i].dado);
      l[i].tipo = 0;
    }
  }
}

ListaEstatica cria_lista_estatica(int tamanho) {
  int i;
  ListaEstatica l = (ListaEstatica) malloc(sizeof(Elemento) * tamanho);
  for (i = 0; i < tamanho; i++) {
    inicializa_elemento(l + i);
  }
  return l;
}

void adiciona_lista_estatica(ListaEstatica l, int n, Elemento e) {
  l[n] = e;
}
