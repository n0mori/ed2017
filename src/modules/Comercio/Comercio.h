#ifndef COMERCIO__H
#define COMERCIO__H

/*
Um estabelecimento comercial faz parte de uma cidade. Está localizado na face 
de um CEP, a um número de metros do começo da face. O estabelecimento comercial
possui um nome e um cnpj
*/

#include <stdlib.h>
#include <string.h>
#include "../Address/Address.h"

typedef void* Comercio;

Comercio new_comercio(char* codt, char *cep, char face, int num, char *cnpj, char *nome);
char *comercio_get_codt(Comercio c);
Address comercio_get_address(Comercio c);
char *comercio_get_cep(Comercio c);
char comercio_get_face(Comercio c);
int  comercio_get_num(Comercio c);
char *comercio_get_cnpj(Comercio c);
char *comercio_get_nome(Comercio c);
int  cmp_comercio_cnpj(Comercio c, void *key);
void free_comercio(Comercio c);

#endif