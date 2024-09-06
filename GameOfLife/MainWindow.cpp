#include "MainWindow.h"

// inher wxFrame
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(500, 500)) {

	// ..instantiate it in the MainWindow constructor | Make sure to pass this in as the parent.
	drawingPanel = new DrawingPanel(this);

	// Initialize the grid.
	InitializeGrid();

	// in the constructor for the main window, call bind using something similar to this
	this->Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);
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

void MainWindow::InitializeGrid() {
	// Resize the game board to grid size.
	gameBoard.resize(gridSize);

	// Resize each sub-vector.
	for (int i = 0; i < gridSize; ++i) {
		gameBoard[i].resize(gridSize, false);  // Initialize all cells as false (dead).
	}

	// Pass the grid size to the drawing panel.
	drawingPanel->SetGridSize(gridSize);
}