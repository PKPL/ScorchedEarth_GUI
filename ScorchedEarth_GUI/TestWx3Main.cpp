/***************************************************************
 * Name:      TestWx3Main.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2014-05-12
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "TestWx3Main.h"
#include "maps_create.h"
#include "drawing_shots.h"
#include "shot_formula.h"
#include "levels.h"
#include "unit.h"
#include "drawing_units.h"
#include "shot_formula.h"

int map_layout[100][80] = {{0}};
int borderX[100];
float player_ray[4];
float angle_drawing_distanse = 10;
float angle_drawing_distanse_floating = 10;
int player_angle = 60;
float player_power = 100;
int actual_missile_position[2] = {(-5)};

unit player;
unit bot;

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

TestWx3Dialog::TestWx3Dialog(wxDialog *dlg)
    : GUIDialog(dlg)
{
    m_Canvas->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    wxInitAllImageHandlers();
    Doc = new CDrawable();
    missile1 = NULL;
    is2draw = FALSE;
}

TestWx3Dialog::~TestWx3Dialog()
{
    delete Doc;
}

void TestWx3Dialog::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void TestWx3Dialog::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void TestWx3Dialog::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welplayer_power++;come to..."));
}

void TestWx3Dialog::m_CanvasOnPaint( wxPaintEvent& event )
{
    wxBufferedPaintDC DC(m_Canvas);
    int CWidth,CHeight;
    m_Canvas->GetSize(&CWidth,&CHeight);
    Doc->Draw(DC);
    if(missile1!=NULL)Doc->DrawShot(DC, CWidth, CHeight, missile1);
    wxColor *dark_green = new wxColor(45,104,42,0);
    if(is2draw)Doc->drawLineTest(DC, *dark_green, map_layout, borderX);
}

void TestWx3Dialog::m_button2OnButtonClick( wxCommandEvent& event )
{
    this->is2draw = TRUE;

    choose_levels(1, 1);
    create_mountain_map(map_layout);

    unit_func(&player);
    unit_func(&bot);

    drawing_units(map_layout, &player, &bot);

    int x, y;
    for (x = 0; x < 100; x++)
    {
        for (y = 0; y < 80; y++)
        {
            if (map_layout[x][y] == 1 && map_layout[x][y+1] != 1)
            {
                borderX[x] = y;
                y = 80;
            }
        }
    }

    calculate_ray();


    m_Canvas->Refresh();
}

void TestWx3Dialog::key_function( wxKeyEvent& event)
{

    switch ( event.GetKeyCode() )
    {
    case WXK_LEFT:
        player_angle++;
        break;
    case WXK_RIGHT:
        player_angle--;
        break;
    case WXK_UP:
        player_power++;
        break;
    case WXK_DOWN:
        player_power--;
        break;
    case WXK_SPACE:
        missile_data *missile;
        missile = initializeMissile(player.x, player.y);
        shoot_function(missile, player_power, player_angle, map_layout,false, wind_speed);
        break;

    }

    calculate_ray();
    m_Canvas->Refresh();
}


void calculate_ray()
{

    angle_drawing_distanse = 10;
    angle_drawing_distanse_floating = player_power/5.0;

    player_ray[0] = player.x + angle_drawing_distanse*cos(player_angle * PI / 180.0 );
    player_ray[1] = (player.y + angle_drawing_distanse*sin(player_angle * PI / 180.0 ));

    player_ray[2] = player.x + angle_drawing_distanse_floating*cos(player_angle * PI / 180.0 );
    player_ray[3] = (player.y + angle_drawing_distanse_floating*sin(player_angle * PI / 180.0 ));
}


void TestWx3Dialog::m_buttonExplodeOnButtonClick( wxCommandEvent& event )
{

    missile_data *missile;
    missile = initializeMissile(50, 5);
    playerShot(missile, 120, 60, map_layout,false, 0);

    int x, y;
    for (x = 0; x < 100; x++)
    {
        for (y = 0; y < 80; y++)
        {
            if (map_layout[x][y] == 1 && map_layout[x][y+1] != 1)
            {
                borderX[x] = y;
                y = 80;
            }
        }
    }

    m_Canvas->Refresh();


}

void TestWx3Dialog::shoot_function(missile_data *missile, float initial_velocity, int shooting_angle, int matrix[MAX_X][MAX_Y], bool isBot, float some_wind_speed)
{
    int i, flag = 0;

    setInitialVelocity(missile, initial_velocity/4);
    setShootingAngle(missile, shooting_angle);

    shotFunction(missile, windForce(some_wind_speed));

    /*Following cycle controls if the projectile hits anything before going out of the map; if so, functions checking what was hit are called*/
    for (i = 0; i < VECTOR_LENGTH; i++)
    {

        switch (checkHit(i, missile, matrix))
        {

//            case 0: create_arrow(i,matrix, missile);
//                continue;


        case 1:
            if(isBot)

                break;
        case 2: /*explosion: hit ground*/

            create_explosion(matrix,missile,i); //connection with drawing_destruction.c
            int x, y;
            for (x = 0; x < 100; x++)
            {
                for (y = 0; y < 80; y++)
                {
                    if (map_layout[x][y] == 1 && map_layout[x][y+1] != 1)
                    {
                        borderX[x] = y;
                        y = 80;
                    }
                    else if(y == 0 && map_layout[x][y] == 0)
                    {
                        borderX[x] = y;
                        y = 80;
                    }
                }
            }
            flag=1;
            if(isBot)
            actual_missile_position[0] = -5;
            actual_missile_position[1] = -5;

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
            m_Canvas->Refresh();
            m_Canvas->Update();
            wxMilliSleep(1);
            break;
        case 5:
            hit_armor(matrix, missile->x_vector_coordinate[i], missile->y_vector_coordinate[i], isBot);
            flag = 1;

            break;
        }
        if ( flag == 1 ) break;
    }

}

