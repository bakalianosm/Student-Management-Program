
// source file for the inverted index that I implemented for this assignment.


#include <stdlib.h>
#include "inverted_index.h"

struct inverted_index{
    List list;
    int size ;
};

struct index_node{
    int year;
    List indexList;
};

int compare_index_nodes(Pointer a, Pointer b){
	return ((indexNode)a)->year - ((indexNode)b)->year;
}


invertedIndex invertedIndex_create(){
    invertedIndex ii = malloc(sizeof(*ii));
    ii->list = list_create(NULL);

    return ii;
}

int invertedIndex_size(invertedIndex ii){
    return ii->size;
}

void invertedIndex_insert(invertedIndex ii , Record rec){
    
    // The main creterio to insert a record inside the inverted index 
    // is the year . We have to find the list that contains the records 
    // with the inserting record's year and, then to insert it . 

    
    // First make a node with the current year to insert at the list.
    indexNode iNode = malloc(sizeof(*iNode));
    iNode->year = rec->year ;
    iNode->indexList = list_create(NULL);


    ListNode lNode = list_find(ii->list, iNode, compare_index_nodes);

    if(lNode==NULL){
        // that means that now is the first time that we see this year
        // we have to isert the node in the list. 

        // first insert the record in the nested list
        list_insert_next(iNode->indexList, LIST_EOF, rec);

        //and then insert the List node at the inverted indexes list

        list_insert_next(ii->list, LIST_EOF, iNode);

    }
    else{
        // if there is a node that contains records by this year.
        list_insert_next(iNode->indexList, LIST_EOF, rec);

        
    }

}
