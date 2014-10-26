#ifndef RAMPOINTER_H
#define RAMPOINTER_H
#include "interfaces/iPointer.h"

class RAMPointer:public iPointer
{
public:
    RAMPointer();
    void* getPointer();
    void setPointer(void* pPointer);
};

#endif // RAMPOINTER_H
