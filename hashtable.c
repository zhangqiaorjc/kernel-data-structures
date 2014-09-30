#include "hashtable.h"
#include "list.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

struct hashtable {
    /* num of items in hashtable */
    unsigned int size;
    /* num of slots in the underlying array */
    unsigned int arraysize;
    /* minimum size of the underlying array */
    unsigned int init_size;
    /* load factor -- threshold value for array resize */
    float load_factor;
    /* chaining with linked list */
    struct list** vals;
};

struct kv_pair {
    /* key is a C string */
    char* key;
    unsigned int keylen;
    /* value can be of any type */
    void* val;
};

/* 
 * djb2 hash function
 * http://www.cse.yorku.ca/~oz/hash.html
 */
static
unsigned long
hash(char* key, unsigned int keylen)
{
    unsigned long hashval = 5381;
    int c;
    while ((c = *key)) {
        /* hashval * 33 + c */
        hashval = ((hashval << 5) + hashval) + c;
        ++key;
    }
    return hashval;
}

/*
 * Fill the array with empty lists from start to end index.
 */
static
int
init_array_with_lists(struct list** vals, unsigned int start, unsigned int end)
{
    int i;
    int j = -1;
    for (i = start; i < end; ++i) {
        vals[i] = list_create();
        if (vals[i] == NULL) {
            /* If out of memory, remember to free lists. */
            j = i;
            break;
        }
    }
    if (j >= 0) {
        /* Free all lists in the array */
        for (i = 0; i < j; ++i) {
            list_destroy(vals[i]);
        }
        return ENOMEM;
    }
    return 0;
}

/*
 * Cleanup the array with empty lists from start to end index.
 */
static
void
cleanup_array_with_lists(struct list** vals, unsigned int start, unsigned int end)
{
    int i;
    for (i = start; i < end; ++i) {
        assert(list_isempty(vals[i]));
        list_destroy(vals[i]);
    }
}

struct hashtable*
hashtable_create(unsigned int init_size, float load_factor)
{
    assert(load_factor > 0);
    struct hashtable* h = (struct hashtable*)malloc(sizeof(struct hashtable));
    h->init_size = init_size;
    h->load_factor = load_factor;
    h->size = 0;
    h->arraysize = init_size;
    h->vals = (struct list**)malloc(init_size * sizeof(struct list*));
    if (h->vals == NULL) {
        return NULL;
    }
    /* Allocate lists for the array. */
    int err = init_array_with_lists(h->vals, 0, h->arraysize);
    if (err == ENOMEM) {
        return NULL;
    }
    return h;
}

/* 
 * Typically, called after grow(...) or shrink(...).
 * Relocates all hashtable items from source array to the new array
 * in the hashtable.
 */
static
void
rehash(struct hashtable* h,
       struct list** source_array, unsigned int source_size)
{
    unsigned int i;
    struct list* chain;
    struct kv_pair* item;
    for (i = 0; i < source_size; ++i) {
        chain = source_array[i];
        assert(chain != NULL);
        if (list_getsize(chain) > 0) {
            item = (struct kv_pair*)list_front(chain);
            while (item) {
                hashtable_add(h, item->key, item->keylen, item->val);
                list_pop_front(chain);
                free(item);
                item = (struct kv_pair*)list_front(chain);
            }
            assert(list_getsize(chain) == 0);
        }
    }
}

/*
 * Double the size of the array in hashtable.
 * Relocate the hashtable elements from old array to the expanded array
 * by calling rehash(...).
 */
static
int
grow(struct hashtable* h)
{
    struct list** old_array = h->vals;
    unsigned int old_arraysize = h->arraysize;

    /* allocate a new array twice the size. */
    struct list** new_array
        = (struct list**)malloc(old_arraysize * 2 * sizeof(struct list*));
    if (new_array == NULL) {
        return ENOMEM;         
    }
    /* allocate lists for the new array. */
    int err = init_array_with_lists(new_array, 0, old_arraysize * 2);
    if (err == ENOMEM) {
        return ENOMEM;
    }

    /* replace old array with new array in hash table. */
    h->vals = new_array;
    h->size = 0;
    h->arraysize = old_arraysize * 2;

    /* relocate all items from old array to new array */
    rehash(h, old_array, old_arraysize);
    
    /* cleanup list objects in old array and free old array. */
    cleanup_array_with_lists(old_array, 0, old_arraysize);
    free(old_array);

    return 0;
}

static
float
compute_load(unsigned int num_elements, unsigned int arraysize)
{
    assert(arraysize != 0);
    return (float)num_elements / (float)arraysize;
}

int
hashtable_add(struct hashtable* h, char* key, unsigned int keylen, void* val)
{
    assert(h != NULL);
    /* If LOAD_FACTOR exceeded, double the size of array. */
    if (compute_load(h->size + 1, h->arraysize) >= h->load_factor) {
        grow(h);
    }
    /* Compute the hash to index into array. */
    int index = hash(key, keylen) % h->arraysize;
    struct list* chain = h->vals[index];
    assert(chain != NULL);
    
    /* Append the new item to end of chain. */
    struct kv_pair* new_item = (struct kv_pair*)malloc(sizeof(struct kv_pair));
    if (new_item == NULL) {
        return ENOMEM;
    }
    new_item->key = key;
    new_item->keylen = keylen;
    new_item->val = val;
    int err = list_push_back(chain, new_item);
    if (err == ENOMEM) {
        return ENOMEM;
    }

    ++h->size;

    return 0;
}

static
int
key_comparator(void* left, void* right)
{
    struct kv_pair* l = (struct kv_pair*)left;
    struct kv_pair* r = (struct kv_pair*)right;
    if (l->keylen == r->keylen) {
        return strcmp(l->key, r->key);
    }
    return (l->keylen - r->keylen);    
}

void*
hashtable_find(struct hashtable* h, char* key, unsigned int keylen)
{
    assert(h != NULL);

    /* Compute the hash to index into array. */
    int index = hash(key, keylen) % h->arraysize;
    struct list* chain = h->vals[index];
    assert(chain != NULL);
    
    /* Build a kv_pair object with the query key. */
    struct kv_pair query_item;
    query_item.key = key;
    query_item.keylen = keylen;

    struct kv_pair* found
        = (struct kv_pair*)list_find(chain, &query_item, &key_comparator);
    if (found == NULL) {
        return NULL;
    }
    return found->val;
}

/*
 * Half the size of the array in hashtable.
 * Relocate the hashtable elements from old array to the shrunk array
 * by calling rehash(...).
 */
static
int
shrink(struct hashtable* h)
{
    struct list** old_array = h->vals;
    unsigned int old_arraysize = h->arraysize;
    unsigned int new_arraysize = old_arraysize / 2;

    /* Allocate a new array half the size. */
    struct list** new_array
        = (struct list**)malloc(new_arraysize * sizeof(struct list*));
    if (new_array == NULL) {
        return ENOMEM;         
    }
    /* Allocate lists for the new array. */
    int err = init_array_with_lists(new_array, 0, new_arraysize);
    if (err == ENOMEM) {
        return ENOMEM;
    }

    /* replace old array with new array in hash table. */
    h->vals = new_array;
    h->size = 0;
    h->arraysize = new_arraysize;

    /* relocate all items from old array to new array */
    rehash(h, old_array, old_arraysize);
    
    /* cleanup list objects in old array and free old array. */
    cleanup_array_with_lists(old_array, 0, old_arraysize);
    free(old_array);

    return 0;
}

void*
hashtable_remove(struct hashtable* h, char* key, unsigned int keylen)
{
    assert(h != NULL);

    /* Compute the hash to index into array. */
    int index = hash(key, keylen) % h->arraysize;
    struct list* chain = h->vals[index];
    assert(chain != NULL);
    
    /* Build a kv_pair object with the query key. */
    struct kv_pair query_item;
    query_item.key = key;
    query_item.keylen = keylen;

    struct kv_pair* removed
        = (struct kv_pair*)list_remove(chain, &query_item, &key_comparator);
    if (removed == NULL) {
        /* Key does not exist. */
        return NULL;
    }

    /* Key value pair removed. */
    --h->size;
    if (h->arraysize > h->init_size &&
        compute_load(h->size - 1, h->arraysize) < h->load_factor) {
        /* Half the size of array. */
        shrink(h);
    }
    void* res = removed->val;
    free(removed);
    
    return res;
}

int
hashtable_isempty(struct hashtable* h)
{
    assert(h != NULL);
    return (h->size == 0);
}

unsigned int
hashtable_getsize(struct hashtable* h)
{
    assert(h != NULL);
    return h->size;
}

void
hashtable_destroy(struct hashtable* h)
{
    if (h != NULL) {
        free(h->vals);
    }
    free(h);
}

void
hashtable_assertvalid(struct hashtable* h)
{
    assert(h != NULL);
    /* Validate if the size of items in the hashtable is correct. */
    unsigned int count = 0;
    unsigned int i, j, size;
    struct list* chain;
    struct kv_pair* kv;
    for (i = 0; i < h->arraysize; ++i) {
        chain = h->vals[i];
        assert(chain != NULL);
        size = list_getsize(chain);
        count += size;
        /* check if key hashes to the correct index */
        for (j = 0; j < size; ++j) {
            kv = (struct kv_pair*)list_front(chain);
            assert(hash(kv->key, kv->keylen) % h->arraysize == i);
            list_pop_front(chain);
            list_push_back(chain, kv);
        }
    }
    assert(count == h->size);
}

