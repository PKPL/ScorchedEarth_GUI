#ifndef __DRAWING_DESTRUCTION_H__
#define __DRAWING_DESTRUCTION_H__

//---------------------------- Draw destructions -------------------------
// Drawing destructions
//------------------------------------------------------------------------

#include "maps_create.h"
#include "shot_final_equation.h"
#include "defines.h"

void test_drawing_destruction(int map_layout [MAX_X][MAX_Y]);
void create_explosion(int map_layout [MAX_X][MAX_Y],missile_data *m,int i);
void create_destruction(int map_layout [MAX_X][MAX_Y]);

#endif // __DRAWING_DESTRUCTION_H__
