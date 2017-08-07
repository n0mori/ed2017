#include <stdio.h>
#include "modules/Lista/Lista.h"
#include "modules/Quadra/Quadra.h"

int main() {
  Lista *l = create_lista();
  Node *n;
  Quadra *q = new_quadra(10, 10, 10, 10, "ayanami", "white", "blue");
  Quadra *a;
  printf("%d\n", q);
  insert_first(l, q);

  n = l->head;
  printf("%d\n", n->val);
  a = get(l, n);
  printf("%d\n", a);
  printf("%s\n", a->cep);

  free_lista(l);
}
