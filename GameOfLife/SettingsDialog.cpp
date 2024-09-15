#include "SettingsDialog.h"
#include <wx/sizer.h>
#include "Settings.h"
#include "wx/clrpicker.h"
#include "wx/stattext.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_BUTTON(wxID_OK, SettingsDialog::OnOK)
EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancel)
wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent, Settings* settings) : wxDialog(parent, wxID_ANY, "Settings", wxDefaultPosition, wxSize(250, 400)), settings(settings) {

    // main vertical sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // create controls
    livingColorPicker = new wxColourPickerCtrl(this, wxID_ANY);
    deadColorPicker = new wxColourPickerCtrl(this, wxID_ANY);
    gridSizeCtrl = new wxSpinCtrl(this, wxID_ANY);
    intervalCtrl = new wxSpinCtrl(this, wxID_ANY);

    // set controls to the current settings
    livingColorPicker->SetColour(settings->GetLivingCellColor());
    deadColorPicker->SetColour(settings->GetDeadCellColor());
    gridSizeCtrl->SetValue(settings->gridSize);
    intervalCtrl->SetValue(settings->interval);

    // grid size control
    wxBoxSizer* gridSizeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* gridSizeLabel = new wxStaticText(this, wxID_ANY, "Grid Size: ");
    gridSizeCtrl->SetRange(5, 100);
    gridSizeSizer->Add(gridSizeLabel, 1, wxEXPAND | wxALL, 5);
    gridSizeSizer->Add(gridSizeCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(gridSizeSizer, 0, wxEXPAND);

    // interval control
    wxBoxSizer* intervalSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* intervalLabel = new wxStaticText(this, wxID_ANY, "Interval (ms): ");
    intervalCtrl->SetRange(10, 5001);
    intervalSizer->Add(intervalLabel, 1, wxEXPAND | wxALL, 5);
    intervalSizer->Add(intervalCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(intervalSizer, 0, wxEXPAND);

    // generations control
    wxBoxSizer* generationsSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* generationsLabel = new wxStaticText(this, wxID_ANY, "Generations: ");
    generationsCtrl = new wxSpinCtrl(this, wxID_ANY);
    generationsCtrl->SetRange(10, 1001);
    generationsSizer->Add(generationsLabel, 1, wxEXPAND | wxALL, 5);
    generationsSizer->Add(generationsCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(generationsSizer, 0, wxEXPAND);

    // living color picker
    wxBoxSizer* livingColorSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* livingColorLabel = new wxStaticText(this, wxID_ANY, "Living Cell Color: ");
    livingColorSizer->Add(livingColorLabel, 1, wxEXPAND | wxALL, 5);
    livingColorSizer->Add(livingColorPicker, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(livingColorSizer, 0, wxEXPAND);

    // dead color picker
    wxBoxSizer* deadColorSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* deadColorLabel = new wxStaticText(this, wxID_ANY, "Dead Cell Color: ");
    deadColorSizer->Add(deadColorLabel, 1, wxEXPAND | wxALL, 5);
    deadColorSizer->Add(deadColorPicker, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(deadColorSizer, 0, wxEXPAND);

    // grid color picker
    wxBoxSizer* gridColorSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* gridColorLabel = new wxStaticText(this, wxID_ANY, "Grid Color: ");
    gridColorPicker = new wxColourPickerCtrl(this, wxID_ANY, settings->GetGridColor());
    gridColorSizer->Add(gridColorLabel, 1, wxEXPAND | wxALL, 5);
    gridColorSizer->Add(gridColorPicker, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(gridColorSizer, 0, wxEXPAND);

    // ok and Cancel buttons
    wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);
}

SettingsDialog::~SettingsDialog() {

    delete livingColorPicker;
    delete deadColorPicker;
    delete gridSizeCtrl;
    delete intervalCtrl;
}
void SettingsDialog::OnOK(wxCommandEvent& event) {

    // saving the settings
    settings->gridSize = gridSizeCtrl->GetValue();
    settings->interval = intervalCtrl->GetValue();
    settings->numGenerations = generationsCtrl->GetValue();
    settings->SetLivingCellColor(livingColorPicker->GetColour());
    settings->SetDeadCellColor(deadColorPicker->GetColour());
    settings->SetGridColor(gridColorPicker->GetColour());

    settings->Save();

    // close dialog
    EndModal(wxID_OK);
}

void SettingsDialog::OnCancel(wxCommandEvent& event) {
    
    // obvious
    EndModal(wxID_CANCEL);
}
