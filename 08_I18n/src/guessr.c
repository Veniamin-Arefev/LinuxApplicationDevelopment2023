//
// Created by venia on 08.11.2023.
//

#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#include "config.h"

enum {
    START = 0,
    END = 100,
    USER_ANSWER_LEN = 256
};

#define _(STRING) gettext(STRING)

int main(int argc, char *argv[]) {
    char user_answer[USER_ANSWER_LEN];

    setlocale(LC_ALL, "");
    bindtextdomain("guessr", LOCALE_PATH);
    textdomain("guessr");

    printf(_("Guess your integer between %d and %d\n"), START, END);

    printf(_("Answer on next questions only '%s' or '%s'\n"), _("yes"), _("no"));

    int left = START, right = END, mid = (left + right) / 2;
    while (left < right) {
        mid = (left + right) / 2;
        printf(_("Is your number greater than %d?\n"), mid);
        scanf("%s", user_answer);
        if (strcmp(user_answer, _("yes")) == 0) {
            left = mid + 1;
        } else if (strcmp(user_answer, _("no")) == 0) {
            right = mid;
        }
    }
    printf(_("Your number is %d.\n"), left);

    return 0;
}