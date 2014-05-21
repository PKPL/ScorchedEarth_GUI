//---------------------------- Level ------------------------------------
// Stuctur resposible for levels setting
//-----------------------------------------------------------------------

#include "levels_level.h"
#include <time.h>


level_struct selected_level; //Global variable selected_level if you want use it add "levels_level.h"
float wind_speed; //Global variable wind_speed if you want use it add "levels_level.h"

void levels(int option)
{
    level_struct easy_level;
    {
        easy_level.level_wind = WIND_NO;
        easy_level.level_ai = AI_EASY;
    }

    level_struct medium_level;
    {
        medium_level.level_wind = WIND_CONST;
        medium_level.level_ai = AI_MEDIUM;
    }

    level_struct hard_level;
    {
        hard_level.level_wind = WIND_VARIABLE;
        hard_level.level_ai = AI_HARD;
    }

        level_struct PvP;
    {
        PvP.level_wind = WIND_VARIABLE;
        PvP.level_ai = PVP_MODE;
    }
    switch (option)
    {
    case 1:
        selected_level = easy_level;
        wind_speed = 0;
        break;
    case 2:
        selected_level = medium_level;
        wind_speed = random_wind();
        break;
    case 3:
        selected_level = hard_level;
        wind_speed = random_wind(); //And addictionally it will be generated in all next rounds
        break;
    case 4:
        selected_level = PvP;
        //PvP.level_wind = WIND_VARIABLE;
        choose_wind();
        break;
    }

}
void choose_wind()
{
     selected_level.level_wind = WIND_NO;
}

float random_wind()
{
    int random_value;
    srand ( time(NULL) );
    random_value = (rand() % 201 - 100);
    return  (float)random_value;
}
