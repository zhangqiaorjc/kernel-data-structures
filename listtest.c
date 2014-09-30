#include "list.h"
#include <stdio.h>
#include <assert.h>

#define TESTSIZE 133

int
list_test()
{
    printf("Beginning list test...\n");

    struct list* newlist;
    newlist = list_create();
    assert(newlist != NULL);
    assert(list_getsize(newlist) == 0);
    assert(list_isempty(newlist));

    int i;
    int* elem;
    /* push back TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)malloc(sizeof(int));
        *elem = i;
        list_push_back(newlist, (void*) elem);
    }
    assert(list_getsize(newlist) == TESTSIZE);
    assert(!list_isempty(newlist));

    /* pop front TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)list_front(newlist);
        assert(*elem == i);
        list_pop_front(newlist);
        free(elem);
    }
    assert(list_getsize(newlist) == 0);
    assert(list_isempty(newlist));

    /* push back TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)malloc(sizeof(int));
        *elem = i;
        list_push_back(newlist, (void*) elem);
    }
    assert(list_getsize(newlist) == TESTSIZE);
    assert(!list_isempty(newlist));

    /* pop front TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)list_front(newlist);
        assert(*elem == i);
        list_pop_front(newlist);
        free(elem);
    }
    assert(list_getsize(newlist) == 0);
    assert(list_isempty(newlist));

    list_destroy(newlist);

    printf("List test complete\n");

    return 0;
}

int
main(int nargs, char** args)
{
    (void)nargs;
    (void)args;

    list_test();
}
