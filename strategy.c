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
    int best = -1;
    double bestScore = -1.0;

    /* Check every living escort and remember the highest score. */
    for (i = 0; i < game->escortCount; i++) {
        const Escort *escort = &game->escorts[i];
        double distance;
        double time;
        double angle;
        double threatTime;
        double threatAngle;
        double power;
        double score;
        int canAttack;

        /* Do not waste another shell on a dead or already doomed escort. */
        if (!escort->alive ||
            pending_damage(game, i) >= escort->health - 0.000001) {
            continue;
        }
        /* Skip targets that cannot be reached with the allowed gun angles. */
        if (!find_shot(game->battle.position, escort->position, 0.0,
                       game->battle.maxSpeed, minAngle, 90.0,
                       &time, &angle)) {
            continue;
        }
        distance = position_distance(game->battle.position, escort->position);
        power = feature == PART_1A ? 1.0 : escort->currentImpact;
        if (power <= 0.0) {
            power = escort->impact;
        }
        /* A gun that can still hit B is a greater threat than a harmless E. */
        canAttack = (feature >= PART_2B || escort->stepShots == 0) &&
                    find_shot(escort->position, game->battle.position,
                              escort->minSpeed, escort->maxSpeed,
                              escort->minAngle, escort->maxAngle,
                              &threatTime, &threatAngle);
        score = power / (distance + 1.0);
        if (canAttack) {
            score = score + 1.0;
        }
        if (score > bestScore) {
            bestScore = score;
            best = i;
            *flightTime = time;
        }
    }
    return best;
}
