#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define SUCCESS 0
#define WRONG_FLAG "wf"
#define LIB_ERROR "404: Lib not found."

#include <stdio.h>

typedef int boolean;
typedef const char* mode;
typedef struct componente_struct* componente;

 struct componente_struct {
    const char* comp_nom;
    int rango[2];
    boolean _lleno : 1;
//    int (*crear_bibptr)(const void* miInstancia, const char*pathname , mode pmode);
};

componente ptr_comp_list[10];
//done
//int crear_bib (const void* miInstancia ,const char *pathname, mode pmode);
int crear_bib (const char *pathname, mode pmode);
int abrir_bib (const char *pathname, int flags);
int cerrar_bib (int bib_fd);

//TODO
int abrir_comp (int bib_fd, const char *compname);

size_t print_data (int bib_fd, int comp_id, void *buf, size_t count);

off_t repos_seek_aleatorio(int bib_fd, int comp_id, void *buf, size_t count);

size_t escribir_comp (int bib_fd, int comp_id, void *buf, size_t count);

int incluir_comp(int bib_fd, const char *pathcomp);

int extraer_comp (int bib_fd, int comp_id, const char *pathcomp);

int cargar_dir(int bib_fd, const char *pathdir);

int eliminar_comp (int bib_fd, int comp_id, const char *pathcomp);

//aux

//componente newComponente();

#endif // BIBLIOTECA_H
