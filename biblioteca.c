#include "biblioteca.h"
#define FILE_ERROR -1
#define FILE_CREATED 0

int crear_bib(char *pathname ,char *mode){

    FILE *newBib;
    newBib = fopen(pathname , mode);

    if (newBib == NULL){
        printf ( " Failed.");
        return FILE_ERROR;
    }else{
        printf ( "Succesful.");
        return  FILE_CREATED;
    }
}
