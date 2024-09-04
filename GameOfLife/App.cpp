#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {

	//Instantiate the MainWindow pointer
	mainWin = new MainWindow();
	//Call the Show() method on the pointer 
	mainWin->Show();
	return true;
}