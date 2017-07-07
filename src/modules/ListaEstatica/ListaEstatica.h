#ifndef LISTAESTATICA__H
#define LISTAESTATICA__H

/* Uma lista eh uma coleção de objetos de tamanho limitado em sua criacao*/

#include <stdlib.h>
#include <stdio.h>
#include "../Elemento/Elemento.h"

typedef Elemento* ListaEstatica;

Elemento *busca_id(ListaEstatica l, int n, int buscado);
void limpa_vetor(ListaEstatica l, int n);
ListaEstatica cria_lista_estatica(int tamanho);
void adiciona_lista_estatica(ListaEstatica l, int n, Elemento e);

#endif
