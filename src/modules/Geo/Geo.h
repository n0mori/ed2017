#ifndef GEO__H
#define GEO__H

/*
Esse arquivo contem as funcoes que tratam de geometria em geral (e.g. verificar
se duas formas geometricas possuem interseccao), e seus tipos abstratos.
*/

#include "../Circ/Circ.h"
#include "../Rect/Rect.h"
#include "../Pilha/Pilha.h"
#include <math.h>

int intersec_cc(Circ a, Circ b);
void extremidades_cc(Circ a, Circ b, double *extremidades);
int intersec_rr(Rect a, Rect b);
void extremidades_rr(Rect a, Rect b, double *extremidades);
double distancia(double xa, double ya, double xb, double yb);
int circ_interno(Circ c, double x, double y);
int rect_interno(Rect r, double x, double y);
int intersec_cr(Circ c, Rect r);
void extremidades_cr(Circ c, Rect r, double *extremidades);
int rect_inside_circ(Rect r, Circ c);
int rect_inside_rect(Rect in, Rect out);
double area_pilha_pontos(Pilha p);

#endif
