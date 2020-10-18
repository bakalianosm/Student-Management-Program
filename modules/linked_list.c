

#include <stdlib.h>

#include "linked_list.h"


// A list is a pointer to this struct
struct list {
	ListNode dummy;				// dummy node 
	ListNode last;				// pointer to the last node 
	int size;					
	DestroyFunc destroy_value;	
};

struct list_node {
	ListNode next;		
	Pointer value;		
};


List list_create(DestroyFunc destroy_value) {
	// First allocate the memory that is needed to represent a list
	List list = malloc(sizeof(*list));
	list->size = 0;
	list->destroy_value = destroy_value;

	// initialize dummy node 
	list->dummy = malloc(sizeof(*list->dummy));
	list->dummy->next = NULL;	
	
	// the list is empty, then the last node is the dummy node (or the first ;) )
	list->last = list->dummy;

	return list;
}

int list_size(List list) {
	return list->size;
}

void list_insert_next(List list, ListNode node, Pointer value) {

	// if the node is NULL then insert after the dummy node 
	if (node == NULL)
		node = list->dummy;

	// Crete a new node
	ListNode new = malloc(sizeof(*new));
	new->value = value;

	// Connect the next of the given node with the node we made
	new->next = node->next;
	node->next = new;

	// Update the size
	list->size++;
	if (list->last == node)
		list->last = new;
}

void list_remove_next(List list, ListNode node) {
	// if the node is NULL then remove the next after the dummy

	if (node == NULL)
		node = list->dummy;

	// The node to be deletet is the next of the given node 
	ListNode removed = node->next;

	if (list->destroy_value != NULL)
		list->destroy_value(removed->value);

	node->next = removed->next;		

	free(removed);

	// Update the size
	list->size--;
	if (list->last == removed)
		list->last = node;
}

Pointer list_find(List list, Pointer value, CompareFunc compare) {
	ListNode node = list_find_node(list, value, compare);
	return node == NULL ? NULL : node->value;
}

DestroyFunc list_set_destroy_value(List list, DestroyFunc destroy_value) {
	DestroyFunc old = list->destroy_value;
	list->destroy_value = destroy_value;
	return old;
}

void list_destroy(List list) {
	// Iterate through the list 
	ListNode node = list->dummy;
	while (node != NULL) {				
		ListNode next = node->next;		
		// Call the destroy value  function , even if the node is not the dummy 
		if (node != list->dummy && list->destroy_value != NULL)
			list->destroy_value(node->value);

		free(node);
		node = next;
	}

	// Free the struct 
	free(list);
}


// List iteration /////////////////////////////////////////////

ListNode list_first(List list) {
	// The first node is the next of the dummy 
	return list->dummy->next;
}

ListNode list_last(List list) {
	if (list->last == list->dummy)
		return LIST_EOF;		// the list is empty 
	else
		return list->last;
}

ListNode list_next(List list, ListNode node) {
    if(node != NULL)
        return node->next;
    else 
        return NULL;
}

Pointer list_node_value(List list, ListNode node) {
	if(node != NULL)
	    return node->value;
    else 
        return NULL;
}

ListNode list_find_node(List list, Pointer value, CompareFunc compare) {
	// Iterate through the list untill we find a node with the given value
	for (ListNode node = list->dummy->next; node != NULL; node = node->next)
		if (compare(value, node->value) == 0)
			return node;		// we found it!

	return NULL;	// Dont exists
}

