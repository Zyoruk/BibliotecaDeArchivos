#ifndef SIMPLELIST_H
#define SIMPLELIST_H
#include "SimpleListNode.h"
#include "iostream"
using namespace std;
const int EMPTY = 0;
const int FIRST_POSITION = 0;
const int NULL_INDEX = -1;
template <typename K>
class SimpleList{
public:
    SimpleList();
    unsigned int getLenght();
    bool append (K pElement);
    bool remove (K pElement);
    bool ifExists (K pElement);
    bool isEmpty();
    bool removeAt (int pIndex);
    bool clear ();
    SimpleListNode<K>* search(K pElement);
    SimpleListNode<K>* getHead();
    SimpleListNode<K>* getTail();
    SimpleListNode<K>* elementAt(int pIndex);
    int indexOf(K pElement);
    bool deleteHead();
    void describe();
    void sort();
    bool operator == (SimpleList<K>* pSLToCompare);
private:
    unsigned int _lenght;
    SimpleListNode<K>* _head;
    SimpleListNode<K>* _tail;
};

template <typename K> SimpleList<K>::SimpleList(){
    this->_head = NULL ;
    this->_lenght= EMPTY;
    this->_tail = NULL;
}


template <typename K>
bool SimpleList<K>::isEmpty(){ return this->_lenght == EMPTY;}

template <typename K>
unsigned int SimpleList<K>::getLenght(){return this->_lenght;}

template <typename K>
SimpleListNode<K>* SimpleList<K>::getHead(){return this->_head;}

template <typename K>
SimpleListNode<K>* SimpleList<K>::getTail(){return this->_tail;}

template <typename K>
SimpleListNode<K>* SimpleList<K>::search(K pElement){
    if (this->isEmpty()){
        return NULL;
    }else{
        SimpleListNode<K>* current = this->_head;
        for ( int i = FIRST_POSITION ; i < this->_lenght ; i++){
            if (*(current->getElement())==pElement){
                return current;
            }else{
                if ( current->getNext() == NULL){
                    return NULL;
                }
                current = current->getNext();
            }
        }
        return NULL;
    }
}

template <typename K>
bool SimpleList<K>::ifExists(K pElement){
    if (this->isEmpty()){
        return false;
    }
    SimpleListNode<K>* current = this->_head;
    for ( int i = FIRST_POSITION; i < this->_lenght ; i++){
        if (*(current->getElement())==pElement){
            return true;
        }else{
            if ( current->getNext() == NULL){
                return false;
            }
            current = current->getNext();
        }
    }
    return false;
}

template <typename K>
bool SimpleList<K>::append(K pElement){
    if (this->isEmpty()){
        SimpleListNode<K>* tmp = new SimpleListNode<K>();
        tmp->setElement(pElement);
        this->_head = tmp;
        this->_tail = this->_head;
        this->_lenght += 1;
        return true;
    }else{
        SimpleListNode<K>* tmp = new SimpleListNode<K>();
        tmp->setElement(pElement);
        this->getTail()->setNext(tmp);
        this->_tail = tmp;
        this->_lenght += 1;
        return true;
    }
}

template <typename K>
bool SimpleList<K>::remove(K pElement){
    if (this->isEmpty()){
        return false;
    }else{
        SimpleListNode<K>* current = this->_head;
        for ( int i = FIRST_POSITION ; i < this->_lenght ; i++){
            if (*(current->getElement())==pElement){
                if (this->_head->getNext() == NULL){
                    this->_head = NULL;
                    this->_lenght -=1;
                    return true;
                }else{
                    this->_head = this->_head->getNext();
                    this->_lenght -=1;
                    return true;
                }
            }else if (current->getNext()->getNext() == NULL){
                if (*(current->getNext()->getElement())==pElement){
                    SimpleListNode<K>* tmp = current->getNext()->getNext();
                    current->getNext()->setNext(NULL);
                    current->setNext(tmp);
                    this->_lenght -=1;
                    return true;
                }
                return false;
            }else{
                if (*(current->getNext()->getElement())==pElement){
                    SimpleListNode<K>* tmp = current->getNext()->getNext();
                    current->getNext()->setNext(NULL);
                    current->setNext(tmp);
                    this->_lenght -=1;
                    this->_tail = tmp;
                    return true;
                }else{
                    current = current->getNext();
                }
            }
        }
        return false;
    }
}

template <typename K>
SimpleListNode<K>* SimpleList<K>::elementAt(int pIndex){
    if (this->isEmpty()){
        return NULL;
    }else if (pIndex > this->_lenght -1){
        return NULL;
    }else{
        SimpleListNode<K>* current = this->_head;
        for ( int i = FIRST_POSITION ; i < this->_lenght ; i++){
            if (i == pIndex){
                return current;
            }else{
                if ( current->getNext() == NULL){
                    return NULL;
                }
                current = current->getNext();
            }
        }
        return NULL;
    }
}

template <typename K>
int SimpleList<K>::indexOf(K pElement){
    if (this->isEmpty()){
        return NULL_INDEX;
    }else{
        SimpleListNode<K>* current = this->_head;
        for ( int i = FIRST_POSITION ; i < this->_lenght ; i++){
            if (*(current->getElement())->compare(pElement)){
                return i;
            }else{
                if ( current->getNext() == NULL){
                    return NULL_INDEX;
                }
                current = current->getNext();
            }
        }
        return NULL_INDEX;
    }
}

template <typename K>
bool SimpleList<K>::removeAt (int pIndex){
    if (this->isEmpty()){
        return false;
    }else if (pIndex == FIRST_POSITION){
        this->deleteHead();
        return true;
    }else{
        if (pIndex >= this->_lenght){            
            return false;
        }
        SimpleListNode<K>* current = this->_head;
        SimpleListNode<K>* previous = NULL;
        int i = FIRST_POSITION;
        while (i != pIndex){
            if  (current->getNext() == NULL ){
                this->_tail = previous;
                current = NULL;
                this->_lenght --;
                return true;
            }
            current = current->getNext();
            previous = current;
        }
        if (current->getNext()->getNext() == NULL){
            this->_tail = previous;
            current = NULL;
            this->_lenght--;
            return true;
        }
        previous->setNext(current->getNext()->getNext());
        current->setElement(NULL);
        current = NULL;
        this->_lenght --;
        return true;
    }
}

template <typename K >
bool SimpleList<K>::clear(){
    while (this->isEmpty() != true){
        this->deleteHead();
    }
    return true;
}

template <typename K>
bool SimpleList<K>::deleteHead(){
    if ( this->isEmpty()){
        return true;
    }else if ( this->getLenght() == 1){
        this->_head = NULL;
        this->_tail = NULL;
        this->_lenght --;
        return true;
    }
    SimpleListNode<K>* temp = this->_head->getNext();
    this->_head = NULL;
    this->_head = temp;
    this->_lenght--;
    return true;
}

template <typename K>
void SimpleList<K>::describe(){
    if (this->isEmpty()){
        cout << "The simple list is empty.\n\n";
    }else{
        cout << "Head: " << *this->_head->getElement() <<"\n"
             << "Tail: " << *this->_tail->getElement() <<"\n";
        SimpleListNode<K>* temp = this->_head;
        for (int i = FIRST_POSITION; i != this->_lenght; i++){
            cout << *temp->getElement() << " ";
            temp = temp->getNext();
        }
           cout << "\n\n";
    }
}

template <typename K>
void SimpleList<K>::sort(){
    K swap;
    for (int i = FIRST_POSITION ; i < ( this->_lenght - 1 ); i++)
      {
        for (int j = FIRST_POSITION ; j < this->_lenght - i - 1; j++)
        {
          if (*this->elementAt(j)->getElement() > (*this->elementAt(j+1)->getElement()))
          {
            swap = *this->elementAt(j)->getElement();
            this->elementAt(j)->setElement(*this->elementAt(j+1)->getElement());
            this->elementAt(j+1)->setElement(swap);
          }
        }
      }
}

/*!
 * /brief Compares two simple list. Two lists are the same only if they have the same size and
 * have its elements in the same order and the same elements.
 * /param receives other simplelist
 * /return boolean
 */
template<typename K>
bool SimpleList<K>::operator ==(SimpleList<K>* pSLToCompare){
    if( this->_lenght == pSLToCompare->getLenght()){
        SimpleListNode<K>* tempHead = this->_head;
        SimpleListNode<K>* tempParamSLHead = pSLToCompare->getHead();
        for (int counter = FIRST_POSITION ; counter <= this->_lenght;counter++){
            if(*tempHead == *tempParamSLHead){
                tempHead = tempHead->getNext();
                tempParamSLHead = tempParamSLHead->getNext();
            }else{
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
}

#endif // SIMPLELIST_H
