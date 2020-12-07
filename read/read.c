#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int do_open(char *file) {
    int fd = open(file, O_RDONLY);

    if (fd == -1) {
        perror("open");
        exit(1);
    }

    return fd;
}

int safe_atoi(char *s) {
    if (s[0] == '0' && s[1] == '\0') {
        return 0;
    }
    
    int num;
    if ((num = atoi(s)) == 0) {
        printf("num_bytes must be a number\n");
        exit(1);
    }

    return num;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Reads the specified number of bytes from a file.\n");
        printf("Usage: read [file] [num-bytes]\n");
        exit(1);
    }


    int num_bytes, num_read;
    num_bytes = safe_atoi(argv[2]);
    int fd = do_open(argv[1]);

    printf("fd=%d\n", fd);

    char buf[num_bytes + 1];

    if ((num_read = read(fd, &buf, num_bytes)) == -1) {
        perror("read");
    }

    buf[num_bytes] = '\0';

    printf("%s\n", buf);
    
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
}
