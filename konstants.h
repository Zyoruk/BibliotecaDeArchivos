#ifndef KONSTANTS_H
#define KONSTANTS_H
#include <string>

using namespace std;

class konstants
{
public:
    konstants();
    const int ZE_ROW = 0;
    const int ONE_BYTE = 1;
    const string EMPTY_STRING = "";
    const string DIRFILE = "../FSQL/";
    const int DEFAULT_COLUMN_SIZE = 3;
    const int DEFAULT_REGISTER_SIZE = 4;
    const int REGISTER_SIZE_ADDRESS = 3;
    const int MAX_REGISTER_SIZE = 999;
    const int METADATA_SIZE = 3;
};

#endif // KONSTANTS_H
