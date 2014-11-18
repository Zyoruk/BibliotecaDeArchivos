#ifndef SIMPLETOARR_H
#define SIMPLETOARR_H
#include "SimpleList.h"
#include "array/array.h"
#include "konstants.h"
template <typename K>
class simpleToArr
{
public:
    simpleToArr();
    array<K>* convertFromSL(SimpleList<K>* pSLToConvert);
    konstants* C;
};

template <typename K>
simpleToArr::simpleToArr(){
    C = new konstants();
}

template <typename K>
array<K>* simpleToArr::convertFromSL(SimpleList<K>* pSLToConvert){
    int lenght = pSLToConvert->getLenght();
    array<K> arrToreturn (lenght);
    if(lenght == C->ZE_ROW) {
        return arrToreturn;
    }

    SimpleListNode<K>* tempH = pSLToConvert->getHead();
    for (int i = C->ZE_ROW ; i < lenght ;i++){
        arrToreturn[i] = *tempH->getElement();
    }
    return arrToreturn;
}

#endif // SIMPLETOARR_H
