#include "Vias.h"

typedef struct vias {
  Grafo g;
}* StVias;

Vias new_vias();
void vias_insert_esquina(char *id, double x, double y);
void vias_insert_rua(char *from, char *to, char *ldir, char *lesq, double comprimento, double velocidade, char *nome);
Rota vias_calcular_rota(Ponto inicio, Ponto fim);
