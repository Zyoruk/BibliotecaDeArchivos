#ifndef IDATA_H
#define IDATA_H
using namespace std;
template <typename K>
class iData{
public :
    iData();
    void setData(K pData);
    K* getData();
    bool compare (K pElement);
    bool lessThan(K pElement);
    bool moreThan(K pElement);
protected:
    K _data;
};
template <typename K>
iData<K>::iData(){
    this->_data = 0;
}

template <typename K>
void iData<K>::setData(K pData){
    this->_data = pData;
}

template <typename K>
K* iData<K>::getData(){
    return &this->_data;
}

template <typename K>
bool iData<K>::compare (K pElement){return *_data == pElement;}
template <typename K>
bool iData<K>::lessThan (K pElement){return *_data < pElement;}
template <typename K>
bool iData<K>::moreThan (K pElement){return *_data > pElement;}
#endif // IDATA_H
