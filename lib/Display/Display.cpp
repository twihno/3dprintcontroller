#include "Display.hpp"

// LCD object
LiquidCrystal_I2C lcd(0x27, _LCDML_DISP_cols, _LCDML_DISP_rows);

// LCDMenuLib2 objects
LCDMenuLib2_menu LCDML_0(255, 0, 0, NULL, NULL); // root menu element (do not change)
LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************

LCDML_add(0, LCDML_0, 1, "Information", mFunc_information);                // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(1, LCDML_0, 2, "Time info", mFunc_timer_info);                   // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(2, LCDML_0, 3, "Program", NULL);                                 // NULL = no menu function
LCDML_add(3, LCDML_0_3, 1, "Program 1", NULL);                             // NULL = no menu function
LCDML_add(4, LCDML_0_3_1, 1, "P1 dummy", NULL);                            // NULL = no menu function
LCDML_add(5, LCDML_0_3_1, 2, "P1 Settings", NULL);                         // NULL = no menu function
LCDML_add(6, LCDML_0_3_1_2, 1, "Warm", NULL);                              // NULL = no menu function
LCDML_add(7, LCDML_0_3_1_2, 2, "Cold", NULL);                              // NULL = no menu function
LCDML_add(8, LCDML_0_3_1_2, 3, "Back", mFunc_back);                        // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(9, LCDML_0_3_1, 3, "Back", mFunc_back);                          // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(10, LCDML_0_3, 2, "Program 2", mFunc_p2);                        // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(11, LCDML_0_3, 3, "Back", mFunc_back);                           // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(12, LCDML_0, 4, "Special", NULL);                                // NULL = no menu function
LCDML_add(13, LCDML_0_4, 1, "Go to Root", mFunc_goToRootMenu);             // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(14, LCDML_0_4, 2, "Jump to Time info", mFunc_jumpTo_timer_info); // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(15, LCDML_0_4, 3, "Back", mFunc_back);                           // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(16, LCDML_0, 5, "Dummy B", NULL);                                // NULL = no menu function
LCDML_add(17, LCDML_0, 6, "Screensaver", mFunc_screensaver);               // this menu function can be found on "LCDML_display_menuFunction" tab
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

    // LCDMenuLib Setup
    LCDML_setup(_LCDML_DISP_cnt);

    // Enable Menu Rollover
    LCDML.MENU_enRollover();

    // Enable Screensaver (screensaver menu function, time to activate in ms)
    LCDML.SCREEN_enable(mFunc_screensaver, 10000); // set to 10 seconds
}

// *********************************************************************
// LOOP
// *********************************************************************
void display_loop()
{
    LCDML.loop();
}