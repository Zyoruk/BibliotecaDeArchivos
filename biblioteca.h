#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include <stdio.h>

typedef struct {
    char* F_Path;
}biblioteca;

biblioteca bib ;
extern int crear_bib(char *pathname , char *mode);
extern int abrir_bib();
extern int cerrar_bib();
#endif // BIBLIOTECA_H
