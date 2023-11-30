#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char filename[] = "test.txt"; // 파일 이름
    char content[] = "abcdefghijklmnop"; // 저장할 내용
    int fd; // 파일 디스크립터
    char buffer[1]; // 1 바이트씩 읽은 데이터를 저장할 버퍼

        if ((fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
        perror("open");
        exit(1);
    }

    if (write(fd, content, strlen(content)) == -1) {
        perror("write");
        close(fd);
        exit(1);
    }

    if (lseek(fd, 10, SEEK_SET) == -1) {
        perror("lseek");
        close(fd); 
        exit(1);
    }

    for (int i = 0; i < 6; i++) {
        if (read(fd, buffer, sizeof(buffer)) == -1) {
            perror("read");
            close(fd);
            exit(1);
        }        
        write(STDOUT_FILENO, buffer, sizeof(buffer));
    }
        
    off_t end_position = lseek(fd, -5, SEEK_END); 
    if (end_position == -1) {
        perror("lseek");
        close(fd);
        exit(1);
    }
    
    write(STDOUT_FILENO, " ", 1); //출력 구분을 위한 공백 추가

    for (off_t pos = 0; pos < end_position; pos++) {
        if (lseek(fd, pos, SEEK_SET) == -1) {
            perror("lseek");
            close(fd);
             exit(1);
        }

	if (read(fd, buffer, sizeof(buffer)) == -1) {
            perror("read");
            close(fd); 
            exit(1);
        }  
        write(STDOUT_FILENO, buffer, sizeof(buffer));
    }

    write(STDOUT_FILENO, "\n", 1);

    close(fd);
    return 0;
}



