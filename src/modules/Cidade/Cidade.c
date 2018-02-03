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
  c.printable_people = create_lista();
  c.printable_comercios = create_lista();
  c.printable_connections = create_lista();
  c.printable_phones = create_lista();
  c.necroterio = create_lista();
  c.qt_quadras = new_quadtree();
  c.qt_hidrantes = new_quadtree();
  c.qt_semaforos = new_quadtree();
  c.qt_torres = new_quadtree();
  c.qt_formas = new_quadtree();
  c.cpf_cep = new_hash(TAMANHO_HASH);
  c.numcel_pessoa = new_hash(TAMANHO_HASH);
  c.numcel_torre = new_hash(TAMANHO_HASH);
  c.sercomtuel = new_hash(TAMANHO_HASH);
  c.uelmobile = new_hash(TAMANHO_HASH);
  c.tipo_comercio = new_hash(TAMANHO_HASH);
  c.pessoas = new_hash(TAMANHO_HASH);
  c.cep_quadra = new_hash(TAMANHO_HASH);
  c.estabelecimentos = new_hash(TAMANHO_HASH);
  c.moradores = new_hash(TAMANHO_HASH);
  c.registradores = new_hash(20);
  c.vias = new_vias();
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
  while (length_lista(c.printable_people)) {
    remove_first(c.printable_people);
  }
  free(c.printable_people);
  while (length_lista(c.printable_comercios)) {
    remove_first(c.printable_comercios);
  }
  free(c.printable_comercios);
  while (length_lista(c.printable_connections)) {
    free_connection(remove_first(c.printable_connections));
  }
  free(c.printable_connections);
  free_lista(c.printable_phones);
  free_lista(c.necroterio);

  free_quadtree(c.qt_quadras);
  free_quadtree(c.qt_hidrantes);
  free_quadtree(c.qt_semaforos);
  free_quadtree(c.qt_torres);
  quadtree_percorre(quadtree_root(c.qt_formas), destroy_dado_elemento);
  free_quadtree(c.qt_formas);

  hash_free(c.cpf_cep, free);
  hash_delete_all(c.numcel_pessoa);
  hash_delete_all(c.numcel_torre);
  hash_free(c.sercomtuel, free);
  hash_free(c.uelmobile, free);
  hash_free(c.tipo_comercio, free);
  hash_free(c.pessoas, free);
  hash_delete_all(c.cep_quadra);
  hash_free(c.estabelecimentos, free_comercio);
  hash_free(c.moradores, free_morador);
  hash_delete_all(c.registradores);
  /*algo para deletar as vias*/
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

Torre conectar_celular(Cidade c, Celular celular, Address a) {
  Torre near;
  Lista torres = create_lista();
  Node n;
  double menor, dist;
  Ponto pt = cidade_get_ponto_address(c, a);
  char op = celular_get_operadora(celular);

  quadtree_filter_to_list(quadtree_root(c.qt_torres), torres, cmp_torre_operadora, &op);

  near = get(get_first(torres), torres);
  menor = distancia(get_x(pt), get_y(pt), torre_get_x(near), torre_get_y(near));

  for (n = get_first(torres); n != NULL; n = get_next(torres, n)) {
    dist = distancia(get_x(pt), get_y(pt), torre_get_x(get(torres, n)), torre_get_y(get(torres, n)));
    if (dist < menor) {
      menor = dist;
      near = get(torres, n);
    }
  }

  while (length_lista(torres) > 0) {
    remove_first(torres);
  }
  free(torres);

  celular_conecta(celular, torre_get_id(near));

  return near;
}

Comercio cidade_comercio_proximo(Cidade c, Ponto p) {
  Comercio near = NULL;
  double menor, dist;
  Lista comercios = create_lista();

  menor = -1;

  hash_filter(c.estabelecimentos, comercios, cmp_true, NULL);

  while (length_lista(comercios) > 0) {
    Comercio co = remove_first(comercios);
    Ponto pc = cidade_get_ponto_address(c, comercio_get_address(co));
    dist = distancia(get_x(p), get_y(p), get_x(pc), get_y(pc));
    free(pc);
    if (dist < menor || menor == -1) {
      menor = dist;
      near = co;
    }
  }

  return near;
}

Ponto cidade_get_ponto_address(Cidade c, Address a) {
  Ponto p;
  Quadra q = hash_get(c.cep_quadra, address_get_cep(a));
  char face = address_get_face(a);
  int numero = address_get_numero(a);
  double x, y;

  if (q == NULL) {
    return NULL;
  }

  if (face == 'S' || face == 's') {
    x = quadra_get_x(q) + numero;
    y = quadra_get_y(q);
  } else if (face == 'N' || face == 'n') {
    x = quadra_get_x(q) + numero;
    y = quadra_get_y(q) + quadra_get_height(q);
  } else if (face == 'O' || face == 'o') {
    x = quadra_get_x(q) + quadra_get_width(q);
    y = quadra_get_y(q) + numero;
  } else if (face == 'L' || face == 'l') {
    x = quadra_get_x(q);
    y = quadra_get_y(q) + numero;
  }

  p = new_ponto(x, y);
  return p;
}

void cidade_query_clientes(Cidade c, Lista query, char *op) {
  hash_filter(c.pessoas, query, cmp_pessoa_operadora, op);
  sort_lista(query, cmp_pessoa_pessoa);
}

void cidade_query_tipos(Cidade c, Lista quadras, Lista tipos) {
  Node n, no, nod;
  char *codt;
  int achou;
  Lista comercios = create_lista();

  for (n = get_first(quadras); n != NULL; n = get_next(quadras, n)) {
    Quadra q = get(quadras, n);
    hash_filter(c.estabelecimentos, comercios, cmp_comercio_cep, quadra_get_cep(q));

    for (no = get_first(comercios); no != NULL; no = get_next(comercios, no)) {
      Comercio c = get(comercios, no);
      codt = comercio_get_codt(c);

      achou = 0;
      for (nod = get_first(tipos); nod != NULL; nod = get_next(tipos, nod)) {
        if (strcmp(codt, get(tipos, nod)) == 0) {
          achou = 1;
          break;
        }
      }

      if (!achou) {
        insert_last(tipos, codt);
      }
    }
  }
}

void cidade_kill(Cidade c, char *cpf, FILE *out) {
  Pessoa p = hash_delete(c.pessoas, cpf);
  Celular celular;
  Morador m = hash_delete(c.moradores, cpf);


  if (p == NULL) {
    fputs("Não havia pessoa com tal cpf!\n", out);
    return;
  }

  fprintf(out, "RIP: %s %s, portador do cpf %s, sexo %c, nascido em %s",
          pessoa_get_nome(p),
          pessoa_get_sobrenome(p),
          pessoa_get_cpf(p),
          pessoa_get_sexo(p),
          pessoa_get_nasc(p));

  if (m != NULL) {
    fprintf(out, ", residia em %s, face %c, %d",
            morador_get_cep(m),
            morador_get_face(m),
            morador_get_numero(m));

    insert_last(c.necroterio, cidade_get_ponto_address(c, morador_get_address(m)));

    free_morador(m);
  }

  celular = pessoa_get_celular(p);

  if (celular != NULL) {
    char op = celular_get_operadora(celular);

    hash_delete(c.sercomtuel, celular_get_numero(celular));
    hash_delete(c.uelmobile, celular_get_numero(celular));
    hash_delete(c.numcel_pessoa, celular_get_numero(celular));

    fprintf(out, ", usuario da linha movel %s, da operadora ", celular_get_numero(celular));

    if (op == 's') {
      fprintf(out, "SercomtUEL");
    } else if (op == 'u') {
      fprintf(out, "UELmobile");
    }

    free(celular);
  }

  free(p);
  fprintf(out, "\n");
}

void cidade_kikoho(Cidade c, Rect *r, FILE *out) {
  Lista quadras = create_lista();
  Lista torres = create_lista();
  Lista hidrantes = create_lista();
  Lista semaforos = create_lista();
  Lista celulares = create_lista();
  Lista moradores = create_lista();
  Lista comercios = create_lista();
  
  quadtree_filter_remove(quadtree_root(c.qt_quadras), quadras, quadra_inside_rect, r);
  quadtree_filter_remove(quadtree_root(c.qt_hidrantes), hidrantes, hidrante_inside_rect, r);
  quadtree_filter_remove(quadtree_root(c.qt_semaforos), semaforos, semaforo_inside_rect, r);
  quadtree_filter_remove(quadtree_root(c.qt_torres), torres, torre_inside_rect, r);

  fprintf(out, "Quadras demolidas: \n");
  while (length_lista(quadras) > 0) {
    Quadra q = remove_first(quadras);

    fprintf(out, "\t%s\n", quadra_get_cep(q));
    hash_filter(c.moradores, moradores, cmp_morador_cep, quadra_get_cep(q));
    hash_filter(c.estabelecimentos, comercios, cmp_comercio_cep, quadra_get_cep(q));

  }
  free(quadras);

  fprintf(out, "Moradores agora sem moradia: \n");
  while (length_lista(moradores) > 0) {
    Morador m = remove_first(moradores);
    fprintf(out,"\t%s\n", morador_get_cpf(m));
    hash_delete(c.moradores, morador_get_cep(m));
  }
  free(moradores);

  fprintf(out, "Estabelecimentos comerciais demolidos: \n");
  while (length_lista(comercios) > 0) {
    Comercio com = remove_first(comercios);
    fprintf(out,"\t%s\n", comercio_get_cnpj(com));
    hash_delete(c.moradores, comercio_get_cep(com));
  }
  free(comercios);

  fprintf(out, "Hidrantes demolidos: \n");
  while (length_lista(hidrantes) > 0) {
    Hidrante h = remove_first(hidrantes);

    fprintf(out, "\t%s\n", hidrante_get_id(h));
  }
  free(hidrantes);

  fprintf(out, "Semaforos demolidos: \n");
  while (length_lista(semaforos) > 0) {
    Semaforo s = remove_first(semaforos);

    fprintf(out, "\t%s\n", semaforo_get_id(s));
  }
  free(semaforos);

  fprintf(out, "Torres demolidas: \n");
  while (length_lista(torres) > 0) {
    Torre t = remove_first(torres);

    fprintf(out, "\t%s\n", torre_get_id(t));
    if (torre_get_operadora(t) == 's') {
      hash_filter(c.sercomtuel, celulares, cmp_celular_torre, torre_get_id(t));
    } else if (torre_get_operadora(t) == 'u') {
      hash_filter(c.uelmobile, celulares, cmp_celular_torre, torre_get_id(t));
    }

  }
  free(torres);

  fprintf(out, "Celulares desconectados: \n");
  while (length_lista(celulares) > 0) {
    Celular cel = remove_first(celulares);
    fprintf(out,"\t%s\n", celular_get_numero(cel));
    celular_disconecta(cel);
  }
  free(celulares);
  
}

void cidade_insert_register(Cidade c, char *reg, char type, void *data) {
  Register r = hash_get(c.registradores, reg);

  if (r == NULL) {
    r = new_register('p', data);
    hash_insert(c.registradores, reg, r);
  } else {
    register_set_type(r, type);
    register_set_data(r, data);
  }
}