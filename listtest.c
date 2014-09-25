#include "list.h"
#include <stdio.h>
#include <assert.h>

#define TESTSIZE 133

int
list_test()
{
    printf("large list test\n");

    struct list* newlist;
    newlist = list_create();
    assert(newlist != NULL);
    assert(list_getsize(newlist) == 0);
    assert(list_isempty(newlist));

    /* push back TESTSIZE number of elements */
    int i;
    for (i = 0; i < TESTSIZE; ++i) {
        list_push_back(newlist, (void*) i);
    }
    assert(list_getsize(newlist) == TESTSIZE);
    assert(!list_isempty(newlist));

    /* pop front TESTSIZE number of elements */
    int elem;
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int)list_pop_front(newlist);
        assert(elem == i);
    }
    assert(list_getsize(newlist) == 0);
    assert(list_isempty(newlist));

    /* push back TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        list_push_back(newlist, (void*) i);
    }
    assert(list_getsize(newlist) == TESTSIZE);
    assert(!list_isempty(newlist));

    /* pop front TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int)list_pop_front(newlist);
        assert(elem == i);
    }
    assert(list_getsize(newlist) == 0);
    assert(list_isempty(newlist));

    list_destroy(newlist);

    printf("large list test complete\n");

    return 0;
}

int
main(int nargs, char** args)
{
    (void)nargs;
    (void)args;

    printf("Beginning list test...\n");
    list_test();
    printf("List test complete\n");
}
