#ifndef DS_AVLTREE_H
#define DS_AVLTREE_H

typedef int    avltree_key_t;
typedef int    avltree_size_t;

typedef struct avltree_node_s {
  avltree_key_t		 key;
  avltree_size_t	 height;
  struct avltree_node_s *left;
  struct avltree_node_s *right;
} avltree_node_t;

typedef struct avltree_s {
  avltree_node_t *root;
} avltree_t;

avltree_t      *avltree_create();
void            avltree_delete(avltree_t *tree);

avltree_node_t *avltree_insert(avltree_t *tree, avltree_key_t key);
avltree_node_t *avltree_remove(avltree_t *tree, avltree_key_t key);

avltree_node_t *avltree_find(avltree_t *tree, avltree_key_t key);

void            avltree_print(avltree_t *tree);

#endif
