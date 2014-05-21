//On this file Team 1 is working: Federico Bollotta and Lorenzo Romanelli
//UNDER DEVELOPMENT!!!!

#include "shot_hit.h"

int checkHit (int i, missile_data *m,int matrix[MAX_X][MAX_Y]) {
    if (m->y_vector_coordinate[i] >= MAX_Y)
    {
        //Sleep(20);
        return 0; //If the projectile outgoes map height without hitting anything, it waits for it to enter again in the map
    }
    if (m->x_vector_coordinate[i] >= MAX_X || m->x_vector_coordinate[i] < 0 || m->y_vector_coordinate[i] < 0) return 1; //If the projectile outgoes map length (either on the left or right side) without hitting anything, the shot goes lost
    if (matrix[m->x_vector_coordinate[i]][m->y_vector_coordinate[i]] == 1) //Projectile hits ground
        return 2;
    if (matrix[m->x_vector_coordinate[i]][m->y_vector_coordinate[i]] == 10 || matrix[m->x_vector_coordinate[i]][m->y_vector_coordinate[i]] == 20) //Projectile hits unit (either player's ones or enemy's ones)
        return 3;
    if (matrix[m->x_vector_coordinate[i]][m->y_vector_coordinate[i]] == 4) return 5;
    return 4;
}
/*
void extra_explosion(missile_data *m){

}
*/
