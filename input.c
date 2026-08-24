#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "input_line.h"

int read_int(const char *message, int minimum, int maximum)
{
    char line[100], *end;
    long value;
    for (;;) {
        if (!input_line(message, line, sizeof(line))) continue;
        errno = 0;
        value = strtol(line, &end, 10);
        if (errno == 0 && end != line && only_space(end) &&
            value >= minimum && value <= maximum) return (int)value;
        printf("Enter a whole number from %d to %d.\n", minimum, maximum);
    }
}

double read_double(const char *message, double minimum, double maximum)
{
    char line[100], *end;
    double value;
    for (;;) {
        if (!input_line(message, line, sizeof(line))) continue;
        errno = 0;
        value = strtod(line, &end);
        if (errno == 0 && end != line && only_space(end) &&
            isfinite(value) && value >= minimum && value <= maximum)
            return value;
        printf("Enter a number from %.1f to %.1f.\n", minimum, maximum);
    }
}

/* Require one letter, accepting lowercase and surrounding spaces. */
static char read_letter(const char *message, const char *allowed)
{
    char line[100], value, extra;
    const char *p;
    for (;;) {
        if (!input_line(message, line, sizeof(line))) continue;
        if (sscanf(line, " %c %c", &value, &extra) == 1) {
            value = (char)toupper((unsigned char)value);
            for (p = allowed; *p; p++) if (*p == value) return value;
        }
        printf("Enter one of these letters: %s.\n", allowed);
    }
}

char read_ship_type(const char *message)
{
    puts("U: USS Iowa | M: MS King George V | R: Richelieu");
    puts("S: Sovetsky Soyuz-class");
    return read_letter(message, "UMRS");
}

int read_yes_no(const char *message)
{
    return read_letter(message, "YN") == 'Y';
}
