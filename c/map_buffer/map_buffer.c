#include "data_structure.h"

static map_buffer_buffer_t *
_map_buffer_buffer_create(map_buffer_size_t size)
{
  map_buffer_buffer_t *buffer = malloc(sizeof(*buffer));
  if (buffer == NULL)
    return NULL;
  buffer->datas = malloc(sizeof(*buffer->datas) * size);
  if (buffer->datas == NULL)
    return NULL;

  buffer->cur = map_buffer_npos;
  buffer->last = size;
  return buffer;
}

static void _map_buffer_buffer_delete(map_buffer_buffer_t *buffer)
{
  if (buffer) {
    free(buffer->datas);
    free(buffer);
  }
}

static inline map_buffer_size_t
_map_buffer_buffer_push_front(map_buffer_buffer_t *buffer,
			      map_buffer_data_t data)
{
  if (buffer->cur == map_buffer_npos)
    buffer->cur = buffer->last;
  if (buffer->cur == 0)
    return map_buffer_npos;
  --buffer->cur;
  buffer->datas[buffer->cur] = data;
  return buffer->cur;
}

static inline map_buffer_size_t
_map_buffer_buffer_push_back(map_buffer_buffer_t *buffer,
			     map_buffer_data_t data)
{
  if (buffer->cur == map_buffer_npos)
    buffer->cur = -1;
  if (buffer->cur == buffer->last-1)
    return map_buffer_npos;
  ++buffer->cur;
  buffer->datas[buffer->cur] = data;
  return buffer->cur;
}

static inline map_buffer_size_t
_map_buffer_buffer_pop_front(map_buffer_buffer_t *buffer)
{
  if (buffer->cur != buffer->last)
    ++buffer->cur;
  if (buffer->cur == buffer->last)
    return map_buffer_npos;
  return buffer->cur;
}

static inline map_buffer_size_t
_map_buffer_buffer_pop_back(map_buffer_buffer_t *buffer)
{
  if (buffer->cur != -1)
    return --buffer->cur;
  if (buffer->cur == -1)
    return map_buffer_npos;
  return buffer->cur;
}


map_buffer_t *map_buffer_create()
{
  return calloc(1, sizeof(map_buffer_t));
}

void map_buffer_delete(map_buffer_t *map_buffer)
{
  int i;
  for (i = 0; i < map_buffer->map_size; ++i) {
    _map_buffer_buffer_delete(map_buffer->buffers[i]);
  }
  free(map_buffer->buffers);
  free(map_buffer);
}

static void map_buffer_realloc(map_buffer_t *map_buffer)
{
  map_buffer_buffer_t **tmp_buffers = map_buffer->buffers;

  if (map_buffer->map_size == 0)
    map_buffer->map_size = 2;
  else
    map_buffer->map_size <<= 1;

  map_buffer->buffers =
    malloc(sizeof(*map_buffer->buffers) * map_buffer->map_size);
  if (map_buffer->buffers == NULL) {
    map_buffer->buffers = tmp_buffers;
    return;
  }

  if (map_buffer->map_size == 2) { /* first alloc */
    map_buffer->last = map_buffer->map_size;
    map_buffer->buffers[map_buffer->first] =
      _map_buffer_buffer_create(MAP_BUFFER_SIZE);
    map_buffer->buffers[map_buffer->last-1] =
      _map_buffer_buffer_create(MAP_BUFFER_SIZE);
  } else {
    map_buffer_size_t used_size = map_buffer->last - map_buffer->first;
    map_buffer_size_t offset = (map_buffer->map_size - used_size) / 2;
    memcpy(map_buffer->buffers + offset,
	   tmp_buffers + map_buffer->first,
	   sizeof(*map_buffer->buffers) * used_size);
    map_buffer->first = offset;
    map_buffer->last = map_buffer->first + used_size;
    free(tmp_buffers);
  }
}

map_buffer_size_t map_buffer_push_front(map_buffer_t *map_buffer,
					map_buffer_data_t data)
{
  map_buffer_size_t pos;
  if (map_buffer->map_size == 0) {
    map_buffer_realloc(map_buffer);
  }

  pos = _map_buffer_buffer_push_front(map_buffer->buffers[map_buffer->first], data);
  if (pos == map_buffer_npos) {
    if (map_buffer->first == 0) {
      map_buffer_realloc(map_buffer);
    }
    if (map_buffer->first == 0) {
      return map_buffer_npos;
    }

    --map_buffer->first;
    map_buffer->buffers[map_buffer->first] =
      _map_buffer_buffer_create(MAP_BUFFER_SIZE);
    if (map_buffer->buffers[map_buffer->first] == NULL)
      return map_buffer_npos;

    return _map_buffer_buffer_push_front(map_buffer->buffers[map_buffer->first], data);
  }
  return pos;
}

map_buffer_size_t map_buffer_push_back(map_buffer_t *map_buffer,
				       map_buffer_data_t data)
{
  map_buffer_size_t pos;

  if (map_buffer->map_size == 0) {
    map_buffer_realloc(map_buffer);
  }

  pos = _map_buffer_buffer_push_back(map_buffer->buffers[map_buffer->last-1], data);
  if (pos == map_buffer_npos) {
    if (map_buffer->last == map_buffer->map_size) {
      map_buffer_realloc(map_buffer);
    }
    if (map_buffer->last == map_buffer->map_size) {
      return map_buffer_npos;
    }

    ++map_buffer->last;
    map_buffer->buffers[map_buffer->last-1] =
      _map_buffer_buffer_create(MAP_BUFFER_SIZE);
    if (map_buffer->buffers[map_buffer->last-1] == NULL)
      return map_buffer_npos;

    return _map_buffer_buffer_push_back(map_buffer->buffers[map_buffer->last-1], data);
  }
  return pos;
}

void map_buffer_pop_front(map_buffer_t *map_buffer)
{
  if (_map_buffer_buffer_pop_front(map_buffer->buffers[map_buffer->first])
      == map_buffer_npos) {
    if (map_buffer->first < map_buffer->last-2)
      ++map_buffer->first;
    return;
  }
}

void map_buffer_pop_back(map_buffer_t *map_buffer)
{
  if (_map_buffer_buffer_pop_back(map_buffer->buffers[map_buffer->last-1])
      == map_buffer_npos) {
    if (map_buffer->last-2 > map_buffer->first)
      --map_buffer->last;
    return;
  }
  _map_buffer_buffer_pop_back(map_buffer->buffers[map_buffer->last-1]);
}

map_buffer_size_t map_buffer_find(map_buffer_t *map_buffer,
				  map_buffer_data_t data)
{
  map_buffer_size_t i, j, pos = 0;
  map_buffer_buffer_t *buffer;
  if (map_buffer->map_size == 0)
    return map_buffer_npos;

  for (i = map_buffer->first; i != map_buffer->last; ++i) {
    map_buffer_size_t start, end;
    buffer = map_buffer->buffers[i];

    start = 0;
    end = buffer->last;
    if (i == map_buffer->first)
      start = buffer->cur;
    else if (i == map_buffer->last-1)
      end = buffer->cur+1;

    for (j = start; j != end; ++j, ++pos) {
      if (buffer->datas[j] == data)
	return pos;
    }
  }
  return map_buffer_npos;
}

void map_buffer_print(map_buffer_t *map_buffer)
{
  map_buffer_size_t i, j;
  map_buffer_buffer_t *buffer;
  if (map_buffer->map_size == 0)
    return;

  for (i = map_buffer->first; i != map_buffer->last; ++i) {
    map_buffer_size_t start, end;
    printf("[%d] ", i);
    buffer = map_buffer->buffers[i];

    start = 0;
    end = buffer->last;
    if (i == map_buffer->first)
      start = buffer->cur;
    else if (i == map_buffer->last-1)
      end = buffer->cur+1;

    for (j = start; j != end; ++j) {
      printf("%d ", buffer->datas[j]);
    }
    printf("\n");
  }
}
