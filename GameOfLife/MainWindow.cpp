#include "MainWindow.h"

// inher wxFrame
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(500, 500)) {

	// ..instantiate it in the MainWindow constructor | Make sure to pass this in as the parent.
	drawingPanel = new DrawingPanel(this);

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