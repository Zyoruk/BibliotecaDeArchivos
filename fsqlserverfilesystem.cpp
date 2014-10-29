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

void FSQLServerFileSystem::createNewFile(int* pRegisterSize,
                                         array<int>* pColumnSizes ,
                                         array<char*>* pColumnNames ,
                                         string* pFile){
    char confirm ;
    if (checkIfFileExists(*pFile)){
            cout << _C->OVER_WRITE;
            cin >> confirm;
            switch (confirm){
                case _Y:
                    WF->createTable(pRegisterSize, pColumnSizes, pColumnNames ,
                                   pFile);
                case _N:
                    cout << _C->FILE_NOT_CREATED << endl;
            }
        }
}

void FSQLServerFileSystem::writeNewLineToFile(string pFileName ,
                                              array<char*>* pWhatToWrite,
                                              array<int>* pColumnPos){
    if (checkIfFileExists(pFileName)){
        WF->writeRegister(pFileName, pWhatToWrite , pColumnPos);
    }else{
        cout << _C->NO_EXISTANT_FILE;
    }

}

void FSQLServerFileSystem::removeFile(string pFileName){
    if (checkIfFileExists(pFileName)){
        string newFileDir ;
        newFileDir = _C->DIRFILE;
        newFileDir.append(pFileName);
        remove(newFileDir.c_str());
    }else{
        cout << _C->NO_EXISTANT_FILE;
    }
}

void FSQLServerFileSystem::readFromFile(string pFileName , int pColumn,
                                        int pRow){
    if (checkIfFileExists(pFileName)){
        //If column is zero then the user means to read a whole registry
        if(pColumn == _C->ZE_ROW){
            array<char*> registryData = RF->readRegistry(pFileName , pRow);

            string newFileDir ;
            newFileDir = _C->DIRFILE;
            newFileDir.append(pFileName);

            for(int i = _C->ZE_ROW ; i < registryData.getLenght();i++){
                cout << RF->getColumnName(&newFileDir , &i)<< registryData[i] << endl;
            }

        //If the row is 0 then the user means to read a whole column
        }else if(pRow == _C->ZE_ROW){

            string newFileDir ;
            newFileDir = _C->DIRFILE;
            newFileDir.append(pFileName);

            array<char*> columnData =
                    RF->readColumn(pFileName ,
                                   RF->getColumnName(&newFileDir , &pColumn));

            for(int i = _C->ZE_ROW ; i < columnData.getLenght();i++){
                cout << RF->getColumnName(&newFileDir , &i);
                cout << columnData[i] << endl;
            }
        }else if (pRow < _C->ZE_ROW ||pColumn <_C->ZE_ROW){
            cout << _C->INVALID_VALUES << endl;
        }else{
            string field = RF->readField(pFileName, pRow, pColumn);
            cout << field << endl;
        }
    }else{
        cout << _C->NO_EXISTANT_FILE << endl;
    }
}

void FSQLServerFileSystem::backUpFile (string pFileName){
    if (checkIfFileExists(pFileName)){
        WF->backUpFile(pFileName);
    }else{
        cout << _C->NO_EXISTANT_FILE << endl;
    }
}

void FSQLServerFileSystem::restoreFile(string pFileName){
    string backUp = _C->BACKUP_STRING;
    backUp.append(pFileName);
    if (checkIfFileExists(backUp)){
         WF->restoreFile(pFileName);
    }else{
        cout << _C->NO_EXISTANT_FILE << endl;
    }

}

bool FSQLServerFileSystem::checkIfFileExists(string pFile){
    string newFileDir ;
    bool isOpen;
    newFileDir = _C->DIRFILE;
    newFileDir.append(pFile);
    fstream file;
    file.open(newFileDir.c_str());
    isOpen = file.is_open();
    if (!isOpen) cout << _C->NO_EXISTANT_FILE << endl;
    file.close();
    return isOpen;
}
