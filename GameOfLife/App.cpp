#include "App.h"
#include "MainWindow.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#define MEMORY_LEAK_LINE -1

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(MEMORY_LEAK_LINE);

	//Instantiate the MainWindow pointer
	mainWin = new MainWindow();
	//Call the Show() method on the pointer 
	mainWin->Show();
	return true;
}

int App::OnExit()
{
	_CrtDumpMemoryLeaks();
	return wxApp::OnExit();
}