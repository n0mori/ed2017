#include <stdio.h>
#include "../modules/Lista/Lista.h"
#include "../modules/Geo/Geo.h"

int main() {
  Lista *l = create_lista();
  Node *p;
  Rect *first, *last, *second;
  insert_last(l, new_rect(10, 10, 1, 1, "ayanami"));
  insert_first(l, new_rect(10, 10, 1, 1, "orange"));
  insert_last(l, new_rect(10, 10, 0, 0, "blue"));
  insert_last(l, new_rect(10, 10, 0, 0, "blue"));
  insert_last(l, new_rect(10, 10, 0, 0, "blue"));
  insert_last(l, new_rect(10, 10, 0, 0, "blue"));
  p = l->head->next->next;
  insert_before(l, p, new_rect(10, 10, 0, 0, "before"));
  insert_after(l, p, new_rect(10, 10, 0, 0, "after"));
  insert_last(l, new_rect(10, 10, 0, 0, "blue"));
  insert_last(l, new_rect(30, 30, 0, 0, "green"));
  insert_after(l, l->tail, new_rect(20, 20, 0, 0, "green"));
  insert_first(l, new_rect(100, 100, 0, 0, "brown"));
  /*insert_before(&l, l.head, new_rect(30, 30, 0, 0, "orange"));
  remove_first(&l);
  remove_last(&l);*/

  for (p = l->head; p != NULL; p = p->next) {
    first = (Rect*) get(l, p);
    printf("x: %lf, y: %lf, cor: %s\n", first->width, first->height, first->cor);
  }

  puts("");

  for (p = l->tail; p != NULL; p = p->prev) {
    first = (Rect*) get(l, p);
    printf("x: %lf, y: %lf, cor: %s\n", first->width, first->height, first->cor);
  }

  free(remove_first(l));
  free(remove_last(l));

  free_lista(l);

  return 0;
}
