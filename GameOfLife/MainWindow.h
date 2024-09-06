#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include <vector>

class wxCommandEvent;

class MainWindow : public wxFrame {

private:

    // Create a DrawingPanel pointer in the MainWindow header file..
    DrawingPanel* drawingPanel;

    // store game board
    std::vector<std::vector<bool>> gameBoard;

    // status information
    int generationCount;
    int livingCellsCount;

    // add a status bar variable to the main window header file 
    wxStatusBar* statusBar;

    // toolbar
    wxToolBar* toolBar;

public:
    MainWindow();
    ~MainWindow();

    // window resizing event handler declaration
    void OnSizeChange(wxSizeEvent& event);
    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);

    // access game board
    std::vector<std::vector<bool>>& GetGameBoard() { 
        return gameBoard; 
    }

    // count living neighbors
    int CountLivingNeighbors(int row, int col) const;

    // next gen
    void ComputeNextGeneration();

    // clear board
    void ClearBoard();

    void UpdateStatusBar();

    wxDECLARE_EVENT_TABLE();
};

