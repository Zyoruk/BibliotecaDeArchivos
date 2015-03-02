#ifndef HARD_DRIVE_H
#define HARD_DRIVE_H

int abrir_bib (const char *pathname, int flags);

int crear_bib (const char *pathname, mode_t mode);

int cerrar_bib (int bib_fd);

int abrir_comp (int bib_fd, const char *compname);

ssize_t read_comp (int bib_fd, int comp_id, void *buf, size_t count);

off_t repos_comp();

ssize_t write_comp ();

int eliminar_comp (int bib_fd, const char *pathcomp);

int file_transfer(int bib_fd, const char *pathcomp);


#endif // HARD_DRIVE_H
