#pragma once
#include "wx/wx.h"
#include <wx/colour.h>
#include <fstream>

struct Settings {
    // Colors for living and dead cells
    unsigned int livingRed = 0;
    unsigned int livingGreen = 255;
    unsigned int livingBlue = 0;
    unsigned int livingAlpha = 255;

    unsigned int deadRed = 85;
    unsigned int deadGreen = 107;
    unsigned int deadBlue = 47;
    unsigned int deadAlpha = 255;

    // Grid size and interval
    unsigned int gridSize = 15;
    unsigned int interval = 50;

    // Number of generations and grid color
    int numGenerations = 100;
    wxColour gridColor = *wxBLACK;

    bool showNeighborCount = false;

    // Returns wxColor based on RGBA values
    wxColor GetLivingCellColor() const {
        return wxColor(livingRed, livingGreen, livingBlue, livingAlpha);
    }

    wxColor GetDeadCellColor() const {
        return wxColor(deadRed, deadGreen, deadBlue, deadAlpha);
    }

    // setters/gettters
    void SetLivingCellColor(const wxColor& color) {
        livingRed = color.Red();
        livingGreen = color.Green();
        livingBlue = color.Blue();
        livingAlpha = color.Alpha();
    }

    void SetDeadCellColor(const wxColor& color) {
        deadRed = color.Red();
        deadGreen = color.Green();
        deadBlue = color.Blue();
        deadAlpha = color.Alpha();
    }

    int GetNumGenerations() const {
        return numGenerations;
    }

    void SetNumGenerations(int value) {
        numGenerations = value;
    }

    wxColour GetGridColor() const {
        return gridColor;
    }

    void SetGridColor(const wxColour& color) {
        gridColor = color;
    }

    // save settings to file
    void Save() const {
        std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(this), sizeof(Settings));
            file.close();
        }
    }

    // load the settings from file
    void Load() {
        std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(this), sizeof(Settings));
            file.close();
        }
    }
};
