t1: t1.o nick_string.o
		gcc -o t1 t1.o nick_string.o -g

t1.o: t1.c
		gcc -c t1.c

t2: t2.o circ.o rect.o coord.o nick_string.o
		gcc -o t2 t2.o circ.o -g

t2.o: t2.c
		gcc -c t2.c

coord.o: modules/coord/coord.c
		gcc -c modules/coord/coord.c

nick_string.o: modules/nick_string/nick_string.c
		gcc -c modules/nick_string/nick_string.c

circ.o: modules/circ/circ.c
		gcc -c modules/circ/circ.c

rect.o: modules/rect/rect.c
		gcc -c modules/rect/rect.c
