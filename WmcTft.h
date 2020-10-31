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
#include <TFT_eSPI.h>
#include <User_Setup.h>

#ifdef LOAD_GFXFF
// Fonts
#define MONO9     &FreeMono9pt7b
#define MONO12    &FreeMono12pt7b
#define MONO18    &FreeMono18pt7b
#define MONO24    &FreeMono24pt7b

#define MONO9_B   &FreeMonoBold9pt7b
#define MONO12_B  &FreeMonoBold12pt7b
#define MONO18_B  &FreeMonoBold18pt7b
#define MONO24_B  &FreeMonoBold24pt7b

#define SANS9C    &Open_Sans_Condensed_Light_9Bitmaps
#define SANS9     &FreeSans9pt7b
#define SANS12    &FreeSans12pt7b
#define SANS18    &FreeSans18pt7b
#define SANS24    &FreeSans24pt7b

#define SANS9_B   &FreeSansBold9pt7b
#define SANS12_B  &FreeSansBold12pt7b
#define SANS18_B  &FreeSansBold18pt7b
#define SANS24_B  &FreeSansBold24pt7b
#endif

#define FUNCTION_BUTTON_SIZE  25
#define STATUSBAR_HEIGHT      25
#define STATUSBAR_MARGIN      5

// aditional colors                 // http://www.rinkydinkelectronics.com/calc_rgb565.php
#define TFT_DARKBLUE          0x0008
#define TFT_RED2              0xFC10

#define COLOR_STATUSBAR       0x3186  // #333333

#define FONT0     0
#define FONT1     1
#define FONT2     2
#define FONT3     3
#define FONT4     4
#define FONT1_B   11
#define FONT2_B   21
#define FONT3_B   31
#define FONT4_B   41

#define LANG_EN                        0
#define LANG_GER                       1

#define LANG                           LANG_EN

/**
 * Text strings for LCD texts.
 * Note: The order must be the same as in enum lcdTextStringIndex below.
 */
#if LANG == LANG_EN
    PGM_P const lcdTextStrings[] PROGMEM = {
        #if APP_CFG_UC == APP_CFG_UC_ESP8266
            "WIFI",
        #else
            "XMC",
        #endif
        "MANUAL",
        "CONTROL II",

        "WiFi Config Mode",
        "is active.",
        "Please connect",
        "to WiFi SSID:",

        "Connecting to WLAN",
        "Connecting to Central",
        "POWER ON",
        "POWER OFF",
        "Receiving",
        "Sorting",
        "Program mode",
        "Turnout",
        "Add Loc",
        "Functions",
        "Change Function",
        "Delete",
        "Send Loc data",
        "Command line",
        "CV Programming",
        "POM Programming",
        "Settings",
        "WRITING CV",
        "READING CV",

        "Confirmation",
        "The WiFi settings are",
        "All locomotives are",
        "All settings are",
        "deleted. Continue?",
        "OK (9)  -  Cancel (0)",

        "1  Add Loc",
        "2  Change Loc",
        "3  Delete Loc",
        "4  CV Programming",
        "5  POM Programming",
        "6  STOP",
        "6  Emergency STOP",
        "7  Transmit",
        "8  Delete Locs",
        #if APP_CFG_UC == APP_CFG_UC_STM32
            "9  Delete WiFi Settings",
        #else
            "9  XPNET",
        #endif
        "0  Delete ALL",

        "Erasing WiFi settings ...",
        "Erasing all locomotives ...",
        "Erasing all settings ...",

        "Reset or",
        "power off and on",
        "to continue",

        "Power off",
        "Please release key!",

        "Firmware update",
        "Progress:",
        "Waiting for completion ...",
        "Error: ",
        "Auth Failed",
        "Begin Failed",
        "Connect Failed",
        "Receive Failed",
        "End Failed",
};
#else
    // ToDo: German translation
    PGM_P const lcdTextStrings[] PROGMEM = {
    }
#endif

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
     * Enum for lcd text strings. Note: The order must be the same as in lcdTextStrings defination.
     */
    enum lcdTextStringIndex
    {
        txtAppName_Line1,
        txtAppName_Line2,
        txtAppName_Line3,

        txtWifi_configModeLine1,
        txtWifi_configModeLine2,
        txtWifi_configModeLine3,
        txtWifi_configModeLine4,

        txtStatus_wifiConnect,
        txtStatus_z21Connect,
        txtStatus_powerOn,
        txtStatus_powerOff,
        txtStatus_receiving,
        txtStatus_sorting,
        txtStatus_programMode,
        txtStatus_turnout,
        txtStatus_addLoc,
        txtStatus_functions,
        txtStatus_changeFunction,
        txtStatus_statusDelete,
        txtStatus_sendLocData,
        txtStatus_commandLine,
        txtStatus_cvProgramming,
        txtStatus_pomProgramming,
        txtStatus_settings,
        txtStatus_writingCV,
        txtStatus_readingCV,

        txtConfirmation_line1,
        txtConfirmation_line2_wifi,
        txtConfirmation_line2_locs,
        txtConfirmation_line2_settings,
        txtConfirmation_line3,
        txtConfirmation_line4,

        txtMenu_addLoc,
        txtMenu_changeLoc,
        txtMenu_deleteLoc,
        txtMenu_cvPgm,
        txtMenu_pomPgm,
        txtMenu_stop,
        txtMenu_stopEmergency,
        txtMenu_transmit,
        txtMenu_delAllLocs,
        txtMenu_delWifi_XpNet,
        txtMenu_delSettings,

        txtEraseing_wifi,
        txtEraseing_locs,
        txtEraseing_settings,

        txtComandline_line1,
        txtComandline_line2,
        txtComandline_line3,

        txtPowerOff_line1,
        txtPowerOff_line2,

        txtOtaUpdate_line1,
        txtOtaUpdate_line2,
        txtOtaUpdate_line3,
        txtOtaUpdate_Error,
        txtOtaUpdate_Error0,
        txtOtaUpdate_Error1,
        txtOtaUpdate_Error2,
        txtOtaUpdate_Error3,
        txtOtaUpdate_Error4,
    };

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

    uint8_t runningWheel = 0;

    /**
     *  Init the display functions.
     */
    void Init(void);

    void Grid(void);

    void drawTextMultiline(uint8_t textIndexFrom, uint8_t textIndexTo, uint8_t lineHeight, uint8_t posLeft, uint8_t posTop, uint8_t textDatum, uint16_t color, uint8_t font, bool clear);

    void drawText(const char* string, uint8_t x, uint8_t y, uint8_t textDatum, uint16_t color, uint8_t font);

    /**
     * Show version info.
     */
    void ShowVersion(uint16_t SwMajor, uint8_t SwMinor, uint8_t SwPatch, const char *compileTime);

    /**
     * Show info
     */
    void ShowName(void);

    void ShowWifiConfigMode();

    /**
     * Clear the display.,
     */
    void Clear();

    /**
     * Update the status left up in the sreen.
     */
    void UpdateStatus(lcdTextStringIndex index, bool clearRowFull, color textColor);
    void UpdateStatus(String index, bool clearRowFull, color textColor);
    void UpdateStatusBattery(String txt);
    void UpdateStatusWifi(sint8 rssiPercent);
    void UpdateStatusZ21(uint8_t state);
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
        locoInfo* locInfoRcvPtr, locoInfo* locInfoActPtr, uint8_t* assignedFunctions, char* LocName, bool updateAll);

    /**
     * Shoe transmitted loc number count when transmitting loc database
     */
    void UpdateTransmitCount(uint8_t count, uint8_t totalCount);

    /**
     * Error message when connecting to Wifi failed.
     */
    void WifiConnectFailed();

    /**
     * Error message when connecting to Z21 control unit failed.
     */
    void UdpConnectFailed();

    /**
     * Show a confirmation message.
     */
    void ShowConfirmation(uint8_t confirmationType);

    /**
     * Display first menu.
     */
    void ShowMenu(bool emergencyStop);

    /**
     * Display erase.
     */
    void ShowErase(uint8_t eraseType);

    /**
     * Show initial turnout screen.
     */
    void ShowTurnoutScreen();

    /**
     * Show turnout address
     */
    void ShowTurnoutAddress(uint16_t address);

    /**
     * Show loc address.
     */
    void ShowlocAddress(uint16_t address, color textColor);

    /**
     * Show loc speed
     */
    void ShowlocSpeed(uint8_t Speed);

    /**
     * Enable or disable the light symbol.
     */
    void ShowLampStatus(locoLight Light);

    /**
     * Draw a fucntion symbol
     */
    void ShowFunction(uint32_t Functions, uint8_t Function, uint8_t Location);

    /**
     * Show name of loc (when present)
     */
    void ShowlocName(char* NamePtr, color textColor);

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
     * Show loc symbol
     *
     * @param[in] locSymbolColor
     * @param[in] direction (1 = forward, 0 = backward
     */
    void ShowLocSymbol(color locSymbolColor, uint8_t direction);

    void ShowTurnoutSymbol(uint8_t direction);

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
    void ShowPomAddress(uint16_t Address, bool Init, color Clr);

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

    void ShowPowerOffMessage(void);

    void ShowFirmwareUpdateMessage(uint8_t updateState, uint8_t progress);

private:
    /**
     * Convert color enum to display value.
     */
    uint16_t getColor(color Clr);
};

#endif
