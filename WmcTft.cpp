/**
 * Functions to show data on the display of the Wmc application.
 */

// include this library's description file
#include "WmcTft.h"
#include "Adafruit_ST7735.h"
#include "Loclib.h"
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
#define TFT_RST D2
#define TFT_DC D1
#define TFT_CS D8
#define TFT_SCLK D3
#define TFT_MOSI D4
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

#define GRAY 0xE73C

/***********************************************************************************************************************
 */
WmcTft::WmcTft() {}

/***********************************************************************************************************************
 */
void WmcTft::Init(void)
{
    // Initialize a ST7735S chip / display and show text.
    tft.initR(INITR_GREENTAB);
    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(37, 40);
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(2);
    tft.println("WIFI");
    tft.setCursor(27, 60);
    tft.println("MANUAL");
    tft.setCursor(22, 80);
    tft.println("CONTROL");
}

/***********************************************************************************************************************
 */
void WmcTft::Clear(void) { tft.fillScreen(ST7735_BLACK); }

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
void WmcTft::UpdateSelectedAndNumberOfLocs(uint8_t actualLocIndex, uint8_t NumberOfLocs)
{
    tft.fillRect(88, 0, 128, 14, 0);
    tft.setCursor(88, 5);
    tft.setTextSize(1);
    tft.setTextColor(ST7735_GREEN);
    tft.print("(");
    tft.print(actualLocIndex);
    tft.print("/");
    tft.print(NumberOfLocs);
    tft.print(")");
}

/***********************************************************************************************************************
 */
void WmcTft::UpdateLocInfo(
    Z21Slave::locInfo* locInfoRcvPtr, Z21Slave::locInfo* locInfoActPtr, uint8_t* assignedFunctions, bool updateAll)
{
    uint8_t Index    = 0;
    uint8_t Function = 0;

    if ((updateAll == true) || (locInfoRcvPtr->Direction != locInfoActPtr->Direction))
    {
        if (locInfoRcvPtr->Direction == Z21Slave::locDirectionForward)
        {
            ShowLocSymbolFw();
        }
        else
        {
            ShowLocSymbolBw();
        }
    }

    if ((updateAll == true) || (locInfoRcvPtr->Address != locInfoActPtr->Address))
    {
        /* Show address. */
        ShowlocAddress(locInfoRcvPtr->Address, WmcTft::color_green);
    }

    if ((updateAll == true) || (locInfoRcvPtr->Steps != locInfoActPtr->Steps))
    {
        switch (locInfoRcvPtr->Steps)
        {
        case Z21Slave::locDecoderSpeedSteps14: ShowLocDecoderSteps(14); break;
        case Z21Slave::locDecoderSpeedSteps28: ShowLocDecoderSteps(28); break;
        case Z21Slave::locDecoderSpeedSteps128: ShowLocDecoderSteps(128); break;
        case Z21Slave::locDecoderSpeedStepsUnknown: ShowLocDecoderSteps(28); break;
        }
    }

    /* Update speed. */
    if ((updateAll == true) || (locInfoRcvPtr->Speed != locInfoActPtr->Speed))
    {
        /* Show Speed. */
        tft.fillRect(0, 53, 75, 30, ST7735_BLACK);
        tft.setCursor(10, 53);
        tft.setTextColor(ST7735_GREEN);
        tft.setTextSize(3);
        tft.println(locInfoRcvPtr->Speed);
    }

    /* Show light symbol (or not) depending on light status. */
    if ((updateAll == true) || (locInfoRcvPtr->Light != locInfoActPtr->Light))
    {
        if (locInfoRcvPtr->Light == Z21Slave::locLightOn)
        {
            tft.drawBitmap(80, 50, bulbBitmapOn, 28, 28, ST7735_BLACK, ST7735_WHITE);
        }
        else
        {
            tft.fillRect(80, 50, 28, 28, ST7735_BLACK);
        }
    }

    tft.setTextSize(1);

    for (Index = 0; Index < 5; Index++)
    {
        Function = assignedFunctions[Index];
        if (Function != 0)
        {
            if ((updateAll == true)
                || (((locInfoRcvPtr->Functions & (1 << (Function - 1)))
                       != (locInfoActPtr->Functions & (1 << (Function - 1))))))
            {
                if ((locInfoRcvPtr->Functions & (1 << (Function - 1))) == (1 << (Function - 1)))
                {
                    tft.drawBitmap(9 + (Index * 23), 100, FuntionBackgroundBitmap, 20, 20, ST7735_BLACK, ST7735_GREEN);
                }
                else
                {
                    tft.drawBitmap(9 + (Index * 23), 100, FuntionBackgroundBitmap, 20, 20, ST7735_BLACK, GRAY);
                }

                tft.setTextColor(ST7735_BLACK);
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
        else
        {
            tft.fillRect(9, 100, 21, 21, 0);
        }
    }
}

/***********************************************************************************************************************
 */
void WmcTft::WifiConnectUpdate(uint8_t count)
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
void WmcTft::WifiConnectFailed()
{
    Clear();
    tft.setCursor(37, 40);
    tft.setTextColor(ST7735_RED);
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
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(2);
    tft.println("Z21 CONTROL");
    tft.setCursor(24, 60);
    tft.println("CONNECT");
    tft.setCursor(29, 80);
    tft.println("FAILED");
}

/***********************************************************************************************************************
 */
void WmcTft::ShowMenu()
{
    Clear();
    UpdateStatus("MENU", true, WmcTft::color_green);
    tft.setCursor(0, 22);
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(2);
    tft.println("1 ADD");
    tft.println("2 CHANGE");
    tft.println("3 DELETE");
    tft.println("4 EXIT");
}

/***********************************************************************************************************************
 */
void WmcTft::ShowTurnoutScreen()
{
    Clear();
    UpdateStatus("TURNOUT", true, WmcTft::color_green);

    tft.drawBitmap(85, 20, TurnoutBitmap, 28, 28, ST7735_BLACK, ST7735_WHITE);
}

/***********************************************************************************************************************
 */
void WmcTft::ShowTurnoutAddress(uint16_t address)
{
    tft.fillRect(10, 22, 70, 30, ST7735_BLACK);
    tft.setCursor(10, 22);
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(3);
    tft.print(address);
}

/***********************************************************************************************************************
 */
void WmcTft::ShowTurnoutDirection(uint8_t direction)
{
    switch (direction)
    {
    case 0: tft.drawBitmap(85, 20, TurnoutBitmap, 28, 28, ST7735_BLACK, ST7735_WHITE); break;
    case 1: tft.drawBitmap(85, 20, TurnoutForwardBitmap, 28, 28, ST7735_BLACK, ST7735_WHITE); break;
    case 2: tft.drawBitmap(85, 20, TurnoutLeftBitmap, 28, 28, ST7735_BLACK, ST7735_WHITE); break;
    default: tft.drawBitmap(85, 20, TurnoutBitmap, 28, 28, ST7735_BLACK, ST7735_WHITE); break;
    }
}

/***********************************************************************************************************************
 */
void WmcTft::ShowlocAddress(uint16_t address, color textColor)
{
    uint16_t Color;
    tft.fillRect(10, 22, 70, 30, ST7735_BLACK);
    tft.setCursor(10, 22);
    Color = getColor(textColor);
    tft.setTextColor(Color);
    tft.setTextSize(3);
    tft.print(address);
}

/***********************************************************************************************************************
 */
void WmcTft::ShowLocDecoderSteps(uint8_t Steps)
{
    tft.fillRect(65, 0, 19, 14, 0);
    tft.setCursor(65, 5);
    tft.setTextSize(1);
    tft.setTextColor(ST7735_GREEN);
    tft.print(Steps);
}

/***********************************************************************************************************************
 */
void WmcTft::FunctionAddSet()
{
    uint8_t Index;
    tft.setCursor(10, 52);
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(3);
    tft.print(0);

    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(1);

    for (Index = 0; Index < 5; Index++)
    {
        tft.drawBitmap(9 + (Index * 23), 100, FuntionBackgroundBitmap, 20, 20, ST7735_BLACK, ST7735_GREEN);
        tft.setCursor(17 + (Index * 23), 107);
        tft.print(Index);
    }
    tft.drawBitmap(80, 50, bulbBitmapOn, 28, 28, ST7735_BLACK, ST7735_WHITE);
}

/***********************************************************************************************************************
 */
void WmcTft::ShowLocSymbolFw() { tft.drawBitmap(85, 20, locBitmapFw, 28, 28, ST7735_BLACK, ST7735_WHITE); }

/***********************************************************************************************************************
 */
void WmcTft::ShowLocSymbolBw() { tft.drawBitmap(85, 20, locBitmapBw, 28, 28, ST7735_BLACK, ST7735_WHITE); }

/***********************************************************************************************************************
 */
void WmcTft::FunctionAddUpdate(uint16_t function)
{
    tft.fillRect(10, 50, 75, 25, ST7735_BLACK);
    tft.setCursor(10, 52);
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(3);
    tft.print(function);
}

/***********************************************************************************************************************
 */
void WmcTft::UpdateFunction(uint8_t Index, uint8_t Function)
{
    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(1);

    if ((Index == 0) && (Function == 0))
    {
        tft.drawBitmap(80, 50, bulbBitmapOn, 28, 28, ST7735_BLACK, ST7735_WHITE);
        tft.fillRect(9, 100, 21, 21, 0);
    }
    else
    {
        if (Index == 0)
        {
            tft.fillRect(80, 50, 28, 28, 0);
        }
        tft.drawBitmap(9 + (Index * 23), 100, FuntionBackgroundBitmap, 20, 20, ST7735_BLACK, ST7735_GREEN);

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
uint16_t WmcTft::getColor(color Clr)
{
    uint16_t ColorReturn;
    switch (Clr)
    {
    case color_red: ColorReturn = ST7735_RED; break;
    case color_green: ColorReturn = ST7735_GREEN; break;
    case color_yellow: ColorReturn = ST7735_YELLOW; break;
    default: ColorReturn = ST7735_RED; break;
    }

    return (ColorReturn);
}