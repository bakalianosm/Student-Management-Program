
// source file for the inverted index that I implemented for this assignment.


#include <stdlib.h>
#include "inverted_index.h"

#define INT_MAX 99999999
struct inverted_index{
    List list;
    int size ;
};

struct index_node{
    int year;
    int yearCount;
    List indexList;
};



int rec_compare(Pointer a, Pointer b){
  return ((Record)a)->StudentID - ((Record)b)->StudentID  ;      
}
void rec_destroy(Pointer a){
    free( ((Record)a)->firstName);
    free( ((Record)a)->lastName);
    free( ((Record)a));
}
void indexNode_destroy(Pointer a){
    
    list_destroy( ((indexNode)a)->indexList);
    free(((indexNode)a));
}

int compare_index_nodes(Pointer a, Pointer b){
	return ((indexNode)a)->year - ((indexNode)b)->year;
}



invertedIndex invertedIndex_create(){
    invertedIndex ii = malloc(sizeof(*ii));
    ii->list = list_create(indexNode_destroy);
    ii->size = 0;

    return ii;
}

int invertedIndex_size(invertedIndex ii){
    return ii->size;
}

int indexNode_year(indexNode node){
    return node->year;
}

int indexNode_yearCount(indexNode node){
    return node->yearCount;
}
void invertedIndex_insert(invertedIndex ii , Record rec){
    
    
    // First we have to find in which list it has to be stored.

    //printf("Inverted index inserting\n");
    indexNode toFind = malloc(sizeof(*toFind));
    toFind->year =rec->year;

    indexNode iNode = (indexNode)list_find(ii->list, toFind, compare_index_nodes);


    if(iNode!=NULL){
        //printf("Exists node with this year.Insert the record\n");
        list_insert_next(iNode->indexList, LIST_EOF, rec);
        ii->size++;
        iNode->yearCount++;
    }
    else{
        //printf("Doesn't exist node with this year.Let's create it!\n");
        indexNode new = malloc(sizeof(*new));
        new->year = rec->year;
        // new->indexList = list_create(rec_destroy);
        new->indexList = list_create(NULL);
        list_insert_next(new->indexList, LIST_EOF, rec);
        list_insert_next(ii->list, LIST_EOF, new);
        ii->size++;
        new->yearCount=1 ;

    }


    // list_destroy(toFind->indexList);
    free(toFind);

    // list_destroy(toFind->indexList);
    // free(toFind);
}

bool invertedIndex_find( Record rec){
    return 0;
}

void invertedIndex_delete(invertedIndex ii,int id, int year){

    indexNode toFind = malloc(sizeof(*toFind));
    toFind->year =year;

    indexNode iNode = (indexNode)list_find(ii->list, toFind, compare_index_nodes);

    if(iNode!=NULL){
        list_remove(iNode->indexList, create_int(id) , rec_compare);
        printf("Record removed form inverted index\n");
        ii->size--;
    }
    else{
        printf("Not found year \n");
    }
    

    free(toFind);
}
void invertedIndex_destroy(invertedIndex ii){
    
    list_destroy(ii->list);
    free(ii);
}

int invertedIndex_yearCount(invertedIndex ii, int year){
    indexNode toFind = malloc(sizeof(*toFind));
    toFind->year = year;

    indexNode iNode = (indexNode)list_find(ii->list, toFind, compare_index_nodes);
    

    free(toFind);
    if(iNode!=NULL) return iNode->yearCount;
    else return 0;
    

    
}

void invertedIndex_count(invertedIndex ii){
    for(ListNode node = list_first(ii->list) ;          
        node != LIST_EOF;                          
        node = list_next(ii->list, node)) { 
            indexNode iNode = (indexNode)list_node_value(ii->list,node);
            int y = indexNode_year(iNode);
            int yCnt = indexNode_yearCount(iNode);
            printf("[%d,%d],",y,yCnt);
    }   
   
}



void invertedIndex_topNstudents(invertedIndex ii, int num,int year){
    indexNode toFind = malloc(sizeof(*toFind));
    toFind->year = year;

    indexNode iNode = (indexNode)list_find(ii->list, toFind, compare_index_nodes);
    
    if(num < iNode->yearCount){

    }
    else{
        for(ListNode node = list_first(iNode->indexList) ;          
        node != LIST_EOF;                          
        node = list_next(iNode->indexList, node)) { 
            Record r = (Record)list_node_value(iNode->indexList, node);
            printf("RECORD :  %d %s %s %d %d %.1f\n",r->StudentID,r->firstName,r->lastName,r->zipNum,r->year,r->gpa);
        }
    }
    
    free(toFind);
}

void invertedIndex_averageYear(invertedIndex ii, int year){
    indexNode toFind = malloc(sizeof(*toFind));
    toFind->year = year;

    indexNode iNode = (indexNode)list_find(ii->list, toFind, compare_index_nodes);

    free(toFind);
    if(iNode!=NULL){
        float sum = 0.0 ;
        float avg ;
        for(ListNode node = list_first(iNode->indexList) ;          
            node != LIST_EOF;                          
            node = list_next(iNode->indexList, node)) { 
                Record r = (Record)list_node_value(iNode->indexList, node);
                sum += r->gpa ;
            }

        avg = sum/iNode->yearCount;
        printf("\033[0;32m");
        printf("%.2f\n",avg);
        printf("\033[0m"); 
    }
    else{
        printf("\033[0;31m");
        printf("No students enrolled in %d\n", year);
        printf("\033[0m"); 
    }
}

void invertedIndex_minimumYear(invertedIndex ii, int year){
    indexNode toFind = malloc(sizeof(*toFind));
    toFind->year = year;

    indexNode iNode = (indexNode)list_find(ii->list, toFind, compare_index_nodes);

    free(toFind);
    if(iNode!=NULL){
        float min = INT_MAX ; 
        for(ListNode node = list_first(iNode->indexList) ;          
            node != LIST_EOF;                          
            node = list_next(iNode->indexList, node)) { 
                Record r = (Record)list_node_value(iNode->indexList, node);
                if (r->gpa < min )
                    min = r->gpa ;    
        }
        if(min!=INT_MAX) printf("MINIMUM GPA FOR THIS YEAR IS %.2f\n",min);
        for(ListNode node = list_first(iNode->indexList) ;          
            node != LIST_EOF;                          
            node = list_next(iNode->indexList, node)) { 
                Record r = (Record)list_node_value(iNode->indexList, node);
                if (r->gpa == min )
                    printf("%d,",r->StudentID);    
        } 
        printf("\n");  
    }
    else{
        printf("\033[0;31m");
        printf("No students enrolled in %d\n", year);
        printf("\033[0m");  
    }
    


}