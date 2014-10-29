#include "writefile.h"
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

writefile::writefile()
{
    K = new konstants();
}

string writefile::toChar(int toChar){
    string s;
    stringstream out;
    out << toChar;
    s = out.str();
    return s;
}

void writefile::checkSize(string* add, int count){
    string tmp;

    for (int a = 1 ; a < count ; a++){
        if((unsigned)(tmp.length() + add->length()) == (unsigned) count){
            break;
        }
        tmp.push_back(K->SINGLE_NULL);
    }
    tmp.append(*add);
    *add = tmp;
}

string writefile::intToChar(int metadata){
    int ch;
    string tmp ;
    while (metadata != 0){
        ch = metadata % 10;
        metadata = metadata / 10;
        tmp.append(toChar(ch));
    }
    return tmp;
}

string writefile::createNewFile(string newFileName){
    string newFileDir ;
    newFileDir = K->DIRFILE;
    newFileDir.append(newFileName);
    return newFileDir;
}

int writefile::stringToInt(string* pStr){
    int i;
    i= atoi(pStr->c_str());
    return i;
}

string writefile::charCallocToString(char* pCharCalloc){
    string stringToReturn ;
    stringToReturn = "";
    for (int i = 0; i <= K->DEFAULT_COLUMN_SIZE ; i++){
        stringToReturn.append(((const char*)(pCharCalloc + i)));
    }
    return stringToReturn;
}

int writefile::getRegisterSize(){
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

int writefile::getMetaDataSize(){
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

int writefile::getRegisterQuantity(){
    int currSeek = file.tellg();
    file.seekg(K->ZE_ROW, ios::end);
    int fileSize = file.tellg();
    int registerSize = getRegisterSize();
    int regQty ;
    regQty = (fileSize - (getMetaDataSize()))/registerSize;
    file.seekg(currSeek);
    return regQty;
}

int writefile::columnSize(int pColumnInt){
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
int writefile::sizeUntilColumn(int pColumn){
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
void writefile::fillString(string* pData, int pSize){
    while ( (unsigned) pData->length() < (unsigned) pSize){
        pData->push_back(K->NULL_CHAR);
    }
}

void writefile::checkString(string* pStringToCheck){
    char* tempString = new char[(*pStringToCheck).size()+1];
    strcpy(tempString, (*pStringToCheck).c_str());
    for (int i = K->ZE_ROW ; (unsigned) i < (unsigned) pStringToCheck->length(); i++){
        if (tempString[i] == ' ' ){
            tempString[i] = '_';
        }
    }
    string stringToReturn(tempString);
    *pStringToCheck = stringToReturn;
}

void writefile::placeSeekOn(int* pRow , int* pColumn, int* pSizeToColumn,
                 int* pCSize){
    //Move seek to the row
      file.seekg(  getMetaDataSize() + ( getRegisterSize() * (*pRow-1) )  );
    //move seek to the beginning of the column

    *pSizeToColumn = sizeUntilColumn(*pColumn);
    file.seekg(*pSizeToColumn , ios::cur);
   //Read the info
    *pCSize = columnSize(*pColumn-1);
}

void writefile::writeColumnNames(string* fileName, array<char*>* columnNames){
    string col = "Columns";
    string path = *fileName;
    path.append(col);
    array<char*> columnNames2Use = *columnNames;

    ofstream whatever(path.c_str() , ios::trunc);
    //cout << whatever.is_open() <<endl;
    for (int i = 0 ; i < columnNames2Use.getLenght() ; i++){
        whatever << columnNames2Use[i];
        if ( i < (columnNames->getLenght() - 1))
            whatever << "\n";
    }
    whatever.close();
}

/**
 * @brief getColumnNumber For a column number get its name.
 * @param fileName Complete path of file to be asociated with.
 * @param columnName
 * @return
 */
int writefile::getColumnNumber(string* fileName ,string* columnName){
    string tmp = "Columns";
    string path = *fileName;
    string COLNAME;
    path.append(tmp);
    int i = K->ONE_BYTE;
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

//****************************************************************************//

/**
 * @brief createTable creates the database and metadata.
 * @param registerSize is the size for each registry.
 * @param columnSizes is the sizes for each column.
 */
void writefile::createTable(int* registerSize, array<int>* columnSizes ,
                            array<char*>* columnNames , string* pFile){

    int offset = 0;
    string add;

    string theFileName = createNewFile(*pFile);
    writefile::writeColumnNames(&theFileName, columnNames);
    ofstream database (theFileName.c_str() , ios::trunc);

    //check if buffer = true
    if(database.is_open())
        cout << "****Database succesfully created***" << endl;
    else
        cout << "****Database could not be created***" << endl;

    //Register size valideichion.
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
bool writefile::writeRegister(string pFileName, array<char*>* pColumnData ,
                              array<int>* columnPos){

    int currSeek = file.tellg();
    string standardDir = createNewFile(pFileName);
    file.open(standardDir.c_str());
    bool isOpen = true;

    if(!file.is_open()){
        cout << "NED "  + pFileName << endl;
        return false;
    }

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
    return isOpen;
}

/**
 * @brief updateField changes the value of a  given field on the whole database.
 * @param newData new information to be inserted.
 * @param pFile the database to be used
 * @param pRow
 * @param pColumn
 */
bool writefile::updateField(string newData, string pFile , int pRow , int pColumn){
    int currSeek = file.tellg();
    int sizeToColumn;
    int cSize;
    bool bowl = true;

    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string fileH = pFile;
        string standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }

    if ( !(file.is_open()) ){
        cout << "NED " + pFile << endl;
        bowl = false;
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
    return bowl;
}

/**
 * @brief updateColumn From pCname of pFile, replace pToCompare with newData
 * @param newData
 * @param pToCompare
 * @param pFile
 * @param pCName
 */
bool writefile::updateColumn(string newData,string pToCompare, string pFile, string pCName){
    int currSeek = file.tellg();
    int sizeToColumn;
    int cSize;
    string standardDir;
    bool bowl = true;

    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string fileH = pFile;
        standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }

    if ( !(file.is_open()) ){
        cout << "NED " + pFile << endl;
        bowl = false;
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
    return bowl;
}

void writefile::backUpFile(string fileTobackUp){
    string backUp= "backup";
    backUp.append(fileTobackUp); //backupTest8

    string pathFileToBackUp = createNewFile(fileTobackUp); //../FSQL/Test8
    string pathbackUpFile = createNewFile(backUp);// ../FSQL/backupTest8

    ofstream newfile (pathbackUpFile.c_str() , ios::trunc);
    newfile.close();

    std::ifstream ifs(pathFileToBackUp.c_str(), std::ios::binary);
    std::ofstream ofs(pathbackUpFile.c_str(), std::ios::binary);

    ofs << ifs.rdbuf();

    ifs.close();
    ofs.close();

    pathFileToBackUp.append("Columns");
    pathbackUpFile.append("Columns");

    ofstream newfile2 (pathbackUpFile.c_str() , ios::trunc);
    newfile2.close();

    std::ifstream ifs2(pathFileToBackUp.c_str(), std::ios::binary);
    std::ofstream ofs2(pathbackUpFile.c_str(), std::ios::binary);

    ifs2.close();
    ofs2.close();

    ofs2 << ifs2.rdbuf();

}

void writefile::restoreFile(string fileToRestore){
    string backUp= "backup";
    backUp.append(fileToRestore);

    string pathFileToRestore = createNewFile(backUp);
    string pathRestoredFile = createNewFile(fileToRestore);

    ofstream newfile (pathRestoredFile.c_str() , ios::trunc);
    newfile.close();


    std::ifstream ifs(pathFileToRestore.c_str(), std::ios::binary);
    std::ofstream ofs(pathRestoredFile.c_str(), std::ios::binary);

    ofs << ifs.rdbuf();

    ifs.close();
    ofs.close();

    pathFileToRestore.append("Columns");
    pathRestoredFile.append("Columns");

    ofstream newfile2 (pathRestoredFile.c_str() , ios::trunc);
    newfile2.close();

    std::ifstream ifs2(pathFileToRestore.c_str(), std::ios::binary);
    std::ofstream ofs2(pathRestoredFile.c_str(), std::ios::binary);

    ofs2 << ifs2.rdbuf();

    ifs2.close();
    ofs2.close();


}
