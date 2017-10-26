#include <stdio.h>
#include "../modules/Convex/Convex.h"
#include "../modules/Torre/Torre.h"
#include "../modules/Pilha/Pilha.h"
#include "../modules/Lista/Lista.h"
#include "../modules/svg/svg.h"

int main() {
  Lista *l = create_lista();
  Lista *hulls = create_lista();
  int i, j;

  /*
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      insert_first(l, new_hidrante(100 * (i + 1), 100 * (j + 1), "", "red", "black"));
    }
  }
  */

  /*
  insert_first(l, new_hidrante(10 , 10 , "", "red", "black"));
  insert_first(l, new_hidrante(50, 11, "", "red", "black"));
  insert_first(l, new_hidrante(0 , 50, "", "red", "black"));
  insert_first(l, new_hidrante(0 , 70, "", "red", "black"));
  */

  insert_first(l, new_hidrante(10, 10, "", "red", "black"));
  insert_first(l, new_hidrante(40, 70, "", "red", "black"));
  insert_first(l, new_hidrante(30, 20, "", "red", "black"));
  insert_first(l, new_hidrante(60, 40, "", "red", "black"));
  insert_first(l, new_hidrante(90, 70, "", "red", "black"));
  insert_first(l, new_hidrante(100, 90, "", "red", "black"));
  printf("<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

  while (length_lista(l) > 0) {
    Pilha p = new_pilha();
    convex_hull(l, p, hidrante_get_x, hidrante_get_y, cmp_hidrante_hidrante_y0, cmp_hidrante_hidrante_x0);
    insert_first(hulls, p);
  }

  while (length_lista(hulls) > 0) {
    Pilha p = remove_first(hulls);
    printf("<polygon stroke=\"fuchsia\" fill=\"fuchsia\" fill-opacity=\"0.2\" points=\"");
    while (!empty(p)) {
      Hidrante pt = pop(p);
      printf("%f, %f ", hidrante_get_x(pt), hidrante_get_y(pt));
    }
  printf("\" />");
    free(p);
  }

  printf("</svg>");
  return 0;
}
