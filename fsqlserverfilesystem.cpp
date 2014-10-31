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
    if (fileExists(*pFile)){
            cout << " Do you want to overwrite the existant file ?";
            cin >> confirm;
            switch (confirm){
                case 'Y':
                    WF->createTable(pRegisterSize, pColumnSizes, pColumnNames ,
                                   pFile);
                case 'N':
                    cout << " File was not created."<< endl;
                default:
                    cout << " No monkeys allowed"<< endl;
            }
        }
}

bool FSQLServerFileSystem::writeNewLineToFile(string pFileName ,
                                              array<char*>* pWhatToWrite,
                                              array<int>* pColumnPos){
    if (fileExists(pFileName)){
        WF->writeRegister(pFileName, pWhatToWrite , pColumnPos);
    }else{
        return false;
        //cout << _C->NO_EXISTANT_FILE;
    }
    return true;
}

bool FSQLServerFileSystem::removeFile(string pFileName){
    if (fileExists(pFileName)){
        string newFileDir ;
        newFileDir = _C->DIRFILE;
        newFileDir.append(pFileName);
        remove(newFileDir.c_str());
    }else{
        //cout << _C->NO_EXISTANT_FILE;
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

            columnData = RF->readColumn(pFileName, RF->getColumnName(&newFileDir,
                                                                     &pColumn));
        }else{
            string field = RF->readField(pFileName, pRow, pColumn);
            cout << "Data inside field: " << field << endl;
        }
    }else{
        cout << _C->NO_EXISTANT_FILE << endl;
    }
    return columnData;
}

bool FSQLServerFileSystem::backUpFile (string pFileName){
    if (fileExists(pFileName)){
        WF->backUpFile(pFileName);
    }else{
        //cout << _C->NO_EXISTANT_FILE << endl;
        return false;
    }
    return true;
}

bool FSQLServerFileSystem::restoreFile(string pFileName){
    string backUp= "backup";
    backUp.append(pFileName);
    if (fileExists(backUp)){
         WF->restoreFile(pFileName);
    }else{
        //cout << _C->NO_EXISTANT_FILE << endl;
        return false;
    }
    return true;
}

bool FSQLServerFileSystem::fileExists(string pFile){
    string newFileDir ;
    fstream file;
    bool op;
    newFileDir = _C->DIRFILE;
    newFileDir.append(pFile);
    file.open(newFileDir.c_str());
    if (!file.is_open())
        //cout << _C->NO_EXISTANT_FILE << endl;
    op = file.is_open();
    file.close();
    return op;
}
