//---------------------------- Levels ------------------------------------
// It combines the files responsible for levels of a game
//------------------------------------------------------------------------

// Included libraries
//
// Included files

// It was a hard nut for us to understand what kind of return is here. So we change this in working stage to something simplier

// Ania Gil  and Nuno  Valente



#include "levels.h"
//#include "menu_new_game.h"
//#include "menu.h"

void choose_levels(int i, int j) // function for agreagate testing
{
    levels(i);
    test_edge(j);
    //create_mountain_map(map_layout);
//    game_loop(map_layout);
}

void test_edge (int j)
{
    switch(j)
    {
        case 1:
        selected_level.edge = EDGE_NO;
        break;

        case 2:
        selected_level.edge = EDGE_BOUNCE;
        break;

        case 3:
        selected_level.edge = EDGE_CONTINUE;
        break;
    }

}
