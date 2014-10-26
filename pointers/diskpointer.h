#ifndef DISKPOINTER_H
#define DISKPOINTER_H
#include <iostream>
using namespace std;
class DiskPointer
{
public:
    DiskPointer();
private:
    int _seek;
    string _file;
};

#endif // DISKPOINTER_H
