#ifndef LISTA__H
#define LISTA__H

/*
Uma lista é uma coleção de objetos.
*/

typedef struct node {
  struct node *prev;
  void *val;
  struct node *next;
} Node;

typedef struct lista {
  Node *head;
  Node *tail;
  int length;
} Lista;

#include <stdlib.h>

Lista create_lista();
int length_lista(Lista *l);
void insert_first(Lista *l, void *val);
void insert_last(Lista *l, void *val);
void insert_before(Lista *l, int posic, void *val);
void insert_after(Lista *l, int posic, void *val);
void remove_first(Lista *l);
void remove_last(Lista *l);
void remove_at(Lista *l, int posic);
void *get_first(Lista *l);
void *get_last(Lista *l);
void *get_next(Lista *l, int posic);
void *get_before(Lista *l, int posic);
void *get_index(Lista *l, int posic);
void free_lista(Lista *l);

#endif
