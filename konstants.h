#ifndef KONSTANTS_H
#define KONSTANTS_H
#include <string>

using namespace std;

class konstants
{
public:
    konstants();
    const string NO_EXISTANT_FILE = "NEF";
    const string NO_EXISTANT_DALTA = "NED";
    const string INVALID_VALUES = "IV";
    const string EMPTY_STRING = "";
    const string DIRFILE = "../FSQL/";
    const string TRIPLE_NULL = "000";
    const string OVER_WRITE = "Do you want to overwrite the existant file ?";
    const string FILE_NOT_CREATED = "File was not created.";
    const string BACKUP_STRING = "backup";

    static const int ZE_ROW = 0;
    static const int ONE_BYTE = 1;
    static const int DEFAULT_COLUMN_SIZE = 3;
    static const int DEFAULT_REGISTER_SIZE = 4;
    static const int REGISTER_SIZE_ADDRESS = 3;
    static const int MAX_REGISTER_SIZE = 999;
    static const int METADATA_SIZE = 3;
    static const int METADATA_COLUMN_START = 7;

    static const char NULL_CHAR = '*';
    static const char SINGLE_NULL = '0';
    static const char _Y_ = 'Y';
    static const char _N_ = 'N';
};

#endif // KONSTANTS_H
