#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define NAME "socket"
#define SIZE 1024

int main() {
    int sc; 
    struct sockaddr_un *socketname = malloc(sizeof(struct sockaddr_un) + sizeof(NAME));
    char buf[SIZE] = "";

    if (socketname == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    sc = socket(PF_UNIX, SOCK_DGRAM, 0);

    socketname->sun_family = PF_UNIX;
    strcpy(socketname->sun_path, NAME);

    fgets(buf, SIZE, stdin);
    sendto(sc, (const char *)buf, SIZE, 0, (const struct sockaddr *)socketname, sizeof(struct sockaddr_un));

    unlink(NAME);
    close(sc);
    free(socketname);

    return 0;
}

