#include <iostream>
#include <fstream>
#include "array/array.h"

using namespace std;

fstream file_COL;

void writeColumnNames(string* fileName, array<string>* columnNames){
    string K = "Columns";
    string path = *fileName;
    path.append(K);
    array<string> columnNames2Use = *columnNames;

    file_COL.open(path.c_str());
    for (int i = 0 ; i < columnNames->getLenght() ; i++){
        file_COL << columnNames2Use[i];
        if ( i < (columnNames->getLenght() - 1))
            file_COL << '/n';
    }
    file_COL.close();
}

//La variable de regreso es eliminada
int getColumnNumber(string* fileName ,string* columnName){
    string K = "Columns";
    string path = *fileName;
    string COLNAME;
    path.append(K);
    int i = 0;

    int columnNumber = -2;
    file_COL.open(path.c_str());

    while (! file_COL.eof() )
    {
        getline(file_COL,COLNAME);
        if ( *columnName == COLNAME)
            columnNumber = i;
        i++;
    }
    return columnNumber;
}

//La variable de regreso es eliminada
string getColumnName(string* fileName ,int* columnNumber){
    string K = "Columns";
    string path = *fileName;
    path.append(K);
    int i = 0;

    string columnName = "NOT FOUND";
    file_COL.open(path.c_str());

    while (i != *columnNumber)
    {
        getline(file_COL, columnName);
        if(file_COL.eof())
            break;
    }
    return columnName;
}

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

