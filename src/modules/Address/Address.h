#ifndef ADDRESS__H
#define ADDRESS__H

/* 
Esse módulo cria uma representação para endereços da cidade (Address).
Possui um cep, uma face, um numero e um complemento.
*/

#include <stdlib.h>
#include <string.h>

typedef void * Address;

Address new_address(char *cep, char face, int numero, char *complemento);
char *address_get_cep(Address a);
char address_get_face(Address a);
int  address_get_numero(Address a);
char *address_get_complemento(Address a);

#endif