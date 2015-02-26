#ifndef LIBMANAGER_H
#define LIBMANAGER_H
#include "SimpleList.h"

class libManager
{

public:    
    //Methods
    libManager();

private:    
    typedef const char mode;
    //Variables
    SimpleList<biblioteca>* _libList;

    //Methods
    int abrir_bib (const char *pPathname, int pFlags);
    int crear_bib (const char *pPathname, mode pMode);
    int cerrar_bib (int pBib);
};

#endif // LIBMANAGER_H
