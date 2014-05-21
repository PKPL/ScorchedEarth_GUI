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

int map_layout[100][80] = {{0}};
int borderX[100];

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
    wxMessageBox(msg, _("Welcome to..."));
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

    create_mountain_map(map_layout);

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
