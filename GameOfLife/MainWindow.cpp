#include "MainWindow.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_SIZE(MainWindow::OnSizeChange)
	EVT_MENU(10001, MainWindow::OnPlay)
	EVT_MENU(10002, MainWindow::OnPause)
	EVT_MENU(10003, MainWindow::OnNext)
	EVT_MENU(10004, MainWindow::OnClear)
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

	//intialize
	toolBar = CreateToolBar();

	// add buttons to the toolbar
	wxBitmap playIcon(play_xpm);
	toolBar->AddTool(10001, "Play", playIcon);
	// Repeat for other icons (pause, next, clear)
	wxBitmap pauseIcon(pause_xpm);
	toolBar->AddTool(10002, "Pause", pauseIcon);
	wxBitmap nextIcon(next_xpm);
	toolBar->AddTool(10003, "Next", nextIcon);
	wxBitmap clearIcon(trash_xpm);
	toolBar->AddTool(10004, "Clear", clearIcon);

	// finalize toolbar setup
	toolBar->Realize();

	// refresh its layout by adding this->Layout()
	this->Layout();
}

MainWindow::~MainWindow() {
}

void MainWindow::OnSizeChange(wxSizeEvent& event) {

	// inside of the method, save the size of the window as a wxSize
	wxSize newSize = this->GetSize();

	// check to avoid crash
	if (drawingPanel) {
		drawingPanel->SetSize(newSize);
	}

	// add event.Skip() as the final line
	event.Skip();
}

// leave empty for now
void MainWindow::OnPlay(wxCommandEvent& event) {
}

void MainWindow::OnPause(wxCommandEvent& event) {
}

void MainWindow::OnNext(wxCommandEvent& event) {
	ComputeNextGeneration();
}

void MainWindow::OnClear(wxCommandEvent& event) {
}

void MainWindow::UpdateStatusBar() {
	wxString generationText = wxString::Format("Generations: %i", generationCount);
	wxString livingCellsText = wxString::Format("Living Cells: %i", livingCellsCount);

	statusBar->SetStatusText(generationText, 0);
	statusBar->SetStatusText(livingCellsText, 1);
}

int MainWindow::CountLivingNeighbors(int row, int col) const {
	int livingNeighbors = 0;

	// check neighboring cells
	for (int r = row - 1; r <= row + 1; ++r) {
		for (int c = col - 1; c <= col + 1; ++c) {

			// if itself, skip
			if (r != row || c != col) {

				// check neighbor
				if (r >= 0 && r < gameBoard.size() && c >= 0 && c < gameBoard[r].size()) {
					if (gameBoard[r][c]) {
						++livingNeighbors;
					}
				}
			}
		}
	}

	return livingNeighbors;
}

void MainWindow::ComputeNextGeneration() {

	// create sandbox to store next generation
	std::vector<std::vector<bool>> sandbox(gameBoard.size(), std::vector<bool>(gameBoard[0].size(), false));

	// iterate over each cell in the game board
	for (size_t row = 0; row < gameBoard.size(); ++row) {
		for (size_t col = 0; col < gameBoard[row].size(); ++col) {
			int livingNeighbors = CountLivingNeighbors(row, col);

			// apply GoL rules
			if (gameBoard[row][col]) {
				
				// living cell
				if (livingNeighbors < 2 || livingNeighbors > 3) {
					sandbox[row][col] = false;
				}
				else {
					sandbox[row][col] = true;
				}
			}
			else {
				
				// dead cell
				if (livingNeighbors == 3) {
					sandbox[row][col] = true;
				}
			}
		}
	}

	// swap the sandbox with the game board
	gameBoard.swap(sandbox);

	// update living cell count
	livingCellsCount = 0;
	for (const auto& row : gameBoard) {
		for (bool cell : row) {
			if (cell) {
				++livingCellsCount;
			}
		}
	}

	// update the generation count
	++generationCount;

	// update the status bar
	UpdateStatusBar();

	// refresh the drawing panel
	drawingPanel->Refresh();
}
