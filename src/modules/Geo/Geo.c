#include "Geo.h"

int intersec_cc(Circ a, Circ b) {
  if (distancia(a.x, a.y, b.x, b.y) <= a.raio + b.raio) {
    return 1;
  }
  return 0;
}

double distancia(double xa, double ya, double xb, double yb) {
  double d = pow(xa - xb, 2) + pow(ya - yb, 2);
  double dist = sqrt(d);
  return dist;
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
  if (((a.x >= b.x && a.x <= b.x + b.width) ||
       (b.x >= a.x && b.x <= a.x + a.width)) &&
       ((a.y >= b.y && a.y <= b.y + b.height) ||
       (b.y >= a.y && b.y <= a.y + a.height))) {
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
  if (c.x >= r.x && c.x <= r.x && distancia(c.x, c.y, c.x, r.y) <= c.raio) { return 1; }
  if (c.x >= r.x && c.x <= r.x && distancia(c.x, c.y, c.x, r.y + r.height) <= c.raio) { return 1; }
  if (c.y >= r.y && c.y <= r.y && distancia(c.x, c.y, c.y, r.x) <= c.raio) { return 1; }
  if (c.y >= r.y && c.y <= r.y && distancia(c.x, c.y, c.y, r.x + r.width) <= c.raio) { return 1; }
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

int circ_interno(Circ c, double x, double y) {
  double d = distancia(c.x, c.y, x, y);
  /*d = sqrt(pow(c.x - x, 2) + pow(c.x - y, 2));*/
  if (d <= c.raio) {
    return 1;
  } else {
    return 0;
  }
}

int rect_interno(Rect r, double x, double y) {
  if (x >= r.x && x <= r.x + r.width && y >= r.y && y <= r.y + r.height) {
    return 1;
  }
  return 0;
}

int rect_inside_circ(Rect r, Circ c) {
  if (circ_interno(c, r.x, r.y) &&
      circ_interno(c, r.x + r.width, r.y) &&
      circ_interno(c, r.x, r.y + r.height) &&
      circ_interno(c, r.x + r.width, r.y + r.height)) {
    return 1;
  }
  return 0;
}

int rect_inside_rect(Rect in, Rect out) {
  if (rect_interno(out, in.x, in.y) &&
      rect_interno(out, in.x + in.width, in.y) &&
      rect_interno(out, in.x, in.y + in.height) &&
      rect_interno(out, in.x + in.width, in.y + in.height)) {
    return 1;
  }
  return 0;
}

double area_pilha_pontos(Pilha p) {
  Lista *pontos = create_lista();
  Node *n;
  double area, soma1, soma2;

  soma1 = 0;
  soma2 = 0;

  while (!empty(p)) {
    insert_last(pontos, pop(p));
  }

  insert_last(pontos, get(pontos, get_first(pontos)));

  for (n = get_first(pontos); get_next(pontos, n) != NULL; n = get_next(pontos, n)) {
    Ponto a, next;
    a = get(pontos, n);
    next = get(pontos, get_next(pontos, n));
    soma1 += get_x(a) * get_y(next);
    soma2 += get_y(a) * get_x(next);
  }

  remove_first(pontos);
  while (length_lista(pontos) > 0) {
    free(remove_first(pontos));
  }

  area = (soma1 - soma2) / 2;
  return area;
}
