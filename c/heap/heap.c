#include "data_structure.h"

heap_t *heap_create(heap_size_t order)
{
  heap_t *heap = array_create();
  if (heap == NULL)
    return NULL;
  array_push_back(heap, array_npos);
  return heap;
}

void heap_delete(heap_t *heap)
{
  array_delete(heap);
}

heap_size_t heap_empty(heap_t *heap)
{
  return heap->size <= 1;
}

heap_data_t heap_top(heap_t *heap)
{
  if (heap->size != 0)
    return heap->datas[1];
}

#define parent(x)           ((x) / 2)
#define lchild(x)           ((x) * 2)
#define rchild(x)           ((x) * 2 + 1)

static heap_size_t _heap_sift_down(heap_t *heap, heap_size_t pos)
{
  heap_data_t tmp = heap->datas[pos];
  while (lchild(pos) < heap->size && rchild(pos) < heap->size) {
    if (tmp >= heap->datas[lchild(pos)]
	&& tmp >= heap->datas[rchild(pos)])
      break;

    if (heap->datas[lchild(pos)] >= heap->datas[rchild(pos)]) {
      heap->datas[pos] = heap->datas[lchild(pos)];
      pos = lchild(pos);
    } else {
      heap->datas[pos] = heap->datas[rchild(pos)];
      pos = rchild(pos);
    }
  }
  if (lchild(pos) < heap->size && heap->datas[lchild(pos)] > tmp) {
    heap->datas[pos] = heap->datas[lchild(pos)];
    pos = lchild(pos);
  }
  heap->datas[pos] = tmp;
  return pos;
}

static heap_size_t _heap_sift_up(heap_t *heap, heap_size_t pos)
{
  heap_data_t tmp = heap->datas[pos];
  while (parent(pos) != 0) {
    if (tmp <= heap->datas[parent(pos)])
      break;
    heap->datas[pos] = heap->datas[parent(pos)];
    pos = parent(pos);
  }
  heap->datas[pos] = tmp;
  return pos;
}

heap_size_t heap_push(heap_t *heap, heap_data_t data)
{
  if (array_push_back(heap, data) == array_npos)
    return heap_npos;
  return _heap_sift_up(heap, heap->size - 1);
}

heap_size_t heap_pop(heap_t *heap)
{
  if (heap->size == 0)
    return heap_npos;
  array_swap(heap, 1, heap->size - 1);
  array_pop_back(heap);
  return _heap_sift_down(heap, 1);
}

/* O(N) */
heap_t *heapify(heap_data_t *datas, heap_size_t size)
{
  heap_size_t i;
  heap_t *heap;
  if (datas == NULL || size < 2)
    return NULL;

  heap = array_create();
  if (heap == NULL)
    return NULL;
  heap->datas = datas;
  heap->size = size;
  heap->capacity = size;
  for (i = heap->size - 1; i > 0; --i) {
    _heap_sift_up(heap, i);
  }
  return heap;
}

heap_t *heap_make(heap_data_t *datas, heap_size_t size)
{
  heap_size_t i;
  heap_t *heap = array_create();
  if (heap == NULL)
    return NULL;

  heap->capacity = size + 1;
  heap->size = size + 1;
  heap->datas = malloc(sizeof(*heap->datas) * heap->size);
  if (heap->datas == NULL)
    return NULL;

  memcpy(heap->datas + 1, datas, sizeof(*datas) * size);
  for (i = heap->size - 1; i > 0; --i) {
    _heap_sift_up(heap, i);
  }
  return heap;
}

void heap_print(heap_t *heap)
{
  array_print(heap);
}
