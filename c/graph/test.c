#include "data_structure.h"

int main(int argc, char *argv[])
{
  adjlist_size_t n, u, v;
  adjlist_t *adj = adjlist_create();
  scanf("%d", &n);
  adjlist_init(adj, n);
  while (scanf("%d%d", &u, &v) == 2) {
    adjlist_insert(adj, u, v);
    adjlist_insert(adj, v, u);
  }
  adjlist_print(adj);
  adjlist_delete(adj);
  return 0;
}
