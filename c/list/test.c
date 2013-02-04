#include "list.h"
#include <assert.h>
#include <stdio.h>

void output(list_node_t *list)
{
	if (list) {
		printf("%d,", *(int*)(list->data));
	}
}

int main(int argc, char **argv)
{
  int x = 1;
  int y = 2;
  int z = 3;
  
  list_node_t *list = list_create(&x);
  list_dump(list, &output);

  list = list_insert_end(list, &y);
  list_dump(list, &output);
  
  list = list_insert_beginning(list, &z);
  list_dump(list, &output);

  list = list_insert_beginning(list, &z);
  list_dump(list, &output);

  list = list_insert_after(list, &y);
  list_dump(list, &output);

  return 0;
}
