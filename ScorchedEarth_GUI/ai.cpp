//---------------------------- Artificial Inteligence --------------------
// It combines the files responsible for artificial inteligence
//------------------------------------------------------------------------
// Polish team is working on this file
// Included files
#include "ai.h"
#include "unit.h"
#include <math.h>
#include <stdlib.h>
#include "maps_create.h"
#include <stdbool.h>
#include <time.h>


float min_angle(unit local_bot)
{
    if(player.y > local_bot.y)return (atan((player.y-local_bot.y)/abs(player.x - local_bot.x)));
    return 0;
}

int find_random(int min_ang, int max_ang)
{
    srand ( time(NULL) );
    return  (rand() % (max_ang - min_ang) + min_ang);
}

bool raycast(unit from, int angle,  int map_layout[MAX_X][MAX_Y])
{
    int ray_length = 20;
    int i = 1;
    for(i = 1; i < ray_length; i++)
    {
        float local_x, local_y;

        local_x = cos(angle)*i;
        local_y = sin(angle)*i;

        int local_x_rounded = (int)(local_x + 0.5);
        int local_y_rounded = (int)(local_y + 0.5);

        if(from.x + local_x_rounded > MAX_X || from.y + local_y_rounded > MAX_Y) break;
        else if(map_layout[from.x + local_x_rounded][from.y + local_y_rounded] == 1)
        {
            return true;
        }

    }
    return false;
}


void ai(unit local_bot, int map_layout[MAX_X][MAX_Y])
{

    if(selected_level.level_ai == AI_EASY)ai_easy(local_bot, map_layout);
    else if(selected_level.level_ai == AI_MEDIUM)ai_medium(local_bot, map_layout);
    else if(selected_level.level_ai == AI_HARD)ai_hard(local_bot, map_layout);

}
