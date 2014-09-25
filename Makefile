CC=g++
CFLAGS=-m32

listtest: list.o listtest.o; \
    $(CC) listtest.o list.o -o listtest $(CFLAGS)

list.o: list.c list.h; \
    $(CC) -c list.c $(CFLAGS)

listtest.o: listtest.c; \
    $(CC) -c listtest.c $(CFLAGS)
