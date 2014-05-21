//---------------------------- Draw units --------------------------------
// Drawing units
// DANIEL PINTO
// PORTUGUESE TEAM
//------------------------------------------------------------------------

#include "drawing_units.h"
#include "unit.h"
#include <time.h>
#include <math.h>
#include <stdbool.h>


extern int map_layout [MAX_X][MAX_Y];

void drawing_units (int map_layout[MAX_X][MAX_Y], unit *player_t, unit *bot_t)
{
    srand (time (NULL));
    tCoordinates coordinates_player, coordinates_enemy;
    int error = 0;

    if (player_t->x % 2 != 1 && player_t->x % 2 != 0 )
    {
        error = 1;
        printf("Errors in units parameters.\n");
    }
    else if (player_t->y % 2 != 1 && player_t->y % 2 != 0) {
        error = 1;
        printf("Errors in units parameters.\n");
    }
    else if (player_t->hp % 2 != 1 && player_t->hp % 2 != 0) {
     error = 1;
     printf("Errors in units parameters.\n");
    }
    else if (player_t->points % 2 != 1 && player_t->points % 2 != 0) {
     error = 1;
     printf("Errors in units parameters.\n");
    }
    if (error != 1)
    {
        do
        {
            coordinates_player = position (map_layout, false);
            coordinates_enemy = position (map_layout,true);
            if (abs(coordinates_enemy.x - coordinates_player.x) <= DISTANCE && abs(coordinates_enemy.y - coordinates_player.y) <= DISTANCE)
            {
                map_layout[coordinates_player.x][coordinates_player.y] = 1;
                map_layout[coordinates_enemy.x][coordinates_enemy.y] = 1;
            }
        }
        while (abs(coordinates_enemy.x - coordinates_player.x) <= DISTANCE && abs(coordinates_enemy.y - coordinates_player.y) <= DISTANCE);
        map_layout[coordinates_player.x][coordinates_player.y] = PLAYER;
        map_layout[coordinates_enemy.x][coordinates_enemy.y] = ENEMY;

        player_t->x = coordinates_player.x;
        player_t->y = coordinates_player.y;
        bot_t->x = coordinates_enemy.x;
        bot_t->y = coordinates_enemy.y;

        int i,j;
        for(i = 0; i < MAX_X; i++)
        {
            for(j = 0; j < MAX_Y; j++)
            {
                if(j >= player_t->y && abs(i - player_t->x) <= 5 && map_layout[i][j] == 1)
                {
//                    gotoxy(i, 79 - j);
                    map_layout[i][j] = 0;
//                    printf(" ");
                }
            }

        }

        for(i = 0; i < MAX_X; i++)
        {
            for(j = 0; j < MAX_Y; j++)
            {
                if(j >= bot_t->y && abs(i - bot_t->x) <= 5 && map_layout[i][j] == 1)
                {
//                    gotoxy(i, 79 - j);
                    map_layout[i][j] = 0;
//                    printf(" ");
                }
            }

        }
    }


}

tCoordinates position (int map_layout[MAX_X][MAX_Y], bool isBot)
{
    int i;
    tCoordinates coordinates;
    if(!isBot) coordinates.x = rand () % (MAX_X/3) + 1;
    if(isBot) coordinates.x = rand () % (MAX_X/3) + 1 + MAX_X / 1.5;
    for (i = 0; i < MAX_Y; i++)   //Sorry for small change son my own i just reverse your "for" loop becouse it was working form te bottoem and units always was an the bottom :)
    {
        if (map_layout[coordinates.x][i] == 1)
        {
            continue;
        }
        else
        {
            coordinates.y = i; // +1 to be on ground no in ground
            break;
        }
    }
    return coordinates;
}

