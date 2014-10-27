#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "konstants.h"
#include "array/array.h"

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

string toChar(int toChar){
    string s;
    stringstream out;
    out << toChar;
    s = out.str();
    return s;
}

void checkSize(string* add, int count){
    string hola = "0";
    string tmp;

    for (int a = 1 ; a < count ; a++){
        if((tmp.length() + add->length()) == count){
            break;
        }
        tmp.append(hola);
    }
    tmp.append(*add);
    *add = tmp;
}

string intToChar(int metadata){
    int ch;
    string tmp ;
    while (metadata != 0){
        ch = metadata % 10;
        metadata = metadata / 10;
        tmp.append(toChar(ch));
    }
    return tmp;
}

string createNewFile(string newFileName){
    string newFileDir ;
    newFileDir = K->DIRFILE;
    newFileDir.append(newFileName);
    //cout << newFileDir << endl;
    return newFileDir;
}

void createTable(int* registerSize, array<int>* columnSizes){
    int offset = 0;
    cout << "**** Insert name for new table ***" << endl;
    string newFileName = "";
    cin >> newFileName;

    string add;

    string theFileName = createNewFile(newFileName);
    //fstream database (theFileName.c_str() , ios::trunc);
    fstream database (theFileName.c_str());

    //append database name to path and creates it there.
    ofstream database (createNewFile(newFileName).c_str() , ios::trunc);

    //check if buffer = true
    if(database.is_open())
        cout << "****Database succesfully created***" << endl;
    else
        cout << "****Database could not be created***" << endl;

    //Register size validachion.
    if(*registerSize >= K->MAX_REGISTER_SIZE)
        cout << "Error: Register size beyond max size" << endl;
    else
    {
        database << "000";
//      database.seekp(K->REGISTER_SIZE_ADDRESS , ios::beg);
        add = toChar(*registerSize);
        checkSize(&add, K->DEFAULT_REGISTER_SIZE);
        database.write(add.c_str() , K->DEFAULT_REGISTER_SIZE);
    }

    //set column sizes on file
    array<int> tempArr = *columnSizes;
    for (int i = 0 ; i < tempArr.getLeght() ; i++)
    {
        int integerElem = tempArr[i];
        add = toChar(integerElem);
        checkSize(&add,K->DEFAULT_COLUMN_SIZE);
        database.write(add.c_str() , K->DEFAULT_COLUMN_SIZE);
    }

    //sets seek on the end, gets the address then turns it to char
    //to insert on the beginning.
    database.seekp(offset, ios::end);
    int meta = database.tellp();
    string metadata = intToChar(meta);
    checkSize(&metadata, K->METADATA_SIZE);
    database.seekp(K->ZE_ROW);
    if (metadata.length() <= 3){
        const char *p = metadata.c_str();
        while (*p != '\0')
            database.put( *(p++) );
    }else{
        cout << "Invalid metadata size. Yoh ! Pls kontact ur admin...\n";
    }
    database.close();
}

//void updateField(){
//    fstream file (K->DIRFILE.c_str() , ios::app);
//    if(data.size() <= 64){

//    }
//    file.close();
//}

int stringToInt(string* pStr){
    int i;
    i= atoi(pStr->c_str());
    return i;
}

string charCallocToString(char* pCharCalloc){
    string stringToReturn ;
    stringToReturn = "";
    for (int i = NULL; i <= K->DEFAULT_COLUMN_SIZE;i++){
        stringToReturn.append(((const char*)(pCharCalloc + i)));
    }
    return stringToReturn;
}

int getRegisterSize(fstream* pFile){
    pFile->seekg(K->DEFAULT_COLUMN_SIZE);
    char* charString = (char*)calloc(4 ,1);
    pFile->read(charString, K->REGISTER_SIZE_ADDRESS);
    string regSizeString = charCallocToString(charString);
    int regSize;
    regSize = stringToInt(&regSizeString);
    return regSize;
}

int getMetaDataSize(fstream* pFile){
    pFile->seekg(NULL);
    char* charString = (char*)calloc(3 ,1);
    pFile->read(charString, K->DEFAULT_COLUMN_SIZE);
    string MDSizeString = charCallocToString(charString);
    int MDSizeInt  = stringToInt(&MDSizeString);
    return MDSizeInt;
}

int getRegisterQuantity(fstream* pFile){
    pFile->seekg(0 , ios::end);
    int fileSize = pFile->tellg();
    int registerSize = getRegisterSize(pFile);
    int regQty ;
    regQty = (fileSize - (getMetaDataSize(pFile)))/registerSize;
    return regQty;
}

//array<string>& getAllDataFromColumn(fstream* pFile, int pColumn){
//    int* regQtt = getRegisterQuantity(pFile , pColumn);
//    array<string>* columnData(*regQtt);
//    for (int row = NULL; row <= regQtt; i++){
//        string* stringToAppend = readField(pFile, row, pColumn);
//        columnData[row] = *stringToAppend;
//    }
//    return columnData;
//}

int columnSize(fstream* pFile , int pColumnInt){
    //Move the seek to the beginning of the column.
    pFile->seekg((K->REGISTER_SIZE_ADDRESS + K->DEFAULT_COLUMN_SIZE) +
                 ((pColumnInt - K->ONE_BYTE) * K->DEFAULT_COLUMN_SIZE));
    char* charString = (char*)calloc(K->DEFAULT_COLUMN_SIZE, K->ONE_BYTE);
    pFile->read(charString , K->DEFAULT_COLUMN_SIZE);
    string cSize = K->EMPTY_STRING;
    // build the string;
    for (int i = NULL; i <= K->DEFAULT_COLUMN_SIZE ; i++){
        cSize.append(((const char*)charString + i));
    }
    int cSizeInt = stringToInt(&cSize);
    cout << cSizeInt;
    return cSizeInt;
}

int sizeUntilColumn(fstream* pFile, int pColumn){
    int sizeToReturn = K->ZE_ROW;
    for (int i = NULL; i < pColumn; i++){
        sizeToReturn = (sizeToReturn)+ columnSize(pFile, i);
    }
    return sizeToReturn;
}

void fillString(string* pData, int pSize){
    while ( pData->length() < pSize){
        pData->append(K->NULL_CHAR.c_str());
    }
}

void writeRegister(string pFile, array<char*>* columnData ,
                   array<int>* columnPos){
    array<int> tempCPosArr = *columnPos;
    array<char*> tempCDataArr = *columnData;
    string registerToWrite = "";

    string standardDir = createNewFile(pFile);
    fstream file (standardDir.c_str(), ios::app | ios::in | ios::out);

    file.seekp(K->ZE_ROW, ios::end);
    fillString (&registerToWrite , getRegisterSize(&file));
    //Get each data and fill the blanks.
    for (int i = 0 ; i < tempCPosArr.getLeght() ; i++){
        string Cdata  = tempCDataArr[i];
        int Csize = columnSize(&file , tempCPosArr[i]);
        int spacesToMove = sizeUntilColumn(&file ,Csize);
        fillString(&Cdata ,Csize);
        cout << Cdata << "  " << spacesToMove << "  " << Csize <<"\n";
        registerToWrite.replace(spacesToMove , Csize , Cdata.c_str());
    }
    cout <<"Registro: " <<registerToWrite;
    file << registerToWrite;
}

string readField(string pFile , int pRow , int Column){
    //Relative route + the name of the file
    string standardDir = createNewFile(pFile.c_str());
    fstream file (standardDir.c_str());


    //Move seek to the row
    file.seekg((getRegisterSize(&file))*pRow);

    //move seek to the beginning of the column
    int sizeToColumn = sizeUntilColumn(&file , Column);
    file.seekg(sizeToColumn);

    //Read the info
    int cSize = columnSize(&file , Column);

    char* infoInsideColumn = (char*)calloc(cSize, sizeof(char));
    file.read(infoInsideColumn , cSize);

    //build the stringto return
    string stringToReturn = charCallocToString(infoInsideColumn);
    return stringToReturn;
}

void test0(){
    cout << "*** Bienvenido a FSQL Server ***" << endl;
    cout << "\n";
    int regSize;
    regSize = 320;
    array<int> columnSais (5);
    columnSais[0] = 64;
    columnSais[1] = 64;
    columnSais[2] = 128;
    columnSais[3] = 64;
    columnSais[4] = 32;
    createTable(&regSize ,&columnSais);
}

void test1(){
    array<char*> cData(1);
    string stringToAdd = "Luis";
    char *s2 = new char[stringToAdd.size()+1];
    strcpy(s2, stringToAdd.c_str());
    cData[0] = s2;

    array<int> cPos(1);
    cPos[0] = 0;

    string fileName = "Test8";
    cout << fileName;
    writeRegister(fileName, &cData, &cPos);
}

int main()
{
    setup();
    test1();
    return 0;
}

