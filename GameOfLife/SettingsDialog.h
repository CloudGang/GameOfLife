#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"
#include "Settings.h"

class SettingsDialog : public wxDialog {
public:

    SettingsDialog(wxWindow* parent, Settings* settings);
    ~SettingsDialog();

private:

    // controls
    wxSpinCtrl* gridSizeCtrl;
    wxSpinCtrl* intervalCtrl;
    wxSpinCtrl* generationsCtrl;
    wxColourPickerCtrl* livingColorPicker;
    wxColourPickerCtrl* deadColorPicker;
    wxColourPickerCtrl* gridColorPicker;

    Settings* settings;

    // event handlers
    void OnOK(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};
