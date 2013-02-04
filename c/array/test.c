#include "array.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  array_t *array = array_create();
  array_size_t pos;

  array_push_back(array, 1);
  array_push_back(array, 2);
  array_push_back(array, 3);
  array_push_back(array, 4);
  array_push_back(array, 5);
  array_print(array);
  
  array_remove(array, 0);
  array_print(array);

  array_insert(array, 6, 4);
  array_print(array);

  pos = array_find(array, 1);
  printf("pos = %d\n", pos);

  array_delete(array);
  return 0;
}
