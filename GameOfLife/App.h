#pragma once

#include "wx/wx.h"
#include "MainWindow.h"

class App : public wxApp {

private:
	MainWindow* mainWin;

public:
	App();
	~App();
	virtual bool OnInit();
	virtual int OnExit();
};

