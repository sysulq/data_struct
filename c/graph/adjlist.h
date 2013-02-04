#ifndef DS_ADJLIST_H
#define DS_ADJLIST_H

#include "data_structure.h"

typedef int          adjlist_size_t;

typedef struct adjlist_s {
  adjlist_size_t size;
  list_t **lists;
} adjlist_t;

adjlist_t *adjlist_create();
void       adjlist_delete(adjlist_t *adj);
adjlist_t *adjlist_init(adjlist_t *adj, adjlist_size_t n);

void       adjlist_insert(adjlist_t *adj,
			  adjlist_size_t u, adjlist_size_t v);
void       adjlist_remove(adjlist_t *adj,
			  adjlist_size_t u, adjlist_size_t v);

void       adjlist_print(adjlist_t *adj);

#endif /* DS_ADJLIST_H */
