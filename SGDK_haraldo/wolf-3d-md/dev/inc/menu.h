#ifndef MENU_H
#define MENU_H
#include "wl_types.h"
void US_ControlPanel(void);
void NewGame(s16 difficulty, s16 episode);
extern boolean startgame, loadedgame;
extern boolean ingame;
extern s16 newgame_difficulty;
#endif
