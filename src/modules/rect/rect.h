#ifndef RECT__H
#define RECT__H

/*
Esse arquivo define os métodos e atributos de um retângulo (abbr: rect).
Um retângulo é uma forma geométrica bidimensional que possui uma coordenada que
define sua posição, altura (height) e largura (width). Também possui uma cor em
formato reconhecido por SVG, guardada em uma string.
*/

#include "../coord/coord.h"
#include <stdlib.h>

typedef struct r {
  int id;
  coord ancora;
  double width, height;
  char cor[100];
} rect;

rect *alloc_rect();

#endif
