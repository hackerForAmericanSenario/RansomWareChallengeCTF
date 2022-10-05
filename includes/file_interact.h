#ifndef __FILE_INTERACT_H_
#define __FILE_INTERACT_H_

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "../includes/errors.h"

#define BEGIN_DIR "/home/ubuntu" // pour le programme final
// #define BEGIN_DIR "." // pour faire les test

typedef struct Fichier {
	char fileLink[100];
	struct Fichier *next;
} fichier_t;

int       find_files(fichier_t **files);
fichier_t *new_file(char *dirName, char *fileName);
int       add_directory_in_list(fichier_t **dossiers, char *dirName, char *fileName);
void      draw_files(fichier_t *files);
int       clear_list_file(fichier_t **files);
int       depiler_fichier(fichier_t **files);
int       cipher_file(char *file, char *key);

#endif
