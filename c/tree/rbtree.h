#ifndef DS_RBTREE_H
#define DS_RBTREE_H

typedef int    rbtree_key_t;
typedef char   rbtree_color_t;

typedef struct rbtree_node_s {
  rbtree_key_t		 key;
  rbtree_color_t	 color;
  struct rbtree_node_s	*parent;
  struct rbtree_node_s	*left;
  struct rbtree_node_s	*right;
} rbtree_node_t;

typedef struct rbtree_s {
  rbtree_node_t *root;
  rbtree_node_t *sentinel;
} rbtree_t;

rbtree_t      *rbtree_create();
void           rbtree_delete(rbtree_t *tree);

rbtree_node_t *rbtree_insert(rbtree_t *tree, rbtree_key_t key);
rbtree_node_t *rbtree_remove(rbtree_t *tree, rbtree_node_t *node);

rbtree_node_t *rbtree_find(rbtree_t *tree, rbtree_key_t key);

void           rbtree_print(rbtree_t *tree);

#endif
