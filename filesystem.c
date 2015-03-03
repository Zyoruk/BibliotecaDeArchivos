#include "filesystem.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int index_size = 32;


int crear_bib(const char *pathname ,mode pmode){
    _pathname = pathname;
    newBib = fopen(pathname , pmode);
    //init
    int i ;
    componente_struct* nuevo;
    for (i = 0 ;i <= 10 ; i++){
        nuevo = malloc ( sizeof(componente_struct));
        ptr_comp_list[i]= nuevo;
    }
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
    //SI ENTRA
        componente_struct newComp = *ptr_comp_list[i];
        if (ptr_comp_list[i]->_lleno == FALSE){
            //Si encuentra un espacio exacto
            if ((newComp.rango[1] - newComp.rango[0])
                    == size ){
                newComp.comp_nom = pathcomp;
                newComp._lleno = TRUE;
                newComp.seek_pos = 0;
                newComp.comp_id = 0;
                newComp.permit = 0;
                ptr_comp_list[i] = &newComp;
//                copiar_contenido ( comp, size , ptr_comp_list[i]->rango[0]);
                return SUCCESS;
            //Si encuentra un espacio mayor. Divide.
            }else if(((newComp.rango[1] - newComp.rango[0])
                     > size)){

                int nuevo_limite = newComp.rango[1] - size;

                newComp.comp_nom = pathcomp;
                newComp._lleno = TRUE;
                newComp.seek_pos = 0;
                newComp.comp_id = 0;
                newComp.permit = 0;

                componente_struct newComp2;
                newComp2.comp_id = 0 ;
                newComp2.comp_nom = "EMPTY";
                newComp2.permit = 0;
                newComp2.rango[0] = nuevo_limite;
                newComp2.rango[1] = ptr_comp_list[i]->rango[1];
                newComp2.seek_pos = 0;
                newComp2._lleno = FALSE;

                newComp2.rango[1] = nuevo_limite;


                //Si esta lleno
                if (( comp_qtt ) == ( sizeof(ptr_comp_list)
                                      / sizeof(ptr_comp_list[0]))){
                    //enlarge
                    *ptr_comp_list = elargeArray(ptr_comp_list ,
                                               (sizeof(ptr_comp_list)/
                                                sizeof(ptr_comp_list[0])));
                }
                comp_qtt++;
                ptr_comp_list[comp_qtt] = &newComp2;
                ptr_comp_list[i] = &newComp;
                copiar_contenido ( comp, size , newComp.rango[0]);
                return SUCCESS;
            }
        }
    }




    componente_struct newComp;

    printf("%p\n" , &newComp);
    newComp.comp_id = 0 ;
    newComp.comp_nom = pathcomp;
    newComp.permit = 0;
    newComp.rango[0] = bib_size + MET_SIZE;
    newComp.rango[1] = size;
    newComp.seek_pos = 0;
    newComp._lleno = FALSE;
    printf("%d\n",newComp.rango[0]);
    //Si esta lleno
    int size_arr=( sizeof(ptr_comp_list)
                   / sizeof(ptr_comp_list[0]));
    if (( comp_qtt ) == size_arr){
        //enlarge
        *ptr_comp_list = elargeArray(ptr_comp_list ,size_arr);
    }
    comp_qtt++;
    ptr_comp_list[comp_qtt] = &newComp;




    copiar_contenido ( comp, size , ptr_comp_list[comp_qtt]->rango[0]);

    return SUCCESS;
}

void copiar_contenido(FILE* comp ,int size , int PDC){

    //abrir bib y comp en binario.

    printf("sdfsadfs\n");
    fseek (newBib, PDC , SEEK_SET);
    fseek( comp , 0 , SEEK_SET);

    char* buffer;
    int count = size ;
    while ( count >= 40 ){
        buffer =  malloc(40);
        fread(buffer , sizeof(char) , 40 , comp);
        fwrite (buffer, sizeof(char) , 40 , newBib );
        count -= 40 ;
        free(buffer);
    }
    buffer =  malloc(40);
    fread(buffer , sizeof(char) , count , comp);
    fwrite(buffer , sizeof(char) , count , newBib);
    free(buffer);
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



