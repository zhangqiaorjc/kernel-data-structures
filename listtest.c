#include "list.h"
#include <stdio.h>
#include <assert.h>

#define TESTSIZE 133

static
int
int_comparator(void* left, void* right)
{
    int l = *(int*)left;
    int r = *(int*)right;
    return l-r;
}

int
list_test()
{
    printf("Beginning list test...\n");

    struct list* newlist;
    newlist = list_create();
    assert(newlist != NULL);
    assert(list_getsize(newlist) == 0);
    assert(list_isempty(newlist));

    int i, found, removed;
    int* elem;
    /* push back TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)malloc(sizeof(int));
        *elem = i;
        list_push_back(newlist, (void*) elem);
        /* find the element added */
        found = *(int*)list_find(newlist, (void*) elem, &int_comparator);
        assert(found == i);
    }
    assert(list_getsize(newlist) == TESTSIZE);
    assert(!list_isempty(newlist));

    /* remove TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)malloc(sizeof(int));
        *elem = i;
        /* remove the element added */
        removed = *(int*)list_remove(newlist, (void*) elem, &int_comparator);
        assert(removed == i);
    }
    assert(list_getsize(newlist) == 0);
    assert(list_isempty(newlist));

    /* push back TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)malloc(sizeof(int));
        *elem = i;
        list_push_back(newlist, (void*) elem);
        /* find the element added */
        found = *(int*)list_find(newlist, (void*) elem, &int_comparator);
        assert(found == i);
    }

    /* pop front TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)list_front(newlist);
        assert(*elem == i);
        list_pop_front(newlist);
        free(elem);
    }
    assert(list_getsize(newlist) == 0);
    assert(list_isempty(newlist));

    /* REPEAT to check if list is reusable */

    /* push back TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)malloc(sizeof(int));
        *elem = i;
        list_push_back(newlist, (void*) elem);
        /* find the element added */
        found = *(int*)list_find(newlist, (void*) elem, &int_comparator);
        assert(found == i);
    }
    assert(list_getsize(newlist) == TESTSIZE);
    assert(!list_isempty(newlist));

    /* remove TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)malloc(sizeof(int));
        *elem = i;
        /* remove the element added */
        removed = *(int*)list_remove(newlist, (void*) elem, &int_comparator);
        assert(removed == i);
    }
    assert(list_getsize(newlist) == 0);
    assert(list_isempty(newlist));

    /* push back TESTSIZE number of elements */
    for (i = 0; i < TESTSIZE; ++i) {
        elem = (int*)malloc(sizeof(int));
        *elem = i;
        list_push_back(newlist, (void*) elem);
        /* find the element added */
        found = *(int*)list_find(newlist, (void*) elem, &int_comparator);
        assert(found == i);
    }

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
