
#include "common_types.h"
#include "hash_table.h"
#include "inverted_index.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 200 

int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

int compare_recs(Pointer a, Pointer b) {
	return ((Record)a)->StudentID - ((Record)b)->StudentID ;
}


int main(int argc, char* argv[]){
    printf("Everything is ok inside the main program\n");
    

    // Initialize the data structures         
    Map hashTable = map_create(compare_recs,NULL,NULL);
    map_set_hash_function(hashTable, hash_int);




    // First open the file for input.
    FILE *fptr ;
    fptr = fopen("/home/michalis/Desktop/os_delis/os_project_1/tst/input2.txt" , "r");
    
    // Just a check for successfully file opening.
    if(fptr == NULL) {
      perror("Error opening file");
      return(-1);
    }
    else{
        printf("File opened successfully!\n");
    }

    // Fetch lines of file.
    int counter = 0;
    while(!feof(fptr)){

        Record r = malloc(sizeof(*r)); 
        int id;
        char lastname[20];
        char firstname[20];
        int zip;
        int year;
        double gpa;


        fscanf(fptr, "%d %s %s %d %d %lf", &id, lastname, firstname, &zip, &year, &gpa);

        printf("DATA ENTERED : %d %s %s %d %d %.2f\n", id, lastname, firstname, zip, year, gpa);
        r->StudentID = id;
        r->lastName =  strdup(lastname);
        r->firstName = strdup(firstname);
        r->zipNum = zip;
        r->year = year;
        r->gpa = gpa;
        counter++;


        map_insert(hashTable, create_int(r->StudentID) , r);
    }
    int ht_size = map_size(hashTable);
    printf("HASH TABLE SIZE IS %d\n", ht_size);
    printf("READ %d RECORDS\n",counter);



    // Free allocated memory.
    map_destroy(hashTable);
    fclose(fptr);
}