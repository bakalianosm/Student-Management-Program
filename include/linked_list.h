
#pragma once 
#include "common_types.h"


#define LIST_BOF (ListNode)0 // the node before the first
#define LIST_EOF (ListNode)0 // the node after the last 


typedef struct list* List;
typedef struct list_node* ListNode;

// If the destroy value != NULL then every time we remove an item
// the destroy_value(value) function is called

List list_create(DestroyFunc destroy_value);

// returns the size of the list

int list_size(List list);

// Inserts a new node after the given node or at the start of the list
// if the node is LIST_BOF with "value"
void list_insert_next(List list, ListNode node, Pointer value);

// Removes the next of the "node" or the first node if the given node is LIST_BOF
void list_remove_next(List list, ListNode node);


// Returns the first node that has "value" value based on  the compare function 

Pointer list_find(List list, Pointer value, CompareFunc compare);

// Changes the function tha is called when we remove or replace an element 
// to destroy_value and returns the past destroy_function
DestroyFunc list_set_destroy_value(List list, DestroyFunc destroy_value);

// Frees all the memory that the list has allocated 

void list_destroy(List list);


// List Iterate /////////////////////////////////////////////


// Returns the first node of the list, or LIST_EOF if the list is empty

ListNode list_first(List list);

// Returns the last node of the list, or LIST_BOF if the list is empty
ListNode list_last(List list);

// Returns the node after the "node" or LIST_EOF if the "node" hasn't next

ListNode list_next(List list, ListNode node);

// Returns the "value" of the "node"

Pointer list_node_value(List list, ListNode node);


// Finds the first element that has "value" value due to compare function
// Returns the node that contains the "value" either LIST_EOF if don't exists
// node with "value" value

ListNode list_find_node(List list, Pointer value, CompareFunc compare);

