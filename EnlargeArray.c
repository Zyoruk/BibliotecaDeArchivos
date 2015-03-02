#include "EnlargeArray.h"

void* elargeIndex(void *arraytoElarge, int var){
    void *newArray = malloc(var * sizeof(struct indexElem));
<<<<<<< HEAD
    newArray = arraytoElarge;
=======
    for(int i = 0 ; i < (var * sizeof(struct indexElem) ; i++){
        *newArray[i] = *arraytoElarge[i];
    }
    //*newArray = *arraytoElarge;
>>>>>>> e271190a795432802f55188b56460c0683de238f
    free(arraytoElarge);
    return newArray;
}

void* elargeArray(void *arraytoElarge, int var){
    void *newArray = malloc(var);
<<<<<<< HEAD
    newArray = arraytoElarge;
=======
    for(int i = 0 ; i < (var * sizeof(struct indexElem) ; i++){
        *newArray[i] = *arraytoElarge[i];
    }
    //*newArray = *arraytoElarge;
>>>>>>> e271190a795432802f55188b56460c0683de238f
    free(arraytoElarge);
    return newArray;
}

void updateIndex(void *arraytoElarge){
    var = var++;
    arraytoElarge = elargeIndex(arraytoElarge, var);
}

void* reallocateMem(){
    void* indexList;
    if(var == 0){
        indexList = (struct indexElem*) malloc (sizeof(struct indexElem));
        //printf("pointer address = %p\n", indexList);
        indexList = updateArray(indexList);
        //printf("pointer address = %p\n", indexList);
    }else if (var > 0){
        indexList = (struct indexElem*) malloc (var * sizeof(struct indexElem));
        //printf("pointer address = %p\n", indexList);
        indexList = updateArray(indexList);
        //printf("pointer address = %p\n", indexList);
    }else{
        return -1;
    }
}
