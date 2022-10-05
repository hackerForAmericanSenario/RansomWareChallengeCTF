#ifndef __GET_KEY_H_
#define __GET_KEY_H_

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>

#include "../includes/errors.h"

#define POST_SRV 4444
#define ADDR_SRV "127.0.0.1"

typedef struct {
	char key[501];
} clef_t;

int get_key(clef_t **key);

#endif