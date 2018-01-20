#ifndef VIAS__H
#define VIAS__H

/*
Vias é um módulo que se encarrega da representação de ruas e esquinas de um
sistema viário e sua navegação (chegar de um ponto a outro no sistema viário).
*/

#include <stdlib.h>
#include "../Grafo/Grafo.h"
#include "../Ponto/Ponto.h"

typedef void* Vias;
/*
typedef void* Rua;
*/
typedef void* Rota;

Vias new_vias();
void vias_insert_esquina(char *id, double x, double y);
void vias_insert_rua(char *from, char *to, char *ldir, char *lesq, double comprimento, double velocidade, char *nome);
Rota vias_calcular_rota(Ponto inicio, Ponto fim);

#endif