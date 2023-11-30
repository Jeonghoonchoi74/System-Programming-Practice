#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFSIZE 512

int main() 
{
    char afile[] = "afile";
    char bfile[] = "bfile";
    int original, copy;
    ssize_t nread;
    char buffer[BUFSIZE];

    if ((original = open(afile, O_RDONLY)) == -1) 
    {
        perror(" 열기 실패 (afile)");
        exit(1);
    }

    if ((copy = open(bfile, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) 
    {
        perror("열기 실패 (bfile)");
        close(original);
        exit(1);
    }

    off_t source_size = lseek(original, 0, SEEK_END);
    lseek(original, 0, SEEK_SET);

    if (source_size < BUFSIZE) 
    {
        if ((nread = read(original, buffer, source_size)) > 0) 
	{
            if (write(copy, buffer, nread) != nread) 
	    {
                perror("작성 실패");
                close(original);
                close(copy);
                exit(1);
            }
        }
    } 
    else 
    {   
        while ((nread = read(original, buffer, BUFSIZE)) > 0) 
	{
            if (write(copy, buffer, nread) != nread) 
	    {
                perror("작성 실패");
                close(original);
                close(copy);
                exit(1);
            }
        }
    }

    close(original);
    close(copy);
    return 0;
}
