
// this module contains common functions for all the structures.

#include "general_functions.h"
#include "common_types.h"
#include <stdlib.h>

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

bool checkString(char *str, int num) {
    int counter = 0;
    char *token;
    char s[2] = " ";
    char temp[100];
    strcpy(temp, str);
    token = strtok(temp, s);
    /* walk through other tokens */
    while( token != NULL ) {
        token = strtok(NULL, s);
        counter+=1;
    }
    printf("%d\n", counter);
    if(counter != num)
        return false;
    return true;
}