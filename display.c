#include "display.h"
#include "icons/logo.h" // your logo image array
void draw_boot(TFT_eSPI &tft){
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_CYAN);
    tft.drawString("Habob Firmware", 120, 250);
    tft.pushImage(40, 60, 100, 70,epd_bitmap_LOGO2);
    tft.setTextColor(TFT_CYAN);
     tft.drawString("Loading...", 120, 50);
}
void main_menu(TFT_eSPI &tft, int selected){
    tft.fillScreen(TFT_BLACK);
    
    const char *items[] = {
        "Wi-Fi Scanner",
        "Clock",
        "settings"
    };
    for (int i = 0; i < 5; i++){
        int y = 60 + i *35;
        if (selected == i){ 
        tft.fillRoundRect(20, y - 5, 200, 30, 6, COLOR_MAIN);
            tft.setTextColor(TFT_BLACK, TFT_CYAN);
        } else {
            tft.setTextColor(TFT_CYAN, TFT_BLACK);
        }

        tft.drawCentreString(items[i], 120, y, 2);
    }

    tft.setTextColor(TFT_DARKGREY, COLOR_BG);
}
void wifi_menu(TFT_eSPI &tft){
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_CYAN);
    tft.drawString("Wi-Fi Scanner", 80, 20);
    // Additional Wi-Fi scanning code would go here
}
