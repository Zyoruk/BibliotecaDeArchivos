#ifndef HARD_DRIVE_H
#define HARD_DRIVE_H

bool createNewFile(array<int>* pColumnSizes, array<char*>* pColumnNames,
				   string* pFile, int* raidMode);
bool writeNewLineToFile(string* pFileName , array<char*>* pWhatToWrite,
						array<char*>* pColumnNam);
bool removeFile(string pFileName);

array<char*> readFromFile(string pFileName , string pColumn, int pRow);

bool exportComponent(string pFileName);

bool update (string pData , string pFileName,  int pRow, string pColumn);

bool restoreFile(string pFileName);

bool fileExists(string *pFile);

bool deleteData(string pFileName, string pColumnName, string pData);

bool updateColumn(string newData, string pToCompare, string pFile,
                  string pCName);

#endif // HARD_DRIVE_H
