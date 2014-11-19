#ifndef USER_H
#define USER_H
#include "SimpleList.h"

class user
{
public:
    user();
    bool CanWrite(char* pFileName);
    bool CanRead(char* pFileName);
    char* getUsername();
    void setUserName(char* pNewName);
    void addToWrite(char* pFileName);
    void addToRead(char* pFileName);

private:
    bool _admin;
    char* _userName;
    SimpleList<char*>* _ReadOnlyDBS;
    SimpleList<char*>* _WriteDBS;
};

#endif // USER_H
