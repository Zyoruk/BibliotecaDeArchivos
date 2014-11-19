#include "user.h"

user::user()
{
    this->_ReadOnlyDBS = new SimpleList < char* >();
    this->_WriteDBS = new SimpleList < char* >();
    this->_admin = false;
    this->_userName = 0;
}

void user::addToRead(char *pFileName){
    this->_ReadOnlyDBS->append(pFileName);
}

void user::addToWrite(char *pFileName){
    this->_WriteDBS->append(pFileName);
}

bool user::CanRead(char *pFileName){
    if(this->_ReadOnlyDBS->ifExists(pFileName)){
        return true;
    }else{
        return false;
    }
}

bool user::CanWrite(char *pFileName){
    if(this->_WriteDBS->ifExists(pFileName)){
        return true;
    }else{
        return false;
    }
}

char* user::getUsername(){
    return this->_userName;
}

void user::setUserName(char *pNewName){
    this->_userName = pNewName;
}


