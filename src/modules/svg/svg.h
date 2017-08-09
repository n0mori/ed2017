#ifndef SVG__H
#define SVG__H

/*
Este modulo gerencia as representacoes em SVG dos objetos geometricos.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../Geo/Geo.h"
#include "../Elemento/Elemento.h"
#include "../Lista/Lista.h"
#include "../Cidade/Cidade.h"

void print_svg_circ(FILE *fsvg, Circ *c);
void print_svg_rect(FILE *fsvg, Rect *r);
void print_svg_quadra(FILE *fsvg, Quadra *q);
void print_svg_hidrante(FILE *fsgv, Hidrante *h);
void print_sobreposto(FILE *svg, double *extremidades);
void print_circ_points(FILE *fsvg, Circ *c, char *cor);
void print_rect_points(FILE *fsvg, Rect *r, char *cor);
void print_svg_cidade(char *svg, Cidade c);

#endif
