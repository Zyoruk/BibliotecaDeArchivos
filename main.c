#include <stdio.h>
#include "biblioteca.h"
int main(void)
{
//    crear_bib("Test2.bin" , "wb");
//    int FH = abrir_bib("Test2.bin" , 0);

//    cerrar_bib(FH);
    FILE* file = fopen("Test3.txt" , "wb+");
    int ptr = 999;
    fwrite(&ptr , sizeof(ptr),1,file);
//    c_1->crear_bibptr("Test1.bin","rb");
    return 0;
}

