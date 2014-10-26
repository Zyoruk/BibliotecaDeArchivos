#include <iostream>
#include <fstream>
#include "konstants.h"
#include <limits>
#include <cstdlib>
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
string* createNewFile(string newFileName){
    string* newFileDir ;
    *newFileDir = K->DIRFILE;
    newFileDir->append(newFileName);
    //cout << newFileDir << endl;
    return newFileDir;
}

string* toChar(int *toChar){
    string* s;
    stringstream out;
    out << *toChar;
    *s = out.str();
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

string* intToChar(int *metadata){
    int ch;
    string* tmp;
    while (*metadata != 0){
        ch = *metadata % 10;
        *metadata = *metadata / 10;
        tmp->append(*(toChar(&ch)));
    }
    return tmp;
}


void createTable(int *registerSize, int* columnSizes, int *columns){
    cout << "**** Insert name for new table ***" << endl;
    cin >> newFileName;

    ofstream database ((*createNewFile(newFileName)).c_str() , ios::trunc);
    //append database name to path and creates it there.
    if(database.is_open())
        cout << "****Database succesfully created***" << endl;
    else
        cout << "****Database could not be created***" << endl;

    if(*registerSize >= K->MAX_REGISTER_SIZE)
        cout << "Error: Register size beyond max size" << endl;
    else
    {
        database.seekp(K->METADATA_SIZE_ADDRESS , ios::beg);
        string* add = toChar(&registerSize);]
        checkSize(add,K->DEFAULT_REGISTER_SIZE);
        database << *add;
    }

    for (int i = 0 ; i < columns ; i++)
    {
        add = toChar(columnSizes[i]);
        checkColSize(add,K->DEFAULT_COLUMN_SIZE);
        database << *add;
    }
    //Place char pointer on the data start pointer.
    database.seekp(*getDataInit(&newFileName));


    //sets seek on the end, gets the address then turns it to char
    //to insert on the beginning.
    database.seekp(0, ios::end);
    int meta = database.tellp();
    if (meta <= 3){
        string metadata = *(intToChar(&meta));
        const char *p = metadata.c_str();
        while (*p != '\0')
            database.put( *p++ );
    }else{

    }

    database.close();
}
 void createTable(string &ColumnNames, int &ColumnSizes){
     cout << "****Name for new table***" << endl;
     cin >> newFileName;
     ofstream* database = createNewFile(newFileName);
 }
int& getDataInit(string *newFileName){

}

void updateField(){
    ofstream file (K->DIRFILE.c_str() , ios::app);
    if(data.size() <= 64){

    }
    file.close();
}

int* stringToInt(string* pStr){
    int* i;
    *i= atoi(pStr->c_str());
    return i;
}
void readField(){
    ifstream file (K->DIRFILE.c_str());
    char character;
}
string* charCallocToString(char* pCharCalloc){
    string* stringToReturn ;
    *stringToReturn = "";
    for (int i = NULL; i <= K->THREE_BYTES;i++){
        stringToReturn->append(((const char*)(pCharCalloc + i)));
    }
    return stringToReturn;
}

int* getRegisterSize(ifstream* pFile){
    pFile->seekg(K->THREE_BYTES);
    char* charString = (char*)calloc(4 ,1);
    pFile->read(charString, K->HEADER_FILE_SIZE);
    string* regSizeString = charCallocToString(charString);
    int* regSize;
    *regSize = *stringToInt(regSizeString);
    return regSize;
}

int* getMetaDataSize(ifstream* pFile){
    pFile->seekg(NULL);
    char* charString = (char*)calloc(3 ,1);
    pFile->read(charString, K->THREE_BYTES);
    string* MDSizeString = charCallocToString(charString);
    int* MDSizeInt  = stringToInt(MDSizeString);
    return MDSizeInt;
}

int* getRegisterQuantity(ifstream* pFile){
    pFile->seekg(0 , ios::end);
    int fileSize = pFile->tellg();
    int registerSize = *getRegisterSize(pFile);
    int* regQty ;
    *regQty = (fileSize - (*getMetaDataSize(pFile)))/registerSize;
    return regQty;
}

//array<string>& getAllDataFromColumn(ifstream* pFile, int pColumn){
//    int* regQtt = getRegisterQuantity(pFile , pColumn);
//    array<string>* columnData(*regQtt);
//    for (int row = NULL; row <= regQtt; i++){
//        string* stringToAppend = readField(pFile, row, pColumn);
//        columnData[row] = *stringToAppend;
//    }
//    return columnData;
//}

int* columnSize(ifstream* pFile , int pColumnInt){
    //Move the seek to the beginning of the column.
    pFile->seekg((K->HEADER_FILE_SIZE + K->THREE_BYTES) +
                 ((pColumnInt - K->ONE_BYTE) * K->THREE_BYTES));
    char* charString = (char*)calloc(K->THREE_BYTES, K->ONE_BYTE);
    pFile->read(charString , K->THREE_BYTES);
    string cSize = K->EMPTY_STRING;
    // build the string;
    for (int i = NULL; i <= K->THREE_BYTES ; i++){
        cSize.append(((const char*)charString + i));
    }
    int* cSizeInt = stringToInt(&cSize);
    return cSizeInt;
}

int* sizeUntilColumn(ifstream* pFile, int pColumn){
    int* sizeToReturn = NULL;
    for (int i = NULL; i < pColumn; i++){
        *sizeToReturn = (*sizeToReturn)+ *columnSize(pFile, i);
    }
    return sizeToReturn;
}

string& readField(string* pFile , int pRow , int Column){
    //Relative route + the name of the file
    string fileToRead = K->dirFile;
    fileToRead.append(pFile);
    ifstream file (fileToRead.c_str());


    //Move seek to the row
    file.seekg((getRegisterSize(&file))*pRow);

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

