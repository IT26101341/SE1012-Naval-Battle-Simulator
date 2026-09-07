#include <stdio.h>
#include "core.h"
#include "files.h"
#include "simulation.h"

/* This file connects the menus, simulation engine and saved reports. */
void run_one_simulation(const Game *base, int feature, int field)
{
    /* Copying base keeps the user's original setup unchanged. */
    Game game = *base;
    Result result = {0};
    FILE *report;
    char fileName[160];
    result.sankBy = -1;
    /* Reset, simulate, then save the complete result in order. */
    reset_combat(&game);
    report = open_report(feature, field, fileName, sizeof(fileName));
    if (report == NULL) {
        return;
    }
    write_initial(report, &game, feature, field);
    simulate_field(&game, feature, field, report, &result);
    write_final(report, &game, &result);
    fclose(report);
    append_history(fileName, feature, field, &result);
    printf("\nFinished %s - %s\n", feature_name(feature), field_name(field));
    if (result.sankBy >= 0)
        printf("Battleship sank after an attack from E%d.\n", result.sankBy);
    else
        printf("Battleship survived and destroyed %d escorts.\n",
               result.escortsHit);
    printf("Battle time %.2f seconds, damage received %.3f.\n",
           result.duration, result.damageBattle);
    printf("Report saved in %s\n", fileName);
}

void run_all_simulations(const Game *base)
{
    int feature;
    int field;
    printf("\nRunning all 15 combinations using the same setup.\n");
    /* Five feature levels multiplied by three fields gives 15 runs. */
    for (feature = PART_1A; feature <= PART_2C; feature++) {
        for (field = STATIC_FIELD; field <= JAM_FIELD; field++) {
            run_one_simulation(base, feature, field);
        }
    }
}
