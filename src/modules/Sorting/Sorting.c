#include "Sorting.h"

void **lista_to_array(Lista l) {
  int len = length_lista(l);
  int i = 0;
  void **arr = malloc(sizeof(void*) * len);
  Node n;
  for (n = get_first(l); n != NULL; n = get_next(l, n)) {
    arr[i++] = get(l, n);
  }
  return arr;
}

void array_to_lista(void **arr, int length, Lista l) {
  int i;
  while (length_lista(l) > 0) remove_last(l);
  for (i = 0; i < length; i++) {
    insert_last(l, arr[i]);
  }
}

void sort_lista(Lista l, int (*compar)(void *a, void *b)) {
  int length = length_lista(l);
  void **arr = lista_to_array(l);

  quick_sort(arr, 0, length, compar);

  array_to_lista(arr, length, l);
  free(arr);
}

int particiona(void **vetor, int inicio, int fim, int (*compar)(void *a, void *b)) {
  void *pivo = vetor[fim - 1];
  void *aux;
  int i, parede;
  parede = inicio;
  for (i = inicio; i < fim; i++) {
    if (compar(vetor[i], pivo) <= 0) {
      aux = vetor[i];
      vetor[i] = vetor[parede];
      vetor[parede] = aux;
      parede++;
    }
  }
  return parede - 1;
}

void quick_sort(void **vetor, int inicio, int fim, int (*compar)(void *a, void *b)) {
  if (fim - inicio > 1) {
    int meio = particiona(vetor, inicio, fim, compar);
    quick_sort(vetor, inicio, meio, compar);
    quick_sort(vetor, meio, fim, compar);
  }
}
