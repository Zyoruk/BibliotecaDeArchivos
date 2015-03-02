#include "filesystem.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int index_size = 32;
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
            //If the comp count is bigger than the array size
            //it will mean that the array is already full.
            //So enlarge is needed

            if (comp_count >= ((sizeof(open_comp_list)/
                                   sizeof(open_comp_list[0])))){
                //enlarge
               open_comp_list = elargeArray(open_comp_list , (sizeof(open_comp_list)/
                                             sizeof(open_comp_list[0])));
            }else{
                open_comp_list[comp_count] = current;
            }
            comp_count+=1;
            current->comp_id = comp_count;
            return SUCCESS;
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
            //Pos seek at the beginning of the component
            fseek( newBib , current->rango[0] + current->seek_pos, SEEK_SET);

            //"Read" the component.

            buf = malloc(sizeof(char) * count - (current->rango[1] -
                                                (current->rango[0] +
                                                 current->seek_pos)));
            fread(buf , 1 ,  count - (current->rango[1] - (current->rango[0] +
                  current->seek_pos)), newBib);
            return count;
        }
    }
    //Si se sale del for significa que no lo encontró.
    return ERROR;
}

off_t repos_seek_aleatorio(int bib_fd, int comp_id, size_t count){
    if (file_handle != bib_fd){return ERROR;}

    //Search the COMP ID
    unsigned int i;
    for ( i = 0; i < (sizeof(ptr_comp_list)/sizeof(ptr_comp_list[0])) ; i++){
        //Since the list stores only the pointers to the components,
        //we need to create a new component
        componente current = (componente)ptr_comp_list[i];
        //if found
        if ( current->comp_id == comp_id){
            if ((current->seek_pos + count + current->rango[0]) >
                    (unsigned int ) current->rango[1]){
                return ERROR;
            }
            current->seek_pos += count;
            return SUCCESS;
        }
    }
    return ERROR;
}

size_t escribir_comp (int bib_fd, int comp_id, void *buf, size_t count){
    if (file_handle != bib_fd){ return ERROR;}
    //Search the COMP ID
    unsigned int i;
    for ( i = 0; i < (sizeof(ptr_comp_list)/sizeof(ptr_comp_list[0])) ; i++){
        //Since the list stores only the pointers to the components,
        //we need to create a new component
        componente current = (componente)ptr_comp_list[i];
        //if found
        if ( current->comp_id == comp_id){
            //Pos seek at the beginning of the component
            fseek( newBib , current->rango[0] + current->seek_pos, SEEK_SET);

            //"Read" the component.
            fwrite(buf , 1 ,  count - (current->rango[1] - (current->rango[0] +
                  current->seek_pos)), newBib);
            return count;
        }
    }
    return ERROR;
}


int incluir_comp(int bib_fd, const char *pathcomp){
    if ( file_handle != bib_fd){ return ERROR;}

    FILE* comp = fopen(pathcomp , "rb");
    if  (comp == NULL) {
        printf ( N_F);
        return ERROR;
    }

    //Copiamos todo a un buffer.
    fseek (pathcomp ,0,SEEK_END);
    int size  = ftell(comp);
    //CAMBIAR
//    void* _buffer =  malloc (size);

//    fread (_buffer , 1 , size , comp);


    //Tenemos que buscar que la bib tenga algun espacio vacío en donde quepa.

    int i;

    for (i = 0 ; i <= (sizeof(ptr_comp_list)/ sizeof(ptr_comp_list[0])); i++){
        if (ptr_comp_list[i]->_lleno = FALSE){
            //Si encuentra un espacio exacto
            if ((ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0]) == size ){
                ptr_comp_list[i]->comp_nom = pathcomp;
                ptr_comp_list[i]->_lleno = TRUE;
                ptr_comp_list[i]->seek_pos = 0;
                ptr_comp_list[i]->comp_id = 0;
                ptr_comp_list[i]->permit = 0;

            //Si encuentra un espacio mayor. Divide.
            }else if((ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0]) < size){
                int nuevo_limite = ptr_comp_list[i]->rango[1] - size;

                ptr_comp_list[i]->comp_nom = pathcomp;
                ptr_comp_list[i]->_lleno = TRUE;
                ptr_comp_list[i]->seek_pos = 0;
                ptr_comp_list[i]->comp_id = 0;
                ptr_comp_list[i]->permit = 0;

                componente newComp;
                newComp->comp_id = 0 ;
                newComp->comp_nom = "EMPTY";
                newComp->permit = 0;
                newComp->rango[0] = nuevo_limite;
                newComp->rango[1] = ptr_comp_list[i]->rango[1];
                newComp->seek_pos = 0;
                newComp->_lleno = FALSE;

                ptr_comp_list[i]->rango[1] = nuevo_limite;

                if (( comp_qtt ) == ( sizeof(ptr_comp_list)
                                      / sizeof(ptr_comp_list[0]))){
                    //enlarge
                    ptr_comp_list = elargeArray(ptr_comp_list , (sizeof(ptr_comp_list)/
                                                  sizeof(ptr_comp_list[0])));
                }else{

                }


            }
        }
    }

    return 0;

}
