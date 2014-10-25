#include <iostream>
#include <fstream>
#include "konstants.h"
#include <limits>
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

string& createNewFile(string newFileName){
    string newFileDir = K->DIRFILE;
    newFileDir.append(newFileName);
    //cout << newFileDir << endl;
    return &newFileDir;
}

string& toChar(int *toChar){
    string s;
    stringstream out;
    out << *toChar;
    s = out.str();    
    return &s;
}

void checkSize(string* add, int count){
    string hola = "0";
    string tmp;

    for (int a = 1 ; a < count ; a++){
        if((tmp.length() + *add.length()) == count){
            break;
        }
        tmp.append(hola);
    }
    tmp.append(*add);
    add = tmp;
}

string& intToChar(int *metadata){
    int ch;
    string tmp;
    while (metadata != 0){
        ch = metadata % 10;
        metadata = metadata / 10;
        tmp.append(*(toChar(ch)));
    }
    return &tmp;
}


void createTable(int *registerSize, int* columnSizes, int *columns){
    cout << "**** Insert name for new table ***" << endl;
    cin >> newFileName;
    ofstream database ((*createNewFile(newFileName)).c_str() , ios::trunc); //append database name to path and creates it there.
    if(database.is_open())
        cout << "****Database succesfully created***" << endl;
    else
        cout << "****Database could not be created***" << endl;

    if(registerSize >= K->MAX_REGISTER_SIZE)
        cout << "Error: Register size beyond max size" << endl;
    else
    {
        database.seekp(K->METADATA_SIZE_ADDRESS , ios::beg);
        string* add = toChar(&registerSize);]
        checkSize(add,K->DEFAULT_REGISTER_SIZE);
        database << *add;
    }

    for (int i = 0 ; i < columns ; i++)
    {
        add = toChar(columnSizes[i]);
        checkColSize(add,K->DEFAULT_COLUMN_SIZE);
        database << *add;
    }

    database.seekp(0, ios::end);
    int meta = database.tellp();
    string metadata = *(intToChar(&meta));
    const char *p = metadata.c_str();
    while (*p != '\0')
        database.put( *p++ );

    database.close();
}

int& getDataInit(string *newFileName){

}

void updateField(){
    ofstream file (K->DIRFILE.c_str() , ios::app);
    if(data.size() <= 64){

    }
    file.close();
}

void readField(){
    ifstream file (K->DIRFILE.c_str());
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

