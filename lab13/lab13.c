#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) != 0) {
        perror("pipe");
        exit(1);
    }

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) { // 자식 프로세스
        close(fd[1]); // 자식은 파이프의 쓰기 끝을 닫음

        if (fd[0] != STDIN_FILENO) {
            dup2(fd[0], STDIN_FILENO); // 파이프의 읽기 끝을 표준 입력으로 복사
            close(fd[0]); // 복사가 완료되면 파이프 읽기 끝을 닫음
        }

        execlp("grep", "grep", "telnet", NULL);
        perror("exec failed");
        exit(1);
    } else { // 부모 프로세스
        if (fd[1] != STDOUT_FILENO) {
            dup2(fd[1], STDOUT_FILENO); // 파이프의 쓰기 끝을 표준 출력으로 복사
            close(fd[1]); // 복사가 완료되면 파이프 쓰기 끝을 닫음
        }

        execlp("ps", "ps", "-ef", NULL);
        perror("exec failed");
        exit(1);
    }

    return 0;
}

