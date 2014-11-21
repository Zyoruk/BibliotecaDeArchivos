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
//        net->client->link(PORTNO, SERVER_IP1, DATAAAAAAA);
    }

    if (*raidMode >= 5){
//        net->client->link(PORTNO, SERVER_IP2, DATAAAAAAA);
    }

    if (*raidMode == 10){
//        net->client->link(PORTNO, SERVER_IP3, DATAAAAAAA);
    }
}

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
//                netRegPosition = net->client->link(PORTNO, SERVER_IP1, DATAAAAAAAA);
                FS->updateDatabaseStruct(pFileName, &SERVER_IP1 , netRegPosition);
            }
            else if(location == SERVER_IP1 ||
                    location == const_cast<char*> (NI)){

                netRegPosition = FS->writeNewLineToFile(*pFileName, pWhatToWrite,
                                                        pColumnNam);
                FS->updateDatabaseStruct(pFileName, (string*)LOCAL,
                                         netRegPosition);
            }

        case RAID1:
            //todo local y copiado al S1, min 2 servers
            netRegPosition = FS->writeNewLineToFile(*pFileName, pWhatToWrite,
                                                    pColumnNam);
//            net->client->link(PORTNO, SERVER_IP1, DATAAAAAAAA);
            FS->updateDatabaseStruct(pFileName, (string*)LOCAL, netRegPosition);

        case RAID10:
            //loop y copiado, min 4 servers
            if(location == LOCAL){
//                netRegPosition = net->client->link(PORTNO, SERVER_IP2, DATAAAAAAAA);
//                net->client->link(PORTNO, SERVER_IP3, DATAAAAAAAA);
                FS->updateDatabaseStruct(pFileName, &SERVER_IP1, netRegPosition);
            }
            else if(location == SERVER_IP2 ||
                    location == const_cast<char*> (NI)){

                netRegPosition = FS->writeNewLineToFile(*pFileName, pWhatToWrite,
                                                        pColumnNam);
//                net->client->link(PORTNO, SERVER_IP1, DATAAAAAAAA);
                FS->updateDatabaseStruct(pFileName, (string*) LOCAL,
                                         netRegPosition);
            }

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
//        net->client->link(PORTNO, SERVER_IP1, DATAAAAAAAA);
    }
    if (location == SERVER_IP2){
//        net->client->link(PORTNO, SERVER_IP2, DATAAAAAAAA);
    }
    if (location == SERVER_IP3){
//        net->client->link(PORTNO, SERVER_IP3, DATAAAAAAAA);
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
