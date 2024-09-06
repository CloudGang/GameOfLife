#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include <vector>

class MainWindow : public wxFrame {

private:

    // Create a DrawingPanel pointer in the MainWindow header file..
    DrawingPanel* drawingPanel;

    // Add a variable for grid size (default to 15).
    int gridSize = 15;

    // Create a vector of vectors to represent the game board.
    std::vector<std::vector<bool>> gameBoard;

public:
    MainWindow();
    ~MainWindow();

    // window resizing event handler declaration
    void OnSizeChange(wxSizeEvent& event);

    // Method to initialize the grid.
    void InitializeGrid();

};

