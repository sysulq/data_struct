#ifndef DS_BINARY_TREE_H
#define DS_BINARY_TREE_H

typedef int binary_tree_key_t;

typedef struct binary_tree_node_s {
  binary_tree_key_t		 key;
  struct binary_tree_node_s	*parent;
  struct binary_tree_node_s	*left;
  struct binary_tree_node_s	*right;
} binary_tree_node_t;

typedef struct binary_tree_s {
  binary_tree_node_t *root;
} binary_tree_t;

binary_tree_t      *binary_tree_create();
void                binary_tree_delete(binary_tree_t *tree);

binary_tree_node_t *binary_tree_insert(binary_tree_t *tree,
				       binary_tree_key_t key);
binary_tree_node_t *binary_tree_remove(binary_tree_t *tree,
				       binary_tree_node_t *node);

binary_tree_node_t *binary_tree_predecessor(binary_tree_t *tree,
					    binary_tree_node_t *node);
binary_tree_node_t *binary_tree_successor(binary_tree_t *tree,
					  binary_tree_node_t *node);

binary_tree_node_t *binary_tree_find(binary_tree_t *tree,
				     binary_tree_key_t key);

void                binary_tree_print(binary_tree_t *tree);

#endif
