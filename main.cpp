#include <iostream>
#include <fstream>
#include "konstants.h"
#include <limits>
#include <vector>
//#define STR(x) #x << '=' << x

using namespace std;

konstants* K;
int option;
string data;
string newFileName;

void setup()
{
    K = new konstants();
}

fstream& createNewFile(string newFileName){
    string newFileDir = K->dirFile;
    newFileDir.append(newFileName);
    cout << newFileDir << endl;
    ofstream database (newFileDir.c_str() , ios::trunc);
    if(database.is_open())
        cout << "****Database succesfully created***" << endl;
    else
        cout << "****Database could not be created***" << endl;
    return &database;
}

 void createTable(string &ColumnNames, int &ColumnSizes){
     cout << "****Name for new table***" << endl;
     cin >> newFileName;
     ofstream* database = createNewFile(newFileName);
     for_each

 }

void updateField(){
    ofstream file (K->dirFile.c_str() , ios::app);
    if(data.size() <= 64){

    }
    file.close();
}

void readField(){
    ifstream file (K->dirFile.c_str());
    char character;

    int row = (6 - 1) * 128;
    //show name
    file.seekg(row);
    while (file.tellg() < (64 * row)){
        character = file.get();
        if( character == '*'){
            cout << ' ' << endl;
            break;
        }
        cout << character;
    }

    cout << "------------------------------------------" << endl;

    //show lastname
    file.seekg(row + 64, ios::beg);
    while (file.tellg() < (128 * row)){
        character = file.get();
        if( character == '*'){
            cout << ' ' << endl;
            break;
        }
        cout << character;
    }

    /*
    //show adress
    file.seekg(row + 128, ios::beg);
    while (file.tellg() < 256 * row){
        character = file.get();
        if( character == '*'){
            cout << ' ' << endl;
            break;
        }
        cout << number;
    }

    //show country
    file.seekg(row + 256, ios::beg);
    while (file.tellg() < 320 * row){
        character = file.get();
        if( character == '*'){
            cout << ' ' << endl;
            break;
        }
        cout << number;
    }

    //show line
    string t;
    while(getline (file,t)){
        if(t != "\n"){
            cout << t << endl;
        }
    }*/
}

int main()
{
    setup();
    cout << "****Field operations***" << endl;
    cout << "****1. Edit ****" << endl;
    cout << "****2. Read ****" << endl;

    cin >> option;
    switch (option) {
        case 1:
        {
            updateField();
            break;
        }
        case 2:
        {
            readField();
            break;
        }
        default:
        {
            cout << "The cat said miau...\n";
            break;
}
    }

    return 0;
}

