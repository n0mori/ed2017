#include "svg.h"

void print_svg_circ(FILE *fsvg, Circ *c) {
  fprintf(fsvg, "<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\"/>\n", c->x, c->y, c->raio, c->cor);
}

void print_svg_rect(FILE *fsvg, Rect *r) {
  fprintf(fsvg, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\"/>\n", r->x, r->y, r->width, r->height, r->cor);
}

void print_svg_quadra(FILE *fsvg, Quadra q) {
  fprintf(fsvg, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\"/>\n",
          quadra_get_x(q),
          quadra_get_y(q),
          quadra_get_width(q),
          quadra_get_height(q),
          quadra_get_fill(q),
          quadra_get_stroke(q));
  fprintf(fsvg, "<text x=\"%f\" y=\"%f\" fill=\"red\" font-size=\"16\" style=\"z-index:100\">%s</text>\n",
          quadra_get_x(q),
          quadra_get_y(q) + 16,
          quadra_get_cep(q));
}

void print_svg_hidrante(FILE *fsvg, Hidrante h) {
  fprintf(fsvg, "<circle cx=\"%f\" cy=\"%f\" r=\"16\" fill=\"%s\" stroke=\"%s\"/>\n",
          hidrante_get_x(h),
          hidrante_get_y(h),
          hidrante_get_fill(h),
          hidrante_get_stroke(h));
  fprintf(fsvg, "<text x=\"%f\" y=\"%f\" fill=\"white\" font-size=\"16\" style=\"z-index:100\">H</text>\n",
          hidrante_get_x(h) - 5,
          hidrante_get_y(h) + 4);
}

void print_svg_semaforo(FILE *fsvg, Semaforo s) {
  fprintf(fsvg, "<circle cx=\"%f\" cy=\"%f\" r=\"16\" fill=\"%s\" stroke=\"%s\"/>\n",
          semaforo_get_x(s),
          semaforo_get_y(s),
          semaforo_get_fill(s),
          semaforo_get_stroke(s));
  fprintf(fsvg, "<text x=\"%f\" y=\"%f\" fill=\"white\" font-size=\"16\" style=\"z-index:100\">S</text>\n",
          semaforo_get_x(s) - 5,
          semaforo_get_y(s) + 4);
}

void print_svg_torre(FILE *fsvg, Torre t) {
  fprintf(fsvg, "<circle cx=\"%f\" cy=\"%f\" r=\"16\" fill=\"%s\" stroke=\"%s\"/>\n",
          torre_get_x(t),
          torre_get_y(t),
          torre_get_fill(t),
          torre_get_stroke(t));
  fprintf(fsvg, "<text x=\"%f\" y=\"%f\" fill=\"white\" font-size=\"16\" style=\"z-index:100\">T</text>\n",
          torre_get_x(t) - 5,
          torre_get_y(t) + 4);
}

void print_sobreposto(FILE *fsvg, double *extremidades) {
  fprintf(fsvg, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"none\" style=\"stroke:pink;stroke-width:3;stroke-dasharray:5,5;z-index:1000\"/>\n", extremidades[1], extremidades[0], extremidades[3] - extremidades[1], extremidades[2] - extremidades[0]);
  fprintf(fsvg, "<text x=\"%f\" y=\"%f\" fill=\"red\" font-size=\"16\" style=\"z-index:100\">sobrepoe</text>\n", extremidades[1], extremidades[0] + 16);
}

void print_circ_points(FILE *fsvg, Circ *c, char *cor) {
  fprintf(fsvg, "<circle cx=\"%f\" cy=\"%f\" r=\"5\" fill=\"%s\"/>\n", c->x, c->y, cor);
}

void print_rect_points(FILE *fsvg, Rect *r, char *cor) {
  fprintf(fsvg, "<circle cx=\"%f\" cy=\"%f\" r=\"5\" fill=\"%s\"/>\n", r->x, r->y, cor);
  fprintf(fsvg, "<circle cx=\"%f\" cy=\"%f\" r=\"5\" fill=\"%s\"/>\n", r->x + r->width, r->y, cor);
  fprintf(fsvg, "<circle cx=\"%f\" cy=\"%f\" r=\"5\" fill=\"%s\"/>\n", r->x, r->y + r->height, cor);
  fprintf(fsvg, "<circle cx=\"%f\" cy=\"%f\" r=\"5\" fill=\"%s\"/>\n", r->x + r->width, r->y + r->height, cor);
}

void print_svg_cidade(char *svg, Cidade c) {
  Node n;
  Lista ruas = grafo_all_edges(c.vias);

  FILE *file_svg = fopen(svg, "w");
  fprintf(file_svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

  /*
  Node *n;
  for (n = get_first(c.lista_quadras); n != NULL; n = get_next(c.lista_quadras, n)) {
    Quadra *q = (Quadra*) get(c.lista_quadras, n);
    print_svg_quadra(file_svg, q);
  }

  for (n = get_first(c.lista_hidrantes); n != NULL; n = get_next(c.lista_hidrantes, n)) {
    Hidrante *h = (Hidrante*) get(c.lista_hidrantes, n);
    print_svg_hidrante(file_svg, h);
  }

  for (n = get_first(c.lista_semaforos); n != NULL; n = get_next(c.lista_semaforos, n)) {
    Semaforo *s = (Semaforo*) get(c.lista_semaforos, n);
    print_svg_semaforo(file_svg, s);
  }

  for (n = get_first(c.lista_torres); n != NULL; n = get_next(c.lista_torres, n)) {
    Torre *t = (Torre*) get(c.lista_torres, n);
    print_svg_torre(file_svg, t);
  }

  for (n = get_first(c.lista_formas); n != NULL; n = get_next(c.lista_formas, n)) {
    Elemento *e = (Elemento*) get(c.lista_formas, n);
    if (e->tipo == 'c') {
      Circ *c = (Circ*) e->dado;
      print_svg_circ(file_svg, c);
    } else if (e->tipo == 'r') {
      Rect *r = (Rect*) e->dado;
      print_svg_rect(file_svg, r);
    } else if (e->tipo == 'e') {
      Rect *r = (Rect*) e->dado;
      double extremidades[4];
      extremidades[1] = r->x;
      extremidades[0] = r->y;
      extremidades[3] = r->x + r->height;
      extremidades[2] = r->y + r->width;
      print_sobreposto(file_svg, extremidades);
    }
  }
  */

  quadtree_percorre_print(quadtree_root(c.qt_quadras), file_svg, print_svg_quadra);
  quadtree_percorre_print(quadtree_root(c.qt_hidrantes), file_svg, print_svg_hidrante);
  quadtree_percorre_print(quadtree_root(c.qt_semaforos), file_svg, print_svg_semaforo);
  quadtree_percorre_print(quadtree_root(c.qt_torres), file_svg, print_svg_torre);
  quadtree_percorre_print(quadtree_root(c.qt_formas), file_svg, print_svg_elemento);

  for (n = get_first(c.printable_people); n != NULL; n = get_next(c.printable_people, n)) {
    Ponto p = get(c.printable_people, n);

    fprintf(file_svg, "<circ cx=\"%f\" cy=\"%f\" r=\"10\" fill=\"burlywood\" />",
            get_x(p), 
            get_y(p));    
  }

  for (n = get_first(c.printable_comercios); n != NULL; n = get_next(c.printable_comercios, n)) {
    Comercio com = get(c.printable_comercios, n);
    Ponto p = cidade_get_ponto_address(c, comercio_get_address(com));

    fprintf(file_svg, "<circ cx=\"%f\" cy=\"%f\" r=\"20\" fill=\"navy\"/>",
            get_x(p), 
            get_y(p));
  }

  for (n = get_first(c.printable_connections); n != NULL; n = get_next(c.printable_connections, n)) {
    Connection con = get(c.printable_connections, n);

    fprintf(file_svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"gold\" stroke-width=\"7\"/>",
            connection_get_xa(con), 
            connection_get_ya(con),
            connection_get_xb(con),
            connection_get_yb(con));
  }

  for (n = get_first(c.printable_phones); n != NULL; n = get_next(c.printable_phones, n)) {
    Ponto p = get(c.printable_phones, n);

    fprintf(file_svg, "<rect x=\"%f\" y=\"%f\" width=\"16\" height=\"16\" />",
            get_x(p), get_y(p));
  }

  for (n = get_first(c.necroterio); n != NULL; n = get_next(c.necroterio, n)) {
    Ponto p = get(c.necroterio, n);

    fprintf(file_svg, "<rect x=\"%f\" y=\"%f\" width=\"16\" height=\"16\" transform=\"rotate(45 %f %f)\" />",
            get_x(p), get_y(p), get_x(p), get_y(p));
  }

  for (n = get_first(ruas); n != NULL; n = get_next(ruas, n)) {
    Rua r = get(ruas, n);
    Ponto a = grafo_get_vertex_data(c.vias, rua_get_from(r));
    Ponto b = grafo_get_vertex_data(c.vias, rua_get_to(r));

    fprintf(file_svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"black\" stroke-width=\"3\"></line>\n",
             get_x(a), get_y(a), get_x(b), get_y(b));
  }

  fprintf(file_svg, "</svg>");
  fclose(file_svg);
}

void print_svg_rota(char *svg, Cidade c, Lista rota, char *cor) {
  Node n;

  FILE *file_svg = fopen(svg, "w");
  fprintf(file_svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

  quadtree_percorre_print(quadtree_root(c.qt_quadras), file_svg, print_svg_quadra);
  quadtree_percorre_print(quadtree_root(c.qt_hidrantes), file_svg, print_svg_hidrante);
  quadtree_percorre_print(quadtree_root(c.qt_semaforos), file_svg, print_svg_semaforo);
  quadtree_percorre_print(quadtree_root(c.qt_torres), file_svg, print_svg_torre);
  quadtree_percorre_print(quadtree_root(c.qt_formas), file_svg, print_svg_elemento);

  for (n = get_first(rota); n != NULL; n = get_next(rota, n)) {
    Rua r = get(rota, n);
    Ponto a = grafo_get_vertex_data(c.vias, rua_get_from(r));
    Ponto b = grafo_get_vertex_data(c.vias, rua_get_to(r));

    fprintf(file_svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"3\"></line>\n",
             get_x(a), get_y(a), get_x(b), get_y(b), cor);
  }

  fprintf(file_svg, "</svg>");
  fclose(file_svg);
}

void print_svg_elemento(FILE *file_svg, void *elemento) {
  Elemento *e = (Elemento*) elemento;
  if (e->tipo == 'c') {
    Circ *c = (Circ*) e->dado;
    print_svg_circ(file_svg, c);
  } else if (e->tipo == 'r') {
    Rect *r = (Rect*) e->dado;
    print_svg_rect(file_svg, r);
  } else if (e->tipo == 'e') {
    Rect *r = (Rect*) e->dado;
    double extremidades[4];
    extremidades[1] = r->x;
    extremidades[0] = r->y;
    extremidades[3] = r->x + r->height;
    extremidades[2] = r->y + r->width;
    print_sobreposto(file_svg, extremidades);
  }
}

void print_svg_point_stack(FILE *file_svg, Pilha p) {
  Ponto pt;
  fprintf(file_svg, "<polygon stroke=\"fuchsia\" fill=\"fuchsia\" fill-opacity=\"0.2\" points=\"");
  while (!empty(p)) {
    pt = pop(p);
    fprintf(file_svg, "%f %f ", get_x(pt), get_y(pt));
    free(pt);
  }
  fprintf(file_svg, "\" />");
}

void print_svg_torre_range(FILE *fsvg, Torre t) {
  fprintf(fsvg, "<circle fill-opacity=\"0.6\" cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\" stroke=\"%s\"/>\n",
          torre_get_x(t),
          torre_get_y(t),
          torre_get_range(t),
          torre_get_fill(t),
          torre_get_stroke(t));
}
