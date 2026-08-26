#include <stdlib.h>
#include "core.h"

/* Gives each battleship type its own reload and decay ranges. */
static void set_battle_values(Battleship *battle)
{
    double reload = 5.0;
    double gamma = 0.010;
    if (battle->type == 'M') {
        reload = 6.0;
        gamma = 0.013;
    } else if (battle->type == 'R') {
        reload = 5.5;
        gamma = 0.011;
    } else if (battle->type == 'S') {
        reload = 7.0;
        gamma = 0.015;
    }
    battle->reload = reload + (rand() % 11) / 10.0;
    battle->gamma = gamma + (rand() % 4) / 1000.0;
}

void set_ship_properties(Game *game)
{
    /* These five array positions match the five escort types. */
    double impacts[5] = {0.08, 0.06, 0.07, 0.05, 0.04};
    double widths[5] = {20.0, 30.0, 25.0, 50.0, 70.0};
    double reloads[5];
    double gammas[5];
    int i;

    set_battle_values(&game->battle);
    /* A seed makes these small random differences repeatable. */
    for (i = 0; i < 5; i++) {
        reloads[i] = 6.0 + i + (rand() % 6) / 10.0;
        gammas[i] = 0.050 + i * 0.01 + (rand() % 5) / 1000.0;
    }
    for (i = 0; i < game->escortCount; i++) {
        Escort *ship = &game->escorts[i];
        int type = ship->type;
        int highestLow = (int)(90.0 - widths[type]); /* Keeps max angle <= 90. */
        ship->impact = impacts[type];
        ship->reload = reloads[type];
        ship->gamma = gammas[type];
        ship->minAngle = (double)(rand() % (highestLow + 1));
        ship->maxAngle = ship->minAngle + widths[type];
        /* Type 0 is faster; other types use a random speed percentage. */
        if (type == 0) ship->maxSpeed = game->battle.maxSpeed * 1.2;
        else ship->maxSpeed = game->battle.maxSpeed *
                              (0.55 + (rand() % 35) / 100.0);
        ship->minSpeed = ship->maxSpeed *
                         (0.30 + (rand() % 31) / 100.0);
    }
}
