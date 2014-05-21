///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIDialog__
#define __GUIDialog__

#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class GUIDialog
///////////////////////////////////////////////////////////////////////////////
class GUIDialog : public wxDialog
{
	private:

	protected:
		wxPanel* m_panel1;
		wxStaticBitmap* top_image;
		wxScrolledWindow* m_Canvas;
		wxButton* m_button2;
		wxButton* m_buttonExplode;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void key_function( wxKeyEvent& event ) { event.Skip(); }
		virtual void m_CanvasOnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void m_button2OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonExplodeOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		GUIDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Scorched Earth"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 936,720 ), long style = wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX );
		~GUIDialog();

};

#endif //__GUIDialog__
