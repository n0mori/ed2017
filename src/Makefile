cc = gcc -ansi -pedantic -g -lm -Wall
deps_t2 = t2.o svg.o Geo.o Rect.o Circ.o Nick_string.o Elemento.o ListaEstatica.o
deps_geo = Geo.o Circ.o Rect.o
deps_cidade = Cidade.o Quadra.o Hidrante.o Semaforo.o Torre.o Hash.o Comparacao.o Comercio.o Pessoa.o Morador.o Address.o Celular.o
deps_sorts = Sorting.o
deps_siguel = $(deps_cidade) $(deps_geo) svg.o Nick_string.o Lista.o Elemento.o $(deps_sorts) Quadtree.o Ponto.o Pilha.o Convex.o Connection.o
unit = unit_tests

t1: t1.o nick_string.o
	gcc -o t1 t1.o nick_string.o -g -ansi -pedantic

t1.o: t1.c
	gcc -c t1.c -ansi -pedantic

t2:	$(deps_t2)
	$(cc) $(deps_t2) -o t2

t2.o: t2.c
	$(cc) -c t2.c

siguel: siguel.o $(deps_siguel)
	$(cc) siguel.o $(deps_siguel) -o siguel

siguel.o: siguel.c
	$(cc) -c siguel.c

Address.o: modules/Address/Address.c
	$(cc) -c modules/Address/Address.c

Cidade.o: modules/Cidade/Cidade.c
	$(cc) -c modules/Cidade/Cidade.c

Quadra.o: modules/Quadra/Quadra.c
	$(cc) -c modules/Quadra/Quadra.c

Hidrante.o: modules/Hidrante/Hidrante.c
	$(cc) -c modules/Hidrante/Hidrante.c

Semaforo.o: modules/Semaforo/Semaforo.c
	$(cc) -c modules/Semaforo/Semaforo.c

Torre.o: modules/Torre/Torre.c
	$(cc) -c modules/Torre/Torre.c

Geo.o: modules/Geo/Geo.c
	$(cc) -c modules/Geo/Geo.c

svg.o: modules/svg/svg.c Geo.o
	$(cc) -c modules/svg/svg.c

Nick_string.o: modules/Nick_string/Nick_string.c
	$(cc) -c modules/Nick_string/Nick_string.c

Circ.o: modules/Circ/Circ.c
	$(cc) -c modules/Circ/Circ.c

Rect.o: modules/Rect/Rect.c
	$(cc) -c modules/Rect/Rect.c

Elemento.o: modules/Elemento/Elemento.c
	$(cc) -c modules/Elemento/Elemento.c

ListaEstatica.o: modules/ListaEstatica/ListaEstatica.c Elemento.o
	$(cc) -c modules/ListaEstatica/ListaEstatica.c

Lista.o: modules/Lista/Lista.c
	$(cc) -c modules/Lista/Lista.c

Pilha.o: modules/Pilha/Pilha.c
	$(cc) -c modules/Pilha/Pilha.c

Sorting.o: modules/Sorting/Sorting.c
	$(cc) -c modules/Sorting/Sorting.c

Comparacao.o: modules/Comparacao/Comparacao.c
	$(cc) -c modules/Comparacao/Comparacao.c

Quadtree.o: modules/Quadtree/Quadtree.c
	$(cc) -c modules/Quadtree/Quadtree.c

Convex.o: modules/Convex/Convex.c
	$(cc) -c modules/Convex/Convex.c

Ponto.o: modules/Ponto/Ponto.c
	$(cc) -c modules/Ponto/Ponto.c

Pessoa.o: modules/Pessoa/Pessoa.c
	$(cc) -c modules/Pessoa/Pessoa.c

Comercio.o: modules/Comercio/Comercio.c
	$(cc) -c modules/Comercio/Comercio.c

TipoCom.o: modules/TipoCom/TipoCom.c
	$(cc) -c modules/TipoCom/TipoCom.c

Celular.o: modules/Celular/Celular.c
	$(cc) -c modules/Celular/Celular.c

Connection.o: modules/Connection/Connection.c
	$(cc) -c modules/Connection/Connection.c

Morador.o: modules/Morador/Morador.c
	$(cc) -c modules/Morador/Morador.c

Hash.o: modules/Hash/Hash.c
	$(cc) -c modules/Hash/Hash.c

Grafo.o: modules/Grafo/Grafo.c
	$(cc) -c modules/Grafo/Grafo.c

teste_lista.o: $(unit)/teste_lista.c
	$(cc) -c $(unit)/teste_lista.c

teste_lista: teste_lista.o Lista.o Geo.o Rect.o Circ.o
	$(cc) teste_lista.o Lista.o Geo.o Rect.o Circ.o -o teste_lista

teste_pilha.o: $(unit)/teste_pilha.c
	$(cc) -c $(unit)/teste_pilha.c

teste_pilha: teste_pilha.o Pilha.o
	$(cc) teste_pilha.o Pilha.o -o teste_pilha

teste_quadras.o: $(unit)/teste_quadras.c
	$(cc) -c $(unit)/teste_quadras.c

teste_quadras: teste_quadras.o Lista.o Quadra.o
	$(cc) teste_quadras.o Lista.o Quadra.o -o teste_quadras

teste_sorting.o: $(unit)/teste_sorting.c
	$(cc) -c $(unit)/teste_sorting.c

teste_sorting: teste_sorting.o Lista.o Sorting.o Quadra.o Comparacao.o
	$(cc) teste_sorting.o Lista.o Sorting.o Quadra.o Comparacao.o -o teste_sorting

teste_quadtree.o: $(unit)/teste_quadtree.c
	$(cc) -c $(unit)/teste_quadtree.c

teste_quadtree: teste_quadtree.o Quadtree.o Quadra.o svg.o
	$(cc) teste_quadtree.o Quadra.o Quadtree.o svg.o -o teste_quadtree

teste_convex.o: $(unit)/teste_convex.c
	$(cc) -c $(unit)/teste_convex.c

teste_convex: teste_convex.o 	$(deps_siguel)
	$(cc) teste_convex.o $(deps_siguel) -o teste_convex

teste_colisao.o: $(unit)/teste_colisao.c
	$(cc) -c $(unit)/teste_colisao.c

teste_colisao: teste_colisao.o Geo.o Rect.o Circ.o
	$(cc) teste_colisao.o Geo.o Rect.o Circ.o -o teste_colisao

teste_hash.o: $(unit)/teste_hash.c
	$(cc) -c $(unit)/teste_hash.c

teste_hash: teste_hash.o Lista.o Hash.o Pessoa.o Comercio.o
	$(cc) teste_hash.o Lista.o Hash.o Pessoa.o Comercio.o -o teste_hash

teste_grafo.o: $(unit)/teste_grafo.c
	$(cc) -c $(unit)/teste_grafo.c

teste_grafo: teste_grafo.o Lista.o Hash.o Grafo.o Nick_string.o
	$(cc) teste_grafo.o Lista.o Hash.o Grafo.o Nick_string.o -o teste_grafo

clean:
	rm -f *.o
