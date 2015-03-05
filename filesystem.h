#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define SUCCESS 0
#define WRONG_FLAG "wf"
#define N_F "404: Not found."
#define MET_SIZE 7
#include "enlargeArray.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

//#include "enlargeArray.h

//typedef struct componente_struct* componente;

typedef struct  {
    char* comp_nom;
    int comp_id;
    int rango[2];
    int _lleno;
    char permit;
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
char* _pathname;



//done
int abrir_bib (const char *pathname, int flags);

int crear_bib (const char *pathname, mode_t mode);

int cerrar_bib (int bib_fd);

int abrir_comp (int bib_fd, const char *compname);
size_t print_data (int bib_fd, int comp_id, void *buf, size_t count);
off_t repos_seek_aleatorio(int bib_fd, int comp_id, size_t count);
size_t escribir_comp (int bib_fd, int comp_id, void *buf, size_t count);
int incluir_comp(int bib_fd, char *pathcomp);
int extraer_comp (int bib_fd, const char *pathcomp);
int eliminar_comp (int bib_fd, const char *pathcomp);
char* cortarPath(char* path);
//TODO
int incluir_dir(int bib_fd, const char *pathdir);

#endif // FILESYSTEM_H
