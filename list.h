#ifndef _LIST_H_
#define _LIST_H_

struct list;  /* Opaque. */

struct list* list_create();
void list_push_back(struct list* lst, void* newval);
void* list_pop_front(struct list* lst);
bool list_isempty(struct list* lst);
unsigned int list_getsize(struct list* lst);
void list_destroy(struct list* lst);

#endif /* _LIST_H_ */
