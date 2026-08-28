#include <stdio.h>
#include "core.h"
int main(void)
{
    Game game = {0};
    int i;
    first_setup(&game);
    show_setup(&game);
    for (i = 0; i < game.escortCount; i++) {
        double time, angle;
        Escort *e = &game.escorts[i];
        if (find_shot(game.battle.position, e->position, 0,
                      game.battle.maxSpeed, 0, 90, &time, &angle))
            printf("B can reach E%d: angle %.3f, flight %.3f seconds\n",
                   e->id, angle, time);
        else printf("E%d is unreachable.\n", e->id);
    }
    return 0;
}
