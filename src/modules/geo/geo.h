#ifndef GEO__H
#define GEO__H

/*
Esse arquivo contem as funcoes que tratam de geometria em geral (e.g. verificar
se duas formas geometricas possuem interseccao), e seus tipos abstratos.
*/

#include "../circ/circ.h"
#include "../rect/rect.h"
#include <math.h>

int intersec_cc(circ a, circ b);
void extremidades_cc(circ a, circ b, double *extremidades);
double dist(double xa, double ya, double xb, double yb);

#endif
