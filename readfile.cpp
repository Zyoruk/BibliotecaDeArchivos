#include "readfile.h"
#include "usefile.h"

readfile::readfile()
{
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
    file_col.open(path.c_str());

    while (i != *columnNumber)
    {
        getline(file_col, columnName);
        i++;
        if(file_col.eof())
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
string readfile::readField(string pFile , int pRow , string pColumn){
    int currSeek =file.tellg();
    int sizeToColumn;
    int cSize;
    int intpColumn = this->getColumnNumber(&pFile, &pColumn);
    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string fileH = pFile;
        string standardDir = createNewFile(&fileH);
        file.open(standardDir.c_str());
    }

    if ( !(file.is_open()) ){
        return "NED " + pFile;
    }

   placeSeekOn(&pRow , &intpColumn, &sizeToColumn, &cSize);

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
        string standardDir = createNewFile(&pFile);
        file.open(standardDir.c_str());
    }

    if ( !(file.is_open()) ){
        return "NED " + pFile;
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
/**
 * @brief readColumn return all the values on a named column
 * @param pFile is the database to be readed from.
 * @param pColumnName parameter for returning a value.
 * @return
 */
array<char*> readfile::readColumn(string pFile , string pColumnName){
    string standardDir;
    array <char*> errorArray (ONE_BYTE);   //if !database, return null array

    if ( !(file.is_open()) ){
        standardDir = createNewFile(&pFile);
        file.open(standardDir.c_str());
    }

    if ( !(file.is_open()) ){
        cout << "NED " + pFile << endl;
        return errorArray;
    }

    int Column = getColumnNumber(&standardDir , &pColumnName );
    int regQty = getRegisterQuantity();
    string strToConvert = EMPTY_STRING;
    char * toAdd;
    array <char*> arrayToReturn (regQty);

    for (int rowCounter = ONE_BYTE ; rowCounter <= regQty ; rowCounter++){
        strToConvert = readField(pFile , rowCounter , pColumnName);
        toAdd = new char[strToConvert.size()+1];
        strcpy(toAdd, strToConvert.c_str());
        arrayToReturn[rowCounter - ONE_BYTE] = toAdd;
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
        string standardDir = createNewFile(&pFile);
        file.open(standardDir.c_str());
    }

    if ( !(file.is_open()) ){
        cout << NO_EXISTANT_DATA + pFile << endl;
        return errorArray;
    }

    //Create an array that will contain all the columns
    int columnQty = (getMetaDataSize() - METADATA_COLUMN_START)
                    / DEFAULT_COLUMN_SIZE;

    array < char* > arrayToReturn (columnQty);
    string tempString = EMPTY_STRING;
    char* toAdd;
    for (int i = ZE_ROW; i < columnQty; i++){
        tempString = readField(pFile , pRegister , i+1);
        toAdd = new char[tempString.size()+1];
        strcpy(toAdd, tempString.c_str());
        arrayToReturn[i] = toAdd;
    }

    file.close();
    return arrayToReturn;
}

array< array<char*> > readfile::getRegisters(string pFile, string pColumnName,
                                             string valueToConsult){
    string standardDir;
    int regs = getRegisterQuantity();
    int colNum;

    if ( !(file.is_open()) ){
        standardDir = createNewFile(&pFile);
        file.open(standardDir.c_str());
    }

    colNum = getColumnNumber(&standardDir, &pColumnName);

    array< array<char*> > select (getRegisterQuantity());

    for ( int i = ZE_ROW ; i < regs ; i ++){
        if(valueToConsult == readField(pFile,i+1,colNum)){
            select [i] = readRegistry( pFile , colNum);
        }
    }
    return select;
}

string readfile::readDataLocation(string* pFile){
    int currSeek = file.tellg();

    //Relative route + the name of the file
    if ( !(file_lo.is_open()) ){
        string standardDir = createNewFile(pFile);
        file_lo.open(standardDir.c_str());
    }

    if ( !(file_lo.is_open()) ){
        return "NED " + *pFile;
    }

    //build the stringto return
    string stringToReturn = "";

    while (!file_lo.eof())
    {
        getline(file_lo, stringToReturn);
    }

    file.seekg(currSeek);
    if (stringToReturn == "") stringToReturn = "404";
    return stringToReturn;
}

int readfile::getRaidMode(string* pFile){
    int currSeek = file.tellg();

    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string standardDir = createNewFile(pFile);
        file.open(standardDir.c_str());
    }

    if ( !(file.is_open()) ){
        cout << NO_EXISTANT_FILE <<endl;
        return -1;
    }

    string raid;
    file.seekg(RAID_MODE_START);
    for (short i = ZE_ROW; i < 2 ; i++){
        raid.push_back(file.get());
    }
    int RD = stringToInt(&raid);
    file.seekg(currSeek);
    return RD;
}
