#ifndef NODE_H
#define NODE_H
#include "cstddef"
#include "iData.h"
/*!
 * \brief The Node class is the base of all other data structure nodes. The idea is to keep relationship
 * between all the different nodes.
 */
template <typename K>
class interfaceNode {
public:
    interfaceNode();
    virtual ~interfaceNode();
    virtual K* getElement();
    virtual void setElement(K* pElement);
private:
    K _data;
};
template <typename K>
interfaceNode<K>::interfaceNode(){
}

template <typename K>
interfaceNode<K>::~interfaceNode(){}

template <typename K>
void interfaceNode<K>::setElement(K* pElement)
{
    this->_data = *pElement;
}
template <typename K>
K* interfaceNode<K>::getElement(){ return &(this->_data); }



#endif // NODE_H
