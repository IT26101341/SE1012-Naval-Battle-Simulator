#include "core.h"
/* Clear results from an earlier battle without changing the setup. */
void reset_combat(Game *game)
{
    int i;

    game->currentTime = 0.0; /* A new simulation begins at zero seconds. */
    game->battle.alive = 1;
    game->battle.shots = 0;
    game->battle.health = 1.0;
    game->battle.nextFire = 0.0;
    game->battle.currentImpact = 1.0;
    /* Restore each ship's health, firing timer and shot counter. */
    for (i = 0; i < game->escortCount; i++) {
        game->escorts[i].alive = 1;
        game->escorts[i].shots = 0;
        game->escorts[i].stepShots = 0;
        game->escorts[i].health = 1.0;
        game->escorts[i].nextFire = 0.0;
        game->escorts[i].currentImpact = game->escorts[i].impact;
    }
    /* Mark every stored projectile slot as unused. */
    for (i = 0; i < MAX_ACTIVE_SHOTS; i++) {
        game->shots[i].active = 0;
        game->shots[i].fromBattle = 0;
        game->shots[i].escortIndex = -1;
        game->shots[i].impactTime = 0.0;
        game->shots[i].damage = 0.0;
    }
}
/* Supply a complete, sensible setup before asking the player to edit it. */
void set_default_game(Game *game)
{
    game->canvas = 1000.0;
    game->escortCount = 12;
    game->seed = 42;
    game->pathCount = 4;
    game->jamStep = 2;
    game->jamAngle = 20.0;
    game->battle.type = 'U';
    game->battle.position.x = 500.0;
    game->battle.position.y = 500.0;
    game->battle.maxSpeed = 120.0;
    generate_battlefield(game); /* Build ships from the default seed. */
    generate_path(game);        /* Build a default movement route. */
}
