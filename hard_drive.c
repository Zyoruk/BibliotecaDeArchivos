#include "hard_drive.h"

//----------------------------------------------------------------------------//
// HARD DRIVE RELATED
//----------------------------------------------------------------------------//

void create(const char *pathname, mode_t pmode){
    _pathname = *pathname;
    FILE* newBib = fopen(_pathname , pmode);

    if (newBib == NULL){
        printf ( "Failure.\n");
        return ERROR;
    }else{
        printf ( "Succesful.\n");
        return  SUCCESS;
    }
}

void mount(const char *pathname, int flags){
    file_handle = open(pathname ,flags);
    if (file_handle == ERROR){ printf (N_F);}
    insertOnIndex(file_handle);
}

void umount(int bib_fd){
    if (bib_fd == file_handle){
        fclose (newBib);
        int o = deletoFromIndex(file_handle);
        if (o = 0){
            printf ( "Succesful.\n");
        }else{
            printf ( "File Not Found\n");
        }
        //return SUCCESS;
    }else{
        printf("Failure. \n");
        //return ERROR;
    }
}
//----------------------------------------------------------------------------//
// IMPORT- EXPORT
//----------------------------------------------------------------------------//

void import(char *bib_fd, const char *path, char *opt){

    if (*opt == 'd'){
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir (path)) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                //printf ("%s\n", ent->d_name);
                //incluir_dir((int)*bib_fd, *path);
            }
            closedir(dir);
        }else {
            /* could not open directory */
            perror ("");
        }
    } else if (*opt == 'f') {
        incluir_comp((int)*bib_fd, *path);
    }else{
        /* NO available option */
        //printf ("%d\n", opt);
        perror ("");
    }
}

//CONVERTIR NOMBRE A ID
void exportFile(char *bib_fd, int comp_id, const char *pathcomp){
    extraer_comp ((int)*bib_fd, *pathcomp);
}

//----------------------------------------------------------------------------//
// FILE SYSTEM RELATED
//----------------------------------------------------------------------------//

void openc (char *bib_fd, const char *compname){
    abrir_comp ((int)*bib_fd, *compname);
}

void print(char *bib_fd, int comp_id, size_t count){
    void *buf;
    //print_data((int)*bib_fd, comp_id, *buf, count);
}

void del(char *bib_fd, const char *pathcomp){
    eliminar_comp ((int)*bib_fd, *pathcomp);
}

int listComp (int bib_fd){

}

//----------------------------No UI Connection--------------------------------//

//off_t repos_comp(){
//    repos_comp(bib_fd, comp_id, count);
//}

//ssize_t write_comp (){
//    write_comp (bib_fd, comp_id, *buf, count);
//}

//----------------------------------------------------------------------------//
// INDEX RELATED
//----------------------------------------------------------------------------//

void initializeStructs(){
    int i;
    for (i = 0; i < strlen(sarray); i++){
        //sarray[i]->id = ERROR;
    }
}

void insertOnIndex(int id){
    int i;
//    for (i = 0; i < strlen(sarray); i++){
//        if(!strcmp(sarray[i]->id, ERROR)){
//            sarray[i]->id = id;
//        }
//    }
}

int deletoFromIndex(int id){
    int i = 0;
    //get index for desired file
//    while(!(sarray[i]->id == id)){
//        i++;
//        if(sarray[i]->id == 0){
//            //if not present return 0
//            return ERROR;
//        }
//    }
    //if element + 1 is not null
    if(!sarray[i+1] == 0){
        //on remaining array, reorganize elements
        for (i; i < strlen; i++){
//            if (!sarray[i+1] == 0){
//                sarray[i+1]->id = sarray[i]->id;
//                sarray[i+1]->filename = sarray[i]->filename;
//            }
        }
    }else{
        //sarray[i]->id = ERROR;
    }
    return 0;
}
