#include <stdio.h>
#include "types.h"
/* The model is introduced before generation or battle behaviour. */
int main(void)
{
    Game game = {0};
    Result result = {0};
    game.battle.type = 'U';
    game.battle.health = 1.0;
    result.sankBy = -1;
    printf("Battleship %c, health %.1f, sink source %d\n",
           game.battle.type, game.battle.health, result.sankBy);
    printf("Capacity: %d escorts, %d path points, %d projectiles\n",
           MAX_ESCORTS, MAX_PATH, MAX_ACTIVE_SHOTS);
    return 0;
}
