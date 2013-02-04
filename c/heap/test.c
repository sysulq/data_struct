#include "heap.h"
#include <stdio.h>

void heap_sort(heap_t *heap)
{
  heap_data_t data;
  while (!heap_empty(heap)) {
    data = heap_top(heap);
    heap_pop(heap);
    printf("%d ", data);
  }
  printf("\n");
}

#define DATA_SIZE       100

int main(int argc, char **argv)
{
  heap_size_t i;
  heap_t *heap = heap_create();
  heap_data_t datas[DATA_SIZE];

  heap_push(heap, 3);
  heap_push(heap, 1);
  heap_push(heap, 2);
  heap_push(heap, 4);
  heap_print(heap);

  heap_pop(heap);
  heap_print(heap);

  for (i = 0; i < DATA_SIZE; ++i) {
    heap_push(heap, i);
    datas[i] = i;
  }

  heap_sort(heap);
  heap_delete(heap);

  heap = heap_make(datas, DATA_SIZE);
  heap_sort(heap);
  heap_delete(heap);

  return 0;
}
