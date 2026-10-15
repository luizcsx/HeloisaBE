#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

typedef enum
{
    STATE_TITLE,
    STATE_MENU,
    STATE_GAME

} GameState;

extern GameState game_state;

#endif
