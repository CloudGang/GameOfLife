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
EVT_TIMER(TIMER_ID, MainWindow::OnTimer)
wxEND_EVENT_TABLE()


// inher wxFrame
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(500, 500)), generationCount(0), livingCellsCount(0) {

	// initialize the game board with default values (false = dead cells) - using settings grid size
	gameBoard.resize(settings.gridSize, std::vector<bool>(settings.gridSize, false));

	// ..instantiate it in the MainWindow constructor | Make sure to pass this in as the parent.
	drawingPanel = new DrawingPanel(this, gameBoard);

	// Set the settings object for DrawingPanel
	drawingPanel->SetSettings(&settings); 


	// 2 fields status bar
	statusBar = CreateStatusBar(2);

	// update the status bar
	UpdateStatusBar();

	//intialize
	toolBar = CreateToolBar();

	// add buttons to the toolbar
	wxBitmap playIcon(play_xpm);
	toolBar->AddTool(10001, "Play", playIcon);
	// repeat for other icons (pause, next, clear)
	wxBitmap pauseIcon(pause_xpm);
	toolBar->AddTool(10002, "Pause", pauseIcon);
	wxBitmap nextIcon(next_xpm);
	toolBar->AddTool(10003, "Next", nextIcon);
	wxBitmap clearIcon(trash_xpm);
	toolBar->AddTool(10004, "Clear", clearIcon);

	// finalize toolbar setup
	toolBar->Realize();

	// timer initialize
	timer = new wxTimer(this, TIMER_ID);

	// refresh its layout by adding this->Layout()
	this->Layout();
}

MainWindow::~MainWindow() {
	delete timer;
	delete drawingPanel;
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


void MainWindow::OnPlay(wxCommandEvent& event) {
	timer->Start(TIMER_INTERVAL);
}

void MainWindow::OnPause(wxCommandEvent& event) {
	timer->Stop();
}

void MainWindow::OnNext(wxCommandEvent& event) {
	ComputeNextGeneration();
}

void MainWindow::OnClear(wxCommandEvent& event) {
	ClearBoard();
}

void MainWindow::UpdateStatusBar() {
	statusBar->SetStatusText(wxString::Format("Generation: %d", generationCount), 0);
	statusBar->SetStatusText(wxString::Format("Living Cells: %d", livingCellsCount), 1);
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

void MainWindow::ClearBoard() {

	// reset game board to all dead [ ]
	for (auto& row : gameBoard) {
		std::fill(row.begin(), row.end(), false);
	}

	// reset generation and living cells count
	generationCount = 0;
	livingCellsCount = 0;

	UpdateStatusBar();

	drawingPanel->Refresh();
}

void MainWindow::OnTimer(wxTimerEvent& event) {
	ComputeNextGeneration();
}