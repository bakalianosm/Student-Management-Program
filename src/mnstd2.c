

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_types.h"
#include "general_functions.h"
#include "hash_table.h"
#include "inverted_index.h"
#include "linked_list.h"

#define BUFFER_SIZE 200 


int main(int argc, char* argv[]){
    invertedIndex ii = invertedIndex_create();
    int hash_size;
    Map hashTable;
    if(argc==1){
        printf("\033[1;34m");
        printf("No arguments given , waiting for your command\n");
        printf("\033[0m"); 
        hash_size = 100;
        hashTable = map_create(compare_recs,hash_size,rec_destroy_key,rec_destroy_value);
        map_set_hash_function(hashTable, hash_int);
    }
    else{
        String input = NULL;
        String config = NULL;
        if(argc==5){
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
              
            }
        }
        else if(argc < 5){
            printf("\033[0;31m");
            printf("To few command line arguments given\n");
            printf("\033[0m"); 
           
        }
        else if(argc >5){
            printf("\033[0;31m");
            printf("To many command line arguments given\n");
            printf("\033[0m"); 
           
        }

        if( (input != NULL) && (config != NULL) ){
            printf("\033[1;34m");
            printf("Input file: %s\tConfigfile: %s\n",input,config);
            printf("\033[0m"); 
        }

        FILE *input_fptr , *config_fptr;
        if(input!=NULL) input_fptr = fopen(input,"r");
        if(config!=NULL)config_fptr = fopen(config,"r");

        if(input_fptr == NULL) {
            perror("Error opening input file");
            return(-1);
        }
        else{
            printf("\033[0;32m");
            printf("Input file opened successfully!\n");
            printf("\033[0m");
        }

        if(config_fptr == NULL) {
            perror("Error opening configurationfile");
            return(-1);
        }
        else{
            printf("\033[0;32m");
            printf("Configuration file opened successfully!\n");
            printf("\033[0m");
        }

        char hash_size_str[10];
        fgets(hash_size_str ,10, config_fptr);
        hash_size = atoi(hash_size_str);

        int doublicates = 0;
        int *inID;
        hashTable = map_create(compare_recs,hash_size,rec_destroy_key,rec_destroy_value);
        map_set_hash_function(hashTable, hash_int);
        while(!feof(input_fptr)){
            
            // Initialize some variables 
            
            int id;
            char lastname[20];
            char firstname[20];
            int zip;
            int year;
            float gpa;

            
            // Fill variable's fields with the parsed data
            fscanf(input_fptr, "%d %s %s %d %d %f", &id, lastname, firstname, &zip, &year, &gpa);

            inID = create_int(id);
            MapNode m = map_find_node(hashTable, inID);

            if(m!=MAP_EOF) {
                doublicates+=1 ;
                free(inID);
                continue;
            }
    
            //Initialize Record values 
            Record r = malloc(sizeof(*r)); 
            r->StudentID = id;
            r->lastName =  strdup(lastname);
            r->firstName = strdup(firstname);
            r->zipNum = zip;
            r->year = year;
            r->gpa = gpa;
            
            // And then insert the record inside the Data Structures i made
            map_insert(hashTable, create_int(r->StudentID) , r);
            invertedIndex_insert(ii,r);
            free(inID);
            
            
        }
        printf("%d duplicated records found and not inserted\n",doublicates);
        if(input!=NULL) free(input);
        if(config!=NULL) free(config);
        if(input_fptr!=NULL) fclose(input_fptr);
        if(config_fptr!=NULL) fclose(config_fptr);        
    } //if args != 1

    char str[BUFFER_SIZE];
    
    printf("\033[1;34m");
    printf("\nEnter a command: \n");
    printf("\033[0m"); 
    while(fgets(str, BUFFER_SIZE, stdin) !=0 ){
    if(strcmp("exit\n", str)==0){
        // When the user types "exit" it's time to free the allocated space and exit the program .
       
        map_destroy(hashTable);
        invertedIndex_destroy(ii);
        exit(EXIT_SUCCESS);

    }
    else{

        MapNode m; 
        char ch;
        int *pId; // A pointer to hold the id 
        char option = str[0]; // The type of the instruction 
        int id;

        
        // In this if statement , I execute the querries.
        if (option=='i'){
            bool check = checkString(str,7);
            if(!check){
                printf("\033[0;31m");
                printf("Wrong choice . Try again \n");
                printf("\033[0m");
                continue;
            }
            else{
                
                Record r = malloc(sizeof(*r)); 
                

                char lastname[20];
                char firstname[20];
                int zip;
                int year;
                float gpa;

                sscanf(str, " %c %d %s %s %d %d %f", &ch,&id, lastname,firstname, &zip, &year, &gpa);
                pId = create_int(id);
                
                m  = map_find_node(hashTable, pId);
                if (m==NULL){
                    r->StudentID = id;
                    r->lastName = strdup(lastname);
                    r->firstName = strdup(firstname);
                    r->zipNum = zip;
                    r->year = year;
                    r->gpa = gpa;

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
            }
            free(pId);
        }
        else if(option=='l'){
            bool check = checkString(str,2);
            if(!check){
                printf("\033[0;31m");
                printf("Wrong choice . Try again \n");
                printf("\033[0m"); 
                continue;
            }
            else{
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
                    printf("Student %d does not exists\n", id);
                    printf("\033[0m"); 
                }
                free(pId);
            }
        }
        else if(option=='d'){
            bool check = checkString(str,2);
            if(!check){
                printf("\033[0;31m");
                printf("Wrong choice . Try again \n");
                printf("\033[0m"); 
                continue;
            }
            else{
                sscanf(str, " %c %d ", &ch,&id);
                int year ;
                pId = create_int(id);
                m = map_find_node(hashTable, pId);
                if(m!=NULL) { 
                    Record r = (Record)map_node_value(hashTable, m);
                    year  = r->year;
                }
                else{
                    year = 0 ;
                }
                invertedIndex_delete(ii,id,year);
                if(map_remove(hashTable, pId)) {
                    printf("\033[0;32m");
                    printf("Record %d deleted\n",id);
                    printf("\033[0m"); 
                    
                }
                else{
                    printf("\033[0;31m");
                    printf("Student %d does not exists\n", id);
                    printf("\033[0m"); 
                } 
                free(pId);
            }
        }
        else if(option=='n'){
            bool check = checkString(str,2);
                if(!check){
                printf("\033[0;31m");
                printf("Wrong choice . Try again \n");
                printf("\033[0m"); 
                continue;
            }
            else{
                int year;
                sscanf(str, " %c %d ", &ch,&year);
                int count = invertedIndex_yearCount(ii,year);
                printf("\033[0;32m");
                count>0 ? printf("%d students in %d\n",count,year) : printf("NO students enrolled in %d\n",year);           
                printf("\033[0m"); 
            }
        }
        else if(option=='t'){
            bool check = checkString(str,3);
            if(!check){
                printf("\033[0;31m");
                printf("Wrong choice . Try again \n");
                printf("\033[0m"); 
                continue;
            }
            else{
                int num, year;
                sscanf(str, " %c %d %d", &ch,&num, &year);
                printf("\033[0;32m");   
                invertedIndex_topNstudents(ii,num,year);
                printf("\033[0m");
            }

        }
        else if(option=='a'){
            bool check = checkString(str,2);
            if(!check){
                printf("\033[0;31m");
                printf("Wrong choice . Try again \n");
                printf("\033[0m"); 
                continue;
            }
            else{
                int year;
                sscanf(str, " %c %d", &ch, &year);
                invertedIndex_averageYear(ii, year);
            }
        }
        else if(option=='m'){
            bool check = checkString(str,2);
            if(!check){
                printf("\033[0;31m");
                printf("Wrong choice . Try again \n");
                printf("\033[0m"); 
                continue;
            }
            else{
                int year;
                sscanf(str, " %c %d", &ch, &year);
                invertedIndex_minimumYear(ii, year);
            }
        }
        else if(option=='c'){
            bool check = checkString(str,1);
            if(!check){
                printf("\033[0;31m");
                printf("Wrong choice . Try again \n");
                printf("\033[0m"); 
                continue;
            }
            else{
                printf("\033[0;32m");
                invertedIndex_count(ii);
                printf("\033[0m"); 
                printf("\n");
            }
        }
        else if(option=='p'){
            bool check = checkString(str,2);
            if(!check){
                printf("\033[0;31m");
                printf("Wrong choice . Try again \n");
                printf("\033[0m"); 
                continue;
            }
            else{
                
                
            }
        }
        else{
            printf("\033[1;31m");
            printf("Command not found\n");
            printf("\033[0m"); 
        }
    }    
}

}

