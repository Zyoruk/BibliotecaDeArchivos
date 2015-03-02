#include "hard_drive.h"
#include "filesystem.h"

int file_transfer(int bib_fd, const char *pathcomp){
    int incluir_comp(int bib_fd, const char *pathcomp);

    int extraer_comp (int bib_fd, const char *pathcomp);

    int cargar_dir(int bib_fd, const char *pathdir);
}

int abrir_bib (const char *pathname, int flags){
    int abrir_bib (const char *pathname, int flags);
}

int crear_bib (const char *pathname, mode_t mode){
    int crear_bib (const char *pathname, mode_t mode);
}

int cerrar_bib (int bib_fd){
    int cerrar_bib (int bib_fd);
}

int abrir_comp (int bib_fd, const char *compname){
    int abrir_comp (int bib_fd, const char *compname);
}

ssize_t read_comp (int bib_fd, int comp_id, void *buf, size_t count){
    ssize_t read_comp (int bib_fd, int comp_id, void *buf, size_t count);
}

off_t repos_comp(){
    off_t repos_comp(int bib_fd, int comp_id, size_t count);
}

ssize_t write_comp (){
    ssize_t write_comp (int bib_fd, int comp_id, void *buf, size_t count);
}

int eliminar_comp (int bib_fd, const char *pathcomp){
    int eliminar_comp (int bib_fd, const char *pathcomp);
}
