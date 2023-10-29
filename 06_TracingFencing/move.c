//
// Created by venia on 29.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAXGR 10

enum {
    ARGC_IN_FILE = 1, ARGC_OUT_FILE = 2, BUF_SIZE = 16384
};


int main(int argc, char *argv[]) {

    char exit_code = 0;
    if (argc != 3) {
        printf("Usage is <executable> infile outfile\n");
        exit(1);
    }

    int fd_in = open(argv[ARGC_IN_FILE], O_RDONLY);
    if (fd_in == -1) {
        printf("Failed to open infile file\nError:%s\n", strerror(errno));
        exit(2);
    }
    remove(argv[ARGC_OUT_FILE]);
    int fd_out = open(argv[ARGC_OUT_FILE], O_WRONLY | O_CREAT);
    if (fd_out == -1) {
        printf("Failed to open outfile file\nError:%s\n", strerror(errno));
        printf("%s\n", strerror(errno));
        exit(3);
    }

    char *buf = malloc(BUF_SIZE * sizeof(char));
    if (buf == NULL) {
        printf("Failed to allocate buffer memory\nError:%s\n", strerror(errno));
        exit(4);
    }

    size_t b_read, b_wrote;
    while (1) {
        b_read = read(fd_in, buf, BUF_SIZE);
        if (b_read == -1) {
            printf("Failed to read from file\nError:%s\n", strerror(errno));
            exit_code = 5;
            break;
        } else if (b_read == 0) {
            break;
        }
        b_wrote = write(fd_out, buf, b_read);
        if (b_wrote == -1) {
            printf("Failed to write fo file\nError:%s\n", strerror(errno));
            exit_code = 6;
            break;
        }
    }

    b_wrote = close(fd_out);
    if (b_wrote == -1) {
        printf("Failed to close write file\nError:%s\n", strerror(errno));
        exit_code = 7;
    }
    b_read = close(fd_in);
    if (b_read == -1) {
        printf("Failed to close read file\nError:%s\n", strerror(errno));
        exit_code = 8;
    }
    if (exit_code == 0) {
        remove(argv[ARGC_IN_FILE]);
    } else {
        remove(argv[ARGC_OUT_FILE]);
    }

    return exit_code;
}