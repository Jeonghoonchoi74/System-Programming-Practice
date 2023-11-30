#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *newPath = "~/Desktop/hoon/lab/lab7";

    char *currentPath = getenv("PATH");

    if (currentPath!=NULL) {
        printf("현재 PATH: %s\n", currentPath);

        unsetenv("PATH");

        setenv("PATH", newPath, 1);

        printf("변경된 PATH: %s\n", getenv("PATH"));
    } else {
        printf("PATH 에러.\n");
    }

    return 0;
}

