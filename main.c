#include <stdio.h>
#include "biblioteca.h"

void test1 (){
    //    crear_bib("Test2.bin" , "wb");
    //    int FH = abrir_bib("Test2.bin" , 0);

    //    cerrar_bib(FH);
        FILE* file = fopen("Test3.txt" , "w+");
        struct componente_struct ptr;
        ptr.comp_nom = "Hola";
        ptr.rango[0] = 1 ;
        ptr.rango[1] = 2;
        ptr._lleno = TRUE;

        fwrite(&(ptr.comp_nom) , sizeof(ptr),1,file);
    //    c_1->crear_bibptr("Test1.bin","rb");
}

int main(void)
{

    return 0;
}

