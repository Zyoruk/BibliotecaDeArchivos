#include "permissionslayer.h"

permissionsLayer::permissionsLayer()
{
}

bool permissionsLayer::checkUser(string pUserName , string pPass){
    string newFileDir ;
    bool isOpen;
    fstream file;
    newFileDir = USERS_DIR;
    newFileDir.append(pUserName);
    file.open(newFileDir.c_str());
    isOpen = file.is_open();
    if (!isOpen){
        cout << NO_EXISTANT_FILE << endl;
        return false;
    }
    string pass ="";
    getline(file, pass);
    if (pass == pPass){
        file.close();
        return isOpen;
    }
}

user permissionsLayer::loadUser(string pUserName){

}

bool permissionsLayer::createUser(string pUserName , string pPass){
    if (!checkUser(pUserName, pPass)){
        //
        string userPath = createNewUser(pUserName);
        ofstream whatever(userPath.c_str() , ios::trunc);
        whatever << pPass;
        whatever.close();
        return true;
    }else{
        cout << USER_ALREADY_EXISTS << endl;
        return false;
    }
}

bool permissionsLayer::dropUser (string pUserName){

}

bool permissionsLayer::grantPermission(string pUserName , string pNewPermission, string pFile){

}

bool permissionsLayer::revokePermission(string pUserName, string pNewPermission, string pFile){

}

//************************************************

string permissionsLayer::createNewUser(string pNewUser){
    string newUserDir ;
    newUserDir = USERS_DIR;
    newUserDir.append(pNewUser);
    return newUserDir;
}
