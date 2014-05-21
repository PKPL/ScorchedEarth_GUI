#ifndef __LEVELS_LEVEL_H__
#define __LEVELS_LEVEL_H__

//---------------------------- Level ------------------------------------
// Stuctur resposible for levels setting
//-----------------------------------------------------------------------
#include "levels.h"

#include "defines.h"

typedef enum wind_type
{
  WIND_NO,
  WIND_CONST,
  WIND_VARIABLE
} wind_type;

typedef enum ai_type
{
  AI_EASY,
  AI_MEDIUM,
  AI_HARD,
  PVP_MODE
} ai_type;

typedef enum edge_type
{
    EDGE_NO,
    EDGE_BOUNCE,
    EDGE_CONTINUE
} edge_type;

typedef struct level_struct
{
   wind_type level_wind;
   ai_type level_ai;
   edge_type edge;
} level_struct;

void choose_wind();
void levels(int option);
float random_wind();
extern level_struct selected_level;
extern float wind_speed;

#endif // __LEVELS_LEVEL_H__
