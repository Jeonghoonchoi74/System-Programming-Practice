#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NAME "socket"
#define SIZE 1024

void main() {
    int sock, length, fromlen;
    struct sockaddr_un name, from;     char buf[SIZE] = "";

    sock = socket(PF_UNIX, SOCK_DGRAM, 0);
    name.sun_family = PF_UNIX;
    strcpy(name.sun_path, NAME);
    bind(sock, (struct sockaddr*)&name, sizeof(struct sockaddr_un));
    printf("socket -> %s\n", NAME);

    recvfrom(sock, buf, SIZE, 0, (struct sockaddr *)&from, &fromlen);
    printf("->%s\n", buf);

    unlink(NAME);
    close(sock);
}
