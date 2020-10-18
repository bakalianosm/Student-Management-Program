
// source file for the inverted index that I implemented for this assignment.


#include <stdlib.h>
#include "inverted_index.h"

#define INT_MAX 99999999
#define INT_MIN -9999999

// The struct of inverted index 
struct inverted_index{
    List list;
    int size ;
};


// The index node is a node that is contained inside the inverted index and 
// contains year ,year count and a list of records assigned to each year
struct index_node{
    int year;
    List indexList;
};

// This is a compare function for Records
int rec_compare(Pointer a, Pointer b){
  return ((Record)a)->StudentID - ((Record)b)->StudentID  ;      
}

// This function is used to deallocate the memory that a record holds.
void rec_destroy(Pointer a){
    free( ((Record)a)->firstName);
    free( ((Record)a)->lastName);
    free( ((Record)a));
}

// This function deallocates an indexNode 
void indexNode_destroy(Pointer a){    
    list_destroy( ((indexNode)a)->indexList);
    free(((indexNode)a));
}

// This function is used for indexNodes similarity
// Two indexNodes are similar if they have the same year 
int compare_index_nodes(Pointer a, Pointer b){
	return ((indexNode)a)->year - ((indexNode)b)->year;
}


invertedIndex invertedIndex_create(){
    // First allcate the memory that an invertedIndex needs
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


void invertedIndex_insert(invertedIndex ii , Record rec){
    
    
    // First we have to find in which list it has to be stored.
    // We make a temporary indexNode only to use in the compare function
    indexNode toFind = malloc(sizeof(*toFind));
    toFind->year =rec->year;


    // Try to find the node with "year" in the invertedIndex 
    indexNode iNode = (indexNode)list_find(ii->list, toFind, compare_index_nodes);


    if(iNode!=NULL){

        // And if exist node with this year  
        // Insert the record at the end of the indexNodes list
        list_insert_next(iNode->indexList, LIST_EOF, rec);
        ii->size++;
    }
    else{
        // If there is no indexNode with the records year, we have to make 
        // a new indexNode with this year
        indexNode new = malloc(sizeof(*new));
        new->year = rec->year;
        
        // Allocate memory for it's list
        new->indexList = list_create(NULL);
        // Insert the record into the nested list
        list_insert_next(new->indexList, LIST_EOF, rec);

        // And , insert the indexNode into the invertedIndex 
        list_insert_next(ii->list, LIST_EOF, new);
        ii->size++;


    }

    // Deallocate unused pointers
    free(toFind);
}



void invertedIndex_delete(invertedIndex ii,int id, int year){
    
    // First we have to find in which list it has to be stored.
    // We make a temporary indexNode only to use in the compare function
    indexNode toFind = malloc(sizeof(*toFind));
    toFind->year =year;

    indexNode iNode = (indexNode)list_find(ii->list, toFind, compare_index_nodes);
    
    // And if exist node with this year 
    if(iNode!=NULL){
        ListNode prev = LIST_BOF ;
        // Remove the current record from the nested list 
        // First, find the record in the list
        for(ListNode node = list_first(iNode->indexList) ;          
            node != LIST_EOF;                          
            node = list_next(iNode->indexList, node)) { 
               Record r = (Record)list_node_value(iNode->indexList, node); 
               if (id == r->StudentID){
                   list_remove_next(iNode->indexList, prev);
                   break;
               }
                prev = node ;
        }
    }
    else{
        printf("Not found year \n");
    }

    // Deallocate unused Pointers
    free(toFind);
}
void invertedIndex_destroy(invertedIndex ii){

    list_destroy(ii->list);
    free(ii);
}

int invertedIndex_yearCount(invertedIndex ii, int year){
    // First we have to find in which list it has to be stored.
    // We make a temporary indexNode only to use in the compare function
    indexNode toFind = malloc(sizeof(*toFind));
    toFind->year = year;

    indexNode iNode = (indexNode)list_find(ii->list, toFind, compare_index_nodes);
    

    free(toFind);
    if(iNode!=NULL) return list_size(iNode->indexList);
    else return 0;
    

    
}

void invertedIndex_count(invertedIndex ii){
    // Iterate throught the Inverted Index Nodes and for each
    // year return its count and then print it 

    for(ListNode node = list_first(ii->list) ;          
        node != LIST_EOF;                          
        node = list_next(ii->list, node)) { 
            indexNode iNode = (indexNode)list_node_value(ii->list,node);
            int y = indexNode_year(iNode);
            int yCnt = list_size(iNode->indexList);
            printf("[%d,%d],",y,yCnt);
    }   
   
}


float findMax(List list){
    float max = INT_MIN ; 
        for(ListNode node = list_first(list) ;          
            node != LIST_EOF;                          
            node = list_next(list, node)) { 
                Record r = (Record)list_node_value(list, node);
                if (r->gpa > max )
                    max = r->gpa ;    
        }
        if(max!=INT_MIN){
            for(ListNode node = list_first(list) ;          
                node != LIST_EOF;                          
                node = list_next(list, node)) { 
                    Record r = (Record)list_node_value(list, node);
                    if (r->gpa == max ){
                        printf("%d %s %s %d %d %.1f\n",r->StudentID,r->firstName,r->lastName,r->zipNum,r->year,r->gpa);
                        break;
                    }  
            } 
        }
        printf("\n"); 
       
    return max;
}

void invertedIndex_topNstudents(invertedIndex ii, int num,int year){
    indexNode toFind = malloc(sizeof(*toFind));
    toFind->year = year;

    indexNode iNode = (indexNode)list_find(ii->list, toFind, compare_index_nodes);
    

    List tempList = list_create(NULL);
    for(ListNode node = list_first(iNode->indexList) ;          
        node != LIST_EOF;                          
        node = list_next(iNode->indexList, node)) { 
            Record r = (Record)list_node_value(iNode->indexList, node);
            list_insert_next(tempList,LIST_EOF,r);
    }

    if(num < list_size(iNode->indexList)){

        for(int i = 0 ; i < num ; i++){
            ListNode prev = LIST_BOF;
            float max = findMax(tempList);
            for(ListNode node = list_first(tempList) ;          
                node != LIST_EOF;                          
                node = list_next(tempList, node)) { 
                Record r = (Record)list_node_value(tempList, node); 
                if (r->gpa == max){
                    list_remove_next(tempList, prev);
                    break;
                }
                prev = node ;
            }
        }

    }
    else{
        for(ListNode node = list_first(iNode->indexList) ;          
        node != LIST_EOF;                          
        node = list_next(iNode->indexList, node)) { 
            Record r = (Record)list_node_value(iNode->indexList, node);
            printf("RECORD :  %d %s %s %d %d %.1f\n",r->StudentID,r->firstName,r->lastName,r->zipNum,r->year,r->gpa);
        }
    }
    list_destroy(tempList);
    free(toFind);
}

void invertedIndex_averageYear(invertedIndex ii, int year){

    // First we have to find in which list it has to be stored.
    // We make a temporary indexNode only to use in the compare function
    indexNode toFind = malloc(sizeof(*toFind));
    toFind->year = year;

    indexNode iNode = (indexNode)list_find(ii->list, toFind, compare_index_nodes);

    // And if exist node with this year 
    if(iNode!=NULL){

        float sum = 0.0 ;
        float avg ;

        //Iterate throught the nested list with the records 
        for(ListNode node = list_first(iNode->indexList) ;          
            node != LIST_EOF;                          
            node = list_next(iNode->indexList, node)) { 
                Record r = (Record)list_node_value(iNode->indexList, node);
                // and add each records gpa to the summary variable
                sum += r->gpa ;
            }
        
        // Calculate the average and print it.
        avg = sum/list_size(iNode->indexList);
        printf("\033[0;32m");
        printf("%.2f\n",avg);
        printf("\033[0m"); 
    }
    else{
        // If there are no students in this year
        printf("\033[0;31m");
        printf("No students enrolled in %d\n", year);
        printf("\033[0m"); 
    }

    free(toFind);

}

void invertedIndex_minimumYear(invertedIndex ii, int year){
    // First we have to find in which list it has to be stored.
    // We make a temporary indexNode only to use in the compare function

    indexNode toFind = malloc(sizeof(*toFind));
    toFind->year = year;

    indexNode iNode = (indexNode)list_find(ii->list, toFind, compare_index_nodes);
    
     // And if exist node with this year  
    if(iNode!=NULL){
        // Iterate through its list and find the minimum
        float min = INT_MAX ; 
        for(ListNode node = list_first(iNode->indexList) ;          
            node != LIST_EOF;                          
            node = list_next(iNode->indexList, node)) { 
                Record r = (Record)list_node_value(iNode->indexList, node);
                if (r->gpa < min )
                    min = r->gpa ;    
        }
        if(min!=INT_MAX){
            for(ListNode node = list_first(iNode->indexList) ;          
                node != LIST_EOF;                          
                node = list_next(iNode->indexList, node)) { 
                    Record r = (Record)list_node_value(iNode->indexList, node);
                    if (r->gpa == min ){
                        printf("\033[0;32m");
                        printf("%d %s %s %d %d %.1f\n",r->StudentID,r->firstName,r->lastName,r->zipNum,r->year,r->gpa);
                        printf("\033[0m"); 
                    }
            } 
        }
        printf("\n");  
    }
    else{
        printf("\033[0;31m");
        printf("No students enrolled in %d\n", year);
        printf("\033[0m");  
    }
    
    free(toFind);
}
