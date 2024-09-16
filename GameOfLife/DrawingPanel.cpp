#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"


wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnMouseUp)
wxEND_EVENT_TABLE()


DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& board, std::vector<std::vector<int>>& count) : wxPanel(parent), gameBoard(board), neighborCount(count) {
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    settings = nullptr;
}

// settingsssssss
void DrawingPanel::SetSettings(Settings* settings) {
    this->settings = settings;
}

DrawingPanel::~DrawingPanel()
{

}

void DrawingPanel::SetNeighborCount(const std::vector<std::vector<int>>& count) {
    neighborCount = count;
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
    //context->SetPen(*wxBLACK);
    //context->SetBrush(*wxWHITE);

    wxPen gridPen(settings->GetGridColor(), 1);
    context->SetPen(gridPen);


    // get the size of the panel
    int panelWidth, panelHeight;
    this->GetClientSize(&panelWidth, &panelHeight);

    // cell size calculation | They need to be calculated separately.
    int cellWidth = panelWidth / settings->gridSize;
    int cellHeight = panelHeight / settings->gridSize;

    // create the grid
    for (size_t row = 0; row < gameBoard.size(); ++row) {
        for (size_t col = 0; col < gameBoard[row].size(); ++col) {
            int x = col * cellWidth;
            int y = row * cellHeight;

            // check [ ] state and set color accordingly
            if (gameBoard[row][col]) {
                // alive cells
                //context->SetBrush(*wxLIGHT_GREY);
                context->SetBrush(wxBrush(settings->GetLivingCellColor()));
            }
            else {
                // dead cells
                //context->SetBrush(*wxWHITE);
                context->SetBrush(wxBrush(settings->GetDeadCellColor()));
            }
            context->DrawRectangle(x, y, cellWidth, cellHeight);

            if (settings->showNeighborCount) {
                wxString text = wxString::Format("%d", neighborCount[row][col]);
                dc.SetTextForeground(*wxWHITE);
                dc.DrawText(text, col * cellWidth + 2, row * cellHeight + 2);
            }
        }
    }
    wxSize size = GetClientSize();

    dc.SetPen(wxPen(settings->gridColor, 1));
    for (size_t row = 0; row <= gameBoard.size(); ++row) {
        dc.DrawLine(0, row * cellHeight, size.GetWidth(), row * cellHeight);
    }
    for (size_t col = 0; col <= gameBoard[0].size(); ++col) {
        dc.DrawLine(col * cellWidth, 0, col * cellWidth, size.GetHeight());
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