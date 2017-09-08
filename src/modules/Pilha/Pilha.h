#ifndef PILHA__H
#define PILHA__H value

/*Uma pilha é uma estrutura de dados em que apenas o ultimo elemento colocado é
acessável */

#include <stdlib.h>

typedef void* Pilha;

Pilha new_pilha(); /*retorna uma nova pilha*/
int empty(Pilha p); /*retorna 1 se a pilha estiver vazia ou 0 se não estiver*/
void push(Pilha p, void *e); /*insere um elemento na pilha*/
void *pop(Pilha p); /*remove e retorna o elemento do topo da pilha*/
void *peek(Pilha p); /*igual o pop, porém não remove o elemento*/

#endif
