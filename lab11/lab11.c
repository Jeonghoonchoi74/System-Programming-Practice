#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
int sigint_count = 0;

void sig_handler(int signo) {
    if (signo == SIGINT) {
        sigint_count++;
        printf("SIGINT 입력  (%d 번)\n", sigint_count);
    } else if (signo == SIGQUIT) {
        printf("SIGQUIT 입력\n");
	printf("SIGINT 총 입력 수 : %d 번\n",sigint_count);
	printf("종료\n");
        exit(0);
    }
}

int main() {
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        perror("Unable to register SIGINT handler");
        exit(1);
    }

    if (signal(SIGQUIT, sig_handler) == SIG_ERR) {
        perror("Unable to register SIGQUIT handler");
        exit(1);
    }

    printf("Ctrl+C (SIGINT)를 누르면 count 증가 혹은 Ctrl+\\ (SIGQUIT) 누를 시 종료\n");

    for (;;) {
        pause();  // Wait for signals
    }

    return 0;
}



