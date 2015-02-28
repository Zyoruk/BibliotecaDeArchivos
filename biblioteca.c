#include "biblioteca.h"
#include <fcntl.h>
#include <stdlib.h>


int crear_bib(const char *pathname ,mode pmode){
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
    if (file_handle == ERROR){ printf (N_F);}

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

    //Search the compname
    unsigned int i;
    for ( i = 0; i < (sizeof(ptr_comp_list)/sizeof(ptr_comp_list[0])) ; i++){
        componente current = (componente)ptr_comp_list[i];
        //if found
        if ( current->comp_nom == compname){
            current->_abierto = TRUE;
            comp_count+=1;
            current->comp_id = comp_count;
        }else{
            printf(N_F);
        }

    }
    //Si se sale del for significa que no lo encontró.
    return ERROR;
}

size_t print_data (int bib_fd, int comp_id, void *buf, size_t count){
    if(file_handle != bib_fd){
        return ERROR;
    }

    //Search the COMP ID
    unsigned int i;
    for ( i = 0; i < (sizeof(ptr_comp_list)/sizeof(ptr_comp_list[0])) ; i++){
        //Since the list stores only the pointers to the components,
        //we need to create a new component
        componente current = (componente)ptr_comp_list[i];
        //if found
        if ( current->comp_id == comp_id){
//            //open library
//            newBib = fopen(_pathname,"rb+");

            //Pos seek at the beginning of the component
            fseek( newBib , current->rango[0], SEEK_SET);

            //"Read" the component.
            int current_seek_pos = current->rango[0];
            int end_of_component = current->rango[1];

            do{
                buf = malloc(sizeof(char)*40);
                fread(buf , 1 , 40 , newBib);
                printf((char*)buf);
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
                fclose(newBib);
                return SUCCESS;
            }else{
                //Sino se asume que hace falta un poco.
                int missing = end_of_component - current_seek_pos;
                buf = malloc(sizeof(char)*missing);
                fread(buf , 1 , missing , newBib);
                printf((char*)buf);
                fclose(newBib);
                return SUCCESS;
            }
        }
    }
    //Si se sale del for significa que no lo encontró.
    return ERROR;

}
