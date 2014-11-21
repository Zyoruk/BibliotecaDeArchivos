#include "user.h"

user::user()
{
    this->_ReadOnlyDBS = new SimpleList < char* >();
    this->_WriteDBS = new SimpleList < char* >();
    this->_userName = "";
}

void user::addToRead(string pFileName){
    this->_ReadOnlyDBS->append(const_cast<char *>(pFileName.c_str()));
}

void user::addToWrite(string pFileName){
    this->_WriteDBS->append(const_cast<char *>(pFileName.c_str()));
}

bool user::CanRead(string pFileName){
    if(this->_ReadOnlyDBS->ifExists(const_cast<char *>(pFileName.c_str()))){
        return true;
    }else{
        return false;
    }
}

bool user::CanWrite(string pFileName){
    char* temp = const_cast<char *>(pFileName.c_str());
    if(this->_WriteDBS->ifExists(temp)){
        return true;
    }else{
        return false;
    }
}

string user::getUsername(){
    return this->_userName;
}

void user::setUserName(string pNewName){
    this->_userName = pNewName;
}


