#include <stdio.h>
#include "core.h"
#include "menu.h"
#include "simulation.h"


void start_menu(Game *game)
{
    int feature, field, i;
    for (i = 1; i <= 4; i++)
        printf("%d. %s\n", i, feature_name(i));
    puts("0. Run all available combinations");
    feature = read_int("Feature: ", 0, 4);
    if (feature == 0) { run_all_simulations(game); return; }
    puts("1. Static  2. Path");
    field = read_int("Field: ", 1, 2);
    run_one_simulation(game, feature, field);
}

void show_instructions(void)
{
    puts("Choose a setup, then select an available feature and battlefield.");
    puts("A repeated seed recreates the same initial ships in this build.");
    puts("All comparisons start from a fresh copy of the setup.");
}

void main_menu(Game *game)
{
    int choice;
    for (;;) {
        puts("\n1. Start simulation  2. Change setup  3. Instructions");
        puts("4. Statistics  5. Exit");
        choice = read_int("Choose an option: ", 1, 5);
        if (choice == 1) start_menu(game);
        else if (choice == 2) edit_setup(game);
        else if (choice == 3) show_instructions();
        else if (choice == 4) {
            puts("Reports and saved statistics are added on Day 12.");
        } else if (read_yes_no("Exit? (y/n): ")) return;
    }
}
