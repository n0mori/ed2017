t1: t1.o nick_string.o
		gcc -o t1 t1.o nick_string.o -g -ansi -pedantic

t1.o: t1.c
		gcc -c t1.c -ansi -pedantic

t2: t2.o svg.o geo.o rect.o circ.o nick_string.o elemento.o
		gcc -o t2 t2.o svg.o geo.o rect.o circ.o nick_string.o elemento.o -lm -g -ansi -pedantic

t2.o: t2.c
		gcc -c t2.c -g -ansi -pedantic

geo.o: modules/geo/geo.c circ.o rect.o
		gcc -c modules/geo/geo.c -lm -g -ansi -pedantic

svg.o: modules/svg/svg.c geo.o
		gcc -c modules/svg/svg.c -lm -g -ansi -pedantic

nick_string.o: modules/nick_string/nick_string.c
		gcc -c modules/nick_string/nick_string.c -ansi -pedantic

circ.o: modules/circ/circ.c
		gcc -c modules/circ/circ.c -ansi -pedantic

rect.o: modules/rect/rect.c
		gcc -c modules/rect/rect.c -ansi -pedantic

elemento.o: modules/elemento/elemento.c
		gcc -c modules/elemento/elemento.c -ansi -pedantic

clean:
		rm -f *.o