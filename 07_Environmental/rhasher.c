//
// Created by venia on 06.11.2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "rhash.h"

#include "config.h"

#ifdef READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif


int main(int argc, char *argv[]) {
    rhash_library_init();

    char digest_static[64];
    char *digest = digest_static;
    char output[130];

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;


#ifndef READLINE
    while ((nread = getline(&line, &len, stdin)) != -1) {
#else
        while ((line = readline(">")) != NULL) {
#endif
        char *token = strtok(line, " ");

        char *alg = NULL;
        char *to_hash = NULL;

        for (int j = 1;; j++, token = strtok(NULL, " ")) {
            if (token == NULL)
                break;
//            printf("%d: %s\n", j, token);

            if (j == 1) {
                alg = token;
            } else if (j == 2) {
                to_hash = token;
            }
        }
        if (alg == NULL || to_hash == NULL) {
            continue;
        }

        unsigned PRINT_FLAG = islower(alg[0]) ? RHPR_BASE64 : RHPR_HEX;
        for (int i = 0; i < strlen(alg); ++i) {
            alg[i] = (char) toupper(alg[i]);
        }

//        printf("a = %s t = %s\n", alg, to_hash);

        unsigned int hash_id;

        if (strcmp(alg, "MD5") == 0) {
            hash_id = RHASH_MD5;
        } else if (strcmp(alg, "SHA1") == 0) {
            hash_id = RHASH_SHA1;
        } else if (strcmp(alg, "TTH") == 0) {
            hash_id = RHASH_TTH;
        }

        int res = 0;
        if (to_hash[0] == '\"') {
            res = rhash_msg(hash_id, to_hash + 1, strlen(to_hash + 1) - strlen(strstr(to_hash + 1, "\"")), digest);
        } else {
            res = rhash_file(hash_id, to_hash, digest);
        }
        if (res < 0) {
            fprintf(stderr, "LibRHash error: %s\n", strerror(errno));
            continue;
        }

        rhash_print_bytes(output, digest, rhash_get_digest_size(hash_id), (PRINT_FLAG | RHPR_UPPERCASE));

        printf("Digest : %s\n", output);
    }

    free(line);
    return 0;
}
