#ifndef KONSTANTS_H
#define KONSTANTS_H
#include <string>

using namespace std;

class konstants
{
public:
    konstants();
    static const int ZE_ROW = 0;
    static const int ONE_BYTE = 1;
    const string EMPTY_STRING = "";
    const string DIRFILE = "../FSQL/databases/";
    const string BACK_UPS_DIR = "../FSQL/backups/";
    static const int DEFAULT_COLUMN_SIZE = 3;
    static const int DEFAULT_REGISTER_SIZE = 4;
    static const int REGISTER_SIZE_ADDRESS = 3;
    static const int MAX_REGISTER_SIZE = 999;
    static const int METADATA_SIZE = 3;
    static const int METADATA_COLUMN_START = 7;
    const char NULL_CHAR = '*';
    const string TRIPLE_NULL = "000";
    const char SINGLE_NULL = '0';
    const string NO_EXISTANT_FILE = "NEF";
    const char _Y_ = 'Y';
    const char _N_ = 'N';
};

#endif // KONSTANTS_H
