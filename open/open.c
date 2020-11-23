#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void do_open(char *file) {
    int fd = open(file, O_RDONLY);

    if (fd == -1) {
        perror("open");
        exit(1);
    }

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: open [file]\n");
        return 1;
    }
    
    do_open(argv[1]);
}
