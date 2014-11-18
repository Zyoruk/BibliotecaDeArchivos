#include "usefile.h"

useFile::useFile()
{
    K  = new konstants();
}

/**
 * @brief getColumnNumber For a column number get its name.
 * @param fileName Complete path of file to be asociated with.
 * @param columnName
 * @return
 */
int useFile::getColumnNumber(string* fileName ,string* columnName){
    string tmp = "Columns";
    string path = *fileName;
    string COLNAME;
    path.append(tmp);
    int i = K->ONE_BYTE;
    int columnNumber = -2;
    if (!file_COL.is_open()) {
        file_COL.open(path.c_str());
    }

    if (!file_COL.is_open()){
        cout << K->NO_EXISTANT_FILE ;
        return -1;
    }

    file_COL.seekg(K->ZE_ROW);
    while (!file_COL.eof())
    {
        getline(file_COL,COLNAME);
        if ( *columnName == COLNAME)
            columnNumber = i;
        i++;
    }
    file_COL.close();
    //La variable de regreso es eliminada
    return columnNumber;
}
string useFile::toChar(int toChar){
    string s;
    stringstream out;
    out << toChar;
    s = out.str();
    return s;
}

void useFile::checkSize(string* add, int count){
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

string useFile::intToChar(int metadata){
    int ch;
    string tmp ;
    while (metadata != 0){
        ch = metadata % 10;
        metadata = metadata / 10;
        tmp.append(toChar(ch));
    }
    return tmp;
}

string useFile::createNewFile(string newFileName){
    string newFileDir ;
    newFileDir = K->DIRFILE;
    newFileDir.append(newFileName);
    return newFileDir;
}

string useFile::createNewBackUp(string newFileName){
    string newFileDir ;
    newFileDir = K->BACK_UPS_DIR;
    newFileDir.append(newFileName);
    return newFileDir;
}


int useFile::stringToInt(string* pStr){
    int i;
    i= atoi(pStr->c_str());
    return i;
}

//string useFile::charCallocToString(char* pCharCalloc){
//    string stringToReturn ;
//    stringToReturn = "";
//    for (int i = 0; i <= K->DEFAULT_COLUMN_SIZE ; i++){
//        stringToReturn.append(((const char*)(pCharCalloc + i)));
//    }
//    return stringToReturn;
//}

int useFile::getRegisterSize(){
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

int useFile::getMetaDataSize(){
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

int useFile::getRegisterQuantity(){
    int currSeek = file.tellg();
    file.seekg(K->ZE_ROW, ios::end);
    int fileSize = file.tellg();
    int registerSize = getRegisterSize();
    int regQty ;
    regQty = (fileSize - (getMetaDataSize()))/registerSize;
    file.seekg(currSeek);
    return regQty;
}

int useFile::columnSize(int pColumnInt){
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
int useFile::sizeUntilColumn(int pColumn){
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
void useFile::fillString(string* pData, int pSize){
    while ( (unsigned) pData->length() < (unsigned) pSize){
        pData->push_back(K->NULL_CHAR);
    }
}

void useFile::checkString(string* pStringToCheck){
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

void useFile::placeSeekOn(int* pRow , int* pColumn, int* pSizeToColumn,
                 int* pCSize){
    //Move seek to the row
      file.seekg(  getMetaDataSize() + ( getRegisterSize() * (*pRow-1) )  );
    //move seek to the beginning of the column

    *pSizeToColumn = sizeUntilColumn(*pColumn);
    file.seekg(*pSizeToColumn , ios::cur);
   //Read the info
    *pCSize = columnSize(*pColumn-1);
}
