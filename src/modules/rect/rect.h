#ifndef RECT__H
#define RECT__H value

typedef struct r {
  int id;
  coord ancora;
  double width, height;
  char cor[100];
} rect;

rect *alloc_rect();

#endif
