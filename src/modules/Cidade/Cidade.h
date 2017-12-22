#ifndef CIDADE__H
#define CIDADE__H

/* Uma cidade é uma representação de uma cidade real. Possui uma quantidade
indeterminada de quarteiroes, hidrantes, semaforos, torres de celular, etc.
*/

#include <stdio.h>
#include "../Lista/Lista.h"
#include "../Quadtree/Quadtree.h"
#include "../Geo/Geo.h"
#include "../Elemento/Elemento.h"
#include "../Quadra/Quadra.h"
#include "../Hidrante/Hidrante.h"
#include "../Semaforo/Semaforo.h"
#include "../Torre/Torre.h"
#include "../Hash/Hash.h"
#include "../Comparacao/Comparacao.h"
#include "../Pessoa/Pessoa.h"
#include "../Comercio/Comercio.h"
#include "../Morador/Morador.h"
#include "../Celular/Celular.h"
#include "../Ponto/Ponto.h"
#include "../Connection/Connection.h"
#include "../Sorting/Sorting.h"

typedef struct cidade {
  Lista lista_quadras;
  Lista lista_hidrantes;
  Lista lista_semaforos;
  Lista lista_torres;
  Lista lista_formas;
  Lista printable_people;
  Lista printable_comercios;
  Lista printable_connections;
  Lista printable_phones;
  Quadtree qt_quadras;
  Quadtree qt_hidrantes;
  Quadtree qt_semaforos;
  Quadtree qt_torres;
  Quadtree qt_formas;
  Hash cpf_cep;
  Hash numcel_pessoa;
  Hash numcel_torre;
  Hash sercomtuel;
  Hash uelmobile;
  Hash tipo_comercio;
  Hash pessoas;
  Hash cep_quadra;
  Hash estabelecimentos;
  Hash moradores;
} Cidade;

Cidade new_cidade();
void insere_quadra(Cidade c, Quadra q, int *cmp, int *insercoes);
void insere_hidrante(Cidade c, Hidrante h);
void insere_semaforo(Cidade c, Semaforo s);
void insere_torre(Cidade c, Torre t);
void insere_forma(Cidade c, Elemento *e);
Elemento *search_forma_lista(Cidade c, int id);
void free_cidade(Cidade c);
void remove_quadras_in_rect(Cidade c, FILE *f, Rect *r, int *cmp, int *del);
void remove_hidrantes_in_rect(Cidade c, FILE *f, Rect *r);
void remove_semaforos_in_rect(Cidade c, FILE *f, Rect *r);
void remove_torres_in_rect(Cidade c, FILE *f, Rect *r);
void remove_quadras_in_circ(Cidade c, FILE *f, Circ *ci, int *cmp, int *del);
void remove_hidrantes_in_circ(Cidade c, FILE *f, Circ *ci);
void remove_semaforos_in_circ(Cidade c, FILE *f, Circ *ci);
void remove_torres_in_circ(Cidade c, FILE *f, Circ *ci);
void search_cep_or_id(Cidade c, FILE *f, char *id);
Torre conectar_celular(Cidade c, Celular celular, Address a);
Ponto cidade_get_ponto_address(Cidade c, Address a);
void cidade_query_clientes(Cidade c, Lista query, char *op);
void cidade_query_tipos(Cidade c, Lista quadras, Lista tipos);

#endif
