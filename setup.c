#include <stdio.h>
#include "core.h"
/* Rebuild positions and the route after a setup value changes. */
static void regenerate(Game *game)
{
    generate_battlefield(game);
    generate_path(game);
    printf("Battlefield regenerated.\n");
}
/* Ask the player for all values needed before the first battle. */
void first_setup(Game *game)
{
    set_default_game(game); /* Gives every field a safe starting value. */
    show_setup_art();
    printf(" \n");
    game->canvas = read_double("Square canvas side size (100-10000): ", 100.0, 10000.0);
    game->escortCount = read_int("Number of escorts (1-40): ", 1, MAX_ESCORTS);
    game->seed = (unsigned int)read_int("Random seed (1-999999): ", 1, 999999);
    game->battle.type = read_ship_type("Choose battleship code: ");
    game->battle.maxSpeed = read_double("Battleship maximum shell speed (20-500): ", 20.0, 500.0);
    game->battle.position.x = read_double("Battleship X position: ", 0.0, game->canvas);
    game->battle.position.y = read_double("Battleship Y position: ", 0.0, game->canvas);
    game->pathCount = read_int("Number of path points (2-10): ", 2, MAX_PATH);
    game->jamStep = read_int("Gun jam step: ", 1, game->pathCount - 1);
    game->jamAngle = read_double("Jammed minimum angle (1-29): ", 1.0, 29.0);
    regenerate(game);
}
/* These small functions edit one related group of settings. */
static void edit_battle(Game *game)
{
    game->battle.type = read_ship_type("Choose battleship code: ");
    game->battle.maxSpeed = read_double("Maximum shell speed (20-500): ", 20.0, 500.0);
    game->battle.position.x = read_double("Battleship X position: ", 0.0, game->canvas);
    game->battle.position.y = read_double("Battleship Y position: ", 0.0, game->canvas);
}
/* Keep the battleship inside the canvas if its size becomes smaller. */
static void edit_field(Game *game)
{
    game->canvas = read_double("Square canvas side size (100-10000): ", 100.0, 10000.0);
    game->escortCount = read_int("Number of escorts (1-40): ", 1, MAX_ESCORTS);
    if (game->battle.position.x > game->canvas ||
        game->battle.position.y > game->canvas) {
        game->battle.position.x = game->canvas / 2.0;
        game->battle.position.y = game->canvas / 2.0;
    }
}
/* Path settings also decide when and how the gun becomes jammed. */
static void edit_path(Game *game)
{
    game->pathCount = read_int("Number of path points (2-10): ", 2, MAX_PATH);
    game->jamStep = read_int("Gun jam step: ", 1, game->pathCount - 1);
    game->jamAngle = read_double("Jammed minimum angle (1-29): ", 1.0, 29.0);
}
/* Repeat the setup menu until the player chooses to return. */
void edit_setup(Game *game)
{
    int choice;

    do {
        show_setup_menu_art();
        choice = read_int("Choice: ", 1, 6);
        if (choice == 1) edit_battle(game);
        else if (choice == 2) edit_field(game);
        else if (choice == 3) edit_path(game);
        else if (choice == 4) {
            game->seed = (unsigned int)read_int("Random seed: ", 1, 999999);
        }
        if (choice != 6) regenerate(game); /* Apply the changed values. */
    } while (choice != 6);
}
/* Display the complete setup so it can be checked before a battle. */
void show_setup(const Game *game)
{
    int i;
    const Escort *escort;

    show_setup_art();
    printf("Canvas: %.1f by %.1f | Seed: %u | Escorts: %d\n",
           game->canvas, game->canvas, game->seed, game->escortCount);
    printf("Battle: %c %s at (%.1f, %.1f), Vmax %.1f\n",
           game->battle.type, battle_name(game->battle.type),
           game->battle.position.x, game->battle.position.y,
           game->battle.maxSpeed);
    printf("Gun: %s | Reload %.1f | Gamma %.3f\n",
           battle_gun(game->battle.type), game->battle.reload,
           game->battle.gamma);
    printf("Path points: %d | Jam step: %d | Jam angle: %.1f\n",
           game->pathCount, game->jamStep, game->jamAngle);
    for (i = 0; i < game->escortCount; i++) {
        escort = &game->escorts[i];
        printf("E%02d %-28s (%.1f,%.1f) V %.1f-%.1f A %.1f-%.1f ",
               escort->id, escort_name(escort->type), escort->position.x,
               escort->position.y, escort->minSpeed, escort->maxSpeed,
               escort->minAngle, escort->maxAngle);
        printf("IP %.2f R %.1f G %.3f\n", escort->impact,
               escort->reload, escort->gamma);
    }
}
