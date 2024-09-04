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
    context->DrawRectangle(40, 25, 100, 100);

    // Try creating some more shapes
    context->DrawEllipse(40, 25, 50, 50);

    context->SetBrush(*wxGREEN);
    context->DrawEllipse(90, 75, 50, 50);

    delete context;
}