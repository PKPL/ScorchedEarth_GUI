#include "CDrawable.h"
#include "TestWx3Main.h"
#include "maps_create.h"
#include "maps.h"
#include "unit.h"

float map_ratio = 7;
wxList *map_list = new wxList();
wxList *unit_list = new wxList();
wxPoint *win1;
wxColor *player_color = new wxColor(45,190,15,0);
wxColor *missile_color = new wxColor(150,190,15,0);
wxColor *enemy_color = new wxColor(250,20,15,0);
wxColor *turret_color = new wxColor(150,120,200,0);
extern float player_ray[2];
extern float enemy_ray[2];
extern int actual_missile_position[2];
extern int isEND;



CDrawable::CDrawable()
{
    angle1 = M_PI/4;
    angle2 = 2*M_PI/3;
}

CDrawable::~CDrawable()
{
    //dtor
}

void CDrawable::Draw(wxBufferedPaintDC & DC)
{
    wxColor *ourSky = new wxColor(172,225,255,0);
    wxBrush Brush(*ourSky);
    DC.SetBrush(Brush);
    DC.SetBackground(Brush);
    DC.Clear();
    //drawTank(DC, 50, 300, *wxRED, angle1);
    //drawTank(DC, 450, 300, *wxBLUE, angle2);
    //if(is2draw) drawLineTest(DC, *wxRED);
}

void CDrawable::DrawShot(wxBufferedPaintDC & DC, int CWidth, int CHeight, missile_data* m)
{
    wxPoint p[100];
    for(int i=0; i<100; i++)
    {
        p[i].x = m->x_vector_coordinate[i]*10;
        p[i].y = m->y_vector_coordinate[i]*10;
    }
    DC.DrawLines(100, p);
}

void CDrawable::drawLineTest(wxBufferedPaintDC& DC, wxColor C, int map_layout[100][80], int borderX[100])
{
    if(isEND == 0)
    {

    wxBrush B;
    wxPen P;
    //DC.DrawLine(wxPoint(0, 0),wxPoint(600, 400));
    //DC.DrawLine(wxPoint(0*map_ratio, 0*map_ratio), wxPoint(100, 100));
    int x, y;
    B.SetColour(*wxBLACK);
    P.SetColour(*wxBLACK);
    P.SetWidth(2);
    DC.SetBrush(B);
    DC.SetPen(P);
    DC.DrawCircle(wxPoint(actual_missile_position[0]*map_ratio,(79 - actual_missile_position[1])*map_ratio), 5);
//    for (x = 0; x < 100; x++)
//    {
//        DC.DrawLine(wxPoint(x*map_ratio, (79 - borderX[x])*map_ratio), wxPoint((x+1)*map_ratio, (79 - borderX[x+1])*map_ratio));
//    }

    B.SetColour(*missile_color);
    P.SetColour(*missile_color);
    P.SetWidth(2);
    DC.SetBrush(B);
    DC.SetPen(P);
    map_list = new wxList();
    wxPoint *win1 = new wxPoint(0*map_ratio,(80)*map_ratio);
    map_list->Append((wxObject *)win1);

    for (x = 0; x < 100; x++)
    {
        for (y = 0; y < 80; y++)
        {
            if (borderX[x] == (y))
            {

                wxPoint *win1 = new wxPoint(x*map_ratio,(79 - y)*map_ratio);
                map_list->Append((wxObject *)win1);
            }
        }
    }

    win1 = new wxPoint(100*map_ratio,(80)*map_ratio);
    map_list->Append((wxObject *)win1);


    B.SetColour(C);
    DC.SetBrush(B);
    DC.DrawPolygon(map_list);


    P.SetColour(*player_color);//player gun color
    P.SetWidth(8);
    DC.SetPen(P);
    DC.DrawLine(player.x*map_ratio, (79 - player.y)*map_ratio, player_ray[0]*map_ratio, (79 - player_ray[1])*map_ratio);
    P.SetColour(*wxBLACK);//Gun color
    P.SetWidth(2);
    DC.SetPen(P);
    DC.DrawLine(player.x*map_ratio, (79 - player.y)*map_ratio, player_ray[2]*map_ratio, (79 - player_ray[3])*map_ratio);


    P.SetColour(*enemy_color);//bot gun color
    P.SetWidth(8);
    DC.SetPen(P);
    DC.DrawLine(bot.x*map_ratio, (79 - bot.y)*map_ratio, enemy_ray[0]*map_ratio, (79 - enemy_ray[1])*map_ratio);




    B.SetColour(*player_color);
    P.SetColour(*player_color);
    P.SetWidth(2);
    DC.SetBrush(B);
    DC.SetPen(P);

    unit_list = new wxList();
    wxPoint *win2 = new wxPoint((player.x + 1)*map_ratio,(79 - (player.y + 1))*map_ratio);
    unit_list->Append((wxObject *)win2);
    win2 = new wxPoint((player.x + 2)*map_ratio,(79 - (player.y - 1))*map_ratio);
    unit_list->Append((wxObject *)win2);
    win2 = new wxPoint((player.x - 2)*map_ratio,(79 - (player.y - 1))*map_ratio);
    unit_list->Append((wxObject *)win2);
    win2 = new wxPoint((player.x - 1)*map_ratio,(79 - (player.y + 1))*map_ratio);
    unit_list->Append((wxObject *)win2);

    DC.DrawPolygon(unit_list);


    B.SetColour(*enemy_color);
    P.SetColour(*enemy_color);
    P.SetWidth(2);
    DC.SetBrush(B);
    DC.SetPen(P);

    unit_list = new wxList();
    wxPoint *win3 = new wxPoint((bot.x + 1)*map_ratio,(79 - (bot.y + 1))*map_ratio);
    unit_list->Append((wxObject *)win3);
    win3 = new wxPoint((bot.x + 2)*map_ratio,(79 - (bot.y - 1))*map_ratio);
    unit_list->Append((wxObject *)win3);
    win3 = new wxPoint((bot.x - 2)*map_ratio,(79 - (bot.y - 1))*map_ratio);
    unit_list->Append((wxObject *)win3);
    win3 = new wxPoint((bot.x - 1)*map_ratio,(79 - (bot.y + 1))*map_ratio);
    unit_list->Append((wxObject *)win3);

    DC.DrawPolygon(unit_list);








    }
    else
    {

        if(isEND == 1)
        {
            //WIN
            DC.DrawText(L"GAME OVER! You win!", 250, 100);
        }
        else if(isEND == 2)
        {
            //LOSE
            DC.DrawText(L"GAME OVER! You lose!", 250, 100);
        }

    }
}
