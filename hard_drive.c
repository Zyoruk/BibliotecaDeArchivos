#include "hard_drive.h"

bool createNewFile(array<int>* pColumnSizes, array<char*>* pColumnNames ,
                                         string* pFile, int* raidMode){
    bool op;
    char confirm ;
    if (fileExists(pFile)){
        cout << OVER_WRITE;
        op = true;
        cin >> confirm;
        switch (confirm){
            case _Y:
                WF->createTable(pColumnSizes, pColumnNames ,
                               pFile, raidMode);
            case _N:
                cout << FILE_NOT_CREATED << endl;
                op = false;
            default:
                //cout << " No monkeys allowed"<< endl;
                op = false;
        }
    }else{
        WF->createTable(pColumnSizes, pColumnNames, pFile, raidMode);
    }
    return op;
}

bool writeNewLineToFile(string* pFileName , array<char*>* pWhatToWrite,
                        array<char*>* pColumnNam){

    if (fileExists(pFileName)){
       bool toReturn =  WF->writeRegister(*pFileName, pWhatToWrite , pColumnNam);
       return toReturn;
    }else{
        cout << "here";
        return false;
    }
}

bool removeFile(string pFileName){
    if (fileExists(&pFileName)){
        string newFileDir ;
        newFileDir = DIRFILE;
        newFileDir.append(pFileName);
        remove(newFileDir.c_str());
    }else{
        return false;
    }
    return true;
}

array<char*> readFromFile(string pFileName , string pColumn, int pRow){

    array<char*> columnData;

    if (pRow < ZE_ROW ){
        cout << " Eres un bolonio. Invalid values." << endl;
        return columnData;
    }

    string newFileDir ;
    newFileDir = DIRFILE;
    newFileDir.append(pFileName);

    if (fileExists(&pFileName)){
        //If column is zero then the user means to read a whole registry
        if(pColumn == ""){
            columnData = RF->readRegistry(pFileName , pRow);
        //If the row is 0 then the user means to read a whole column
        }else if (pColumn == "*"){
            for ( int i = 0 ; i <= RF->getRegisterQuantity(); i++){
                columnData = RF->readRegistry(pFileName , i);
            }
        }else if(pRow == ZE_ROW){

            array<char*> columnData =
                    RF->readColumn(pFileName ,
                                  pColumn);

            for(int i = ZE_ROW ; i < columnData.getLenght();i++){
                cout << RF->getColumnName(&newFileDir , &i);
                cout << columnData[i] << endl;
            }
        }else if (pRow < ZE_ROW ){
            cout << INVALID_VALUES << endl;
        }else{
            string field = RF->readField(pFileName, pRow, pColumn);
            cout << field << endl;
        }
    }else{
        cout << NO_EXISTANT_FILE << endl;
    }
    return columnData;
}

bool exportComponent (string pFileName){
    if (fileExists(&pFileName)){
        WF->backUpFile(pFileName);
        if (backupExists(pFileName)){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool update(string pData, string pFileName,int pRow, string pColumn){
    if (fileExists(&pFileName)){
        bool toReturn = WF->updateField(pData , pFileName , pRow , RF->getColumnNumber(&pFileName , &pColumn));
        return toReturn;
    }else{
        return false;
    }
}

bool restoreFile(string pFileName){
    string backUp = BACKUP_STRING;
    backUp.append(pFileName);
    if (backupExists(backUp)){
         WF->restoreFile(pFileName);
         if (fileExists(&pFileName)){
             return true;
         }else{
             return false;
         }
    }else{
        //cout << NO_EXISTANT_FILE << endl;
        return false;
    }
}

bool fileExists(string* pFile){
    string newFileDir ;
    fstream file;
    bool exist = false;
    newFileDir = DIRFILE;
    newFileDir.append(*pFile);
    file.open(newFileDir.c_str());
    if (file.is_open()){
        exist = true;
    }else{
        cout << NO_EXISTANT_FILE << endl;
    }
    file.close();
    return exist;
}

bool deleteData(string pFileName, string pColumnName, string pData){
    if (fileExists(&pFileName)){
        bool toReturn = WF->deleteRegister(pFileName , pColumnName , pData);
        return toReturn;
    }else{
        return false;
    }
}

bool updateColumn(string newData, string pToCompare, string pFile,
                  string pCName){
    if (fileExists(&pFile)){
        bool toReturn = WF->updateColumn(newData,pToCompare,pFile,pCName);
        return toReturn;
    }else{
        return false;
    }
}
