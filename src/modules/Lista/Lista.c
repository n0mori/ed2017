#include "Lista.h"

Lista create_lista() {
  Lista l;
  l.head = NULL;
  l.tail = NULL;
  return l;
}

int length_lista(Lista *l) {
  /*if (l.head == NULL || l.tail == NULL) {
    return 0;
  }
  Node *n;
  i = 0;
  for (n = head; n->next != NULL; n = n->next) {
    i++;
  }
  return i;*/
  return l->length;
}

void insert_first(Lista *l, void *val) {
  Node *n = malloc(sizeof(Node));
  n->prev = NULL;
  n->val = val;
  n->next = l->head;
  l->head = n;
  l->length++;
  if (l->tail == NULL) {
    l->tail = l->head;
  }
}

void insert_last(Lista *l, void *val) {
  Node *n = malloc(sizeof(Node));
  n->prev = l->tail;
  n->val = val;
  n->next = NULL;
  l->tail = n;
  l->length++;
  if (l->head == NULL) {
    l->head = l->tail;
  }
}

void insert_before(Lista *l, int posic, void *val) {
  if (posic <= 0) {
    insert_first(l, val);
    return;
  }
  if (posic > l->length) {
    insert_last(l, val);
    return;
  }
  int i = 0;
  Node *n, *new;
  for (n = l->head; i < posic; i++) {
    n = n->next;
  }
  new = malloc(sizeof(Node));
  new->prev = n->prev;
  new->val = val;
  new->next = n;
  new->prev->next = new;
  l->length++;
}

void insert_after(Lista *l, int posic, void *val) {
  if (posic < 0) {
    insert_first(l, val);
    return;
  }
  if (posic >= l->length) {
    insert_last(l, val);
    return;
  }
  int i = 0;
  Node *n, *new;
  for (n = l->head; i < posic; i++) {
    n = n->next;
  }
  new = malloc(sizeof(Node));
  new->prev = n->prev;
  new->val = val;
  new->next = n;
  new->prev->next = new;
  l->length++;
}

void remove_first(Lista *l) {
  Node *aux;
  if (l->head == NULL) {
    return;
  }
  if (l->head == l->tail) {
    free(l->head);
    l->head = NULL;
    l->tail = NULL;
    l->length--;
    return;
  }
  aux = l->head;
  l->head = aux->next;
  l->head->prev = NULL;
  l->length--;
  free(aux);
}

void remove_last(Lista *l) {
  Node *aux;
  if (l->tail == NULL) {
    return;
  }
  if (l->head == l->tail) {
    free(l->head);
    l->head == NULL;
    l->tail == NULL;
    l->length--;
    return;
  }
  aux = l->tail;
  l->tail = aux->prev;
  l->tail->next = NULL;
  l->length--;
  free(aux);
}

void remove_at(Lista *l, int posic) {
  Node *aux;
  int i = 0;
  if (posic < 0 || posic >= l->length) {
    return;
  }
  if (posic == 0) {
    remove_first(l);
    return;
  }
  if (posic == l->length - 1) {
    remove_last(l);
    return;
  }
  for (aux = l->head; i < posic && aux->next != l->tail; i++) {
    aux = aux->next;
  }
  aux->prev->next = aux->next;
  aux->next->prev = aux->prev;
  l->length--;
  free(aux);
}

void *get_first(Lista *l) {
  return l->head->val;
}

void *get_last(Lista *l) {
  return l->tail->val;
}

void *get_next(Lista *l, int posic) {
  int i = 0;
  Node *aux;

  if (posic < 0) {
    return get_first(l);
  }
  if (posic >= l->length - 1) {
    return get_last(l);
  }

  for (aux = l->head; i < posic && i < l->length; i++) {
    aux = aux->next;
  }
  return aux->next;
}

void *get_before(Lista *l, int posic) {
  int i = 0;
  Node *aux;

  if (posic < 0) {
    return get_first(l);
  }
  if (posic >= l->length - 1) {
    return get_last(l);
  }

  for (aux = l->head; i < posic && i < l->length; i++) {
    aux = aux->next;
  }
  return aux->prev;
}

void free_lista(Lista *l) {
  Node *aux;
  if (l->head == NULL || l->tail == NULL) {
    return;
  }
  for (aux = l->head; aux->next != NULL; aux = aux->next) {
    if (aux->prev != NULL) {
      free(aux->prev);
    }
  }
  free(l->tail);
}
