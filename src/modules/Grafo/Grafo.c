#include "Grafo.h"

typedef struct vertex {
  char id[100];
  void *data;
}* StVertex;

typedef struct edge {
  char from[100];
  char to[100];
  char *data;
}* StEdge;

typedef struct grafo {
  Hash vertices;
  Lista edges;
}* StGrafo;

Grafo new_grafo() {
  StGrafo g = malloc(sizeof(struct grafo));
  g->vertices = new_hash(98);
  g->edges = create_lista();
  return g;
}

StVertex new_vertex(char *id, void *data) {
  StVertex v = malloc(sizeof(struct vertex));
  strcpy(v->id, id);
  v->data = data;
  return v; 
}

void grafo_insert_vertex(Grafo g, char *id, void *data) {
  StGrafo grafo = (StGrafo) g;
  StVertex v = new_vertex(id, data);
  hash_insert(grafo->vertices, id, v);
}

void *grafo_get_vertex_data(Grafo g, char *id) {
  StGrafo grafo = (StGrafo) g;
  StVertex v = hash_get(grafo->vertices, id);
  if (v == NULL) {
    return NULL;
  }
  return v->data;
}

StEdge new_edge(char *from, char *to, void *data) {
  StEdge e = malloc(sizeof(struct edge));
  strcpy(e->from, from);
  strcpy(e->to, to);
  e->data = data;
  return e;
}

int cmp_edge_edge(void *a, void *b) {
  StEdge ea = (StEdge) a;
  StEdge eb = (StEdge) b;

  return (strcmp(ea->from, eb->from) == 0 && strcmp(ea->to, eb->to) == 0);
}

int cmp_edge_from(void *id, void *edge) {
  StEdge e = (StEdge) edge;
  return strcmp(id, e->from) == 0;
}

void *free_edge(StEdge e) {
  void *data = e->data;
  free(e);
  return data;
}

void grafo_insert_edge(Grafo g, char *from, char *to, void *data) {
  StGrafo grafo = (StGrafo) g;
  StEdge e;
  StVertex vfrom, vto;

  vfrom = hash_get(grafo->vertices, from);
  vto = hash_get(grafo->vertices, to);

  if (vfrom == NULL || vto == NULL) {
    return;
  }

  e = new_edge(from, to, data);
  
  insert_first(grafo->edges, e);

}

void *grafo_get_edge_data(Grafo g, char *from, char *to) {
  StGrafo grafo = (StGrafo) g;
  StEdge aux, e;

  if (!grafo_adjacente(g, from, to)) {
    return NULL;
  }

  aux = new_edge(from, to, NULL);

  e = search_lista(grafo->edges, cmp_edge_edge, aux);

  free_edge(aux);

  return e->data;
}

void *grafo_remove_edge(Grafo g, char *from, char *to) {
  void *data;
  StGrafo grafo = (StGrafo) g;
  StEdge aux, e;

  if (!grafo_adjacente(g, from, to)) {
    return NULL;
  }

  aux = new_edge(from, to, NULL);

  e = seek_and_destroy_lista(grafo->edges, cmp_edge_edge, aux);

  free_edge(aux);

  data = free_edge(e);
  return data;
  
}

int grafo_adjacente(Grafo g, char *from, char *to) {
  StGrafo grafo = (StGrafo) g;
  StVertex vfrom, vto;
  StEdge aux, e;

  vfrom = hash_get(grafo->vertices, from);
  vto = hash_get(grafo->vertices, to);

  if (vfrom == NULL || vto == NULL) {
    return 0;
  }

  aux = new_edge(from, to, NULL);

  e = search_lista(grafo->edges, cmp_edge_edge, aux);

  free_edge(aux);

  if (e == NULL) {
    return 0;
  }

  return 1;
    
}

void grafo_adjacentes(Grafo g, char *id, Lista l) {
  StGrafo grafo = (StGrafo) g;
  Node n;

  for (n = get_first(grafo->edges); n != NULL; n = get_next(grafo->edges, n)) {
    StEdge e = get(grafo->edges, n);
    if (cmp_edge_from(id, e)) {
      insert_last(l, e);
    }
  }

}

void *edge_get_data(Edge e) {
  StEdge edge = (StEdge) e;
  return edge->data;
}