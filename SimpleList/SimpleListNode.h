#ifndef SIMPLELISTNODE_H
#define SIMPLELISTNODE_H
#include "interfaces/interfaceNode.h"
#include "interfaces/iData.h"
/*!
 * \brief The SimpleListNode class. A simple list node is the corresponding node to the data structure
 * "simple linked list".
 */
template <typename K>
class SimpleListNode: public interfaceNode<K>{
public:
    /*!
     * \brief SimpleListNode is the constructor
     */
    SimpleListNode();
    virtual ~SimpleListNode();
    /*!
     * \brief setElement function that sets the element of the node
     * \param pElement the element that is going to be set
     */
    void setElement(K pElement);
    /*!
     * \brief getElement
     * \return the element that contains the node.
     */
    K* getElement();
    /*!
     * \brief setNext
     * \param pNextNode
     */
    void setNext(SimpleListNode<K>* pNextNode);
    /*!
     * \brief getNext
     * \return
     */
    SimpleListNode<K>* getNext();
    /*!
     * \brief setPrevious
     * \param pPreviousNode
     */
    void setPrevious(SimpleListNode<K>* pPreviousNode);
    /*!
     * \brief getPrevious
     * \return
     */
    SimpleListNode<K>* getPrevious();

    bool operator == (SimpleListNode<K> pSLNodeToCompare);
private:
    /*!
     * \brief _next this is a pointer to a node that is said is next to the current one
     */

    interfaceNode<K>* _next ;
    /*!
     * \brief _previous pointer to the node is said is before the current one
     */
    interfaceNode<K>* _previous;
    bool compare(K pElement);
};

template <typename K>
SimpleListNode<K>::SimpleListNode() {
    this->_next = NULL;
}

template <typename K>
SimpleListNode<K>::~SimpleListNode() {
}
template <typename K>
void SimpleListNode<K>::setElement(K pElement){interfaceNode<K>::setElement(&pElement);}

template <typename K>
K* SimpleListNode<K>::getElement(){return interfaceNode<K>::getElement();}

template <typename K>
void SimpleListNode<K>::setNext(SimpleListNode<K> *pNextNode){this->_next = pNextNode;}

template <typename K>
SimpleListNode<K>* SimpleListNode<K>::getNext(){return (SimpleListNode<K>*)this->_next;}

template <typename K>
void SimpleListNode<K>::setPrevious(SimpleListNode<K>* pNextNode){this->_next = pNextNode;}

template <typename K>
SimpleListNode<K>* SimpleListNode<K>::getPrevious(){return (SimpleListNode<K>*)this->_previous;}

template <typename K>
bool SimpleListNode<K>::operator == (SimpleListNode<K> pSLNodeToCompare){
    if (*this->getElement() == *pSLNodeToCompare.getElement()){
        return true;
    }else{
        return false;
    }
}

#endif // SIMPLELISTNODE_H
