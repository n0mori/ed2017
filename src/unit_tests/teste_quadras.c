#include <stdio.h>
#include "../modules/Quadra/Quadra.h"

int main() {
  Quadra q = new_quadra(10, 20, 30, 40, "ayanami", "white", "blue");

  printf("%f\n", quadra_get_x(q));
  printf("%f\n", quadra_get_y(q));
  printf("%f\n", quadra_get_width(q));
  printf("%f\n", quadra_get_height(q));
  printf("%s\n", quadra_get_cep(q));
  printf("%s\n", quadra_get_fill(q));
  printf("%s\n", quadra_get_stroke(q));

  free(q);

  return 0;
}
