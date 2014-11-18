#include "fsqlserverfilesystem.h"

//Switch case doesn't allow the use of "_C->".
const char _Y = 'Y';
const char _N = 'N';

FSQLServerFileSystem::FSQLServerFileSystem()
{
    this->RF = new readfile();
    this->WF = new writefile();
    this->_C = new konstants();
}

bool FSQLServerFileSystem::createNewFile(int* pRegisterSize,
                                         array<int>* pColumnSizes ,
                                         array<char*>* pColumnNames ,
                                         string* pFile){
    char confirm ;
<<<<<<< HEAD
    if (checkIfFileExists(*pFile)){
            cout << _C->OVER_WRITE;
=======
    bool op = true;
    if (fileExists(*pFile)){
            cout << " Do you want to overwrite the existant file ?";
>>>>>>> 79b448cbd07c58f486baadf69888cefa70e6f053
            cin >> confirm;
            switch (confirm){
                case _Y:
                    WF->createTable(pRegisterSize, pColumnSizes, pColumnNames ,
                                   pFile);
<<<<<<< HEAD
                case _N:
                    cout << _C->FILE_NOT_CREATED << endl;
=======
                case 'N':
                    //cout << " File was not created."<< endl;
                    op = false;
                default:
                    //cout << " No monkeys allowed"<< endl;
                    op = false;
>>>>>>> 79b448cbd07c58f486baadf69888cefa70e6f053
            }
        }else{
            WF->createTable(pRegisterSize, pColumnSizes, pColumnNames ,
                           pFile);
    }
    return op;
}

bool FSQLServerFileSystem::writeNewLineToFile(string pFileName ,
                                              array<char*>* pWhatToWrite,
                                              array<char*>* pColumnNam){

    if (fileExists(pFileName)){
       bool toReturn =  WF->writeRegister(pFileName, pWhatToWrite , pColumnNam);
       return toReturn;
    }else{
        return false;
    }
}

bool FSQLServerFileSystem::removeFile(string pFileName){
    if (fileExists(pFileName)){
        string newFileDir ;
        newFileDir = _C->DIRFILE;
        newFileDir.append(pFileName);
        remove(newFileDir.c_str());
    }else{
        return false;
    }
    return true;
}

array<char*> FSQLServerFileSystem::readFromFile(string pFileName , int pColumn,
                                        int pRow){

    array<char*> columnData;

    if (pRow < _C->ZE_ROW || pColumn <_C->ZE_ROW ){
        cout << " Eres un bolonio. Invalid values." << endl;
        return columnData;
    }

    if (fileExists(pFileName)){
        //If column is zero then the user means to read a whole registry
        if(pColumn == _C->ZE_ROW){
            columnData = RF->readRegistry(pFileName , pRow);
        //If the row is 0 then the user means to read a whole column
        }else if(pRow == _C->ZE_ROW){

            string newFileDir ;
            newFileDir = _C->DIRFILE;
            newFileDir.append(pFileName);

<<<<<<< HEAD
            array<char*> columnData =
                    RF->readColumn(pFileName ,
                                   RF->getColumnName(&newFileDir , &pColumn));

            for(int i = _C->ZE_ROW ; i < columnData.getLenght();i++){
                cout << RF->getColumnName(&newFileDir , &i);
                cout << columnData[i] << endl;
            }
        }else if (pRow < _C->ZE_ROW ||pColumn <_C->ZE_ROW){
            cout << _C->INVALID_VALUES << endl;
=======
            columnData = RF->readColumn(pFileName, RF->getColumnName(&newFileDir,
                                                                     &pColumn));
>>>>>>> 79b448cbd07c58f486baadf69888cefa70e6f053
        }else{
            string field = RF->readField(pFileName, pRow, pColumn);
            cout << field << endl;
        }
    }else{
        cout << _C->NO_EXISTANT_FILE << endl;
    }
    return columnData;
}

bool FSQLServerFileSystem::backUpFile (string pFileName){
    if (fileExists(pFileName)){
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

<<<<<<< HEAD
void FSQLServerFileSystem::restoreFile(string pFileName){
    string backUp = _C->BACKUP_STRING;
=======
bool FSQLServerFileSystem::restoreFile(string pFileName){
    string backUp= "backup";
>>>>>>> 79b448cbd07c58f486baadf69888cefa70e6f053
    backUp.append(pFileName);
    if (backupExists(backUp)){
         WF->restoreFile(pFileName);
         if (fileExists(pFileName)){
             return true;
         }else{
             return false;
         }
    }else{
        //cout << _C->NO_EXISTANT_FILE << endl;
        return false;
    }
}
bool FSQLServerFileSystem::backupExists(string pBackUp){
    string newFileDir ;
    fstream file;
    newFileDir = _C->BACK_UPS_DIR;
    newFileDir.append(pBackUp);
    file.open(newFileDir.c_str());
    bool op = file.is_open();
    file.close();

    return op;
}

bool FSQLServerFileSystem::fileExists(string pFile){
    string newFileDir ;
<<<<<<< HEAD
    bool isOpen;
=======
    fstream file;
>>>>>>> 79b448cbd07c58f486baadf69888cefa70e6f053
    newFileDir = _C->DIRFILE;
    newFileDir.append(pFile);
    file.open(newFileDir.c_str());
<<<<<<< HEAD
    isOpen = file.is_open();
    if (!isOpen) cout << _C->NO_EXISTANT_FILE << endl;
    file.close();
    return isOpen;
=======
    bool op = file.is_open();
    file.close();
    return op;
}

bool FSQLServerFileSystem::update(string pData, string pFileName,int pRow, int pColumn){
    if (fileExists(pFileName)){
        bool toReturn = WF->updateField(pData , pFileName , pRow , pColumn);
        return toReturn;
    }else{
        return false;
    }
}

bool FSQLServerFileSystem::deleteData(string pFileName, string pColumnName, string pData){
    if (fileExists(pFileName)){
        bool toReturn = WF->deleteRegister(pFileName , pColumnName , pData);
        return toReturn;
    }else{
        return false;
    }
}

bool FSQLServerFileSystem::updateColumn(string newData,string pToCompare, string pFile, string pCName){
    if (fileExists(pFile)){
        bool toReturn = WF->updateColumn(newData,pToCompare,pFile,pCName);
        return toReturn;
    }else{
        return false;
    }
>>>>>>> 79b448cbd07c58f486baadf69888cefa70e6f053
}
