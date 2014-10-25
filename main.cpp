#include <iostream>
#include <fstream>
#include "konstants.h"
#include <limits>
#include <vector>
#include <cstdlib>
//#define STR(x) #x << '=' << x

using namespace std;

konstants* K;
int option;
string data;
string newFileName;
void setup()
{
    K = new konstants();
}

fstream& createNewFile(string newFileName){
    string newFileDir = K->dirFile;
    newFileDir.append(newFileName);
    cout << newFileDir << endl;
    ofstream database (newFileDir.c_str() , ios::trunc);
    if(database.is_open())
        cout << "****Database succesfully created***" << endl;
    else
        cout << "****Database could not be created***" << endl;
    return &database;
}

 void createTable(string &ColumnNames, int &ColumnSizes){
     cout << "****Name for new table***" << endl;
     cin >> newFileName;
     ofstream* database = createNewFile(newFileName);
 }

void updateField(){
    ofstream file (K->dirFile.c_str() , ios::app);
    if(data.size() <= 64){

    }
    file.close();
}

int& stringToInt(string* pStr){
    int i = atoi(pStr);
    return &i;
}

string& charCallocToString(char* pCharCalloc){
    string stringToReturn = "";
    for (int i = NULL; i <= K->THREE_BYTES;i++){
        stringToReturn.append(*(pCharCalloc + i));
    }
    return &stringToReturn;
}

int& getRegisterSize(ifstream* pFile){
    pFile->seekg(K->FOUR_BYTES);
    char* charString = calloc(3 ,1);
    pFile->read(charString, K->THREE_BYTES);
    string* regSizeString = charCallocToString(charString);
    int* regSize  = stringToInt(regSizeString);
    return regSize;
}

int& columnSize(ifstream* pFile , int pColumnInt){
    pFile->seekg((K->FOUR_BYTES + K->THREE_BYTES) + ((pColumnInt - K->ONE_BYTE) * K->THREE_BYTES)); //Move the seek to the beginning of the column.
    char* charString = calloc(K->THREE_BYTES, K->ONE_BYTE);
    pFile->read(charString , K->THREE_BYTES);
    string cSize = K->EMPTY_STRING;
    // build the string;
    for (int i = 0; i <= 3;i++){
        cSize.append(*(charString + i));
    }
    int* cSizeInt = stringToInt(&cSize);
    return cSizeInt;
}

int& sizeUntilColumn(int pColumn){
    int sizeToReturn = NULL;
    for (int i = NULL; i < pColumn; i++){
        sizeToReturn = (sizeToReturn)+ *columnSize(i);
    }
    return &sizeToReturn;
}

string& readField(string* pFile , int pRow , int Column){
    //Relative route + the name of the file
    string fileToRead = K->dirFile;
    fileToRead.append(pFile);
    ifstream file (fileToRead.c_str());


    //Move seek to the row
    file.seekg((*getRegisterSize())*pRow);

    //move seek to the beginning of the column
    int sizeToColumn = *sizeUntilColumn(Column);
    file.seekg(sizeToColumn);

    //Read the info
    int cSize = *columnSize(Column);

    char* infoInsideColumn = calloc(cSize, sizeof(char));
    file.read(infoInsideColumn , cSize);

    //build the stringto return
    string* stringToReturn = charCallocToString(infoInsideColumn);
    return stringToReturn;
}

int main()
{
//    setup();
//    cout << "****Field operations***" << endl;
//    cout << "****1. Edit ****" << endl;
//    cout << "****2. Read ****" << endl;

//    cin >> option;
//    switch (option) {
//        case 1:
//        {
//            updateField();
//            break;
//        }
//        case 2:
//        {
//            readField();
//            break;
//        }
//        default:
//        {
//            cout << "The cat said miau...\n";
//            break;
//}
//    }

    return 0;
}

