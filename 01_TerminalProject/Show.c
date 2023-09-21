//
// Created by venia on 20.09.2023.
//
#include <ncurses.h>
#include <locale.h>
#include <sys/stat.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

enum {
    TOP_PADDING = 1, LEFT_PADDING = 1,
};


int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc != 2) {
        printf("Specify file to read with first argument\n");
        return 1;
    }

    struct stat file_info;
    if (stat(argv[1], &file_info) != 0) {
        printf("Failed to read info about specified file\n");
        return 1;
    }

    char *buf = calloc(file_info.st_size + 1, sizeof(char));
    if (buf == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("Failed to open specified file\n");
        return 1;
    }
    read(fd, buf, file_info.st_size + 1);
    close(fd);


    size_t str_count = 0;
    for (size_t i = 0; i < file_info.st_size; ++i) {
        if (buf[i] == '\n') {
            str_count += 1;
        }
    }
    char **strings = calloc(str_count, sizeof(char *));
    size_t *strings_len = malloc(str_count * sizeof(size_t));
    size_t max_str_len = 0;
    if (strings == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }

    {
        size_t prev_index = 0;
        size_t str_index = 0;
        for (size_t i = 0; i < file_info.st_size; ++i) {
            if (buf[i] == '\n') {
                char *cur = malloc((i - prev_index + 1) * sizeof(char));
                if (cur == NULL) {
                    printf("Failed to allocate memory\n");
                    return 1;
                }
                memcpy(cur, buf + prev_index, i - prev_index);
                if (cur[i - prev_index - 1] == '\r') {
                    cur[i - prev_index - 1] = '\0';
                } else {
                    cur[i - prev_index] = '\0';
                }
                strings[str_index] = cur;
                strings_len[str_index] = i - prev_index;
                max_str_len = i - prev_index > max_str_len ? i - prev_index : max_str_len;

                str_index++;
                prev_index = i + 1;
            }
        }
    }
    free(buf);

    WINDOW *win;

    initscr();
    noecho();
    cbreak();
    printw("Filename: %-15s It's size: %5ld bytes", argv[1], file_info.st_size);
    refresh();

    win = newwin(LINES - TOP_PADDING, COLS, TOP_PADDING, 0);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    box(win, 0, 0);
    wmove(win, 1, 0);

    size_t height = LINES - TOP_PADDING - 2;
    size_t width = COLS - 2;

    size_t first_line_index = 0;
    size_t line_offset = 0;


    char format[32];
    char *temp_line = malloc((width + 1) * sizeof(char));
    size_t temp_max_width;
    {
        sprintf(format, "%zu", str_count);
        size_t counter_len = strlen(format);
        sprintf(format, "%%%zud: %%s", counter_len);
        temp_max_width = width - counter_len - 2;
    }

    int c = 0, exit = 0;
    char key_text[100];
    while (!exit) {
        werase(win);

        box(win, 0, 0);
        sprintf(key_text, "Pressed %s (%d); Offset:%zu", keyname(c), c, line_offset);
        mvwaddstr(win, 0, 2, key_text);

        for (size_t i = 0; i < height; ++i) {
            size_t true_index = first_line_index + i;
            if (true_index < str_count && strings_len[true_index] > line_offset) {
                strncpy(temp_line, strings[true_index] + line_offset, temp_max_width);
                temp_line[temp_max_width] = '\0';
            } else {
                temp_line[0] = '\0';
            }
            mvwprintw(win, i + 1, LEFT_PADDING, format, true_index, temp_line);
        }

        wrefresh(win);
        c = wgetch(win);
        switch (c) {
            case 27:
            case 9:
                exit = 1;
                break;
            case KEY_UP:
                if (first_line_index > 0)
                    first_line_index -= 1;
                break;
            case 32:
            case KEY_DOWN:
                if (first_line_index + height < str_count + 1)
                    first_line_index += 1;
                break;
            case KEY_PPAGE:
                if (first_line_index > 0) {
                    if (first_line_index < height) {
                        first_line_index = 0;
                    } else {
                        first_line_index -= height;
                    }
                }
                break;
            case KEY_NPAGE:
                first_line_index += height;
                if (first_line_index + height > str_count) {
                    first_line_index = str_count - height + 1;
                }
                break;
            case KEY_RIGHT:
                if (max_str_len > width && line_offset < max_str_len - width + 20)
                    line_offset += 1;
                break;
            case KEY_LEFT:
                if (line_offset > 0)
                    line_offset -= 1;
                break;
            default:
                break;
        }
    }
    endwin();

    for (size_t i = 0; i < str_count; ++i) {
        free(strings[i]);
    }
    free(strings);
}
