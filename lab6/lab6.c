#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

// 함수 선언
int match(char *s1, char *s2);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <디렉토리명> <확장자 명>\n", argv[0]);
	printf("예시: ./a.out ~/Desktop/hoon .txt \n");
        exit(1);
    }else{
	    printf("인자 3개 확인완료 \n");
    }
    char *directory = argv[1];
    char *target = argv[2];

    // 디렉터리 열기
    DIR *dir = opendir(directory);
    if (!dir) {
        perror("opendir");
        exit(1);
    }

    struct dirent *entry;
    struct stat file_stat;

    // 디렉터리 탐색
    while ((entry = readdir(dir)) != NULL) {
        // 접미사가 일치하면 출력하고 종료
        if (match(entry->d_name, target)) {
            char file_path[256];

            strcpy(file_path, directory);
            strcat(file_path, "/");
            strcat(file_path, entry->d_name);

            if (stat(file_path, &file_stat) == -1) {
                perror("stat");
                exit(1);
            }

            printf("File Name: %s\n", entry->d_name);
            printf("I-Node: %lu\n", (unsigned long)file_stat.st_ino);

            // 첫 번째 일치 항목만 출력 후 종료
            break;
        }
    }

    closedir(dir);
    return 0;
}

int match(char *s1, char *s2) {
    int diff = strlen(s1) - strlen(s2);
    if (strlen(s1) > strlen(s2)) {
        return (strcmp(&s1[diff], s2) == 0);
    } else {
        return 0;
    }
}



