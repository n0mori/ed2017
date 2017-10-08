#include "Convex.h"

typedef struct angleData {
  double angle;
  void *data;
} *AngleData;

int convex_ccw(double ax, double ay, double bx, double by, double cx, double cy) {
  double result = (bx - ax)*(cy - ay) - (by - ay)*(cx - ax);
  printf("ccw: %f\n", result);
  printf("xa: %f ya: %f\n", ax, ay);
  printf("xb: %f yb: %f\n", bx, by);
  printf("xc: %f yc: %f\n", cx, cy);
  if (result < 0) {
    return -1;
  } else if (result == 0) {
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

int cmp_angle_data(void *a, void *b) {
  AngleData a1 = (AngleData) a;
  AngleData a2 = (AngleData) b;
  if ((a1)->angle < (a2)->angle) {
    return -1;
  } else if ((a1)->angle == (a2)->angle) {
    return 0;
  } else {
    return 1;
  }
}

void sort_by_angle(Lista *l, double (*get_x)(void *a), double (*get_y)(void *b)) {
  void *first = get(l, get_first(l));
  double x0 = get_x(first);
  double y0 = get_y(first);
  Lista *angles = create_lista();
  AngleData a = malloc(sizeof(struct angleData));
  Node *n, *aux;
  aux = get_first(l);

  for (n = get_first(l); n != NULL && get_y(get(l, n)) == get_y(get(l, aux)); n = get_next(l, n)) {
    if (get_x(get(l, n)) < get_x(get(l, aux))) {
      aux = n;
    }
  }

  first = remove_at(l, aux);
  insert_first(l, first);

  a->data = first;
  a->angle = 0;

  for (n = get_next(l, get_first(l)); n != NULL; n = get_next(l, n)) {
    AngleData a = malloc(sizeof(struct angleData));
    a->data = get(l, n);
    a->angle = calculate_angle(x0, y0, get_x(get(l, n)), get_y(get(l, n)));
    insert_last(angles, a);
  }

  while (length_lista(l) > 0) {
    remove_first(l);
  }

  sort_lista(angles, cmp_angle_data);
  insert_first(angles, a);

  while (length_lista(angles) > 0) {
    printf("%f\n", ((AngleData) get(angles, get_first(angles)))->angle);
    insert_last(l, ((AngleData)get(angles, get_first(angles)))->data);
    free(remove_first(angles));
  }
}

void convex_hull(Lista *l, Pilha p, double (*get_x)(void* a), double (*get_y)(void* b), int (*compar)(void *a, void *b)) {
  if (length_lista(l) > 3) {
    Node *n;
    Pilha aux = new_pilha();
    sort_lista(l, compar); /*sort para y0*/
    sort_by_angle(l, get_x, get_y);

    push(aux, get(l, get_first(l)));
    push(aux, get(l, get_next(l, get_first(l))));

    for (n = get_next(l, get_next(l, get_first(l))); n != NULL; n = get_next(l, n)) {
      void *top = pop(aux);
      while (convex_ccw(get_x(peek(aux)), get_y(peek(aux)), get_x(top), get_y(top), get_x(get(l, n)), get_y(get(l, n))) < 0) {
        top = pop(aux);
        puts("POP!");
      }
      push(aux, top);
      push(aux, get(l, n));
    }

    n = get_last(l);
    printf("<polygon fill=\"none\" stroke=\"black\" points=\"");
    while (!empty(aux)) {
      if (peek(aux) == get(l, n)) {
        push(p, pop(aux));
        printf("%f,%f ", get_x(peek(p)), get_y(peek(p)));
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
    printf("\"/>\n");

    free(aux);

    convex_hull(l, p, get_x, get_y, compar);

  } else {
    while (length_lista(l) > 0) {
      push(p, remove_last(l));
    }
  }
}
