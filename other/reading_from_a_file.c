#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int fd = open("demo.txt", O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    #define MAX_BUF 1024

    char buffer[MAX_BUF + 1];
    ssize_t bytesRead = read(fd, buffer, MAX_BUF);
    if(bytesRead == -1){
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    buffer[bytesRead] = '\0';
    write(STDOUT_FILENO, buffer, bytesRead);

    close(fd);
    exit(EXIT_SUCCESS);
}
