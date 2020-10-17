/**
 * Functions to show data on the display of the Wmc application.
 */

// include this library's description file
#include "WmcTft.h"
#include <TFT_eSPI.h>
#include "app_cfg.h"
#include <string.h>

/**
 * Forward direction loc symbol.
 */
const unsigned char locBitmapFw[] = { 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xf8,
    0x1f, 0xff, 0xf0, 0x80, 0x1, 0xff, 0xf0, 0x80, 0x1, 0xff, 0xf0, 0x87, 0xe1, 0xf0, 0xf0, 0xc7, 0xe3, 0xf0, 0x70,
    0xc7, 0xe3, 0xf0, 0x70, 0xc7, 0xf3, 0xf0, 0x70, 0x80, 0x0, 0x0, 0x70, 0x80, 0x0, 0x0, 0x30, 0x80, 0x0, 0x0, 0x10,
    0x80, 0x0, 0x0, 0x10, 0x80, 0x0, 0x0, 0x10, 0x87, 0x80, 0x0, 0x10, 0x8f, 0xc0, 0x0, 0x30, 0x9c, 0xe0, 0x0, 0x30,
    0x9c, 0xe1, 0x83, 0x10, 0x9c, 0xe3, 0xc7, 0x90, 0x8f, 0xc3, 0xc7, 0x90, 0xcf, 0xc3, 0xc7, 0x90, 0xc3, 0x11, 0x2,
    0x30, 0xf0, 0x38, 0x10, 0x30, 0xf8, 0xfe, 0x7c, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff,
    0xff, 0xf0 };

/**
 * Backward direction loc symbol.
 */
const unsigned char locBitmapBw[] = { 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff,
    0xff, 0x81, 0xf0, 0xff, 0xf8, 0x0, 0x10, 0xff, 0xf8, 0x0, 0x10, 0xf0, 0xf8, 0x7e, 0x10, 0xe0, 0xfc, 0x7e, 0x30,
    0xe0, 0xfc, 0x7e, 0x30, 0xe0, 0xfc, 0xfe, 0x30, 0xe0, 0x0, 0x0, 0x10, 0xc0, 0x0, 0x0, 0x10, 0x80, 0x0, 0x0, 0x10,
    0x80, 0x0, 0x0, 0x10, 0x80, 0x0, 0x0, 0x10, 0x80, 0x0, 0x1e, 0x10, 0xc0, 0x0, 0x3f, 0x10, 0xc0, 0x0, 0x73, 0x90,
    0x8c, 0x18, 0x73, 0x90, 0x9e, 0x3c, 0x73, 0x90, 0x9e, 0x3c, 0x3f, 0x10, 0x9e, 0x3c, 0x3f, 0x30, 0xc4, 0x8, 0x8c,
    0x30, 0xc0, 0x81, 0xc0, 0xf0, 0xf3, 0xe7, 0xf1, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff,
    0xff, 0xf0 };

/**
 * Bulb symbol for display of light function.
 */
const unsigned char bulbBitmapOn[] = { 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff,
    0xb9, 0xdf, 0xf0, 0xff, 0x99, 0x9f, 0xf0, 0xff, 0x9f, 0x9f, 0xf0, 0xff, 0xf9, 0xff, 0xf0, 0xf8, 0xe0, 0x71, 0xf0,
    0xfc, 0x8f, 0x13, 0xf0, 0xff, 0x9f, 0x9f, 0xf0, 0xff, 0x3f, 0xcf, 0xf0, 0xf1, 0x3f, 0xc8, 0xf0, 0xf1, 0x3f, 0xc8,
    0xf0, 0xff, 0x3f, 0xcf, 0xf0, 0xff, 0xbf, 0xdf, 0xf0, 0xfc, 0x9f, 0x93, 0xf0, 0xf8, 0xcf, 0x31, 0xf0, 0xff, 0xcf,
    0x3f, 0xf0, 0xff, 0xe7, 0x7f, 0xf0, 0xff, 0xe6, 0x7f, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xe0, 0x7f, 0xf0, 0xff,
    0xf0, 0xff, 0xf0, 0xff, 0xf0, 0xff, 0xf0, 0xff, 0xf0, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0,
    0xff, 0xff, 0xff, 0xf0 };

/**
 * Background of function symbol.
 */
const unsigned char FuntionBackgroundBitmap[]
    = { 0xfc, 0x3, 0xf0, 0xf8, 0x1, 0xf0, 0xf0, 0x0, 0xf0, 0xe0, 0x0, 0x70, 0xc0, 0x0, 0x30, 0x80, 0x0, 0x10, 0x0, 0x0,
          0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
          0x80, 0x0, 0x10, 0xc0, 0x0, 0x30, 0xe0, 0x0, 0x70, 0xf0, 0x0, 0xf0, 0xf8, 0x1, 0xf0, 0xfc, 0x3, 0xf0 };

/**
 *
 */
const unsigned char TurnoutBitmap[] = { 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf8, 0x0, 0xff, 0xff, 0xf8, 0x0, 0xff,
    0xff, 0xf0, 0x0, 0xff, 0xff, 0xc0, 0x0, 0xff, 0xff, 0xc0, 0x0, 0xff, 0xff, 0x80, 0x0, 0xff, 0xfe, 0x0, 0x10, 0xff,
    0xfc, 0x0, 0x70, 0xff, 0xfc, 0x0, 0x70, 0xff, 0xf8, 0x0, 0xf0, 0xff, 0xe0, 0x3, 0xf0, 0xff, 0xe0, 0x3, 0xf0, 0xff,
    0xc0, 0x7, 0xf0, 0xff, 0x0, 0xf, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0,
    0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0 };

/**
 *
 */
const unsigned char TurnoutLeftBitmap[]
    = { 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf8, 0x0, 0xff, 0xff, 0xf8, 0x0, 0xff, 0xff, 0xf3, 0xe0, 0xff, 0xff, 0xc7,
          0xe0, 0xff, 0xff, 0xc7, 0xe0, 0xff, 0xff, 0x8f, 0x80, 0xff, 0xfe, 0x3f, 0x10, 0xff, 0xfc, 0x7c, 0x70, 0xff,
          0xfc, 0x7c, 0x70, 0xff, 0xf9, 0xf8, 0xf0, 0xff, 0xe3, 0xf3, 0xf0, 0xff, 0xe3, 0xf3, 0xf0, 0xff, 0xc7, 0xc7,
          0xf0, 0xff, 0x1f, 0x8f, 0xf0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x7f, 0xfc, 0x0, 0x0, 0x7f, 0xf8, 0x0,
          0x0, 0x7f, 0xf8, 0x0, 0x0, 0x7f, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff,
          0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0 };

/**
 *
 */
const unsigned char TurnoutForwardBitmap[] = { 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf8, 0x0, 0xff, 0xff, 0xf8, 0x0,
    0xff, 0xff, 0xf0, 0x0, 0xff, 0xff, 0xc0, 0x0, 0xff, 0xff, 0xc0, 0x0, 0xff, 0xff, 0x80, 0x0, 0xff, 0xfe, 0x0, 0x10,
    0xff, 0xfc, 0x0, 0x70, 0xff, 0xfc, 0x0, 0x70, 0xff, 0xf8, 0x0, 0xf0, 0xff, 0xe0, 0x3, 0xf0, 0xff, 0xe0, 0x3, 0xf0,
    0xff, 0xc0, 0x7, 0xf0, 0xff, 0x0, 0xf, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0xff, 0xe0, 0x7f,
    0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xf0, 0xff,
    0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0 };

// These pins will also work for the 1.8" TFT shield
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define GRAY 0xE73C

/***********************************************************************************************************************
 */
WmcTft::WmcTft() {}

/***********************************************************************************************************************
 */
void WmcTft::Init(void)
{
	// initialize TFT display
	tft.init();
	tft.fillScreen(TFT_BLACK);
	tft.setRotation(2);

    tft.setTextWrap(false);
#if APP_CFG_UC == APP_CFG_UC_STM32
    ShowName();
#endif
}

/***********************************************************************************************************************
 */
void WmcTft::ShowVersion(uint16_t SwMajor, uint8_t SwMinor, uint8_t SwPatch)
{
    char VersionStr[20];

    if (SwPatch != 99)
    {
        snprintf(VersionStr, sizeof(VersionStr), "%02hu.%02hu.%02hu", SwMajor, SwMinor, SwPatch);
    }
    else
    {
        snprintf(VersionStr, sizeof(VersionStr), " %04hu", SwMajor);
    }
    tft.setTextSize(1);
    tft.setCursor(39, 103);
    tft.print(VersionStr);
}

/***********************************************************************************************************************
 */
void WmcTft::ShowName(void)
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(2);
#if APP_CFG_UC == APP_CFG_UC_ESP8266
    tft.setCursor(37, 40);
    tft.println("WIFI");
#else
    tft.setCursor(34, 40);
    tft.println(" XMC");
#endif
    tft.setCursor(27, 60);
    tft.println("MANUAL");
    tft.setCursor(22, 80);
    tft.println("CONTROL");
}

/***********************************************************************************************************************
 */
void WmcTft::Clear(void) { tft.fillScreen(TFT_BLACK); }

/***********************************************************************************************************************
 */
void WmcTft::UpdateStatus(const char* StrPtr, bool clearRowFull, color textColor)
{
    uint16_t Color;
    if (clearRowFull == true)
    {
        tft.fillRect(0, 0, 128, 14, 0);
    }
    else
    {
        tft.fillRect(0, 0, 64, 14, 0);
    }

    Color = getColor(textColor);
    tft.setTextColor(Color);

    tft.setCursor(5, 4);
    tft.setTextSize(1);
    tft.println(StrPtr);
}

/***********************************************************************************************************************
 */
void WmcTft::ShowIpAddressToConnectTo(const char* IpStr)
{
    uint16_t Length;

    Length = strlen(IpStr);
    Length *= 6;

    // "Center" the IP address.
    tft.setCursor(60 - (Length / 2), 14);
    tft.setTextColor(getColor(WmcTft::color_yellow));
    tft.setTextSize(1);
    tft.print("(");
    tft.print(IpStr);
    tft.print(")");
}

/***********************************************************************************************************************
 */
void WmcTft::ShowNetworkName(const char* StrPtr)
{
    uint16_t Length;

    Length = strlen(StrPtr);
    Length *= 6;

    /* "Center" the text under the status row. */
    tft.setCursor(56 - (Length / 2), 14);
    tft.setTextSize(1);
    tft.print("(");
    tft.print(StrPtr);
    tft.print(")");
}

/***********************************************************************************************************************
 */
void WmcTft::ClearNetworkName(void) { tft.fillRect(0, 14, 128, 26, 0); }

/***********************************************************************************************************************
 */
void WmcTft::UpdateSelectedAndNumberOfLocs(uint8_t actualLocIndex, uint8_t NumberOfLocs)
{
    tft.fillRect(88, 0, 128, 14, 0);
    tft.setCursor(88, 5);
    tft.setTextSize(1);
    tft.setTextColor(TFT_GREEN);
    tft.print("(");
    tft.print(actualLocIndex);
    tft.print("/");
    tft.print(NumberOfLocs);
    tft.print(")");
}

/***********************************************************************************************************************
 */
void WmcTft::UpdateLocInfo(
    locoInfo* locInfoRcvPtr, locoInfo* locInfoActPtr, uint8_t* assignedFunctions, char* LocName, bool updateAll)
{
    uint8_t Index    = 0;
    uint8_t Function = 0;

    if ((updateAll == true) || (locInfoRcvPtr->Direction != locInfoActPtr->Direction)
        || (locInfoRcvPtr->Occupied != locInfoActPtr->Occupied))
    {
        if (locInfoRcvPtr->Direction == locoDirectionForward)
        {
            if (locInfoRcvPtr->Occupied == false)
            {
                ShowLocSymbolFw(color_white);
            }
            else
            {
                ShowLocSymbolFw(color_yellow);
            }
        }
        else
        {
            if (locInfoRcvPtr->Occupied == false)
            {
                ShowLocSymbolBw(color_white);
            }
            else
            {
                ShowLocSymbolBw(color_yellow);
            }
        }
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

    for (Index = 0; Index < 5; Index++)
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
 */
void WmcTft::UpdateRunningWheel(uint8_t count)
{
    tft.fillRect(120, 0, 128, 14, 0);
    tft.setCursor(120, 5);
    tft.setTextSize(1);
    if (count % 2)
    {
        tft.print("|");
    }
    else
    {
        tft.print("-");
    }
}

/***********************************************************************************************************************
 */
void WmcTft::UpdateTransmitCount(uint8_t count, uint8_t totalCount)
{
    char TmpStr[10];
    snprintf(TmpStr, sizeof(TmpStr), "%02hu/%02hu", count, totalCount);
    tft.fillRect(95, 0, 128, 14, 0);
    tft.setCursor(95, 4);
    tft.setTextSize(1);
    tft.print(TmpStr);
}

/***********************************************************************************************************************
 */
void WmcTft::WifiConnectFailed()
{
    Clear();
    tft.setCursor(37, 40);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(2);
    tft.println("WIFI");
    tft.setCursor(21, 60);
    tft.println("CONNECT");
    tft.setCursor(26, 80);
    tft.println("FAILED");
}

/***********************************************************************************************************************
 */
void WmcTft::UdpConnectFailed()
{
    Clear();
    tft.setCursor(1, 40);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(2);
    tft.println("Z21 CONTROL");
    tft.setCursor(24, 60);
    tft.println("CONNECT");
    tft.setCursor(29, 80);
    tft.println("FAILED");
}

/***********************************************************************************************************************
 */
void WmcTft::ShowMenu1()
{
    Clear();
    UpdateStatus("MENU 1", true, WmcTft::color_green);
    tft.setCursor(0, 22);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(2);
    tft.println("1 ADD");
    tft.println("2 CHANGE");
    tft.println("3 DELETE");
    tft.println("4 CV PROG");
    tft.println("5 POM PROG");
}

/***********************************************************************************************************************
 */
void WmcTft::ShowMenu2(bool emergencyStop, bool clearScreen)
{
    if (clearScreen == true)
    {
        Clear();
        UpdateStatus("MENU 2", true, WmcTft::color_green);
    }

    tft.setCursor(0, 22);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(2);
#if APP_CFG_UC == APP_CFG_UC_STM32
    tft.println("1 XPNET ");
#else
    tft.println("");
#endif
    tft.fillRect(0, 36, 128, 17, 0);
    if (emergencyStop == true)
    {
        tft.println("2 EM STOP  ");
    }
    else
    {
        tft.println("2 OFF      ");
    }
    tft.println("3 TRANSMIT");
    tft.println("4 DEL LOCS");
    tft.println("5 DEL ALL");
}

/***********************************************************************************************************************
 */
void WmcTft::ShowErase()
{
    Clear();
    tft.setCursor(10, 50);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(2);
    tft.println(" ERASING");
}

/***********************************************************************************************************************
 */
void WmcTft::ShowTurnoutScreen()
{
    UpdateStatus("TURNOUT", true, WmcTft::color_green);

    tft.drawBitmap(85, 20, TurnoutBitmap, 28, 28, TFT_BLACK, TFT_WHITE);
}

/***********************************************************************************************************************
 */
void WmcTft::ShowTurnoutAddress(uint16_t address)
{
    tft.fillRect(10, 22, 70, 30, TFT_BLACK);
    tft.setCursor(10, 22);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(3);
    tft.print(address);
}

/***********************************************************************************************************************
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
    uint16_t Color;
    tft.fillRect(10, 22, 70, 30, TFT_BLACK);
    tft.setCursor(10, 22);
    Color = getColor(textColor);
    tft.setTextColor(Color);
    tft.setTextSize(3);
    tft.print(address);
}

/***********************************************************************************************************************
 */
void WmcTft::ShowlocSpeed(uint8_t Speed)
{
    tft.fillRect(0, 53, 75, 30, TFT_BLACK);
    tft.setCursor(10, 53);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(3);
    tft.println(Speed);
}

/***********************************************************************************************************************
 */
void WmcTft::ShowLampStatus(locoLight Light)
{
    if (Light == locoLightOn)
    {
        tft.drawBitmap(80, 50, bulbBitmapOn, 28, 28, TFT_BLACK, TFT_WHITE);
    }
    else
    {
        tft.fillRect(80, 50, 28, 28, TFT_BLACK);
    }
}

/***********************************************************************************************************************
 */
void WmcTft::ShowFunction(uint32_t Functions, uint8_t Function, uint8_t Location)
{
    tft.setTextSize(1);

    if (Function != 0)
    {
        if ((Functions & (1 << (Function - 1))) == (uint32_t)((1 << (Function - 1))))
        {
            tft.drawBitmap(9 + (Location * 23), 100, FuntionBackgroundBitmap, 20, 20, TFT_BLACK, TFT_GREEN);
        }
        else
        {
            tft.drawBitmap(9 + (Location * 23), 100, FuntionBackgroundBitmap, 20, 20, TFT_BLACK, GRAY);
        }

        tft.setTextColor(TFT_BLACK);
        if (Function < 10)
        {
            tft.setCursor(17 + (Location * 23), 107);
        }
        else if (Function < 20)
        {
            tft.setCursor(13 + (Location * 23), 107);
        }
        else
        {
            tft.setCursor(12 + (Location * 23), 107);
        }
        tft.print(Function);
    }
    else
    {
        tft.fillRect(9, 100, 21, 21, 0);
    }
}

/***********************************************************************************************************************
 */
void WmcTft::ShowlocName(char* NamePtr, color textColor)
{
    uint16_t Length;
    uint16_t Color;

    tft.fillRect(0, 80, 127, 14, TFT_BLACK);

    // Only print name when string has data.
    if (NamePtr != NULL)
    {
        // "Center" the locname address and print the name.
        Length = strlen(NamePtr);
        Length *= 6;
        tft.setCursor(60 - (Length / 2), 83);

        Color = getColor(textColor);
        tft.setTextColor(Color);
        tft.setTextSize(1);
        tft.print(NamePtr);
    }
}

/***********************************************************************************************************************
 */
void WmcTft::ShowLocDecoderSteps(uint8_t Steps)
{
    tft.fillRect(65, 0, 19, 14, 0);
    tft.setCursor(65, 5);
    tft.setTextSize(1);
    tft.setTextColor(TFT_GREEN);
    tft.print(Steps);
}

/***********************************************************************************************************************
 */
void WmcTft::ShowXpNetAddress(uint16_t Address)
{
    tft.fillRect(10, 22, 70, 30, TFT_BLACK);
    tft.setCursor(10, 22);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(3);
    tft.print(Address);
}

/***********************************************************************************************************************
 */
void WmcTft::FunctionAddSet()
{
    uint8_t Index;
    tft.setCursor(10, 52);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(3);
    tft.print(0);

    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(1);

    for (Index = 0; Index < 5; Index++)
    {
        tft.drawBitmap(9 + (Index * 23), 100, FuntionBackgroundBitmap, 20, 20, TFT_BLACK, TFT_GREEN);
        tft.setCursor(17 + (Index * 23), 107);
        tft.print(Index);
    }
    tft.drawBitmap(80, 50, bulbBitmapOn, 28, 28, TFT_BLACK, TFT_WHITE);
}

/***********************************************************************************************************************
 */
void WmcTft::ShowLocSymbolFw(color locSymbolColor)
{
    switch (locSymbolColor)
    {
    case color_red: tft.drawBitmap(85, 20, locBitmapFw, 28, 28, TFT_BLACK, TFT_RED); break;
    case color_green: tft.drawBitmap(85, 20, locBitmapFw, 28, 28, TFT_BLACK, TFT_GREEN); break;
    case color_white: tft.drawBitmap(85, 20, locBitmapFw, 28, 28, TFT_BLACK, TFT_WHITE); break;
    case color_yellow: tft.drawBitmap(85, 20, locBitmapFw, 28, 28, TFT_BLACK, TFT_YELLOW); break;
    }
}

/***********************************************************************************************************************
 */
void WmcTft::ShowLocSymbolBw(color locSymbolColor)
{
    switch (locSymbolColor)
    {
    case color_red: tft.drawBitmap(85, 20, locBitmapBw, 28, 28, TFT_BLACK, TFT_RED); break;
    case color_green: tft.drawBitmap(85, 20, locBitmapBw, 28, 28, TFT_BLACK, TFT_GREEN); break;
    case color_white: tft.drawBitmap(85, 20, locBitmapBw, 28, 28, TFT_BLACK, TFT_WHITE); break;
    case color_yellow: tft.drawBitmap(85, 20, locBitmapBw, 28, 28, TFT_BLACK, TFT_YELLOW); break;
    }
}

/***********************************************************************************************************************
 */
void WmcTft::FunctionAddUpdate(uint16_t function)
{
    tft.fillRect(10, 50, 75, 25, TFT_BLACK);
    tft.setCursor(10, 52);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(3);
    tft.print(function);
}

/***********************************************************************************************************************
 */
void WmcTft::UpdateFunction(uint8_t Index, uint8_t Function)
{
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(1);

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
 */
void WmcTft::CommandLine(void)
{
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(2);
    tft.setCursor(9, 40);
    tft.println(" RESET OR");
    tft.setCursor(7, 60);
    tft.println("POWERCYCLE");
    tft.setCursor(22, 890);
    tft.println("TO EXIT");
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
 */
void WmcTft::ShowPomAddress(uint16_t Address, bool Init, color Clr)
{
    if (Init == true)
    {
        tft.setCursor(5, 20);
        tft.setTextColor(TFT_YELLOW);
        tft.setTextSize(1);
        tft.print("POM loc address");
    }

    tft.fillRect(60, 30, 68, 30, TFT_BLACK);
    tft.setCursor(60, 30);
    tft.setTextColor(getColor(Clr));
    tft.setTextSize(3);
    tft.print(Address);
}

/***********************************************************************************************************************
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
        tft.setTextSize(1);
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
    tft.setTextSize(3);
    tft.print(CvNUmber);
}

/***********************************************************************************************************************
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
        tft.setTextSize(1);
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
    tft.setTextSize(3);
    tft.print(CvValue);
}

/***********************************************************************************************************************
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
