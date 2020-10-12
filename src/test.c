#include "common_types.h"
#include "hash_table.h"
#include "inverted_index.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a temporary object file for testing the modules
int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

int compare_recs(Pointer a, Pointer b) {
	return ((Record)a)->StudentID - ((Record)b)->StudentID ;
}


int main(void){


    // invertedIndex i_i = invertedIndex_create(NULL);
    // Map hashTable = map_create(compare_recs,NULL,NULL);
    // map_set_hash_function(hashTable, hash_int);
    Record r1= malloc(sizeof(*r1));
    r1->StudentID = 10001;
    r1->firstName = strdup("miche");
    r1->lastName = strdup("bakalianos");
    r1->zipNum = 35001;
    r1->year = 2020;
    r1->gpa = 5.2 ;

    Record r2= malloc(sizeof(*r1));
    r2->StudentID = 25306;
    r2->firstName = strdup("gians");
    r2->lastName = strdup("bakalianos");
    r2->zipNum = 35001;
    r2->year = 2019;
    r2->gpa = 6.2 ;

    Record r3= malloc(sizeof(*r1));
    r3->StudentID = 30056;
    r3->firstName = strdup("jimmy");
    r3->lastName = strdup("bakalianos");
    r3->zipNum = 17745;
    r3->year = 2010;
    r3->gpa = 9.2 ;

    Record r4= malloc(sizeof(*r1));
    r4->StudentID = 15352;
    r4->firstName = strdup("stefa");
    r4->lastName = strdup("bakalianos");
    r4->zipNum = 12545;
    r4->year = 2020;
    r4->gpa = 6.4 ;

    Record r5= malloc(sizeof(*r1));
    r5->StudentID = 10045;
    r5->firstName = strdup("chris");
    r5->lastName = strdup("bakalianos");
    r5->zipNum = 11595;
    r5->year = 2008;
    r5->gpa = 5.2 ;
    

    Record r6= malloc(sizeof(*r1));
    r6->StudentID = 10034;
    r6->firstName = strdup("orsan");
    r6->lastName = strdup("bakalianos");
    r6->zipNum = 12195;
    r6->year = 2008;
    r6->gpa = 5.9 ;


    // printf("RECORD :  %d %s %s %d %d %.1f\n",r1->StudentID,r1->firstName,r1->lastName,r1->zipNum,r1->year,r1->gpa);
    // printf("RECORD :  %d %s %s %d %d %.1f\n",r2->StudentID,r2->firstName,r2->lastName,r2->zipNum,r2->year,r2->gpa);
    // printf("RECORD :  %d %s %s %d %d %.1f\n",r3->StudentID,r3->firstName,r3->lastName,r3->zipNum,r3->year,r3->gpa);
    // printf("RECORD :  %d %s %s %d %d %.1f\n",r4->StudentID,r4->firstName,r4->lastName,r4->zipNum,r4->year,r4->gpa);
    // printf("RECORD :  %d %s %s %d %d %.1f\n",r5->StudentID,r5->firstName,r5->lastName,r5->zipNum,r5->year,r5->gpa);



    // map_insert(hashTable, create_int(r1->StudentID) , r1);
    // map_insert(hashTable, create_int(r2->StudentID) , r2);
    // map_insert(hashTable, create_int(r3->StudentID) , r3);
    // map_insert(hashTable, create_int(r4->StudentID) , r4);
    // map_insert(hashTable, create_int(r5->StudentID) , r5);

    // printf("HASH TABLE SIZE IS %d\n",map_size(hashTable));
    // map_destroy(hashTable);


    invertedIndex ii = invertedIndex_create();
    // invertedIndex_destroy(ii);

    invertedIndex_insert(ii,r1);
    invertedIndex_insert(ii,r2);
    invertedIndex_insert(ii,r3);
    invertedIndex_insert(ii,r4);
    invertedIndex_insert(ii,r5);
    invertedIndex_insert(ii,r6);


    invertedIndex_delete(ii,r1);
    invertedIndex_delete(ii,r2);
    invertedIndex_delete(ii,r3);
    invertedIndex_delete(ii,r4);
    invertedIndex_delete(ii,r5);
    invertedIndex_delete(ii,r6);
    invertedIndex_destroy(ii);
    
}

