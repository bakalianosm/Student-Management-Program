
// this module contains common functions for all the structures.

#include "common_types.h"
#include <stdlib.h>
int compare_recs(Pointer a, Pointer b) {
	return ((Record)a)->StudentID - ((Record)b)->StudentID ;
}

int compare_ints(Pointer a, Pointer b) {
	return *(int*)a - *(int*)b;
}

int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

// char* load_file(char const* path)
// {
//     char* buffer = 0;
//     long length;
//     FILE * f = fopen (path, "rb"); //was "rb"

//     if (f)
//     {
//       fseek (f, 0, SEEK_END);
//       length = ftell (f);
//       fseek (f, 0, SEEK_SET);
//       buffer = (char*)malloc ((length+1)*sizeof(char));
//       if (buffer)
//       {
//         fread (buffer, sizeof(char), length, f);
//       }
//       fclose (f);
//     }
//     buffer[length] = '\0';
//     return buffer;
// }