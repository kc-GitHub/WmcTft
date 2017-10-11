/**
 **********************************************************************************************************************
 * @file  WmcTft.h
 * @brief Functions to show data on the display of the Wmc application.
 ***********************************************************************************************************************
 */

#ifndef WMC_TFT_H
#define WMC_TFT_H

#include "Loclib.h"
#include "Z21Slave.h"
#include <Arduino.h>

class WmcTft
{
public:
    /**
     * Enum for text xolor.
     */
    enum color
    {
        color_red,
        color_green,
        color_yellow
    };

    /* Constructor */
    WmcTft();

    /**
     *  Init the display functions.
     */
    void Init(void);

    /**
     * Clear the display.,
     */
    void Clear();

    /**
     * Update the status left up in the sreen.
     */
    void UpdateStatus(const char* StrPtr, bool clearRowFull, color textColor);

    /**
     * Update the actual selected and total number of locs right upper in the
     * screen.
     */
    void UpdateSelectedAndNumberOfLocs(uint8_t actualLocIndex, uint8_t NumberOfLocs);

    /**
     * Update loc data.
     */
    void UpdateLocInfo(
        Z21Slave::locInfo* locInfoRcvPtr, Z21Slave::locInfo* locInfoActPtr, uint8_t* assignedFunctions, bool updateAll);

    /**
     * Show |/-\ while connecting to Wifi.
     */
    void WifiConnectUpdate(uint8_t count);

    /**
     * Error message when connecting to Wifi failed.
     */
    void WifiConnectFailed();

    /**
     * Display menu.
     */
    void ShowMenu();

    /**
     * Show loc address.
     */
    void ShowlocAddress(uint16_t address, color textColor);

    /**
     * Show in middle of upper row the decoder step of selected loc.
     */
    void ShowLocDecoderSteps(uint8_t Steps);

    /**
     * Screen for adding functions.
     */
    void FunctionAddSet();

    /**
     * Update functiuon number to be added or changed.
     */
    void FunctionAddUpdate(uint16_t function);

    /**
     * Loc symbol forward.
     */
    void ShowLocSymbolFw();

    /**
     * Loc symbol backward.
     */
    void ShowLocSymbolBw();

    /**
     * Update the function info in lower part of screen.
     */
    void UpdateFunction(uint8_t Index, uint8_t Function);

private:
    /**
     * Convert color enum to display value.
     */
    uint16_t getColor(color Clr);
};

#endif
