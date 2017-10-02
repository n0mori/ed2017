#include <stdio.h>
#include "../modules/Lista/Lista.h"
#include "../modules/Sorting/Sorting.h"
#include "../modules/Comparacao/Comparacao.h"
#include "../modules/Quadra/Quadra.h"

int comparando(void *a, void *b) {
  if (a < b) {
    return -1;
  } else if (a == b) {
    return 0;
  } else {
    return 1;
  }
}

int main() {
  int i;
  Lista *l = create_lista();
  Node *n;
  void **arr;
  for (i = 0; i < 10; i++) {
    insert_last(l, new_quadra(0, 100 - i, 0, 0, "", "", ""));
  }

  sort_lista(l, cmp_quadra_quadra_y0);

  for (n = get_first(l); n != NULL; n = get_next(l, n)) {
    printf("%f\n", quadra_get_y(get(l, n)));
  }
  /*
  arr = lista_to_array(l);

  for (i = 0; i < length_lista(l); i++) {
    int *d = arr[i];
    printf("printando da nova array: %d\n", d);
  }

  free(arr);
  */
  return 0;
}
