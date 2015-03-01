#ifndef FILESYSTEM_H
#define FILESYSTEM_H

bool createNewFile(array<int>* pColumnSizes, array<char*>* pColumnNames,
				   string* pFile, int* raidMode);
bool writeNewLineToFile(string* pFileName , array<char*>* pWhatToWrite,
						array<char*>* pColumnNam);
bool removeFile(string pFileName);
bool update (string pData , string pFileName,  int pRow, string pColumn);
array<char*> readFromFile(string pFileName , string pColumn, int pRow);
bool backUpFile (string pFileName);
bool restoreFile(string pFileName);
bool deleteData ( string pFilename , string pColumnName , string pData);
bool backupExists(string pBackUp);
bool updateColumn(string newData,string pToCompare, string pFile, string pCName);
void updateDatabaseStruct(string* pFile, string ip, int pos);
int getRaidMode(string* pFile);
string readDataLocation(string* pFile);
bool fileExists(string *pFile);
readfile* RF;
writefile* WF;


#endif // FILESYSTEM_H
