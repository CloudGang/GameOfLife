#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include "Settings.h"
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

    // timer
    wxTimer* timer;
    static const int TIMER_ID = 10000;
    static const int TIMER_INTERVAL = 50;
    static const int wxID_SETTINGS = 11111;

    // add settings object/should not be a pointer
    Settings settings;
    void OnSettings(wxCommandEvent& event);
    void UpdateGridSettings();


public:
    MainWindow();
    ~MainWindow();

    // window resizing event handler declaration
    void OnSizeChange(wxSizeEvent& event);
    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);

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
