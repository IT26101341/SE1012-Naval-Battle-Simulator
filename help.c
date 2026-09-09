#include <stdio.h>
#include "core.h"
#include "menu.h"

/* Print a short explanation of the goal, feature levels and field styles. */
void show_instructions(void)
{
    show_help_art();
    printf("Goal: destroy escort ships while keeping the battleship safe.\n");
    printf("The square battlefield contains one battleship and many escorts.\n");
    printf("Shell range and flight time use normal projectile motion.\n\n");
    printf("FEATURE LEVELS\n");
    printf("Part 1-A: one hit sinks any ship and every escort fires once.\n");
    printf("Part 1-C: escort hits cause their listed percentage damage.\n");
    printf("Part 2-A: the battleship has reload time and chooses targets.\n");
    printf("Part 2-B: escorts reload and can fire more than once.\n");
    printf("Part 2-C: every ship's impact power falls after each shot.\n\n");
    printf("FIELD STYLES\n");
    printf("Static: fight once at the starting battleship position.\n");
    printf("Path: move through the saved path points without ship velocity.\n");
    printf("Jammed: follow the same path, then limit the gun angle.\n\n");
    printf("Use Setup to make a new battlefield and change values.\n");
    printf("Run All compares all 15 choices with the same initial setup.\n");
    printf("Every run is saved in results, and Statistics shows its summary.\n");
}
