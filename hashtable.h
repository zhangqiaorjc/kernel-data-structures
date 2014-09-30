#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

/*
 * Hash table.
 *
 * Functions:
 *     hashtable_create       - Allocates and returns a new hashtable object with a given
 *                              initial size (e.g. 8) and a given load factor (e.g. 0.7).
 *                              Returns NULL on error.
 *     hashtable_add          - Adds a new element with the given key to the hashtable.
 *     hashtable_find         - Finds the element with the given key from the hashtable.
 *                              Returns NULL if not found.
 *     hashtable_remove       - Removes the element with the given key from the hashtable.
 *                              Returns the element removed. Returns NULL if element does
 *                              not exist.
 *     hashtable_isempty      - Returns whether the hashtable is empty.
 *     hashtable_getsize      - Returns the number of elements in the hashtable.
 *     hashtable_destroy      - Destroys the hashtable object; frees internal data
 *                              structures.
 *                              DOES NOT free any element contained in the hashtable.
 *                              To avoid memory leak, please free all elements added
 *                              to the hashtable.
 *     hashtable_assertvalid  - Validates the integrity of the hashtable data structure
 *                              e.g. whether the hashtable contains the stated number
 *                              of elements and whether each key is hashed to the correct
 *                              slot.
 */

struct hashtable; /* Opaque. */

struct hashtable* hashtable_create(unsigned int init_size, float load_factor);
int hashtable_add(struct hashtable* h, char* key, unsigned int keylen, void* val);
void* hashtable_find(struct hashtable* h, char* key, unsigned int keylen);
void* hashtable_remove(struct hashtable* h, char* key, unsigned int keylen);
int hashtable_isempty(struct hashtable* h);
unsigned int hashtable_getsize(struct hashtable* h);
void hashtable_destroy(struct hashtable* h);
void hashtable_assertvalid(struct hashtable* h);

#endif /* _HASHTABLE_H_ */
