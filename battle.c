#include "simulation.h"

/* Runs all firing and impact events while ships stay at one position. */
double run_position(Game *game, int feature, double minAngle,
                    FILE *report, Result *result, int step)
{
    double startTime = game->currentTime;
    fprintf(report, "\nStep %d: B at (%.1f, %.1f), minimum angle %.1f\n",
            step, game->battle.position.x, game->battle.position.y, minAngle);
    while (game->battle.alive || has_active_shots(game)) {
        double impactTime;
        double fireTime;
        double next = -1.0;
        int fired;

        /* Resolve shots that arrive now before allowing another attack. */
        apply_impacts(game, game->currentTime, report, result);
        if (game->battle.alive) {
            fired = fire_battleship(game, feature, minAngle, report, result);
            /* Early features have no reload delay, so B fires at every target. */
            if (feature < PART_2A) {
                int tries = 1;
                while (fired && tries < game->escortCount) {
                    fired = fire_battleship(game, feature, minAngle,
                                            report, result);
                    tries++;
                }
            }
            fire_escorts(game, feature, report, result);
        }
        /* Jump straight to the next impact or time when a gun can fire. */
        impactTime = next_impact_time(game);
        fireTime = game->battle.alive
                   ? next_possible_fire(game, feature, minAngle) : -1.0;
        if (impactTime > game->currentTime + 0.000001) {
            next = impactTime;
        }
        if (fireTime > game->currentTime + 0.000001 &&
            (next < 0.0 || fireTime < next)) {
            next = fireTime;
        }
        /* A negative time means that no further event is possible. */
        if (next < 0.0) {
            break;
        }
        game->currentTime = next;
    }
    return game->currentTime - startTime;
}

void simulate_field(Game *game, int feature, int field,
                    FILE *report, Result *result)
{

    /* Each selected battlefield starts with a clean event list and clock. */
    clear_shots(game);
    game->currentTime = 0.0;
    fprintf(report, "Feature: %d\nField style: %d\n", feature, field);
    run_position(game, feature, 0.0, report, result, 1);
    result->duration = game->currentTime;
    fprintf(report, "\nBattle duration: %.2f seconds\n", result->duration);
    fprintf(report, "Escorts destroyed: %d\n", result->escortsHit);
    fprintf(report, "Damage received by B: %.3f\n", result->damageBattle);
}
