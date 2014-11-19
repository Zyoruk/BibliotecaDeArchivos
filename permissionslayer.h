#ifndef PERMISSIONSLAYER_H
#define PERMISSIONSLAYER_H

#include "fsqlserverfilesystem.h"
#include "user.h"
class permissionsLayer: public FSQLServerFileSystem
{
public:
    permissionsLayer();
    bool checkUser(char* pUserName , char* pPass);
    user loadUser(char* pUserName);
    bool createUser(char* pUserName , char* pPass);
    bool dropUser (char* pUserName);
    bool grantPermission(char* pUserName , char* pNewPermission, char* pFile);
    bool revokePermission(char* pUserName, char* pNewPermission, char* pFile);
};

#endif // PERMISSIONSLAYER_H
