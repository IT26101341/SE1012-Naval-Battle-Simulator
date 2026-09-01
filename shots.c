#include "simulation.h" /* Stores shells until their calculated impact time. */
void clear_shots(Game *game)
{
    int i;

    for (i = 0; i < MAX_ACTIVE_SHOTS; i++) { /* Reset every projectile slot. */
        game->shots[i].active = 0;
        game->shots[i].fromBattle = 0;
        game->shots[i].escortIndex = -1;
        game->shots[i].impactTime = 0.0;
        game->shots[i].damage = 0.0;
    }
}

int add_shot(Game *game, int fromBattle, int escortIndex,
             double impactTime, double damage)
{
    int i;

    if (escortIndex < 0 || escortIndex >= game->escortCount) {
        return 0;
    }
    for (i = 0; i < MAX_ACTIVE_SHOTS; i++) {
        if (!game->shots[i].active) { /* Use the first empty array slot. */
            game->shots[i].active = 1;
            game->shots[i].fromBattle = fromBattle;
            game->shots[i].escortIndex = escortIndex;
            game->shots[i].impactTime = impactTime;
            game->shots[i].damage = damage;
            return 1;
        }
    }
    return 0;
}

int has_active_shots(const Game *game)
{
    int i;

    for (i = 0; i < MAX_ACTIVE_SHOTS; i++) {
        if (game->shots[i].active) { /* One active entry is enough. */
            return 1;
        }
    }
    return 0;
}

double next_impact_time(const Game *game)
{
    double next = -1.0;
    int i;

    for (i = 0; i < MAX_ACTIVE_SHOTS; i++) {
        if (game->shots[i].active && /* Keep the earliest arrival time. */
            (next < 0.0 || game->shots[i].impactTime < next)) {
            next = game->shots[i].impactTime;
        }
    }
    return next;
}

int apply_impacts(Game *game, double time, FILE *report, Result *result)
{
    int i;
    int count = 0;

    for (i = 0; i < MAX_ACTIVE_SHOTS; i++) {
        Shot *shot = &game->shots[i];
        Escort *escort;
        if (!shot->active || shot->impactTime > time + 0.000001) { /* Not due yet. */
            continue;
        }
        escort = &game->escorts[shot->escortIndex];
        if (shot->fromBattle && escort->alive) { /* Battleship shell hits an escort. */
            escort->health = escort->health > shot->damage ? escort->health - shot->damage : 0.0;
            fprintf(report, "Time %.2f: B hit E%d for %.3f damage.\n",
                    time, escort->id, shot->damage);
            if (escort->health <= 0.000001) {
                escort->alive = 0;
                result->escortsHit++;
                fprintf(report, "E%d was destroyed.\n", escort->id);
            }
        } else if (!shot->fromBattle) { /* Escort shell hits the battleship. */
            int wasAlive = game->battle.alive;
            game->battle.health = game->battle.health > shot->damage ? game->battle.health - shot->damage : 0.0;
            result->damageBattle = result->damageBattle + shot->damage;
            fprintf(report, "Time %.2f: E%d hit B for %.3f damage.\n",
                    time, escort->id, shot->damage);
            if (wasAlive && game->battle.health <= 0.000001) {
                game->battle.alive = 0;
                result->sankBy = escort->id;
                fprintf(report, "Battleship was sunk by E%d.\n", escort->id);
            }
        }
        shot->active = 0; /* The impact is finished, so free this slot. */
        count++;
    }
    return count;
}
