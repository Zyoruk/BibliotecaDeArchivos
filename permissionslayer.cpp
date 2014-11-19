#include "permissionslayer.h"

permissionsLayer::permissionsLayer()
{
}

bool permissionsLayer::checkUser(string pUserName){
    string newFileDir ;
    bool isOpen;
    fstream file;
    newFileDir = USERS_DIR;
    newFileDir.append(pUserName);
    file.open(newFileDir.c_str());
    isOpen = file.is_open();
    if (!isOpen){
        cout << NO_EXISTANT_FILE << endl;
        return isOpen;
    }
    file.close();
    return isOpen;
}

bool checkPass(string pUserName, string pPass){
    string newFileDir ;
    bool isOpen;
    fstream file;
    newFileDir = USERS_DIR;
    newFileDir.append(pUserName);
    file.open(newFileDir.c_str());
    isOpen = file.is_open();
    if (!isOpen){
        cout << NO_EXISTANT_FILE << endl;
        return isOpen;
    }
    string pass ="";
    getline(file, pass);
    if (pass == pPass){
        file.close();
        return isOpen;
    }else{
        cout << INVALID_PASSWORD << endl;
    }
}

user permissionsLayer::loadUser(string pUserName){
    if (!checkUser(pUserName)){
        cout << INVALID_USERNAME;
    }
    user tempUser ;
}

bool permissionsLayer::createUser(string pUserName , string pPass){
    if (!checkUser(pUserName, pPass)){
        //create file with pass
        string path = createNewUser(pUserName);
        ofstream whatever(path.c_str() , ios::trunc);
        whatever << pPass;
        whatever.close();

        //create file to store read-only
        string RODBS = "read";
        RODBS.append(pUserName);
        path = createNewUser(RODBS);
        ofstream whatever2 (path.c_str() , ios::trunc);
        whatever2.close();

        //create file to store write files
        string WDBS = "write";
        WDBS.append(pUserName);
        path = createNewUser(WDBS);
        ofstream whatever3 (path.c_str() , ios::trunc);
        whatever3.close();
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
