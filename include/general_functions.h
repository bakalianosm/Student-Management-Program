#pragma once
#include <string.h>
#include "common_types.h"

int* create_int(int value) ;


int compare_recs(Pointer a, Pointer b) ;


void rec_destroy_value(Pointer a);


void rec_destroy_key(Pointer a);


bool checkString(char *str, int num);