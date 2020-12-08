/**
 * Functions to show data on the display of the Wmc application.
 */

// include this library's description file
#include "WmcTft.h"
#include <TFT_eSPI.h>
#include "app_cfg.h"
#include <string.h>
#include "WmcBitmaps.h"

#define UNUSED(x) (void)(x)

// These pins will also work for the 1.8" TFT shield
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

/***********************************************************************************************************************
 */
void WmcTft::Init(void)
{
	// initialize TFT display
	tft.init();
	Clear(true);
	tft.setRotation(2);

    tft.setTextWrap(false);
#if APP_CFG_UC == APP_CFG_UC_STM32
    ShowName();
#endif

    menuItemStart = 0;
    menuItemStartOld = 0;
    menuSelected = 0;
    menuSelectedOld = 0;
}

void WmcTft::drawTextMultiline(uint8_t textIndexFrom, uint8_t textIndexTo, uint8_t lineHeight, uint8_t posLeft, uint8_t posTop, uint8_t textDatum, uint16_t color, uint8_t font, bool clear) {
    if (clear) {
        Clear(true);
    }

    for (uint8_t i = textIndexFrom; i <= textIndexTo; i++){
        drawText(lcdTextStrings[i], posLeft, posTop, textDatum, color, font);
        posTop += lineHeight;
    }
}

/**
 * Wrapper to write text and set position, set text alignment, text color and font
 */
void WmcTft::drawText(const char* string, uint8_t x, uint8_t y, uint8_t textDatum, uint16_t color, uint8_t font)
{
    if (font == FONT0) {
    } else if (font == FONT1) {
        tft.setFreeFont(SANS9);
    } else if (font == FONT2) {
        tft.setFreeFont(SANS12);
    } else if (font == FONT2_B) {
        tft.setFreeFont(SANS12_B);
    } else if (font == FONT3) {
        tft.setFreeFont(SANS18);
    } else if (font == FONT4) {
        tft.setFreeFont(SANS24);
    }

    tft.setTextColor(color);
    tft.setTextDatum(textDatum);
    tft.drawString(string, (uint32_t)x, (uint32_t)y);
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
void WmcTft::ShowVersion(uint16_t SwMajor, uint8_t SwMinor, uint8_t SwPatch, const char *compileTime)
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
    drawText(compileTime, TFT_WIDTH/2, TFT_HEIGHT/2+70, MC_DATUM, TFT_GREEN, FONT1);
}

/***********************************************************************************************************************
 * Display the name of the firmware on the start screen
 */
void WmcTft::ShowName(void)
{
    drawTextMultiline(txtAppName_Line1, txtAppName_Line3, 30, TFT_WIDTH/2, TFT_HEIGHT/2 - 50, MC_DATUM, TFT_GREEN, FONT2_B, true);
}

#if APP_CFG_UC == APP_CFG_UC_ESP8266
    /***********************************************************************************************************************
     * Notification screen if WiFi config mode (AccessPoint mode) is active
     */
    void WmcTft::ShowWifiConfigMode()
    {
      Init();
      String ssid = DEVICE_NAME_PREFIX + String(ESP.getChipId());

      drawTextMultiline(txtWifi_configModeLine2, txtWifi_configModeLine4, 30, TFT_WIDTH/2, TFT_HEIGHT/2-40, MC_DATUM, TFT_YELLOW, FONT2_B, true);
      drawText(lcdTextStrings[txtWifi_configModeLine1], TFT_WIDTH/2, TFT_HEIGHT/2-70, MC_DATUM, TFT_YELLOW, FONT2_B);
      drawText(ssid.c_str(), TFT_WIDTH/2, TFT_HEIGHT/2+60, MC_DATUM, TFT_YELLOW, FONT2_B);
    }
#endif

/***********************************************************************************************************************
 * Clear the whole screen
 */
void WmcTft::Clear(uint8_t withStatusBar) {
    tft.fillRect(0, (withStatusBar ? 0 : STATUSBAR_HEIGHT+1), TFT_WIDTH, TFT_HEIGHT, TFT_BLACK);
}

/***********************************************************************************************************************
 * Update the top status bar
 */
void WmcTft::UpdateStatus(lcdTextStringIndex index, bool clearRowFull, color textColor)
{
    uint16_t Color;
    Color = getColor(textColor);
    tft.fillRect(0, 0, (clearRowFull ? TFT_WIDTH : TFT_WIDTH-125), STATUSBAR_HEIGHT, COLOR_STATUSBAR);
    drawText(lcdTextStrings[index], STATUSBAR_MARGIN, STATUSBAR_MARGIN, TL_DATUM, Color, FONT1);
}

void WmcTft::UpdateStatus(String txt, bool clearRowFull, color textColor)
{
    uint16_t Color;
    Color = getColor(textColor);
    tft.fillRect(0, 0, (clearRowFull ? TFT_WIDTH : TFT_WIDTH-125), STATUSBAR_HEIGHT, COLOR_STATUSBAR);
    drawText(txt.c_str(), STATUSBAR_MARGIN, STATUSBAR_MARGIN, TL_DATUM, Color, FONT1);
}

#if APP_CFG_UC == APP_CFG_UC_ESP8266
    void WmcTft::UpdateStatusBattery(String txt)
    {
        tft.fillRect(TFT_WIDTH-65, 0, 65, STATUSBAR_HEIGHT, COLOR_STATUSBAR);
        tft.fillRect(TFT_WIDTH-9, 2, 4, 2, TFT_WHITE);
        tft.fillRect(TFT_WIDTH-12, 5, 10, 17, TFT_WHITE);

        drawText(txt.c_str(), TFT_WIDTH-18, STATUSBAR_MARGIN, TR_DATUM, TFT_WHITE, FONT1);
    }
#endif

void WmcTft::drawStatusDisabled(uint8_t left) {
    for (uint8_t i = 0; i < 3; i++) {
        tft.drawLine(left+2+i,  2, left+20+i, 22, TFT_RED);
        tft.drawLine(left+2+i, 22, left+20+i,  2, TFT_RED);
    }
}

#if APP_CFG_UC == APP_CFG_UC_ESP8266
    void WmcTft::UpdateStatusWifi(uint8 rssiPercent)
    {
        uint8_t left = TFT_WIDTH-88;
        tft.drawBitmap(left, 1, wifi, 24, 24, COLOR_STATUSBAR, TFT_DARKGREY);
        if (rssiPercent >=0) {
            if (rssiPercent > 85) {
                tft.drawBitmap(left, 1, wifi_100, 24, 8, COLOR_STATUSBAR, TFT_WHITE);
            }
            if (rssiPercent > 55) {
                tft.drawBitmap(left+2, 8, wifi_66, 20, 7, COLOR_STATUSBAR, TFT_WHITE);
            }
            if (rssiPercent > 25) {
                tft.drawBitmap(left+6, 14, wifi_33, 12, 5, COLOR_STATUSBAR, TFT_WHITE);
            }
            if (rssiPercent > 5) {
                tft.drawBitmap(left+10, 21, wifi_0, 4, 4, COLOR_STATUSBAR, TFT_WHITE);
            }
        } else {
            // WiFi not connected
            drawStatusDisabled(left);
        }
        tft.drawLine(left+30, 0, left+30, STATUSBAR_HEIGHT-1, TFT_DARKGREY);
    }

    void WmcTft::UpdateStatusZ21(uint8_t state)
    {
        uint8_t left = TFT_WIDTH-125;
        tft.fillRect(left-13, 0, 50, STATUSBAR_HEIGHT, COLOR_STATUSBAR);
        tft.drawLine(left-8, 0, left-8, STATUSBAR_HEIGHT-1, TFT_DARKGREY);

        if (state) {
            tft.drawBitmap(left, 3, z21Icon, 22, 22, COLOR_STATUSBAR, TFT_WHITE);
        } else {
            tft.drawBitmap(left, 3, z21Icon, 22, 22, COLOR_STATUSBAR, TFT_DARKGREY);
            drawStatusDisabled(left);
        }
        tft.drawLine(left+30, 0, left+30, STATUSBAR_HEIGHT-1, TFT_DARKGREY);
    }
#endif

/***********************************************************************************************************************
 * Display number of loc in top stytus bar (<currentLocIndex>/<maxLocCount>)
 * Sample: (1/23)
 */
void WmcTft::UpdateSelectedAndNumberOfLocs(uint8_t actualLocIndex, uint8_t NumberOfLocs)
{
    uint8_t left = 42;
    tft.fillRect(left, 0, 61, STATUSBAR_HEIGHT, COLOR_STATUSBAR);

    char buffer[9];
    snprintf(buffer, sizeof(buffer), "%u/%u", actualLocIndex, NumberOfLocs);
    drawText(buffer, left+60, STATUSBAR_MARGIN, TR_DATUM, TFT_WHITE, FONT1);
}

void WmcTft::UpdateStatusPower(uint8_t state)
{
    tft.fillRect(0, 0, STATUSBAR_MARGIN*2+31, STATUSBAR_HEIGHT, COLOR_STATUSBAR);

    uint16_t color = TFT_RED;
    if (state == 1) {
        color = TFT_GREEN;
    } else if (state == 2) {
        color = TFT_YELLOW;
    }

    tft.drawBitmap(STATUSBAR_MARGIN, 2, powerState, 31, 22, COLOR_STATUSBAR, color);
    tft.drawLine(STATUSBAR_MARGIN*2+31, 0, STATUSBAR_MARGIN*2+31, STATUSBAR_HEIGHT-1, TFT_DARKGREY);
}

#if APP_CFG_UC == APP_CFG_UC_ESP8266
    /***********************************************************************************************************************
     * Show WiFi SSID to connect at the start screen at second to status bar.
     */
    void WmcTft::ShowNetworkName(const char* StrPtr)
    {
        tft.fillRect(0, STATUSBAR_HEIGHT, TFT_WIDTH, STATUSBAR_HEIGHT, COLOR_STATUSBAR);
        drawText(StrPtr, TFT_WIDTH/2, STATUSBAR_HEIGHT + STATUSBAR_MARGIN, TC_DATUM, TFT_YELLOW, FONT1);
    }
#endif

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
        if ((updateAll == true) || ( (locInfoRcvPtr->Functions & (1 << (Function - 1))) != (locInfoActPtr->Functions & (1 << (Function - 1)))) )
        {
            ShowFunction(locInfoRcvPtr->Functions, Function, Index);
        }
    }
}

/***********************************************************************************************************************
 * ToDo
 */
void WmcTft::UpdateTransmitCount(uint8_t count, uint8_t totalCount)
{
    // ToDo
    UNUSED(totalCount);
    tft.fillRect(195, 5, 240, 25, TFT_YELLOW);
    drawText(String(count).c_str(), 195, 150, TL_DATUM, TFT_GREEN, FONT1);
}

/**
 * Show a confirmation message
 */
void WmcTft::ShowConfirmation(uint8_t confirmationType)
{
    drawTextMultiline(txtConfirmation_line3, txtConfirmation_line4, 40, TFT_WIDTH/2, TFT_HEIGHT/2, MC_DATUM, TFT_YELLOW, FONT2, true);

    drawText(lcdTextStrings[txtConfirmation_line1], TFT_WIDTH/2, TFT_HEIGHT/2 - 80, MC_DATUM, TFT_YELLOW, FONT2_B);
    drawText(lcdTextStrings[txtConfirmation_line1 + confirmationType], TFT_WIDTH/2, TFT_HEIGHT/2 - 20, MC_DATUM, TFT_YELLOW, FONT2);
}

/***********************************************************************************************************************
 * ToDo
 */
void WmcTft::ShowMenu(bool emergencyStop, uint8_t menuSelected, uint8_t menuSelectedOld, uint8_t menuItemStart, uint8_t m_menuItemStartOld, uint8_t clear)
{
    // ToDo
    UNUSED(emergencyStop);

    uint8_t itemHeight = 21;
    uint8_t posTop = 30;

    if (clear || menuItemStart != m_menuItemStartOld) {
        Clear(false);
        UpdateStatus(txtStatus_settings, true, WmcTft::color_green);

        uint8_t menuItemMax = (uint8_t)WmcTft::lcdTextMenuStringIndex::maxMenuItemCount;
        uint8_t renderItemsMax = menuItemMax > 10 ? 10 : menuItemMax;
        for (uint8_t i = menuItemStart; i < renderItemsMax + menuItemStart; i++){
            tft.fillRect(0, posTop + ((i-menuItemStart) * itemHeight), TFT_WIDTH, itemHeight, ((i == menuSelected) ? TFT_DARKGREY : TFT_BLACK));
            drawText(lcdTextMenuStrings[i], 5, posTop + ((i - menuItemStart) * itemHeight) + 3, TL_DATUM, TFT_GREEN, FONT1);
        }

    } else {
        uint8_t posTop2 = posTop + (menuSelected - menuItemStart) * itemHeight;
        tft.fillRect(0, posTop2, TFT_WIDTH, itemHeight, TFT_DARKGREY);
        drawText(lcdTextMenuStrings[menuSelected], 5, posTop2 + 3, TL_DATUM, TFT_GREEN, FONT1);

        posTop2 = posTop + (menuSelectedOld - menuItemStart) * itemHeight;
        tft.fillRect(0, posTop2, TFT_WIDTH, itemHeight, TFT_BLACK);
        drawText(lcdTextMenuStrings[menuSelectedOld], 5, posTop2 + 3, TL_DATUM, TFT_GREEN, FONT1);
    }
}

/***********************************************************************************************************************
 * Show info screen
*/
void WmcTft::ShowInfo(String& localIP, String& subnetMask, String& gatewayIP, String& dnsIP, String& centralIp, String& ssid)
{
    Clear(true);
    UpdateStatus("Info", false, WmcTft::color_green);

    #if APP_CFG_UC == APP_CFG_UC_ESP8266
        drawText("IP address:"     ,   0, 30,  TL_DATUM, TFT_GREEN, FONT1);
        drawText(localIP.c_str()   , 100, 30,  TL_DATUM, TFT_GREEN, FONT1);

        drawText("IP Gateway:"     ,   0, 55,  TL_DATUM, TFT_GREEN, FONT1);
        drawText(gatewayIP.c_str() , 100, 55,  TL_DATUM, TFT_GREEN, FONT1);

        drawText("DNS:"            ,   0, 80,  TL_DATUM, TFT_GREEN, FONT1);
        drawText(dnsIP.c_str()     , 100, 80,  TL_DATUM, TFT_GREEN, FONT1);

        drawText("Subnet:"         ,   0, 105, TL_DATUM, TFT_GREEN, FONT1);
        drawText(subnetMask.c_str(), 100, 105, TL_DATUM, TFT_GREEN, FONT1);

        drawText("SSID:"           ,   0, 130, TL_DATUM, TFT_GREEN, FONT1);
        drawText(ssid.c_str()      , 100, 130, TL_DATUM, TFT_GREEN, FONT1);

        drawText("IP Central:"     ,   0, 155, TL_DATUM, TFT_GREEN, FONT1);
        drawText(centralIp.c_str(), 100, 155, TL_DATUM, TFT_GREEN, FONT1);
    #else
        // ToDo
        UNUSED(localIP);
        UNUSED(subnetMask);
        UNUSED(gatewayIP);
        UNUSED(dnsIP);
        UNUSED(centralIp);
        UNUSED(ssid);
    #endif
}


/***********************************************************************************************************************
 * ToDo
*/
void WmcTft::ShowErase(uint8_t eraseType)
{
    Clear(true);

    drawText(lcdTextStrings[txtEraseing_wifi + eraseType], TFT_WIDTH/2, TFT_HEIGHT/2, MC_DATUM, TFT_YELLOW, FONT1);
}

/***********************************************************************************************************************
 * ToDo
*/
void WmcTft::ShowTurnoutScreen()
{
    Clear(false);
    UpdateStatus(txtStatus_turnout, true, WmcTft::color_green);
    ShowTurnoutSymbol(0);
}

/***********************************************************************************************************************
 */
void WmcTft::ShowTurnoutAddress(uint16_t address)
{
    tft.fillRect(40, TFT_HEIGHT-85, 200, 35, TFT_BLACK);
    drawText(String(address).c_str(), TFT_WIDTH/2, TFT_HEIGHT-80, TC_DATUM, TFT_GREEN, FONT3);
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
    if (Light == locoLightOn) {
        tft.drawBitmap(10, 145, bulbOn, 42, 44, TFT_BLACK, TFT_YELLOW);
    } else {
        tft.drawBitmap(10, 145, bulbOff, 42, 44, TFT_BLACK, TFT_DARKGREY);
    }
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

#if APP_CFG_UC == APP_CFG_UC_ESP8266
#else
    /***********************************************************************************************************************
     * ToDo: Remove?
     */
    void WmcTft::ShowXpNetAddress(uint8_t Address)
    {
        tft.fillRect(TFT_WIDTH/2-30, TFT_HEIGHT/2-30, 60, 50, TFT_BLACK);
        drawText(String(Address).c_str(), TFT_WIDTH/2, TFT_HEIGHT/2-10, MC_DATUM, TFT_GREEN, FONT4);
    }
#endif

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
    ShowLampStatus(locoLightOn);
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

void WmcTft::ShowTurnoutSymbol(uint8_t direction) {
    uint8_t width = 20;
    uint8_t width2 = 26;
    uint8_t left = TFT_WIDTH/2;
    uint8_t top = 40;  // 0
    uint8_t height = 100;
    uint8_t lineWidth = 3;

    tft.fillRect(left-width2, top, left+width, height, TFT_BLACK);
    for (uint8_t i = 0; i < lineWidth; i++) {
        tft.drawRect(left+i,       top+i,    width-i*2,    height-i*2, TFT_WHITE);

        tft.drawLine(left,          top+60-i, left-width2+i, top+10,   TFT_WHITE);
        tft.drawLine(left-width2+i, top+10,   left-10,       top+i,      TFT_WHITE);
        tft.drawLine(left-10,       top+i,    left,          top+20+i,   TFT_WHITE);
    }

    if (direction == 1) {
        for (uint8_t i = 0; i < lineWidth; i++) {
            tft.drawLine(left, top+20+i, left+width-1, top+60+i, TFT_WHITE);
        }

        tft.fillRect(left+lineWidth, top+60, width-lineWidth*2, height-60-lineWidth, TFT_GREEN);

        tft.fillTriangle(left+lineWidth-1, top+60, left-width2+lineWidth, top+10,          left-10,              top+lineWidth-1, TFT_GREEN);
        tft.fillTriangle(left+lineWidth-1, top+60, left-10,               top+lineWidth-1, left+width-lineWidth, top+60,          TFT_GREEN);

    } else if (direction == 2) {
        tft.fillRect(left+lineWidth, top+lineWidth,    width-lineWidth*2, height-lineWidth*2, TFT_GREEN);
    }
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
        ShowLampStatus(locoLightOn);
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

/**
 * Show screen to request a reset or a power cycle
 */
void WmcTft::AskForReset(void)
{
    Clear(true);
    UpdateStatus(WmcTft::txtStatus_commandLine, true, WmcTft::color_green);
    drawTextMultiline(txtAskForReset_line1, txtAskForReset_line3, 30, TFT_WIDTH/2, TFT_HEIGHT/2-25, MC_DATUM, TFT_YELLOW, FONT1, false);
}

/***********************************************************************************************************************
 * Show reset message
 */
void WmcTft::ShowResetMessage()
{
    Clear(true);
    UpdateStatus(WmcTft::txtStatus_commandLine, true, WmcTft::color_green);
    drawTextMultiline(txtShowReset_line1, txtShowReset_line2, 30, TFT_WIDTH/2, TFT_HEIGHT/2-12, MC_DATUM, TFT_YELLOW, FONT1, false);
}

/***********************************************************************************************************************
 */
uint16_t WmcTft::getColor(color Clr)
{
    uint16_t ColorReturn;
    switch (Clr)
    {
    case color_red: ColorReturn = 0xFC10; break;
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

#if APP_CFG_UC == APP_CFG_UC_ESP8266
    void WmcTft::ShowPowerOffMessage(void) {
        Clear(true);
        drawText(lcdTextStrings[txtPowerOff_line1], TFT_WIDTH/2, 30, MC_DATUM, TFT_YELLOW, FONT2_B);
        drawText(lcdTextStrings[txtPowerOff_line2], TFT_WIDTH/2, TFT_HEIGHT - 40, MC_DATUM, TFT_YELLOW, FONT2);

        // draw powerOff symbol
        uint8_t top = 80;
        for (uint8_t r = 35; r <= 40; r++){
            tft.drawCircle(TFT_WIDTH/2, top + 40, r, TFT_RED);
        }
        tft.fillRect(TFT_WIDTH/2 - 15, top , 30, 40, TFT_BLACK);
        tft.fillRect(TFT_WIDTH/2 - 3, top - 5 , 6, 40, TFT_RED);
    }

    void WmcTft::ShowFirmwareUpdateMessage(uint8_t updateState, uint8_t progress) {
        if (updateState == 0) {
            Clear(true);
            drawText(lcdTextStrings[txtOtaUpdate_line1], TFT_WIDTH/2, 30, MC_DATUM, TFT_YELLOW, FONT2_B);

            // draw uppdate symbol
            uint8_t top = 80;
            for (uint8_t r = 35; r <= 45; r++){
                tft.drawCircle(TFT_WIDTH/2, top + 40, r, TFT_GREEN);
            }
            tft.fillRect(TFT_WIDTH/2, top + 45 , 60, 55, TFT_BLACK);
            tft.fillTriangle(TFT_WIDTH/2, top + 65, TFT_WIDTH/2, top + 95, TFT_WIDTH/2+25, top + 80, TFT_GREEN);
        }

        tft.fillRect(0, TFT_HEIGHT - 50 , TFT_WIDTH, 40, TFT_BLACK);

        if (updateState == 1) {
            String txtProgress = lcdTextStrings[txtOtaUpdate_line2];
            txtProgress += " " + String(progress) + " %";
            drawText(txtProgress.c_str(), TFT_WIDTH/2, TFT_HEIGHT - 40, MC_DATUM, TFT_YELLOW, FONT2);

        } else if (updateState == 2) {
            drawText(lcdTextStrings[txtOtaUpdate_line3], TFT_WIDTH/2, TFT_HEIGHT - 40, MC_DATUM, TFT_YELLOW, FONT1);

        } else if (updateState > 2) {
            // process update errors
            String txtError = lcdTextStrings[txtOtaUpdate_Error];
            txtError += lcdTextStrings[txtOtaUpdate_Error0 + updateState];
            drawText(lcdTextStrings[txtOtaUpdate_line3], TFT_WIDTH/2, TFT_HEIGHT - 40, MC_DATUM, TFT_RED, FONT1);
        }
    }
#endif
