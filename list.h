#ifndef _LIST_H_
#define _LIST_H_

struct list;  /* Opaque. */

struct list* list_create();
int list_push_back(struct list* lst, void* newval);
void list_pop_front(struct list* lst);
void* list_front(struct list* lst);
void* list_find(struct list* lst, void* query_val, int(*comparator)(void* left, void* right));
void* list_remove(struct list* lst, void* query_val, int(*comparator)(void* left, void* right));
bool list_isempty(struct list* lst);
unsigned int list_getsize(struct list* lst);
void list_destroy(struct list* lst);

#endif /* _LIST_H_ */
