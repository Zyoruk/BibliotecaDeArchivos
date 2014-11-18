#ifndef ARRAY_H
#define ARRAY_H
#include <stdlib.h>
#include <assert.h>
#include <iostream>
using namespace std;
const int EMPTY = 0;
const int FIRST_POSITION = 0;
template <typename K>
class array{
public:
    array (int pLenght);
    array();
    ~array();
    void insert(int pIndex , K pElement);
    void removeElementAt(int pIndex);
    void removeElement(K pElement);
    void removeAllOcurrencesOf(K pElement);
    void setArrayBuffer(K* pArrayBuffer);
    int getLenght();
    bool operator== (array<K>& newArray);
    array<K>& operator= (array<K>& newArray);
    array<K> operator= (array<K> newArray);
    const K& operator[](int pIndex) const;
    K& operator[](int pIndex);
private:
    K* _arrayBuffer;
    int _lenght,  _currentLenght;
    void resize();
};

template <typename K>
array<K>::array(int pLenght){
    //this->_arrayBuffer = new T[pLenght];
    this->_arrayBuffer = (K*)calloc(pLenght, sizeof(K));
    this->_lenght = pLenght;
    this->_currentLenght = EMPTY;
}

template <typename K>
array<K>::array(){
    //this->_arrayBuffer = new T[pLenght];
    this->_arrayBuffer = EMPTY;
    this->_lenght = EMPTY;
    this->_currentLenght = EMPTY;
}

template<typename K>
array<K>::~array(){
}

template <typename K>
int array<K>::getLenght(){
    return this->_lenght;
}

template <typename K>
void array<K>::setArrayBuffer(K *pArrayBuffer){
    this->_arrayBuffer = pArrayBuffer;
}

template<typename K>
void array<K>::insert(int pIndex, K pElement){
    //If the array is full ,then we will resize it.
    if (_currentLenght +1 > this->_lenght) resize();
    //Moving from the back of the array to the index where we want to add(Moving the elements).
    for (int counter = this->_currentLenght; counter >pIndex ; counter--){
        this->_arrayBuffer[counter] = this->_arrayBuffer[counter-1];
    }
    this->_arrayBuffer[pIndex] = pElement;
    this->_currentLenght++;
}
template <typename K>
void array<K>::removeElementAt(int pIndex){
    *(this->_arrayBuffer + pIndex)  = 0;
}

/*!
 * /brief removes the first ocurrence
 */
template <typename K>
void array<K>::removeElement(K pElement){
    for (int counter = FIRST_POSITION; counter < this->_lenght;counter++){
        if ( *(this->_arrayBuffer + counter) == pElement){
            removeElementAt(counter);
            break;
        }
    }
}

template <typename K>
void array<K>::removeAllOcurrencesOf(K pElement){
    for (int counter = FIRST_POSITION; counter < this->_lenght;counter++){
        if ( *(this->_arrayBuffer + counter) == pElement){
            this->removeElementAt(counter);
        }
    }
}

/*###################################### OPERATOR OVERLOAD #################################################################**/
//In order to work with normals assignments
template<typename K>
K& array<K>::operator[](int pIndex){

    if (pIndex < FIRST_POSITION || pIndex >= this->_lenght) {
        cout << "Invalid Index\n";
    }
    return *(_arrayBuffer + pIndex);
}

//In order to work with constant objects
template<typename K>
const K& array<K>::operator[](int pIndex) const{
    if (pIndex < FIRST_POSITION || pIndex >= this->_lenght){
        cout << "Invalid Index\n";
    }else{
        return *(_arrayBuffer + pIndex);
    }
}

//Method that let us replace arrays.
template <typename K>
array<K>& array<K>::operator= (array<K>& newArray){
    //if (this->_arrayBuffer != NULL) delete[] this->_arrayBuffer;
    if (this->_arrayBuffer != NULL) free(_arrayBuffer);
    this->_arrayBuffer = newArray._arrayBuffer;
    this->_lenght = newArray._lenght;
    return *this;
}

template <typename K>
array<K> array<K>::operator= (array<K> newArray){
    //if (this->_arrayBuffer != NULL) delete[] this->_arrayBuffer;
    if (this->_arrayBuffer != NULL) free(_arrayBuffer);
    this->_arrayBuffer = newArray._arrayBuffer;
    this->_lenght = newArray._lenght;
    return *this;
}

template <typename K>
bool array<K>::operator== (array<K>& pArrToCompare){
    //Check if both have the same size.
    if ( this->_lenght != pArrToCompare._lenght){
        return false;

    }else{
        //If they have the same size, then iterate searching for a difference
        for (int counter = FIRST_POSITION; counter < this->_lenght ; counter++){
            //If found a difference, then return false.
            if(*(this->_arrayBuffer+counter )!= pArrToCompare[counter]){
                return false;
            }
        }
        return true;
    }
}

#endif // ARRAY_H
