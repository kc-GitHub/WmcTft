/**
 **********************************************************************************************************************
 * @file  WmcTft.h
 * @brief Functions to show data on the display of the Wmc application.
 ***********************************************************************************************************************
 */

#ifndef WMC_TFT_H
#define WMC_TFT_H

/***********************************************************************************************************************
 * I N C L U D E S
 **********************************************************************************************************************/
#include "Loclib.h"
#include "Z21Slave.h"
#include <Arduino.h>

/***********************************************************************************************************************
 * T Y P E D E F S  /  E N U M
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * C L A S S E S
 **********************************************************************************************************************/
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
        color_white,
        color_yellow,
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
     * Show the name is the network connecting to...
     */
    void ShowNetworkName(const char* StrPtr);

    /**
     * Clear the network name on the screen.
     */
    void ClearNetworkName(void);

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
     * Show | or - while connecting to Wifi.
     */
    void WifiConnectUpdate(uint8_t count);

    /**
     * Error message when connecting to Wifi failed.
     */
    void WifiConnectFailed();

    /**
     * Error message when connecting to Z21 control unit failed.
     */
    void UdpConnectFailed();

    /**
     * Display menu.
     */
    void ShowMenu();

    /**
     * Show initial turnout screen.
     */
    void ShowTurnoutScreen();

    /**
     * Show turnout address
     */
    void ShowTurnoutAddress(uint16_t address);

    /**
     * Show turnout direction
     */
    void ShowTurnoutDirection(uint8_t direction);

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
    void ShowLocSymbolFw(color locSymbolColor);

    /**
     * Loc symbol backward.
     */
    void ShowLocSymbolBw(color locSymbolColor);

    /**
     * Update the function info in lower part of screen.
     */
    void UpdateFunction(uint8_t Index, uint8_t Function);

    /**
     * Show command line screen.
     */
    void CommandLine(void);

private:
    /**
     * Convert color enum to display value.
     */
    uint16_t getColor(color Clr);
};

#endif
