
#include "common_types.h"
#include "hash_table.h"
#include "inverted_index.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 200 
#define YEAR_LIMIT 8 
int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

int compare_recs(Pointer a, Pointer b) {	return ((Record)a)->StudentID - ((Record)b)->StudentID ;
}

void rec_destroy_value(Pointer a){

    free(((Record)a)->firstName);
    free(((Record)a)->lastName);
    free(((Record)a));

}


void rec_destroy_key(Pointer a){
    free((int*)a);
}

int main(int argc, char* argv[]){
    printf("Program run\n");
    

    // Fetch the current year that running the program 

    // time_t s; //, val = 1;
    // struct tm* current_time;
    
    // s = time(NULL);
    
    // current_time = localtime(&s);
    
    // printf("Current year = %d\n",(current_time->tm_year + 1900));


    // String main_path = "/home/michalis/Desktop/os_delis/os_project_1/tst/" ;
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
    // Initialize input and output file names.
    
    
    
    // Initialize the data structures         
    Map hashTable = map_create(compare_recs,rec_destroy_key,rec_destroy_value);
    map_set_hash_function(hashTable, hash_int);
    
    invertedIndex ii = invertedIndex_create();
    // if(ii!=NULL) printf("Inverted Index created!\n");


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
        float gpa;


        fscanf(fptr, "%d %s %s %d %d %f", &id, lastname, firstname, &zip, &year, &gpa);

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
        invertedIndex_insert(ii,r);
    }


    // printf("Now it's your choice to interract with this system\n");
    
    char str[BUFFER_SIZE];

    while(fgets(str, BUFFER_SIZE, stdin)!=0){
        if(strcmp("exit", str)==0){
            printf("Choosen option is EXIT\n");
            exit(0);
        }
        else{
            MapNode m;
            char ch;
            int *pId;
            char option = str[0];
            int id;
            // int year;
            // printf("you given this input : %s\n",str);
            if (option=='i'){
                printf("selected option is INSERTION\n");
                printf("%s", str);
                // char ch ;
                // Initialize the record to insert

                Record r = malloc(sizeof(*r)); 
                

                char lastname[20];
                char firstname[20];
                int zip;
                int year;
                float gpa;

                //printf("string is %s\n",str);
                sscanf(str, " %c %d %s %s %d %d %f", &ch,&id, lastname,firstname, &zip, &year, &gpa);

                //printf("specs are %c %d %s %s %d %d %.1f \n", ch,id,lastname,firstname,zip,year,gpa);
                // i 1700269 bakalianos michail 15772 2017 6.2
                // int* pId = create_int(id);
                pId = create_int(id);
                // MapNode m  = map_find_node(hashTable, pId);
                m  = map_find_node(hashTable, pId);
                if (m==NULL){
                    r->StudentID = id;
                    r->lastName = strdup(lastname);
                    r->firstName = strdup(firstname);
                    r->zipNum = zip;
                    r->year = year;
                    r->gpa = gpa;
                    //printf("RECORD :  %d %s %s %d %d %.1f\n",r->StudentID,r->firstName,r->lastName,r->zipNum,r->year,r->gpa);

                    map_insert(hashTable, create_int(r->StudentID) , r);
                    invertedIndex_insert(ii,r);
                    
                    printf("\033[0;32m");
                    printf("Student %d inserted\n",id);
                    printf("\033[0m"); 
                }
                else{
                    printf("\033[0;31m");
                    printf("Student %d exists\n", id);
                    printf("\033[0m"); 
                    
                }
                free(pId);
            }
            else if(option=='l'){
                printf("selected option is LOOKUP\n");
                printf("%s", str);
                sscanf(str, " %c %d ", &ch,&id);
                pId = create_int(id);

                m = map_find_node(hashTable, pId);
                if(m!=NULL){
                    Record r = (Record)map_node_value(hashTable, m);
                    printf("\033[0;32m");
                    printf("%d %s %s %d %d %.1f\n",r->StudentID,r->firstName,r->lastName,r->zipNum,r->year,r->gpa);
                    printf("\033[0m"); 
                }
                else{
                    printf("\033[0;31m");
                    printf("Student %d does exists\n", id);
                    printf("\033[0m"); 
                }

                free(pId);
            }
            else if(option=='d'){
                printf("selected option is DELETE\n");
                // printf("%s", str);
                sscanf(str, " %c %d ", &ch,&id);
                pId = create_int(id);
                if(map_remove(hashTable, pId)) {
                    // invertedIndex_delete(ii,rec);
                    printf("inverted index size is %d\n", invertedIndex_size(ii));
                    printf("Hash size is %d\n", map_size(hashTable));
                    printf("\033[0;32m");
                    printf("Record %d deleted\n",id);
                    printf("\033[0m"); 
                }
                else{
                    printf("\033[0;31m");
                    printf("Student %d does exists\n", id);
                    printf("\033[0m"); 
                } 
                free(pId);

            }
            else if(option=='n'){
                int year;
                printf("Selected option is number year\n");
                sscanf(str, " %c %d ", &ch,&year);

                printf("\033[0;32m");
                printf("%d students in %d\n",invertedIndex_yearCount(ii,year),year);
                printf("\033[0m"); 

            }
            else if(option=='t'){

            }
            else if(option=='a'){

            }
            else if(option=='m'){

            }
            else if(option=='c'){
                printf("selected option is COUNT\n");
                printf("%s", str);
                sscanf(str, " %c", &ch);
                printf("\033[0;31m");
                invertedIndex_count(ii);
                printf("\033[0m"); 
                printf("\n");

            }
            else if(option=='p'){

            }
            else{
                printf("\033[1;31m");
                printf("Command not found\n");
                printf("\033[0m"); 
                exit(0);
            }
            
            
            
            
            
            // if(pId!=NULL) free(pId);
                    

        }

    // switch()
    }
    // Free allocated memory.

    //printf(" STRUCT SIZE IS : %d", map_size(hashTable));
    free(input);
    free(config);
    map_destroy(hashTable);
    invertedIndex_destroy(ii);
    fclose(fptr);
    
}