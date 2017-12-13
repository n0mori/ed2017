#ifndef CELULAR__H
#define CELULAR__H

#include <stdlib.h>
#include <string.h>

/* Um celular é um aparelho utilizado para efetuar chamadas telefonicas com o 
intuito de comunicar pessoas. O aparelho se conecta a uma radio-base para que
funcione. Cada aparelho possui um número identificador unico, um dono e um 
identificador para a operadora de telefonia cujo dono é cliente. */

typedef void* Celular;

Celular new_celular(char *dono, char *numero, char operadora);
char* celular_get_dono(Celular c);
char* celular_get_numero(Celular c);
char celular_get_operadora(Celular c);
void celular_set_operadora(Celular c, char opdest);
char* celular_get_torre(Celular c);
void celular_conecta(Celular c, char *id_torre);
void celular_disconecta(Celular c);

#endif