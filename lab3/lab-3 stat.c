#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    const char *filename = "dummy.txt"; // 파일 경로를 지정
    const char *content = "this is test file"; // 파일에 쓸 내용
    const char *content2 = "this is second info"; //두번째 접근 때 쓸 내용
    struct stat file_info;
    int fd;

    // 파일을 생성하거나 열기
    if ((fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
        perror("open");
        exit(1);
    }

    // 파일에 내용 쓰기
    if (write(fd, content, strlen(content)) == -1) {
        perror("write");
        close(fd); // 파일 닫기
        exit(1);
    }

    // 파일 정보 가져오기
    if (stat(filename, &file_info) == 0) {
        printf("%s의 inode 위치는: %ld\n", filename, (unsigned long)file_info.st_ino);
        printf("최종 상태 변경 시각 : %ld\n", (long)file_info.st_ctime);
        printf("최종 변경 시각 : %ld\n", (long)file_info.st_mtime);
        printf("최종 엑세스 시각 : %ld\n", (long)file_info.st_atime);
    } else {
        perror("stat");
    }

    printf("\n 2초간 기다리기\n\n");
    //2초간 기다리기
    sleep(2);
    
    // 파일을 생성하거나 열기 
    if ((fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
        perror("open");
        exit(1);
    }
    // 파일에 내용 쓰기
    if (write(fd, content2, strlen(content2)) == -1) {
        perror("write");
        close(fd); // 파일 닫기
        exit(1);
    }
    
    // 파일 정보 가져오기
    if (stat(filename, &file_info) == 0) {
    	printf("다시 파일에 접근 후 출력\n");
        printf("%s의 inode 위치는: %ld\n", filename, (unsigned long)file_info.st_ino);
        printf("최종 상태 변경 시각 : %ld\n", (long)file_info.st_ctime);
        printf("최종 변경 시각 : %ld\n", (long)file_info.st_mtime);
        printf("최종 엑세스 시각 : %ld\n", (long)file_info.st_atime);
    } else {
        perror("stat");
    }

    // 파일 닫기
    close(fd);

    return 0;
}

