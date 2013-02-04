#ifndef __list_h__
#define __list_h__

typedef struct list_node {
	void *data;
	struct list_node *next;
} list_node_t;

/* linked list */
list_node_t* list_create(void *data);
void list_destroy(list_node_t **list);
list_node_t* list_insert_after(list_node_t *node, void *data);
list_node_t* list_insert_beginning(list_node_t *list, void *data);
list_node_t* list_insert_end(list_node_t *list, void *data);
void list_remove(list_node_t **list, list_node_t *node);
void list_remove_by_data(list_node_t **list, void *data);
list_node_t* list_find_node(list_node_t *list, list_node_t *node);
list_node_t* list_find_by_data(list_node_t *list, void *data);
list_node_t* list_find(list_node_t *list, int(*func)(list_node_t*,void*), void *data);

#endif
