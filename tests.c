#include <math.h>
#include <stdio.h>
#include "core.h"
#include "simulation.h"

int case_high_arc(void);
int case_part2c_first_shot(void);
int case_post_sink_impacts(void);
int case_path_rearming(void);
int case_long_battle(void);
int case_threat_strategy(void);
int case_shot_capacity(void);

static int failures = 0;
static void check(int condition, const char *name)
{
    if (condition) printf("PASS: %s\n", name);
    else { printf("FAIL: %s\n", name); failures++; }
}

static void test_physics(void)
{
    Position start = {0.0, 0.0}, near = {100.0, 0.0};
    Position far = {1000.0, 0.0};
    Position boundary = {100.0 / GRAVITY, 0.0};
    double time = 0.0, angle = 0.0;
    check(find_shot(start, near, 0.0, 50.0, 1.0, 89.0,
                    &time, &angle) && time > 0.0, "reachable projectile");
    check(!find_shot(start, far, 0.0, 10.0, 1.0, 89.0,
                     &time, &angle), "unreachable projectile");
    check(find_shot(start, boundary, 0.0, 10.0, 1.1, 90.0,
                    &time, &angle) && fabs(angle - 45.0) < 0.000001,
          "continuous-angle boundary shot");
    check(case_high_arc(), "minimum-speed high-arc shot");
}

static void test_power(void)
{
    double initial = degraded_power(1.0, 0.1, 0);
    double fired = degraded_power(1.0, 0.1, 1);
    check(fabs(initial - 1.0) < 0.000001, "initial IP0 is full power");
    check(fired > 0.0 && fired < initial, "power falls after first firing");
    check(case_part2c_first_shot(), "Part 2-C needs multiple B hits");
}

static void test_randomness(void)
{
    Game first, second;
    set_default_game(&first); set_default_game(&second);
    check(first.escorts[0].type == second.escorts[0].type &&
          first.escorts[0].position.x == second.escorts[0].position.x,
          "same seed repeats battlefield");
    second.seed = 43; generate_battlefield(&second);
    check(first.escorts[0].position.x != second.escorts[0].position.x,
          "different seed changes battlefield");
}

static void test_constraints(void)
{
    Game game; int i, valid = 1;
    set_default_game(&game);
    for (i = 0; i < game.escortCount; i++) {
        Escort *ship = &game.escorts[i];
        if (ship->maxAngle > 90.0) valid = 0;
        if (ship->type == 0 &&
            fabs(ship->maxSpeed - game.battle.maxSpeed * 1.2) > 0.001)
            valid = 0;
        if (ship->type != 0 && ship->maxSpeed >= game.battle.maxSpeed)
            valid = 0;
    }
    check(valid, "generated escort limits");
}

int main(void)
{
    test_physics(); test_power(); test_randomness(); test_constraints();
    check(case_post_sink_impacts(), "in-flight shells resolve after sinking");
    check(case_path_rearming(), "escort fires once per path step");
    check(case_long_battle(), "valid battle completes beyond 600 seconds");
    check(case_threat_strategy(), "strategy prioritizes armed threat");
    check(case_shot_capacity(), "projectile queue covers allowed concurrency");
    printf("\n%d test(s) failed.\n", failures);
    return failures == 0 ? 0 : 1;
}
