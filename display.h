#ifndef DISPLAY_H
#define DISPLAY_H 


#include <TFT_eSPI.h>
#include <Arduino.h>

// ========== GLOBAL TFT INSTANCE ==========
extern TFT_eSPI tft;
extern uint16_t tftWidth;
extern uint16_t tftHeight;

// ========== COLORS ==========
#define COLOR_BG     TFT_BLACK //backgruond color
#define COLOR_PRI    TFT_WHITE  //selected color
#define COLOR_TEXT   TFT_CYAN  //text color

// ========== UI INITIALIZATION ==========
void initDisplay();

// ========== CORE UI HELPERS ==========
void setDisplay(int x, int y, uint16_t color, uint8_t size, uint16_t bg);

// ========== TOP STATUS BAR ==========
void drawStatusBar(uint8_t battery, const char* timeStr);

// ========== GENERAL LAYOUT ==========
void drawMainBorder(bool clearScreen);
void drawMainBorderWithTitle(String title, bool clearScreen);

// ========== TITLES / TEXT ==========
void printTitle(String title);
void printSubtitle(String subtitle, bool underline);
void printCenterMessage(String text);

// ========== FOOTER ==========
void printFooter(String text);

// ========== SMALL ICONS ==========
void drawBatteryIcon(int x, int y, uint8_t percent);
void drawClockIcon(int x, int y);
void drawWifiIcon(int x, int y);
void drawSettingsIcon(int x, int y);

// ========== PAGES ==========
void drawBootScreen();
void drawMainMenu(uint8_t selected);
void drawWifiPage();
void drawClockPage();

// ========== POPUP ==========
void popupMessage(String title, String subtitle, uint16_t ms);

#endif
