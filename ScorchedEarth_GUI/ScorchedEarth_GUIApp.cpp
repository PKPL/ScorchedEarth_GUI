/***************************************************************
 * Name:      ScorchedEarth_GUIApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2014-05-19
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "ScorchedEarth_GUIApp.h"

//(*AppHeaders
#include "ScorchedEarth_GUIMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ScorchedEarth_GUIApp);

bool ScorchedEarth_GUIApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	ScorchedEarth_GUIFrame* Frame = new ScorchedEarth_GUIFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
