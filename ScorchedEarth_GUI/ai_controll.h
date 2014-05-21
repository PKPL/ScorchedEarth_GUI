#ifndef __AI_MEDIUM_H__
#define __AI_MEDIUM_H__

//---------------------------- AI Medium level ---------------------------
// AI for medium level
//------------------------------------------------------------------------

#include "maps_create.h"
#include "unit.h"
#include "shot.h"
#include "defines.h"

extern int ai_angle;
void ai_easy(unit local_bot, int map_layout[MAX_X][MAX_Y]);
void ai_medium(unit local_bot, int map_layout[MAX_X][MAX_Y]);
void ai_hard(unit local_bot, int map_layout[MAX_X][MAX_Y]);

#endif // __AI_MEDIUM_H__


