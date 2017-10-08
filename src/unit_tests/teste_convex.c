#include <stdio.h>
#include "../modules/Convex/Convex.h"
#include "../modules/Hidrante/Hidrante.h"
#include "../modules/Pilha/Pilha.h"
#include "../modules/Lista/Lista.h"
#include "../modules/svg/svg.h"

int main() {
  Lista *l = create_lista();
  Lista *hulls = create_lista();
  int i, j;

  /*
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      insert_first(l, new_hidrante(100 * (i + 1), 100 * (j + 1), "", "red", "black"));
    }
  }
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
    convex_hull(l, p, hidrante_get_x, hidrante_get_y, cmp_hidrante_hidrante_y0);
    insert_first(hulls, p);
  }

  while (length_lista(hulls) > 0) {
    Pilha p = remove_first(hulls);
    while(!empty(p)) {
      Hidrante h = (Hidrante)(pop(p));

      /*
      printf("<circle cx=\"%f\" cy=\"%f\" r=\"16\" fill=\"%s\" stroke=\"%s\"/>\n",
              hidrante_get_x(h),
              hidrante_get_y(h),
              hidrante_get_fill(h),
              hidrante_get_stroke(h));
      printf("<text x=\"%f\" y=\"%f\" fill=\"white\" font-size=\"16\" style=\"z-index:100\">H</text>\n",
              hidrante_get_x(h) - 5,
              hidrante_get_y(h) + 4);
              */

      free(h);
    }
    free(p);
  }

  printf("</svg>");
  return 0;
}
