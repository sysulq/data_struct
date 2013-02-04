#include "data_structure.h"

static binary_tree_node_t *
binary_tree_node_create(binary_tree_key_t key)
{
  binary_tree_node_t *node = calloc(1, sizeof(*node));
  if (node)
    node->key = key;
  return node;
}

static void _binary_tree_node_delete(binary_tree_node_t *node)
{
  free(node);
}

static binary_tree_node_t *
_binary_tree_node_min(binary_tree_node_t *node)
{
  if (node) {
    while (node->left)
      node = node->left;
  }
  return node;
}

static binary_tree_node_t *
_binary_tree_node_max(binary_tree_node_t *node)
{
  if (node) {
    while (node->right)
      node = node->right;
  }
  return node;
}

static void _binary_tree_node_print(binary_tree_node_t *node)
{
  if (node) {
    _binary_tree_node_print(node->left);
    printf("%d ", node->key);
    _binary_tree_node_print(node->right);
  }
}

binary_tree_t *binary_tree_create()
{
  return calloc(1, sizeof(binary_tree_t));
}

static void    _binary_tree_delete(binary_tree_node_t *node)
{
  if (node) {
    _binary_tree_delete(node->left);
    _binary_tree_delete(node->right);
    free(node);
  }
}

void           binary_tree_delete(binary_tree_t *tree)
{
  _binary_tree_delete(tree->root);
}

binary_tree_node_t *binary_tree_insert(binary_tree_t *tree,
				       binary_tree_key_t key)
{
  binary_tree_node_t *node = tree->root, *parent = NULL;
  while (node) {
    parent = node;
    if (key <= node->key)
      node = node->left;
    else
      node = node->right;
  }
  node = binary_tree_node_create(key);
  if (node) {
    if (parent == NULL) {
      tree->root = node;
    } else {
      node->parent = parent;
      if (key <= parent->key) {
	parent->left = node;
      } else {
	parent->right = node;
      }
    }
  }
  return node;
}

binary_tree_node_t *binary_tree_remove(binary_tree_t *tree,
				       binary_tree_node_t *node)
{
  binary_tree_node_t *remove, *child;
  if (node == NULL)
    return NULL;
  if (node->left == NULL || node->right == NULL)
    remove = node;
  else
    remove = binary_tree_successor(tree, node);
  if (remove->left)
    child = remove->left;
  else
    child = remove->right;

  if (child)
    child->parent = remove->parent;

  if (remove->parent == NULL)
    tree->root = child;
  else if (remove == remove->parent->left)
    remove->parent->left = child;
  else
    remove->parent->right = child;

  if (remove != node)
    node->key = remove->key;
  _binary_tree_node_delete(remove);

  return remove;
}

binary_tree_node_t *binary_tree_predecessor(binary_tree_t *tree,
					    binary_tree_node_t *node)
{
  binary_tree_node_t *parent;
  if (node) {
    if (node->left)
      return _binary_tree_node_max(node->left);
    for (parent = node->parent;
	 parent && node == parent->left;
	 node = parent, parent = node->parent);
    return parent;
  }
  return NULL;
}

binary_tree_node_t *binary_tree_successor(binary_tree_t *tree,
					  binary_tree_node_t *node)
{
  binary_tree_node_t *parent;
  if (node) {
    if (node->right)
      return _binary_tree_node_min(node->right);
    for (parent = node->parent;
	 parent && node == parent->right;
	 node = parent, parent = node->parent);
    return parent;
  }
  return NULL;
}

binary_tree_node_t *binary_tree_find(binary_tree_t *tree,
				     binary_tree_key_t key)
{
  binary_tree_node_t *node = tree->root;
  while (node) {
    if (key == node->key)
      return node;
    else if (key < node->key)
      node = node->left;
    else
      node = node->right;
  }
  return NULL;
}

void           binary_tree_print(binary_tree_t *tree)
{
  _binary_tree_node_print(tree->root);
  printf("\n");
}
