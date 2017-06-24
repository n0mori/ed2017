#include "coord.h"

double dist(double xa, double ya, double xb, double yb) {
  return sqrt(pow(xa - xb, 2) + pow(ya - yb, 2));
}

double dist_cc(coord a, coord b) {
  return dist(a.x, a.y, b.x, b.y);
}

double dist_cp(coord a, double x, double y) {
  return dist(a.x, a.y, x, y);
}
