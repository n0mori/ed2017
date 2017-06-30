#include "Geo.h"

double dist(double xa, double ya, double xb, double yb) {
  return sqrt(pow(xa - xb, 2) + pow(ya - yb, 2));
}

int intersec_cc(Circ a, Circ b) {
  if (dist(a.x, a.y, b.x, b.y) <= a.raio + b.raio) {
    return 1;
  }
  return 0;
}

void extremidades_cc(Circ a, Circ b, double *extremidades) {
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

int intersec_rr(Rect a, Rect b) {
  if (((a.x >= b.x && a.x <= b.x + b.width) || (b.x >= a.x && b.x <= a.x + a.width)) && ((a.y >= b.y && a.y <= b.y + b.height) || (b.y >= a.y && b.y <= a.y + a.height))) {
    return 1;
  }
  return 0;
}

void extremidades_rr(Rect a, Rect b, double *extremidades) {
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

int intersec_cr(Circ c, Rect r) {
  if (rect_interno(r, c.x, c.y)) { return 1; }
  if (c.x >= r.x && c.x <= r.x && dist(c.x, c.y, c.x, r.y) <= c.raio) { return 1; }
  if (c.x >= r.x && c.x <= r.x && dist(c.x, c.y, c.x, r.y + r.height) <= c.raio) { return 1; }
  if (c.y >= r.y && c.y <= r.y && dist(c.x, c.y, c.y, r.x) <= c.raio) { return 1; }
  if (c.y >= r.y && c.y <= r.y && dist(c.x, c.y, c.y, r.x + r.width) <= c.raio) { return 1; }
  if (circ_interno(c, r.x, r.y)) { return 1; }
  if (circ_interno(c, r.x, r.y + r.height)) { return 1; }
  if (circ_interno(c, r.x + r.width, r.y)) { return 1; }
  if (circ_interno(c, r.x + r.width, r.y + r.height)) { return 1; }
  return 0;
}

void extremidades_cr(Circ c, Rect r, double *extremidades) {
  if (circ_upmost(c) <= r.y) {
    extremidades[0] = circ_upmost(c);
  } else {
    extremidades[0] = r.y;
  }
  if (circ_leftmost(c) <= r.x) {
    extremidades[1] = circ_leftmost(c);
  } else {
    extremidades[1] = r.x;
  }
  if (circ_botmost(c) >= r.y + r.height) {
    extremidades[2] = circ_botmost(c);
  } else {
    extremidades[2] = r.y + r.height;
  }
  if (circ_rightmost(c) >= r.x + r.width) {
    extremidades[3] = circ_rightmost(c);
  } else {
    extremidades[3] = r.x + r.width;
  }
}
