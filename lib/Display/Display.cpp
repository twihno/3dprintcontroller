#include "Display.hpp"

// LCD object
Printer_LiquidCrystal_I2C lcd(0x27, _LCDML_DISP_cols, _LCDML_DISP_rows);

// LCDMenuLib2 objects
LCDMenuLib2_menu LCDML_0(255, 0, 0, NULL, NULL); // root menu element (do not change)
LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
LCDML_add(0, LCDML_0, 1, "Zur\365ck", mFunc_screensaver);
LCDML_addAdvanced(1, LCDML_0, 2, COND_mode_auto_off, "Modus: [Auto aus]", mFunc_changeMode, 1, _LCDML_TYPE_default); //Immer die Nummer des nächsten Modus
LCDML_addAdvanced(2, LCDML_0, 3, COND_mode_copycat, "Modus: [Copycat]", mFunc_changeMode, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(3, LCDML_0, 4, COND_light_off, "Licht aus", mFunc_turnOffLight, 0, _LCDML_TYPE_default);
LCDML_add(4, LCDML_0, 5, "Licht an", mFunc_turnOnLight);
LCDML_add(5, LCDML_0, 6, "Ausschalten", NULL);
LCDML_add(6, LCDML_0_6, 1, "Nein", mFunc_screensaver);
LCDML_add(7, LCDML_0_6, 2, "Ja", mFunc_shutdown);

// hidden function to enable shutdown popup
LCDML_addAdvanced(8, LCDML_0, 7, COND_false, "SHUTDOWN_POPUP", mFunc_shutdownPopup, 0, _LCDML_TYPE_default);
// ***TIP*** Try to update _LCDML_DISP_cnt when you add a menu element.

// create menu
LCDML_createMenu(_LCDML_DISP_cnt);

// *********************************************************************
// SETUP
// *********************************************************************
void display_setup()
{
    // LCD Begin
    lcd.init();
    lcd.backlight();

    // set special chars for scrollbar
    lcd.createChar(0, (uint8_t *)scroll_bar[0]);
    lcd.createChar(1, (uint8_t *)scroll_bar[1]);
    lcd.createChar(2, (uint8_t *)scroll_bar[2]);
    lcd.createChar(3, (uint8_t *)scroll_bar[3]);
    lcd.createChar(4, (uint8_t *)scroll_bar[4]);

    // set special chars for screensaver
    lcd.createChar(5, (uint8_t *)custom_characters[0]); // thermometer
    lcd.createChar(6, (uint8_t *)custom_characters[1]); // lamp

    // LCDMenuLib Setup
    LCDML_setup(_LCDML_DISP_cnt);

    // Enable Menu Rollover
    // LCDML.MENU_enRollover();

    // Enable Screensaver (screensaver menu function, time to activate in ms)
    LCDML.SCREEN_enable(mFunc_screensaver, SCREENSAVER_TIMEOUT); // set to 10 seconds

    LCDML.MENU_allCondetionRefresh();
    LCDML.DISP_update();

    LCDML.OTHER_jumpToFunc(mFunc_screensaver);

    LCDML.CE_setOnChangeCbFunction(0, mFunc_shutdownPopup);

    lcd.turnOnBacklight(millis());
}

// *********************************************************************
// LOOP
// *********************************************************************
void display_loop()
{
    LCDML.loop();
    lcd.tick(millis());
    updateMenuLoop();
}