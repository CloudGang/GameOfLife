#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& board) : wxPanel(parent), gameBoard(board), gridSize(15) {

    // drawing panel render control
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    // wxPanel needs to know to use the OnPaint method when it renders
    this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);

    // mouse event
    this->Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseUp, this);

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
    int cellWidth = panelWidth / gridSize;
    int cellHeight = panelHeight / gridSize;

    // create the grid
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            int x = col * cellWidth;
            int y = row * cellHeight;

            // check [ ] state and set color accordingly
            if (gameBoard[row][col]) {
                // alive cells
                context->SetBrush(*wxLIGHT_GREY);
            }
            else {
                // dead cells
                context->SetBrush(*wxWHITE);
            }
            context->DrawRectangle(x, y, cellWidth, cellHeight);
        }
    }
    delete context;
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event) {
    int x = event.GetX();
    int y = event.GetY();

    int panelWidth, panelHeight;
    this->GetClientSize(&panelWidth, &panelHeight);

    int cellWidth = panelWidth / gridSize;
    int cellHeight = panelHeight / gridSize;

    int row = y / cellHeight;
    int col = x / cellWidth;

    if (row >= 0 && row < gridSize && col >= 0 && col < gridSize) {
        gameBoard[row][col] = !gameBoard[row][col];
        Refresh();
    }
}
void DrawingPanel::SetSize(wxSize& size) {

    // first call SetSize on the base wxPanel class
    wxPanel::SetSize(size);

    // "Then call Refresh();
    Refresh();               
}