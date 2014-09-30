#ifndef _QUEUE_H_
#define _QUEUE_H_

/*
 * Queue.
 *
 * Functions:
 *     queue_create
 *     queue_enqueue
 *     queue_dequeue
 *     queue_getsize
 *     queue_destroy
 */

struct queue; /* OPAQUE */

struct queue* queue_create();
void queue_push(struct queue* q, void* newval);
void queue_pop(struct queue* q);
void* queue_front(struct queue* q);
bool queue_isempty(struct queue* q);
unsigned int queue_getsize(struct queue* q);
void queue_destroy(struct queue* q);

#endif /* _QUEUE_H_ */
