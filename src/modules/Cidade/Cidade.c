#include "Cidade.h"

Cidade new_cidade() {
  Cidade c;
  c.quadras = create_lista();
  c.hidrantes = create_lista();
  c.semaforos = create_lista();
  c.torres = create_lista();
  c.formas = create_lista();
  return c;
}

void insere_quadra(Cidade c, Quadra *q, int *cmp, int *insercoes) {
  *cmp += insert_last(c.quadras, q);
  *insercoes++;
}

void insere_hidrante(Cidade c, Hidrante *h) {
  insert_last(c.hidrantes, h);
}

void insere_semaforo(Cidade c, Semaforo *s) {
  insert_last(c.semaforos, s);
}

void insere_torre(Cidade c, Torre *t) {
  insert_last(c.torres, t);
}

void insere_forma(Cidade c, Elemento *e) {
  insert_last(c.formas, e);
}

Elemento *search_forma(Cidade c, int id) {
  Node *n;
  for (n = get_first(c.formas); n != NULL; n = get_next(c.formas, n)) {
    Elemento *e = (Elemento*) get(c.formas, n);
    if (get_elemento_id(*e) == id) {
      return e;
    }
  }
  return NULL;
}

void free_cidade(Cidade c) {
  Node *n;
  free_lista(c.quadras);
  free_lista(c.hidrantes);
  free_lista(c.semaforos);
  free_lista(c.torres);
  for (n = get_first(c.formas); length_lista(c.formas) > 0;) {
    Elemento *e = remove_last(c.formas);
    free(e->dado);
    free(e);
  }
  free_lista(c.formas);
}

void remove_quadras_in_rect(Cidade c, FILE *f, Rect *r, int *cmp, int *del) {
	return;
}

void remove_hidrantes_in_rect(Cidade c, FILE *f, Rect *r) {
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.hidrantes); n != NULL; n = get_next(c.hidrantes, n)) {
    Hidrante *h = (Hidrante*) get(c.hidrantes, n);
    if (rm_anterior) {
      remove_at(c.hidrantes, get_before(c.hidrantes, n));
    }
    rm_anterior = 0;
    if (rect_interno(*r, h->x, h->y)) {
      fputs(h->id, f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.hidrantes));
  }
}

void remove_semaforos_in_rect(Cidade c, FILE *f, Rect *r) {
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.semaforos); n != NULL; n = get_next(c.semaforos, n)) {
    Semaforo *s = (Semaforo*) get(c.semaforos, n);
    if (rm_anterior) {
      free(remove_at(c.semaforos, get_before(c.semaforos, n)));
    }
    rm_anterior = 0;
    if (rect_interno(*r, s->x, s->y)) {
      fputs(s->id, f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.semaforos));
  }
}

void remove_torres_in_rect(Cidade c, FILE *f, Rect *r) {
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.torres); n != NULL; n = get_next(c.torres, n)) {
    Torre *t = (Torre*) get(c.torres, n);
    if (rm_anterior) {
      free(remove_at(c.torres, get_before(c.torres, n)));
    }
    rm_anterior = 0;
    if (rect_interno(*r, t->x, t->y)) {
      fputs(t->id, f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.torres));
  }
}

void remove_quadras_in_circ(Cidade c, FILE *f, Circ *ci, int *cmp, int *del) {
	return;
}

void remove_hidrantes_in_circ(Cidade c, FILE *f, Circ *ci) {
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.hidrantes); n != NULL; n = get_next(c.hidrantes, n)) {
    Hidrante *h = (Hidrante*) get(c.hidrantes, n);
    if (rm_anterior) {
      free(remove_at(c.hidrantes, get_before(c.hidrantes, n)));
    }
    rm_anterior = 0;
    if (circ_interno(*ci, h->x, h->y)) {
      fputs(h->id, f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.hidrantes));
  }
}

void remove_semaforos_in_circ(Cidade c, FILE *f, Circ *ci) {
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.semaforos); n != NULL; n = get_next(c.semaforos, n)) {
    Semaforo *s = (Semaforo*) get(c.semaforos, n);
    if (rm_anterior) {
      free(remove_at(c.semaforos, get_before(c.semaforos, n)));
    }
    rm_anterior = 0;
    if (circ_interno(*ci, s->x, s->y)) {
      fputs(s->id, f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.semaforos));
  }
}

void remove_torres_in_circ(Cidade c, FILE *f, Circ *ci) {
  Node *n;
  int rm_anterior = 0;
  for (n = get_first(c.torres); n != NULL; n = get_next(c.torres, n)) {
    Torre *t = (Torre*) get(c.torres, n);
    if (rm_anterior) {
      free(remove_at(c.torres, get_before(c.torres, n)));
    }
    rm_anterior = 0;
    if (circ_interno(*ci, t->x, t->y)) {
      fputs(t->id, f);
      fputs("\n", f);
      rm_anterior = 1;
    }
  }
  if (rm_anterior) {
    free(remove_last(c.torres));
  }
}

void search_cep_or_id(Cidade c, FILE *f, char *id) {
  Node *n;
  for (n = get_first(c.quadras); n != NULL; n = get_next(c.quadras, n)) {
    Quadra *q = (Quadra*) get(c.quadras, n);
    if (strcmp(q->cep, id) == 0) {
      fprintf(f, "Quadra - x: %lf y: %lf\n", q->x, q->y);
    }
  }

  for (n = get_first(c.hidrantes); n != NULL; n = get_next(c.hidrantes, n)) {
    Hidrante *h = (Hidrante*) get(c.hidrantes, n);
    if (strcmp(h->id, id) == 0) {
      fprintf(f, "Hidrantes - x: %lf y: %lf\n", h->x, h->y);
    }
  }

  for (n = get_first(c.semaforos); n != NULL; n = get_next(c.semaforos, n)) {
    Semaforo *s = (Semaforo*) get(c.semaforos, n);
    if (strcmp(s->id, id) == 0) {
      fprintf(f, "Semaforo - x: %lf y: %lf\n", s->x, s->y);
    }
  }

  for (n = get_first(c.torres); n != NULL; n = get_next(c.torres, n)) {
    Torre *t = (Torre*) get(c.torres, n);
    if (strcmp(t->id, id) == 0) {
      fprintf(f, "Torre - x: %lf y: %lf\n", t->x, t->y);
    }
  }
}
