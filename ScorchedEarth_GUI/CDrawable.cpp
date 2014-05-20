#include "CDrawable.h"
#include "TestWx3Main.h"
#include "maps_create.h"
#include "maps.h"

CDrawable::CDrawable()
{
    angle1 = M_PI/4;
    angle2 = 2*M_PI/3;
}

CDrawable::~CDrawable()
{
    //dtor
}

int map_layout[100][80] = {{0}};
int borderX[100];

void CDrawable::Draw(wxBufferedPaintDC & DC, int CWidth, int CHeight)
{
    wxBrush Brush(*wxWHITE);
    DC.SetBrush(Brush);
    DC.SetBackground(Brush);
    DC.Clear();
    //drawTank(DC, 50, 300, *wxRED, angle1);
    //drawTank(DC, 450, 300, *wxBLUE, angle2);
    //drawLineTest(DC, *wxRED);
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

void TestWx3Dialog::m_button2OnButtonClick( wxCommandEvent& event )
{
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


void CDrawable::drawLineTest(wxBufferedPaintDC& DC, wxColor C)
{
    wxBrush B;
    wxPen P;
    B.SetColour(*wxWHITE);
    DC.SetBrush(B);
    P.SetColour(C);
    P.SetWidth(3);
    DC.SetPen(P);
    //DC.DrawLine(wxPoint(0, 0),wxPoint(600, 400));
    int x;
    for (x = -5; x < 95; x++)
    {
        DC.DrawLine(wxPoint(x+5, borderX[x+5]), wxPoint(x+6, borderX[x+6]));
    }
}

void CDrawable::drawTank(wxBufferedPaintDC& DC, int X, int Y, wxColor C, double angle)
{
    wxBrush B;
    wxPen P;
    B.SetColour(*wxWHITE);
    DC.SetBrush(B);
    P.SetColour(C);
    P.SetWidth(3);
    DC.SetPen(P);
    DC.DrawCircle(wxPoint(X,Y),wxCoord(10));
    DC.DrawCircle(wxPoint(X+10,Y),wxCoord(10));
    DC.DrawCircle(wxPoint(X+20,Y),wxCoord(10));
    DC.DrawRectangle(wxPoint(X-10,Y-26),wxSize(40,15));
    x1 = X+10+20*cos(angle);
    y1 = Y-26-20*sin(angle);
    DC.DrawLine(wxPoint(X+10,Y-26),wxPoint(x1,y1));
}
