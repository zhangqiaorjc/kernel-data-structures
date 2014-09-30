CC=g++
CFLAGS=-m32

all: listtest queuetest heaptest hashtabletest

listtest: list.o listtest.o; \
    $(CC) listtest.o list.o -o listtest $(CFLAGS)

list.o: list.c list.h; \
    $(CC) -c list.c $(CFLAGS)

listtest.o: listtest.c; \
    $(CC) -c listtest.c $(CFLAGS)

queuetest: list.o queue.o queuetest.o; \
    $(CC) queuetest.o queue.o list.o -o queuetest $(CFLAGS)

queue.o: queue.c queue.h; \
    $(CC) -c queue.c $(CFLAGS)

queuetest.o: queuetest.c; \
    $(CC) -c queuetest.c $(CFLAGS)

heaptest: heap.o heaptest.o; \
    $(CC) heaptest.o heap.o -o heaptest $(CFLAGS)

heap.o: heap.c heap.h; \
    $(CC) -c heap.c $(CFLAGS)

heaptest.o: heaptest.c; \
    $(CC) -c heaptest.c $(CFLAGS)

hashtabletest: list.o hashtable.o hashtabletest.o; \
    $(CC) hashtabletest.o hashtable.o list.o -o hashtabletest $(CFLAGS)

hashtable.o: hashtable.c hashtable.h; \
    $(CC) -c hashtable.c $(CFLAGS)

hashtabletest.o: hashtabletest.c; \
    $(CC) -c hashtabletest.c $(CFLAGS)
