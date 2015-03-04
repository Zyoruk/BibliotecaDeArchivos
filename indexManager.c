#include <stdio.h>
#include <stdlib.h>
#include "indexManager.h"

struct IndexElemC *sarray = (IndexElemC*) malloc(INITIAL_SIZE * sizeof(IndexElemC*));
long sarray_len = INITIAL_SIZE;

void initializeStructs(IndexElemC* sarray, int* sarray_len){
    int i;
    for (i = 0; i < *sarray_len; i++){
        sarray[i].fileIndexArray = (IndexElem **) malloc(INITIAL_SIZE * sizeof(IndexElem *));
        sarray[i].fileIndexArray_len = INITIAL_SIZE;
    }
}

void closeProgram(IndexElemC* sarray, int* sarray_len){
    int i;
    for (i = 0; i < *sarray_len; i++){
        free(sarray[i].fileIndexArray);
    }
    free(sarray);
}


