#ifndef QUADTREE__H
#define QUADTREE__H

/*Uma Quadtree é uma árvore usada para representar um plano 2D. Cada um de seus
nós possui 4 nós, NE, SE, SW, NW. Na inserção, a Quadtree é percorrida em relação
aos pontos cardeais até que encontremos um espaço vazio.
*/

#include <stdlib.h>
#include <stdio.h>

typedef void* Quadtree;
typedef void* QNode;

Quadtree new_quadtree(); /* retorna uma nova Quadtree */
int quadtree_empty(Quadtree q);
QNode quadtree_root(Quadtree q);
int quadtree_insert(Quadtree q, void *e, double x, double y);
int quadtree_remove(Quadtree q, QNode n);
int quadtree_percorre(Quadtree q, void (*lambda)(void *a));
int quadtree_percorre_print(Quadtree q, FILE *f, void (*lambda)(FILE *f, void *a));

#endif
