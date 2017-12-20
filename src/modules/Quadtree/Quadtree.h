#ifndef QUADTREE__H
#define QUADTREE__H

/*Uma Quadtree é uma árvore usada para representar um plano 2D. Cada um de seus
nós possui 4 nós, NE, SE, SW, NW. Na inserção, a Quadtree é percorrida em relação
aos pontos cardeais até que encontremos um espaço vazio.
*/

#include <stdlib.h>
#include <stdio.h>
#include "../Lista/Lista.h"
#include "../Ponto/Ponto.h"
#include "../Geo/Geo.h"

typedef void* Quadtree;
typedef void* QNode;

Quadtree new_quadtree(); /* retorna uma nova Quadtree */
int quadtree_empty(Quadtree q);
QNode quadtree_root(Quadtree q);
int quadtree_insert(Quadtree q, void *e, double x, double y);
int quadtree_percorre(QNode q, void (*lambda)(void *a));
int quadtree_percorre_print(QNode q, FILE *f, void (*lambda)(FILE *f, void *a));
int quadtree_remove_conditional(QNode q, int (*compar)(void* a, void *b), void *comparado, int *acc, FILE *f, char* (*id)(void *a));
void free_quadtree(Quadtree q);
void quadtree_filter_to_list(QNode q, Lista l, int (*compar)(void *a, void *b), void *comparado);

#endif
