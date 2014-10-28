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
fstream file;
fstream file_COL;

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
    string tmp;

    for (int a = 1 ; a < count ; a++){
        if((tmp.length() + add->length()) == count){
            break;
        }
        tmp.push_back(K->SINGLE_NULL);
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
    return newFileDir;
}

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

int getRegisterSize(){
    int currSeek = file.tellg();
    file.seekg(K->ZE_ROW);
    file.seekg(K->DEFAULT_COLUMN_SIZE);
    string regSizeString = "";
    for (int i  = 0 ; i < K->DEFAULT_REGISTER_SIZE;i++){
        regSizeString.push_back(file.get());
    }
    int regSize;
    regSize = stringToInt(&regSizeString);
    file.seekg(currSeek);
    return regSize;
}

int getMetaDataSize(){
    int currSeek = file.tellg();
    file.seekg(K->ZE_ROW);
    string MDSizeString = "";
    for (int i  = 0 ; i < K->METADATA_SIZE;i++){
        MDSizeString.push_back(file.get());
    }
    int MDSizeInt  = stringToInt(&MDSizeString);
    file.seekg(currSeek);
    return MDSizeInt;
}

int getRegisterQuantity(){
    int currSeek = file.tellg();
    file.seekg(K->ZE_ROW, ios::end);
    int fileSize = file.tellg();
    int registerSize = getRegisterSize();
    int regQty ;
    regQty = (fileSize - (getMetaDataSize()))/registerSize;
    file.seekg(currSeek);
    return regQty;
}

int columnSize(int pColumnInt){
    int currSeek = file.tellg();
    file.seekg(K->ZE_ROW);

    //Move the seek to the beginning of the column.
    int whereToMove = K->METADATA_COLUMN_START+
                      (pColumnInt * K->DEFAULT_COLUMN_SIZE);
    file.seekg(whereToMove);
    string cSize = K->EMPTY_STRING;
    // build the string;
    for (int i = whereToMove; i < (whereToMove + K->DEFAULT_COLUMN_SIZE) ; i++){
        cSize.push_back(file.get());
    }

    int cSizeInt = stringToInt(&cSize);
    file.seekg(currSeek);
    return cSizeInt;
}

/*!
 * \brief sizeUntilColumn saber la cantidad de espacios a recorrer hasta
 * el inicio de la columna
 * \param pColumn
 * \return
 */
int sizeUntilColumn(int pColumn){
    int sizeToReturn = K->ZE_ROW;
    for (int i = K->ZE_ROW; i < pColumn -1 ; i++){
        sizeToReturn += columnSize(i);
    }
    return sizeToReturn;
}

/**
 * @brief fillString creates a string with the size of a registry
 * @param pData registry to be initialized.
 * @param pSize size of the registry.
 */
void fillString(string* pData, int pSize){
    while ( pData->length() < pSize){
        pData->push_back(K->NULL_CHAR);
    }
}

void checkString(string* pStringToCheck){
    char* tempString = new char[(*pStringToCheck).size()+1];
    strcpy(tempString, (*pStringToCheck).c_str());
    for (int i = K->ZE_ROW ; i < pStringToCheck->length(); i++){
        if (tempString[i] == ' ' ){
            tempString[i] = '_';
        }
    }
    string stringToReturn(tempString);
    *pStringToCheck = stringToReturn;
}

void placeSeekOn(int* pRow , int* pColumn, int* pSizeToColumn,
                 int* pCSize){
    //Move seek to the row
      file.seekg(  getMetaDataSize() + ( getRegisterSize() * (*pRow-1) )  );
    //move seek to the beginning of the column

    *pSizeToColumn = sizeUntilColumn(*pColumn);
    file.seekg(*pSizeToColumn , ios::cur);
   //Read the info
    *pCSize = columnSize(*pColumn-1);
}

void writeColumnNames(string* fileName, array<char*>* columnNames){
    string K = "Columns";
    string path = *fileName;
    path.append(K);
    array<char*> columnNames2Use = *columnNames;

    ofstream whatever(path.c_str() , ios::trunc);
    cout << whatever.is_open() <<endl;
    for (int i = 0 ; i < columnNames2Use.getLenght() ; i++){
        whatever << columnNames2Use[i];
        if ( i < (columnNames->getLenght() - 1))
            whatever << "\n";
    }
    whatever.close();
}

//La variable de regreso es eliminada
int getColumnNumber(string* fileName ,string* columnName){
    string tmp = "Columns";
    string path = *fileName;
    string COLNAME;
    path.append(tmp);
    int i =K->ONE_BYTE;
    int columnNumber = -2;
    file_COL.open(path.c_str());
    while (file_COL.tellg() != -1)
    {
        getline(file_COL,COLNAME);
        if ( *columnName == COLNAME)
            columnNumber = i;
        i++;
    }
    return columnNumber;
}

//La variable de regreso es eliminada
string getColumnName(string* fileName ,int* columnNumber){
    string K = "Columns";
    string path = *fileName;
    path.append(K);
    int i = 0;

    string columnName = "NOT FOUND";
    file_COL.open(path.c_str());

    while (i != *columnNumber)
    {
        getline(file_COL, columnName);
        if(file_COL.eof())
            break;
    }
    return columnName;
}

//****************************************************************************//

/**
 * @brief createTable creates the database and metadata.
 * @param registerSize is the size for each registry.
 * @param columnSizes is the sizes for each column.
 */
void createTable(int* registerSize, array<int>* columnSizes ,
                 array<char*>* columnNames , string* pFile){
//    string newFileName = *pFile;
    int offset = 0;
    string add;

    string theFileName = createNewFile(*pFile);
    writeColumnNames(&theFileName, columnNames);
    ofstream database (theFileName.c_str() , ios::trunc);

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
        database << K->TRIPLE_NULL;
        add = toChar(*registerSize);
        checkSize(&add, K->DEFAULT_REGISTER_SIZE);
        database.write(add.c_str() , K->DEFAULT_REGISTER_SIZE);
    }

    //set column sizes on file
    array<int> tempArr = *columnSizes;
    for (int i = 0 ; i < tempArr.getLenght() ; i++)
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
    database.seekp(K->ZE_ROW , ios::end);
    database.close();
}

/**
 * @brief writeRegister Method to append a whole registry. Add new element to database.
 * @param pFileName is the name of database file to add to.
 * @param pColumnData it's what to append.
 * @param columnPos is where to append it.
 */
void writeRegister(string pFileName, array<char*>* pColumnData ,
                   array<int>* columnPos){
    int currSeek = file.tellg();
    string standardDir = createNewFile(pFileName);
    file.open(standardDir.c_str());
    file.seekg(0);

    array<int> tempCPosArr = *columnPos;
    array<char*> tempCDataArr = *pColumnData;

    string registerToWrite = "";
    int spacesToMove;
    string Cdata;
    int Csize;

    //Get each data and fill the blanks.
    fillString (&registerToWrite , getRegisterSize());

    for (int i = 0 ; i < tempCPosArr.getLenght() ; i++){
        Cdata  = tempCDataArr[i];
        checkString(&Cdata);
        Csize = columnSize(tempCPosArr[i]);
        //Not sure
        spacesToMove = sizeUntilColumn(tempCPosArr[i]);
        fillString(&Cdata ,Csize);
        registerToWrite.replace(spacesToMove , Csize , Cdata.c_str());
    }

    if (file.is_open()){
        file.seekg(K->ZE_ROW , ios::end);
        file << registerToWrite;
    }
    file.seekg(currSeek);
    file.close();
}

/**
 * @brief readField returns the data readed on field of the database.
 * @param pFile is the name of the file to be readed from.
 * @param pRow is the row of the desired data.
 * @param Column is the column of the desired data.
 * @return
 */
string readField(string pFile , int pRow , int pColumn){
    int currSeek =file.tellg();
    int sizeToColumn;
    int cSize;
    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string fileH = pFile;
        string standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }
    placeSeekOn(&pRow , &pColumn, &sizeToColumn, &cSize);
    //build the stringto return
    string stringToReturn = "";

    for (int i  = 0 ; i < cSize ; i++){
        char currChar = file.get();
        if (currChar != '*'){
            stringToReturn.push_back(currChar);
        }else{
            break;
        }
    }
    file.seekg(currSeek);
    if (stringToReturn == "") stringToReturn = "404";
    return stringToReturn;
}

//array<string>& readColumn(fstream* pFile, int pColumn){
//    int* regQtt = getRegisterQuantity(pFile , pColumn);
//    array<string>* columnData(*regQtt);
//    for (int row = NULL; row <= regQtt; i++){
//        string* stringToAppend = readField(pFile, row, pColumn);
//        columnData[row] = *stringToAppend;
//    }
//    return columnData;
//}
void updateField(string newData, string pFile , int pRow , int pColumn){
    int currSeek = file.tellg();
    int sizeToColumn;
    int cSize;

    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string fileH = pFile;
        string standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }

    placeSeekOn(&pRow , &pColumn, &sizeToColumn, &cSize);

    fillString(&newData,cSize);

    if (file.is_open()){
        file << newData;
    }
    file.seekg(currSeek);
    if (file.is_open()){
        file.close();
    }
}

//From pCname of pFile, replace pToCompare with newData
void updateColumn(string newData,string pToCompare, string pFile, string pCName){
    int currSeek = file.tellg();
    int sizeToColumn;
    int cSize;
    string standardDir;
    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string fileH = pFile;
        standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }
    int Column = getColumnNumber(&standardDir , &pCName );
    int regQty = getRegisterQuantity();
    string currentData = K->EMPTY_STRING;
    for (int rowCounter = K->ONE_BYTE ; rowCounter <= regQty ; rowCounter++){
        //Move the seek to the column and register.
        placeSeekOn( &rowCounter , &Column, &sizeToColumn, &cSize);
        //Build the string of the old data
        for (int i = 0 ; i < cSize ; i++){
            char temp = file.get();
            if (temp == '*'){
                break;
            }else{
                currentData.push_back(temp);
            }
        }
        //Compare data.
        if (currentData == pToCompare){
            updateField(newData, pFile , rowCounter , Column);
        }
    }

    file.seekg(currSeek);
    if (file.is_open()){
        file.close();
    }
}

array< char* > readRegistry(string pFile , int pRegister){

    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string fileH = pFile;
        string standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }
    //Create an array that will contain all the columns
    int columnQty = (getMetaDataSize() - K->METADATA_COLUMN_START)/K->DEFAULT_COLUMN_SIZE;

    array < char* > arrayToReturn (columnQty);
    string tempString = K->EMPTY_STRING;
    char* toAdd;
    for (int i = K->ZE_ROW; i < columnQty; i++){
        tempString = readField(pFile , pRegister , i+1);
        toAdd = new char[tempString.size()+1];
        strcpy(toAdd, tempString.c_str());
        arrayToReturn[i] = toAdd;
    }

    file.close();
    return arrayToReturn;
}

//****************************************************************************//

void test0(){
    cout << "*** Bienvenido a FSQL Server ***" << endl;
    cout << "\n";
    int regSize;
    regSize = 352;
    array<int> columnSais (5);
    columnSais[0] = 64;
    columnSais[1] = 64;
    columnSais[2] = 128;
    columnSais[3] = 64;
    columnSais[4] = 32;
    array<char*> cNames(5);
    cNames[0] = "Nombre";
    cNames[1] = "Apellido";
    cNames[2] = "Direccion";
    cNames[3] = "Telefono";
    cNames[4] = "Sexo";
    string file ="Test9";
    createTable(&regSize ,&columnSais, &cNames ,&file);
}

void test1(){

    string fileName = "Test9";

    array<char*> cData(2);
    string nameToAdd = "Luis";
    string lastNameToAdd = "Simon Barrantes";
    char *s2 = new char[nameToAdd.size()+1];
    char *s3 = new char[lastNameToAdd.size()+1];
    strcpy(s2, nameToAdd.c_str());
    strcpy(s3, lastNameToAdd.c_str());
    cData[0] = s2;
    cData[1] = s3;

    array<int> cPos(2);
    cPos[0] = 1;
    cPos[1] = 2;

    writeRegister(fileName, &cData, &cPos);
    writeRegister(fileName, &cData, &cPos);
    writeRegister(fileName, &cData, &cPos);
}

void test2(){
    string fileName = "Test8";
    string field = readField(fileName.c_str(),1 ,1);
}

void test3(){
    updateField("Daniel", "Test8" , 1 , 1);
    updateField("Jenkins", "Test8" , 1 , 2);
}

void test4(){
    array<char*> test4 = readRegistry("Test8" , 1);
    for (int i = 0 ; i < test4.getLenght();i++){
        cout << test4[i] <<endl;
    }
}

void test5(){
    updateColumn("Simon_Barrantes" ,"Angel","Test9","Apellido");
}

//****************************************************************************//

int main()
{
    setup();
    return 0;
}

