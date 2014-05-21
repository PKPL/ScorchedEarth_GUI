//---------------------------- AI Medium level ---------------------------
// AI for medium level
//------------------------------------------------------------------------

#include "ai.h"
#include "ai_controll.h"
#include "unit.h"
#include "maps_create.h"
#include <stdbool.h>

static float medium_dec_range = 10;
int ai_angle = 180;

void ai_easy(unit local_bot, int map_layout[MAX_X][MAX_Y])
{

    int mini_angle = min_angle(local_bot);//searching for minimal angle
    int maxi_angle = 70;
    int ai_shoot_angle;

    while(true)
    {


       ai_shoot_angle = find_random(mini_angle+15,maxi_angle);
       if(player.x < local_bot.x)ai_shoot_angle = 180 - ai_shoot_angle;
       break;
       //if(raycast(local_bot, ai_shoot_angle, map_layout[MAX_X][MAX_Y]) == false)break;
    }


    int ai_shoot_power = find_random(30,200);
    //printf("ai_shoot angle = %d ai_shoot_power = %d",ai_shoot_angle,ai_shoot_power );
    //in easy AI, shoot angle and shoot velocity (power) is random
    //take_a_shot(bot.x,bot.y,ai_shoot_angle,ai_shoot_power);
    //we are waiting for complex function which take a shoot from given arguments like coords of unit, angle and power of the shoot
    //testShot(ENEMY, ai_shoot_power, ai_shoot_angle, local_bot.x, local_bot.y);


    missile_data *missile;
    missile = initializeMissile(local_bot.x, local_bot.y);
    playerShot(missile, ai_shoot_power, ai_shoot_angle, map_layout,false, wind_speed, &ai_angle);


}


void ai_medium(unit local_bot, int map_layout[MAX_X][MAX_Y])
{

int power;


power = -1;

while(power == -1)
{
ai_angle --;
if(ai_angle <= 50)
{
    gotoxy(10,40);
    printf("EASY MODE ACTIVATED");
    ai_easy(local_bot, map_layout);
    return;
}
power = AIcheck (local_bot.x, local_bot.y, 1.8, ai_angle, player.x, player.y, wind_speed);

}
missile_data *missile;
    missile = initializeMissile(local_bot.x, local_bot.y);

int rnd = find_random(-4,5);





    playerShot(missile, (power + rnd) * 4, 180 - ai_angle, map_layout,false, wind_speed, &ai_angle);
}

void ai_hard(unit local_bot, int map_layout[MAX_X][MAX_Y])
{

int power;


power = -1;

while(power == -1)
{
ai_angle --;
if(ai_angle <= 50)
{
    gotoxy(10,40);
    printf("EASY MODE ACTIVATED");
    ai_easy(local_bot, map_layout);
    return;
}
power = AIcheck (local_bot.x, local_bot.y, 1.8, ai_angle, player.x, player.y, wind_speed);


}
missile_data *missile;
    missile = initializeMissile(local_bot.x, local_bot.y);

int rnd = find_random(-3,4);

    playerShot(missile, (power + rnd) * 4, 180 - ai_angle, map_layout,false, wind_speed, &ai_angle);
}




