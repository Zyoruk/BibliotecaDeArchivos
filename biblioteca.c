#include "biblioteca.h"
#include <fcntl.h>
#define ERROR -1
#define SUCCESS 0
#define WRONG_FLAG "wf"
#define LIB_ERROR "404: Lib not found."

typedef const char* mode ;
int file_handle;
FILE *newBib;

int crear_bib(const char *pathname ,mode pmode){

    newBib = fopen(pathname , pmode);

    if (newBib == NULL){
        printf ( " Failure.\n");
        return ERROR;
    }else{
        printf ( "Succesful.\n");
        return  SUCCESS;
    }
}

int abrir_bib(const char *pathname, int flags){

    file_handle = open(pathname ,flags);
    if (file_handle == ERROR){ printf (LIB_ERROR);}

    return file_handle;
}

int cerrar_bib(int bib_fd){
    if ( bib_fd == file_handle){
        fclose (newBib);
        printf ( "Succesful.\n");
        return SUCCESS;
    }else{
        printf("Failure. \n");
        return ERROR;
    }
}

//const char* flags_val(int flags){
//    switch (flags){
//        case 0 :
//            return "rb";
//        case 1:
//            return "wb";
//        case 2:
//            return "ab";
//        default:
//            return WRONG_FLAG;
//    }
//}
