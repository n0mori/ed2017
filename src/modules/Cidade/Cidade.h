#ifndef CIDADE__H
#define CIDADE__H

/* Uma cidade é uma representação de uma cidade real. Possui uma quantidade
indeterminada de quarteiroes, hidrantes, semaforos, torres de celular, etc.
*/

#include "../Lista/Lista.h"
#include "../Geo/Geo.h"
#include "../Quadra/Quadra.h"
#include "../Hidrante/Hidrante.h"
#include "../Semaforo/Semaforo.h"
#include "../Torre/Torre.h"

typedef struct cidade {
  Lista *quadras;
  Lista *hidrantes;
  Lista *semaforos;
  Lista *torres;
} Cidade;

Cidade new_cidade();
void insere_quadra(Cidade c, Quadra *q, int *cmp, int *insercoes);
void insere_hidrante(Cidade c, Hidrante *h);
void insere_semaforo(Cidade c, Semaforo *s);
void insere_torre(Cidade c, Torre *t);

#endif
