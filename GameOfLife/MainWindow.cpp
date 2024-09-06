#include "MainWindow.h"


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
wxEND_EVENT_TABLE()


// inher wxFrame
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(500, 500)), generationCount(0), livingCellsCount(0) {

	// initialize the game board with default values (false = dead cells)
	gameBoard.resize(15, std::vector<bool>(15, false));

	// ..instantiate it in the MainWindow constructor | Make sure to pass this in as the parent.
	drawingPanel = new DrawingPanel(this, gameBoard);

	// 2 fields status bar
	statusBar = CreateStatusBar(2);

	// update the status bar
	UpdateStatusBar();

	// refresh its layout by adding this->Layout()
	this->Layout();
}

MainWindow::~MainWindow() {
}

void MainWindow::OnSizeChange(wxSizeEvent& event) {

	// inside of the method, save the size of the window as a wxSize
	wxSize newSize = this->GetSize();

	// pass it along to a SetSize method that needs to be created for the drawing panel object
	drawingPanel->SetSize(newSize);

	// add event.Skip() as the final line
	event.Skip();
}

void MainWindow::UpdateStatusBar() {
	wxString generationText = wxString::Format("Generations: %i", generationCount);
	wxString livingCellsText = wxString::Format("Living Cells: %i", livingCellsCount);

	statusBar->SetStatusText(generationText, 0);
	statusBar->SetStatusText(livingCellsText, 1);
}