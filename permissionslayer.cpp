#include "permissionslayer.h"
#include "unistd.h"
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
        return isOpen;
    }
    file.close();
    return isOpen;
}

bool permissionsLayer::checkPass(string pUserName, string pPass){
    string newFileDir ;
    bool isOpen;
    fstream file;
    newFileDir = USERS_DIR;
    newFileDir.append(pUserName);
    file.open(newFileDir.c_str());
    isOpen = file.is_open();
    if (!isOpen){
        cout << INVALID_USERNAME << endl;
        return isOpen;
    }
    string pass ="";
    getline(file, pass);
    if (pass == pPass){
        file.close();
        return true;
    }else{
        cout << INVALID_PASSWORD << endl;
        return false;
    }
}

user permissionsLayer::loadUser(string pUserName){
    if (!checkUser(pUserName)){
        cout << INVALID_USERNAME;
    }
    user tempUser ;
    tempUser.setUserName(pUserName);

    string toAdd= "E";
    string path = " ";
    fstream file;
    //open file that stores read-only
    string RODBS = "read";
    RODBS.append(pUserName);
    path = createNewUser(RODBS);
    file.open(path.c_str());
    file.seekg(ios::beg);
    while(!file.eof()){
        getline(file , toAdd);
        tempUser.addToRead(toAdd);
    }
    file.close();

    //open file that stores write
    string WDBS = "write";
    WDBS.append(pUserName);
    path = createNewUser(WDBS);
    file.open(path.c_str());
    file.seekg(ios::beg);
    while(!file.eof()){
        getline(file , toAdd);
        tempUser.addToWrite(toAdd);
    }
    file.close();

    return tempUser;
}

bool permissionsLayer::createUser(string pUserName , string pPass){
    if (!checkUser(pUserName)){
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
    // hay que borrar los archivos
    if (checkUser(pUserName)){
        string temp = createNewUser(pUserName);
        unlink(temp.c_str());

        string temp2 = "write";
        temp2.append(pUserName);
        temp2 = createNewUser(temp2);
        unlink(temp2.c_str());

        temp2 = "read";
        temp2.append(pUserName);
        temp2 = createNewUser(temp2);
        unlink(temp2.c_str());
        return true;
    }else{
        cout << INVALID_USERNAME;
        return false;
    }
}

bool permissionsLayer::grantPermission(string pUserName , string pNewPermission,
                                       string pFile)
{
    if (!checkUser(pUserName))
    {
        cout << INVALID_USERNAME <<endl;
        return false;
    }else if (!fileExists(pFile))
    {
        cout << NO_EXISTANT_FILE << endl;
        return false;
    }else
    {
        string temp;
        string path;
        if(pNewPermission =="read" || pNewPermission == "write"){
            temp = pNewPermission;
            temp.append(pUserName);
            path = createNewUser(temp);
            fstream file ;
            file.open(path.c_str());
            file.seekg(ZE_ROW , ios::end);
            file << pFile;
            file << "\n";
            return true;
        return false;
        }
    }
}

bool permissionsLayer::revokePermission(string pUserName, string pPermission,
                                        string pFile)
{
    bool toReturn = true;
    if (!checkUser(pUserName))
    {
        cout << INVALID_USERNAME <<endl;
        return !toReturn;
    }else if (!fileExists(pFile))
    {
        cout << NO_EXISTANT_FILE << endl;
        return !toReturn;
    }else
    {
        string temp;
        string path;
        fstream file;
        if(pPermission =="read"){
            temp = pPermission;
            temp.append(pUserName);
            path = createNewUser(temp);

            file.open(path.c_str());
            file.seekg(ios::beg);

            string toCompare = " ";
            while(toCompare != ""){
                int saveSeek = file.tellg();
                getline(file , toCompare);
                if (toCompare == pFile){
                    string temp = "";
                    while (temp.length() != toCompare.length()){
                        temp.push_back('*');
                    }
                    file.seekg(saveSeek);
                    file << temp;
                    return toReturn;
                }
            }
            return !toReturn;

        }else if(pPermission == "write"){
            temp = pPermission;
            temp.append(pUserName);
            path = createNewUser(temp);

            file.open(path.c_str());
            file.seekg(ios::beg);

            string toCompare = " ";
            while(toCompare != ""){
                int saveSeek = file.tellg();
                getline(file , toCompare);
                if (toCompare == pFile){
                    string temp = "";
                    while (temp.length() != toCompare.length()){
                        temp.push_back('*');
                    }
                    file.seekg(saveSeek);
                    file << temp;
                    return toReturn;
                }
            }
            return !toReturn;
        }
        return false;
    }
}

//************************************************

string permissionsLayer::createNewUser(string pNewUser){
    string newUserDir ;
    newUserDir = USERS_DIR;
    newUserDir.append(pNewUser);
    return newUserDir;
}
