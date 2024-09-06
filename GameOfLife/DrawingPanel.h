#pragma once
#include "wx/wx.h"

class DrawingPanel : public wxPanel {

private:
    void OnPaint(wxPaintEvent& event);

    // Add a variable for grid size (default to 15).
    int gridSize = 15;

public:
    DrawingPanel(wxWindow* parent);
    ~DrawingPanel();

    // Create a method in your drawing panel header file for setting the size
    void SetSize(wxSize& size);

    // Add a method to set the grid size.
    void SetGridSize(int size);
};

