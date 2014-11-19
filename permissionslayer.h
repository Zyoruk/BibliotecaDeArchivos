#ifndef PERMISSIONSLAYER_H
#define PERMISSIONSLAYER_H

#include "fsqlserverfilesystem.h"
#include "user.h"
class permissionsLayer: public FSQLServerFileSystem
{
public:
    permissionsLayer();
    bool checkUser(string pUserName);
    user loadUser(string pUserName);
    bool createUser(string pUserName , string pPass);
    bool dropUser (string pUserName);
    bool grantPermission(string pUserName , string pNewPermission, string pFile);
    bool revokePermission(string pUserName, string pNewPermission, string pFile);
private:
    string createNewUser(string pNewUser);
};

#endif // PERMISSIONSLAYER_H
