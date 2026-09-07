#include <stdio.h>
#include "core.h"
#include "files.h"

/* This file writes the detailed beginning and ending data for one run. */
static void write_escort(FILE *file, const Escort *ship)
{
    /* Keep one escort's related values together in the report. */
    fprintf(file, "E%d type=E%c name=%s gun=%s alive=%d shots=%d\n",
            ship->id, 'A' + ship->type, escort_name(ship->type),
            escort_gun(ship->type), ship->alive, ship->shots);
    fprintf(file, "  position=(%.2f, %.2f) speed=%.2f..%.2f ",
            ship->position.x, ship->position.y,
            ship->minSpeed, ship->maxSpeed);
    fprintf(file, "angle=%.2f..%.2f health=%.3f\n",
            ship->minAngle, ship->maxAngle, ship->health);
    fprintf(file, "  impact=%.4f gamma=%.4f reload=%.2f ",
            ship->impact, ship->gamma, ship->reload);
    fprintf(file, "next_fire=%.2f current_impact=%.4f\n",
            ship->nextFire, ship->currentImpact);
}

void write_initial(FILE *file, const Game *game, int feature, int field)
{
    int i;
    /* First save the choices and the starting state for fair comparisons. */
    fprintf(file, "ADVANCED NAVAL BATTLE SIMULATOR\n");
    fprintf(file, "Feature: %s\nField: %s\n\n",
            feature_name(feature), field_name(field));
    fprintf(file, "INITIAL SETUP\nCanvas: %.2f x %.2f\n", game->canvas,
            game->canvas);
    fprintf(file, "Seed: %u  Escorts: %d  Path points: %d\n",
            game->seed, game->escortCount, game->pathCount);
    fprintf(file, "Jam step: %d  Jam minimum angle: %.2f\n\n",
            game->jamStep, game->jamAngle);
    fprintf(file, "BATTLESHIP\nType=%c name=%s gun=%s alive=%d shots=%d\n",
            game->battle.type, battle_name(game->battle.type),
            battle_gun(game->battle.type), game->battle.alive,
            game->battle.shots);
    fprintf(file, "Position=(%.2f, %.2f) max_speed=%.2f health=%.3f\n",
            game->battle.position.x, game->battle.position.y,
            game->battle.maxSpeed, game->battle.health);
    fprintf(file, "Gamma=%.4f reload=%.2f next_fire=%.2f impact=%.4f\n\n",
            game->battle.gamma, game->battle.reload,
            game->battle.nextFire, game->battle.currentImpact);
    fprintf(file, "ESCORT SHIPS\n");
    /* Each escort is written using the helper above. */
    for (i = 0; i < game->escortCount; i++) {
        write_escort(file, &game->escorts[i]);
    }
    fprintf(file, "\nBATTLESHIP PATH\n");
    /* Path points show where the battleship moves during path modes. */
    for (i = 0; i < game->pathCount; i++) {
        fprintf(file, "Point %d = (%.2f, %.2f)\n", i + 1,
                game->path[i].x, game->path[i].y);
    }
    fprintf(file, "\nEVENT LOG\n");
}

void write_final(FILE *file, const Game *game, const Result *result)
{
    int i;
    /* The final section records the winner, totals and remaining ships. */
    fprintf(file, "\nFINAL RESULT\n");
    fprintf(file, "Battleship: %s\n", game->battle.alive ? "SURVIVED" : "SANK");
    if (result->sankBy >= 0)
        fprintf(file, "Sank by escort: E%d\n", result->sankBy);
    else
        fprintf(file, "Sank by escort: none\n");
    fprintf(file, "Duration: %.2f  Escorts hit: %d\n",
            result->duration, result->escortsHit);
    fprintf(file, "Battleship shots: %d  Escort shots: %d\n",
            result->battleShots, result->escortShots);
    fprintf(file, "Damage to battleship: %.3f  Health: %.3f\n",
            result->damageBattle, game->battle.health);
    fprintf(file, "Battleship position=(%.2f, %.2f) shots=%d impact=%.4f\n",
            game->battle.position.x, game->battle.position.y,
            game->battle.shots, game->battle.currentImpact);
    fprintf(file, "Attack order:");
    for (i = 0; i < result->attackCount; i++) {
        fprintf(file, " %d", result->attackOrder[i]);
    }
    if (result->attackCount == 0) {
        fprintf(file, " none");
    }
    fprintf(file, "\n\nFINAL ESCORT CONDITIONS\n");
    for (i = 0; i < game->escortCount; i++) {
        write_escort(file, &game->escorts[i]);
    }
}
