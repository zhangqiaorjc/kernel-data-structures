#include "queue.h"
#include "list.h"
#include <assert.h>

struct queue {
    struct list* vals;
};

struct queue*
queue_create()
{
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    q->vals = list_create();
    if (q->vals == NULL) {
        return NULL;
    }
    return q;
}

void
queue_push(struct queue* q, void* newval)
{
    assert(q != NULL);
    list_push_back(q->vals, newval);
}

void
queue_pop(struct queue* q)
{
    assert(q != NULL);
    list_pop_front(q->vals);
}

void*
queue_front(struct queue* q)
{
    assert(q != NULL);
    return list_front(q->vals);
}

bool
queue_isempty(struct queue* q)
{
    assert(q != NULL);
    return list_isempty(q->vals);
}

unsigned int
queue_getsize(struct queue* q)
{
    assert(q != NULL);
    return list_getsize(q->vals);
}

void
queue_destroy(struct queue* q)
{
    if (q != NULL) {
        list_destroy(q->vals);
    }
    free(q);
}
