#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "myfifo"

int main() {
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    int fifo_fd = open(FIFO_NAME, O_RDONLY);
    if (fifo_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t bytesRead;
    while ((bytesRead = read(fifo_fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    close(fifo_fd);

    if (unlink(FIFO_NAME) == -1) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}

