#include "Lista.h"

Lista *create_lista() {
  Lista *l = malloc(sizeof(Lista));
  l->head = NULL;
  l->tail = NULL;
  l->length = 0;
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

int insert_first(Lista *l, void *val) {
  Node *n = malloc(sizeof(Node));
  n->prev = NULL;
  n->val = val;
  n->next = l->head;
  l->head = n;
  l->length++;
  if (n->next != NULL) {
    n->next->prev = l->head;
  }
  if (l->tail == NULL) {
    l->tail = l->head;
  }
  return 1;
}

int insert_last(Lista *l, void *val) {
  Node *n;
  if (length_lista(l) == 0) {
    insert_first(l, val);
    return 1;
  }
  n = malloc(sizeof(Node));
  n->prev = l->tail;
  n->prev->next = n;
  n->val = val;
  n->next = NULL;
  l->tail = n;
  l->length++;
  if (l->head == NULL) {
    l->head = l->tail;
  }
  return 1;
}

int insert_before(Lista *l, Node *posic, void *val) {
  Node *new;
  if (posic == l->head) {
    insert_first(l, val);
    return 1;
  }
  new = malloc(sizeof(Node));
  new->prev = posic->prev;
  new->prev->next = new;
  new->val = val;
  new->next = posic;
  posic->prev = new;
  l->length++;
  return 1;
}

int insert_after(Lista *l, Node *posic, void *val) {
  Node *new;
  if (posic == l->tail) {
    insert_last(l, val);
    return 1;
  }
  new = malloc(sizeof(Node));
  new->next = posic->next;
  posic->next = new;
  new->val = val;
  new->prev = posic;
  new->next->prev = new;
  l->length++;
  return 1;
}

void *remove_first(Lista *l) {
  Node *aux;
  void *p;
  p = l->head->val;
  if (l->head == NULL) {
    return NULL;
  }
  if (l->head == l->tail) {
    free(l->head);
    l->head = NULL;
    l->tail = NULL;
    l->length--;
    return p;
  }
  aux = l->head;
  l->head = aux->next;
  l->head->prev = NULL;
  l->length--;
  free(aux);
  return p;
}

void *remove_last(Lista *l) {
  Node *aux;
  void *p = l->tail->val;
  if (l->length == 0 || l->tail == NULL) {
    return NULL;
  }
  if (l->head == l->tail) {
    free(l->head);
    l->head == NULL;
    l->tail == NULL;
    l->length--;
    return p;
  }
  aux = l->tail;
  l->tail = aux->prev;
  l->tail->next = NULL;
  l->length--;
  free(aux);
  return p;
}

void *remove_at(Lista *l, Node *posic) {
  void *p = posic->val;
  if (posic == l->head) {
    p = remove_first(l);
    return p;
  }
  if (posic == l->tail) {
    p = remove_last(l);
    return p;
  }
  posic->prev->next = posic->next;
  posic->next->prev = posic->prev;
  l->length--;
  free(posic);
  return p;
}

Node *get_first(Lista *l) {
  return l->head;
}

Node *get_last(Lista *l) {
  return l->tail;
}

Node *get_next(Lista *l, Node *posic) {
  return posic->next;
}

Node *get_before(Lista *l, Node *posic) {
  return posic->prev;
}

void *get(Lista *l, Node *posic) {
  return posic->val;
}

void free_lista(Lista *l) {
  /*Node *aux;
  if (l->head == NULL || l->tail == NULL) {
    return;
  }
  for (aux = l->head; aux->next != NULL; aux = aux->next) {
    if (aux->prev != NULL) {
      free(aux->prev);
    }
  }
  free(l->tail);
  */
  for (; l->length > 0;) {
    void *val = remove_first(l);
    if (val != NULL) {
      free(val);
    }
  }

  free(l);
}
