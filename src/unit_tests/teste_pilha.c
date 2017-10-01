#include <stdio.h>
#include "../modules/Pilha/Pilha.h"

int main() {
  Pilha p = new_pilha();
  int i;
  if (empty(p)) {
    puts("pilha vazia");
  }
  for (i = 0; i < 10; i++) {
    push(p, (void*) (i * 10));
  }
  printf("Peekando: %d\n", peek(p));

  while (!empty(p)) {
    printf("Pop! O numero popado foi: %d\n", pop(p));
  }

  free(p);

  return 0;
}
