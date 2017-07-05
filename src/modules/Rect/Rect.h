#ifndef RECT__H
#define RECT__H

/*
Esse arquivo define os metodos e atributos de um retangulo (abbr: Rect).
Um retangulo eh uma forma geometrica bidimensional que possui uma coordenada que
define sua posicao, altura (height) e largura (width). Tambem possui uma cor em
formato reconhecido por SVG, guardada em uma string.
*/

#include <stdlib.h>
#include <string.h>

typedef struct r {
  double x, y, width, height;
  char cor[100];
} Rect;

Rect *new_rect(double width, double height, double x, double y, char *cor);

#endif
