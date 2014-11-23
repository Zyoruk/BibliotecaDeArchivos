#include "raidmanager.h"

raidManager::raidManager()
{
    this->FS = new FSQLServerFileSystem();
    this->net = new TCPClient();
}

/**
 * @brief raidManager::createNewFile creates the database (local or on network)
 * according with the raid mode selected.
 * @param columnSizes
 * @param columnNames
 * @param pFile
 * @param raidMode
 * @param commandLine
 * @return
 */
bool raidManager::createNewFile(array<int>* columnSizes,
                                array<char*>* columnNames,
                                string* pFile, int *raidMode,
                                string* commandLine){

    FS->createNewFile(columnSizes, columnNames, pFile, raidMode);
    bool clean = true;

    if (*raidMode >= 0){
        clean = net->link(SERVER_IP1, *commandLine);
    }
    /*
    if (*raidMode >= 5){
        clean = net->link(SERVER_IP2, *commandLine);
    }

    if (*raidMode == 10){
        clean = net->link(SERVER_IP3, *commandLine);
    }*/
    return clean;
}

/**
 * @brief raidManager::storeRegister
 * @param pFileName
 * @param pWhatToWrite Line caught from CMD.
 * @param pColumnNam
 * @return
 */
bool raidManager::storeRegister(string* pFileName , array<char*>* pWhatToWrite,
                                array<char*>* pColumnNam , string* commandLine){

    int netRegPosition;
    int raid = FS->getRaidMode(pFileName);
    string location = getLatestRegistryLocation(pFileName);
    cout << location << endl;

    if (location == ""){
        location = const_cast<char*> (NI);
    }

    switch(raid){
        case RAID0:
            //loop de servers, min 2 servers
            if(location == LOCAL){
                netRegPosition = net->linkIndex(SERVER_IP1, *commandLine);
                FS->updateDatabaseStruct(pFileName, SERVER_IP1 , netRegPosition);
            }
            else if(location == SERVER_IP1 ||
                    location == const_cast<char*> (NI)){

                netRegPosition = FS->writeNewLineToFile(*pFileName, pWhatToWrite,
                                                        pColumnNam);
                FS->updateDatabaseStruct(pFileName, LOCAL,
                                         netRegPosition);
            }
            break;

        /*
        case RAID1:
            //todo local y copiado al S1, min 2 servers
            netRegPosition = FS->writeNewLineToFile(*pFileName, pWhatToWrite,
                                                    pColumnNam);
            net->link(SERVER_IP1, commandLine);
            FS->updateDatabaseStruct(pFileName, (string*)LOCAL, netRegPosition);
            break;

        case RAID5:
            string lst = LAST_REG;
            //loop de servers, min 2 servers
            if(location == LOCAL){
                //ask for last reg written
                string last = net->link(location,&lst); //asking for last reg inserted
                string XOR = last ^ getOnRegFormat(commandLine); //create xor string
                netRegPosition = net->link(SERVER_IP1, commandLine); //write on net
                FS->updateDatabaseStruct(pFileName, &SERVER_IP1 , netRegPosition); //write localy
                netRegPosition = net->link(SERVER_IP2, XOR); //write xor (should overwrite)
            }
            else if(location == SERVER_IP1 ||
                    location == const_cast<char*> (NI)){

                netRegPosition = FS->writeNewLineToFile(*pFileName, pWhatToWrite,
                                                        pColumnNam);
                FS->updateDatabaseStruct(pFileName, (string*)LOCAL,
                                         netRegPosition);
                netRegPosition = net->link(SERVER_IP2,
                                                     getOnRegFormat(commandLine)); //write xor
            }
            break;

        case RAID10:
            //loop y copiado, min 4 servers
            if(location == LOCAL){
                netRegPosition = net->link(SERVER_IP2, commandLine);
                net->link(SERVER_IP3, commandLine);
                FS->updateDatabaseStruct(pFileName, &SERVER_IP1, netRegPosition);
            }
            else if(location == SERVER_IP2 ||
                    location == const_cast<char*> (NI)){

                netRegPosition = FS->writeNewLineToFile(*pFileName, pWhatToWrite,
                                                        pColumnNam);
                net->link(SERVER_IP1, commandLine);
                FS->updateDatabaseStruct(pFileName, (string*) LOCAL,
                                         netRegPosition);
            }
            break;
        */

        default:
            FS->writeNewLineToFile(*pFileName , pWhatToWrite , pColumnNam);
            FS->updateDatabaseStruct(pFileName, "127.0.0.1", netRegPosition);
    }
}

/**
 * @brief raidManager::retrieveRegister
 * @param pFileName
 * @param commandLine
 * @param pRow
 * @return
 */
string raidManager::retrieveRegister(string* pFileName , string* commandLine,
                                    int pRow){

    string location = getLatestRegistryLocation(pFileName);
    string data;

    if(location == LOCAL){
        FS->readFromFile(*pFileName , ZE_ROW, pRow);
    }
    if (location == SERVER_IP1){
        data = net->link(SERVER_IP1, *commandLine);
    }
    if (location == SERVER_IP2){
        data = net->link(SERVER_IP2, *commandLine);
    }
    if (location == SERVER_IP3){
        data = net->link(SERVER_IP3, *commandLine);
    }

}

bool raidManager::dataRecovery(string* database){
    if(FS->getRaidMode(database) != 05){
        cout << "*** Non recovery raid mode ***";
        return false;
    }
}

string raidManager::getLatestRegistryLocation(string* pFile){
    string location = FS->readDataLocation(pFile);
    return location;
}

string raidManager::getOnRegFormat(string* pWhatToWrite){
    //METER INTERPRETE DE LINEA DE NUEVO REGISTRO
    string regFormat;
    return regFormat;
}
