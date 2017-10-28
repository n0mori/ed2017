#include "Convex.h"

typedef struct angleData {
  double x, y;
  void *data;
} *AngleData;

static AngleData p0;

int convex_ccw(double ax, double ay, double bx, double by, double cx, double cy) {
  double result = (bx - ax)*(cy - ay) - (by - ay)*(cx - ax);
  /*
  printf("ccw: %f\n", result);
  printf("xa: %f ya: %f\n", ax, ay);
  printf("xb: %f yb: %f\n", bx, by);
  printf("xc: %f yc: %f\n", cx, cy);
  */
  if (result < -10e-7) {
    return -1;
  } else if (result < 10e-7) {
    return 0;
  } else {
    return 1;
  }
 }

double calculate_angle(double x0, double y0, double x, double y) {
  if (y0 == y) {
    return x - x0;
  }
  return - (x - x0) / (y - y0);
}

double dist_sq(AngleData a, AngleData b) {
  return (a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y);
}

int cmp_angle_data(void *a, void *b) {
  AngleData a1 = (AngleData) a;
  AngleData a2 = (AngleData) b;
  int orientation = convex_ccw(p0->x, p0->y, a1->x, a1->y, a2->x, a2->y);
  if (orientation == 0) {
    return (dist_sq(p0, a) >= dist_sq(p0, b))? -1 : 1;
  }

  return (orientation == 1)? -1: 1;

}

void sort_by_angle(Lista *l, double (*get_x)(void *a), double (*get_y)(void *b), int (*compar)(void *a, void *b)) {
  Node *n;
  Lista *angles = create_lista();

  for (n = get_first(l); n != NULL; n = get_next(l, n)) {
    AngleData a = malloc(sizeof(struct angleData));
    a->x = get_x(get(l, n));
    a->y = get_y(get(l, n));
    a->data = get(l, n);
    insert_last(angles, a);
  }

  sort_lista(angles, cmp_angle_data);
  /*insert_first(angles, p0);*/

  while (length_lista(l) > 0) {
    remove_first(l);
  }

  while (length_lista(angles) > 0) {
    AngleData a = remove_first(angles);
    insert_last(l, a->data);
    free(a);
  }

  free_lista(angles);

}

void encontra_menor_e_coloca_no_comeco(Lista *l, int (*compar_y0)(void *a, void *b), int (*compar_x0)(void *a, void *b)) {
  Node *n;
  void *menor = get(l, get_first(l));
  for (n = get_next(l, get_first(l)); n != NULL; n = get_next(l, n)) {
    if (compar_y0(menor, get(l, n)) > 0
    || (compar_y0(menor, get(l, n)) == 0
    && compar_x0(menor, get(l, n)) > 0)) {
      void *new_menor = get(l, n);
      n = get_before(l, n);
      remove_at(l, get_next(l, n));
      insert_first(l, new_menor);
      menor = get(l, get_first(l));
    }
  }
}

void convex_hull(Lista *l, Pilha p, double (*get_x)(void* a), double (*get_y)(void* b), int (*compar_y0)(void *a, void *b), int (*compar_x0)(void *a, void *b)) {
  Pilha aux = new_pilha();
  Lista *maybes = create_lista();
  Node *n;
  void *menor;

  /* encontrando o menor */
  encontra_menor_e_coloca_no_comeco(l, compar_y0, compar_x0);


  menor = remove_first(l);

  p0 = malloc(sizeof(struct angleData));
  p0->x = get_x(menor);
  p0->y = get_y(menor);
  p0->data = menor;
  sort_by_angle(l, get_x, get_y, compar_y0);
  insert_first(l, menor);
  /* FUNCIONA ACIMA */
  /*
  for (n = get_first(l); n != NULL; n = get_next(l, n)) {
    printf("%f %f\n", get_x(get(l, n)), get_y(get(l, n)));
  }
  */

  /*
  if (length_lista(l) > 3) {
    for (n = get_next(l, get_first(l)); n != NULL; n = get_next(l,n)) {
      while (get_next(l, n) != NULL
      && convex_ccw(get_x(menor), get_y(menor),
      get_x(get(l, n)), get_y(get(l, n)),
      get_x(get(l, get_next(l, n))), get_y(get(l, get_next(l, n)))) == 0) {
        n = get_before(l, n);
        insert_last(maybes, remove_at(l, get_next(l, n)));
      }
    }
  }
  */

  if (length_lista(l) > 3) {
    push(aux, get(l, get_first(l)));
    push(aux, get(l, get_next(l, get_first(l))));

    for (n = get_next(l, get_next(l, get_first(l))); n != NULL; n = get_next(l, n)) {
      void *top = pop(aux);
      while (convex_ccw(get_x(peek(aux)), get_y(peek(aux)), get_x(top), get_y(top), get_x(get(l, n)), get_y(get(l, n))) < 0) {
        top = pop(aux);
      }
      push(aux, top);
      push(aux, get(l, n));
    }

    n = get_last(l);
    while (!empty(aux)) {
      if (peek(aux) == get(l, n)) {
        push(p, pop(aux));
        if (n == get_last(l)) {
          remove_last(l);
          n = get_last(l);
        } else {
          n = get_next(l, n);
          remove_at(l, get_before(l, n));
        }
      } else {
        n = get_before(l, n);
      }
    }
  } else {
    while (length_lista(l) > 0) {
      push(p, remove_first(l));
    }
  }
  free(maybes);

}
