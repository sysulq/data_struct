#include "rbtree.h"

#define rbtree_set_black(x)       ((x)->color = 0)
#define rbtree_set_red(x)         ((x)->color = 1)
#define rbtree_is_black(x)        ((x)->color == 0)
#define rbtree_is_red(x)          (!rbtree_is_black(x))
static inline void
rbtree_color_swap(rbtree_node_t *x, rbtree_node_t *y)
{
  rbtree_color_t tmp = x->color;
  x->color = y->color;
  y->color = tmp;
}

static rbtree_node_t *
rbtree_node_create(rbtree_key_t key, rbtree_node_t *sentinel)
{
  rbtree_node_t *node = malloc(sizeof(*node));
  if (node) {
    node->key = key;
    rbtree_set_black(node);
    node->parent = sentinel;
    node->left = sentinel;
    node->right = sentinel;
  }
  return node;
}

static void rbtree_node_delete(rbtree_node_t *node)
{
  free(node);
}

rbtree_t      *rbtree_create()
{
  rbtree_t *tree = malloc(sizeof(*tree));
  if (tree) {
    tree->sentinel = rbtree_node_create(0, NULL);
    if (tree->sentinel == NULL) {
      free(tree);
      return NULL;
    }
    tree->sentinel->parent = tree->sentinel;
    tree->sentinel->left   = tree->sentinel;
    tree->sentinel->right  = tree->sentinel;
    tree->root = tree->sentinel;
  }
  return tree;
}

static void _rbtree_delete(rbtree_t *tree, rbtree_node_t *node)
{
  if (node != tree->sentinel) {
    _rbtree_delete(tree, node->left);
    _rbtree_delete(tree, node->right);
    rbtree_node_delete(node);
  }
}

void           rbtree_delete(rbtree_t *tree)
{
  if (tree->root != tree->sentinel)
    _rbtree_delete(tree, tree->root);
  rbtree_node_delete(tree->sentinel);
}

static void rbtree_left_rotate(rbtree_t *tree, rbtree_node_t *node)
{
  rbtree_node_t *rchild = node->right;
  node->right = rchild->left;
  if (rchild->left != tree->sentinel)
    rchild->left->parent = node;

  rchild->parent = node->parent;
  if (node->parent == tree->sentinel)
    tree->root = rchild;
  else if (node == node->parent->left)
    node->parent->left = rchild;
  else
    node->parent->right = rchild;

  rchild->left = node;
  node->parent = rchild;
}

static void rbtree_right_rotate(rbtree_t *tree, rbtree_node_t *node)
{
  rbtree_node_t *lchild = node->left;
  node->left = lchild->right;
  if (lchild->right != tree->sentinel)
    lchild->right->parent = node;

  lchild->parent = node->parent;
  if (node->parent == tree->sentinel)
    tree->root = node;
  else if (node == node->parent->left)
    node->parent->left = lchild;
  else
    node->parent->right = lchild;

  lchild->right = node;
  node->parent = lchild;
}

static void rbtree_insert_fixup(rbtree_t *tree, rbtree_node_t *node)
{
  while (rbtree_is_red(node->parent)) {
    if (node->parent == node->parent->parent->left) {
      if (rbtree_is_red(node->parent->parent->right)) {
	rbtree_set_black(node->parent);
	rbtree_set_black(node->parent->parent->right);
	rbtree_set_red(node->parent->parent);
	node = node->parent->parent;
      } else {
	if (node == node->parent->right) {
	  node = node->parent;
	  rbtree_left_rotate(tree, node);
	}
	rbtree_set_black(node->parent);
	rbtree_set_red(node->parent->parent);
	rbtree_right_rotate(tree, node->parent->parent);
      }
    } else {
      if (rbtree_is_red(node->parent->parent->left)) {
	rbtree_set_black(node->parent);
	rbtree_set_black(node->parent->parent->left);
	rbtree_set_red(node->parent->parent);
      } else {
	if (node == node->parent->left) {
	  node = node->parent;
	  rbtree_right_rotate(tree, node);
	}
	rbtree_set_black(node->parent);
	rbtree_set_red(node->parent->parent);
	rbtree_left_rotate(tree, node->parent->parent);
      }
    }
  }
  rbtree_set_black(tree->root);
}

rbtree_node_t *rbtree_insert(rbtree_t *tree, rbtree_key_t key)
{
  rbtree_node_t *node, *parent;
  node = tree->root;
  parent = tree->sentinel;
  while (node != tree->sentinel) {
    parent = node;
    if (key <= node->key)
      node = node->left;
    else
      node = node->right;
  }

  node = rbtree_node_create(key, tree->sentinel);
  if (node) {
    node->parent = parent;
    if (parent == tree->sentinel)
      tree->root = node;
    else if (node->key <= parent->key)
      parent->left = node;
    else
      parent->right = node;

    rbtree_set_red(node);
    rbtree_insert_fixup(tree, node);
  }

  return node;
}

static void rbtree_remove_fixup(rbtree_t *tree, rbtree_node_t *node)
{
  rbtree_node_t *brother;
  while (node != tree->root && rbtree_is_black(node)) {
    if (node == node->parent->left) {
      brother = node->parent->right;
      if (rbtree_is_red(brother)) {
	rbtree_color_swap(node->parent, brother);
	rbtree_left_rotate(tree, node->parent);
	brother = node->parent->right;
      }
      if (rbtree_is_black(brother->left) &&
	  rbtree_is_black(brother->right)) {
	rbtree_set_red(brother);
	node = node->parent;
      } else {
	if (rbtree_is_black(brother->right)) {
	  rbtree_color_swap(brother, brother->left);
	  rbtree_right_rotate(tree, brother);
	  brother = node->parent->right;
	}
	rbtree_set_black(brother->right);
	rbtree_color_swap(node->parent, brother);
	rbtree_left_rotate(tree, node->parent);
	node = tree->root;
      }
    } else {
      brother = node->parent->left;
      if (rbtree_is_red(brother)) {
	rbtree_color_swap(node->parent, brother);
	rbtree_right_rotate(tree, node->parent);
	brother = node->parent->left;
      }
      if (rbtree_is_black(brother->left) &&
	  rbtree_is_black(brother->right)) {
	rbtree_set_red(brother);
	node = node->parent;
      } else {
	if (rbtree_is_black(brother->left)) {
	  rbtree_color_swap(brother, brother->right);
	  rbtree_left_rotate(tree, brother);
	  brother = node->parent->left;
	}
	rbtree_set_black(brother->left);
	rbtree_color_swap(node->parent, brother);
	rbtree_right_rotate(tree, node->parent);
	node = tree->root;
      }
    }
  }
  rbtree_set_black(node);
}

static rbtree_node_t *
rbtree_successor(rbtree_t *tree, rbtree_node_t *node)
{
  if (node->right != tree->sentinel) {
    node = node->right;
    while (node->left != tree->sentinel)
      node = node->left;
    return node;
  } else {
    while (node->parent != tree->sentinel && node == node->parent->right)
      node = node->parent;
    return node->parent;
  }
}

rbtree_node_t *rbtree_remove(rbtree_t *tree, rbtree_node_t *node)
{
  rbtree_node_t *remove, *child;
  if (node->left == tree->sentinel || node->right == tree->sentinel)
    remove = node;
  else
    remove = rbtree_successor(tree, node);
  if (remove->left != tree->sentinel)
    child = remove->left;
  else
    child = remove->right;

  child->parent = remove->parent;
  if (remove->parent == tree->sentinel)
    tree->root = child;
  else if (remove == remove->parent->left)
    remove->parent->left = child;
  else
    remove->parent->right = child;

  if (remove != node) {
    node->key = remove->key;
  }

  if (rbtree_is_black(remove))
    rbtree_remove_fixup(tree, child);
  rbtree_node_delete(remove);

  return node;
}

rbtree_node_t *rbtree_find(rbtree_t *tree, rbtree_key_t key)
{
  rbtree_node_t *node = tree->root;
  while (node != tree->sentinel) {
    if (key == node->key)
      return node;
    else if (key < node->key)
      node = node->left;
    else
      node = node->right;
  }
  return NULL;
}

static void _rbtree_print(rbtree_t *tree, rbtree_node_t *node)
{
  if (node != tree->sentinel) {
    _rbtree_print(tree, node->left);
    printf("%d[%c] ", node->key, rbtree_is_black(node) ? 'b' : 'r');
    _rbtree_print(tree, node->right);
  }
}

void rbtree_print(rbtree_t *tree)
{
  _rbtree_print(tree, tree->root);
  printf("\n");
}
