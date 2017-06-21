#include "coord.h"

double dist_coords(coord a, coord b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double dist_ponto(coord a, double x, double y) {
  return sqrt(pow(a.x - x, 2) + pow(a.y - y, 2));
}
