#ifndef ENLARGEARRAY_H
#define ENLARGEARRAY_H
#include <stdlib.h>
#define INITIAL_SIZE 5
#define NONE *****
#define offset 0.5

void reallocSarray(IndexElemC* sarray, long* sarray_len);

void reallocFileIndex(IndexElemC* sarray, long* sarray_len, int _id);

#endif // ENLARGEARRAY_H
