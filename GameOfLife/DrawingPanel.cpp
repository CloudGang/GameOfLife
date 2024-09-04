#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

DrawingPanel::DrawingPanel(wxWindow* parent) : wxPanel(parent) {

    // drawing panel render control
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    // wxPanel needs to know to use the OnPaint method when it renders
    this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
}

DrawingPanel::~DrawingPanel()
{
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    // Add the following two lines of code to the beginning of the method
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    // drawing surface
    wxGraphicsContext* context = wxGraphicsContext::Create(dc);
    if (!context) {
        return;
    }

    // control over some colors [ Pen = the Stroke | Brush = the Fill ]
    context->SetPen(*wxBLACK);
    context->SetBrush(*wxWHITE);

    // draw something on the drawing panel by calling the DrawRectangle method on the graphics context
    //context->DrawRectangle(40, 25, 100, 100);

    //// Try creating some more shapes
    //context->DrawEllipse(40, 25, 50, 50);

    //context->SetBrush(*wxGREEN);
    //context->DrawEllipse(90, 75, 50, 50);

    //////////////////////////////////////////////////////////////////

    // For now cell width/height can be assumed to be 10
    //int cellSize = 10;

    //// It now time to create the grid | The rectangles will need to be creating using a series of loops using some math
    //for (int row = 0; row < gridSize; ++row) {
    //    for (int col = 0; col < gridSize; ++col) {
    //        int x = col * cellSize;
    //        int y = row * cellSize;
    //        context->DrawRectangle(x, y, cellSize, cellSize);
    //    }
    //}

    //////////////////////////////////////////////////////////////////
    
    // get the size of the panel
    int panelWidth, panelHeight;
    this->GetClientSize(&panelWidth, &panelHeight);

    // cell size calculation | They need to be calculated separately.
    int cellWidth = panelWidth / gridSize;
    int cellHeight = panelHeight / gridSize;

    // create the grid
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            int x = col * cellWidth;
            int y = row * cellHeight;
            context->DrawRectangle(x, y, cellWidth, cellHeight);
        }
    }
    delete context;
}