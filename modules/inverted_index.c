
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
void rec_destroy(Record a){
    free(a->firstName);
    free(a->lastName);
    free(a);
}
void indexNode_destroy(indexNode a){

    list_destroy(a->indexList);
    free(a);
}

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
    

    
    // First we have to find in which list it has to be stored.

    

    // if(invertedIndex_size(ii)==0){

    //     printf("Empty inverted index\n");

    //     indexNode new = malloc(sizeof(*new));
    //     new->year = rec->year;
    //     new->indexList = list_create(NULL);

    //     list_insert_next(new->indexList,LIST_EOF, rec);
    //     ii->size++;

    // }
    // else{
    //     printf("Entering in non empty inverted index\n");
    //     indexNode temp =malloc(sizeof(*temp));
    //     temp->year = rec->year;
        
    //     indexNode iNode = (indexNode)list_find_node(ii->list, temp, compare_index_nodes);

    //     if(iNode!=NULL){
    //         printf("Exists node with this year.Insert the record");
    //         List l = (List)iNode->indexList;
    //         list_insert_next(l, LIST_EOF, rec);
            
    //     }
    //     else{
    //         printf("Doesn't exist node with this year.Let's create it!\n");
    //         indexNode new = malloc(sizeof(*new));
    //         new->year = rec->year;
    //         new->indexList = list_create(NULL);
    //         list_insert_next(new->indexList, LIST_EOF, rec);
    //         list_insert_next(ii->list, LIST_EOF, new);

    //     }

    // }

    
    printf("Inverted index inserting\n");
    indexNode toFind = malloc(sizeof(*toFind));
    toFind->year =rec->year;

    indexNode iNode = (indexNode)list_find(ii->list, toFind, compare_index_nodes);


    if(iNode!=NULL){
        printf("Exists node with this year.Insert the record\n");
        list_insert_next(iNode->indexList, LIST_EOF, rec);
        ii->size++;
    }
    else{
        printf("Doesn't exist node with this year.Let's create it!\n");
        indexNode new = malloc(sizeof(*new));
        new->year = rec->year;
        new->indexList = list_create(NULL);
        list_insert_next(new->indexList, LIST_EOF, rec);
        list_insert_next(ii->list, LIST_EOF, new);
        ii->size++;

    }


    // list_destroy(toFind->indexList);
    // free(toFind);

    // list_destroy(toFind->indexList);
    // free(toFind);
}


void invertedIndex_destroy(invertedIndex ii){

    
    
    list_destroy(ii->list);
    free(ii);

}
