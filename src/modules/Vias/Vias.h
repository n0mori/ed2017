#ifndef VIAS__H
#define VIAS__H

/*
Vias é um módulo que se encarrega da representação de ruas e esquinas de um
sistema viário e sua navegação (chegar de um ponto a outro no sistema viário).
*/

#include <stdlib.h>
#include <float.h>
#include "../Grafo/Grafo.h"
#include "../Ponto/Ponto.h"
#include "../Rua/Rua.h"

typedef void* Vias;
typedef void* Rota;

Vias new_vias();
void vias_insert_esquina(Vias v, char *id, double x, double y);
void vias_insert_rua(Vias v, char *from, char *to, char *ldir, char *lesq, double comprimento, double velocidade, char *nome);
Lista vias_calcular_rota(Vias v, Ponto inicio, Ponto fim, int option);
/*
Retorna uma lista de ruas indicando o caminho.
option seleciona o caminho por distancia ou por tempo
1 - distancia
2 - tempo
default: distancia
*/

#endif