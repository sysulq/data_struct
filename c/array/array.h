#ifndef DS_ARRAY_H
#define DS_ARRAY_H

#define array_npos -1

typedef int    array_data_t;
typedef int    array_size_t;

typedef struct array_s {
  array_data_t	*datas;
  array_size_t	 size;
  array_size_t   capacity;
} array_t;

array_t		*array_create();
void		 array_delete(array_t *array);

array_size_t	 array_push_back(array_t *array, array_data_t data);
array_size_t	 array_insert(array_t *array, array_data_t data,
			      array_size_t pos);

array_size_t     array_pop_back(array_t *array);
array_size_t	 array_remove(array_t *array, array_size_t pos);

array_size_t	 array_find(array_t *array, array_data_t data);
void		 array_sort(array_t *array);
void             array_swap(array_t *array,
			    array_size_t p1, array_size_t p2);
void		 array_print(array_t *array);

#endif
