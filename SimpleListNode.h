#ifndef SIMPLELISTNODE_H
#define SIMPLELISTNODE_H
#include "src/dataStructures/interfaceNode.h"
/*!
 * \brief The SimpleListNode class. A simple list node is the corresponding node to the data structure
 * "simple linked list".
 */
template <typename K>
class SimpleListNode: public interfaceNode<K> {
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
private:
    /*!
     * \brief _next this is a pointer to a node that is said is next to the current one
     */

    interfaceNode<K>* _next ;
    /*!
     * \brief _previous pointer to the node is said is before the current one
     */
    interfaceNode<K>* _previous;
};

template <typename K>
SimpleListNode<K>::SimpleListNode() {
    this->_next = 0;
    this->_element = 0;
}

template <typename K>
SimpleListNode<K>::~SimpleListNode() {
}
template <typename K>
void SimpleListNode<K>::setElement(K pElement){this->_element = pElement;}

template <typename K>
K* SimpleListNode<K>::getElement(){return &(this->_element);}

template <typename K>
void SimpleListNode<K>::setNext(SimpleListNode<K> *pNextNode){this->_next = pNextNode;}

template <typename K>
SimpleListNode<K>* SimpleListNode<K>::getNext(){return (SimpleListNode<K>*)this->_next;}

template <typename K>
void SimpleListNode<K>::setPrevious(SimpleListNode<K>* pNextNode){this->_next = pNextNode;}

template <typename K>
SimpleListNode<K>* SimpleListNode<K>::getPrevious(){return (SimpleListNode<K>*)this->_previous;}


#endif // SIMPLELISTNODE_H
