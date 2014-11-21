#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "array/array.h"
#include "decriptor.h"

using namespace std;

decriptor::decriptor(string pline, user* pCurrentuser, bool pAdmin) {
    this->currentUser = pCurrentuser;
    this->admin = pAdmin;
    this->FS = new permissionsLayer();
    this->RM = new raidManager();
    this->line = pline;
    this->cNames = array <char*>(BIG_A_SIZE);
    this->cSais = array <int > (BIG_A_SIZE);
    this->RegSaiz = ZE_ROW;
    this->fileName = EMPTY_STRING;
    decript();
}

string decriptor::NextWord() {
    string bhla = EMPTY_STRING;
    int cut = this->line.find(' ');
    bhla = this->line.substr(ZE_ROW, cut);
    this->line =  this->line.substr(cut + ONE_BYTE, this->line.length());
    cout <<bhla<<endl;
    return bhla;
}


string charToStr(char* pChar){
    string toReturn = EMPTY_STRING;
    toReturn.assign(pChar , sizeof(pChar));
    return toReturn;
}


int decriptor::ColNameToIndex(string pName) {
    string ColName = EMPTY_STRING;
    int Index = MINUS_ONE;
    for (int i = ZE_ROW; i < cNames.getLenght(); i++) {
        ColName = charToStr(cNames[i]);
        if (ColName.compare(pName)) {
            Index=i;
            break;
        }
    }
    return Index;
}

int decriptor::StrToInt (string ToParse) {
    int number  = atoi(ToParse.c_str());
    return number;
}

void decriptor::getCreationArguments () {
    string col = EMPTY_STRING;
    int split = ZE_ROW;
    int cut = ZE_ROW;
    int saiz = ZE_ROW;

    cut = this->line.find(SPACE_CHAR);
    while (line != EMPTY_STRING) {
        split = this->line.find(COLON);
        col = this->line.substr(ZE_ROW, split);
        saiz = StrToInt(this->line.substr(split+ONE_BYTE, cut-(split-ONE_BYTE))); //~ substr is not reliable
        this->line = this->line.substr(cut+ONE_BYTE, this->line.length());

        RegSaiz += saiz;
        cNames.insert(ZE_ROW, const_cast<char*>( col.c_str()));
        cSais.insert(ZE_ROW, saiz);
        }
}

void decriptor::decript () {

    string fName = EMPTY_STRING;
    string cName = EMPTY_STRING;
    string uName = EMPTY_STRING;

    string firstWord = NextWord();
    if (firstWord == CREATE) {
        if (this->admin){
            if (NextWord() == TABLE) {
                fileName = NextWord();
                getCreationArguments(); //RegSize, cSais, cNames
                if (NextWord()== USING){
                    if (NextWord()== RAID){
                        int  RAID = this->StrToInt(NextWord());
                        FS->createNewFile(&RegSaiz ,&cSais, &cNames ,&fileName, &RAID);
                    }else{
                        cout << INVALID_COMMAND << endl;
                    }
                } else {
                    int RAID = NOT_RAID;
                    FS->createNewFile(&RegSaiz ,&cSais, &cNames ,&fileName, &RAID);
                }
            }else if (NextWord() == USER) {
                uName = NextWord();
                if (NextWord() == PASSWORD) {
                    FS->createUser(uName, NextWord());
                }else{
                    cout << INVALID_COMMAND << endl;
                }
            }else if (NextWord() == INDEX){
                if (NextWord() == ON){
                    //                fName = NextWord();
                    //                cName = NextWord();
                    cout << NYI << endl;
                }else{
                    cout << INVALID_COMMAND << endl;
                }
            }else{
                cout << INVALID_COMMAND << endl;
            }
        }else{
            cout << INVALID_COMMAND << endl;
        }
    }else if (firstWord == INSERT) {
        if (NextWord() == INTO){
            fName = NextWord();
            if(this->admin){
             //            FS->writeNewLineToFile(&fName, &cData, &cPos);
            }else if (this->currentUser->CanWrite(fName)){
                //            FS->writeNewLineToFile(&fName, &cData, &cPos);
            }else{
                cout << INVALID_COMMAND << endl;
            }
        }else{
            cout << INVALID_COMMAND << endl;
        }
    }else if (firstWord == SELECT) {
        cName = NextWord();
        if (NextWord()== FROM) {
            fName = NextWord();
            if (this->admin || this->currentUser->CanWrite(fName)){
                if (cName == ASTERISC) {
                    //filesystem->readFromFile(&NextWord(), &cNames());
                } else {
                    //filesystem->readFromFile(&fileName , &ColNameToIndex(cName), &ONE_BYTE);
                }
            }else{
                cout << INVALID_COMMAND << endl;
            }
        }else{
            cout << INVALID_COMMAND << endl;
        }
    }else if (firstWord == UPDATE) {
        fName = NextWord();
        if (this->admin || this->currentUser->CanWrite(fName)){
            if (NextWord() == SET) {
                cName = NextWord();
                if (NextWord() == TO) {
                    getCreationArguments();
                    //filesystem->update("&Daniel", &fName, ONE_BYTE , ONE_BYTE);
                }else{
                    cout << INVALID_COMMAND << endl;
                }
            } else{
                cout << INVALID_COMMAND << endl;
            }
        }else{
            cout << INVALID_COMMAND << endl;
        }
    }else if (firstWord == DELETE) {
        if (NextWord() == FROM) {
            fName = NextWord();
            if (this->admin || this->currentUser->CanWrite(fName)){
                cName = NextWord();
                uName = NextWord();
                FS->deleteData(fName , cName , uName);
            }else{
                cout << INVALID_COMMAND << endl;
            }
        }else{
            cout << INVALID_COMMAND << endl;
        }
    }else if (firstWord == COMPRESS){
        if(this->admin){
            if (NextWord() == TABLE){
    //            fName = NextWord();
                cout << NYI << endl;
            }else{
                cout << INVALID_COMMAND <<endl;
            }
        }else{
            cout << INVALID_COMMAND <<endl;
        }
    }else if (firstWord == BACKUP){
        if ( this->admin){
            if (NextWord() == TABLE){
                fName = NextWord();
                FS->backUpFile(NextWord());
            }else{
                cout << INVALID_COMMAND <<endl;
            }
        }else{
            cout << INVALID_COMMAND << endl;
        }
    }else if (firstWord == RESTORE){
        if (this->admin){
            if (NextWord() == TABLE){
                fName = NextWord();
                FS->restoreFile(NextWord());
            }else{
                cout << INVALID_COMMAND <<endl;
            }
        }else{
            cout << INVALID_COMMAND << endl;
        }

    }else if (firstWord == DROP){
        if ( this->admin){
            if (NextWord() == USER) {
                uName = NextWord();
                FS->dropUser(uName);
            }else{
                cout << INVALID_COMMAND <<endl;
            }
        }else{
            cout << INVALID_COMMAND << endl;
        }
    }else if (firstWord == GRANT){
        if ( this->admin){
            string permit = NextWord();
            if (NextWord() == ON) {
                fName = NextWord();
                if (NextWord() == TO) {
                    uName = NextWord();
                    FS->grantPermission(uName, permit, fName);
                }else{
                    cout << INVALID_COMMAND << endl;
                }
            }else{
                cout << INVALID_COMMAND <<endl;
            }
        }else{
            cout << INVALID_COMMAND << endl;
        }
    }else if (firstWord == REVOKE){
        if ( this->admin){
            string permit = NextWord();
            if (NextWord() == ON) {
                fName = NextWord();
                if (NextWord() == TO) {
                    uName = NextWord();
                    FS->revokePermission(uName, permit, fName);
                }else{
                    cout << INVALID_COMMAND << endl;
                }
            }else{
                cout << INVALID_COMMAND << endl;
            }
        }else{
            cout << INVALID_COMMAND << endl;
        }
    }else{
        cout << INVALID_COMMAND << endl;
    }
}

