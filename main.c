#include "core.h"
#include "menu.h"

/* The program starts here and passes one Game structure between screens. */
int main(void)
{
    Game game;
    /* Setup fills the game before the main menu lets the user change it. */
    show_title_art();
    first_setup(&game);
    show_setup(&game);
    main_menu(&game);
    return 0;
}
