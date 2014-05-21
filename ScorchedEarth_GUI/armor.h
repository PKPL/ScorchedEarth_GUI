#ifndef __ARMOR_H__
#define __ARMOR_H__

#include "defines.h"
#include "unit.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

extern int map_layout[MAX_X][MAX_Y];

typedef struct {
    int x, y;
} armorCoords;

void drawing_armors(int map_layout[MAX_X][MAX_Y], int);
armorCoords create_armor(int map_layout[MAX_X][MAX_Y], int);
void hit_armor(int map_layout[MAX_X][MAX_Y], int, int, bool);

#endif // __ARMOR_H__
