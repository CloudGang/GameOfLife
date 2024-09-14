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

public:
    DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& board);
    ~DrawingPanel();

    // Create a method in your drawing panel header file for setting the size
    void SetSize(wxSize& size);

    // create a setter for the settings pointer
    void SetSettings(Settings* settings);

    wxDECLARE_EVENT_TABLE();

};

