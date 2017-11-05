#ifndef TIPOCOM__H
#define TIPOCOM__H 

/* 
TipoCom é uma estrutura que guarda um código de estabelecimento comercial
junto com a sua descrição
*/

#include <stdlib.h>
#include <string.h>

typedef void* TipoCom;

TipoCom new_tipocom(char *codt, char *desc);
char *tipocom_get_codt(TipoCom t);
char *tipocom_get_desc(TipoCom t);
int  cmp_tipocom_codt(TipoCom t, void *codt);
void free_tipocom(TipoCom t);

#endif