#include <stdio.h>
#include "core.h"
#include "files.h"
#include "menu.h"
#include "simulation.h"

/* Read the simulation type and run either one field or every field. */
void start_menu(Game *game)
{
    int feature;
    int field;
    show_start_menu_art();
    feature = read_int("Choose a feature: ", 1, 7);
    if (feature == 7) {
        return;
    }
    /* Feature 6 performs every feature and field combination automatically. */
    if (feature == 6) {
        run_all_simulations(game);
        return;
    }
    show_field_menu_art();
    field = read_int("Choose a field style: ", 1, 4);
    if (field == 4) {
        /* The constants are consecutive, so this visits all three fields. */
        for (field = STATIC_FIELD; field <= JAM_FIELD; field++) {
            run_one_simulation(game, feature, field);
        }
    } else {
        run_one_simulation(game, feature, field);
    }
}

/* Keep showing the main menu until the user confirms that they want to exit. */
void main_menu(Game *game)
{
    int choice;
    while (1) {
        show_main_menu_art();
        choice = read_int("Choose an option: ", 1, 5);
        switch (choice) {
            case 1:
                start_menu(game);
                break;
            case 2:
                show_setup(game);
                edit_setup(game);
                break;
            case 3:
                show_instructions();
                break;
            case 4:
                show_statistics();
                break;
            case 5:
                if (read_yes_no("Are you sure you want to exit? (y/n): ")) {
                    show_exit_art();
                    return;
                }
                break;
        }
    }
}
