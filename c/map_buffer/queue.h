#ifndef DS_QUEUE_H
#define DS_QUEUE_H

/* TODO */

#include "map_buffer.h"

typedef map_buffer_t      queue_t;
typedef map_buffer_data_t queue_data_t;
typedef map_buffer_size_t queue_size_t;

#define queue_create      map_buffer_create
#define queue_delete      map_buffer_delete
#define queue_push_front  map_buffer_push_front
#define queue_push_back   map_buffer_push_back
#define queue_pop_front   map_buffer_pop_front
#define queue_pop_back    map_buffer_pop_back
#define queue_empty       map_buffer_empty
#define queue_top         map_buffer_top
#define queue_print       map_buffer_print

#endif /* DS_QUEUE_H */
