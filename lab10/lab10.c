#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child1, child2;

    // Child 1 생성
    child1 = fork();
    if (child1 == 0) {
        // Child 1
        printf("Child 1: This is Child 1\n");
        execl("/bin/echo", "echo", "This is Child 1", NULL);
        // 실패 할 경우
        perror("execl");
        exit(1);
    } else if (child1 < 0) {
        perror("fork");
        exit(1);
    }

    // Child 2 생성
    child2 = fork();
    if (child2 == 0) {
        // Child 2 process
        printf("Child 2: This is Child 2\n");
        execl("/bin/echo", "echo", "This is Child 2", NULL);
        // 실패 할 경우
        perror("execl");
        exit(1);
    } else if (child2 < 0) {
        perror("fork");
        exit(1);
    }

    // 부모 프로세스
    printf("Parent: Waiting for children\n");
    int status;
    
    // Child number에 맞게 종료
    pid_t firstChild = wait(&status);
    if (firstChild == child1) {
        printf("Parent: First Child: Child 1 terminated with status %d\n", WEXITSTATUS(status));
    } else if (firstChild == child2) {
        printf("Parent: First Child: Child 2 terminated with status %d\n", WEXITSTATUS(status));
    }

    // Child number에 맞게 종료
    pid_t secondChild = wait(&status);
    if (secondChild == child1) {
        printf("Parent: Second Child: Child 1 terminated with status %d\n", WEXITSTATUS(status));
    } else if (secondChild == child2) {
        printf("Parent: Second Child: Child 2 terminated with status %d\n", WEXITSTATUS(status));
    }

    //종료
    printf("Parent: All Children terminated\n");

    return 0;
}



