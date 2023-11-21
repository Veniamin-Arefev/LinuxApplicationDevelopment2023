//
// Created by venia on 29.10.2023.
//

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    int maze_size = 6;

    char **maze_array = calloc(sizeof(char *), (maze_size * 2) + 1);
    for (int i = 0; i < (maze_size * 2) + 1; ++i) {
        maze_array[i] = calloc(sizeof(char), (maze_size * 2) + 2);
    }


    for (int i = 0; i < (maze_size * 2) + 1; ++i) {
        for (int j = 0; j < (maze_size * 2) + 1; ++j) {
            maze_array[i][j] = i % 2 == 1 && j % 2 == 1 ? '.' : '#';
        }
    }

//    generate maze_array

    for (int i = 1; i < (maze_size * 2); i += 2) {
        for (int j = 1; j < (maze_size * 2); j += 2) {
            if (i == 1) {
                if (j == maze_size * 2 - 1) {
                    continue;
                }
                maze_array[i][j + 1] = '.';
            } else if (j == maze_size * 2 - 1) {
                maze_array[i - 1][j] = '.';
            } else {
                int direction = rand() % 2;
                if (direction == 0) {
                    maze_array[i][j + 1] = '.';
                } else {
                    maze_array[i - 1][j] = '.';
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