//
// Created by venia on 08.11.2023.
//

/** @mainpage
 * # Guesser numbers
 *
 * This is free and unencumbered software released into the public domain.
 *
 * This is simple program that can guess your hidden number with a log(max number) tries
 */

/** @file guessr.c
 * Implementation
 *
 */


#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#include "config.h"

enum {
    START = 1, /**< Minimal number for guess */
    END = 100, /**< Maximum number for guess */
    USER_ANSWER_LEN = 256 /**< Buffer for user answer */
};

int using_roman = 0; /**< Is using roman translation or not */
char number_string_buffer[1024]; /**< Predefined buffer for printing number */

#define _(STRING) gettext(STRING)

/** Translate int @p number to roman string and print if in number_string_buffer
 *
 * @param number number to translate
 * @return predefined buffer, named as number_string_buffer
 */

char * to_roman(int number) {
    char *map[] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI",
                   "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII",
                   "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX",
                   "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII",
                   "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV",
                   "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI",
                   "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI",
                   "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII",
                   "XCVIII", "XCIX", "C"};

    strcpy(number_string_buffer, map[number]);
}

/** Translate int @p number to string
 *
 * @param number number to translate
 * @return predefined buffer, named as number_string_buffer
 */

char *to_string(int number) {
    if (using_roman) {
        to_roman(number);
    } else {
        sprintf(number_string_buffer, "%d", number);
    }
    return number_string_buffer;
}


int main(int argc, char *argv[]) {
    char user_answer[USER_ANSWER_LEN];

    setlocale(LC_ALL, "");
    bindtextdomain("guessr", LOCALE_PATH);
    textdomain("guessr");

    if (argc == 2 && strcmp(argv[1], "-r") == 0) {
        using_roman = 1;
    }

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        printf(_("This is simple program that can guess your hidden number with a log(max number) tries\n"));
        return 0;
    }

    printf(_("Guess your integer between %s and %s\n"), to_string(START), to_string(END));

    printf(_("Answer on next questions only '%s' or '%s'\n"), _("yes"), _("no"));

    int left = START, right = END, mid = (left + right) / 2;
    while (left < right) {
        mid = (left + right) / 2;
        printf(_("Is your number greater than %s?\n"), to_string(mid));
        scanf("%s", user_answer);
        if (strcmp(user_answer, _("yes")) == 0) {
            left = mid + 1;
        } else if (strcmp(user_answer, _("no")) == 0) {
            right = mid;
        }
    }
    printf(_("Your number is %s.\n"), to_string(left));

    return 0;
}