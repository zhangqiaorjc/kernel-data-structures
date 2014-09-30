#ifndef _HEAP_H_
#define _HEAP_H_

/*
 * Heap (priority queue).
 *
 * Functions:
 *     heap_create   - Allocates and returns a new heap object given a
 *                     comparator.
 *                     Returns NULL on error.
 *                     Comparator returns 1 if the left element precedes the
 *                     second element, returns 0 otherwise.
 *     heap_push     - Adds a new element to the heap.
 *     heap_pop      - Removes the next element (with the highest priority)
 *                     from the heap.
 *     heap_top      - Peeks the next element.
 *     heap_isempty  - Returns whether the heap is empty.
 *     heap_getsize  - Returns the number of elements in the heap.
 *     heap_destroy  - Destroys the heap object; frees internal data
 *                     structures.
 *                     DOES NOT free any element contained in the heap.
 *                     To avoid memory leak, please free all elements added
 *                     to the heap.
 */

struct heap; /* Opaque. */

struct heap* heap_create(int(*comparator)(const void*, const void*));
void heap_push(struct heap* q, void* newval);
void* heap_pop(struct heap* q);
const void* heap_top(struct heap* q);
int heap_isempty(struct heap* q);
unsigned int heap_getsize(struct heap* q);
void heap_destroy(struct heap* q);

#endif /* _HEAP_H_ */
