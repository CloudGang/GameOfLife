#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame {

private:

    // Create a DrawingPanel pointer in the MainWindow header file..
    DrawingPanel* drawingPanel;

public:
    MainWindow();
    ~MainWindow();

    // window resizing event handler declaration
    void OnSizeChange(wxSizeEvent& event);
};

