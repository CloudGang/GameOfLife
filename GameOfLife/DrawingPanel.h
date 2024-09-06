#pragma once
#include "wx/wx.h"

class DrawingPanel : public wxPanel {

private:
    void OnPaint(wxPaintEvent& event);

    // private variable in the drawing panel header file to store the grid size
    int gridSize = 15;

public:
    DrawingPanel(wxWindow* parent);
    ~DrawingPanel();

    // Create a method in your drawing panel header file for setting the size
    void SetSize(wxSize& size);

};

