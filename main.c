#include <stdio.h>
#include "core.h"
/* A small interactive driver demonstrates all four input functions. */
int main(void)
{
    int count = read_int("Number of escorts (1-40): ", 1, MAX_ESCORTS);
    double speed = read_double("Shell speed (20-500): ", 20, 500);
    char ship = read_ship_type("Battleship code: ");
    int confirmed = read_yes_no("Use these values? (y/n): ");
    printf("Escorts=%d speed=%.1f ship=%c confirmed=%d\n",
           count, speed, ship, confirmed);
    return 0;
}
