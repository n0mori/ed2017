#include <stdio.h>
#include "modules/Lista/Lista.h"
#include "modules/Geo/Geo.h"

int main() {
  Lista l = create_lista();
  Rect *first, *last;
  insert_first(&l, new_rect(10, 10, 0, 0, "red"));
  insert_last(&l, new_rect(10, 10, 0, 0, "blue"));
  insert_last(&l, new_rect(30, 30, 0, 0, "green"));
  puts("Ola");
  /*insert_after(&l, 21, new_rect(20, 20, 0, 0, "green"));*/
  insert_before(&l, 0, new_rect(30, 30, 0, 0, "orange"));
  remove_first(&l);
  remove_last(&l);

  first = (Rect*) get_first(&l);
  last  = (Rect*) get_last(&l);

  printf("Cor do primeiro: %s\nCor do segundo: %s\n", first->cor, last->cor);

  return 0;
}
