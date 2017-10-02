#include <stdio.h>
#include "../modules/Quadtree/Quadtree.h"
#include "../modules/Quadra/Quadra.h"
#include "../modules/svg/svg.h"

void printa(void *a) {
  Quadra *q = (Quadra*) a;
  printf("x: %f y: %f cep: %s\n", q->x, quadra_get_y(q), q->cep);
}

int main() {
  Quadtree q = new_quadtree();
  int cmp = 0;

  cmp += quadtree_insert(q, new_quadra(100, 150, 10, 10, "1", "black", "red"), 100, 150);
  cmp += quadtree_insert(q, new_quadra(400, 160, 10, 10, "2", "black", "red"), 400, 160);
  cmp += quadtree_insert(q, new_quadra(50, 170, 10, 10, "3", "black", "red"), 50, 170);
  cmp += quadtree_insert(q, new_quadra(90, 120, 10, 10, "4", "black", "red"), 90, 120);
  cmp += quadtree_insert(q, new_quadra(10, 130, 10, 10, "5", "black", "red"), 10, 130);
  cmp += quadtree_insert(q, new_quadra(80, 250, 10, 10, "6", "black", "red"), 80, 250);

  FILE *f = fopen("arquivo.txt", "w+");
  quadtree_percorre_print(quadtree_root(q), f, print_svg_quadra);

  printf("%d\n", cmp);

  return 0;
}
