#include "core.h"
#include "simulation.h"

/* Part 1-A opens with every reachable shot fired at time zero.
   Compute one-hit outcomes directly; a projectile queue follows later. */
void simulate_field(Game *game, int feature, int field,
                    FILE *report, Result *result)
{
    double firstHit = -1.0, duration = 0.0;
    int i;
    (void)feature;
    (void)field;
    for (i = 0; i < game->escortCount; i++) {
        Escort *escort = &game->escorts[i];
        double time, angle;
        if (find_shot(game->battle.position, escort->position, 0,
                      game->battle.maxSpeed, 0, 90, &time, &angle)) {
            result->battleShots++;
            game->battle.shots++;
            escort->alive = 0;
            escort->health = 0.0;
            result->escortsHit++;
            result->attackOrder[result->attackCount++] = escort->id;
            if (time > duration) duration = time;
            fprintf(report, "B fired at E%d: destruction at %.3f\n",
                    escort->id, time);
        }
        /* Escorts were alive at the common opening firing time. */
        if (find_shot(escort->position, game->battle.position,
                      escort->minSpeed, escort->maxSpeed,
                      escort->minAngle, escort->maxAngle, &time, &angle)) {
            escort->shots++;
            escort->stepShots++;
            result->escortShots++;
            result->damageBattle += 1.0;
            if (firstHit < 0.0 || time < firstHit) {
                firstHit = time;
                result->sankBy = escort->id;
            }
            if (time > duration) duration = time;
            fprintf(report, "E%d returned fire: arrival at %.3f\n",
                    escort->id, time);
        }
    }
    if (firstHit >= 0.0) {
        game->battle.alive = 0;
        game->battle.health = 0.0;
    }
    game->currentTime = duration;
    result->duration = duration;
}
