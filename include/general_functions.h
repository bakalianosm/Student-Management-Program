#pragma once
#include <string.h>
#include "common_types.h"


// Creates a pointer to integer with "value" value
int* create_int(int value) ;

// Compare function for records 
int compare_recs(Pointer a, Pointer b) ;

// Frees / Dalllocates the rec value (for Hash Table)
void rec_destroy_value(Pointer a);

// Frees / Dalllocates the rec key (for Hash Table)
void rec_destroy_key(Pointer a);

// Takes a string str and  checks if has "num" words
bool checkString(String str, int num);
