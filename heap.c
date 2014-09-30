#include "heap.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define DEFAULT_SIZE 8
#define PARENT(i) ((i) - 1) / 2
#define LEFT(i) 2 * (i) + 1
#define RIGHT(i) 2 * (i) + 2

struct heap {
    int(*comparator)(const void*, const void*);
    unsigned int size;
    unsigned int max_size;
    void** vals;
};

void
bubble_up(struct heap* h, int index)
{
    assert(index >= 0);
    int p = PARENT(index);
    void* t;
    while (index > 0 && h->comparator(h->vals[index], h->vals[p])) {
        /* SWAP */
        t = h->vals[index];
        h->vals[index] = h->vals[p];
        h->vals[p] = t;
        index = p;
        p = PARENT(index);
    }
}

void
trickle_down(struct heap* h, int index)
{
    int j, r, l;
    void* t;
    while (index >= 0) {
        j = -1;
        r = RIGHT(index);
        if (r < h->size && h->comparator(h->vals[r], h->vals[index])) {
            l = LEFT(index);
            if (h->comparator(h->vals[l], h->vals[r])) {
                j = l;
            } else {
                j = r;
            }
        } else {
            l = LEFT(index);
            if (l < h->size && h->comparator(h->vals[l], h->vals[index])) {
                j = l;
            }
        }
        if (j >= 0) {
            /* SWAP */
            t = h->vals[j];
            h->vals[j] = h->vals[index];
            h->vals[index] = t;
        }
        index = j;
    }
}

struct heap*
heap_create(int (*comparator)(const void*, const void*))
{
    struct heap* h = (struct heap*)malloc(sizeof(struct heap));
    h->comparator = comparator;
    h->size = 0;
    h->max_size = DEFAULT_SIZE;
    h->vals = (void**)malloc(DEFAULT_SIZE * sizeof(void*));
    if (h->vals == NULL) {
        return NULL;
    }
    return h;
}

void
heap_push(struct heap* h, void* newval)
{
    assert(h != NULL);
    /* if array is full, double the size of array */
    if (h->size + 1 > h->max_size) {
        // TODO: watch out for overflow.
        /* double array */
        void** new_array = (void**)malloc(h->max_size * 2 * sizeof(void*));
        memcpy(new_array, h->vals, h->size * sizeof(void*));
        free(h->vals);
        h->vals = new_array;
        h->max_size *= 2;
    }
    h->vals[h->size] = newval;
    /* heapify up from the last element until root */
    bubble_up(h, h->size);
    ++h->size;
}

void*
heap_pop(struct heap* h)
{
    assert(h != NULL);
    if (h->size == 0) {
        return NULL;
    }
    void* top = h->vals[0];
    h->vals[0] = h->vals[h->size - 1];
    --h->size;
    trickle_down(h, 0);
    /* half the array */
    if (2 * h->size < h->max_size) {
        void** new_array = (void**)malloc(h->max_size / 2 * sizeof(void*));
        memcpy(new_array, h->vals, h->size * sizeof(void*));
        free(h->vals);
        h->vals = new_array;
        h->max_size /= 2;
    }
    return top;
}

const void*
heap_top(struct heap* h)
{
    assert(h != NULL);
    return h->vals[0];
}

int
heap_isempty(struct heap* h)
{
    assert(h != NULL);
    return (h->size == 0);
}

unsigned int
heap_getsize(struct heap* h)
{
    assert(h != NULL);
    return h->size;
}

void
heap_destroy(struct heap* h)
{
    if (h != NULL) {
        free(h->vals);
    }
    free(h);
}
