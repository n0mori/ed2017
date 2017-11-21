#include "Cidade.h"

#ifndef TAMANHO_HASH
#define TAMANHO_HASH 100
#endif

Cidade new_cidade() {
  Cidade c;
  c.lista_quadras = create_lista();
  c.lista_hidrantes = create_lista();
  c.lista_semaforos = create_lista();
  c.lista_torres = create_lista();
  c.lista_formas = create_lista();
  c.qt_quadras = new_quadtree();
  c.qt_hidrantes = new_quadtree();
  c.qt_semaforos = new_quadtree();
  c.qt_torres = new_quadtree();
  c.qt_formas = new_quadtree();
  c.cpf_cep = new_hash(TAMANHO_HASH);
  c.numcel_pessoa = new_hash(TAMANHO_HASH);
  c.numcel_torre = new_hash(TAMANHO_HASH);
  c.tipo_comercio = new_hash(TAMANHO_HASH);
  c.pessoas = new_hash(TAMANHO_HASH);
  c.cep_quadra = new_hash(TAMANHO_HASH);
  c.estabelecimentos = new_hash(TAMANHO_HASH);
  return c;
}

void insere_quadra(Cidade c, Quadra q, int *cmp, int *insercoes) {
  *cmp += insert_last(c.lista_quadras, q);
  *insercoes += 1;
}

void insere_hidrante(Cidade c, Hidrante h) {
  insert_last(c.lista_hidrantes, h);
}

void insere_semaforo(Cidade c, Semaforo s) {
  insert_last(c.lista_semaforos, s);
}

void insere_torre(Cidade c, Torre t) {
  insert_last(c.lista_torres, t);
}

void insere_forma(Cidade c, Elemento *e) {
  insert_last(c.lista_formas, e);
}

Elemento *search_forma_lista(Cidade c, int id) {
  Node *n;
  for (n = get_first(c.lista_formas); n != NULL; n = get_next(c.lista_formas, n)) {
    Elemento *e = (Elemento*) get(c.lista_formas, n);
    if (get_elemento_id(*e) == id) {
      return e;
    }
  }
  return NULL;
}

void free_cidade(Cidade c) {
  Node *n;
  free_lista(c.lista_quadras);
  free_lista(c.lista_hidrantes);
  free_lista(c.lista_semaforos);
  free_lista(c.lista_torres);
  for (n = get_first(c.lista_formas); length_lista(c.lista_formas) > 0;) {
    Elemento *e = remove_last(c.lista_formas);
    free(e->dado);
    free(e);
  }
  free_lista(c.lista_formas);

  free_quadtree(c.qt_quadras);
  free_quadtree(c.qt_hidrantes);
  free_quadtree(c.qt_semaforos);
  free_quadtree(c.qt_torres);
  quadtree_percorre(quadtree_root(c.qt_formas), destroy_dado_elemento);
  free_quadtree(c.qt_formas);

  hash_free(c.cpf_cep, free);
  hash_delete_all(c.numcel_pessoa);
  hash_delete_all(c.numcel_torre);
  hash_free(c.tipo_comercio, free);
  hash_free(c.pessoas, free);
  hash_delete_all(c.cep_quadra);
}

void remove_quadras_in_rect(Cidade c, FILE *f, Rect *r, int *cmp, int *del) {
  *del += quadtree_remove_conditional(quadtree_root(c.qt_quadras), quadra_inside_rect, r, cmp, f, quadra_get_cep);
  /*
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.lista_quadras); n != NULL; n = get_next(c.lista_quadras, n)) {
    Quadra q = (Quadra) get(c.lista_quadras, n);
    *cmp += 1;
    if (rm_anterior) {
      free(remove_at(c.lista_quadras, get_before(c.lista_quadras, n)));
      *del += 1;
    }
    rm_anterior = 0;
    if (quadra_inside_rect(q, r)) {
      fputs(quadra_get_cep(q), f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.lista_quadras));
    *del += 1;
  }
  */
}

void remove_hidrantes_in_rect(Cidade c, FILE *f, Rect *r) {
  int w;
  quadtree_remove_conditional(quadtree_root(c.qt_hidrantes), hidrante_inside_rect, r, &w, f, hidrante_get_id);

  /*
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.lista_hidrantes); n != NULL; n = get_next(c.lista_hidrantes, n)) {
    Hidrante h = (Hidrante) get(c.lista_hidrantes, n);
    if (rm_anterior) {
      free(remove_at(c.lista_hidrantes, get_before(c.lista_hidrantes, n)));
    }
    rm_anterior = 0;
    if (hidrante_inside_rect(h, r)) {
      fputs(hidrante_get_id(h), f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.lista_hidrantes));
  }
  */
}

void remove_semaforos_in_rect(Cidade c, FILE *f, Rect *r) {
  int w;
  quadtree_remove_conditional(quadtree_root(c.qt_semaforos), semaforo_inside_rect, r, &w, f, semaforo_get_id);
  /*
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.lista_semaforos); n != NULL; n = get_next(c.lista_semaforos, n)) {
    Semaforo s = (Semaforo) get(c.lista_semaforos, n);
    if (rm_anterior) {
      free(remove_at(c.lista_semaforos, get_before(c.lista_semaforos, n)));
    }
    rm_anterior = 0;
    if (semaforo_inside_rect(s, r)) {
      fputs(semaforo_get_id(s), f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.lista_semaforos));
  }
  */
}

void remove_torres_in_rect(Cidade c, FILE *f, Rect *r) {
  int w;
  quadtree_remove_conditional(quadtree_root(c.qt_torres), torre_inside_rect, r, &w, f, torre_get_id);
  /*
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.lista_torres); n != NULL; n = get_next(c.lista_torres, n)) {
    Torre t = (Torre) get(c.lista_torres, n);
    if (rm_anterior) {
      free(remove_at(c.lista_torres, get_before(c.lista_torres, n)));
    }
    rm_anterior = 0;
    if (torre_inside_rect(t, r)) {
      fputs(torre_get_id(t), f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.lista_torres));
  }
  */
}

void remove_quadras_in_circ(Cidade c, FILE *f, Circ *ci, int *cmp, int *del) {
  *del += quadtree_remove_conditional(quadtree_root(c.qt_quadras), quadra_inside_circ, ci, cmp, f, quadra_get_cep);
  /*
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.lista_quadras); n != NULL; n = get_next(c.lista_quadras, n)) {
    Quadra q = (Quadra) get(c.lista_quadras, n);
    *cmp += 1;
    if (rm_anterior) {
      free(remove_at(c.lista_quadras, get_before(c.lista_quadras, n)));
      *del += 1;
    }
    rm_anterior = 0;
    if (quadra_inside_circ(q, ci)) {
      fputs(quadra_get_cep(q), f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.lista_quadras));
    *del += 1;
  }
  */
}

void remove_hidrantes_in_circ(Cidade c, FILE *f, Circ *ci) {
  int w;
  quadtree_remove_conditional(quadtree_root(c.qt_hidrantes), hidrante_inside_circ, ci, &w, f, hidrante_get_id);
  /*
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.lista_hidrantes); n != NULL; n = get_next(c.lista_hidrantes, n)) {
    Hidrante h = (Hidrante) get(c.lista_hidrantes, n);
    if (rm_anterior) {
      free(remove_at(c.lista_hidrantes, get_before(c.lista_hidrantes, n)));
    }
    rm_anterior = 0;
    if (hidrante_inside_circ(h, ci)) {
      fputs(hidrante_get_id(h), f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.lista_hidrantes));
  }
  */
}

void remove_semaforos_in_circ(Cidade c, FILE *f, Circ *ci) {
  int w;
  quadtree_remove_conditional(quadtree_root(c.qt_semaforos), semaforo_inside_circ, ci, &w, f, semaforo_get_id);
  /*
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.lista_semaforos); n != NULL; n = get_next(c.lista_semaforos, n)) {
    Semaforo s = (Semaforo) get(c.lista_semaforos, n);
    if (rm_anterior) {
      free(remove_at(c.lista_semaforos, get_before(c.lista_semaforos, n)));
    }
    rm_anterior = 0;
    if (semaforo_inside_circ(s, ci)) {
      fputs(semaforo_get_id(s), f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.lista_semaforos));
  }
  */
}

void remove_torres_in_circ(Cidade c, FILE *f, Circ *ci) {
  int w;
  quadtree_remove_conditional(quadtree_root(c.qt_semaforos), semaforo_inside_circ, ci, &w, f, semaforo_get_id);
  /*
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.lista_torres); n != NULL; n = get_next(c.lista_torres, n)) {
    Torre t = (Torre) get(c.lista_torres, n);
    if (rm_anterior) {
      free(remove_at(c.lista_torres, get_before(c.lista_torres, n)));
    }
    rm_anterior = 0;
    if (torre_inside_circ(t, ci)) {
      fputs(torre_get_id(t), f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.lista_torres));
  }
  */
}

void search_cep_or_id(Cidade c, FILE *f, char *id) {
  Node *n;
  Lista hidrantes = create_lista();
  Lista semaforos = create_lista();
  Lista torres = create_lista();
  Quadra q = hash_get(c.cep_quadra, id);

  if (q != NULL) {
    fprintf(f, "Quadra - x: %f y: %f\n", quadra_get_x(q), quadra_get_y(q));
  }

  quadtree_filter_to_list(c.qt_hidrantes, hidrantes, cmp_hidrante_string, id);
  quadtree_filter_to_list(c.qt_semaforos, semaforos, cmp_semaforo_string, id);
  quadtree_filter_to_list(c.qt_torres, torres, cmp_torre_string, id);

  /*
  Node *n;
  for (n = get_first(c.lista_quadras); n != NULL; n = get_next(c.lista_quadras, n)) {
    Quadra q = (Quadra) get(c.lista_quadras, n);
    if (strcmp(quadra_get_cep(q), id) == 0) {
      fprintf(f, "Quadra - x: %f y: %f\n", quadra_get_x(q), quadra_get_y(q));
    }
  }
  */

  for (n = get_first(hidrantes); n != NULL; n = get_next(hidrantes, n)) {
    Hidrante h = (Hidrante) get(hidrantes, n);
    fprintf(f, "Hidrantes - x: %f y: %f\n", hidrante_get_x(h), hidrante_get_y(h));
  }

  for (n = get_first(semaforos); n != NULL; n = get_next(semaforos, n)) {
    Semaforo s = (Semaforo) get(semaforos, n);
    fprintf(f, "Semaforo - x: %f y: %f\n", semaforo_get_x(s), semaforo_get_y(s));
  }

  for (n = get_first(torres); n != NULL; n = get_next(torres, n)) {
    Torre t = (Torre) get(torres, n);
    fprintf(f, "Torre - x: %f y: %f\n", torre_get_x(t), torre_get_y(t));
  }

  while (length_lista(hidrantes) > 0) remove_first(hidrantes);
  while (length_lista(semaforos) > 0) remove_first(semaforos);
  while (length_lista(torres) > 0) remove_first(torres);

  free_lista(hidrantes);
  free_lista(semaforos);
  free_lista(torres);
}
