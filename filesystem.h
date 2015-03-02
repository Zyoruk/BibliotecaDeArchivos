#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define SUCCESS 0
#define WRONG_FLAG "wf"
#define N_F "404: Not found."
#define MET_SIZE 7 ;

#include <stdio.h>
#include "EnlargeArray.h"

typedef char boolean;
typedef const char* mode;
//typedef struct componente_struct* componente;

typedef struct  {
    const char* comp_nom;
    int comp_id;
    int rango[2];
    boolean _lleno : 1;
    char permit: 1;
    int seek_pos;
}componente_struct;

int bib_size;
componente_struct* open_comp_list[5];
componente_struct* ptr_comp_list[10];
unsigned int comp_count ;
int comp_qtt;
int file_handle;
int index_size;
FILE *newBib;
const char* _pathname;



//done
int abrir_comp (int bib_fd, const char *compname);
size_t print_data (int bib_fd, int comp_id, void *buf, size_t count);
off_t repos_seek_aleatorio(int bib_fd, int comp_id, size_t count);
size_t escribir_comp (int bib_fd, int comp_id, void *buf, size_t count);
int incluir_comp(int bib_fd, const char *pathcomp);
int extraer_comp (int bib_fd, const char *pathcomp);
int eliminar_comp (int bib_fd, const char *pathcomp);

//TODO
int incluir_dir(int bib_fd, const char *pathdir);

#endif // FILESYSTEM_H
