#include "../modules/Geo/Geo.h"
#include <stdio.h>

int main() {
  Rect *r = new_rect(100, 50, 100, 390, "yellow");
  Rect *r2 = new_rect(30, 50, 150, 430, "blue");

  printf("%d\n", intersec_rr(*r, *r2));

  return 0;
}
