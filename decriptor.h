#ifndef DECRIPTOR_H
#define DECRIPTOR_H
#include <string>
#include "SimpleList.h"
#include "array/array.h"
#include "permissionslayer.h"
#include "raidManager/raidmanager.h"
#include "user.h"

using namespace std;

class decriptor
{
public:
    decriptor(string pline, user* pCurrentuser, bool pRoot, bool pServer );

private:
    //user
    user * currentUser;
    bool root ;
    bool isServer;
    //file system
    permissionsLayer* FS;
    raidManager* RM;
    string line;
    string fileName;
    SimpleList<char*> pNames;
    SimpleList<char*> cNames;
    SimpleList<char*> cValius;
    SimpleList<int> cSais;
    int RegSaiz;

    //Get the next word of the string??
    string NextWord();

    //???
    int ColNameToIndex(string pName);

    array<char*> arrayCharToSL(SimpleList<char*> toConvert);
    array<int> arrayCharToSL(SimpleList<int> toConvert);
    string charToStr(char* pChar);
    int StrToInt (string ToParse);
    void getCreationArguments ();
    void getValuedArguments ();
    void getArguments();
    void decript ();
    void askForValidCommand();
};

#endif // DECRIPTOR_H
