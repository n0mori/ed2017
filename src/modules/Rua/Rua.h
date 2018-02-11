#ifndef RUA__H
#define RUA__H

/*
Uma rua é uma estrutura que guarda as informações de uma
ligação entre esquinas de um sistema viário. Uma rua possui
o nome das esquinas que liga, um nome, uma velocidade media 
de percurso, um comprimento e o nome das quadras à direita e 
à esquerda.
*/

#include <stdlib.h>
#include <string.h>

typedef void* Rua;

Rua new_rua(char *from, char *to, char *ldir, char *lesq, double comprimento, double velocidade, char *nome);
char* rua_get_from(Rua r);
char* rua_get_to(Rua r);
char* rua_get_ldir(Rua r);
char* rua_get_lesq(Rua r);
char* rua_get_nome(Rua r);
double rua_get_comprimento(Rua r);
double rua_get_velocidade(Rua r);
double rua_get_tempo(Rua r);

#endif