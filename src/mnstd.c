
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
    printf("Program run\n");
    
    String main_path = "/home/michalis/Desktop/os_delis/os_project_1/tst/" ;
    String input = NULL;
    String config = NULL;
    // Arguments Section

    if(argc==2 || argc==3 || argc==4 || argc==5){
        printf("Args given are %d\n",argc);
        printf("Seems like you given some command line arguments\n");
        if( (strcmp(argv[1], "-i")==0) && (strcmp(argv[3], "-c")==0)  ){
            input = strdup(argv[2]);
            config = strdup(argv[4]);
        }
        else if ( (strcmp(argv[1], "-c")==0) && (strcmp(argv[3], "-i")==0) ){
            input = strdup(argv[4]);
            config = strdup(argv[2]);
        }
        else{
            printf("\033[0;31m");
            printf("Wrong command line arguments.Exiting...\n");
            printf("\033[0m"); 
            exit(1);
        }
    }
    else{
        printf("\033[0;31m");
        printf("No command line arguments given\n");
        printf("\033[0m"); 
        exit(1);
    }

    if( (input != NULL) && (config != NULL) ){
        printf("\033[0;32m");
        printf("INPUT: %s\tCONFIGFILE: %s\n",input,config);
        printf("\033[0m"); 

    }
    // Initial ize input and output file names.
    
    
    
    // Initialize the data structures         
    Map hashTable = map_create(compare_recs,NULL,NULL);
    map_set_hash_function(hashTable, hash_int);
    
    invertedIndex ii = invertedIndex_create();
    if(ii!=NULL) printf("Inverted Index created!\n");
    

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

        //printf("DATA ENTERED : %d %s %s %d %d %.2f\n", id, lastname, firstname, zip, year, gpa);
        r->StudentID = id;
        r->lastName =  strdup(lastname);
        r->firstName = strdup(firstname);
        r->zipNum = zip;
        r->year = year;
        r->gpa = gpa;
        
        // Increase record counter 
        counter++;


        map_insert(hashTable, create_int(r->StudentID) , r);
    }
    int ht_size = map_size(hashTable);
    printf("Hash table size is %d.\n", ht_size);
    // printf("READ %d RECORDS\n",counter);



    // Free allocated memory.
    map_destroy(hashTable);
    invertedIndex_destroy(ii);
    fclose(fptr);
}