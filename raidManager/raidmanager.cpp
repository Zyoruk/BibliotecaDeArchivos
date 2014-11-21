#include "raidmanager.h"

raidManager::raidManager()
{
    this->FS = new FSQLServerFileSystem();
    this->net = new networkAccess();
}

bool raidManager::createNewFile(int* pRegisterSize, array<int>* pColumnSizes,
                   array<char*>* pColumnNames, string* pFile, int* raidMode){

    FS->createNewFile(pRegisterSize, pColumnSizes, pColumnNames, pFile, raidMode);

    if (*raidMode >= 0){
        net->networkRequest(SERVER_IP1, DATAAAAAAA);
    }

    if (*raidMode >= 5){
        net->networkRequest(SERVER_IP2, DATAAAAAAA);
    }

    if (*raidMode == 10){
        net->networkRequest(SERVER_IP3, DATAAAAAAA);
    }
}

/**
 * @brief raidManager::storeRegister
 * @param pFileName
 * @param pWhatToWrite Line caught from CMD.
 * @param pColumnNam
 * @return
 */
bool raidManager::storeRegister(string* pFileName ,
                               array<char*>* pWhatToWrite,
                               array<char*>* pColumnNam){

    int netRegPosition;
    int raid = FS->getRaidMode(pFileName);
    string location = getLatestRegistryLocation(pFileName);

    if (location == ""){
        location = const_cast<char*> (NI);
    }

    switch(raid){
        case RAID0:
            //loop de servers, min 2 servers
            if(location == LOCAL){
                netRegPosition = net->networkRequest(SERVER_IP1, pWhatToWrite);
                FS->updateDatabaseStruct(pFileName, &SERVER_IP1 , netRegPosition);
            }
            else if(location == SERVER_IP1 ||
                    location == const_cast<char*> (NI)){

                netRegPosition = FS->writeNewLineToFile(*pFileName, pWhatToWrite,
                                                        pColumnNam);
                FS->updateDatabaseStruct(pFileName, (string*)LOCAL,
                                         netRegPosition);
            }
            break;

        case RAID1:
            //todo local y copiado al S1, min 2 servers
            netRegPosition = FS->writeNewLineToFile(*pFileName, pWhatToWrite,
                                                    pColumnNam);
            net->networkRequest(SERVER_IP1, *pWhatToWrite);
            FS->updateDatabaseStruct(pFileName, (string*)LOCAL, netRegPosition);
            break;

        case RAID5:
            //loop de servers, min 2 servers
            if(location == LOCAL){
                //ask for last reg written
                string last = net->networkRequest(&location,LAST_REG); //asking for last reg inserted
                string XOR = last ^ getOnRegFormat(pWhatToWrite); //create xor string
                netRegPosition = net->networkRequest(SERVER_IP1, pWhatToWrite); //write on net
                FS->updateDatabaseStruct(pFileName, &SERVER_IP1 , netRegPosition); //write localy
                netRegPosition = net->networkRequest(SERVER_IP2, XOR); //write xor (should overwrite)
            }
            else if(location == SERVER_IP1 ||
                    location == const_cast<char*> (NI)){

                netRegPosition = FS->writeNewLineToFile(*pFileName, pWhatToWrite,
                                                        pColumnNam);
                FS->updateDatabaseStruct(pFileName, (string*)LOCAL,
                                         netRegPosition);
                netRegPosition = net->networkRequest(SERVER_IP2,pWhatToWrite); //write xor
            }
            break;

        case RAID10:
            //loop y copiado, min 4 servers
            if(location == LOCAL){
                netRegPosition = net->networkRequest(SERVER_IP2, pWhatToWrite);
                net->networkRequest(SERVER_IP3, pWhatToWrite);
                FS->updateDatabaseStruct(pFileName, &SERVER_IP1, netRegPosition);
            }
            else if(location == SERVER_IP2 ||
                    location == const_cast<char*> (NI)){

                netRegPosition = FS->writeNewLineToFile(*pFileName, pWhatToWrite,
                                                        pColumnNam);
                net->networkRequest(SERVER_IP1, pWhatToWrite);
                FS->updateDatabaseStruct(pFileName, (string*) LOCAL,
                                         netRegPosition);
            }
            break;

        default:
            FS->writeNewLineToFile(*pFileName , pWhatToWrite , pColumnNam);
            FS->updateDatabaseStruct(pFileName, (string*)LOCAL, netRegPosition);
    }
}

string raidManager::retrieveRegister(string* pFileName , int pRow){
    string location = getLatestRegistryLocation(pFileName);

    if(location == LOCAL){
        FS->readFromFile(*pFileName , ZE_ROW, pRow);
    }
    if (location == SERVER_IP1){
        net->networkRequest(SERVER_IP1, pWhatToWrite);
    }
    if (location == SERVER_IP2){
        net->networkRequest(SERVER_IP2, pWhatToWrite);
    }
    if (location == SERVER_IP3){
        net->networkRequest(SERVER_IP3, pWhatToWrite);
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
