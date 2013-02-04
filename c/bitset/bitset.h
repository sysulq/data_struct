#ifndef DS_BITSET_H
#define DS_BITSET_H

#define bitset_npos -1

typedef int    bitset_data_t;
typedef int    bitset_size_t;

typedef struct bitset_s {
  bitset_data_t *datas;
  bitset_size_t  data_size;
  bitset_size_t	 size;
} bitset_t;

bitset_t     *bitset_create();
void          bitset_delete(bitset_t *bitset);
bitset_t     *bitset_init(bitset_t *bitset, bitset_size_t size);

void          bitset_set_all(bitset_t *bitset);
void          bitset_unset_all(bitset_t *bitset);

bitset_size_t bitset_set(bitset_t *bitset, bitset_size_t pos);
bitset_size_t bitset_unset(bitset_t *bitset, bitset_size_t pos);

bitset_size_t bitset_find_first_set_since(bitset_t *bitset,
					  bitset_size_t pos);
bitset_size_t bitset_find_first_unset_since(bitset_t *bitset,
					    bitset_size_t pos);

bitset_size_t bitset_find_first_set(bitset_t *bitset);
bitset_size_t bitset_find_first_unset(bitset_t *bitset);

void          bitset_print(bitset_t *bitset);

#endif
