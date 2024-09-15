#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"


wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnMouseUp)
wxEND_EVENT_TABLE()


DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& board)
    : wxPanel(parent), gameBoard(board), settings(nullptr) {
    // drawing panel render control
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
}

// ??
void DrawingPanel::SetSettings(Settings* newSettings) {
    settings = newSettings;
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

    // Get grid size and colors from settings
    int gridSize = settings->gridSize;
    wxColor livingColor = settings->GetLivingCellColor();
    wxColor deadColor = settings->GetDeadCellColor();

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
                //context->SetBrush(*wxLIGHT_GREY);
                context->SetBrush(wxBrush(livingColor));
            }
            else {
                // dead cells
                //context->SetBrush(*wxWHITE);
                context->SetBrush(wxBrush(deadColor));
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

    // grid size
    int gridSize = this->settings->gridSize;

    int cellWidth = panelWidth / gridSize;
    int cellHeight = panelHeight / gridSize;

    int row = y / cellHeight;
    int col = x / cellWidth;

    if (row >= 0 && row < gridSize && col >= 0 && col < gridSize) {
        this->gameBoard[row][col] = !this->gameBoard[row][col];
        Refresh();
    }
}
void DrawingPanel::SetSize(wxSize& size) {

    // first call SetSize on the base wxPanel class
    wxPanel::SetSize(size);

    // "Then call Refresh();
    Refresh();
}