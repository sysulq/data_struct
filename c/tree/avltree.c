#include "avltree.h"

static avltree_node_t *avltree_node_create(avltree_key_t key)
{
  avltree_node_t *node = calloc(1, sizeof(*node));
  if (node)
    node->key = key;
  return node;
}

static void avltree_node_delete(avltree_node_t *node)
{
  free(node);
}

static inline void avltree_node_set_height(avltree_node_t *node)
{
  avltree_size_t lh = node->left  == NULL ? -1 : node->left->height;
  avltree_size_t rh = node->right == NULL ? -1 : node->right->height;
  node->height = (lh > rh ? lh : rh) + 1;
}

static inline avltree_size_t
avltree_node_factor(avltree_node_t *node)
{
  avltree_size_t lh = node->left  == NULL ? -1 : node->left->height;
  avltree_size_t rh = node->right == NULL ? -1 : node->right->height;
  return lh - rh;
}

avltree_t      *avltree_create()
{
  return calloc(1, sizeof(avltree_t));
}

static void _avltree_delete(avltree_node_t *node)
{
  if (node) {
    _avltree_delete(node->left);
    _avltree_delete(node->right);
    avltree_node_delete(node);
  }
}

void            avltree_delete(avltree_t *tree)
{
  _avltree_delete(tree->root);
}

static avltree_node_t *
avltree_left_rotate(avltree_node_t *node)
{
  avltree_node_t *rchild = node->right;
  node->right = rchild->left;
  rchild->left = node;
  avltree_node_set_height(node);
  avltree_node_set_height(rchild);
  return rchild;
}

static avltree_node_t *
avltree_right_rotate(avltree_node_t *node)
{
  avltree_node_t *lchild = node->left;
  node->left = lchild->right;
  lchild->right = node;
  avltree_node_set_height(node);
  avltree_node_set_height(lchild);
  return lchild;
}

static avltree_node_t *
_avltree_fixup(avltree_node_t *node)
{
  if (avltree_node_factor(node) == 2) {
    if (avltree_node_factor(node->left) == -1)
      node->left = avltree_left_rotate(node->left);
    node = avltree_right_rotate(node);
  } else if (avltree_node_factor(node) == -2) {
    if (avltree_node_factor(node->right) == 1)
      node->right = avltree_right_rotate(node->right);
    node = avltree_left_rotate(node);
  }
  avltree_node_set_height(node);
  return node;
}

static avltree_node_t *
_avltree_insert(avltree_node_t *root, avltree_key_t key)
{
  if (root == NULL)
    return avltree_node_create(key);

  if (key <= root->key)
    root->left = _avltree_insert(root->left, key);
  else
    root->right = _avltree_insert(root->right, key);

  root = _avltree_fixup(root);
  return root;
}

avltree_node_t *avltree_insert(avltree_t *tree, avltree_key_t key)
{
  return tree->root = _avltree_insert(tree->root, key);
}

static avltree_node_t *
_avltree_remove_min(avltree_node_t *root, avltree_node_t *node)
{
  if (root->left) {
    root->left = _avltree_remove_min(root->left, node);
    return _avltree_fixup(root);
  } else {
    node->key = root->key;
    node = root->right;
    avltree_node_delete(root);
    return node;
  }
}

static avltree_node_t *
_avltree_remove(avltree_node_t *root, avltree_key_t key)
{
  if (root == NULL)
    return NULL;
  if (key == root->key) {
    if (root->left && root->right) {
      root->right = _avltree_remove_min(root->right, root);
    } else {
      avltree_node_t *child;
      if (root->left)
	child = root->left;
      else
	child = root->right;
      avltree_node_delete(root);
      return child;
    }
  } else if (key < root->key) {
    root->left = _avltree_remove(root->left, key);
  } else {
    root->right = _avltree_remove(root->right, key);
  }

  return _avltree_fixup(root);
}

avltree_node_t *avltree_remove(avltree_t *tree, avltree_key_t key)
{
  tree->root = _avltree_remove(tree->root, key);
  return tree->root;
}

avltree_node_t *avltree_find(avltree_t *tree, avltree_key_t key)
{
  avltree_node_t *node = tree->root;
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

static void _avltree_print(avltree_node_t *node)
{
  if (node) {
    _avltree_print(node->left);
    printf("%d[%d] ", node->key, node->height);
    _avltree_print(node->right);
  }
}

void            avltree_print(avltree_t *tree)
{
  _avltree_print(tree->root);
  printf("\n");
}
