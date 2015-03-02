#include <stdio.h>
#include "filesystem.h"

void test1 (){
    //    crear_bib("Test2.bin" , "wb");
    //    int FH = abrir_bib("Test2.bin" , 0);

    //    cerrar_bib(FH);
        FILE* file = fopen("Test3.txt" , "w+");
        componente_struct ptr;
        ptr.comp_nom = "Hola";
        ptr.rango[0] = 1 ;
        ptr.rango[1] = 2;
        ptr._lleno = TRUE;

        fwrite(&(ptr.comp_nom) , sizeof(ptr),1,file);
    //    c_1->crear_bibptr("Test1.bin","rb");
}

int main(void)
{
    FILE* bib ;
    bib = fopen("Test14.bin" , "wb+");
//    char ptr[] = "Luis";
    int ptr [5]= {3, 4,5 ,6 ,7} ;
    fwrite(&ptr , sizeof(ptr[0]) , 5, bib);
    fclose(bib);
    fopen("Test14.bin" , "rb");
    int* ptr2 = malloc ( 100);
    fread(ptr2 , sizeof(ptr2[0]) , 5, bib);
    fclose(bib);

    printf ( "%d\n" , ptr2[1]);

    fopen("Test14.bin" , "ab");
    int ptr3 [5] = {12, 13, 14 ,15 ,16};
    fwrite(&ptr3 , sizeof(ptr3[0]) , 5, bib);
    fclose(bib);
    fopen("Test14.bin" , "rb");
    int* ptr4 = malloc ( 100);
    fseek(bib , sizeof(ptr3) , SEEK_SET);
    fread(ptr4 , sizeof(ptr3[0]) , 5, bib);
    fclose(bib);

    printf ( "%d\n" , ptr4[1]);
    return 0;
}

