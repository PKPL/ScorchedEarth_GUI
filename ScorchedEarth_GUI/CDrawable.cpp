#include "CDrawable.h"
#include "TestWx3Main.h"
#include "maps_create.h"
#include "maps.h"
#include "unit.h"

int map_ratio = 7;
wxList *map_list = new wxList();
wxPoint *win1;
wxColor *player_color = new wxColor(45,190,15,0);
wxColor *enemy_color = new wxColor(250,20,15,0);



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
    wxBrush B;
    wxPen P;
    B.SetColour(*wxWHITE);
    DC.SetBrush(B);
    P.SetColour(C);
    P.SetWidth(3);
    DC.SetPen(P);
    //DC.DrawLine(wxPoint(0, 0),wxPoint(600, 400));
    //DC.DrawLine(wxPoint(0*map_ratio, 0*map_ratio), wxPoint(100, 100));
    int x, y;
//    for (x = 0; x < 100; x++)
//    {
//        DC.DrawLine(wxPoint(x*map_ratio, (79 - borderX[x])*map_ratio), wxPoint((x+1)*map_ratio, (79 - borderX[x+1])*map_ratio));
//    }

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

    B.SetColour(*player_color);
    DC.SetBrush(B);
    DC.DrawCircle(wxPoint(player.x*map_ratio,(79-player.y)*map_ratio), 8);

    B.SetColour(*enemy_color);
    DC.SetBrush(B);
    DC.DrawCircle(wxPoint(bot.x*map_ratio,(79-bot.y)*map_ratio), 8);

}
