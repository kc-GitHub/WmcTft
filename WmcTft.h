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

    /**
     * Decoder step.
     */
    enum locoDecoderSteps
    {
        locoDecoderSpeedSteps14 = 0,
        locoDecoderSpeedSteps28,
        locoDecoderSpeedSteps128,
        locoDecoderSpeedStepsUnknown,
    };

    /**
     * Locomotive direction.
     */
    enum locoDirection
    {
        locoDirectionForward = 0,
        locoDirectionBackward
    };

    /**
     * Light of locomotive.
     */
    enum locoLight
    {
        locoLightOn = 0,
        locoLightOff
    };

    /**
     * Structure with received locomotive data.
     */
    struct locoInfo
    {
        uint16_t Address;
        uint8_t Speed;
        locoDecoderSteps Steps;
        locoDirection Direction;
        locoLight Light;
        uint32_t Functions;
        bool Occupied;
    };

    /* Constructor */
    WmcTft();

    /**
     *  Init the display functions.
     */
    void Init(void);

    /**
     * Show version info.
     */
    void ShowVersion(uint8_t SwMajor, uint8_t SwMinor, uint8_t SwPatch);

    /**
     * Show info
     */
    void ShowName(void);

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
    void UpdateLocInfo(locoInfo* locInfoRcvPtr, locoInfo* locInfoActPtr, uint8_t* assignedFunctions, bool updateAll);

    /**
     * Show | or - as indicating waiting on something.
     */
    void UpdateRunningWheel(uint8_t count);

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
     * Show screen to uodate XpNet address.
     */
    void ShowXpNetAddress(uint16_t Address);

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

    /**
     * Show address of loc for POM mode.
     */
    void ShowPomAddress(uint16_t Address, bool Init);

    /**
     * Show cv number.
     */
    void ShowDccNumber(uint16_t CvNUmber, bool Update, bool PomActive);

    /**
     * Show cv number.
     */
    void ShowDccValue(uint16_t CvValue, bool Init, bool PomActive);

    /**
     * Delete showing cv number.
     */
    void ShowDccValueRemove(bool PomActive);

    /**
     * Delete showing CV value.
     */
    void ShowDccNumberRemove(bool PomActive);

private:
    /**
     * Convert color enum to display value.
     */
    uint16_t getColor(color Clr);
};

#endif
