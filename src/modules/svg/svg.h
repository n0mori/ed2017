#ifndef SVG__H
#define SVG__H

/*
Este modulo gerencia as representacoes em SVG dos objetos geometricos.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../geo/geo.h"

void print_svg_circ(FILE *fsvg, circ *c);
void print_svg_rect(FILE *fsvg, rect *r);
void print_sobreposto(FILE *svg, double *extremidades);
void print_circ_points(FILE *fsvg, circ *c, char *cor);
void print_rect_points(FILE *fsvg, rect *r, char *cor);

#endif
