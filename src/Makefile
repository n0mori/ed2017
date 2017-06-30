t1: t1.o nick_string.o
		gcc -o t1 t1.o nick_string.o -g -ansi -pedantic

t1.o: t1.c
		gcc -c t1.c -ansi -pedantic

t2: t2.o svg.o Geo.o Rect.o Circ.o Nick_string.o Elemento.o
		gcc -o t2 t2.o svg.o Geo.o Rect.o Circ.o Nick_string.o Elemento.o -lm -g -ansi -pedantic

t2.o: t2.c
		gcc -c t2.c -g -ansi -pedantic

Geo.o: modules/Geo/Geo.c Circ.o Rect.o
		gcc -c modules/Geo/Geo.c -lm -g -ansi -pedantic

svg.o: modules/svg/svg.c Geo.o
		gcc -c modules/svg/svg.c -lm -g -ansi -pedantic

Nick_string.o: modules/Nick_string/Nick_string.c
		gcc -c modules/Nick_string/Nick_string.c -ansi -pedantic

Circ.o: modules/Circ/Circ.c
		gcc -c modules/Circ/Circ.c -ansi -pedantic

Rect.o: modules/Rect/Rect.c
		gcc -c modules/Rect/Rect.c -ansi -pedantic

Elemento.o: modules/Elemento/Elemento.c
		gcc -c modules/Elemento/Elemento.c -ansi -pedantic

clean:
		rm -f *.o
