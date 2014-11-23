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

int main(int argc , char* argv[])
{/*
    if (argc < TWO_BYTES)
        exit(0);
    FSQL_plus(argv[1]);*/
    FSQL_plus("1");
    return 0;
}
