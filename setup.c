#include <stdio.h>
#include "core.h"

/* Collect a valid setup, then regenerate every random value from its seed. */
void first_setup(Game *game)
{
    set_default_game(game);
    game->canvas = read_double("Square canvas side size (100-10000): ", 100, 10000);
    game->escortCount = read_int("Number of escorts (1-40): ", 1, MAX_ESCORTS);
    game->seed = (unsigned int)read_int("Random seed (1-999999): ", 1, 999999);
    game->battle.type = read_ship_type("Choose battleship code (U/M/R/S): ");
    game->battle.maxSpeed = read_double("Maximum shell speed (20-500): ", 20, 500);
    game->battle.position.x = read_double("Battleship X position: ", 0, game->canvas);
    game->battle.position.y = read_double("Battleship Y position: ", 0, game->canvas);
    generate_battlefield(game);
}

void edit_setup(Game *game)
{
    first_setup(game);
    show_setup(game);
}

void show_setup(const Game *game)
{
    int i;
    printf("Canvas %.1f x %.1f | seed %u | escorts %d\n",
           game->canvas, game->canvas, game->seed, game->escortCount);
    printf("B: %s at (%.1f, %.1f), maximum speed %.1f\n",
           battle_name(game->battle.type), game->battle.position.x,
           game->battle.position.y, game->battle.maxSpeed);
    for (i = 0; i < game->escortCount; i++) {
        const Escort *e = &game->escorts[i];
        printf("E%d %s at (%.1f, %.1f), speed %.1f..%.1f, angle %.1f..%.1f\n",
               e->id, escort_name(e->type), e->position.x, e->position.y,
               e->minSpeed, e->maxSpeed, e->minAngle, e->maxAngle);
    }
}
