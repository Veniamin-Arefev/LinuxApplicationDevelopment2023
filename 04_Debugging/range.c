//
// Created by venia on 16.10.2023.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int start = 0, step = 1, stop;
    switch (argc - 1) {
        case 1:
            stop = atoi(argv[1]);
            break;
        case 3:
            step = atoi(argv[3]);
        case 2:
            start = atoi(argv[1]);
            stop = atoi(argv[2]);
            break;
        default:
            printf("Invalid number of parameters.\n");
        case 0:
            printf("Usage is range(stop) or range(start, stop[, step]). Print numbers similar to python3 range.\n"
                   "Produces a sequence of integers from start (inclusive) to stop (exclusive) by step.\n"
            );
            exit(0);
    }
    for (int i = start; i < stop; i += step) {
        printf("%d\n", i);
    }
}