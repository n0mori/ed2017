#ifndef SEMAFORO__H
#define SEMAFORO__H

/*
Um semáforo é uma estrutura de uma cidade. Um semáforo possui uma posição (x,y)
no plano cartesiano e uma cor
*/

#include <stdlib.h>
#include <string.h>

typedef void* Semaforo;

Semaforo new_semaforo(double x, double y, char *id, char *fill, char *stroke);
double semaforo_get_x(Semaforo s);
double semaforo_get_y(Semaforo s);
double semaforo_get_ciclo(Semaforo s);
char* semaforo_get_id(Semaforo s);
char* semaforo_get_fill(Semaforo s);
char* semaforo_get_stroke(Semaforo s);
void semaforo_set_ciclo(Semaforo s, double ciclo);

#endif
