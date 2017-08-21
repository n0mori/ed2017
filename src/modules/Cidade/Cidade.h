#ifndef CIDADE__H
#define CIDADE__H

/* Uma cidade é uma representação de uma cidade real. Possui uma quantidade
indeterminada de quarteiroes, hidrantes, semaforos, torres de celular, etc.
*/

#include <stdio.h>
#include "../Lista/Lista.h"
#include "../Geo/Geo.h"
#include "../Elemento/Elemento.h"
#include "../Quadra/Quadra.h"
#include "../Hidrante/Hidrante.h"
#include "../Semaforo/Semaforo.h"
#include "../Torre/Torre.h"

typedef struct cidade {
  Lista *quadras;
  Lista *hidrantes;
  Lista *semaforos;
  Lista *torres;
  Lista *formas;
} Cidade;

Cidade new_cidade();
void insere_quadra(Cidade c, Quadra *q, int *cmp, int *insercoes);
void insere_hidrante(Cidade c, Hidrante *h);
void insere_semaforo(Cidade c, Semaforo *s);
void insere_torre(Cidade c, Torre *t);
void insere_forma(Cidade c, Elemento *e);
Elemento *search_forma(Cidade c, int id);
void free_cidade(Cidade c);
void remove_quadras_in_rect(Cidade c, FILE *f, Rect *r, int *cmp, int *del);
void remove_hidrantes_in_rect(Cidade c, FILE *f, Rect *r);
void remove_semaforos_in_rect(Cidade c, FILE *f, Rect *r);
void remove_torres_in_rect(Cidade c, FILE *f, Rect *r);
void remove_quadras_in_circ(Cidade c, FILE *f, Circ *ci, int *cmp, int *del);
void remove_hidrantes_in_circ(Cidade c, FILE *f, Circ *ci);
void remove_semaforos_in_circ(Cidade c, FILE *f, Circ *ci);
void remove_torres_in_circ(Cidade c, FILE *f, Circ *ci);
void search_cep_or_id(Cidade c, FILE *f, char *id);

#endif
