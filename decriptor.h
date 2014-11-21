#ifndef DECRIPTOR_H
#define DECRIPTOR_H
#include <string>
#include "array/array.h"
#include "permissionslayer.h"
#include "raidManager/raidmanager.h"
#include "user.h";
using namespace std;

class decriptor
{
public:
    decriptor(string pline, user* pCurrentuser, bool pAdmin );

private:
    //user
    user * currentUser;
    bool admin ;
    //file system
    permissionsLayer* FS;
    raidManager* RM;
    //Get the next word of the string??
    string NextWord();

    //???
    int ColNameToIndex(string pName);


    int StrToInt (string ToParse);
    void getCreationArguments ();
    void decript ();

    string line;
    string fileName;
    array<char*> cNames;
    array<int> cSais;
    int RegSaiz;

};

#endif // DECRIPTOR_H
