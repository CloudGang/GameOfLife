#pragma once
#include "wx/wx.h"

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

    // Returns wxColor based on RGBA values
    wxColor GetLivingCellColor() const {
        return wxColor(livingRed, livingGreen, livingBlue, livingAlpha);
    }

    wxColor GetDeadCellColor() const {
        return wxColor(deadRed, deadGreen, deadBlue, deadAlpha);
    }

    // Setters for wxColor to update the RGBA values
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
};
