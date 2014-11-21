#include "raidmanager.h"

raidManager::raidManager()
{
    this->ip1 = SERVER_IP1;
    this->ip2 = SERVER_IP2;
    this->ip3 = SERVER_IP3;
    this->FS = new FSQLServerFileSystem();
    this->net = new networkAccess(mode);
}

bool raidManager::createNewFile(int* pRegisterSize, array<int>* pColumnSizes,
                   array<char*>* pColumnNames, string* pFile, int raidMode){

    FS->createNewFile(pRegisterSize, pColumnSizes, pColumnNames, pFile);

    if (raidMode >= 0){
        net->client->link(CLIENT_PORTNO, ip1, DATAAAAAAA);
    }

    if (raidMode >= 5){
        net->client->link(CLIENT_PORTNO, ip2, DATAAAAAAA);
    }

    if (raidMode == 10){
        net->client->link(CLIENT_PORTNO, ip3, DATAAAAAAA);
    }
}

bool raidManager::storeRegister(string* pFileName ,
                               array<char*>* pWhatToWrite,
                               array<char*>* pColumnNam){

    int netRegPosition;
    int raid = getRaidMode();
    char*[] location = getLatestRegistryLocation(pFileName);

    if (location == ""){
        location = NI;
    }

    switch(raid){
        case RAID0:
            //loop de servers, min 2 servers
            if(location == LOCAL){
                netRegPosition = net->client->link(CLIENT_PORTNO, ip1, DATAAAAAAAA);
                FS->updateDatabaseStruct(string* pFileName, ip1,
                                         netRegPosition);
            }
            else if(location == (ip1 || NI)){
                netRegPosition = FS->writeNewLineToFile(pFileName, pWhatToWrite,
                                                        pColumnNam);
                FS->updateDatabaseStruct(string* pFileName, LOCAL,
                                         netRegPosition);
            }

        case RAID1:
            //todo local y copiado al S1, min 2 servers
            netRegPosition = FS->writeNewLineToFile(pFileName, pWhatToWrite,
                                                    pColumnNam);
            net->client->link(CLIENT_PORTNO, ip1, DATAAAAAAAA);
            FS->updateDatabaseStruct(string* pFileName, LOCAL, netRegPosition);

        case RAID10:
            //loop y copiado, min 4 servers
            if(location == LOCAL){
                netRegPosition = net->client->link(CLIENT_PORTNO, ip2, DATAAAAAAAA);
                net->client->link(CLIENT_PORTNO, ip3, DATAAAAAAAA);
                FS->updateDatabaseStruct(string* pFileName, ip1, netRegPosition);
            }
            else if(location == (ip2 || NI)){
                netRegPosition = FS->writeNewLineToFile(pFileName, pWhatToWrite,
                                                        pColumnNam);
                net->client->link(CLIENT_PORTNO, ip1, DATAAAAAAAA);
                FS->updateDatabaseStruct(string* pFileName, LOCAL,
                                         netRegPosition);
            }

        default:
            FS->writeNewLineToFile(pFileName , pWhatToWrite , pColumnNam);
            FS->updateDatabaseStruct(string* pFileName, LOCAL, netRegPosition);
    }
}

string raidManager::retrieveRegister(string pFileName , int pColumn, int pRow){
    char*[] location = getLatestRegistryLocation(pFileName);

    if(location == LOCAL){
        FS->readFromFile(pFileName , pColumn, pRow);
    }
    if (location == ip1){
        net->client->link(CLIENT_PORTNO, ip1, DATAAAAAAAA);
    }
    if (location == ip2){
        net->client->link(CLIENT_PORTNO, ip2, DATAAAAAAAA);
    }
    if (location == ip3){
        net->client->link(CLIENT_PORTNO, ip3, DATAAAAAAAA);
    }

}

bool raidManager::dataRecovery(char* database){
    if(getRaidMode(&database) != 05){
        cout << "*** Non recovery raid mode ***";
        return false;
    }
}

string raidManager::getLatestRegistryLocation(string* pFile, int pRow){
    string location = FS->RF->readDataLocation(pFile , pRow);
    return location;
}
