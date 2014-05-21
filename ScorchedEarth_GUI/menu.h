#ifndef __MENU_H__
#define __MENU_H__

//---------------------------- Menu --------------------------------------
// It combines the files responsible for menu of a game
//------------------------------------------------------------------------

// Team 2 File (Polish Group)

// Included libraries

// Included files
//#include "menu_new_game.h"
//#include "menu_highscore.h"
//#include "menu_credits.h"
//#include "menu_close_game.h"
#include "maps_create.h"
#include "drawing_maps.h"
#include "drawing_units.h"
#include "levels_level.h"
#include <stdio.h>
#include "defines.h"

void menu(); // function for agreagate testing
void menu_reaction(int SelectedOption, int map_layout [MAX_X][MAX_Y]);

#endif // __MENU_H__
