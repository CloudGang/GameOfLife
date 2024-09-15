#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/clrpicker.h>

class SettingsDialog : public wxDialog {
public:
    SettingsDialog(wxWindow* parent, wxWindowID id, const wxString& title);

private:
    // Declare controls
    wxSpinCtrl* m_spinCtrl;
    wxColourPickerCtrl* m_colourPicker;

    // Event handlers
    void OnOk(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};
