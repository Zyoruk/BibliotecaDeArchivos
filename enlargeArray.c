#include "enlargeArray.h"

void reallocSarray(IndexElemC* sarray, long* sarray_len){
    sarray = (IndexElemC*) realloc(sarray, (*sarray_len + (*sarray_len * offset)) * sizeof(IndexElemC*));
    *sarray_len += (*sarray_len * offset);
}

void reallocFileIndex(IndexElemC* sarray, long* sarray_len, int _id){
    int i;
    char c = 'n';
    long var = *sarray_len + (*sarray_len * offset);
    for(i = 0; i < *sarray_len; i++){
        if(sarray[i].id == _id){
            sarray[i].fileIndexArray = (IndexElem*) realloc(sarray, var * sizeof(IndexElem*));
            sarray[i].fileIndexArray_len += (sarray[i].fileIndexArray_len * offset);
            c = 'y';
        }
    }
    printf("%c\n", c);
}
