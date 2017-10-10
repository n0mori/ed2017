#ifndef PONTO__H
#define PONTO__H

/*Um ponto é uma estrutura com x e y, relacionados a coordenadas cartesianas. No
momento, apenas são utilizados para o polígono de cobertura das torres de radio
*/

#include <stdlib.h>

typedef void* Ponto;

Ponto new_ponto(double x, double y);
double get_x(Ponto p);
double get_y(Ponto p);

#endif
