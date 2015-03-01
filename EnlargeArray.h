#ifndef ENLARGEARRAY_H
#define ENLARGEARRAY_H

struct indexElem {
    int beginning;
    int end;
};

void* elargeArray(void* arraytoElarge, int var);
void* elargeIndex(void *arraytoElarge, int var);

#endif // ENLARGEARRAY_H
