#include <stdio.h>
#include "core.h"
#include "simulation.h"

/* Copy the setup so repeated runs share exactly the same initial conditions. */
void run_one_simulation(const Game *base, int feature, int field)
{
    Game game = *base;
    Result result = {0};
    result.sankBy = -1;
    reset_combat(&game);
    simulate_field(&game, feature, field, stdout, &result);
    printf("%s - %s\n", feature_name(feature), field_name(field));
    printf("Battleship %s | escorts destroyed %d | time %.2f\n",
           game.battle.alive ? "survived" : "sank", result.escortsHit,
           result.duration);
    if (result.sankBy >= 0) printf("Sunk by E%d\n", result.sankBy);
    printf("Shots B:%d E:%d | damage to B %.3f\n",
           result.battleShots, result.escortShots, result.damageBattle);
}

void run_all_simulations(const Game *base)
{
    int feature, field;
    for (feature = 1; feature <= 4; feature++)
        for (field = 1; field <= 2; field++)
            run_one_simulation(base, feature, field);
}
