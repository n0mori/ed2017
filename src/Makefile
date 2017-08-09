cc = gcc -ansi -pedantic -g -lm
deps_t2 = t2.o svg.o Geo.o Rect.o Circ.o Nick_string.o Elemento.o ListaEstatica.o
deps_geo = Geo.o Circ.o Rect.o
deps_cidade = Cidade.o Quadra.o Hidrante.o Semaforo.o Torre.o
deps_siguel = siguel.o $(deps_cidade) $(deps_geo) svg.o Nick_string.o Lista.o Elemento.o

t1: t1.o nick_string.o
	gcc -o t1 t1.o nick_string.o -g -ansi -pedantic

t1.o: t1.c
	gcc -c t1.c -ansi -pedantic

t2:	$(deps_t2)
	$(cc) $(deps_t2) -o t2

t2.o: t2.c
	$(cc) -c t2.c

siguel: $(deps_siguel)
	$(cc) $(deps_siguel) -o siguel

siguel.o: siguel.c
	$(cc) -c siguel.c

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

teste_lista.o: teste_lista.c
	$(cc) -c teste_lista.c

teste_lista: teste_lista.o Lista.o Geo.o Rect.o Circ.o
	$(cc) teste_lista.o Lista.o Geo.o Rect.o Circ.o -o teste_lista

teste_quadras.o: teste_quadras.c
	$(cc) -c teste_quadras.c

teste_quadras: teste_quadras.o Lista.o Quadra.o
	$(cc) teste_quadras.o Lista.o Quadra.o -o teste_quadras

clean:
	rm -f *.o
