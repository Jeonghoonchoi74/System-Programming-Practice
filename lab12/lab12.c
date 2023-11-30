#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void int_handler(int sig) {
    printf("Process %d received signal %d\n", getpid(), sig);
    exit(0);
}

int main() {
    signal(SIGINT, int_handler);

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork 실패");
        exit(1);
    } else if (child_pid == 0) {
        while (1) {
        //핸들러 호출을 위해서 대기상태로 들어가게 하지 않는다.
        }
    } else {
	printf("5초 대기\n");
        sleep(5);
        printf("자식 프로세스에게 SIGINT, 자식의 pid : %d\n", child_pid);
        kill(child_pid, SIGINT);

        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("자식 프로세스 종료 status 값 : %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}



