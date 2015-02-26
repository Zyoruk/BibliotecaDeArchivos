#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include <stdio.h>

typedef int  offset , size;
typedef const char* mode;

typedef struct {
    const char* F_Path;
    int pFileHandle;
}biblioteca;

biblioteca bib ;

//done
int crear_bib (const char *pathname, mode pmode);
int abrir_bib (const char *pathname, int flags);
int cerrar_bib (int bib_fd);
//TODO
int posseekAlPrinc (int bib_fd, const char *compname);

size print_data (int bib_fd, int comp_id, void *buf, size count);

offset repos_seek_aleatorio(int bib_fd, int comp_id, void *buf, size count);

size escribir_comp (int bib_fd, int comp_id, void *buf, size count);

int incluir_comp(int bib_fd, const char *pathcomp);

int extraer_comp (int bib_fd, int comp_id, const char *pathcomp);

int cargar_dir(int bib_fd, const char *pathdir);

int eliminar_comp (int bib_fd, int comp_id, const char *pathcomp);

//aux


#endif // BIBLIOTECA_H
