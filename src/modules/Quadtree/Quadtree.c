#include "Quadtree.h"

typedef struct stqdnode {
  double x, y;
  void *valor;
  int active;
  struct stqdnode *ne, *se, *nw, *sw;
}* st_quadnode;

typedef struct stqdtree {
  st_quadnode root;
}* st_quadtree;

Quadtree new_quadtree() {
  Quadtree qt = malloc(sizeof(st_quadtree));
  st_quadtree quad = (st_quadtree) qt;
  quad->root = NULL;
  return qt;
}

int quadtree_empty(Quadtree q) {
  if (quadtree_root(q) == NULL) {
    return 1;
  }
  return 0;
}

QNode quadtree_root(Quadtree q) {
  st_quadtree quad = (st_quadtree) q;
  return quad->root;
}

int quadtree_insert_in_node(QNode target, QNode insertee) {
  st_quadnode t = (st_quadnode) target;
  st_quadnode i = (st_quadnode) insertee;
  if (i->y >= t->y) {
    if (i->x >= t->x) {
      if (t->nw == NULL) {
        t->nw = i;
        return 1;
      } else {
        return 1 + quadtree_insert_in_node(t->nw, i);
      }
    } else {
      if (t->ne == NULL) {
        t->ne = i;
        return 1;
      } else {
        return 1 + quadtree_insert_in_node(t->ne, i);
      }
    }
  } else {
    if (i->x >= t->x) {
      if (t->sw == NULL) {
        t->sw = i;
        return 1;
      } else {
        return 1 + quadtree_insert_in_node(t->sw, i);
      }
    } else {
      if (t->se == NULL) {
        t->se = i;
        return 1;
      } else {
        return 1 + quadtree_insert_in_node(t->se, i);
      }
    }
  }
}

int quadtree_insert(Quadtree q, void *e, double x, double y) {
  st_quadnode node = malloc(sizeof(struct stqdnode));
  node->x = x;
  node->y = y;
  node->active = 1;
  node->valor = e;
  node->ne = NULL;
  node->nw = NULL;
  node->se = NULL;
  node->sw = NULL;

  if (quadtree_empty(q)) {
    st_quadtree quad = (st_quadtree) q;
    quad->root = node;
    return 0;
  }
  return 1 + quadtree_insert_in_node(quadtree_root(q), node);
}

int quadtree_percorre(QNode q, void (*lambda)(void *a)) {
  st_quadnode node = (st_quadnode) q;
  if (q == NULL) {
    return 1;
  }
  lambda(node->valor);
  return 1 + quadtree_percorre(node->ne, lambda) +
             quadtree_percorre(node->nw, lambda) +
             quadtree_percorre(node->sw, lambda) +
             quadtree_percorre(node->se, lambda);
}

int quadtree_percorre_print(QNode q, FILE *f, void (*lambda)(FILE *f, void *a)) {
  st_quadnode node = (st_quadnode) q;
  if (q == NULL) {
    return 1;
  }
  if (node->active && node->valor != NULL) {
    lambda(f, node->valor);
  }
  return 1 + quadtree_percorre_print(node->ne, f, lambda) +
             quadtree_percorre_print(node->nw, f, lambda) +
             quadtree_percorre_print(node->sw, f, lambda) +
             quadtree_percorre_print(node->se, f, lambda);
}

int quadtree_remove_conditional(QNode q, int (*compar)(void* a, void *b), void *comparado, int *acc, FILE *f, char* (*id)(void *a)) {
  st_quadnode node = (st_quadnode) q;
  if (q == NULL) {
    return 1;
  }

  if (node->active && compar(node->valor, comparado)) {
    node->active = 0;
    fprintf(f, "%s\n", id(node->valor));
    *acc = *acc + 1;
  }

  return 1 + quadtree_remove_conditional(node->ne, compar, comparado, acc, f, id) +
             quadtree_remove_conditional(node->nw, compar, comparado, acc, f, id) +
             quadtree_remove_conditional(node->sw, compar, comparado, acc, f, id) +
             quadtree_remove_conditional(node->se, compar, comparado, acc, f, id);

}

void free_quadtree_nodes(QNode q) {
  st_quadnode node = (st_quadnode) q;
  if (q == NULL) {
    return;
  }

  free_quadtree_nodes(node->ne);
  free_quadtree_nodes(node->nw);
  free_quadtree_nodes(node->se);
  free_quadtree_nodes(node->sw);
  free(node->valor);
  free(node);
}

void free_quadtree(Quadtree q) {
  free_quadtree_nodes(quadtree_root(q));
  free(q);
}

void quadtree_filter_to_list(QNode q, Lista *l, int (*compar)(void *a, void *b), void *comparado) {
  st_quadnode node = (st_quadnode) q;
  if (q == NULL) {
    return;
  }

  if (node->active && compar(node->valor, comparado)) {
    insert_last(l, node->valor);
  }

  quadtree_filter_to_list(node->ne, l, compar, comparado);
  quadtree_filter_to_list(node->nw, l, compar, comparado);
  quadtree_filter_to_list(node->se, l, compar, comparado);
  quadtree_filter_to_list(node->sw, l, compar, comparado);
}
