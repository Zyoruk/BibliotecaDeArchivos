#include "filesystem.h"
#include <string.h>

int index_size = 32;
bib_size = 0;

int crear_bib(const char *pathname ,mode_t pmode){
    _pathname = pathname;
    newBib = fopen(pathname , pmode);
    //init
    int i ;
    componente_struct* nuevo;

    for (i = 0 ;i <= 10 ; i++){

        nuevo = malloc ( sizeof(componente_struct));
        nuevo->comp_nom = "EMPTY";
        nuevo->_lleno = FALSE;
        nuevo->seek_pos = 0;
        nuevo->comp_id = 0;
        nuevo->permit = 0;
        nuevo->rango[0] = 0 ;
        nuevo->rango[1] = 0 ;
        ptr_comp_list[i]= nuevo;
    }


//        componente_struct* nuevo2;
//    int j;
//    for (j = 0 ;j <= 5 ; j++){
//        nuevo2 = malloc ( sizeof(componente_struct));
//        nuevo2->comp_nom = "EMPTY";
////        nuevo2->_lleno = FALSE;
////        nuevo2->seek_pos = 0;
////        nuevo2->comp_id = 0;
////        nuevo2->permit = 0;
////        nuevo2->rango[0] = 0 ;
////        nuevo2->rango[1] = 0 ;
//        open_comp_list[j]= nuevo2;
//        printf("%p\n" , *(open_comp_list[j]));
//    }

    if (newBib == NULL){
        printf ( "Failure.\n");
        return ERROR;
    }else{
        fclose(newBib);
        printf ( "Succesful.\n");
        return  SUCCESS;
    }

}

int abrir_bib(const char *pathname, int flags){

    file_handle = open(pathname ,flags);
    if ( flags == 0){
        newBib = fopen(pathname , "rb");
    }else if (flags == 1){
        newBib = fopen(pathname , "rb+");
    }else if (flags == 2){
        newBib = fopen(pathname , "wb");
    }else if (flags == 3){
        newBib = fopen(pathname , "wb+");
    }else if (flags == 4){
        newBib = fopen(pathname , "ab");
    }else if (flags == 5){
        newBib = fopen(pathname , "ab+");
    }else{
        printf(WRONG_FLAG);
        return ERROR;
    }

    if (file_handle == ERROR){
        printf (N_F);
        return ERROR;
    }

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
        componente_struct current = *ptr_comp_list[i];
        //if found
        if ( ptr_comp_list[i]->comp_nom == compname){
            //If the comp count is bigger than the array size
            //it will mean that the array is already full.
            //So enlarge is needed

            if (comp_count >= ((sizeof(open_comp_list)/
                                   sizeof(open_comp_list[0])))){
                //enlarge
//               *open_comp_list = (componente_struct*)elargeArray(open_comp_list , (sizeof(open_comp_list)/
                                             //sizeof(open_comp_list[0])));
                open_comp_list[comp_count] = &current;
            }else{
                open_comp_list[comp_count] = &current;
            }
            return ptr_comp_list[i]->comp_id;
        }
    }
    printf(N_F);
    //Si se sale del for significa que no lo encontró.
    return ERROR;
}

size_t print_data (int bib_fd, int comp_id, void *buf, size_t count){
    if(file_handle != bib_fd){
        return ERROR;
    }

    //Search the COMP ID
    unsigned int i;
    char* sub_buf = (char*)(buf);
//    buf = malloc(count);
    for ( i = 0; i < (sizeof(ptr_comp_list)/sizeof(ptr_comp_list[0])) ; i++){
        //Since the list stores only the pointers to the components,
        //we need to create a new component
        //if found
        if ( ptr_comp_list[i]->comp_id == comp_id){
            //Pos seek at the beginning of the component
            fseek( newBib , ptr_comp_list[i]->rango[0] + ptr_comp_list[i]->seek_pos, SEEK_SET);

            //"Read" the component.

            fread(sub_buf , count ,  1 , newBib);
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
        //if found
        if ( ptr_comp_list[i]->comp_id == comp_id){
            if ((ptr_comp_list[i]->seek_pos + count + ptr_comp_list[i]->rango[0]) >
                    (unsigned int ) ptr_comp_list[i]->rango[1]){
                return ERROR;
            }
            ptr_comp_list[i]->seek_pos += count;
            return ptr_comp_list[i]->seek_pos;
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
        //if found
        if ( ptr_comp_list[i]->comp_id == comp_id){
            //Pos seek at the beginning of the component
            fseek( newBib , ptr_comp_list[i]->rango[0] + ((i + 1) * MET_SIZE) , SEEK_SET);

            //"Read" the component.
            fwrite(buf , 1 ,  count, newBib);
            return count;
        }
    }
    return ERROR;
}


int incluir_comp(int bib_fd,  char *pathcomp){
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
        if (ptr_comp_list[i]->_lleno == FALSE){
            //Si encuentra un espacio exacto
            if ((ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0])
                    == size ){
                ptr_comp_list[i]->comp_nom = pathcomp;
                ptr_comp_list[i]->_lleno = TRUE;
                ptr_comp_list[i]->seek_pos = 0;
                ptr_comp_list[i]->permit = 0;
                copiar_contenido ( comp, size , ptr_comp_list[i]->rango[0]);
                comp_count+=1;
                ptr_comp_list[i]->comp_id = comp_count;
                fclose(comp);
                return SUCCESS;
            //Si encuentra un espacio mayor. Divide.
            }else if(((ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0])
                     > size)){

                int nuevo_limite = ptr_comp_list[i]->rango[1] - size;

                ptr_comp_list[i]->comp_nom = pathcomp;
                ptr_comp_list[i]->_lleno = TRUE;
                ptr_comp_list[i]->seek_pos = 0;
                comp_count+=1;
                ptr_comp_list[i]->comp_id = comp_count;
                ptr_comp_list[i]->permit = 0;

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
                    //*ptr_comp_list = elargeArray(ptr_comp_list ,
//                                               (sizeof(ptr_comp_list)/
//                                                sizeof(ptr_comp_list[0])));
                }
                comp_qtt++;
                *(ptr_comp_list[comp_qtt]) = newComp2;
                copiar_contenido ( comp, size , ptr_comp_list[i]->rango[0]);
                fclose(comp);
                return SUCCESS;
            }
        }
    }


    //Si esta lleno
    int size_arr=( sizeof(ptr_comp_list)
                   / sizeof(ptr_comp_list[0]));
    if (( comp_qtt ) == size_arr){
        //enlarge
        //*ptr_comp_list = elargeArray(ptr_comp_list ,size_arr);
    }

    comp_count+=1;
    ptr_comp_list[comp_qtt]->comp_id = comp_count;
    ptr_comp_list[comp_qtt]->comp_nom = pathcomp;
    ptr_comp_list[comp_qtt]->permit = 0;
    ptr_comp_list[comp_qtt]->rango[0] = bib_size + MET_SIZE;
    ptr_comp_list[comp_qtt]->rango[1] = size;
    ptr_comp_list[comp_qtt]->seek_pos = 0;
    ptr_comp_list[comp_qtt]->_lleno = TRUE;

    comp_qtt++;




    copiar_contenido ( comp, size , ptr_comp_list[comp_qtt - 1]->rango[0]);
    bib_size = bib_size + size+7;
    fclose(comp);
    return SUCCESS;
}

void copiar_contenido(FILE* comp ,int size , int PDC){

    //abrir bib y comp en binario.

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
//        if(ptr_comp_list[i] == NULL) { return ERROR;}

        if (ptr_comp_list[i]->comp_nom == pathcomp){
            //Chequear si esta abierto
            if (ptr_comp_list[i]->comp_id != 0){
                //Si lo encuentra abierto, se cierra.
                //Cerrar significa eliminarlo del arreglo de comp abiertos.
                //Esto hará que todos los elementos hacia la derecha se muevan
                //Así,  se elimina y queda el espacio vacío al final del arreglo

                printf("\ncaca\n");

                FILE* newComp_file = fopen (pathcomp, "wb+");

                printf("\ncaca\n");
                fseek (newBib, ptr_comp_list[i]->rango[0] , SEEK_SET);
                fseek( newComp_file , 0 , SEEK_SET);

                char* buffer = malloc(40);
                int count = ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0];

                while ( count >= 40 ){
                    printf("\ncaca\n");
                    fread(buffer , sizeof(char) , 40 , newBib);
                    fwrite (buffer, sizeof(char) , 40 , newComp_file );

                    count -= 40 ;
                }

                fread(buffer , sizeof(char) , count , newBib);
                fwrite(buffer , sizeof(char) , count , newComp_file);
                return ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0];
            }else{

                FILE* newComp_file = fopen (pathcomp, "wb+");

                fseek (newBib, ptr_comp_list[i]->rango[0] , SEEK_SET);
                fseek( newComp_file , 0 , SEEK_SET);

                char* buffer = malloc(40);
                int count = ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0];

                while ( count >= 40 ){
                    fread(buffer , sizeof(char) , 40 , newBib);
                    fwrite (buffer, sizeof(char) , 40 , newComp_file );

                    count -= 40 ;
                }

                fread(buffer , sizeof(char) , count , newBib);
                fwrite(buffer , sizeof(char) , count , newComp_file);

                return ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0];
            }
        }
    }
    return ERROR;
}

int eliminar_comp (int bib_fd, const char *pathcomp){
    if ( file_handle != bib_fd){return ERROR;}
    unsigned int i;

//    printf("%d" , ptr_comp_list[i]->rango[0] + ((i + 1) * MET_SIZE));
    for ( i = 0; i < (sizeof(ptr_comp_list)/sizeof(ptr_comp_list[0])) ; i++){

        //if found
        if ( ptr_comp_list[i]->comp_nom == pathcomp){
             fseek( newBib , ptr_comp_list[i]->rango[0] , SEEK_SET);
            char* buffer  = "@@@@@@@@@@";
            int count = ptr_comp_list[i]->rango[1] - ptr_comp_list[i]->rango[0] + 7 ;
            while ( count >= 10 ){
                fwrite (buffer, sizeof(char) , 10 , newBib );
                count -= 10 ;
            }
            fwrite(buffer , sizeof(char) , count , newBib);
            return SUCCESS;
        }
    }
        return ERROR;
    }



