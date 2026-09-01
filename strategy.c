#include "core.h"

/* Totals shells already travelling toward one escort. */
double pending_damage(const Game *game, int escortIndex)
{
    double total = 0.0;
    int i;

    for (i = 0; i < MAX_ACTIVE_SHOTS; i++) {
        if (game->shots[i].active && game->shots[i].fromBattle &&
            game->shots[i].escortIndex == escortIndex) {
            total = total + game->shots[i].damage;
        }
    }
    return total;
}

int choose_target(const Game *game, int feature, double minAngle,
                  double *flightTime)
{
    int i;
    double angle;
    (void)feature;
    /* Use the first reachable escort; threat ranking is added on Day 8. */
    for (i = 0; i < game->escortCount; i++) {
        const Escort *e = &game->escorts[i];
        if (e->alive && pending_damage(game, i) < e->health - 0.000001 &&
            find_shot(game->battle.position, e->position, 0,
                      game->battle.maxSpeed, minAngle, 90, flightTime, &angle))
            return i;
    }
    return -1;
}
