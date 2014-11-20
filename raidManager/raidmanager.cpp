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

    switch(raidMode){
        case RAID0:
            FS->createNewFile(pRegisterSize, pColumnSizes, pColumnNames, pFile);
            net->client->link(PORTNO, ip1, DATAAAAAAA);


        case RAID1:
            FS->createNewFile(pRegisterSize, pColumnSizes, pColumnNames, pFile);
            net->client->link(PORTNO, ip1, DATAAAAAAA);

        case RAID10:
            FS->createNewFile(pRegisterSize, pColumnSizes, pColumnNames, pFile);
            net->client->link(PORTNO, ip1, DATAAAAAAA);
            net->client->link(PORTNO, ip2, DATAAAAAAA);
            net->client->link(PORTNO, ip3, DATAAAAAAA);

        default:

    }
}

bool raidManager::saveRegister(string* pFileName ,
                               array<char*>* pWhatToWrite,
                               array<char*>* pColumnNam){

    int raid = getRaidMode();
    char*[] location = getLatestRegistryLocation(pFileName);

    if (location == ""){
        location = NI;
    }

    switch(raid){
        case RAID0:
            //loop de servers, min 2 servers
            if(location == LOCAL){
                net->client->link(PORTNO, ip1, DATAAAAAAAA);
            }
            else if(location == (S1 || NI)){
                FS->writeNewLineToFile(pFileName, pWhatToWrite,pColumnNam);
            }

        case RAID1:
            //todo local y copiado al S1, min 2 servers
            FS->writeNewLineToFile(pFileName, pWhatToWrite,pColumnNam);
            net->client->link(PORTNO, ip1, DATAAAAAAAA);

        case RAID10:
            //loop y copiado, min 4 servers
            if(location == LOCAL){
                net->client->link(PORTNO, ip2, DATAAAAAAAA);
                net->client->link(PORTNO, ip3, DATAAAAAAAA);
            }
            else if(location == (S2 || NI)){
                FS->writeNewLineToFile(pFileName, pWhatToWrite,pColumnNam);
                net->client->link(PORTNO, ip1, DATAAAAAAAA);
            }

        default:
            cout << "*** No monkeys allowed ***" << endl;
    }
}

string raidManager::retrieveRegister(string pFileName , int pColumn, int pRow){
    char*[] location = getLatestRegistryLocation(pFileName);

    if(location == LOCAL){
        FS->readFromFile(pFileName , pColumn, pRow);
    }
    if (location == S1){
        net->client->link(PORTNO, ip1, DATAAAAAAAA);
    }
    if (location == S2){
        net->client->link(PORTNO, ip2, DATAAAAAAAA);
    }
    if (location == S3){
        net->client->link(PORTNO, ip3, DATAAAAAAAA);
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
