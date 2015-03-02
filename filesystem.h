#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define SUCCESS 0
#define WRONG_FLAG "wf"
#define N_F "404: Not found."

#include <stdio.h>
#include "EnlargeArray.h"

typedef char boolean;
typedef const char* mode;
typedef struct componente_struct* componente;

 struct componente_struct {
    const char* comp_nom;
    int comp_id;
    int rango[2];
    boolean _lleno : 1;
    char permit: 1;
    int seek_pos;
};

componente open_comp_list[5];
componente ptr_comp_list[10];
int comp_count ;
int comp_qtt;
int file_handle;
int index_size;
FILE *newBib;
const char* _pathname;



//done
int crear_bib (const char *pathname, mode pmode);
int abrir_bib (const char *pathname, int flags);
int cerrar_bib (int bib_fd);
int abrir_comp (int bib_fd, const char *compname);
size_t print_data (int bib_fd, int comp_id, void *buf, size_t count);
off_t repos_seek_aleatorio(int bib_fd, int comp_id, size_t count);
size_t escribir_comp (int bib_fd, int comp_id, void *buf, size_t count);
//TODO

int incluir_comp(int bib_fd, const char *pathcomp);

int extraer_comp (int bib_fd, int comp_id, const char *pathcomp);

int cargar_dir(int bib_fd, const char *pathdir);

int eliminar_comp (int bib_fd, int comp_id, const char *pathcomp);

#endif // FILESYSTEM_H
