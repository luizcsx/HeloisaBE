#include <genesis.h>
#include "game_state.h"
#include "title.h"
#include "menu.h"

GameState game_state;

static GameState previous_state;

static void handle_state_transition(void)
{
    if (game_state == previous_state)
        return;

    switch (game_state)
    {
        case STATE_TITLE:
            title_init();
            break;

        case STATE_MENU:
            menu_init();
            break;

        case STATE_GAME:
            break;
    }

    previous_state = game_state;
}

int main(bool hardReset)
{
    JOY_init();

    game_state = STATE_TITLE;
    previous_state = STATE_MENU;

    handle_state_transition();

    while (TRUE)
    {
        handle_state_transition();

        switch (game_state)
        {
            case STATE_TITLE:
                title_update();
                break;

            case STATE_MENU:
                menu_update();
                break;

            case STATE_GAME:
                break;
        }

        SYS_doVBlankProcess();
    }

    return 0;
}
