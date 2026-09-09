#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "core.h"
/* Finish cleanly if input is closed, such as Ctrl+Z on Windows. */
static void stop_at_end_of_input(void)
{
    printf("\nInput ended. Closing the simulator.\n");
    exit(0);
}
/* Read a whole number and keep asking until it is inside the range. */
int read_int(const char *message, int minimum, int maximum)
{
    char line[100];
    char extra;
    int value;

    while (1) {
        printf("%s", message);
        /* Reading a full line prevents bad input remaining in stdin. */
        if (fgets(line, sizeof(line), stdin) == NULL)
            stop_at_end_of_input();
        /* The extra character rejects entries such as "12abc". */
        if (sscanf(line, "%d %c", &value, &extra) == 1 &&
            value >= minimum && value <= maximum) {
            return value;
        }
        printf("Enter a whole number from %d to %d.\n", minimum, maximum);
    }
}
/* This is the decimal-number version of read_int. */
double read_double(const char *message, double minimum, double maximum)
{
    char line[100];
    char extra;
    double value;

    while (1) {
        printf("%s", message);
        if (fgets(line, sizeof(line), stdin) == NULL)
            stop_at_end_of_input();
        if (sscanf(line, "%lf %c", &value, &extra) == 1 &&
            value >= minimum && value <= maximum) {
            return value;
        }
        printf("Enter a number from %.1f to %.1f.\n", minimum, maximum);
    }
}
/* Accept only one of the four battleship letters. */
char read_ship_type(const char *message)
{
    char line[100];
    char value;
    char extra;

    show_ship_choice_art();
    while (1) {
        printf("%s", message);
        if (fgets(line, sizeof(line), stdin) == NULL)
            stop_at_end_of_input();
        if (sscanf(line, " %c %c", &value, &extra) == 1) {
            value = (char)toupper((unsigned char)value); /* Allow lowercase. */
            if (value == 'U' || value == 'M' || value == 'R' || value == 'S') {
                return value;
            }
        }
        printf("Invalid ship code. Choose U, M, R or S from the list above.\n");
    }
}
/* Return 1 for yes and 0 for no. */
int read_yes_no(const char *message)
{
    char line[100];
    char value;

    while (1) {
        printf("%s", message);
        if (fgets(line, sizeof(line), stdin) == NULL)
            stop_at_end_of_input();
        if (sscanf(line, " %c", &value) == 1) {
            value = (char)toupper((unsigned char)value);
            if (value == 'Y') return 1;
            if (value == 'N') return 0;
        }
        printf("Enter Y or N.\n");
    }
}
