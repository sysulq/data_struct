#include "data_structure.h"

#define _bitset_data_bitsize (sizeof(bitset_data_t) * 8)

static inline bitset_size_t _bitset_data_size(bitset_size_t size)
{
  return (size + _bitset_data_bitsize - 1) / _bitset_data_bitsize;
}

static inline bitset_size_t _bitset_data_index(bitset_size_t pos)
{
  return pos / _bitset_data_bitsize;
}

static inline bitset_size_t _bitset_data_bit(bitset_size_t pos)
{
  return pos % _bitset_data_bitsize;
}

static inline bitset_size_t _bitset_data_bitmask(bitset_size_t pos)
{
  return 1 << _bitset_data_bit(pos);
}

static inline bitset_size_t
_bitset_bit_pos(bitset_size_t i, bitset_size_t j)
{
  return i * _bitset_data_bitsize + j;
}

bitset_t     *bitset_create()
{
  return calloc(1, sizeof(bitset_t));
}

void          bitset_delete(bitset_t *bitset)
{
  if (bitset) {
    free(bitset->datas);
    free(bitset);
  }
}

bitset_t     *bitset_init(bitset_t *bitset, bitset_size_t size)
{
  if (bitset == NULL)
    bitset = bitset_create();
  if (bitset == NULL)
    return NULL;
  if (bitset->datas)
    free(bitset->datas);

  bitset->size = size;
  bitset->data_size = _bitset_data_size(size);
  bitset->datas = calloc(bitset->data_size, sizeof(*bitset->datas));
  if (bitset->datas == NULL) {
    bitset_delete(bitset);
    return NULL;
  }
  return bitset;
}

void          bitset_set_all(bitset_t *bitset)
{
  if (bitset && bitset->datas)
    memset(bitset->datas, 255, bitset->data_size * sizeof(*bitset->datas));
}

void          bitset_unset_all(bitset_t *bitset)
{
  if (bitset && bitset->datas)
    memset(bitset->datas, 0, bitset->data_size * sizeof(*bitset->datas));
}

bitset_size_t bitset_set(bitset_t *bitset, bitset_size_t pos)
{
  if (pos < 0 || pos >= bitset->size)
    return bitset_npos;
  bitset->datas[_bitset_data_index(pos)] |= _bitset_data_bitmask(pos);
  return pos;
}

bitset_size_t bitset_unset(bitset_t *bitset, bitset_size_t pos)
{
  if (pos < 0 || pos >= bitset->size)
    return bitset_npos;
  bitset->datas[_bitset_data_index(pos)] &= ~_bitset_data_bitmask(pos);
  return pos;
}

bitset_size_t bitset_find_first_set_since(bitset_t *bitset,
					  bitset_size_t since)
{
  bitset_size_t pos;
  for (pos = since; pos < bitset->size; ++pos) {
    if ((bitset->datas[_bitset_data_index(pos)] &
	 _bitset_data_bitmask(pos)))
      return pos;
  }
  return bitset_npos;
}

bitset_size_t bitset_find_first_unset_since(bitset_t *bitset,
					    bitset_size_t since)
{
  bitset_size_t pos;
  for (pos = since; pos < bitset->size; ++pos) {
    if ((bitset->datas[_bitset_data_index(pos)] &
	 _bitset_data_bitmask(pos)) == 0)
      return pos;
  }
  return bitset_npos;
}

bitset_size_t bitset_find_first_set(bitset_t *bitset)
{
  return bitset_find_first_set_since(bitset, 0);
}

bitset_size_t bitset_find_first_unset(bitset_t *bitset)
{
  return bitset_find_first_unset_since(bitset, 0);
}

void          bitset_print(bitset_t *bitset)
{
  int i, j;
  for (i = 0; i < bitset->data_size; ++i) {
    printf("[%d]\t", i);
    for (j = 0; j < _bitset_data_bitsize; ++j)
      printf("%c", (bitset->datas[i] & (1 << j)) ? '1' : '0');
    printf("\n");
  }
}
