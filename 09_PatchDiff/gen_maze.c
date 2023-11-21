//
// Created by venia on 29.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    ARGC_SEED = 1,
    ARGC_FORMAT_SYMBOLS = 2,
    ARGC_MAZE_SIZE = 3,
    ARGC_COUNT = 4,
};


int main(int argc, char *argv[]) {
    if (argc != ARGC_COUNT) {
        printf("Usage is %s maze_size\n", argv[0]);
        exit(1);
    }

    int maze_size = atoi(argv[ARGC_MAZE_SIZE]);

    if (maze_size <= 0) {
        printf("Maze size must be positive value\n");
        exit(1);
    }

    if (strlen(argv[ARGC_FORMAT_SYMBOLS]) != 2) {
        printf("Format symbols string must include only two chars. First is path, second is wall\n");
        exit(1);
    }
    char path = argv[ARGC_FORMAT_SYMBOLS][0];
    char wall = argv[ARGC_FORMAT_SYMBOLS][1];

    char **maze_array = calloc(sizeof(char *), (maze_size * 2) + 1);
    for (int i = 0; i < (maze_size * 2) + 1; ++i) {
        maze_array[i] = calloc(sizeof(char), (maze_size * 2) + 2);
    }

    for (int i = 0; i < (maze_size * 2) + 1; ++i) {
        for (int j = 0; j < (maze_size * 2) + 1; ++j) {
            maze_array[i][j] = i % 2 == 1 && j % 2 == 1 ? path : wall;
        }
    }

    int seed = atoi(argv[ARGC_SEED]);
    srand(seed);

//    generate maze_array

    for (int i = 1; i < (maze_size * 2); i += 2) {
        for (int j = 1; j < (maze_size * 2); j += 2) {
            if (i == 1) {
                if (j == maze_size * 2 - 1) {
                    continue;
                }
                maze_array[i][j + 1] = path;
            } else if (j == maze_size * 2 - 1) {
                maze_array[i - 1][j] = path;
            } else {
                int direction = rand() % 2;
                if (direction == 0) {
                    maze_array[i][j + 1] = path;
                } else {
                    maze_array[i - 1][j] = path;
                }
            }
        }
    }

    for (int i = 0; i < (maze_size * 2) + 1; ++i) {
        printf("%s\n", maze_array[i]);
    }

    for (int i = 0; i < (maze_size * 2) + 1; ++i) {
        free(maze_array[i]);
    }

    free(maze_array);
    return 0;
}