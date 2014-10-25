#include "rampointer.h"
#include <iostream>

RAMPointer::RAMPointer()
{
    this->_dataAddress = NULL;
}

 void* RAMPointer::getPointer(){
    return this->_dataAddress;
}

 void RAMPointer::setPointer(void* pPointer){
    this->_dataAddress = pPointer;
}
