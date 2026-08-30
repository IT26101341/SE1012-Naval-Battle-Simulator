#include <stdio.h>
#include "core.h"
#include "menu.h"
int main(void)
{
    Game game = {0};
    puts("Advanced Naval Battle Simulator");
    first_setup(&game);
    show_setup(&game);
    main_menu(&game);
    return 0;
}
