#pragma once
#include "wx/wx.h"
#include <vector>

class DrawingPanel : public wxPanel {

private:
    void OnPaint(wxPaintEvent& event);
    void OnMouseUp(wxMouseEvent& event);

    // store the grid size
    int gridSize;
    std::vector<std::vector<bool>>& gameBoard;

public:
    DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& board);
    ~DrawingPanel();

    // Create a method in your drawing panel header file for setting the size
    void SetSize(wxSize& size);

    wxDECLARE_EVENT_TABLE();

};

