#ifndef __SHOT_FINAL_EQUATION_H__
#define __SHOT_FINAL_EQUATION_H__

#include "defines.h"
#include "levels.h"

//On this file Team 1 is working: Federico Bollotta and Lorenzo Romanelli


/* In the following struct are stored all the datas related to the first type of missile
(for further missile types we'll use more structs) */
typedef struct {
    char name[100];
    float weight; //Kilograms per second
    float initial_velocity; //Meters per second
    float x_vector_velocity[VECTOR_LENGTH], y_vector_velocity[VECTOR_LENGTH]; //We're storing velocity value (x and y components) in these vectors as time increases
    int x_turret_position, y_turret_position;
    int x_vector_coordinate[VECTOR_LENGTH], y_vector_coordinate[VECTOR_LENGTH]; //Coordinates of the missile inside the matrix as time increases
    int shot_angle; //In sexagesimal degrees
    int unit_damage;
} missile_data;

float windForce(float);

double cosDegrees(double);
double sinDegrees(double);

missile_data* initializeMissile(int, int);
void setInitialVelocity(missile_data*, float);
void setShootingAngle(missile_data*, int);

void xVelocityFormula(missile_data*, float);
void yVelocityFormula(missile_data*);
void xCoordinate(missile_data*, float);
void yCoordinate(missile_data*);

void shotFunction(missile_data*, float);

float bounce(float);
float continuous(float);

#endif // __SHOT_FINAL_EQUATION_H__
