#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "myfifo"

int main() {
    int fifo_fd = open(FIFO_NAME, O_WRONLY);
    if (fifo_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t bytesRead;
    while ((bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        write(fifo_fd, buffer, bytesRead);
    }

    
    close(fifo_fd);

    return 0;
}

