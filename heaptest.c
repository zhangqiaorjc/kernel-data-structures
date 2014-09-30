#include "heap.h"
#include <stdio.h>
#include <assert.h>

#define TESTSIZE 1333

/* less comparator for int */
int int_lessthan(const void* left, const void* right) {
    int l = *(int*)left;
    int r = *(int*)right;
    return (l < r);
}

static
int
test_heap_push_pop(void)
{
    struct heap* newheap;
    newheap = heap_create(&int_lessthan);
    assert(newheap != NULL);
    assert(heap_getsize(newheap) == 0);
    assert(heap_isempty(newheap));

    int i;
    int* elem;
    /* push TESTSIZE number of elements */
    for (i = TESTSIZE - 1; i >= 0; --i) {
        elem = (int*)malloc(sizeof(int));
        *elem = i;
        heap_push(newheap, (void*)elem);
    }
    assert(heap_getsize(newheap) == TESTSIZE);
    assert(!heap_isempty(newheap));

    /* pop TESTSIZE number of elements; expect numbers in increasing order */
    for (i = 0; i < TESTSIZE; ++i) {
        assert(*(int*)heap_top(newheap) == i);
        elem = (int*)heap_pop(newheap);
        assert(*elem == i);
        /* REMEMBER to free elements we allocated in the beginning */
        free(elem);
    }
    assert(heap_getsize(newheap) == 0);
    assert(heap_isempty(newheap));

    /* REPEAT to test if the heap is reusable */

    /* push TESTSIZE number of elements */
    for (i = TESTSIZE - 1; i >= 0; --i) {
        elem = (int*)malloc(sizeof(int));
        *elem = i;
        heap_push(newheap, (void*)elem);
    }
    assert(heap_getsize(newheap) == TESTSIZE);
    assert(!heap_isempty(newheap));

    /* pop TESTSIZE number of elements; expect numbers in increasing order */
    for (i = 0; i < TESTSIZE; ++i) {
        assert(*(int*)heap_top(newheap) == i);
        elem = (int*)heap_pop(newheap);
        assert(*elem == i);
        /* REMEMBER to free elements we allocated in the beginning */
        free(elem);
    }
    assert(heap_getsize(newheap) == 0);
    assert(heap_isempty(newheap));

    heap_destroy(newheap);

    return 0;
}

int
heap_test(void)
{
    printf("Beginning heap test...\n");

    test_heap_push_pop();

    printf("heap test complete\n");

    return 0;
}

int
main(int nargs, char** args)
{
    (void)nargs;
    (void)args;

    heap_test();
}
