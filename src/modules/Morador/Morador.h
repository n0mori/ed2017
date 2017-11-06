#ifndef MORADOR__H
#define MORADOR__H

/* Um morador é o conjunto de um endereço (cep, face, numero) com a
pessoa que reside nesse endereço (cpf)
*/

#include <stdlib.h>
#include <string.h>

typedef void* Morador;

Morador new_morador(char *cpf, char *cep, char face, int numero);
char *morador_get_cpf(Morador m);
char *morador_get_cep(Morador m);
char  morador_get_face(Morador m);
int   morador_get_numero(Morador m);
int   cmp_morador_cpf(Morador m, void *cpf);

#endif