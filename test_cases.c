#include <math.h>
#include <stdio.h>
#include "core.h"
#include "simulation.h"
static void set_escort(Escort *ship, int id, double x,
                       double maxSpeed, double impact)
{
    ship->id = id; ship->type = 0;
    ship->position.x = x; ship->position.y = 0.0;
    ship->minSpeed = 0.0; ship->maxSpeed = maxSpeed;
    ship->minAngle = 1.0; ship->maxAngle = 89.0;
    ship->impact = impact; ship->gamma = 0.05; ship->reload = 6.0;
}
static int run_case(Game *game, Result *result, int feature, int field)
{
    FILE *report = tmpfile();
    if (report == NULL) return 0;
    reset_combat(game); result->sankBy = -1;
    simulate_field(game, feature, field, report, result);
    fclose(report); return 1;
}
int case_high_arc(void)
{
    Position start = {0.0, 0.0}, end = {5.0, 0.0};
    double time, angle;
    return find_shot(start, end, 240.0, 400.0, 20.0, 90.0,
                     &time, &angle) && angle > 89.0 && time > 0.0;
}
int case_part2c_first_shot(void)
{
    Game game; Result result = {0}; int ran;
    set_default_game(&game); game.escortCount = 1;
    game.battle.position.x = 0.0; game.battle.position.y = 0.0;
    game.battle.maxSpeed = 50.0; game.battle.gamma = 0.1; game.battle.reload = 1.0;
    set_escort(&game.escorts[0], 1, 100.0, 0.0, 0.08);
    ran = run_case(&game, &result, PART_2C, STATIC_FIELD);
    return ran && result.battleShots == 2 && !game.escorts[0].alive &&
           fabs(game.battle.currentImpact - exp(-0.2)) < 0.000001;
}
int case_post_sink_impacts(void)
{
    Game game; Result result = {0}; int ran;
    set_default_game(&game); game.escortCount = 1;
    game.battle.position.x = 0.0; game.battle.position.y = 0.0;
    game.battle.maxSpeed = 10.0;
    set_escort(&game.escorts[0], 1, 10.0, 50.0, 1.0);
    ran = run_case(&game, &result, PART_1A, STATIC_FIELD);
    return ran && !game.battle.alive && !game.escorts[0].alive &&
           result.escortsHit == 1 && !has_active_shots(&game);
}
int case_path_rearming(void)
{
    Game game; Result result = {0}; int i, ran;
    set_default_game(&game); game.escortCount = 1; game.pathCount = 3;
    game.battle.maxSpeed = 0.0;
    set_escort(&game.escorts[0], 1, 10.0, 50.0, 0.08);
    for (i = 0; i < game.pathCount; i++) {
        game.path[i].x = 0.0; game.path[i].y = 0.0;
    }
    ran = run_case(&game, &result, PART_1C, PATH_FIELD);
    return ran && result.escortShots == 3 && game.escorts[0].shots == 3 &&
           fabs(game.battle.health - 0.76) < 0.000001;
}
int case_long_battle(void)
{
    Game game; Result result = {0}; int i, ran;
    set_default_game(&game); game.escortCount = MAX_ESCORTS;
    game.battle.position.x = 0.0; game.battle.position.y = 0.0;
    game.battle.maxSpeed = 50.0; game.battle.gamma = 0.01;
    game.battle.reload = 8.0;
    for (i = 0; i < game.escortCount; i++)
        set_escort(&game.escorts[i], i + 1, 100.0 + 2.0 * i, 0.0, 0.04);
    ran = run_case(&game, &result, PART_2C, STATIC_FIELD);
    return ran && result.escortsHit == MAX_ESCORTS && result.duration > 600.0 &&
           !has_active_shots(&game);
}
int case_threat_strategy(void)
{
    Game game; double flightTime, expected, angle;
    set_default_game(&game); game.escortCount = 2;
    game.battle.position.x = 0.0; game.battle.position.y = 0.0;
    game.battle.maxSpeed = 50.0;
    set_escort(&game.escorts[0], 1, 10.0, 0.0, 0.08);
    set_escort(&game.escorts[1], 2, 100.0, 50.0, 0.04);
    reset_combat(&game);
    find_shot(game.battle.position, game.escorts[1].position, 0.0, 50.0,
              0.0, 90.0, &expected, &angle);
    return choose_target(&game, PART_2A, 0.0, &flightTime) == 1 &&
           fabs(flightTime - expected) < 0.000001;
}
int case_shot_capacity(void)
{
    Game game; int i;
    set_default_game(&game); game.escortCount = MAX_ESCORTS;
    clear_shots(&game);
    for (i = 0; i < 861; i++)
        if (!add_shot(&game, 0, i % MAX_ESCORTS, i + 1.0, 0.01)) return 0;
    return has_active_shots(&game);
}
