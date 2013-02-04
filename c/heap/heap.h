#ifndef DS_HEAP_H
#define DS_HEAP_H

/* max heap */

#define heap_npos       array_npos

typedef array_data_t    heap_data_t;
typedef array_size_t    heap_size_t;
typedef array_t         heap_t;

heap_t     *heap_create();
void        heap_delete(heap_t *heap);

heap_size_t heap_push(heap_t *heap, heap_data_t data);
heap_size_t heap_pop(heap_t *heap);

heap_size_t heap_empty(heap_t *heap);
heap_data_t heap_top(heap_t *heap);

heap_t     *heap_make(heap_data_t *datas, heap_size_t size);
heap_t     *heapify(heap_data_t *datas, heap_size_t size);

void        heap_print(heap_t *heap);

#endif
