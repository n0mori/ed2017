#include "svg.h"

void print_svg_circ(FILE *fsvg, Circ *c) {
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"%s\"/>\n", c->x, c->y, c->raio, c->cor);
}

void print_svg_rect(FILE *fsvg, Rect *r) {
  fprintf(fsvg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\"/>\n", r->x, r->y, r->width, r->height, r->cor);
}

void print_svg_quadra(FILE *fsvg, Quadra *q) {
  fprintf(fsvg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\"/>\n", q->x, q->y, q->width, q->height, q->fill, q->stroke);
  fprintf(fsvg, "<text x=\"%lf\" y=\"%lf\" fill=\"red\" font-size=\"16\" style=\"z-index:100\">%s</text>\n", q->x, q->y + 16, q->cep);
}

void print_svg_hidrante(FILE *fsvg, Hidrante *h) {
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"16\" fill=\"%s\" stroke=\"%s\"/>\n", h->x, h->y, h->fill, h->stroke);
  fprintf(fsvg, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-size=\"16\" style=\"z-index:100\">H</text>\n", h->x - 5, h->y + 4);
}

void print_svg_semaforo(FILE *fsvg, Semaforo *s) {
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"16\" fill=\"%s\" stroke=\"%s\"/>\n", s->x, s->y, s->fill, s->stroke);
  fprintf(fsvg, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-size=\"16\" style=\"z-index:100\">S</text>\n", s->x - 5, s->y + 4);
}

void print_svg_torre(FILE *fsvg, Torre *t) {
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"16\" fill=\"%s\" stroke=\"%s\"/>\n", t->x, t->y, t->fill, t->stroke);
  fprintf(fsvg, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-size=\"16\" style=\"z-index:100\">T</text>\n", t->x - 5, t->y + 4);
}

void print_sobreposto(FILE *fsvg, double *extremidades) {
  fprintf(fsvg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" style=\"stroke:pink;stroke-width:3;stroke-dasharray:5,5;z-index:1000\"/>\n", extremidades[1], extremidades[0], extremidades[3] - extremidades[1], extremidades[2] - extremidades[0]);
  fprintf(fsvg, "<text x=\"%lf\" y=\"%lf\" fill=\"red\" font-size=\"16\" style=\"z-index:100\">sobrepoe</text>\n", extremidades[1], extremidades[0] + 16);
}

void print_circ_points(FILE *fsvg, Circ *c, char *cor) {
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\"/>\n", c->x, c->y, cor);
}

void print_rect_points(FILE *fsvg, Rect *r, char *cor) {
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\"/>\n", r->x, r->y, cor);
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\"/>\n", r->x + r->width, r->y, cor);
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\"/>\n", r->x, r->y + r->height, cor);
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\"/>\n", r->x + r->width, r->y + r->height, cor);
}

void print_svg_cidade(char *svg, Cidade c) {
  Node *n;

  FILE *file_svg = fopen(svg, "w");
  fprintf(file_svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

  for (n = get_first(c.quadras); n != NULL; n = get_next(c.quadras, n)) {
    Quadra *q = (Quadra*) get(c.quadras, n);
    print_svg_quadra(file_svg, q);
  }

  for (n = get_first(c.hidrantes); n != NULL; n = get_next(c.hidrantes, n)) {
    Hidrante *h = (Hidrante*) get(c.hidrantes, n);
    print_svg_hidrante(file_svg, h);
  }

  for (n = get_first(c.semaforos); n != NULL; n = get_next(c.semaforos, n)) {
    Semaforo *s = (Semaforo*) get(c.semaforos, n);
    print_svg_semaforo(file_svg, s);
  }

  for (n = get_first(c.torres); n != NULL; n = get_next(c.torres, n)) {
    Torre *t = (Torre*) get(c.torres, n);
    print_svg_torre(file_svg, t);
  }

  for (n = get_first(c.formas); n != NULL; n = get_next(c.formas, n)) {
    Elemento *e = (Elemento*) get(c.formas, n);
    if (e->tipo == 'c') {
      Circ *c = (Circ*) e->dado;
      print_svg_circ(file_svg, c);
    } else if (e->tipo == 'r') {
      Rect *r = (Rect*) e->dado;
      print_svg_rect(file_svg, r);
    }
  }
  fprintf(file_svg, "</svg>");
  fclose(file_svg);
}
