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

#define STATUSBAR_HEIGHT  25
#define STATUSBAR_MARGIN  5

// aditional colors                 // http://www.rinkydinkelectronics.com/calc_rgb565.php
#define TFT_DARKBLUE      0x0008
#define TFT_RED2          0xFB2C

#define COLOR_STATUSBAR   0x3186  // #333333



#define FONT0     0
#define FONT1     1
#define FONT2     2
#define FONT3     3
#define FONT4     4
#define FONT1_B   11
#define FONT2_B   21
#define FONT3_B   31
#define FONT4_B   41

#define LANG_EN                     0
#define LANG_GER                    1
#define LANG                        LANG_GER

#if LANG == LANG_GER
    #define TXT_WIFI_CONFIG_MODE1  "WiFi Config Mode"
    #define TXT_WIFI_CONFIG_MODE2  "is active."
    #define TXT_WIFI_CONFIG_MODE3  "Please connect"
    #define TXT_WIFI_CONFIG_MODE4  "to WiFi SSID:"
#else
    #define TXT_WIFI_CONFIG_MODE1  "Der WiFi Config"
    #define TXT_WIFI_CONFIG_MODE2  "ist active."
    #define TXT_WIFI_CONFIG_MODE3  "Bitte per WLAN mit"
    #define TXT_WIFI_CONFIG_MODE4  "dieser SSID verbinden:"
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

    /**
     * Show version info.
     */
    void ShowVersion(uint16_t SwMajor, uint8_t SwMinor, uint8_t SwPatch);

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
    void UpdateStatus(const char* StrPtr, bool clearRowFull, color textColor);

    /**
     * Show IP address where to WMC tries to conenct to.
     */
    void ShowIpAddressToConnectTo(const char* IpStr);

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
     * Show | or - as indicating waiting on something.
     */
    void UpdateRunningWheel();

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
     * Display first menu.
     */
    void ShowMenu(bool emergencyStop);

    /**
     * Display erase.
     */
    void ShowErase();

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

private:
    /**
     * Convert color enum to display value.
     */
    uint16_t getColor(color Clr);
};

#endif
