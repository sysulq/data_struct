#include "adjlist.h"

adjlist_t *adjlist_create()
{
  return calloc(1, sizeof(adjlist_t));
}

adjlist_t *adjlist_init(adjlist_t *adj, adjlist_size_t n)
{
  int i;
  if (adj) {
    adjlist_delete(adj);
    adj = adjlist_create();
  }

  adj->size = n;
  adj->lists = malloc(n * sizeof(*adj->lists));
  if (adj->lists == NULL) {
    free(adj);
    return NULL;
  }
  for (i = 0; i < adj->size; ++i) {
      adj->lists[i] = list_create();
      list_push_back(adj->lists[i], i);
  }
  return adj;
}

void       adjlist_delete(adjlist_t *adj)
{
  if (adj) {
    int i;
    for (i = 0; i < adj->size; ++i)
      list_delete(adj->lists[i]);
    free(adj->lists);
    free(adj);
  }
}

void adjlist_insert(adjlist_t *adj,
		    adjlist_size_t u, adjlist_size_t v)
{
  if (u < adj->size)
    list_push_back(adj->lists[u], v);
}

void adjlist_remove(adjlist_t *adj,
		    adjlist_size_t u, adjlist_size_t v)
{
  if (u < adj->size) {
    list_node_t *pos = list_find(adj->lists[u], v);
    if (pos)
      list_remove(adj->lists[u], pos);
  }
}

void       adjlist_print(adjlist_t *adj)
{
  int i;
  for (i = 0; i < adj->size; ++i) {
    list_print(adj->lists[i]);
  }
}
