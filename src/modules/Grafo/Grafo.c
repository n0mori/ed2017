#include "Grafo.h"

typedef struct vertex {
  char id[100];
  void *data
}* Vertex;

typedef struct edge {
  char from[100];
  char to[100];
  char *data;
}* Edge;

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

Vertex new_vertex(char *id, void *data) {
  Vertex v = malloc(sizeof(struct vertex));
  strcpy(v->id, id);
  v->data = data;
  return v; 
}

void grafo_insert_vertex(Grafo g, char *id, void *data) {
  StGrafo grafo = (StGrafo) g;
  Vertex v = create_vertex(id, data);
  hash_insert(grafo->vertices, id, v);
}

void *grafo_get_vertex_data(Grafo g, char *id) {
  StGrafo grafo = (StGrafo) g;
  Vertex v = hash_get(grafo->vertices, id);
  return v->data;
}

void grafo_insert_edge(Grafo g, char *from, char *to, void *data) {
  
}

void *grafo_get_edge_data(Grafo g, char *from, char *to) {
  
}

void *grafo_remove_edge(Grafo g, char *from, char *to) {
  
}

int  grafo_adjacente(Grafo g, char *from, char *to) {
  
}

Lista grafo_adjacentes(Grafo g, char *id) {
  
}