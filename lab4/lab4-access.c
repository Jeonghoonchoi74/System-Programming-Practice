#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <error.h>

#define DATA_SIZE 20

int main(int argc, char *argv[]) {
    if (argc != 2) { // 2개의 인자가 입력이 안됐을 경우
        fprintf(stderr, "Usage: %s <file-name>\n", argv[0]);
        exit(1);
    }

    char filename[256]; // 파일 이름을 저장할 배열
    strncpy(filename, argv[1], sizeof(filename) - 1);
    filename[sizeof(filename) - 1] = '\0'; // 파일 이름 길이 제한

    int fd;

    // 파일이 존재하는지 확인
    if (access(filename, F_OK) != -1) {
        // 파일이 존재하면 읽기 모드로 열고 데이터 읽기
        if ((fd = open(filename, O_RDONLY)) == -1) {
            perror("open");
            exit(1);
        }

        char data[DATA_SIZE];
        ssize_t nread;

        if ((nread = read(fd, data, sizeof(data))) == -1) {
            perror("read");
            close(fd);
            exit(1);
        }

        // 데이터 출력
        write(STDOUT_FILENO, data, nread);
        close(fd);
    } else {
        // 파일이 존재하지 않으면 파일 생성 후 "hello world" 쓰기
        if ((fd = creat(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
            perror("creat");
            exit(1);
        }

        char message[] = "hello world"; // 문자열 배열로 변경
        if (write(fd, message, strlen(message)) == -1) {
            perror("write");
            close(fd);
            exit(1);
        }

        close(fd);
    }

    return 0;
}


