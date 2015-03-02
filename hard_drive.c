#include "hard_drive.h"
#include "filesystem.h"
#include <dirent.h>

int abrir_bib (const char *pathname, int flags){
    int abrir_bib (const char *pathname, int flags);
}

int crear_bib (const char *pathname, mode_t mode){

}

int cerrar_bib (int bib_fd){
    cerrar_bib (bib_fd);
}

//----------------------------------------------------------------------------//

int import(int bib_fd, const char *path){

    DIR *dir;
    FILE *file;
    struct dirent *ent;
    if ((dir = opendir (pathcomp)) != NULL) {
        //print all the files and directories within directory
        while ((ent = readdir(dir)) != NULL) {
            printf ("%s\n", ent->d_name);
        }
        closedir(dir);
    }else {
        /* could not open directory */
        perror ("");
    }
    if(){
        incluir_comp(bib_fd, *path);
    }else{
        incluir_dir(bib_fd, *path);
    }
}

int exportFile(int bib_fd, int comp_id, const char *pathcomp){
    extraer_comp (bib_fd, comp_id, *pathcomp);
}

//----------------------------------------------------------------------------//

int abrir_comp (int bib_fd, const char *compname){
    abrir_comp (bib_fd, *compname);
}

ssize_t read_comp (int bib_fd, int comp_id, void *buf, size_t count){
    read_comp (bib_fd, comp_id, *buf, count);
}

int eliminar_comp (int bib_fd, const char *pathcomp){
    eliminar_comp (bib_fd, *pathcomp);
}

//No UI Connection
off_t repos_comp(){
    repos_comp(bib_fd, comp_id, count);
}

ssize_t write_comp (){
    write_comp (bib_fd, comp_id, *buf, count);
}
