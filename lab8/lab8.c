#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LENGTH 100

int main() {
    char input[MAX_LENGTH];

    FILE *file = fopen("sample.txt", "r");
    if (file == NULL) {
        perror("파일 열기 실패");
        exit(1);
    }
    fgets(input, MAX_LENGTH, file);
    fclose(file);

    int length = strlen(input);

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        perror("파일 열기 실패");
        exit(1);
    }

    for (int i = 0; i < length-1; i++) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("자식 프로세스 생성 실패");
            exit(1);
        }

        if (child_pid == 0) {
            for (int j = 0; j <= i; j++) {
                fputc(input[j], outputFile);
            }
            fputc('\n', outputFile);
            fclose(outputFile); 
            exit(0);
        } else {
	    int status;
	    waitpid(child_pid, &status,0);
	}
    }

    fclose(outputFile);

    return 0;
}



