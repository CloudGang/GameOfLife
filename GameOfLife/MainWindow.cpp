#include "MainWindow.h"

// inher wxFrame
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(500, 500)) {

	// ..instantiate it in the MainWindow constructor | Make sure to pass this in as the parent.
	drawingPanel = new DrawingPanel(this);


}

MainWindow::~MainWindow() {
}
