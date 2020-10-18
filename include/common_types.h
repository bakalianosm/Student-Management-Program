#pragma once
#include <stdbool.h>

typedef void* Pointer;
typedef char* String;
typedef unsigned int uint;
// Pointer to a function that compares 2 items "a" and "b" and returns the following values:
// < 0 if a < b
// = 0 if a = b 
// > 0  if a > b 
typedef int (*CompareFunc)(Pointer a, Pointer b); 

// Pointer to a function that destroys an element "value"
typedef void (*DestroyFunc)(Pointer value);

// The record that holds each student's info
struct record {
    int StudentID;
    String firstName;
    String lastName;
    int zipNum;
    int year;
    float gpa;
};

typedef struct record* Record;


int* create_int(int value);

int compare_recs(Pointer a, Pointer b);

void rec_destroy_value(Pointer a);

void rec_destroy_key(Pointer a);

bool checkString(char *str, int num);