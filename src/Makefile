t1: t1.o nick_string.o
		gcc -o t1 t1.o nick_string.o -g -ansi -pedantic

t1.o: t1.c
		gcc -c t1.c -ansi -pedantic

t2: t2.o geo.o coord.o rect.o circ.o nick_string.o
		gcc -o t2 t2.o geo.o coord.o rect.o circ.o nick_string.o -lm -g -ansi -pedantic

t2.o: t2.c
		gcc -c t2.c -g -ansi -pedantic

geo.o: modules/geo/geo.c coord.o circ.o rect.o
		gcc -c modules/geo/geo.c -lm -g -ansi -pedantic

coord.o: modules/coord/coord.c
		gcc -c modules/coord/coord.c -lm -ansi -pedantic

nick_string.o: modules/nick_string/nick_string.c
		gcc -c modules/nick_string/nick_string.c -ansi -pedantic

circ.o: modules/circ/circ.c coord.o
		gcc -c modules/circ/circ.c -ansi -pedantic

rect.o: modules/rect/rect.c coord.o
		gcc -c modules/rect/rect.c -ansi -pedantic

clean:
		rm -f *.o
