#include "list.h"
#include <assert.h>

struct listnode {
    void* val;
    struct listnode* next;
};

struct list {
    struct listnode* head;
    struct listnode* tail;
    unsigned int size;
};

struct listnode*
listnode_create(void* newval)
{
    struct listnode* newnode;
    
    newnode = (struct listnode*)malloc(sizeof(struct listnode));
    if (newnode == NULL) {
        return NULL;
    }
    newnode->val = newval;
    newnode->next = NULL;

    return newnode;
}

struct list*
list_create()
{
    struct list* newlist;

    newlist = (struct list*)malloc(sizeof(struct list));
    if (newlist == NULL) {
        return NULL;
    }

    newlist->head = NULL;
    newlist->tail = NULL;
    newlist->size = 0;

    return newlist;
}

void
list_push_back(struct list* lst, void* newval)
{
    assert(lst != NULL);

    struct listnode* newnode = listnode_create(newval);
    if (newnode == NULL) {
        return;
    }

    if (lst->size == 0) {
        lst->head = newnode;
    } else {
        lst->tail->next = newnode;
    }
    lst->tail = newnode;

    ++lst->size;

}

void*
list_pop_front(struct list* lst)
{
    assert(lst != NULL);

    if (lst->size == 0) {
        return NULL;
    }

    void* val = lst->head->val;
    lst->head = lst->head->next;
    --lst->size;

    if (lst->size == 0) {
        lst->tail = NULL;
    }

    return val;
}

bool
list_isempty(struct list* lst)
{
    assert(lst != NULL);

    return (lst->size == 0);
}

unsigned int
list_getsize(struct list* lst)
{
    assert(lst != NULL);

    return (lst->size);
}

void
list_destroy(struct list* lst)
{
    if (lst != NULL) {
        struct listnode* p = lst->head;
        struct listnode* q;
        while (p != NULL) {
            q = p->next;
            free(p);
            p = q;
        }
    }
    free(lst);
}

