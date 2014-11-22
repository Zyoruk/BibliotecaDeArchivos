#ifndef DECRIPTOR_H
#define DECRIPTOR_H
#include <string>
#include "SimpleList.h"
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

    array<char*> arrayCharToSL(SimpleList<char*> toConvert);
    array<int> arrayCharToSL(SimpleList<int> toConvert);
    string charToStr(char* pChar);
    int StrToInt (string ToParse);
    void getCreationArguments ();
    void decript ();

    string line;
    string fileName;
    SimpleList<char*> cNames;
    SimpleList<int> cSais;
    int RegSaiz;

};

#endif // DECRIPTOR_H
