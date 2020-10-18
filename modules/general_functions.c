
// this module contains common functions for all the structures.

#include "common_types.h"
#include <stdlib.h>
#include <string.h>
int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

int compare_recs(Pointer a, Pointer b) {	
    return ((Record)a)->StudentID - ((Record)b)->StudentID ;
}

void rec_destroy_value(Pointer a){

    free(((Record)a)->firstName);
    free(((Record)a)->lastName);
    free(((Record)a));

}

void rec_destroy_key(Pointer a){
    free((int*)a);
}

bool checkString(String str, int num) {
    int cnt = 0;
    String tok;
    char delim[2] = " ", temp[200];
    strcpy(temp, str);
    tok = strtok(temp, delim);

    while( tok != NULL ) {
        tok = strtok(NULL, delim);
        cnt++;
    }

    if(cnt != num)
        return false;
    
    return true;
}

