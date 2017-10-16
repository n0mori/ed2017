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
#include <stdio.h>

Lista *create_lista();
int length_lista(Lista *l);
int insert_first(Lista *l, void *val);
int insert_last(Lista *l, void *val);
int insert_after(Lista *l, Node *posic, void *val);
int insert_before(Lista *l, Node *posic, void *val);
void *remove_first(Lista *l);
void *remove_last(Lista *l);
void *remove_at(Lista *l, Node *posic);
Node *get_first(Lista *l);
Node *get_last(Lista *l);
Node *get_next(Lista *l, Node *posic);
Node *get_before(Lista *l, Node *posic);
void *get(Lista *l, Node *posic);
void free_lista(Lista *l);
void *search_lista(Lista *l, int (*compar)(void* a, void *b), void *comparado);

#endif
