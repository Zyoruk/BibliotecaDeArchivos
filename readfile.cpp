#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "konstants.h"
#include "array/array.h"
#include "readfile.h"

readfile::readfile()
{
    C = new konstants();
}

/**
 * @brief checkSize check max size of field size on metadata.
 * @param add the data to be added to metadata.
 * @param count size of the field.
 */
void readfile::checkSize(string* add, int count){
    string tmp;
    int len = add->length();

    if( len > count){
        cout << "Datafield beyond max size";
        return;
    }

    for (int a = 1 ; a < count ; a++){
        if((tmp.length() + add->length()) == count){
            break;
        }
        tmp.push_back( C->SINGLE_NULL);
    }
    tmp.append(*add);
    *add = tmp;
}

/**
 * @brief createNewFile Append constant path to database name for adquiring.
 * @param newFileName
 * @return
 */
string readfile::createNewFile(string newFileName){
    string newFileDir ;
    newFileDir = C->DIRFILE;
    newFileDir.append(newFileName);
    return newFileDir;
}

/**
 * @brief stringToInt Submethod for changing data.
 * @param pStr
 * @return
 */
int readfile::stringToInt(string* pStr){
    int i;
    i= atoi(pStr->c_str());
    return i;
}

/**
 * @brief toChar Submethod for changing data.
 * @param toChar
 * @return
 */
string readfile::toChar(int toChar){
    string s;
    stringstream out;
    out << toChar;
    s = out.str();
    return s;
}

/**
 * @brief intToChar Decompose an int to a char. Fills the blancks then returns
 * a string.
 * @param metadata
 * @return
 */
string readfile::intToChar(int metadata){
    int ch;
    string tmp ;
    while (metadata != 0){
        ch = metadata % 10;
        metadata = metadata / 10;
        tmp.append(toChar(ch));
    }
    return tmp;
}

/**
 * @brief charCallocToString
 * @param pCharCalloc
 * @return
 */
string readfile::charCallocToString(char* pCharCalloc){
    string stringToReturn ;
    stringToReturn = "";
    for (int i = NULL; i <= C->DEFAULT_COLUMN_SIZE;i++){
        stringToReturn.append(((const char*)(pCharCalloc + i)));
    }
    return stringToReturn;
}

/**
 * @brief getRegisterSize
 * @return
 */
int readfile::getRegisterSize(){
    int currSeek = file.tellg();
    file.seekg(C->ZE_ROW);
    file.seekg(C->DEFAULT_COLUMN_SIZE);
    string regSizeString = "";
    for (int i  = 0 ; i < C->DEFAULT_REGISTER_SIZE;i++){
        regSizeString.push_back(file.get());
    }
    int regSize;
    regSize = stringToInt(&regSizeString);
    file.seekg(currSeek);
    return regSize;
}

/**
 * @brief getMetaDataSize Parse file for the size of metadata.
 * @return
 */
int readfile::getMetaDataSize(){
    int currSeek = file.tellg();
    file.seekg(C->ZE_ROW);
    string MDSizeString = "";
    for (int i  = 0 ; i < C->METADATA_SIZE;i++){
        MDSizeString.push_back(file.get());
    }
    int MDSizeInt  = stringToInt(&MDSizeString);
    file.seekg(currSeek);
    return MDSizeInt;
}

/**
 * @brief getRegisterQuantity gets how many registrys are in the file
 * @return
 */
int readfile::getRegisterQuantity(){
    int currSeek = file.tellg();
    file.seekg(C->ZE_ROW, ios::end);
    int fileSize = file.tellg();
    int registerSize = getRegisterSize();
    int regQty ;
    regQty = (fileSize - (getMetaDataSize()))/registerSize;
    file.seekg(currSeek);
    return regQty;
}

/**
 * @brief columnSize Parse the field on file getting a column size.
 * @param pColumnInt
 * @return
 */
int readfile::columnSize(int pColumnInt){
    int currSeek = file.tellg();
    file.seekg(C->ZE_ROW);

    //Move the seek to the beginning of the column.
    int whereToMove = (C->METADATA_COLUMN_START +
                      (pColumnInt * C->DEFAULT_COLUMN_SIZE));
    file.seekg(whereToMove);
    string cSize = C->EMPTY_STRING;
    // build the string;
    for (int i = whereToMove; i < (whereToMove + C->DEFAULT_COLUMN_SIZE) ; i++){
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
int readfile::sizeUntilColumn(int pColumn){
    int sizeToReturn = C->ZE_ROW;
    for (int i = C->ZE_ROW; i < pColumn -1 ; i++){
        sizeToReturn += columnSize(i);
    }
    return sizeToReturn;
}

/**
 * @brief fillString creates a string with the size of a registry
 * @param pData registry to be initialized.
 * @param pSize size of the registry.
 */
void readfile::fillString(string* pData, int pSize){
    while ( pData->length() < pSize){
        pData->push_back(C->NULL_CHAR);
    }
}

/**
 * @brief checkString Check for white spaces on the string entry.
 * @param pStringToCheck
 */
void readfile::checkString(string* pStringToCheck){
    char* tempString = new char[(*pStringToCheck).size()+1];
    strcpy(tempString, (*pStringToCheck).c_str());
    for (int i = C->ZE_ROW ; i < pStringToCheck->length(); i++){
        if (tempString[i] == ' ' ){
            tempString[i] = '_';
        }
    }
    string stringToReturn(tempString);
    *pStringToCheck = stringToReturn;
}

/**
 * @brief placeSeekOn Place the seek on a specific field of the database.
 * @param pRow
 * @param pColumn
 * @param pSizeToColumn Size of previous column before field.
 * @param pCSize Size of the column for the field we wan.
 */
void readfile::placeSeekOn(int* pRow , int* pColumn, int* pSizeToColumn,
                 int* pCSize){
    //Move seek to the row
      file.seekg(  getMetaDataSize() + ( getRegisterSize() * (*pRow-1) )  );
    //move seek to the beginning of the column

    *pSizeToColumn = sizeUntilColumn(*pColumn);
    file.seekg(*pSizeToColumn , ios::cur);
   //Read the info
    *pCSize = columnSize(*pColumn-1);
}

/**
 * @brief getColumnNumber For a column number get its name.
 * @param fileName Complete path of file to be asociated with.
 * @param columnName
 * @return
 */
int readfile::getColumnNumber(string* fileName ,string* columnName){
    string tmp = "Columns";
    string path = *fileName;
    string COLNAME;
    path.append(tmp);
    int i = C->ONE_BYTE;
    int columnNumber = -2;
    file_COL.open(path.c_str());
    while (file_COL.tellg() != -1)
    {
        getline(file_COL,COLNAME);
        if ( *columnName == COLNAME)
            columnNumber = i;
        i++;
    }
    //La variable de regreso es eliminada
    return columnNumber;
}

/**
 * @brief getColumnName Match to files searching for the name of a column number.
 * @param fileName Complete path of file to be asociated with.
 * @param columnNumber
 * @return
 */
string readfile::getColumnName(string* fileName ,int* columnNumber){
    string col = "Columns";
    string path = *fileName;
    path.append(col);
    int i = 0;

    string columnName = "NOT FOUND";
    file_COL.open(path.c_str());

    while (i != *columnNumber)
    {
        getline(file_COL, columnName);
        if(file_COL.eof())
            break;
    }
    //La variable de regreso es eliminada
    return columnName;
}

/**
 * @brief readField returns the data readed on field of the database.
 * @param pFile is the name of the file to be readed from.
 * @param pRow is the row of the desired data.
 * @param Column is the column of the desired data.
 * @return
 */
string readfile::readField(string pFile , int pRow , int pColumn){
    int currSeek =file.tellg();
    int sizeToColumn;
    int cSize;

    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string fileH = pFile;
        string standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }

    if ( !(file.is_open()) ){
        return "NED " + pFile;
    }

    readfile::placeSeekOn(&pRow , &pColumn, &sizeToColumn, &cSize);

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

/**
 * @brief readColumn return all the values on a named column
 * @param pFile is the database to be readed from.
 * @param pColumnName parameter for returning a value.
 * @return
 */
array<char*> readfile::readColumn(string pFile , string pColumnName){
    string standardDir;
    array <char*> errorArray (1);   //if !database, return null array

    if ( !(file.is_open()) ){
        string fileH = pFile;
        standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }

    if ( !(file.is_open()) ){
        cout << "NED " + pFile << endl;
        return errorArray;
    }

    int Column = readfile::getColumnNumber(&standardDir , &pColumnName );
    int regQty = getRegisterQuantity();
    string strToConvert = C->EMPTY_STRING;
    char * toAdd;
    array <char*> arrayToReturn (regQty);

    for (int rowCounter = C->ONE_BYTE ; rowCounter <= regQty ; rowCounter++){
        strToConvert = readField(pFile , rowCounter , Column);
        toAdd = new char[strToConvert.size()+1];
        strcpy(toAdd, strToConvert.c_str());
        arrayToReturn[rowCounter - C->ONE_BYTE] = toAdd;
    }
    return arrayToReturn;
}

/**
 * @brief readRegistry return all the values for a required registry.
 * @param pFile the database to be consulted.
 * @param pRegister the row to be consulted.
 * @return
 */
array< char* > readfile::readRegistry(string pFile , int pRegister){
    array< char* > errorArray (1);
    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string fileH = pFile;
        string standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }

    if ( !(file.is_open()) ){
        cout << "NED " + pFile << endl;
        return errorArray;
    }

    //Create an array that will contain all the columns
    int columnQty = (getMetaDataSize() - C->METADATA_COLUMN_START)
                    / C->DEFAULT_COLUMN_SIZE;

    array < char* > arrayToReturn (columnQty);
    string tempString = C->EMPTY_STRING;
    char* toAdd;
    for (int i = C->ZE_ROW; i < columnQty; i++){
        tempString = readField(pFile , pRegister , i+1);
        toAdd = new char[tempString.size()+1];
        strcpy(toAdd, tempString.c_str());
        arrayToReturn[i] = toAdd;
    }

    file.close();
    return arrayToReturn;
}
