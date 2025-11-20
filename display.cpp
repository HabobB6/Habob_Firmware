#include "display.h"

// ========== GLOBAL DISPLAY OBJECT ==========
TFT_eSPI tft = TFT_eSPI();
uint16_t tftWidth  = 320;
uint16_t tftHeight = 240;

// ========== INIT DISPLAY ==========
void initDisplay() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(COLOR_BG);
}

// ========== BASIC SET DISPLAY ==========
void setDisplay(int x, int y, uint16_t color, uint8_t size, uint16_t bg) {
    tft.setCursor(x, y);
    tft.setTextColor(COLOR_BG);
    tft.setTextSize(size);
}

// ========== DRAW SMALL ICONS ==========
void drawBatteryIcon(int x, int y, uint8_t percent) {
    // Outline
       tft.drawRoundRect(tftWidth - 43, 6, 36, 19, 2,COLOR_BG); // (bolder border)
    tft.drawRoundRect(tftWidth - 42, 7, 34, 17, 2, COLOR_BG);
    tft.setTextSize(FP);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawRightString((int bat == 100 ? "" : " ") + String(bat) + "%", tftWidth - 45, 12, 1);
    tft.fillRoundRect(tftWidth - 40, 9, 30 * bat / 100, 13, 2,TFT_CYAN);
    tft.drawLine(tftWidth - 30, 9, tftWidth - 30, 9 + 13, COLOR_BG);
    tft.drawLine(tftWidth - 20, 9, tftWidth - 20, 9 + 13, COLOR_BG);
    // Fill depending on percentage
}

void drawClockIcon(int x, int y) {
    tft.drawCircle(x + 8, y + 8, 7, COLOR_TEXT);
    tft.drawLine(x + 8, y + 8, x + 8, y + 4, COLOR_TEXT); // hour
    tft.drawLine(x + 8, y + 8, x + 12, y + 8, COLOR_TEXT); // minute
}
void drawWifiIcon(int x, int y){
    tft.fillRect(x, y, 16, 16, COLOR_BG);
    tft.fillCircle(9 + x, 14 + y, 1, COLOR_PRI);
    tft.drawArc(9 + x, 14 + y, 4, 6, 130, 230, COLOR_PRI, COLOR_BG);
    tft.drawArc(9 + x, 14 + y, 10, 12, 130, 230, COLOR_PRI, COLOR_BG);
}
void drawSettingsIcon(int x, int y){

}

// ========== STATUS BAR ==========
void drawStatusBar(uint8_t battery, const char* timeStr) {
    tft.fillRect(0, 0, tftWidth, 20, COLOR_BG);

    // Battery
    drawBatteryIcon(tftWidth - 28, 4, battery);

    // Clock
    setDisplay(5, 4, COLOR_TEXT, 1, COLOR_BG);
    tft.print(timeStr);

    // Separator line
    tft.drawLine(0, 20, tftWidth, 20, COLOR_PRI);
}

// ========== BORDER ==========
void drawMainBorder(bool clearScreen) {
    if (clearScreen) {
        tft.fillScreen(COLOR_BG);
    }

    // Purple outer border
    tft.drawRoundRect(3, 3, tftWidth - 6, tftHeight - 6, 6, COLOR_PRI);

    // Top bar is drawn by user separately (drawStatusBar)
}

void drawMainBorderWithTitle(String title, bool clearScreen) {
    drawMainBorder(clearScreen);
    printTitle(title);
}

// ========== TITLES ==========
void printTitle(String title) {
    setDisplay(0, 25, COLOR_PRI, 2, COLOR_BG);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(title, tftWidth / 2, 38);
    tft.setTextDatum(TL_DATUM);
}

void printSubtitle(String subtitle, bool underline) {
    setDisplay(0, 65, COLOR_TEXT, 1, COLOR_BG);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(subtitle, tftWidth / 2, 70);

    if (underline) {
        tft.drawLine(20, 82, tftWidth - 20, 82, COLOR_PRI);
    }

    tft.setTextDatum(TL_DATUM);
}

void printCenterMessage(String text) {
    setDisplay(0, tftHeight / 2, COLOR_TEXT, 2, COLOR_BG);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(text, tftWidth / 2, tftHeight / 2);
    tft.setTextDatum(TL_DATUM);
}

// ========== FOOTER ==========
void printFooter(String text) {
    tft.fillRect(0, tftHeight - 20, tftWidth, 20, COLOR_BG);
    tft.setTextDatum(MC_DATUM);
    setDisplay(0, 0, COLOR_TEXT, 1, COLOR_BG);
    tft.drawString(text, tftWidth / 2, tftHeight - 10);
    tft.setTextDatum(TL_DATUM);
}

// ========== BOOT SCREEN ==========
void drawBootScreen() {
    tft.fillScreen(COLOR_BG);

    // Center boot title
    setDisplay(0, 0, COLOR_PRI, 2, COLOR_BG);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("MINI OS", tftWidth / 2, tftHeight / 2 - 20);

    // Loading bar
    tft.drawRect(40, tftHeight / 2 + 10, tftWidth - 80, 10, COLOR_PRI);
    tft.fillRect(42, tftHeight / 2 + 12, tftWidth - 84, 6, COLOR_PRI);
    delay(800);

    tft.setTextDatum(TL_DATUM);
}

// ========== MAIN MENU ==========
void drawMainMenu(uint8_t selected) {
    drawMainBorder(true);
    printTitle("MAIN MENU");

    const char* items[] = {
        "WiFi Scanner",
        "Clock",
        "Settings",
        "About"
    };

    int y = 90;
    for (int i = 0; i < 4; i++) {
        if (i == selected) {
            tft.fillRect(20, y - 4, tftWidth - 40, 22, COLOR_PRI);
            setDisplay(30, y, COLOR_BG, 2, COLOR_PRI);
        } else {
            setDisplay(30, y, COLOR_TEXT, 2, COLOR_BG);
        }
        tft.print(items[i]);
        y += 30;
    }

    printFooter("Use buttons to navigate");
}

// ========== WIFI PAGE ==========
void drawWifiPage() {
    drawMainBorder(true);
    printTitle("WIFI SCAN");

    setDisplay(10, 80, COLOR_TEXT, 1, COLOR_BG);
    tft.println("Press SCAN to search networks...");
}

// ========== CLOCK PAGE ==========
void drawClockPage() {
    drawMainBorder(true);
    printTitle("CLOCK");

    setDisplay(0, tftHeight / 2 - 10, COLOR_TEXT, 3, COLOR_BG);
    tft.setTextDatum(MC_DATUM);

    // Example only, actual time comes from RTC or millis
    tft.drawString("12:45", tftWidth / 2, tftHeight / 2);

    tft.setTextDatum(TL_DATUM);
}

// ========== POPUP ==========
void popupMessage(String title, String subtitle, uint16_t ms) {
    tft.fillRoundRect(20, 100, tftWidth - 40, 120, 8, COLOR_PRI);
    tft.drawRoundRect(20, 100, tftWidth - 40, 120, 8, COLOR_TEXT);

    setDisplay(0, 0, COLOR_BG, 2, COLOR_PRI);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(title, tftWidth / 2, 130);

    setDisplay(0, 0, COLOR_BG, 1, COLOR_PRI);
    tft.drawString(subtitle, tftWidth / 2, 170);

    tft.setTextDatum(TL_DATUM);

    delay(ms);
}
