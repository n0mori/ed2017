#include "Vias.h"

typedef Grafo StVias;

Vias new_vias() {
  Vias v = new_grafo();
  return v;
}

void vias_insert_esquina(Vias v, char *id, double x, double y) {
  Ponto esquina = new_ponto(x, y);
  grafo_insert_vertex(v, id, esquina);
}

void vias_insert_rua(Vias v, char *from, char *to, char *ldir, char *lesq, double comprimento, double velocidade, char *nome) {
  Rua rua = new_rua(from, to, ldir, lesq, comprimento, velocidade, nome);
  grafo_insert_edge(v, from, to, rua);
}

Vertex vias_nearest(Lista list, Ponto p) {
  Vertex near = get(list, get_first(list));
  double dist;
  double menor = distancia(get_x(p), get_y(p), get_x(vertex_get_data(near)), get_y(vertex_get_data(near)));
  Node n;

  for (n = get_first(list); n != NULL; n = get_next(list, n)) { 
    Vertex v = get(list, n);
    Ponto atual = vertex_get_data(v);
    dist = distancia(get_x(p), get_y(p), get_x(atual), get_y(atual));
    if (dist < menor) {
      menor = dist;
      near = v;
    }
  }
  return near;
}

Lista vias_calcular_rota(Vias v, Ponto inicio, Ponto fim, int option) {
  Lista rota = create_lista();
  Lista unvisited = grafo_all_vertex(v);
  Vertex start = vias_nearest(unvisited, inicio);
  printf("%s\n", vertex_get_id(start));
  return NULL;
}
