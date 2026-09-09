#include <stdio.h>
#include "core.h"

/* Menu artwork is kept here so menus.c can focus on handling choices. */
void show_main_menu_art(void)
{
    printf("\n+===================================================+\n");
    printf("|          N A V A L   C O M M A N D                |\n");
    printf("+---------------------------------------------------+\n");
    printf("|  [1]  >>  START SIMULATION                        |\n");
    printf("|  [2]  >>  OPEN DOCKYARD SETUP                     |\n");
    printf("|  [3]  >>  READ CAPTAIN'S INSTRUCTIONS             |\n");
    printf("|  [4]  >>  VIEW FLEET ARCHIVES                     |\n");
    printf("|  [5]  >>  RETURN TO PORT                          |\n");
    printf("+---------------------------------------------------+\n");
    printf("~~~~~~~~~~~~  AWAITING YOUR ORDERS  ~~~~~~~~~~~~~~~~\n");
}

void show_start_menu_art(void)
{
    /* Each feature number selects a different stage of the assignment. */
    printf("\n                 __/___\n");
    printf("           _____/______|\n");
    printf("   _______/____________|_____\n");
    printf("   \\  ENGAGE THE ENEMY!    /\n");
    printf("~~~~\\_____________________/~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("|  [1]  Part 1-A : Basic battle                     |\n");
    printf("|  [2]  Part 1-C : Escort impact power              |\n");
    printf("|  [3]  Part 2-A : Reload and attack strategy       |\n");
    printf("|  [4]  Part 2-B : Continuous escort fire           |\n");
    printf("|  [5]  Part 2-C : Impact power degradation         |\n");
    printf("|  [6]  Run all 15 battle combinations              |\n");
    printf("|  [7]  Return to Naval Command                     |\n");
    printf("+---------------------------------------------------+\n");
}

void show_field_menu_art(void)
{
    /* A field style controls how the battleship moves during a battle. */
    printf("\n+---------------------------------------------------+\n");
    printf("|          SELECT A BATTLEFIELD COURSE              |\n");
    printf("+---------------------------------------------------+\n");
    printf("|  [1]  [ANCHOR]  Static battlefield                |\n");
    printf("|  [2]  [PATH]    Battleship route                  |\n");
    printf("|  [3]  [JAM]     Jammed gun route                  |\n");
    printf("|  [4]  [ALL]     Run all three courses             |\n");
    printf("+---------------------------------------------------+\n");
}

void show_ship_choice_art(void)
{
    /* Show every code and full name before asking for a ship letter. */
    printf("\n                 __/___          ___\n");
    printf("           _____/______|________/___\\__\n");
    printf("     _____/   ==   ==   ==             \\___\n");
    printf("     \\_____________________________________/\n");
    printf("~~~~~~~~~~~~  CHOOSE YOUR FLAGSHIP  ~~~~~~~~~~~~~\n");
    printf("+---------------------------------------------------+\n");
    printf("|  [U]  USS Iowa (BB-61)                            |\n");
    printf("|  [M]  MS King George V                            |\n");
    printf("|  [R]  Richelieu                                   |\n");
    printf("|  [S]  Sovetsky Soyuz-class                        |\n");
    printf("+---------------------------------------------------+\n");
}

void show_setup_menu_art(void)
{
    /* Reuse the dockyard picture before showing the setup choices. */
    show_setup_art();
    printf("+---------------------------------------------------+\n");
    printf("|  [1]  Battleship                                  |\n");
    printf("|  [2]  Battlefield and escort fleet                |\n");
    printf("|  [3]  Route and gun jam                           |\n");
    printf("|  [4]  Random seed                                 |\n");
    printf("|  [5]  Regenerate battlefield                      |\n");
    printf("|  [6]  Return to Naval Command                     |\n");
    printf("+---------------------------------------------------+\n");
}
