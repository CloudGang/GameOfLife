#include "SettingsDialog.h"

// Event table definition
wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_BUTTON(wxID_OK, SettingsDialog::OnOk)
EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancel)
wxEND_EVENT_TABLE()

// Constructor
SettingsDialog::SettingsDialog(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxDialog(parent, id, title, wxDefaultPosition, wxSize(300, 200))
{
    // Main vertical sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Spin control sizer
    wxBoxSizer* spinSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* spinLabel = new wxStaticText(this, wxID_ANY, "Select Number:");
    m_spinCtrl = new wxSpinCtrl(this, wxID_ANY);
    spinSizer->Add(spinLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    spinSizer->Add(m_spinCtrl, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(spinSizer, 0, wxALL | wxEXPAND, 5);

    // Colour picker sizer
    wxBoxSizer* colorSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* colorLabel = new wxStaticText(this, wxID_ANY, "Select Color:");
    m_colourPicker = new wxColourPickerCtrl(this, wxID_ANY);
    colorSizer->Add(colorLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    colorSizer->Add(m_colourPicker, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(colorSizer, 0, wxALL | wxEXPAND, 5);

    // OK and Cancel button sizer
    wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    mainSizer->Add(buttonSizer, 0, wxALL | wxALIGN_CENTER, 10);

    // Set the main sizer
    SetSizer(mainSizer);
}

// OK button event handler
void SettingsDialog::OnOk(wxCommandEvent& event)
{
    // Apply settings (store the selected values in settings object)
    // For example:
    // settings->SetValue(m_spinCtrl->GetValue());
    // settings->SetColor(m_colourPicker->GetColour());

    // Close the dialog
    EndModal(wxID_OK);
}

// Cancel button event handler
void SettingsDialog::OnCancel(wxCommandEvent& event)
{
    // Close the dialog without saving changes
    EndModal(wxID_CANCEL);
}