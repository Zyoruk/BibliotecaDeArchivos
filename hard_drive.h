#ifndef HARD_DRIVE_H
#define HARD_DRIVE_H

struct FS {
    int id;
    char* filename;
};

//----------HARD DRIVE RELATED----------//

int create(const char *pathname, mode pmode);

int umount(int bib_fd);

int mount(const char *pathname, int flags);

//----------FILE SYSTEM RELATED----------//

int import(int bib_fd, const char *path, char *opt);

int exportFile(int bib_fd, int comp_id, const char *pathcomp);

int openc(int bib_fd, const char *compname);

int listc (int bib_fd);

ssize_t print(int bib_fd, int comp_id, void *buf, size_t count);

int del(int bib_fd, const char *pathcomp);

//----------------------------No UI Connection--------------------------------//

off_t repos_comp();

ssize_t write_comp ();

#endif // HARD_DRIVE_H
