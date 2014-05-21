#ifndef CDRAWABLE_H
#define CDRAWABLE_H

#include <wx/dcbuffer.h>
#include "shot_final_equation.h"

class CDrawable
{
    public:
        double angle1, angle2;
        double x1, y1;
        CDrawable();
        virtual ~CDrawable();
        void Draw(wxBufferedPaintDC& DC);
        void DrawShot(wxBufferedPaintDC& DC, int CWidth, int CHeight, missile_data* m);
        void drawLineTest(wxBufferedPaintDC& DC, wxColor C, int map_layout[100][80], int borderX[100]);
    protected:
    private:
        virtual void m_button2OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
};

#endif // CDRAWABLE_H
