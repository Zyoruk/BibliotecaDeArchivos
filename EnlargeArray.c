#include "EnlargeArray.h"

void elargeArray(void *arraytoElarge){
    int arraySais = sizeof(&arraytoElarge);
    int newSais = arraySais + (arraySais * (0.5));
    void *newArray = malloc(newSais);
    arraytoElarge = newArray;
    return arraytoElarge;
}

