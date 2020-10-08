
// header file for the inverted_index structure that 
// i implemented for this project 

#pragma once
#include "common_types.h"
#include "linked_list.h"


typedef struct inverted_index* invertedIndex;
typedef struct index_node* indexNode;

// a function to compare inverted index nodes
int compare_index_nodes(Pointer a,Pointer b);

// This function simply allocates the necessary memory that
// needed to store the inverted index
invertedIndex invertedIndex_create();

// This function returns the number of records that are stored
// in the inverted index
int invertedIndex_size(invertedIndex ii);

// This function inserts the given record inside the proper list 
void invertedIndex_insert(invertedIndex ii , Record record);
