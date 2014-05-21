//---------------------------- Draw shots --------------------------------
// Drawing shots
// ROBERTO RIBEIRO
// PORTUGUESE TEAM
//------------------------------------------------------------------------

#include "drawing_shots.h"

extern int map_layout [MAX_X][MAX_Y];


void create_arrow(int i,int map_layout[MAX_X][MAX_Y], missile_data *m)
{
    int arr_offset = 2;
    if(m->x_vector_coordinate[i]>1 && m->x_vector_coordinate[i]<MAX_X-3)
    {

    gotoxy(m->x_vector_coordinate[i],arr_offset-1);
    printf("^");
    gotoxy(m->x_vector_coordinate[i],arr_offset);
    printf("%d",m->y_vector_coordinate[i]);

    Sleep(20);


    gotoxy(m->x_vector_coordinate[i],arr_offset-1);
    printf(" ");
    gotoxy(m->x_vector_coordinate[i],arr_offset);
    printf("   ");

    }

}

void drawing_shots (int i,int map_layout[MAX_X][MAX_Y], missile_data *m)
{
int sign;
char cannonBall = 2;
if(m->x_vector_coordinate[i] != player.x && m->y_vector_coordinate[i] != player.y && (m->y_vector_coordinate[i]) < MAX_Y && m->x_vector_coordinate[i] >= 0 && m->x_vector_coordinate[i] <= MAX_X )
{
    sign = map_layout[m->x_vector_coordinate[i]][m->y_vector_coordinate[i]];
    gotoxy(m->x_vector_coordinate[i],79-(m->y_vector_coordinate[i]));
    printf("%c",cannonBall);
    Sleep(20);
    gotoxy(m->x_vector_coordinate[i],79-(m->y_vector_coordinate[i]));
    switch (sign)
    {
    case 0:
    printf(" ");
    break;
    case 1:
    printf("1");
    break;
    case 2:
    printf("2");
    break;
    }
}
}
