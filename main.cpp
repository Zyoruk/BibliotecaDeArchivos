#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "fsqlserverfilesystem.h"
#include "permissionslayer.h"
#include "user.h"
#include "decriptor.h"
#include "network/tcpserver.h"
#include "tests.h"
#include "raidManager/raidmanager.h"

//#define STR(x) #x << '=' << x

using namespace std;

/*!
 * \brief serverInstance The program has to be instanced as a server. This will
 * force it to listen for a command.
 */
void serverInstance(){
        TCPServer* server = new TCPServer();
        server->receive();

}

/*!
 * \brief clientInstance will be sending the commands to the servers.
 */
void clientInstance(){
    permissionsLayer* pL = new permissionsLayer();

    cout << "Enter username : " <<endl;
    string username = "";
    std::getline(std::cin , username);
    cout << "Enter password : " << endl;
    string Password = "";
    std::getline(std::cin , Password);
    user currentUser = user() ;
    bool root;
    if (username == "root" && Password == "root"){
        root= true;
        string command;
        cout << "Enter command:" <<endl;
        std::getline(std::cin , command);
        decriptor* dekrpt = new decriptor(command , &currentUser, root, false);
    }else{
        root = false;
        if (pL->checkPass(username, Password)){
            currentUser = pL->loadUser(username);
            string command;
            cout << "Enter command:" <<endl;
            cin >> command;
            decriptor* dekrpt = new decriptor(command , &currentUser, root, false);
        }else{
            cout << INVALID_VALUES << endl;
            free(&currentUser);
            free (&Password);
            free(&username);
            free(pL);
            free(&root);
            serverInstance();
        }
    }
}

void FSQL_plus (string mode ){

    int modeInt = atoi(mode.c_str());
    switch(modeInt){
    case ZE_ROW:
        serverInstance();
    case ONE_BYTE:
        clientInstance();
    }
}

void writeAsRM(){
    raidManager* raid = new raidManager();
    array<int> columnSais (5);
    columnSais[0] = 64;
    columnSais[1] = 64;
    columnSais[2] = 128;
    columnSais[3] = 64;
    columnSais[4] = 32;
    array<char*> cNames(5);
    cNames[0] = "Nombre";
    cNames[1] = "Apellido";
    cNames[2] = "Direccion";
    cNames[3] = "Telefono";
    cNames[4] = "Sexo";
    string file ="Agenda";
    int raidMode = -1;
    raid->createNewFile(&columnSais, &cNames, &file, &raidMode, &file);
}

void writeREG(){
    raidManager* raid = new raidManager();
    string fileName = "Agenda";
    array<char*> cData(2);
    string nameToAdd = "Luis";
    string lastNameToAdd = "Simon Barrantes";
    char *s2 = new char[nameToAdd.size()+1];
    char *s3 = new char[lastNameToAdd.size()+1];
    strcpy(s2, nameToAdd.c_str());
    strcpy(s3, lastNameToAdd.c_str());
    cData[0] = s2;
    cData[1] = s3;

    array<char*> cPos(2);
    cPos[0] = "Nombre";
    cPos[1] = "Apellido";

//    raid->storeRegister(fileName , &cData, ,);
}

int main(int argc , char* argv[])
{/*
    if (argc < TWO_BYTES)
        exit(0);
    FSQL_plus(argv[1]);*/
    FSQL_plus("1");
//    writeAsRM();
    return 0;
}
