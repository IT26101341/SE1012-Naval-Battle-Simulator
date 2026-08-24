#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_line.h"

/* Drain overlong lines so their tails cannot become another answer. */
int input_line(const char *message, char *line, size_t size)
{
    int ch;
    printf("%s", message);
    fflush(stdout);
    if (fgets(line, (int)size, stdin) == NULL) {
        puts("\nInput ended. Closing the simulator.");
        exit(0);
    }
    if (strchr(line, '\n') != NULL) return 1;
    ch = getchar();
    if (ch == '\n' || ch == EOF) return 1;
    while (ch != '\n' && ch != EOF) ch = getchar();
    puts("Input is too long. Try again.");
    return 0;
}

int only_space(const char *text)
{
    while (*text && isspace((unsigned char)*text)) text++;
    return *text == '\0';
}
