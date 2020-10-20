/**
 * Functions to show data on the display of the Wmc application.
 */

// include this library's description file
#include "WmcTft.h"
#include <TFT_eSPI.h>
#include "app_cfg.h"
#include <string.h>
#include "WmcBitmaps.h"

// These pins will also work for the 1.8" TFT shield
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

/***********************************************************************************************************************
 */
void WmcTft::Init(void)
{
	// initialize TFT display
	tft.init();
	Clear();
	tft.setRotation(2);

    tft.setTextWrap(false);
#if APP_CFG_UC == APP_CFG_UC_STM32
    ShowName();
#endif
}

/**
 * Wrapper to write text and set position, set text alignment, text color and font
 */
void drawText (const char* string, int32_t x, int32_t y, uint8_t textDatum, uint16_t color, uint8_t font)
{
    if (font == FONT0) {
        tft.setFreeFont(MONO9);
    } else if (font == FONT1) {
        tft.setFreeFont(SANS9);
    } else if (font == FONT1_B) {
        tft.setFreeFont(SANS9_B);
    } else if (font == FONT2) {
        tft.setFreeFont(SANS12);
    } else if (font == FONT2_B) {
        tft.setFreeFont(SANS12_B);
    } else if (font == FONT3) {
        tft.setFreeFont(SANS18);
    } else if (font == FONT3_B) {
        tft.setFreeFont(SANS18_B);
    } else if (font == FONT4) {
        tft.setFreeFont(SANS24);
    } else if (font == FONT4_B) {
        tft.setFreeFont(SANS24_B);
    }

    tft.setTextColor(color);
    tft.setTextDatum(textDatum);
    tft.drawString(string, x, y);
}

void WmcTft::Grid() {
    for (uint8_t i = 10; i < 240; i=i+10) {
        tft.drawFastHLine(0, i, 240, TFT_YELLOW);
    }

    for (uint8_t i = 10; i < 240; i=i+10) {
        tft.drawFastVLine(i, 0, 240, TFT_YELLOW);
    }
}

/***********************************************************************************************************************
 * Show version of firmware at startup screen
 */
void WmcTft::ShowVersion(uint16_t SwMajor, uint8_t SwMinor, uint8_t SwPatch)
{
    char VersionStr[10];

    if (SwPatch != 99)
    {
        snprintf(VersionStr, sizeof(VersionStr), "%02hu.%02hu.%02hu", SwMajor, SwMinor, SwPatch);
    }
    else
    {
        snprintf(VersionStr, sizeof(VersionStr), " %04hu", SwMajor);
    }

    drawText(VersionStr, TFT_WIDTH/2, TFT_HEIGHT/2+40, MC_DATUM, TFT_GREEN, FONT1);
}

/***********************************************************************************************************************
 * Display the name of the firmware on the start screen
 */
void WmcTft::ShowName(void)
{
    Clear();
#if APP_CFG_UC == APP_CFG_UC_ESP8266
    drawText("WIFI", TFT_WIDTH/2, TFT_HEIGHT/2-50, MC_DATUM, TFT_GREEN, FONT2_B);
#else
    drawText("XMC", TFT_WIDTH/2, TFT_HEIGHT/2-50, MC_DATUM, TFT_GREEN, FONT2_B);
#endif

    drawText("MANUAL", TFT_WIDTH/2, TFT_HEIGHT/2-20, MC_DATUM, TFT_GREEN, FONT2_B);
    drawText("CONTROL", TFT_WIDTH/2, TFT_HEIGHT/2+10, MC_DATUM, TFT_GREEN, FONT2_B);
}

#if APP_CFG_UC == APP_CFG_UC_ESP8266
/***********************************************************************************************************************
 * Notification screen if WiFi config mode (AccessPoint mode) is active
 */
void WmcTft::ShowWifiConfigMode()
{
	Init();
  String ssid = DEVICE_NAME_PREFIX + String(ESP.getChipId());

  drawText(TXT_WIFI_CONFIG_MODE1, TFT_WIDTH/2, TFT_HEIGHT/2-70, MC_DATUM, TFT_YELLOW, FONT2_B);
  drawText(TXT_WIFI_CONFIG_MODE2, TFT_WIDTH/2, TFT_HEIGHT/2-40, MC_DATUM, TFT_YELLOW, FONT2_B);
  drawText(TXT_WIFI_CONFIG_MODE3, TFT_WIDTH/2, TFT_HEIGHT/2, MC_DATUM, TFT_YELLOW, FONT2);
  drawText(TXT_WIFI_CONFIG_MODE4, TFT_WIDTH/2, TFT_HEIGHT/2+30, MC_DATUM, TFT_YELLOW, FONT2);
  drawText(ssid.c_str(), TFT_WIDTH/2, TFT_HEIGHT/2+70, MC_DATUM, TFT_YELLOW, FONT2_B);
}
#endif

/***********************************************************************************************************************
 * Clear the whole screen
 */
void WmcTft::Clear(void) { tft.fillScreen(TFT_BLACK); }

/***********************************************************************************************************************
 * Update the top status bar
 */
void WmcTft::UpdateStatus(const char* StrPtr, bool clearRowFull, color textColor)
{
    uint16_t Color;
    Color = getColor(textColor);
    tft.fillRect(0, 0, (clearRowFull ? TFT_WIDTH : TFT_WIDTH-65), STATUSBAR_HEIGHT, COLOR_STATUSBAR);
    drawText(StrPtr, STATUSBAR_MARGIN, STATUSBAR_MARGIN, TL_DATUM, Color, FONT1);
}

/***********************************************************************************************************************
 * Show IP address of Z21 Central Station after WiFi Connect at second to status bar.
 */
void WmcTft::ShowIpAddressToConnectTo(const char* IpStr)
{
    tft.fillRect(0, STATUSBAR_HEIGHT, TFT_WIDTH, STATUSBAR_HEIGHT, COLOR_STATUSBAR);
    drawText(IpStr, TFT_WIDTH/2, STATUSBAR_HEIGHT + STATUSBAR_MARGIN, TC_DATUM, TFT_YELLOW, FONT1);
}

/***********************************************************************************************************************
 * Show WiFi SSID to connect at the start screen at second to status bar.
 */
void WmcTft::ShowNetworkName(const char* StrPtr)
{
    tft.fillRect(0, STATUSBAR_HEIGHT, TFT_WIDTH, STATUSBAR_HEIGHT, COLOR_STATUSBAR);
    drawText(StrPtr, TFT_WIDTH/2, STATUSBAR_HEIGHT + STATUSBAR_MARGIN, TC_DATUM, TFT_YELLOW, FONT1);
}

/***********************************************************************************************************************
 * Display number of loc in top stytus bar (<currentLocIndex>/<maxLocCount>)
 * Sample: (1/23)
 */
void WmcTft::UpdateSelectedAndNumberOfLocs(uint8_t actualLocIndex, uint8_t NumberOfLocs)
{
    char buffer[9];
    tft.fillRect(176, 0, 128, STATUSBAR_HEIGHT, COLOR_STATUSBAR);

    snprintf(buffer, sizeof(buffer), "(%u/%u)", actualLocIndex, NumberOfLocs);
    drawText(String(buffer).c_str(), TFT_WIDTH-STATUSBAR_MARGIN, STATUSBAR_MARGIN, TR_DATUM, TFT_WHITE, FONT1);
}

/***********************************************************************************************************************
 * Update loc information on screen
 */
void WmcTft::UpdateLocInfo(locoInfo* locInfoRcvPtr, locoInfo* locInfoActPtr, uint8_t* assignedFunctions, char* LocName, bool updateAll)
{
    uint8_t Index    = 0;
    uint8_t Function = 0;

    if ((updateAll == true) || (locInfoRcvPtr->Direction != locInfoActPtr->Direction)
        || (locInfoRcvPtr->Occupied != locInfoActPtr->Occupied))
    {
        color locSymbolColor = (locInfoRcvPtr->Occupied == false) ? color_white : color_yellow;
        ShowLocSymbol(locSymbolColor, (locInfoRcvPtr->Direction == locoDirectionForward));
    }

    if ((updateAll == true) || (locInfoRcvPtr->Address != locInfoActPtr->Address))
    {
        /* Show address and locname. */
        ShowlocAddress(locInfoRcvPtr->Address, WmcTft::color_green);
        ShowlocName(LocName, WmcTft::color_green);
    }

    if ((updateAll == true) || (locInfoRcvPtr->Steps != locInfoActPtr->Steps))
    {
        switch (locInfoRcvPtr->Steps)
        {
        case locoDecoderSpeedSteps14: ShowLocDecoderSteps(14); break;
        case locoDecoderSpeedSteps28: ShowLocDecoderSteps(28); break;
        case locoDecoderSpeedSteps128: ShowLocDecoderSteps(128); break;
        case locoDecoderSpeedStepsUnknown: ShowLocDecoderSteps(28); break;
        }
    }

    /* Update speed. */
    if ((updateAll == true) || (locInfoRcvPtr->Speed != locInfoActPtr->Speed))
    {
        /* Show Speed. */
        ShowlocSpeed(locInfoRcvPtr->Speed);
    }

    /* Show light symbol (or not) depending on light status. */
    if ((updateAll == true) || (locInfoRcvPtr->Light != locInfoActPtr->Light))
    {
        ShowLampStatus(locInfoRcvPtr->Light);
    }

    for (Index = 0; Index < MAX_FUNCTION_BUTTONS; Index++)
    {
        Function = assignedFunctions[Index];
        if ((updateAll == true)
            || (((locInfoRcvPtr->Functions & (1 << (Function - 1)))
                   != (locInfoActPtr->Functions & (1 << (Function - 1))))))
        {
            ShowFunction(locInfoRcvPtr->Functions, Function, Index);
        }
    }
}

/***********************************************************************************************************************
 * Displays spinner while waiting for connection to the Z21 central unit.
 */
void WmcTft::UpdateRunningWheel()
{
    WmcTft::runningWheel ++;
    String w;

    if (runningWheel == 1) {
        w = "/";
    } else if (runningWheel == 2) {
        w = "-";
    } else if (runningWheel == 3) {
        w = "\\";
    } else {
        w = "| ";
        runningWheel = 0;
    }

    tft.fillRect(TFT_WIDTH-20, 0, TFT_WIDTH, STATUSBAR_HEIGHT, COLOR_STATUSBAR);
    drawText(w.c_str(), TFT_WIDTH-10, STATUSBAR_MARGIN, TC_DATUM, TFT_YELLOW, FONT0);
}

/***********************************************************************************************************************
 * ToDo
 */
void WmcTft::UpdateTransmitCount(uint8_t count, uint8_t totalCount)
{
    tft.fillRect(195, 5, 240, 25, TFT_YELLOW);
    drawText(String(count).c_str(), 195, 150, TL_DATUM, TFT_GREEN, FONT1);
}

/***********************************************************************************************************************
 * Display error message if connection to the Z21 Central Unit can not established.
 */
void WmcTft::UdpConnectFailed()
{
    Clear();
    drawText("Connection to", TFT_WIDTH/2, TFT_HEIGHT/2-30, MC_DATUM, TFT_RED, FONT2_B);
    drawText("Controll Unit", TFT_WIDTH/2, TFT_HEIGHT/2, MC_DATUM, TFT_RED, FONT2_B);
    drawText("(Z21) failed.", TFT_WIDTH/2, TFT_HEIGHT/2+30, MC_DATUM, TFT_RED, FONT2_B);
}

/**
 * Show a confirmation message
 */
void WmcTft::ShowConfirmation(uint8_t confirmationType)
{
    String textLine1 = "";
    if (confirmationType == 1) {
        textLine1 = "The WiFi settings are";
    } else if (confirmationType == 2) {
        textLine1 = "All locomotives are";
    } else if (confirmationType == 3) {
        textLine1 = "All settings are";
    }

    Clear();
    drawText("Confirmation:", TFT_WIDTH/2, TFT_HEIGHT/2-70, MC_DATUM, TFT_YELLOW, FONT1_B);
    drawText(textLine1.c_str(), TFT_WIDTH/2, TFT_HEIGHT/2-30, MC_DATUM, TFT_YELLOW, FONT1);
    drawText("deleted. Continue?", TFT_WIDTH/2, TFT_HEIGHT/2-5, MC_DATUM, TFT_YELLOW, FONT1);
    drawText("OK (1)  -  Cancel (2)", TFT_WIDTH/2, TFT_HEIGHT/2+35, MC_DATUM, TFT_YELLOW, FONT1_B);
}

/***********************************************************************************************************************
 * ToDo
 */
void WmcTft::ShowMenu(bool emergencyStop)
{
    Clear();
    UpdateStatus("Settings", true, WmcTft::color_green);
    drawText("1  Add Loc",              0, 30,  TL_DATUM, TFT_GREEN, FONT1);
    drawText("2  Change Loc",           0, 50,  TL_DATUM, TFT_GREEN, FONT1);
    drawText("3  Delete Loc",           0, 70,  TL_DATUM, TFT_GREEN, FONT1);
    drawText("4  CV Programming",       0, 90,  TL_DATUM, TFT_GREEN, FONT1);
    drawText("5  POM Programming",      0, 110, TL_DATUM, TFT_GREEN, FONT1);

    if (emergencyStop == true) {
        drawText("6  Emergency STOP",   0, 130, TL_DATUM, TFT_GREEN, FONT1);
    } else {
        drawText("6  STOP",             0, 130, TL_DATUM, TFT_GREEN, FONT1);
    }
    drawText("7  Transmit",             0, 150, TL_DATUM, TFT_GREEN, FONT1);
    drawText("8  Delete Locs",          0, 170, TL_DATUM, TFT_GREEN, FONT1);

#if APP_CFG_UC == APP_CFG_UC_STM32
    drawText("9  XPNET",                0, 190, TL_DATUM, TFT_GREEN, FONT1);
#else
    drawText("9  Delete WiFi Settings", 0, 190, TL_DATUM, TFT_GREEN, FONT1);
#endif

    drawText("0  Delete ALL",           0, 210, TL_DATUM, TFT_GREEN, FONT1);
}

/***********************************************************************************************************************
 * ToDo
*/
void WmcTft::ShowErase(uint8_t eraseType)
{
    Clear();

    String textLine1 = "Erasing ";
    if (eraseType == 1) {
        textLine1 += "WiFi settings";
    } else if (eraseType == 2) {
        textLine1 += "all locomotives";
    } else if (eraseType == 2) {
        textLine1 += "all settings";
    }
    textLine1 += " ...";

    drawText(textLine1.c_str(), TFT_WIDTH/2, TFT_HEIGHT/2, MC_DATUM, TFT_YELLOW, FONT1);
}

/***********************************************************************************************************************
 * ToDo
*/
void WmcTft::ShowTurnoutScreen()
{
    UpdateStatus("TURNOUT", true, WmcTft::color_green);

    tft.drawBitmap(85, 20, TurnoutBitmap, 28, 28, TFT_BLACK, TFT_WHITE);
}

/***********************************************************************************************************************
 * ToDo
 */
void WmcTft::ShowTurnoutAddress(uint16_t address)
{
    tft.fillRect(10, 22, 70, 30, TFT_BLACK);
    tft.setCursor(10, 22);
    tft.setTextColor(TFT_GREEN);
    tft.setFreeFont(SANS24);
    tft.print(address);
}

/***********************************************************************************************************************
 * ToDo:
 */
void WmcTft::ShowTurnoutDirection(uint8_t direction)
{
    switch (direction)
    {
    case 0: tft.drawBitmap(85, 20, TurnoutBitmap, 28, 28, TFT_BLACK, TFT_WHITE); break;
    case 1: tft.drawBitmap(85, 20, TurnoutForwardBitmap, 28, 28, TFT_BLACK, TFT_WHITE); break;
    case 2: tft.drawBitmap(85, 20, TurnoutLeftBitmap, 28, 28, TFT_BLACK, TFT_WHITE); break;
    default: tft.drawBitmap(85, 20, TurnoutBitmap, 28, 28, TFT_BLACK, TFT_WHITE); break;
    }
}

/***********************************************************************************************************************
 */
void WmcTft::ShowlocAddress(uint16_t address, color textColor)
{
    uint16_t Color = getColor(textColor);
    tft.fillRect(0, 110, 70, 25, TFT_BLACK);
    drawText(String(address).c_str(), 50, 110, TR_DATUM, Color, FONT2);

}

/***********************************************************************************************************************
 * Show current speed of the selected loc
 */
void WmcTft::ShowlocSpeed(uint8_t Speed)
{
    tft.fillRect(TFT_WIDTH-95, 150, 55, 40, TFT_BLACK);
    drawText(String(Speed).c_str(), TFT_WIDTH-45, 195, BR_DATUM, TFT_WHITE, FONT4);
}

/***********************************************************************************************************************
 * Display Light icon (Function 0)
 */
void WmcTft::ShowLampStatus(locoLight Light)
{
    tft.drawBitmap(10, 155, bulbBitmapOn, 28, 28, TFT_BLACK, (Light == locoLightOn) ? TFT_WHITE : TFT_DARKGREY);
}

/**
 * Paint function indicator boxes at bottom of display.
 *
 * @param[in] Functions:  function states of the loc
 * @param[in] Function:   function number assigned to function location
 * @param[in] Location:   location index (1 - 9), location 0 would be light and is ignored here
 */
void WmcTft::ShowFunction(uint32_t Functions, uint8_t Function, uint8_t Location)
{
    if (Function != 0)
    {
        Location--;
        tft.setFreeFont(SANS9);
        tft.setTextColor(TFT_BLACK);

        uint8_t boxSize = FUNCTION_BUTTON_SIZE;
        uint8_t boxSpace = 1;
        uint8_t marginLeft = 2;
        uint8_t lineStart = TFT_HEIGHT - boxSize;

        uint8_t lineStartText = TFT_HEIGHT - boxSize + boxSize/2 - 1;
        uint8_t colStartText = marginLeft + (boxSize / 2) + (Location * boxSize) + (boxSpace * Location);

        uint32_t backGround = ((Functions & (1 << (Function - 1))) == (uint32_t)((1 << (Function - 1)))) ? TFT_GREEN : TFT_WHITE;
        tft.fillRect((Location * boxSize) + (boxSpace * Location) + marginLeft, lineStart, boxSize, boxSize, backGround);

        drawText(String(Function).c_str(), colStartText, lineStartText, MC_DATUM, TFT_BLACK, FONT2);
    }
}

/***********************************************************************************************************************
 */
void WmcTft::ShowlocName(char* NamePtr, color textColor)
{
    tft.fillRect(70, 110, TFT_WIDTH-70, 25, TFT_BLACK);

    // Only print name when string has data.
    if (NamePtr != NULL)
    {
        uint16_t color = getColor(textColor);
        drawText(NamePtr, 70, 110, TL_DATUM, color, FONT2);
    }
}

/***********************************************************************************************************************
 */
void WmcTft::ShowLocDecoderSteps(uint8_t Steps)
{
    tft.fillRect(TFT_WIDTH-40, 150, 30, 40, TFT_BLACK);
    String txt = "/ " + String(Steps);
    drawText(txt.c_str(), TFT_WIDTH-35, 190, BL_DATUM, TFT_WHITE, FONT1);
}

/***********************************************************************************************************************
 * ToDo: Remove?
 */
void WmcTft::ShowXpNetAddress(uint16_t Address)
{
    tft.fillRect(10, 22, 70, 30, TFT_BLACK);
    tft.setCursor(10, 22);
    tft.setTextColor(TFT_GREEN);
    tft.setFreeFont(SANS24);
    tft.print(Address);
}

/***********************************************************************************************************************
 * ToDo: Was macht diese Funktion?
 */
void WmcTft::FunctionAddSet()
{
    uint8_t Index;
    tft.setCursor(10, 52);
    tft.setTextColor(TFT_GREEN);
    tft.setFreeFont(SANS24);
    tft.print(0);

    tft.setTextColor(TFT_BLACK);
    tft.setFreeFont(SANS9);

    for (Index = 0; Index < MAX_FUNCTION_BUTTONS; Index++)
    {
        tft.drawBitmap(9 + (Index * 23), 100, FuntionBackgroundBitmap, 20, 20, TFT_BLACK, TFT_GREEN);
        tft.setCursor(17 + (Index * 23), 107);
        tft.print(Index);
    }
    tft.drawBitmap(80, 50, bulbBitmapOn, 28, 28, TFT_BLACK, TFT_WHITE);
}

/***********************************************************************************************************************
 * Show loc symbol
 *
 * @param[in] locSymbolColor
 * @param[in] direction (1 = forward, 0 = backward
 */
void WmcTft::ShowLocSymbol(color locSymbolColor, uint8_t direction) {
    uint8_t locTop = 50;
    uint8_t locHeight = 45;
    uint8_t locWidth = 170;

    uint16_t locColor = getColor(locSymbolColor);

    uint16_t triangleColorLeft  =  direction ? TFT_DARKGREY : TFT_GREEN;
    uint16_t triangleColorRight = !direction ? TFT_DARKGREY : TFT_GREEN;

    // arrow left
    tft.fillTriangle(25, locTop           , 15, locTop            , 15, locTop+locHeight/2, triangleColorLeft);
    tft.fillTriangle(15, locTop           ,  5, locTop+locHeight/2, 15, locTop+locHeight  , triangleColorLeft);
    tft.fillTriangle(15, locTop+locHeight , 25, locTop+locHeight  , 15, locTop+locHeight/2, triangleColorLeft);

    // arrow Right
    tft.fillTriangle(215, locTop          , 225, locTop            , 225, locTop+locHeight/2, triangleColorRight);
    tft.fillTriangle(225, locTop          , 235, locTop+locHeight/2, 225, locTop+locHeight  , triangleColorRight);
    tft.fillTriangle(225, locTop+locHeight, 215, locTop+locHeight  , 225, locTop+locHeight/2, triangleColorRight);

    tft.drawBitmap((TFT_WIDTH-locWidth)/2, locTop, locoBW, locWidth, locHeight, TFT_BLACK, locColor);
}

/***********************************************************************************************************************
 * ToDo
 */
void WmcTft::FunctionAddUpdate(uint16_t function)
{
    tft.fillRect(10, 50, 75, 25, TFT_BLACK);
    tft.setCursor(10, 52);
    tft.setTextColor(TFT_GREEN);
    tft.setFreeFont(SANS24);
    tft.print(function);
}

/***********************************************************************************************************************
 * ToDo: Was macht diese Funktion?
 */
void WmcTft::UpdateFunction(uint8_t Index, uint8_t Function)
{
    tft.setTextColor(TFT_BLACK);
    tft.setFreeFont(SANS9);

    if ((Index == 0) && (Function == 0))
    {
        tft.drawBitmap(80, 50, bulbBitmapOn, 28, 28, TFT_BLACK, TFT_WHITE);
        tft.fillRect(9, 100, 21, 21, 0);
    }
    else
    {
        if (Index == 0)
        {
            tft.fillRect(80, 50, 28, 28, 0);
        }
        tft.drawBitmap(9 + (Index * 23), 100, FuntionBackgroundBitmap, 20, 20, TFT_BLACK, TFT_GREEN);

        if (Function < 10)
        {
            tft.setCursor(17 + (Index * 23), 107);
        }
        else if (Function < 20)
        {
            tft.setCursor(13 + (Index * 23), 107);
        }
        else
        {
            tft.setCursor(12 + (Index * 23), 107);
        }
        tft.print(Function);
    }
}

/***********************************************************************************************************************
 * Show screen to request ar reset or power cycle
 */
void WmcTft::CommandLine(void)
{
    drawText("Reset or",         TFT_WIDTH/2, TFT_HEIGHT/2-25, MC_DATUM, TFT_YELLOW, FONT2);
    drawText("power off and on", TFT_WIDTH/2, TFT_HEIGHT/2, MC_DATUM, TFT_YELLOW, FONT2);
    drawText("to continue",      TFT_WIDTH/2, TFT_HEIGHT/2+25, MC_DATUM, TFT_YELLOW, FONT2);
}

/***********************************************************************************************************************
 */
uint16_t WmcTft::getColor(color Clr)
{
    uint16_t ColorReturn;
    switch (Clr)
    {
    case color_red: ColorReturn = TFT_RED; break;
    case color_green: ColorReturn = TFT_GREEN; break;
    case color_yellow: ColorReturn = TFT_YELLOW; break;
    case color_white: ColorReturn = TFT_WHITE; break;
    default: ColorReturn = TFT_RED; break;
    }

    return (ColorReturn);
}

/***********************************************************************************************************************
 * ToDo
 */
void WmcTft::ShowPomAddress(uint16_t Address, bool Init, color Clr)
{
    if (Init == true)
    {
        tft.setCursor(5, 20);
        tft.setTextColor(TFT_YELLOW);
        tft.setFreeFont(SANS9);
        tft.print("POM loc address");
    }

    tft.fillRect(60, 30, 68, 30, TFT_BLACK);
    tft.setCursor(60, 30);
    tft.setTextColor(getColor(Clr));
    tft.setFreeFont(SANS24);
    tft.print(Address);
}

/***********************************************************************************************************************
 * ToDo
 */
void WmcTft::ShowDccNumber(uint16_t CvNUmber, bool Init, bool PomActive)
{
    if (Init == true)
    {
        if (PomActive == false)
        {
            tft.setCursor(5, 20);
        }
        else
        {
            tft.setCursor(5, 55);
        }
        tft.setTextColor(TFT_YELLOW);
        tft.setFreeFont(SANS9);
        tft.print("Cv number");
    }

    if (PomActive == false)
    {
        tft.fillRect(60, 30, 68, 30, TFT_BLACK);
        tft.setCursor(60, 33);
    }
    else
    {
        tft.fillRect(60, 65, 68, 30, TFT_BLACK);
        tft.setCursor(60, 65);
    }

    tft.setTextColor(TFT_GREEN);
    tft.setFreeFont(SANS24);
    tft.print(CvNUmber);
}

/***********************************************************************************************************************
 * ToDo
 */
void WmcTft::ShowDccValue(uint16_t CvValue, bool Init, bool PomActive)
{
    if (Init == true)
    {
        if (PomActive == false)
        {
            tft.setCursor(5, 55);
        }
        else
        {
            tft.setCursor(5, 90);
        }
        tft.setTextColor(TFT_YELLOW);
        tft.setFreeFont(SANS9);
        tft.print("CV value");
    }

    if (PomActive == false)
    {
        tft.fillRect(60, 65, 65, 30, TFT_BLACK);
        tft.setCursor(60, 65);
    }
    else
    {
        tft.fillRect(60, 100, 100, 30, TFT_BLACK);
        tft.setCursor(60, 100);
    }
    tft.setTextColor(TFT_GREEN);
    tft.setFreeFont(SANS24);
    tft.print(CvValue);
}

/***********************************************************************************************************************
 * ToDo
 */
void WmcTft::ShowDccValueRemove(bool PomActive)
{
    if (PomActive == false)
    {
        tft.fillRect(5, 55, 122, 38, TFT_BLACK);
    }
    else
    {
        tft.fillRect(5, 90, 122, 38, TFT_BLACK);
    }
}

/***********************************************************************************************************************
 * ToDo
 */
void WmcTft::ShowDccNumberRemove(bool PomActive)
{
    if (PomActive == false)
    {
        tft.fillRect(5, 20, 122, 38, TFT_BLACK);
    }
    else
    {
        tft.fillRect(5, 55, 122, 38, TFT_BLACK);
    }
}
