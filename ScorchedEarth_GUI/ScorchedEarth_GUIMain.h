/***************************************************************
 * Name:      ScorchedEarth_GUIMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2014-05-19
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef SCORCHEDEARTH_GUIMAIN_H
#define SCORCHEDEARTH_GUIMAIN_H

//(*Headers(ScorchedEarth_GUIFrame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class ScorchedEarth_GUIFrame: public wxFrame
{
    public:

        ScorchedEarth_GUIFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ScorchedEarth_GUIFrame();

    private:

        //(*Handlers(ScorchedEarth_GUIFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(ScorchedEarth_GUIFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(ScorchedEarth_GUIFrame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SCORCHEDEARTH_GUIMAIN_H
