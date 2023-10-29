//
// Created by venia on 29.10.2023.
//
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

typedef int (*check_f)(char *filename);

int open(char *filename) {
    check_f func = (check_f) dlsym(RTLD_NEXT, "open");
    printf("%s", filename);
    if (strstr(filename, "PROTECT") == NULL) {
        return func(filename);
    } else {
        return -1;
    }
}


