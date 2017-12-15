#ifndef CONNECTION__H
#define CONNECTION__H

#include <stdlib.h>
#include "../Ponto/Ponto.h"

typedef void* Connection;

Connection new_connection(Ponto a, Ponto b);
double connection_get_xa(Connection c);
double connection_get_xb(Connection c);
double connection_get_ya(Connection c);
double connection_get_yb(Connection c);
void free_connection(Connection c);

#endif