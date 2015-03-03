#include <stdio.h>
#include <stdlib.h>
#define INITIAL_SIZE 5
#define NONE *****
#define offset 0.5

//Beg-End of component
typedef struct {
    int beginning;
    int end;
    char used = 'n';
}IndexElem;

//Element of Indexes list
typedef struct {
    struct indexElem* fileIndexArray; //doble puntero
    long fileIndexArray_len;
    int id;
}IndexElemC;

void initializeStructs(IndexElemC* sarray, int *sarray_len);

void closeProgram(IndexElemC* sarray, int* sarray_len);
