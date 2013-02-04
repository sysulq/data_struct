#include "bitset.h"
#include <stdio.h>

#define DATA_SIZE         1000
int main(int argc, char **argv)
{
  bitset_size_t pos;
  bitset_t *bitset = bitset_init(NULL, DATA_SIZE);
  bitset_set(bitset, 0);
  bitset_set(bitset, 5);  
  bitset_set(bitset, 38);  
  bitset_set(bitset, 31);  
  bitset_set(bitset, 32);
  bitset_print(bitset);

  bitset_unset_all(bitset);
  bitset_print(bitset);

  bitset_set_all(bitset);
  bitset_print(bitset);

  /* pos = -1; */
  /* while ((pos = bitset_find_first_set_since(bitset, pos + 1)) */
  /* 	 != bitset_npos) */
  /*   printf("%d is set\n", pos); */

  /* pos = -1; */
  /* while ((pos = bitset_find_first_unset_since(bitset, pos + 1)) */
  /* 	 != bitset_npos) */
  /*   printf("%d is unset\n", pos); */

  bitset_delete(bitset);
  return 0;
}
