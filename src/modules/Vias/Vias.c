#include "Vias.h"

typedef Grafo StVias;

typedef struct djik {
  Vertex v;
  double cost;
  struct djik* from;
}* Djik;

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

Djik new_djik(Vertex v, double cost) {
  Djik d = malloc(sizeof(struct djik));
  d->v = v;
  d->cost = cost;
  d->from = NULL;
  return d;
}

int cmp_djik_v(void* a, void* b) {
  return a == b;
}

Djik djik_low_cost(Lista list) {
  Node n;
  Djik lowest = get(list, get_first(list));
  double menor = lowest->cost;

  for (n = get_first(list); n != NULL; n = get_next(list, n)) {
    Djik d = get(list, n);
    double cost = d->cost;
    if (cost < menor) {
      lowest = d;
      menor = cost;
    }
  }

  return lowest;
}

Lista vias_calcular_rota(Vias v, Ponto inicio, Ponto fim, int option) {
  Lista rota = create_lista();
  Lista unvisited = create_lista();
  Lista visited = create_lista();
  Lista vertices = grafo_all_vertex(v);
  Vertex start = vias_nearest(vertices, inicio);
  Vertex end = vias_nearest(vertices, fim);

  Djik last = new_djik(end, INF);
  Djik current = new_djik(start, 0);
  insert_first(unvisited, current);
  insert_last(unvisited, last);

  while (length_lista(vertices) > 0) {
    Vertex v = remove_first(vertices);
    if (v != start && v != end) {
      insert_last(unvisited, new_djik(v, INF));
    }
  }
  free(vertices);

  while (last->cost == INF && length_lista(unvisited) > 0) {
    Node n;
    seek_and_destroy_lista(unvisited, cmp_djik_v, current);
    insert_first(visited, current);

    for (n = get_first(unvisited); n != NULL; n = get_next(unvisited, n)) {
      Djik d = get(unvisited, n);

      if (grafo_adjacente(v, vertex_get_id(current->v), vertex_get_id(d->v))) {
        Rua r = grafo_get_edge_data(v, vertex_get_id(current->v), vertex_get_id(d->v));
        if (d->cost == INF) {
          if (option == 2) {
            d->cost = rua_get_tempo(r);
          } else {
            d->cost = rua_get_comprimento(r);
          }
          d->from = current;
        } else {
          double calculated_cost;

          if (option == 2) {
            calculated_cost += rua_get_tempo(r);
          } else {
            calculated_cost += rua_get_comprimento(r);
          }

          if (calculated_cost < d->cost) {
            d->cost = calculated_cost;
            d->from = current;
          }
        }
      }
    }

    current = djik_low_cost(unvisited);
  }

  while (last->from != NULL) {
    Rua r = grafo_get_edge_data(v, vertex_get_id(last->from->v), vertex_get_id(last->v));
    insert_first(rota, r);
    last = last->from;
  }

  return rota;
}
