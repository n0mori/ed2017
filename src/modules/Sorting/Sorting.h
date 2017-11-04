#ifndef SORTING__H
#define SORTING__H

/*Esse módulo é responsavel por fazer ordenações. Também possui algumas funções
que auxiliam nas ordenações*/

#include "../Lista/Lista.h"

void **lista_to_array(Lista l);
void array_to_lista(void **arr, int length, Lista l);
void sort_lista(Lista l, int (*compar)(void *a, void *b));
void merge_sort(void **arr, int start, int end, int (*compar)(void *a, void *b));
int particiona(void **vetor, int inicio, int fim, int (*compar)(void *a, void *b));
void quick_sort(void **vetor, int inicio, int fim, int (*compar)(void *a, void *b));

#endif
