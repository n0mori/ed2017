#include "Pilha.h"

typedef struct stStackNode {
  void *valor;
  struct stStackNode *next;
}* StackNode;

typedef struct StStack {
  int length;
  StackNode top;
}* Stack;

Pilha new_pilha() {
  Pilha p = malloc(sizeof(struct stStackNode));
  Stack s = (Stack) p;
  s->length = 0;
  s->top = NULL;
  return p;
}

int empty(Pilha p) {
  Stack s = (Stack) p;
  return s->length == 0;
}

void push(Pilha p, void *e) {
  Stack s = (Stack) p;
  StackNode n = malloc(sizeof(StackNode));
  n->next = s->top;
  n->valor = e;
  s->top = n;
  s->length++;
}

void *pop(Pilha p) {
  if (!empty(p)) {
    Stack s = (Stack) p;
    StackNode n = s->top;
    void *v = n->valor;
    s->top = n->next;
    s->length--;
    free(n);
    return v;
  }
  return NULL;
}

void *peek(Pilha p) {
  Stack s = (Stack) p;
  return s->top->valor;
}
