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

// a function that compares ints 
int compare_recs(Pointer a, Pointer b);

// a function that compares records by year.
int compare_year(Pointer a, Pointer b);

// char* load_file(char const* path);


