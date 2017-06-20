t1: t1.o nick_string.o
		gcc -o t1 t1.o nick_string.o -g

t1.o: t1.c
		gcc -c t1.c

t2: t2.o modules/coord/coord.h circ.o rect.o nick_string.o
		gcc -o t2 t2.o modules/coord/coord.h circ.o rect.o nick_string.o -g

t2.o: t2.c
		gcc -c t2.c

coord.o: modules/coord/coord.h
		gcc -c modules/coord/coord.h

nick_string.o: modules/nick_string/nick_string.c
		gcc -c modules/nick_string/nick_string.c

circ.o: modules/circ/circ.c modules/circ/circ.o
		gcc -c modules/circ/circ.c

rect.o: modules/rect/rect.c
		gcc -c modules/rect/rect.c
