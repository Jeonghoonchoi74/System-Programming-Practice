// pipe.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    FILE* read_fp, *write_fp;
    char buf[BUFSIZ];

    read_fp = popen("who", "r");
    write_fp = popen("sort", "w");

    if (read_fp != NULL && write_fp != NULL) {
        size_t bytesRead;

        while ((bytesRead = fread(buf, sizeof(char), BUFSIZ, read_fp)) > 0) {
            fwrite(buf, sizeof(char), bytesRead, write_fp);
        }

        pclose(read_fp);
        pclose(write_fp);
        exit(0);
    }

    exit(1);
}




