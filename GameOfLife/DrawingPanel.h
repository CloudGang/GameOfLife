#pragma once
#include "wx/wx.h"
#include <vector>
#include "Settings.h"


class DrawingPanel : public wxPanel {

private:
    void OnPaint(wxPaintEvent& event);
    void OnMouseUp(wxMouseEvent& event);

    // store the grid size
    //int gridSize;
    // pointer to Settings
    Settings* settings;

    std::vector<std::vector<bool>>& gameBoard;
    std::vector<std::vector<int>>& neighborCount;

public:
    DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& board, std::vector<std::vector<int>>& count);
    ~DrawingPanel();

    // Create a method in your drawing panel header file for setting the size
    void SetSize(wxSize& size);

    // create a setter for the settings pointer
    void SetSettings(Settings* settings);

    void SetNeighborCount(const std::vector<std::vector<int>>& count);

    wxDECLARE_EVENT_TABLE();

};