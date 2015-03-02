#include "filesystem.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int index_size = 32;

int abrir_comp(int bib_fd, const char *compname){
    if(file_handle != bib_fd){
        return ERROR;
    }

    //Search the compname
    unsigned int i;
    for ( i = 0; i < (sizeof(ptr_comp_list)/sizeof(ptr_comp_list[0])) ; i++){
        componente_struct* current = ptr_comp_list[i];
        //if found
        if ( current->comp_nom == compname){
            //If the comp count is bigger than the array size
            //it will mean that the array is already full.
            //So enlarge is needed

            if (comp_count >= ((sizeof(open_comp_list)/
                                   sizeof(open_comp_list[0])))){
                //enlarge
               *open_comp_list = (componente_struct*)elargeArray(open_comp_list , (sizeof(open_comp_list)/
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
        componente_struct* current = ptr_comp_list[i];
        //if found
        if ( current->comp_id == comp_id){
            //Pos seek at the beginning of the component
            fseek( newBib , current->rango[0] + current->seek_pos, SEEK_SET);

            //"Read" the component.

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
        componente_struct* current = ptr_comp_list[i];
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
        componente_struct* current = ptr_comp_list[i];
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
    fseek (comp ,0,SEEK_END);
    int size  = ftell(comp);
    fseek(comp , 0 , SEEK_SET);

    //Tenemos que buscar que la bib tenga algun espacio vacío en donde quepa.

    unsigned int i;

    for (i = 0 ; i <= (sizeof(ptr_comp_list)/ sizeof(ptr_comp_list[0])); i++){
        if (ptr_comp_list[i]->_lleno == FALSE){
            //Si encuentra un espacio exacto
            if ((ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0])
                    == size ){
                ptr_comp_list[i]->comp_nom = pathcomp;
                ptr_comp_list[i]->_lleno = TRUE;
                ptr_comp_list[i]->seek_pos = 0;
                ptr_comp_list[i]->comp_id = 0;
                ptr_comp_list[i]->permit = 0;

                copiar_contenido ( comp, size , ptr_comp_list[i]->rango[0]);
                return SUCCESS;
            //Si encuentra un espacio mayor. Divide.
            }else if((ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0])
                     < size){
                int nuevo_limite = ptr_comp_list[i]->rango[1] - size;

                ptr_comp_list[i]->comp_nom = pathcomp;
                ptr_comp_list[i]->_lleno = TRUE;
                ptr_comp_list[i]->seek_pos = 0;
                ptr_comp_list[i]->comp_id = 0;
                ptr_comp_list[i]->permit = 0;

                componente_struct* newComp;
                newComp->comp_id = 0 ;
                newComp->comp_nom = "EMPTY";
                newComp->permit = 0;
                newComp->rango[0] = nuevo_limite;
                newComp->rango[1] = ptr_comp_list[i]->rango[1];
                newComp->seek_pos = 0;
                newComp->_lleno = FALSE;

                ptr_comp_list[i]->rango[1] = nuevo_limite;


                //Si esta lleno
                if (( comp_qtt ) == ( sizeof(ptr_comp_list)
                                      / sizeof(ptr_comp_list[0]))){
                    //enlarge
                    *ptr_comp_list = elargeArray(ptr_comp_list ,
                                               (sizeof(ptr_comp_list)/
                                                sizeof(ptr_comp_list[0])));
                }
                comp_qtt++;
                ptr_comp_list[comp_qtt] = newComp;

                copiar_contenido ( comp, size , ptr_comp_list[i]->rango[0]);
                return SUCCESS;
            }
        }
    }

    // Si no encuentra un lugar vacío entonces tiene que crear un componente nuevo
    //y agregarlo.

    componente_struct* newComp;
    newComp->comp_id = 0 ;
    newComp->comp_nom = pathcomp;
    newComp->permit = 0;
    newComp->rango[0] = bib_size + MET_SIZE;
    newComp->rango[1] = size;
    newComp->seek_pos = 0;
    newComp->_lleno = FALSE;

    copiar_contenido ( comp, size , ptr_comp_list[i]->rango[0]);

    return SUCCESS;

}

void copiar_contenido(FILE* comp ,int size , int PDC){

    //abrir bib y comp en binario.

    fseek (newBib, PDC , SEEK_SET);
    fseek( comp , 0 , SEEK_SET);

    char* buffer = malloc(40);
    int count = size ;

    while ( count >= 40 ){
        fread(buffer , sizeof(char) , 40 , comp);
        fwrite (buffer, sizeof(char) , 40 , newBib );

        count -= 40 ;
    }

    fread(buffer , sizeof(char) , count , comp);
    fwrite(buffer , sizeof(char) , count , newBib);
}

int extraer_comp (int bib_fd, const char *pathcomp){
    if ( file_handle != bib_fd){return ERROR;}

    //Buscamos que exista el compo
    int i;
    for (i = 0 ; i <= comp_qtt ; i++){
        if(ptr_comp_list[i] == NULL) { return ERROR;}
        if (ptr_comp_list[i]->comp_nom == pathcomp){
            //Chequear si esta abierto
            if (ptr_comp_list[i]->comp_id != 0){
                //Si lo encuentra abierto, se cierra.
                //Cerrar significa eliminarlo del arreglo de comp abiertos.
                //Esto hará que todos los elementos hacia la derecha se muevan
                //Así,  se elimina y queda el espacio vacío al final del arreglo
                unsigned int j;
                for (j = 0 ; j <= comp_count; j++){
                    if(open_comp_list[j] == NULL) { return ERROR;}
                    if ( open_comp_list[j]->comp_nom){
                        open_comp_list[j]->comp_id = 0;
                        while ( j < comp_count){
                            open_comp_list[j] = open_comp_list[j +1];
                        }

                        if ( j == comp_count) { open_comp_list[j] = NULL;}

                        comp_count--;
                    }
                }

                FILE* newComp = fopen (pathcomp, "wb+");

                fseek (newBib, ptr_comp_list[i]->rango[0] , SEEK_SET);
                fseek( newComp , 0 , SEEK_SET);

                char* buffer = malloc(40);
                int count = ptr_comp_list[i]->rango[1] -
                            ptr_comp_list[i]->rango[0];

                while ( count >= 40 ){
                    fread(buffer , sizeof(char) , 40 , newBib);
                    fwrite (buffer, sizeof(char) , 40 , newComp );

                    count -= 40 ;
                }

                fread(buffer , sizeof(char) , count , newBib);
                fwrite(buffer , sizeof(char) , count , newComp);
                return ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0];
            }else{

                FILE* newComp = fopen (pathcomp, "wb+");

                fseek (newBib, ptr_comp_list[i]->rango[0] , SEEK_SET);
                fseek( newComp , 0 , SEEK_SET);

                char* buffer = malloc(40);
                int count = ptr_comp_list[i]->rango[1] -
                            ptr_comp_list[i]->rango[0];

                while ( count >= 40 ){
                    fread(buffer , sizeof(char) , 40 , newBib);
                    fwrite (buffer, sizeof(char) , 40 , newComp );

                    count -= 40 ;
                }

                fread(buffer , sizeof(char) , count , newBib);
                fwrite(buffer , sizeof(char) , count , newComp);

                return ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0];
            }
        }
    }
    return ERROR;
}

int eliminar_comp (int bib_fd, const char *pathcomp){
    if ( file_handle != bib_fd){return ERROR;}

    //Buscamos que exista el compo
    int i;
    for (i = 0 ; i <= comp_qtt ; i++){
        if(ptr_comp_list[i] == NULL) { return ERROR;}
        if (ptr_comp_list[i]->comp_nom == pathcomp){
            //Chequear si esta abierto
            if (ptr_comp_list[i]->comp_id != 0){
                //Si lo encuentra abierto, se cierra.
                //Cerrar significa eliminarlo del arreglo de comp abiertos.
                //Esto hará que todos los elementos hacia la derecha se muevan
                //Así,  se elimina y queda el espacio vacío al final del arreglo
                unsigned int j;
                for (j = 0 ; j <= comp_count; j++){
                    if(open_comp_list[j] == NULL) { return ERROR;}
                    if ( open_comp_list[j]->comp_nom){
                        open_comp_list[j]->comp_id = 0;
                        while ( j < comp_count){
                            open_comp_list[j] = open_comp_list[j +1];
                        }

                        if ( j == comp_count) { open_comp_list[j] = NULL;}

                        comp_count--;
                    }
                }

                fseek (newBib, ptr_comp_list[i]->rango[0] , SEEK_SET);

                char* buffer = malloc(40);

                int k;
                for(k = 0 ; k <= 40 ;k++){
                    *(buffer+k) =  '\0';
                }

                int count = ptr_comp_list[i]->rango[1] -
                            ptr_comp_list[i]->rango[0];

                while ( count >= 40 ){
                    fwrite (buffer, sizeof(char) , 40 , newBib );
                    count -= 40 ;
                    fseek(newBib ,  sizeof(buffer) , SEEK_CUR );
                }

                fwrite(buffer , sizeof(char) , count , newBib);

                ptr_comp_list[i]->comp_nom = "EMPTY";
                return ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0];
            }else{

                fseek (newBib, ptr_comp_list[i]->rango[0] , SEEK_SET);

                char* buffer = malloc(40);

                int k;
                for(k = 0 ; k <= 40 ;k++){
                    *(buffer+k) =  '\0';
                }

                int count = ptr_comp_list[i]->rango[1] -
                            ptr_comp_list[i]->rango[0];

                while ( count >= 40 ){
                    fread(buffer , sizeof(char) , 40 , newBib);

                    count -= 40 ;
                    fseek(newBib ,  sizeof(buffer) , SEEK_CUR);
                }

                fread(buffer , sizeof(char) , count , newBib);

                return ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0];
            }
        }
    }
    return ERROR;
}



