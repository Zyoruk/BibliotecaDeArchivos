#include <stdio.h>
#include <stdlib.h>
#include "indexManager.h"

void initializeStructs(IndexElemC* sarray, long* sarray_len){
    int i;
    for (i = 0; i < *sarray_len; i++){
        sarray[i].fileIndexArray = (IndexElem **) malloc(INITIAL_SIZE * sizeof(IndexElem *));
        sarray[i].fileIndexArray_len = INITIAL_SIZE;
    }
}

void start(){
    struct IndexElemC *sarray = (IndexElemC*) malloc(INITIAL_SIZE * sizeof(IndexElemC*));
    long sarray_len = INITIAL_SIZE;
    initializeStructs(sarray, &sarray_len);
}
