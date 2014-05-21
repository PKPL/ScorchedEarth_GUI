#ifndef __UNIT_H__
#define __UNIT_H__

//---------------------------- Units -------------------------------------
// It combines the files responsible for units
//------------------------------------------------------------------------

// Included libraries
#include "defines.h"

//Structs
typedef struct {
int x;
int y;
int points;
int hp;
}unit;

// Included files


extern unit player;
extern unit bot;
void unit_func(unit *unit_set);
#endif // __UNIT_H__
