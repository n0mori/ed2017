#include "geo.h"

double dist(double xa, double ya, double xb, double yb) {
  return sqrt(pow(xa - xb, 2) + pow(ya - yb, 2));
}

int intersec_cc(circ a, circ b) {
  if (dist(a.x, a.y, b.x, b.y) <= a.raio + b.raio) {
    return 1;
  }
  return 0;
}

void extremidades_cc(circ a, circ b, double *extremidades) {
  if (circ_upmost(a) <= circ_upmost(b)) {
    extremidades[0] = circ_upmost(a);
  } else {
    extremidades[0] = circ_upmost(b);
  }
  if (circ_leftmost(a) <= circ_leftmost(b)) {
    extremidades[1] = circ_leftmost(a);
  } else {
    extremidades[1] = circ_leftmost(b);
  }
  if (circ_botmost(a) >= circ_botmost(b)) {
    extremidades[2] = circ_botmost(a);
  } else {
    extremidades[2] = circ_botmost(b);
  }
  if (circ_rightmost(a) >= circ_rightmost(b)) {
    extremidades[3] = circ_rightmost(a);
  } else {
    extremidades[3] = circ_rightmost(b);
  }
}

int intersec_rr(rect a, rect b) {
  if (((a.x >= b.x && a.x <= b.x + b.width) || (b.x >= a.x && b.x <= a.x + a.width)) && ((a.y >= b.y && a.y <= b.y + b.height) || (b.y >= a.y && b.y <= a.y + a.height))) {
    return 1;
  }
  return 0;
}

void extremidades_rr(rect a, rect b, double *extremidades) {
  if (a.y <= b.y) {
    extremidades[0] = a.y;
  } else {
    extremidades[0] = b.y;
  }
  if (a.x <= b.x) {
    extremidades[1] = a.x;
  } else {
    extremidades[1] = b.x;
  }
  if (a.y + a.height >= b.y + b.height) {
    extremidades[2] = a.y + a.height;
  } else {
    extremidades[2] = b.y + b.height;
  }
  if (a.x + a.width >= b.x + b.width) {
    extremidades[3] = a.x + a.width;
  } else {
    extremidades[3] = b.x + b.width;
  }
}
