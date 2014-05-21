//---------------------------- Shot formula ------------------------------
// Formula for the shot
//------------------------------------------------------------------------
//On this file Team 1 is working: Lorenzo Romanelli and Federico Bollotta

#include "shot_formula.h"
#include "maps_create.h"








extern int ai_angle;
extern int actual_missile_position[2];


/* When a player shoots, the following function is called: it asks the player for all necessary data (shooting angle, initial velocity), then calculates the shot, checks the shot and, if possible, calls for explosion functions. */


void playerShot(missile_data *missile, float initial_velocity, int shooting_angle, int matrix[MAX_X][MAX_Y], bool isBot, float some_wind_speed)
{


    int i, flag = 0;

    setInitialVelocity(missile, initial_velocity/4);
    setShootingAngle(missile, shooting_angle);

    shotFunction(missile, windForce(some_wind_speed));

    /*Following cycle controls if the projectile hits anything before going out of the map; if so, functions checking what was hit are called*/
    for (i = 0; i < VECTOR_LENGTH; i++) {

        switch (checkHit(i, missile, matrix)) {

//            case 0: create_arrow(i,matrix, missile);
//                continue;


            case 1: if(isBot)

                    break;
            case 2: /*explosion: hit ground*/
                    create_explosion(matrix,missile,i); //connection with drawing_destruction.c
                    if(isBot)


                   // extra_explosion(missile); //you can find it in shot_hit.c
                    flag=1;

                    break;
            case 3: /*explosion: hit unit*/
                //Call function Destruction of Unit or similar. TODO
                flag=1;
                break;

            case 4:
                actual_missile_position[0] = missile->x_vector_coordinate[i];
                actual_missile_position[1] = missile->y_vector_coordinate[i];

                break;
            case 5:
                hit_armor(matrix, missile->x_vector_coordinate[i], missile->y_vector_coordinate[i], isBot);
                flag = 1;

                break;
        }
        if ( flag == 1 ) break;
    }

}

/* Following function returns the exact power value that is needed to exactly hit player with given angle */
float AIcheck (int x_enemy_coord, int y_enemy_coord, float missile_weight, int angle, int x_player_coord, int y_player_coord, float some_wind_speed) {

    if(x_enemy_coord > x_player_coord)angle = 180 - angle;
    const float b = 0.1;
    const float g = 9.81;
    int x0, y0, x_target, y_target;
    float t, velocity, vel_x0, vel_y0, wf;

    wf = windForce(some_wind_speed);
    x0 = x_enemy_coord;
    y0 = y_enemy_coord;
    velocity = 1;
    t = 0; //time

    for (;;) { //This "for cycle" increases initial velocity value by 1 m/s
        t = 0;
        if (velocity > 30) break;
        vel_x0 = velocity * cosDegrees(angle);
        vel_y0 = velocity * sinDegrees(angle);

        for (;;) { //This "for cycle" increases time by 0.2 seconds
            t += 0.2;
            x_target = x0 + ((wf / b) * t) + (missile_weight / b) * (vel_x0 - wf / b) * (1 - exp( - (b / missile_weight) * t ));
            y_target = y0 + missile_weight / b * (vel_y0 + missile_weight * g / b) * (1 - exp(-(b / missile_weight * t))) - missile_weight * g / b * t;

            if (y_target < 0) break; //If projectile outgoes map, it is not good, so next try :)
            if (abs(x_target - x_player_coord)<=4)  {
                if (abs(y_target - y_player_coord)<=4)
                    return velocity;
                else continue; //It might happen that in two consecutive instants, x coord of the shoot remains the same while y coord changes
            }

            else if (x_target >= MAX_X || x_target < 0) //Here instead of LENGTH (of matrix) we'll have to put length of map
                break;
        }
        velocity += 1;
    }

    return -1;

}
