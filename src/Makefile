cc = gcc -ansi -pedantic -O0 -g -lm
deps_t2 = t2.o svg.o Geo.o Rect.o Circ.o Nick_string.o Elemento.o

t1: t1.o nick_string.o
		gcc -o t1 t1.o nick_string.o -g -ansi -pedantic

t1.o: t1.c
		gcc -c t1.c -ansi -pedantic

t2:	$(deps_t2)
		$(cc) $(deps_t2) -o t2

t2.o: t2.c
		$(cc) -c t2.c

Geo.o: modules/Geo/Geo.c Circ.o Rect.o
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

clean:
		rm -f *.o
