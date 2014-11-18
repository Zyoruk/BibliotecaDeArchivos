#ifndef COMPRESSFILE_H
#define COMPRESSFILE_H
#include <string>
class compressString
{
public:
    compressString();
private:
    std::string _compressedString;
    std::string compress(std::string pString);
};

#endif // COMPRESSFILE_H
