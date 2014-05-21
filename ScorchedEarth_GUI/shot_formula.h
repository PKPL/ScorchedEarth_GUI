#ifndef __SHOT_FORMULA_H__
#define __SHOT_FORMULA_H__

//---------------------------- Shot formula ------------------------------
// Formula for the shot
//------------------------------------------------------------------------
//On this file Team 1 is working: Lorenzo Romanelli and Federico Bollotta

#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shot_final_equation.h"
#include "shot_hit.h"
#include "drawing_destruction.h"
#include "drawing_shots.h"
#include "levels_level.h"
#include "maps.h"
#include "drawing.h"
#include "shot.h"
#include "ai.h"
#include "menu.h"
#include "levels.h"
#include "unit.h"
#include "maps_create.h"
#include "armor.h"
#include <windows.h>
#include <stdbool.h>

void playerShot(missile_data*, float, int, int[MAX_X][MAX_Y],bool isBot, float, int*);
void AIShoot(missile_data*, float, int);
float AIcheck(int, int, float, int, int, int, float);

#endif // __SHOT_FORMULA_H__
