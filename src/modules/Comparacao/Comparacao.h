#ifndef COMPARACAO__H
#define COMPARACAO__H

/* Esse módulo possui todas as funções para comparar dois elementos. Comparando dois
elementos a e b, se a for maior que b, retorna 1, se a for igual a b, retorna 0
e se a for menor que b, retorna -1 */

#include "../Quadra/Quadra.h"
#include "../Hidrante/Hidrante.h"
#include "../Semaforo/Semaforo.h"
#include "../Torre/Torre.h"

int cmp_quadra_string(void *a, void *b);
int cmp_hidrante_string(void *a, void *b);
int cmp_semaforo_string(void *a, void *b);
int cmp_torre_string(void *a, void *b);
int cmp_quadra_quadra_y0(void *a, void *b);
int cmp_quadra_quadra_theta(void *a, void *b);
int cmp_int_int(void *a, void *b);
int cmp_double_double(void *a, void *b);

#endif
