

// source file for the hash table that I implemented for this assignment.

#include <stdlib.h>

#include "hash_table.h"
#include "linked_list.h"	



struct map_node{
	Pointer key;		
	Pointer value;  	
} ;

// The hash table structure
struct map {
	List* array;				// The array of lists that implements the map
	int capacity;				
	int size;					// How many elements the map contains
	CompareFunc compare;		// Compare pointers function
	HashFunc hash_function;		//
	DestroyFunc destroy_key;	// Function that destroys / free the keys
	DestroyFunc destroy_value;	// // Function that destroys / free the values
};


Map map_create(CompareFunc compare,int hash_size, DestroyFunc destroy_key, DestroyFunc destroy_value) {
	// First allocate the memory that is needed hash table
	Map map = malloc(sizeof(*map));
	map->capacity = hash_size;
	map->array = malloc(map->capacity * sizeof(List));

	// First initialize the lists that will be used 
	for (int i = 0; i < map->capacity; i++){
		map->array[i] = list_create(free);
	}
	map->size = 0;
	map->compare = compare;
	map->destroy_key = destroy_key;
	map->destroy_value = destroy_value;

	return map;
}


int map_size(Map map) {
	return map->size;
}



void map_insert(Map map, Pointer key, Pointer value) {
	// Scan all the map till we find an empty positioin to store the key and the value
	// or till we find the key and replace the value
	
	bool already_in_map = false;

	// First we have to find where the key is going to be stored
	uint bucket;
	bucket = map->hash_function(key) % map->capacity;	
	

	// This node is used to check if the current key is inside 
	MapNode toFind = map_find_node(map,key);
	if(toFind!=MAP_EOF) already_in_map = true;
	
	// If the key is already in the map 
	// Replace the value  
	if(already_in_map){
		if (toFind->key != key && map->destroy_key != NULL)
			map->destroy_key(toFind->key);

		if (toFind->value != value && map->destroy_value != NULL)
			map->destroy_value(toFind->value);

		toFind->key = key;
		toFind->value = value;
	}
	// If the current key isn't in the map
	else{

		// We make a new node that will be inserted to the map
		// and assign key and value 
		MapNode toInsert  = malloc(sizeof(*toInsert));
		toInsert->key = key;
		toInsert->value = value;

		// And , insert the node in the map
		list_insert_next(map->array[bucket],LIST_BOF,toInsert);

		// Increase the size
		map->size++;
	}
	
}


bool map_remove(Map map, Pointer key) {
	
	// First we have to find where the key stored (if is stored)
	uint bucket;
	bucket = map->hash_function(key) % map->capacity;

	// We are making temp nodes to help us 
	ListNode prev=LIST_BOF;
	MapNode m;

	// Iterate through the list
	for(ListNode node = list_first(map->array[bucket]) ;          
    node != LIST_EOF;                          
    node = list_next(map->array[bucket], node)) {            
		m = list_node_value(map->array[bucket],node);
		int* node_key = map_node_key(map,m );  

		if(map->compare(key,node_key)==0) {
			if (map->destroy_key != NULL)
				map->destroy_key(m->key);
			if (map->destroy_value != NULL)
				map->destroy_value(m->value);

			// Remove the node
			list_remove_next(map->array[bucket],prev);

			// Decrease the map's size
			map->size--;

			// And everything worked fine
			return true;
		} 
		prev = node;
	}
	// If the node didn't find return false
	return false;
}


// Search in the map. Return the value of the given key
Pointer map_find(Map map, Pointer key) {
	MapNode node = map_find_node(map, key);
	if (node != MAP_EOF)
		return node->value;
	else
		return NULL;
}


DestroyFunc map_set_destroy_key(Map map, DestroyFunc destroy_key) {
	DestroyFunc old = map->destroy_key;
	map->destroy_key = destroy_key;
	return old;
}

DestroyFunc map_set_destroy_value(Map map, DestroyFunc destroy_value) {
	DestroyFunc old = map->destroy_value;
	map->destroy_value = destroy_value;
	return old;
}

//  Free the memory that the map allocated 
void map_destroy(Map map) {

	// Iterate throught all the lists
	for (int i = 0 ; i< map->capacity ; i++){
		// And for every list node
		for(ListNode node = list_first(map->array[i]) ;          
    	node != LIST_EOF;                          
    	node = list_next(map->array[i], node)) {   

			// Parse the map node       
			MapNode m = list_node_value(map->array[i],node);
				//Record value = (Record)map_node_value(map, m);

				// And then return its contains
				// and destroy them
				if (map->destroy_key != NULL){
					map->destroy_key(m->key);
				}
				else{
					free(m->key);
				}
			
				if (map->destroy_value != NULL){
					map->destroy_value(m->value);
				}
			}
		// Destroy the current list
		list_destroy(map->array[i]);
	}
	
	// Destroy the array of the list 
	free(map->array);

	// And then the whole map
	free(map);
}


/////////////////////// Iterate through the map///////////////////////////

MapNode map_first(Map map) {
	if(map->array[0]!=NULL)
		if(list_first(map->array[0])!= LIST_EOF) return list_node_value(map->array[0],list_first(map->array[0]));
	return MAP_EOF;
}

MapNode map_next(Map map, MapNode node) {

	// Find where the key hashes
	uint bucket;
	bucket = map->hash_function(node->key) % map->capacity;

	// Find the listnode thah contains the map ndode
	// And then iterate through the list until the wanted node is found

	ListNode lnode ;
	for( lnode = list_first(map->array[bucket]) ;          
    lnode != LIST_EOF;                          
    lnode = list_next(map->array[bucket], lnode)) {            
		MapNode m = list_node_value(map->array[bucket],lnode);
		Pointer node_key = map_node_key(map,m );  		  
		Pointer node_value = map_node_value(map,m );	  
		
		if(map->compare(node->key,node_key)==0 && map->compare(node->value,node_value)==0) break; 
	}

	// If exists next node in this list , I have to return it .
	if(list_next(map->array[bucket],lnode)!=LIST_EOF) 
		return list_node_value(map->array[bucket],list_next(map->array[bucket],lnode));
	else{
	// Either , go to the next bucket and return the first node	
		bucket++;
		if(bucket <= map->capacity ) {
			if(list_first(map->array[bucket])!=NULL)
				return list_node_value(map->array[bucket],list_first(map->array[bucket]));
		}
	}
	// Else something went wrong :(
	return MAP_EOF;
}

Pointer map_node_key(Map map, MapNode node) {
	return node->key;
}

Pointer map_node_value(Map map, MapNode node) {
	return node->value;
}

MapNode map_find_node(Map map, Pointer key) {
	
	uint bucket;
	bucket = map->hash_function(key) % map->capacity;
	
	// Iterate throught the list
	for(ListNode node = list_first(map->array[bucket]) ;         
    node != LIST_EOF;                         
    node = list_next(map->array[bucket], node)) {           
		MapNode m = list_node_value(map->array[bucket],node);
		Pointer node_key = map_node_key(map,m ); 
		if(map->compare(key,node_key)==0) return m;
		
	}
	return MAP_EOF;
}


void map_set_hash_function(Map map, HashFunc func) {
	map->hash_function = func;
}

uint hash_int(Pointer value) {
	return *(int*)value;
}

