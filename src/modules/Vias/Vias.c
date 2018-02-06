#include "Vias.h"

typedef struct vias {
  Grafo g;
}* StVias;

int cmpt(void *a, void *b) {
  return 1;
}

Vias new_vias() {
  StVias v = malloc(sizeof(struct vias));
  v->g = new_grafo();
  return v;
}

void vias_insert_esquina(Vias v, char *id, double x, double y) {
  StVias vias = (StVias) v;
  Ponto esquina = new_ponto(x, y);
  grafo_insert_vertex(vias->g, id, esquina);
}

void vias_insert_rua(Vias v, char *from, char *to, char *ldir, char *lesq, double comprimento, double velocidade, char *nome) {
  StVias vias = (StVias) v;
  Rua rua = new_rua(from, to, ldir, lesq, comprimento, velocidade, nome);
  grafo_insert_edge(vias->g, from, to, rua);
}

Vertex vias_nearest(Lista list, Ponto p) {

}

Lista vias_calcular_rota(Vias v, Ponto inicio, Ponto fim, int option) {
  Lista rota = create_lista();
  Lista unvisited = create_lista();
  Grafo g = ((StVias) v);



}
