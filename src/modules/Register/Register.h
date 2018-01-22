#ifndef REGISTER__H
#define REGISTER__H

/*
Um register é um registrador, no qual será armazenado um dado e seu tipo.
*/

#include <stdlib.h>

typedef void* Register;

Register new_register(char type, void *data);
char register_get_type(Register r);
void* register_get_data(Register r);

#endif