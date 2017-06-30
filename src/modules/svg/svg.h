#ifndef SVG__H
#define SVG__H

/*
Este modulo gerencia as representacoes em SVG dos objetos geometricos.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../Geo/Geo.h"

void print_svg_circ(FILE *fsvg, Circ *c);
void print_svg_rect(FILE *fsvg, Rect *r);
void print_sobreposto(FILE *svg, double *extremidades);
void print_circ_points(FILE *fsvg, Circ *c, char *cor);
void print_rect_points(FILE *fsvg, Rect *r, char *cor);

#endif
