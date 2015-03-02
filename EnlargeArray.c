#include "EnlargeArray.h"

void* elargeIndex(void *arraytoElarge, int var){
    void *newArray = malloc(var * sizeof(struct indexElem));
    newArray = arraytoElarge;
    free(arraytoElarge);
    return newArray;
}

void* elargeArray(void *arraytoElarge, int var){
    void *newArray = malloc(var);
    newArray = arraytoElarge;
    free(arraytoElarge);
    return newArray;
}
