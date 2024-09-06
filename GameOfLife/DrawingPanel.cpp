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

    
    // get the size of the panel
    int panelWidth, panelHeight;
    this->GetClientSize(&panelWidth, &panelHeight);

    // cell size calculation | They need to be calculated separately.
    int cellWidth = panelWidth / this->gridSize;
    int cellHeight = panelHeight / this->gridSize;

    // create the grid
    for (int row = 0; row < this->gridSize; ++row) {
        for (int col = 0; col < this->gridSize; ++col) {
            int x = col * cellWidth;
            int y = row * cellHeight;
            context->DrawRectangle(x, y, cellWidth, cellHeight);
        }
    }
    delete context;
}

void DrawingPanel::SetSize(wxSize& size) {

    // first call SetSize on the base wxPanel class
    wxPanel::SetSize(size);

    // "Then call Refresh();
    Refresh();               
}

void DrawingPanel::SetGridSize(int size) {
    gridSize = size;
    Refresh();
}