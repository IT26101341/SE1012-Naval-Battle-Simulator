#include "core.h"
#include "simulation.h" /* Firing and reload schedules for both sides. */
int fire_battleship(Game *game, int feature, double minAngle,
                    FILE *report, Result *result)
{
    double flightTime, damage;
    int target, shotNumber;
    if (!game->battle.alive || game->currentTime + 0.000001 < game->battle.nextFire) {
        return 0;
    }
    target = choose_target(game, feature, minAngle, &flightTime); /* Best valid escort. */
    if (target < 0) return 0;
    shotNumber = game->battle.shots + 1;
    damage = feature == PART_2C ? degraded_power(1.0,
             game->battle.gamma, shotNumber) : 1.0;
    if (!add_shot(game, 1, target, game->currentTime + flightTime, damage)) { /* Queue impact. */
        return 0;
    }
    game->battle.shots = shotNumber;
    game->battle.currentImpact = damage;
    game->battle.nextFire = feature >= PART_2A ? game->currentTime + game->battle.reload : game->currentTime; /* Reload begins in Part 2A. */
    result->battleShots++;
    if (result->attackCount < MAX_ATTACKS) {
        result->attackOrder[result->attackCount] = game->escorts[target].id;
        result->attackCount++;
    }
    fprintf(report, "Time %.2f: B fired at E%d (impact %.2f).\n",
            game->currentTime, game->escorts[target].id,
            game->currentTime + flightTime);
    return 1;
}
int fire_escorts(Game *game, int feature, FILE *report, Result *result)
{
    int i, fired = 0;
    for (i = 0; i < game->escortCount && game->battle.alive; i++) { /* Try each escort. */
        Escort *escort = &game->escorts[i];
        double flightTime, angle, damage;
        int shotNumber;
        if (!escort->alive || (feature < PART_2B && escort->stepShots > 0) ||
            game->currentTime + 0.000001 < escort->nextFire) {
            continue;
        }
        if (!find_shot(escort->position, game->battle.position,
                       escort->minSpeed, escort->maxSpeed,
                       escort->minAngle, escort->maxAngle,
                       &flightTime, &angle)) {
            continue;
        }
        shotNumber = escort->shots + 1;
        if (feature == PART_1A) { /* First feature uses simple one-hit damage. */
            damage = 1.0;
        } else if (feature == PART_2C) {
            damage = degraded_power(escort->impact, escort->gamma, shotNumber);
        } else {
            damage = escort->impact;
        }
        if (!add_shot(game, 0, i, game->currentTime + flightTime, damage)) { /* Queue impact. */
            continue;
        }
        escort->shots = shotNumber;
        escort->stepShots++;
        escort->currentImpact = damage;
        if (feature >= PART_2B) {
            escort->nextFire = game->currentTime + escort->reload;
        }
        result->escortShots++;
        fired++;
        fprintf(report, "Time %.2f: E%d fired at B (impact %.2f).\n",
                game->currentTime, escort->id, game->currentTime + flightTime);
    }
    return fired;
}
double next_possible_fire(const Game *game, int feature, double minAngle)
{
    double next = -1.0, flightTime, angle;
    int i;
    if (game->battle.alive && /* Find the earliest gun ready to fire. */
        choose_target(game, feature, minAngle, &flightTime) >= 0) {
        next = game->battle.nextFire > game->currentTime ? game->battle.nextFire : game->currentTime;
    }
    for (i = 0; i < game->escortCount && game->battle.alive; i++) {
        const Escort *escort = &game->escorts[i];
        double time;
        if (!escort->alive || (feature < PART_2B && escort->stepShots > 0) ||
            !find_shot(escort->position, game->battle.position,
                       escort->minSpeed, escort->maxSpeed,
                       escort->minAngle, escort->maxAngle,
                       &flightTime, &angle)) {
            continue;
        }
        time = escort->nextFire > game->currentTime
               ? escort->nextFire : game->currentTime;
        if (next < 0.0 || time < next) {
            next = time;
        }
    }
    return next;
}
