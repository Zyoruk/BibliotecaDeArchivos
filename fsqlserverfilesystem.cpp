#include "fsqlserverfilesystem.h"

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
    if (checkIfFileExists(pFileName)){
            cout << "Do you want to overwrite the existant file ?";
            cin << confirm;
            switch (confirm){
                case _C._Y_:
                    WF.createTable(pRegisterSize, pColumnSizes, pColumnNames ,
                                   pFile);
                case _C._N_:
                    cout << "File was not created."<< endl;
            }
        }
}

void FSQLServerFileSystem::writeNewLineToFile(string pFileName ,
                                              array<char*> pWhatToWrite,
                                              array<int>* pColumnPos){
    if (checkIfFileExists(pFileName)){
        WF.writeRegister(pFileName, pWhatToWrite , pColumnPos);
    }else{
        cout << _C.NO_EXISTANT_FILE;
    }

}

void FSQLServerFileSystem::removeFile(string pFileName){
    if (checkIfFileExists(pFileName)){
        string newFileDir ;
        newFileDir = C->DIRFILE;
        newFileDir.append(pFile);
        remove(newFileDir);
    }else{
        cout << _C.NO_EXISTANT_FILE;
    }
}

void FSQLServerFileSystem::readFromFile(string pFileName , int pColumn,
                                        int pRow){
    if (checkIfFileExists(pFileName)){
        //If column is zero then the user means to read a whole registry
        if(pColumn == _C.ZE_ROW){
            array<char*> registryData = RF.readRegistry(pFileName , pRow);

            string newFileDir ;
            newFileDir = C->DIRFILE;
            newFileDir.append(pFile);

            for(int i = _C.ZE_ROW ; i < registryData.getLenght();i++){
                cout << RF.getColumnName(&newFileDir , i)<< registryData[i] << endl;
            }

        //If the row is 0 then the user means to read a whole column
        }else if(pRow == _C.ZE_ROW){
            array<char*> columnData = RF.readColumn(pFileName , RF.getColumnName(pColumn));

            string newFileDir ;
            newFileDir = C->DIRFILE;
            newFileDir.append(pFile);

            cout << RF.getColumnName(&newFileDir , i);

            for(int i = _C.ZE_ROW ; i < columnData.getLenght();i++){
                cout << columnData[i] << endl;
            }
        }else if (pRow < _C.ZE_ROW ||pColumn <_C.ZE_ROW){
            cout << "Invalid values." << endl;
        }else{
            string field = RF.readField(pFile, pRow, pColumn);
            cout << "Data inside field: " << field << endl;
        }
    }else{
        cout << _C.NO_EXISTANT_FILE << endl;
    }
}

void FSQLServerFileSystem::backUpFile (string pFileName){
    if (checkIfFileExists(pFileName)){
        WF.backUpFile(pFileName);
    }else{
        cout << _C.NO_EXISTANT_FILE << endl;
    }
}

void FSQLServerFileSystem::restoreFile(string pFileName){
    string backUp= "backup";
    backUp.append(pFileName);
    if (checkIfFileExists(pFileName)){
         WF.restoreFile(pFileName);
    }else{
        cout << _C.NO_EXISTANT_FILE << endl;
    }

}

bool FSQLServerFileSystem::checkIfFileExists(string pFile){
    string newFileDir ;
    newFileDir = C->DIRFILE;
    newFileDir.append(pFile);
    fstream file;
    file.open(newFileDir);
    if (!file.is_open()) cout << _C.NO_EXISTANT_FILE <<endl;
    return file.is_open();
}
