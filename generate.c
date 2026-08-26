#include <stdlib.h>
#include "core.h"
/* Make a random coordinate between zero and the canvas edge. */
static double random_place(double canvas)
{
    return ((double)rand() / (double)RAND_MAX) * canvas;
}
/* Check that a new escort is not almost on top of another ship. */
static int position_is_close(const Game *game, Position place, int made)
{
    double x;
    double y;
    int i;

    x = place.x - game->battle.position.x;
    y = place.y - game->battle.position.y;
    if (x * x + y * y < 25.0) return 1; /* Less than 5 units away. */
    for (i = 0; i < made; i++) {
        x = place.x - game->escorts[i].position.x;
        y = place.y - game->escorts[i].position.y;
        if (x * x + y * y < 25.0) return 1;
    }
    return 0;
}
/* Create the escort positions and types for a new battlefield. */
void generate_battlefield(Game *game)
{
    int i;
    int attempts;
    int startType;
    int type;
    Position place;

    srand(game->seed); /* The same seed gives the same battlefield. */
    startType = rand() % 5;
    for (i = 0; i < game->escortCount; i++) {
        attempts = 0;
        do {
            place.x = random_place(game->canvas);
            place.y = random_place(game->canvas);
            attempts++;
        } while (position_is_close(game, place, i) && attempts < 100);
        game->escorts[i].id = i + 1;
        game->escorts[i].position = place;
        /* The first five escorts include every type once. */
        if (i < 5) type = (startType + i) % 5;
        else type = rand() % 5;
        game->escorts[i].type = type;
    }
    set_ship_properties(game); /* Fill values such as speed and damage. */
    reset_combat(game);        /* Start all ships in a fresh state. */
}
