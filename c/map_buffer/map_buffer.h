#ifndef DS_MAP_BUFFER_H
#define DS_MAP_BUFFER_H
/* WARNING: BUGS */
#define MAP_BUFFER_SIZE        2
#define map_buffer_npos        -2

typedef int    map_buffer_data_t;
typedef int    map_buffer_size_t;

typedef struct map_buffer_buffer_s {
  map_buffer_data_t	*datas;
  map_buffer_size_t	 cur;
  map_buffer_size_t	 last;
} map_buffer_buffer_t;

typedef struct map_buffer_s {
  map_buffer_buffer_t  **buffers;
  map_buffer_size_t	 first;
  map_buffer_size_t	 last;
  map_buffer_size_t      map_size;
} map_buffer_t;

map_buffer_t	 *map_buffer_create();
void		  map_buffer_delete(map_buffer_t *map_buffer);

map_buffer_size_t map_buffer_push_front(map_buffer_t *map_buffer,
					map_buffer_data_t data);
map_buffer_size_t map_buffer_push_back(map_buffer_t *map_buffer,
				       map_buffer_data_t data);
void              map_buffer_pop_front(map_buffer_t *map_buffer);
void              map_buffer_pop_back(map_buffer_t *map_buffer);

map_buffer_size_t map_buffer_find(map_buffer_t *map_buffer,
				  map_buffer_data_t data);

void	          map_buffer_print(map_buffer_t *map_buffer);

#endif
