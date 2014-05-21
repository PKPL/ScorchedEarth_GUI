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
#include <time.h>


int map_layout[100][80] = {{0}};
int borderX[100];
float player_ray[4];
float enemy_ray[2];
float angle_drawing_distanse = 10;
float angle_drawing_distanse_floating = 10;
int player_angle = 60;
int enemy_angle = 110;
float player_power = 100;
int actual_missile_position[2] = {(-5)};

float psyhics_framerate = 10;

int isEND = 0;

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

    isEND = 0;
    choose_levels(2, 2);
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

    calculate_ray(false);
    calculate_ray(true);


    m_Canvas->Refresh();
    m_Canvas->SetFocus();
}

void TestWx3Dialog::key_function( wxKeyEvent& event)
{
    if(isEND == 0)
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
        if(bot.hp <= 0)isEND = 1;
        else
        {
        int temp_angle;
        int temp_power;
        missile = initializeMissile(bot.x, bot.y);
        ai(bot,map_layout, temp_angle, temp_power); //Calc values
        enemy_angle = temp_angle;
        calculate_ray(true);

        shoot_function(missile, 150, temp_angle, map_layout,true, wind_speed);
        }


        if(player.hp <= 0)isEND = 2;
        break;

    }

    calculate_ray(false);
    m_Canvas->Refresh();
    }
}


void calculate_ray(bool isBot)
{

    angle_drawing_distanse = 5;
    angle_drawing_distanse_floating = player_power/10.0;

    if(!isBot)
    {

        player_ray[0] = player.x + angle_drawing_distanse*cos(player_angle * PI / 180.0 );
        player_ray[1] = (player.y + angle_drawing_distanse*sin(player_angle * PI / 180.0 ));

        player_ray[2] = player.x + angle_drawing_distanse_floating*cos(player_angle * PI / 180.0 );
        player_ray[3] = (player.y + angle_drawing_distanse_floating*sin(player_angle * PI / 180.0 ));

    }
    else
    {
        enemy_ray[0] = bot.x + angle_drawing_distanse*cos(enemy_angle * PI / 180.0 );
        enemy_ray[1] = (bot.y + angle_drawing_distanse*sin(enemy_angle * PI / 180.0 ));
    }

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
        if(missile->x_vector_coordinate[i] < -10)break;
        else if(missile->x_vector_coordinate[i] > 110)break;
        //wxMilliSleep(5);

        for(;;)
        {
            actual_missile_position[0] = missile->x_vector_coordinate[i];
            actual_missile_position[1] = missile->y_vector_coordinate[i];
            m_Canvas->Refresh();
            m_Canvas->Update();
            if(psyhics_delay())break;
        }

        switch (checkHit(i, missile, matrix))
        {

//            case 0: create_arrow(i,matrix, missile);
//                continue;


        case 1:
            if(isBot)

            break;
        case 2: /*explosion: hit ground*/

            create_explosion(matrix,missile,i); //connection with drawing_destruction.c
            falling(matrix);
            calculate_ray(true);
            calculate_ray(false);
            m_Canvas->Refresh();
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

            //wxMilliSleep(5);
            break;
        case 5:
            hit_armor(matrix, missile->x_vector_coordinate[i], missile->y_vector_coordinate[i], isBot);
            flag = 1;

            break;
        }
        if ( flag == 1 ) break;
    }

}

bool psyhics_delay()
{

    static clock_t first_timer = clock();
    static clock_t second_timer = clock();
    float diff;

    if(first_timer == 0)
    {
        first_timer = clock();
        second_timer = clock();
    }

    static float reverse_time = (1.0/psyhics_framerate) * 100;

    second_timer = clock();
    diff = ((second_timer - first_timer)*1000)/CLOCKS_PER_SEC;

    if(diff >= reverse_time)
    {
         first_timer = 0;
         second_timer = 0;
         return true;
    }
    return false;


}





