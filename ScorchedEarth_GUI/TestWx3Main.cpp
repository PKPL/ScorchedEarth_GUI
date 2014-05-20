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

int map_layout[100][80] = {{0}};

TestWx3Dialog::TestWx3Dialog(wxDialog *dlg)
    : GUIDialog(dlg)
{
    m_Canvas->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    Doc = new CDrawable();
    missile1 = NULL;
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
    wxMessageBox(msg, _("Welcome to..."));
}

void TestWx3Dialog::m_CanvasOnPaint( wxPaintEvent& event )
{
    wxBufferedPaintDC DC(m_Canvas);
    int CWidth,CHeight;
    m_Canvas->GetSize(&CWidth,&CHeight);
    Doc->Draw(DC, CWidth, CHeight);
    if(missile1!=NULL)Doc->DrawShot(DC, CWidth, CHeight, missile1);
}

void TestWx3Dialog::m_button3OnButtonClick( wxCommandEvent& event )
{
    Doc->angle1 += 0.1;
    missile1 = NULL;
    m_Canvas->Refresh();
}

void TestWx3Dialog::m_button4OnButtonClick( wxCommandEvent& event )
{
    Doc->angle1 -= 0.1;
    missile1 = NULL;
    m_Canvas->Refresh();
}

void TestWx3Dialog::m_button5OnButtonClick( wxCommandEvent& event )
{
    missile1 = initializeMissile(Doc->x1, Doc->y1);
    xCoordinate(missile1, 0);
    yCoordinate(missile1);
    m_Canvas->Refresh();
}

void TestWx3Dialog::m_button2OnButtonClick( wxCommandEvent& event )
{
    create_mountain_map(map_layout);
    int borderX[100];
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

    for (x = 0; x < 100; x++)
    {
        if (x > 99)
        {
            Close();
        }
        wxString lelel = ( wxT(""));
        lelel.append(wxString::Format(wxT("(%d, %d)"), (int)x, (int)borderX[x]));
        m_textTest->AppendText(lelel);

    }
    //It verifies correctly so borderX holds the border line, How to use:
    //Like a maths function, consider f(x) = borderX[X]
    // If you want to know the border value of the terrain on X = 3: f(3) = y3, which means, borderX[3] retrieves the Y3 value.
    //The points it displays when you click the button are the border points for each X in the map generated. format: (x, y)

}

