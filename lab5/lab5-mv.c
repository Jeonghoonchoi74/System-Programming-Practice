#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
	    printf("입력인자가 3개가 아님\n");
	    exit(1);
    }

    const char *src_file = argv[1];
    const char *dest_file = argv[2];

    // 원본 파일을 새로운 파일로 복사
    if (link(src_file, dest_file) != 0) {
        perror("파일 복사 실패");
        exit(1);
    }

    // 원본 파일 삭제
    if (unlink(src_file) != 0) {
        perror("원본 파일 삭제 실패");
        // 실패 시 새로운 파일을 삭제한다
        if (unlink(dest_file) != 0) {
            perror("새로운 파일 삭제 실패");
        }
        exit(1);
    }

    printf("%s 파일이 %s 파일로 이름변경 완료.\n", src_file, dest_file);
    
    return 0;
}

