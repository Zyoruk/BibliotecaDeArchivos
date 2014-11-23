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

FSQLServerFileSystem* filesystem = new FSQLServerFileSystem();
void test0(){
    cout << "*** Bienvenido a FSQL Server ***" << endl;
    cout << "\n";
    int regSize;
    regSize = 352;
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
    string file ="Test9";

    int* test;
    int temp = 00 ;
    test = &temp;
    cout << test <<endl;
    //filesystem->createNewFile(&regSize ,&columnSais, &cNames ,&file, test);
}

void test1(){

    string fileName = "Test9";
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

    filesystem->writeNewLineToFile(fileName , &cData, &cPos);
    filesystem->writeNewLineToFile(fileName , &cData, &cPos);
//    filesystem->writeNewLineToFile(fileName , &cData, &cPos);
}

void test2(){
    string fileName = "Test9";
    array<char*> field = filesystem->readFromFile(fileName , "Nombre" , 1);
    for (int i = 0 ; i < field.getLenght() ; i++){
        cout << field[i] << " ";
    }
}

void test3(){
    filesystem->update("Daniel", "Test9" , 1 , "Nombre");
    filesystem->update("Jenkins", "Test9" , 1 , "Apellido");;
    filesystem->update("Josafat", "Test9" , 3 , "Nombre");
    filesystem->update("Vargas","Test9" , 3 , "Apellido");
}

void test4(){
    array<char*> test4 =filesystem->readFromFile("Test9" , 0 , 1);
    for (int i = 0 ; i < test4.getLenght();i++){
        cout << test4[i] <<endl;
    }
}

void test5(){
    filesystem->updateColumn("Masculino","","Test9","Sexo");
}

void test6(){
    array<char*> arrTmp = filesystem->readFromFile("Test9" , "Apellido" , 0);
    for (int i = 0; i < arrTmp.getLenght();i++)cout << arrTmp[i] <<endl;
}

void test7(){
    filesystem->backUpFile("Test9");
}

void test8(){
    filesystem->restoreFile("Test9");
}

void test9 (int pColumnSize){
    fstream file("../FSQL/backups/backupTest9");
//    void * pterFile = &file;
//    char*  pterFile2 = (char*)pterFile;
    char* alloc = (char*)calloc(pColumnSize,sizeof(char));
           file.read(alloc,pColumnSize);
           for (int i = 0 ; i < pColumnSize ;i++){

               (cout << *(alloc + i));
           }
}


void test10(){
    filesystem->deleteData("Test9" , "Nombre" , "Luis");
}

void test11(){
    permissionsLayer pL = permissionsLayer();
    pL.createUser("Luis" , "123123");
    pL.grantPermission("Luis" , "read" , "Test9");
//    pL.revokePermission("Luis" , "read" , "Test9");
    pL.checkUser("Luis");
//    pL.dropUser("Luis");
//    cout << pL.checkUser("Luis") << endl;
    user tester = pL.loadUser("Luis");
    tester.CanRead("Test9");
}

void test12(){
//    string command = "GRANT write ON Test9 TO Luis";
//    string command = "CREATE USER Daniel PASSWORD 12313";
    string command = "";
    user currentUser;
    decriptor* dekrpt = new decriptor(command , &currentUser, true,true);
}
