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
    }
    else if (child1 < 0) {
        perror("fork");
        exit(1);
    }
    
    //Child 2 생성
    child2 = fork();
    if (child2 == 0) {
        // Child 2 
        printf("Child 2: This is Child 2\n");
        execl("/bin/echo", "echo", "This is Child 2", NULL);
        // 실패 할 경우
        perror("execl");
        exit(1);
    }
    else if (child2 < 0) {
        perror("fork");
        exit(1);
    }
    
    // 부모 프로세스
    printf("Parent: Waiting for children\n");
    int status;
    
    // Child 1 종료 대기
    waitpid(child1, &status, 0);
    if (WIFEXITED(status)) {
        printf("Parent: Child 1 terminated with status %d\n", WEXITSTATUS(status));
    }
    
    // Child 2 종료 대기
    waitpid(child2, &status, 0);
    if (WIFEXITED(status)) {
        printf("Parent: Child 2 terminated with status %d\n", WEXITSTATUS(status));
    }
   
   // 완전 종료 
    printf("Parent: All Children terminated\n");
    
    return 0;
}



