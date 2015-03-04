#include "enlargeArray.h"

void reallocFileIndex(void* sarray){
    int len = strlen(sizeof(sarray)/sizeof(sarray[0]));
    int var = len + (len * offset);
    sarray = (void*) realloc(sarray, var * sizeof(sarray[0]));
}
