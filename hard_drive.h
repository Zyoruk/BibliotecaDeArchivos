#ifndef HARD_DRIVE_H
#define HARD_DRIVE_H
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"
#define INITIAL_SIZE 5
#define offset 0.5

//----------INDEX RELATED---------------//
typedef struct{
    int id;
    char* filename;
}FS;

struct FS *sarray[INITIAL_SIZE];

void initializeStructs();

//----------HARD DRIVE RELATED----------//

void create(const char *pathname, mode_t pmode);

void umount(int bib_fd);

void mount(const char *pathname, int flags);

//----------FILE SYSTEM RELATED----------//

void import(char* bib_fd, const char *path, char *opt);

void exportFile(char* bib_fd, int comp_id, const char *pathcomp);

void openc(char* bib_fd, const char *compname);

int listComp (int bib_fd);

void print(char* bib_fd, int comp_id, size_t count);

void del(char* bib_fd, const char *pathcomp);

//----------------------------No UI Connection--------------------------------//

off_t repos_comp();

ssize_t write_comp ();

#endif // HARD_DRIVE_H
