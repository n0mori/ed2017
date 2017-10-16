#ifndef COMPARACAO__H
#define COMPARACAO__H

/* Esse módulo possui todas as funções para comparar dois elementos. Comparando dois
elementos a e b, se a for maior que b, retorna 1, se a for igual a b, retorna 0
e se a for menor que b, retorna -1 */

#include <string.h>
#include "../Quadra/Quadra.h"
#include "../Hidrante/Hidrante.h"
#include "../Semaforo/Semaforo.h"
#include "../Torre/Torre.h"
#include "../Elemento/Elemento.h"

int cmp_quadra_string(void *a, void *b);
int cmp_hidrante_string(void *a, void *b);
int cmp_semaforo_string(void *a, void *b);
int cmp_torre_string(void *a, void *b);
int cmp_quadra_quadra_y0(void *a, void *b);
int cmp_quadra_quadra_y0(void *a, void *b);
int cmp_hidrante_hidrante_y0(void *a, void *b);
int cmp_semaforo_semaforo_y0(void *a, void *b);
int cmp_torre_torre_y0(void *a, void *b);
int cmp_int_int(void *a, void *b);
int cmp_double_double(void *a, void *b);
int cmp_elemento_elemento_y0(void *a, void *b);
int cmp_quadra_quadra_x0(void *a, void *b);
int cmp_quadra_quadra_x0(void *a, void *b);
int cmp_hidrante_hidrante_x0(void *a, void *b);
int cmp_semaforo_semaforo_x0(void *a, void *b);
int cmp_torre_torre_x0(void *a, void *b);
int cmp_elemento_elemento_x0(void *a, void *b);
int cmp_true(void *a, void *b);
int cmp_ponto_y0(void *a, void *b);
int cmp_ponto_x0(void *a, void *b);

#endif
