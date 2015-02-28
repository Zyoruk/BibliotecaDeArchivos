#include "biblioteca.h"
#include <fcntl.h>
#include <stdlib.h>


typedef const char* mode ;
int file_handle;
FILE *newBib;
const char* _pathname;

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
    _pathname = pathname;
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
    if(file_handle != bib_fd){
        return ERROR;
    }

    void* _buffer;
    //Search the compname
    unsigned int i;
    for ( i = 0; i < (sizeof(ptr_comp_list)/sizeof(ptr_comp_list[0])) ; i++){
        //Since the list stores only the pointers to the components,
        //we need to create a new component
        componente current = (componente)ptr_comp_list[i];
        //if found
        if ( current->comp_nom == compname){
            //open library
            newBib = fopen(_pathname,"rb+");
            //Pos seek at the beginning of the component
            fseek( newBib , current->rango[0], SEEK_SET);

            //"Read" the component.
            int current_seek_pos = current->rango[0];
            int end_of_component = current->rango[1];

            do{
                _buffer = malloc(sizeof(char)*40);
                fread(_buffer , 1 , 40 , newBib);
                printf((char*)_buffer);
                current_seek_pos += 40;
                fseek( newBib , current_seek_pos, SEEK_SET);

                /*Despues de sumar los 40... Si el seek es más grande o igual
                que el final del componente, el ciclo se rompe.*/

                /*Si la resta entre el final con la posicion actual es menor que
                  40, se rompe el ciclo.*/

            }while((end_of_component - current_seek_pos) >= 40 ||
                   (current_seek_pos >= end_of_component));

            /*Al romperse el ciclo hay que verificar si ya se terminó o si
             * hace falta.
             */

            if (current_seek_pos >= end_of_component){
                //Si la posicion del seek es mayor o igual, se termino
                return SUCCESS;
            }else{
                //Sino se asume que hace falta un poco.
                int faltante = end_of_component - current_seek_pos;
                _buffer = malloc(sizeof(char)*faltante);
                fread(_buffer , 1 , faltante , newBib);
                printf((char*)_buffer);
                return SUCCESS;
            }
        }
    }
    //Si se sale del for significa que no lo encontró.
    return ERROR;
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
