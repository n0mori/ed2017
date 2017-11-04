#ifndef CONVEX__H
#define CONVEX__H

/*Módulo para uso do convex hull.*/

#include <stdlib.h>
#include "../Cidade/Cidade.h"
#include "../Sorting/Sorting.h"
#include "../Comparacao/Comparacao.h"
#include "../Pilha/Pilha.h"
#include "../Lista/Lista.h"

int convex_ccw(double ax, double ay, double bx, double by, double cx, double cy);
void convex_hull(Lista l, Pilha p, double (*get_x)(void* a), double (*get_y)(void* b), int (*compar_y0)(void *a, void *b), int (*compar_x0)(void *a, void *b));
/*Lista de pontos, pilha onde os pontos do hull serão colocados, duas funções para extrair x e y dos elementos
e uma função para comparar o y0*/

#endif
