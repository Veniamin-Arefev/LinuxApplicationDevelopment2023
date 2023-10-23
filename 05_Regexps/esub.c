//
// Created by venia on 16.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAXGR 10

enum {
    REGEXP_INDEX = 1, SUBSTITUTION_INDEX = 2, STRING_INDEX = 3
};

void log_error(int status, regex_t *reg) {
    size_t error_size = regerror(status, reg, NULL, 0);
    char *error_string = malloc((error_size + 1) * sizeof(char));
    regerror(status, reg, error_string, error_size);
    printf("%s\n", error_string);
    free(error_string);

}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage is <executable> regexp substitution string\n");
        exit(0);
    }
    int status;
    regex_t regex;
    status = regcomp(&regex, argv[REGEXP_INDEX], REG_EXTENDED);
    if (status != 0) {
        log_error(status, &regex);
        exit(1);
    }

    regmatch_t bags[MAXGR];

    status = regexec(&regex, argv[STRING_INDEX], MAXGR, bags, 0);
    if (status != 0) {
        log_error(status, &regex);
        exit(1);
    }

    int found_bags = 0;
    for (int i = 1; i < MAXGR && bags[i].rm_so >= 0; i++) {
        found_bags++;
//        int b = bags[i].rm_so, e = bags[i].rm_eo;
//        printf("%d %d/%d\t%.*s\n", i, b, e, e - b, argv[STRING_INDEX] + b);
    }

    size_t total_len = strlen(argv[STRING_INDEX]) - (bags[0].rm_eo - bags[0].rm_so);
    size_t sub_raw_len = strlen(argv[SUBSTITUTION_INDEX]);
    for (int i = 0; i < sub_raw_len; ++i) {
        if (argv[SUBSTITUTION_INDEX][i] == '\\' && (i + 1) < sub_raw_len) {
            if (argv[SUBSTITUTION_INDEX][i + 1] == '\\') {
                total_len += 1;
                ++i;
            }
            if (argv[SUBSTITUTION_INDEX][i + 1] >= '0' && argv[SUBSTITUTION_INDEX][i + 1] <= '9') {
                size_t bag_number = argv[SUBSTITUTION_INDEX][i + 1] - '0';
                if (bag_number > found_bags) {
                    printf("Error in substitution string. Cant match not found bag.\n");
                    exit(1);
                }
                total_len += bags[bag_number].rm_eo - bags[bag_number].rm_so;
                ++i;
            }
        } else {
            total_len += 1;
        }
    }
    char *result = calloc(total_len + 1, sizeof(char));
    size_t cur_index = 0;
    for (; cur_index < bags[0].rm_so; ++cur_index) {
        result[cur_index] = argv[STRING_INDEX][cur_index];
    }

    for (int i = 0; i < sub_raw_len; ++i) {
        if (argv[SUBSTITUTION_INDEX][i] == '\\' && (i + 1) < sub_raw_len) {
            if (argv[SUBSTITUTION_INDEX][i + 1] == '\\') {
                result[cur_index++] = '\\';
                ++i;
            }
            if (argv[SUBSTITUTION_INDEX][i + 1] >= '0' && argv[SUBSTITUTION_INDEX][i + 1] <= '9') {
                size_t bag_number = argv[SUBSTITUTION_INDEX][i + 1] - '0';
                size_t bag_length = bags[bag_number].rm_eo - bags[bag_number].rm_so;
                strncpy(result + cur_index, argv[STRING_INDEX] + bags[bag_number].rm_so, bag_length);
                cur_index += bag_length;
                ++i;
            }
        } else {
            result[cur_index++] = argv[SUBSTITUTION_INDEX][i];
        }
    }

    size_t len_to_write = strlen(argv[STRING_INDEX]) - bags[0].rm_eo;
    for (int i = 0; i < len_to_write; ++i) {
        result[total_len - len_to_write + i] = argv[STRING_INDEX][bags[0].rm_eo + i];
    }

    printf("%s\n", result);

    regfree(&regex);
}