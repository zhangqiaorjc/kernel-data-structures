#include "hashtable.h"
#include <stdio.h>
#include <assert.h>

#define TESTSIZE 1333

int
hashtable_test(void)
{
    printf("Beginning hashtable test...\n");

    struct hashtable* newhashtable;
    newhashtable = hashtable_create(2, 0.5);
    assert(newhashtable != NULL);
    assert(hashtable_getsize(newhashtable) == 0);
    assert(hashtable_isempty(newhashtable));
    hashtable_assertvalid(newhashtable);

    /* Add key value pairs to hashtable. */
    char key1[] = "a";
    char key2[] = "aa";
    char key3[] = "aaa";
    char key4[] = "aaaa";
    int val1 = 111;
    int val2 = 222;
    int val3 = 333;
    int val4 = 444;
    assert(hashtable_add(newhashtable, key1, 1, &val1) == 0);
    assert(hashtable_add(newhashtable, key2, 2, &val2) == 0);
    assert(hashtable_add(newhashtable, key3, 3, &val3) == 0);
    assert(hashtable_add(newhashtable, key4, 4, &val4) == 0);
    assert(hashtable_getsize(newhashtable) == 4);
    assert(!hashtable_isempty(newhashtable));
    hashtable_assertvalid(newhashtable);

    /* Lookup keys from hashtable. */
    int found_val1 = *(int*)hashtable_find(newhashtable, key1, 1);
    assert(found_val1 == val1);

    int found_val2 = *(int*)hashtable_find(newhashtable, key2, 2);
    assert(found_val2 == val2);

    int found_val3 = *(int*)hashtable_find(newhashtable, key3, 3);
    assert(found_val3 == val3);

    int found_val4 = *(int*)hashtable_find(newhashtable, key4, 4);
    assert(found_val4 == val4);

    assert(hashtable_getsize(newhashtable) == 4);
    assert(!hashtable_isempty(newhashtable));
    hashtable_assertvalid(newhashtable);

    /* Remove keys from hashtable. */
    int removed_val1 = *(int*)hashtable_remove(newhashtable, key1, 1);
    assert(removed_val1 == val1);

    int removed_val2 = *(int*)hashtable_remove(newhashtable, key2, 2);
    assert(removed_val2 == val2);

    int removed_val3 = *(int*)hashtable_remove(newhashtable, key3, 3);
    assert(removed_val3 == val3);

    int removed_val4 = *(int*)hashtable_remove(newhashtable, key4, 4);
    assert(removed_val4 == val4);

    assert(hashtable_getsize(newhashtable) == 0);
    assert(hashtable_isempty(newhashtable));
    hashtable_assertvalid(newhashtable);

    /* REPEAT to check if hash table is reusable */
    assert(hashtable_add(newhashtable, key1, 1, &val1) == 0);
    assert(hashtable_add(newhashtable, key2, 2, &val2) == 0);
    assert(hashtable_add(newhashtable, key3, 3, &val3) == 0);
    assert(hashtable_add(newhashtable, key4, 4, &val4) == 0);
    assert(hashtable_getsize(newhashtable) == 4);
    assert(!hashtable_isempty(newhashtable));
    hashtable_assertvalid(newhashtable);

    /* Lookup keys from hashtable. */
    found_val1 = *(int*)hashtable_find(newhashtable, key1, 1);
    assert(found_val1 == val1);

    found_val2 = *(int*)hashtable_find(newhashtable, key2, 2);
    assert(found_val2 == val2);

    found_val3 = *(int*)hashtable_find(newhashtable, key3, 3);
    assert(found_val3 == val3);

    found_val4 = *(int*)hashtable_find(newhashtable, key4, 4);
    assert(found_val4 == val4);

    assert(hashtable_getsize(newhashtable) == 4);
    assert(!hashtable_isempty(newhashtable));
    hashtable_assertvalid(newhashtable);

    /* Remove keys from hashtable. */
    removed_val1 = *(int*)hashtable_remove(newhashtable, key1, 1);
    assert(removed_val1 == val1);

    removed_val2 = *(int*)hashtable_remove(newhashtable, key2, 2);
    assert(removed_val2 == val2);

    removed_val3 = *(int*)hashtable_remove(newhashtable, key3, 3);
    assert(removed_val3 == val3);

    removed_val4 = *(int*)hashtable_remove(newhashtable, key4, 4);
    assert(removed_val4 == val4);

    assert(hashtable_getsize(newhashtable) == 0);
    assert(hashtable_isempty(newhashtable));
    hashtable_assertvalid(newhashtable);

    /* Destroys hashtable. */
    hashtable_destroy(newhashtable);

    printf("hashtable test complete\n");

    return 0;
}

int
main(int nargs, char** args)
{
    (void)nargs;
    (void)args;

    hashtable_test();
}
