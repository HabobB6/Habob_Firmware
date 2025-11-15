#pragma _once
#include <TFT_eSPI.h>
void draw_boot(TFT_eSPI &tft);
void main_menu(TFT_eSPI &tft, int selected);
void wifi_menu(TFT_eSPI &tft);
void clock_menu(TFT_eSPI &tft);
void settings_menu(TFT_eSPI &tft);
