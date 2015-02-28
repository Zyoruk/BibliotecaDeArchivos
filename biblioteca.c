#include "biblioteca.h"
#include <fcntl.h>


typedef const char* mode ;
int file_handle;
FILE *newBib;

//int crear_bib(const void* miInstancia ,const char *pathname ,mode pmode){
int crear_bib(const char *pathname ,mode pmode){
/*hay que tener una lista que maneje la cantidad de bibliotecas
 * Cuando se hace una nueva habrá que agregarla a un arreglo.
 * biblioteca newBib;
 * newBib->bibNom = pathname;
 * newBib->mode = pmode;
 * bib_list[count + 1] = newBib;
 * NOTA: se podría hacer un arreglo de int y lo que se guarde sea un puntero. ??
 * */
    newBib = fopen(pathname , pmode);

    if (newBib == NULL){
        printf ( "Failure.\n");
        return ERROR;
    }else{
        printf ( "Succesful.\n");
        return  SUCCESS;
    }
}

int abrir_bib(const char *pathname, int flags){

    file_handle = open(pathname ,flags);
    if (file_handle == ERROR){ printf (LIB_ERROR);}
    /*Hay que validar las flags de manera que si la biblioteca fue creada con un modo?
     */

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

int abrir_comp(int bib_fd, const char *compname){

}


//aux

//componente newComponente(){
//    componente self = (componente) malloc(sizeof(struct componente_struct));
//    self->comp_nom = "";
//    self->rango[0] = 0;
//    self->rango[1] = 0;
//    self->_lleno = FALSE;
//    self->crear_bibptr = &crear_bib;
//}
