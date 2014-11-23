#ifndef FSQLSERVERFILESYSTEM_H
#define FSQLSERVERFILESYSTEM_H
#include "array/array.h"
//#include "konstants.h"
#include "readfile.h"
#include "writefile.h"
#include <string.h>

using namespace std;

/*!
 * \brief The FSQLServerFileSystem class This class provides the interface to
 * interact with the files.
 */
class  FSQLServerFileSystem
{
public:
    /*!
     * \brief FSQLServerFileSystem loads the needed setup of the class.
     */
    FSQLServerFileSystem();

    /*!
     * \brief createNewFile checks if the file already exists and demand the creation
     * of the file.
     * \param pRegisterSize Declares the size of each register contained into the file.
     * \param pColumnSizes is the array that stores the corresponding sizes of each column.
     * \param pColumnNames stores the name of each column.
     * \param pFile is the name of the new file.
     * \return  boolean if the operation succeded.
     */
    bool createNewFile(array<int>* pColumnSizes, array<char*>* pColumnNames,
                       string* pFile, int* raidMode);

    /*!
     * \brief writeNewLineToFile demands that a new register must be created into the
     * specified file .
     * \param pFileName is the name of the file.
     * \param pWhatToWrite array that contains the data to be written.
     * \param pColumnNam array that contains the corresponding names of the
     * columns where the pWhatToWrite data is going to be placed.
     * \return  true if writing the line was succesful.
     */
    bool writeNewLineToFile(string* pFileName , array<char*>* pWhatToWrite,
                            array<char*>* pColumnNam);

    /*!
     * \brief removeFile removes a file from the filesystem
     * \param pFileName name of the file.
     * \return true if the removal was succesful
     */
    bool removeFile(string pFileName);

    /*!
     * \brief update updates the data stored at some field.
     * \param pData data to be written.
     * \param pFileName name of the file.
     * \param pRow number of rows .
     * \param pColumn number of column to write the data.
     * \return
     */
    bool update (string pData , string pFileName,  int pRow, string pColumn);

    /*!
     * \brief readFromFile reads data specified by the parameters. If the column is zero
     * then all the data at the specified column is going to be selected.
     * \param pFileName name of the file to be read.
     * \param pColumn number of column to read
     * \param pRow number of row to read|
     * \return an array containing the data.
     */
    array<char*> readFromFile(string pFileName , string pColumn, int pRow);

    /*!
     * \brief backUpFile back ups an existant file.
     * \param pFileName name of the file to be backed up.
     * \return
     */
    bool backUpFile (string pFileName);

    /*!
     * \brief restoreFile restores a file from an existing back up file.
     * \param pFileName file name to be restored.
     * \return
     */
    bool restoreFile(string pFileName);

    /*!
     * \brief deleteData remove a register containing the data.
     * \param pFilename
     * \param pColumnName
     * \param pData
     * \return true if it was able to delete the data.
     */
    bool deleteData ( string pFilename , string pColumnName , string pData);

    /*!
     * \brief backupExists checks if the back up file exists.
     * \param pBackUp file name .
     * \return  true if the back up was created.
     */
    bool backupExists(string pBackUp);

    /*!
     * \brief updateColumn updates a column depending on the parameters. From a column replace
     * the old data with the new onw
     * \param newData data to be written
     * \param pToCompare pDataToBreplaced
     * \param pFile file name
     * \param pCName column number
     * \return true it it was possible.
     */
    bool updateColumn(string newData,string pToCompare, string pFile, string pCName);

    void updateDatabaseStruct(string* pFile, string ip, int pos);

    int getRaidMode(string* pFile);

    string readDataLocation(string* pFile);

protected:
//    array<char*> _FilesMetaData;
    bool fileExists(string *pFile);
    readfile* RF;
    writefile* WF;
};

#endif // FSQLSERVERFILESYSTEM_H
