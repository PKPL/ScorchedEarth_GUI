#ifndef __MAPS_CREATE_H__
#define __MAPS_CREATE_H__

/*
PORTUGUESE TEAM

NUNO VALENTE
ROBERTO RIBEIRO
DANIEL PINTO

*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "defines.h"
#define PI 3.14159265

void create_mountain_map(int map_layout[MAX_X][MAX_Y]);
void new_rnd_seed();
void print_loading_status(int x);
void test_maps_create();
int RandInt(int a, int b);
float RandFloatDced(int a, int b);

#endif // __MAPS_CREATE_H__
