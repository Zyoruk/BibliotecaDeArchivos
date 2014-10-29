#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "testclass.h"
#include "konstants.h"
#include "array/array.h"
#include "writefile.h"
#include "readfile.h"

//#define STR(x) #x << '=' << x

using namespace std;

konstants* K;
readfile* RD;
writefile* WR;

void setup(){
    K = new konstants();
    RD = new readfile();
    WR = new writefile();
}

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
    WR->createTable(&regSize ,&columnSais, &cNames ,&file);
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

    array<int> cPos(2);
    cPos[0] = 1;
    cPos[1] = 2;

    WR->writeRegister(fileName, &cData, &cPos);
    WR->writeRegister(fileName, &cData, &cPos);
    WR->writeRegister(fileName, &cData, &cPos);
}

void test2(){
    string fileName = "Test8";
    string field = RD->readField(fileName.c_str(),1 ,1);
}

void test3(){
    WR->updateField("Daniel", "Test8" , 1 , 1);
    WR->updateField("Jenkins", "Test8" , 1 , 2);
}

void test4(){
    array<char*> test4 = RD->readRegistry("Test8" , 1);
    for (int i = 0 ; i < test4.getLenght();i++){
        cout << test4[i] <<endl;
    }
}

void test5(){
    WR->updateColumn("Simon_Barrantes" ,"Angel","Test9","Apellido");
}

void test6(){
    array<char*> arrTmp = RD->readColumn("Test9" , "Apellido");
    for (int i = K->ZE_ROW ; i < arrTmp.getLenght();i++)cout << arrTmp[i] <<endl;
}

int main()
{
    testClass test;
    test.test6();
    setup();
    test1();
    return 0;
}

