#ifndef WMC_BITMAPS_H
#define WMC_BITMAPS_H

// 'powerState', 31x22px
const unsigned char powerState [] PROGMEM = {
    0xe0, 0x03, 0xff, 0xfe, 0xc0, 0x00, 0xff, 0xfe, 0xdf, 0xfc, 0xff, 0xfe, 0xbf, 0xfc, 0xff, 0xfe,
    0xbf, 0xfc, 0x7f, 0xfe, 0xbf, 0xfe, 0x7f, 0xfe, 0xbf, 0xfe, 0x3f, 0xfe, 0x00, 0x00, 0x1f, 0xfe,
    0x00, 0x00, 0x4f, 0xfe, 0x00, 0x00, 0x6f, 0xfe, 0x00, 0x00, 0x63, 0xfe, 0x00, 0x00, 0x69, 0xfe,
    0x30, 0x08, 0x6c, 0xfe, 0x30, 0x1c, 0x6d, 0x3e, 0x20, 0x08, 0x0d, 0xa6, 0x00, 0x00, 0x05, 0xe8,
    0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xfe, 0xc3, 0xe0, 0x00, 0x00
};

// 'locoBW', 170x45px
const unsigned char locoBW [] PROGMEM = {
    0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0f, 0xff, 0xff, 0xc0, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc0, 0xff, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7f, 0xc0, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0xfc, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0f, 0xc0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0xf8, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0xc0,
    0xf8, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x3f, 0x07, 0xc0, 0xf8, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x07, 0xc0, 0xf0, 0x7f, 0xe0, 0x7f,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc3, 0xff,
    0x07, 0xc0, 0xf0, 0x7f, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x1f, 0xc3, 0xff, 0x03, 0xc0, 0xf0, 0x7f, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc3, 0xff, 0x83, 0xc0, 0xf0, 0x7f,
    0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
    0xc3, 0xff, 0x83, 0xc0, 0xe0, 0xff, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc3, 0xff, 0x83, 0xc0, 0xe0, 0xff, 0xe0, 0x7f, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc3, 0xff, 0x81, 0xc0,
    0xe0, 0xff, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1f, 0xc1, 0xff, 0x81, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0,
    0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xe0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0xc0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0xe0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x03, 0xc0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0,
    0xe0, 0x00, 0x30, 0x00, 0x06, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00,
    0x38, 0x00, 0x03, 0x00, 0x03, 0xc0, 0xe0, 0x01, 0xfe, 0x00, 0x3f, 0xc0, 0x03, 0xfc, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0xfe, 0x00, 0x1f, 0xe0, 0x03, 0xc0, 0xe0, 0x03, 0x8f, 0x00,
    0x78, 0xe0, 0x07, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x78, 0x01, 0xc7, 0x80, 0x3c, 0x70,
    0x03, 0xc0, 0xe0, 0x06, 0x03, 0x80, 0xe0, 0x70, 0x0e, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
    0x1c, 0x03, 0x01, 0x80, 0x70, 0x38, 0x03, 0xc0, 0xf0, 0x0e, 0x01, 0x80, 0xc0, 0x38, 0x0c, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x0c, 0x06, 0x00, 0xc0, 0x60, 0x1c, 0x03, 0xc0, 0xf8, 0x0c,
    0x00, 0xc1, 0x80, 0x18, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x60, 0x06, 0x06, 0x00, 0xc0,
    0xc0, 0x0c, 0x07, 0xc0, 0xfc, 0x0c, 0x00, 0xc1, 0x80, 0x18, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x60, 0x06, 0x06, 0x00, 0x60, 0xc0, 0x0c, 0x1f, 0xc0, 0xff, 0xfc, 0x00, 0xc1, 0x80, 0x18,
    0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x60, 0x06, 0x06, 0x00, 0x60, 0xc0, 0x0f, 0xff, 0xc0,
    0xff, 0xfc, 0x00, 0xc1, 0x80, 0x18, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x60, 0x06, 0x06,
    0x00, 0x60, 0xc0, 0x0f, 0xff, 0xc0, 0xff, 0xfc, 0x00, 0xff, 0x80, 0x1f, 0xf8, 0x01, 0x80, 0x00,
    0x00, 0x00, 0x00, 0xe0, 0x07, 0xfe, 0x00, 0xff, 0xc0, 0x0f, 0xff, 0xc0, 0xff, 0xfe, 0x01, 0xff,
    0xc0, 0x3f, 0xfc, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xfe, 0x00, 0xff, 0xe0, 0x1f,
    0xff, 0xc0, 0xff, 0xff, 0x03, 0xff, 0xe0, 0x7f, 0xfe, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
    0x1f, 0xff, 0x01, 0xff, 0xf0, 0x3f, 0xff, 0xc0, 0xff, 0xff, 0xcf, 0xff, 0xf9, 0xff, 0xff, 0x9f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xe7, 0xff, 0xfc, 0xff, 0xff, 0xc0
};

// 'light_off', 42x44px
const unsigned char bulbOff [] PROGMEM = {
  0xff, 0xff, 0xf3, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xc0, 0xff, 0xc7, 0xf3, 0xf9,
  0xff, 0xc0, 0xff, 0xc7, 0xf3, 0xf8, 0xff, 0xc0, 0xff, 0xe3, 0xf3, 0xf1, 0xff, 0xc0, 0xff, 0xe3,
  0xff, 0xf1, 0xff, 0xc0, 0xff, 0xf3, 0xff, 0xf3, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,
  0xe7, 0xff, 0xe1, 0xff, 0xfb, 0xc0, 0xe3, 0xfe, 0x00, 0x3f, 0xe1, 0xc0, 0xe0, 0xfc, 0x00, 0x0f,
  0xc1, 0xc0, 0xf0, 0xf0, 0x3e, 0x07, 0xc3, 0xc0, 0xfd, 0xe0, 0xff, 0xc3, 0xcf, 0xc0, 0xff, 0xe1,
  0xff, 0xe1, 0xff, 0xc0, 0xff, 0xc3, 0xff, 0xf0, 0xff, 0xc0, 0xff, 0xc7, 0xff, 0xf8, 0xff, 0xc0,
  0xff, 0x8f, 0xff, 0xf8, 0xff, 0xc0, 0xff, 0x8f, 0xff, 0xfc, 0x7f, 0xc0, 0x03, 0x8f, 0xff, 0xfc,
  0x70, 0x00, 0x03, 0x8f, 0xff, 0xfc, 0x70, 0x00, 0x03, 0x8f, 0xff, 0xfc, 0x70, 0x00, 0xff, 0x8f,
  0xff, 0xfc, 0x7f, 0xc0, 0xff, 0x8f, 0xff, 0xfc, 0x7f, 0xc0, 0xff, 0xcf, 0xff, 0xf8, 0xff, 0xc0,
  0xff, 0xc7, 0xff, 0xf8, 0xff, 0xc0, 0xff, 0xc7, 0xff, 0xf0, 0xff, 0xc0, 0xfd, 0xe3, 0xff, 0xf1,
  0xef, 0xc0, 0xe0, 0xe1, 0xff, 0xe1, 0xc3, 0xc0, 0xc0, 0xf1, 0xff, 0xe3, 0xc0, 0xc0, 0xc3, 0xf0,
  0xff, 0xc7, 0xf0, 0xc0, 0xef, 0xf8, 0xff, 0xc7, 0xfd, 0xc0, 0xff, 0xfc, 0x7f, 0x8f, 0xff, 0xc0,
  0xff, 0xfc, 0x7f, 0x8f, 0xff, 0xc0, 0xff, 0xfc, 0x7f, 0x1f, 0xff, 0xc0, 0xff, 0xfe, 0x3f, 0x1f,
  0xff, 0xc0, 0xff, 0xfe, 0x3f, 0x1f, 0xff, 0xc0, 0xff, 0xfe, 0x3f, 0x1f, 0xff, 0xc0, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xc0, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xc0,
  0xff, 0xff, 0x80, 0x7f, 0xff, 0xc0, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xc0, 0xff, 0xff, 0x00, 0x3f,
  0xff, 0xc0, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xc0
};
// 'light_on', 42x44px
const unsigned char bulbOn [] PROGMEM = {
  0xff, 0xff, 0xf3, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xc0, 0xff, 0xc7, 0xf3, 0xf9,
  0xff, 0xc0, 0xff, 0xc7, 0xf3, 0xf8, 0xff, 0xc0, 0xff, 0xe3, 0xf3, 0xf1, 0xff, 0xc0, 0xff, 0xe3,
  0xff, 0xf1, 0xff, 0xc0, 0xff, 0xf3, 0xff, 0xf3, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,
  0xe7, 0xff, 0xe1, 0xff, 0xfb, 0xc0, 0xe3, 0xfe, 0x00, 0x3f, 0xe1, 0xc0, 0xe0, 0xfc, 0x00, 0x0f,
  0xc1, 0xc0, 0xf0, 0xf0, 0x00, 0x07, 0xc3, 0xc0, 0xfd, 0xe0, 0x00, 0x03, 0xcf, 0xc0, 0xff, 0xe0,
  0x00, 0x01, 0xff, 0xc0, 0xff, 0xc0, 0x00, 0x00, 0xff, 0xc0, 0xff, 0xc0, 0x00, 0x00, 0xff, 0xc0,
  0xff, 0x80, 0x00, 0x00, 0xff, 0xc0, 0xff, 0x80, 0x00, 0x00, 0x7f, 0xc0, 0x03, 0x80, 0x00, 0x00,
  0x70, 0x00, 0x03, 0x80, 0x00, 0x00, 0x70, 0x00, 0x03, 0x80, 0x00, 0x00, 0x70, 0x00, 0xff, 0x80,
  0x00, 0x00, 0x7f, 0xc0, 0xff, 0x80, 0x00, 0x00, 0x7f, 0xc0, 0xff, 0xc0, 0x00, 0x00, 0xff, 0xc0,
  0xff, 0xc0, 0x00, 0x00, 0xff, 0xc0, 0xff, 0xc0, 0x00, 0x00, 0xff, 0xc0, 0xfd, 0xe0, 0x00, 0x01,
  0xef, 0xc0, 0xe0, 0xe0, 0x00, 0x01, 0xc3, 0xc0, 0xc0, 0xf0, 0x00, 0x03, 0xc0, 0xc0, 0xc3, 0xf0,
  0x00, 0x07, 0xf0, 0xc0, 0xef, 0xf8, 0x00, 0x07, 0xfd, 0xc0, 0xff, 0xf8, 0x00, 0x0f, 0xff, 0xc0,
  0xff, 0xfc, 0x00, 0x0f, 0xff, 0xc0, 0xff, 0xfc, 0x00, 0x1f, 0xff, 0xc0, 0xff, 0xfe, 0x00, 0x1f,
  0xff, 0xc0, 0xff, 0xfe, 0x00, 0x1f, 0xff, 0xc0, 0xff, 0xfe, 0x00, 0x1f, 0xff, 0xc0, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xc0,
  0xff, 0xff, 0x00, 0x3f, 0xff, 0xc0, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xc0, 0xff, 0xff, 0x00, 0x3f,
  0xff, 0xc0, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xc0
};

/**
 * Background of function symbol.
 */
const unsigned char FuntionBackgroundBitmap[]
    = { 0xfc, 0x3, 0xf0, 0xf8, 0x1, 0xf0, 0xf0, 0x0, 0xf0, 0xe0, 0x0, 0x70, 0xc0, 0x0, 0x30, 0x80, 0x0, 0x10, 0x0, 0x0,
          0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
          0x80, 0x0, 0x10, 0xc0, 0x0, 0x30, 0xe0, 0x0, 0x70, 0xf0, 0x0, 0xf0, 0xf8, 0x1, 0xf0, 0xfc, 0x3, 0xf0 };


// 'wifi', 24x24px
const unsigned char wifi [] PROGMEM = {
  0xff, 0x00, 0xff, 0xf8, 0x00, 0x1f, 0xf0, 0x00, 0x0f, 0xe0, 0xff, 0x07, 0xc3, 0xff, 0xc3, 0x87,
  0xff, 0xe1, 0x1f, 0xff, 0xf8, 0x3f, 0x81, 0xfc, 0x7e, 0x00, 0x7e, 0xf8, 0x00, 0x1f, 0xf0, 0xfe,
  0x0f, 0xe1, 0xff, 0x87, 0xc3, 0xff, 0xc3, 0xc7, 0xff, 0xe3, 0xff, 0xc3, 0xff, 0xff, 0x00, 0xff,
  0xfe, 0x00, 0x7f, 0xfc, 0x7e, 0x3f, 0xfc, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff,
  0xc3, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xe7, 0xff
};
// 'wifi_100', 24x8px
const unsigned char wifi_100 [] PROGMEM = {
  0xff, 0x00, 0xff, 0xf8, 0x00, 0x1f, 0xf0, 0x00, 0x0f, 0xe0, 0xff, 0x07, 0xc3, 0xff, 0xc3, 0x87,
  0xff, 0xe1, 0x1f, 0xff, 0xf8, 0x3f, 0x81, 0xfc
};
// 'wifi_66', 20x7px
const unsigned char wifi_66 [] PROGMEM = {
  0xfe, 0x07, 0xf0, 0xf8, 0x01, 0xf0, 0xe0, 0x00, 0x70, 0xc3, 0xf8, 0x30, 0x87, 0xfe, 0x10, 0x0f,
  0xff, 0x00, 0x1f, 0xff, 0x80
};
// 'wifi_33', 12x5px
const unsigned char wifi_33 [] PROGMEM = {
  0xf0, 0xf0, 0xc0, 0x30, 0x80, 0x10, 0x1f, 0x80, 0x3f, 0xc0
};
// 'wifi_0', 4x4px
const unsigned char wifi_0 [] PROGMEM = {
  0x90, 0x00, 0x00, 0x90
};

// 'z21Connect', 22x22px
const unsigned char z21Icon [] PROGMEM = {
  0xc0, 0x00, 0x0c, 0xdf, 0xff, 0xec, 0xdf, 0xff, 0xec, 0xd8, 0x1f, 0xec, 0xdb, 0xde, 0x6c, 0xdb,
  0xdc, 0x2c, 0xdb, 0xdc, 0x2c, 0xdb, 0xde, 0x6c, 0xd8, 0x1f, 0xec, 0xdf, 0xff, 0xec, 0xdf, 0xff,
  0xec, 0xc0, 0x00, 0x0c, 0xff, 0xcf, 0xfc, 0xff, 0xcf, 0xfc, 0xff, 0xcf, 0xfc, 0xff, 0xcf, 0xfc,
  0xff, 0x87, 0xfc, 0xff, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0xfc, 0xff,
  0x87, 0xfc
};

#endif
