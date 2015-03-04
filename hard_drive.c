#include "hard_drive.h"
#include "filesystem.h"
#include <dirent.h>

//----------------------------------------------------------------------------//
// HARD DRIVE RELATED
//----------------------------------------------------------------------------//

int create(const char *pathname, mode pmode){
    _pathname = pathname;
    newBib = fopen(_pathname , pmode);

    if (newBib == NULL){
        printf ( "Failure.\n");
        return ERROR;
    }else{
        printf ( "Succesful.\n");
        return  SUCCESS;
    }
}

int mount(const char *pathname, int flags){
    file_handle = open(pathname ,flags);
    if (file_handle == ERROR){ printf (N_F);}
    return file_handle;
}

int umount(int bib_fd){
    if (bib_fd == file_handle){
        fclose (newBib);
        printf ( "Succesful.\n");
        return SUCCESS;
    }else{
        printf("Failure. \n");
        return ERROR;
    }
}
//----------------------------------------------------------------------------//
// IMPORT- EXPORT
//----------------------------------------------------------------------------//

int import(int bib_fd, const char *path, char *opt){

    if (*opt == 'd'){
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir (path)) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                //printf ("%s\n", ent->d_name);
                incluir_dir(bib_fd, *path);
            }
            closedir(dir);
        }else {
            /* could not open directory */
            perror ("");
        }
    } else if (*opt == 'f') {
        incluir_comp(bib_fd, *path);
    }else{
        /* NO available option */
        //printf ("%d\n", opt);
        perror ("");
    }
}

int exportFile(int bib_fd, int comp_id, const char *pathcomp){
    extraer_comp (bib_fd, comp_id, *pathcomp);
}

//----------------------------------------------------------------------------//
// FILE SYSTEM RELATED
//----------------------------------------------------------------------------//

int openc (int bib_fd, const char *compname){
    abrir_comp (bib_fd, *compname);
}

int listc (int bib_fd){
    listar_comp(bib_fd);
}

ssize_t print(int bib_fd, int comp_id, void *buf, size_t count){
    read_comp (bib_fd, comp_id, *buf, count);
}

int del(int bib_fd, const char *pathcomp){
    eliminar_comp (bib_fd, *pathcomp);
}

//----------------------------No UI Connection--------------------------------//

off_t repos_comp(){
    repos_comp(bib_fd, comp_id, count);
}

ssize_t write_comp (){
    write_comp (bib_fd, comp_id, *buf, count);
}
