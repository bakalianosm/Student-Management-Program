
// header file for the inverted_index structure that 
// i implemented for this project 

#pragma once
#include "common_types.h"
#include "linked_list.h"
#include <stdio.h>

typedef struct inverted_index* invertedIndex;
typedef struct index_node* indexNode;

// a function to compare inverted index nodes
int compare_index_nodes(Pointer a, Pointer b);

// This function simply allocates the necessary memory that
// needed to store the inverted index
invertedIndex invertedIndex_create();

// This function returns the number of records that are stored
// in the inverted index
int invertedIndex_size(invertedIndex ii);

// This function inserts the given record inside the proper list 
void invertedIndex_insert(invertedIndex ii , Record record);

//This function deallocate the memory that the inverted index allocated
void invertedIndex_destroy(invertedIndex ii);

// This function is used for searching a record 
bool invertedIndex_find(Record rec);

// This function is used to delete a record
void invertedIndex_delete(invertedIndex ii,Record rec);


// This function returns the count of records are stored for the (year)
int invertedIndex_yearCount(invertedIndex ii, int year);


// This function returns the count of records are stored for each year
void invertedIndex_count(invertedIndex ii);

// This function prints the top (num) students for (year)
void invertedIndex_topNstudents(invertedIndex ii, int num,int year);

// This function  prints the average GPA for (year) is exists or error message
void invertedIndex_averageYear(invertedIndex ii, int year);

// This function printfs
void invertedIndex_minimumYear(invertedIndex ii, int year);
