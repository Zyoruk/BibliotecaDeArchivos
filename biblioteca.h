#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
<<<<<<< HEAD
#include <stdio.h>

typedef struct {
    char* F_Path;
}biblioteca;
=======
typedef int mode , offset , size;

typedef struct {
    const char* pPathname;
    int pFileHandle;


}biblioteca;

int abrir_bib (const char *pathname, int flags);

int crear_bib (const char *pathname, mode_t mode);

int cerrar_bib (int bib_fd);

int posseekAlPrinc (int bib_fd, const char *compname);

size print_data (int bib_fd, int comp_id, void *buf, size count);

offset repos_seek_aleatorio(int bib_fd, int comp_id, void *buf, size count);

size escribir_comp (int bib_fd, int comp_id, void *buf, size count);

int incluir_comp(int bib_fd, const char *pathcomp);

int extraer_comp (int bib_fd, int comp_id, const char *pathcomp);

int cargar_dir(int bib_fd, const char *pathdir);

int eliminar_comp (int bib_fd, int comp_id, const char *pathcomp);
>>>>>>> a71d6d81a09df1d54699bf522d64cd2b7416e7b8

biblioteca bib ;
extern int crear_bib(char *pathname , char *mode);
extern int abrir_bib();
extern int cerrar_bib();
#endif // BIBLIOTECA_H
