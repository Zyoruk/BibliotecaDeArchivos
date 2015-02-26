#include <stdio.h>
#include "biblioteca.h"
int main(void)
{
    crear_bib("Test2.bin" , "wb");
    int FH = abrir_bib("Test2.bin" , 0);
    cerrar_bib(FH);
    return 0;
}

