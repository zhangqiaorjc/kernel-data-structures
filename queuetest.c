#include "queue.h"
#include <stdio.h>
#include <assert.h>

#define TESTSIZE 133

int
queue_test()
{
    printf("Beginning queue test...\n");

    struct queue* newqueue;
    newqueue = queue_create();
    assert(newqueue != NULL);
    assert(queue_getsize(newqueue) == 0);
    assert(queue_isempty(newqueue));

    int i;
    int* elem;
    /* push back TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)malloc(sizeof(int));
        *elem = i;
        queue_push(newqueue, (void*) elem);
    }
    assert(queue_getsize(newqueue) == TESTSIZE);
    assert(!queue_isempty(newqueue));

    /* pop front TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)queue_front(newqueue);
        assert(*elem == i);
        queue_pop(newqueue);
        free(elem);
    }
    assert(queue_getsize(newqueue) == 0);
    assert(queue_isempty(newqueue));

    /* push back TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)malloc(sizeof(int));
        *elem = i;
        queue_push(newqueue, (void*) elem);
    }
    assert(queue_getsize(newqueue) == TESTSIZE);
    assert(!queue_isempty(newqueue));

    /* pop front TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)queue_front(newqueue);
        assert(*elem == i);
        queue_pop(newqueue);
        free(elem);
    }
    assert(queue_getsize(newqueue) == 0);
    assert(queue_isempty(newqueue));

    queue_destroy(newqueue);

    printf("queue test complete\n");

    return 0;
}

int
main(int nargs, char** args)
{
    (void)nargs;
    (void)args;

    queue_test();
}
