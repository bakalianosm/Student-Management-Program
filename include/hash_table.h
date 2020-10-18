
#pragma once // #include το πολύ μία φορά

#include "common_types.h"

typedef struct map* Map;


// Creates and returns any emply map
Map map_create(CompareFunc compare,int hash_size, DestroyFunc destroy_key, DestroyFunc destroy_value);

// Returns the size of the Map

int map_size(Map map);

// Inserts the key with value. If exists key with the same value the past key and value
// is replaced by the new.
void map_insert(Map map, Pointer key, Pointer value);

// Αφαιρεί το κλειδί που είναι ισοδύναμο με key από το map, αν υπάρχει.
// Επιστρέφει true αν βρέθηκε τέτοιο κλειδί, διαφορετικά false.

// Removes the key from the map if exists and returns true
bool map_remove(Map map, Pointer key);

// Returns the value that has the key
Pointer map_find(Map map, Pointer key);

// Changes the function that is called in every removal of key/value
DestroyFunc map_set_destroy_key  (Map map, DestroyFunc destroy_key  );
DestroyFunc map_set_destroy_value(Map map, DestroyFunc destroy_value);

// Frees all the memory that the map allocated 
void map_destroy(Map map);


#define MAP_EOF (MapNode)0

typedef struct map_node* MapNode;

// Returns the first node of the map

MapNode map_first(Map map);

// Returns the next node of the given mapnode or MAP_EOF

MapNode map_next(Map map, MapNode node);

// Returns the key of the given node

Pointer map_node_key(Map map, MapNode node);

// Returns the value of the given node
Pointer map_node_value(Map map, MapNode node);

// Returns the node with the key
MapNode map_find_node(Map map, Pointer key);




typedef uint (*HashFunc)(Pointer);


// Implemented hash functions
uint hash_string(Pointer value);		// Χρήση όταν το key είναι char*
uint hash_int(Pointer value);			// Χρήση όταν το key είναι int*
uint hash_pointer(Pointer value);		// Χρήση όταν το key είναι pointer που θεωρείται διαφορετικός από οποιονδήποτε άλλο pointer

// Sets the hash function
void map_set_hash_function(Map map, HashFunc hash_func);