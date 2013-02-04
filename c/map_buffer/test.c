#include "map_buffer.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  map_buffer_size_t pos;
  map_buffer_t *map_buffer = map_buffer_create();

  map_buffer_push_front(map_buffer, 4);
  map_buffer_push_front(map_buffer, 3);
  map_buffer_push_front(map_buffer, 2);
  map_buffer_push_back(map_buffer, 5);
  map_buffer_push_back(map_buffer, 6);
  map_buffer_push_back(map_buffer, 7);
  map_buffer_print(map_buffer);

  map_buffer_pop_front(map_buffer);
  map_buffer_pop_back(map_buffer);
  map_buffer_print(map_buffer);

  pos = map_buffer_find(map_buffer, 6);
  printf("pos = %d\n", pos);

  map_buffer_delete(map_buffer);
  return 0;
}
