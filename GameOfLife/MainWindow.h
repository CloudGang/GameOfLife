#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame {

private:

    // Create a DrawingPanel pointer in the MainWindow header file..
    DrawingPanel* drawingPanel;

    // store game board
    std::vector<std::vector<bool>> gameBoard;

public:
    MainWindow();
    ~MainWindow();

    // window resizing event handler declaration
    void OnSizeChange(wxSizeEvent& event);

    // access game board
    std::vector<std::vector<bool>>& GetGameBoard() { 
        return gameBoard; 
    }

    wxDECLARE_EVENT_TABLE();
};

