/***************************************************************
 * Name:      TestWx3Main.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2014-05-12
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef TESTWX3MAIN_H
#define TESTWX3MAIN_H



#include "TestWx3App.h"
#include "CDrawable.h"
#include "shot_final_equation.h"
#include <wx/defs.h>
#include "GUIDialog.h"

class TestWx3Dialog: public GUIDialog
{
        CDrawable* Doc;
        missile_data* missile1;
        bool is2draw;
    public:
        TestWx3Dialog(wxDialog *dlg);
        ~TestWx3Dialog();

    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void m_CanvasOnPaint( wxPaintEvent& event );
		virtual void m_button2OnButtonClick( wxCommandEvent& event );
		virtual void key_function( wxKeyEvent& event );
		virtual void m_buttonExplodeOnButtonClick( wxCommandEvent& event );


};

void calculate_ray();
#endif // TESTWX3MAIN_H
