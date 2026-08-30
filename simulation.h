#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdio.h>
#include "types.h"

/* Functions for storing shells that are still travelling. */
void clear_shots(Game *game);
int add_shot(Game *game, int fromBattle, int escortIndex,
             double impactTime, double damage);
int has_active_shots(const Game *game);
double next_impact_time(const Game *game);
int apply_impacts(Game *game, double time, FILE *report, Result *result);

/* Functions that decide when ships can fire and which target to use. */
int fire_battleship(Game *game, int feature, double minAngle,
                    FILE *report, Result *result);
int fire_escorts(Game *game, int feature, FILE *report, Result *result);
double next_possible_fire(const Game *game, int feature, double minAngle);

/* Functions that run one battle position, field, or group of fields. */
double run_position(Game *game, int feature, double minAngle,
                    FILE *report, Result *result, int step);
void simulate_field(Game *game, int feature, int field,
                    FILE *report, Result *result);
void run_one_simulation(const Game *base, int feature, int field);
void run_all_simulations(const Game *base);

#endif
