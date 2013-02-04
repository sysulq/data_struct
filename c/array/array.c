#include "data_structure.h"

array_t *array_create()
{
  return calloc(1, sizeof(array_t));
}

static void array_realloc(array_t *array)
{
  if (array->capacity == 0) {
    array->capacity = 1;
  } else {
    array->capacity <<= 1;
  }
  array->datas = realloc(array->datas,
			 sizeof(*array->datas) * array->capacity);
}

array_size_t array_push_back(array_t *array, array_data_t data)
{
  if (array->size == array->capacity) {
    array_realloc(array);
  }
  array->datas[array->size] = data;
  return array->size++;
}

array_size_t array_insert(array_t *array, array_data_t data,
			  array_size_t pos)
{
  array_size_t i;
  if (pos > array->size)
    return array_npos;
  if (array->size == array->capacity) {
    array_realloc(array);
  }
  for (i = array->size; i != pos; --i) {
    array->datas[i] = array->datas[i-1];
  }
  array->datas[pos] = data;
  ++array->size;
  return pos;
}

array_size_t array_pop_back(array_t *array)
{
  if (array->size == 0)
    return array_npos;
  return --array->size;
}

array_size_t array_remove(array_t *array, array_size_t pos)
{
  array_size_t i;
  if (pos >= array->size)
    return array_npos;
  --array->size;
  for (i = pos; i != array->size; ++i) {
    array->datas[i] = array->datas[i+1];
  }
  return pos;
}

array_size_t array_find(array_t *array, array_data_t data)
{
  array_size_t i;
  for (i = 0; i != array->size; ++i) {
    if (array->datas[i] == data)
      return i;
  }
  return array_npos;
}

void array_sort(array_t *array)
{
  /* TODO: use [algorithm:sort] */
}

void array_swap(array_t *array, array_size_t p1, array_size_t p2)
{
  array_data_t tmp = array->datas[p1];
  array->datas[p1] = array->datas[p2];
  array->datas[p2] = tmp;
}

void array_delete(array_t *array)
{
  free(array->datas);
  array->size = 0;
  array->capacity = 0;
}

void array_print(array_t *array)
{
  int i;
  for (i = 0; i != array->size; ++i) {
    printf("%d ", array->datas[i]);
  }
  printf("\nsize = %d capacity = %d\n", array->size, array->capacity);
}

