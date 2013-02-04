#include "data_structure.h"

int main(int argc, char **argv)
{
#if 0
  binary_tree_node_t *pos;
  binary_tree_t *tree = binary_tree_create();
  binary_tree_insert(tree, 5);
  binary_tree_insert(tree, 1);
  binary_tree_insert(tree, 7);
  binary_tree_insert(tree, 3);
  binary_tree_insert(tree, 11);
  binary_tree_print(tree);

  pos = binary_tree_find(tree, 7);
  pos = binary_tree_predecessor(tree, pos);
  binary_tree_remove(tree, pos);
  binary_tree_print(tree);

  binary_tree_delete(tree);
#endif

#if 0
  rbtree_node_t *pos;
  rbtree_t *tree = rbtree_create();
  rbtree_insert(tree, 1);
  rbtree_insert(tree, 5);
  rbtree_insert(tree, 3);
  rbtree_insert(tree, 11);
  rbtree_insert(tree, 13);
  rbtree_insert(tree, 1111);
  rbtree_print(tree);

  pos = rbtree_find(tree, 3);
  rbtree_remove(tree, pos);
  pos = rbtree_find(tree, 5);
  rbtree_remove(tree, pos);
  pos = rbtree_find(tree, 1111);
  rbtree_remove(tree, pos);

  rbtree_print(tree);
  rbtree_delete(tree);
#endif

#if 1
  avltree_node_t *pos;
  avltree_t *tree = avltree_create();
  avltree_insert(tree, 1);
  avltree_insert(tree, 2);
  avltree_insert(tree, 3);
  avltree_insert(tree, 4);
  avltree_insert(tree, 5);
  avltree_insert(tree, 7);
  avltree_insert(tree, 6);
  avltree_print(tree);

  pos = avltree_find(tree, 7);
  printf("pos = %d\n", pos->key);

  avltree_remove(tree, 4);
  avltree_remove(tree, 6);
  avltree_remove(tree, 7);
  avltree_remove(tree, 1);
  avltree_print(tree);

  avltree_delete(tree);
#endif
  return 0;
}
