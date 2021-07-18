#include "Display_functions.hpp"

/* ===================================================================== *
 *                                                                       *
 * Menu Callback Function                                                *
 *                                                                       *
 * ===================================================================== *
 *
 * EXAMPLE CODE:
// *********************************************************************
void your_function_name(uint8_t param)
// *********************************************************************
{
    if(LCDML.FUNC_setup())          // ****** SETUP *********
    {
        // remmove compiler warnings when the param variable is not used:
        //LCDML_UNUSED(param);
        // setup
        // is called only if it is started
        // starts a trigger event for the loop function every 100 milliseconds
        LCDML.FUNC_setLoopInterval(100);
        // uncomment this line when the menu should go back to the last called position
        // this could be a cursor position or the an active menu function
        // GBA means => go back advanced
        //LCDML.FUNC_setGBA() 
        //
    }
    if(LCDML.FUNC_loop())           // ****** LOOP *********
    {
        // loop
        // is called when it is triggered
        // - with LCDML_DISP_triggerMenu( milliseconds )
        // - with every button or event status change
        // uncomment this line when the screensaver should not be called when this function is running
        // reset screensaver timer
        //LCDML.SCREEN_resetTimer();
        // check if any button is pressed (enter, up, down, left, right)
        if(LCDML.BT_checkAny()) {
            LCDML.FUNC_goBackToMenu();
        }
    }
    if(LCDML.FUNC_close())      // ****** STABLE END *********
    {
        // loop end
        // you can here reset some global vars or delete it
        // this function is always called when the functions ends.
        // this means when you are calling a jumpTo ore a goRoot function
        // that this part is called before a function is closed
    }
}
 * ===================================================================== *
 */

void printTemp(void)
{
    lcd.setCursor(2, 0);
    lcd.print("--.-/--\337C");
}

uint32_t remaining_led_time = 0;
char tmp_time_string[3];
uint32_t last_light_timer_update = 0;
bool screensaver_timer_light_off = false;
void printLight(void)
{
    last_light_timer_update = millis();
    lcd.setCursor(15, 0);

    if (!ledLighting.isOn())
    {
        screensaver_timer_light_off = true;
        lcd.print("aus  ");
    }
    else
    {
        remaining_led_time = ledLighting.getTimestamp();

        screensaver_timer_light_off = false;
        remaining_led_time -= millis();

        snprintf(tmp_time_string, 3, "%02d", (int16_t)(remaining_led_time / 60000));
        lcd.print(tmp_time_string);

        lcd.print(":");

        snprintf(tmp_time_string, 3, "%02d", (int16_t)((remaining_led_time / 1000) % 60));
        lcd.print(tmp_time_string);
    }
}

bool last_mode_auto_off = false;
void printMode(void)
{
    last_mode_auto_off = enclosurePower.isAutoOff();

    lcd.setCursor(7, 1);
    if (last_mode_auto_off)
    {
        lcd.print("Auto aus");
    }
    else
    {
        lcd.print("Copycat ");
    }
}

bool last_state_internal_vent = false;
void printInternalVentilationState(void)
{
    last_state_internal_vent = ventilation.isEnclosureVentilationOn();

    lcd.setCursor(16, 2);
    if (last_state_internal_vent)
    {
        lcd.print("an ");
    }
    else
    {
        lcd.print("aus");
    }
}

bool last_state_external_vent = false;
void printExternalVentilationState(void)
{
    last_state_external_vent = ventilation.isExternalVentilationReq();

    lcd.setCursor(16, 3);
    if (last_state_external_vent)
    {
        lcd.print("an ");
    }
    else
    {
        lcd.print("aus");
    }
}

void printScreensaver(bool redraw)
{
    if (redraw)
    {
        // temperature
        lcd.setCursor(0, 0);
        lcd.write(byte(0x05));
        printTemp();

        // light
        lcd.setCursor(13, 0);
        lcd.write(byte(0x06));
        printLight();

        lcd.setCursor(0, 1);
        lcd.print("Modus:");
        printMode();

        lcd.setCursor(0, 2);
        lcd.print("L\365ftung intern:");
        printInternalVentilationState();

        lcd.setCursor(0, 3);
        lcd.print("L\365ftung extern:");
        printExternalVentilationState();
    }
    else
    {
        // update light
        if (ledLighting.getTimestamp() > millis() && millis() >= (last_light_timer_update + 1000))
        {
            printLight();
        }
        else if (!screensaver_timer_light_off)
        {
            printLight();
        }

        // update mode
        if (last_mode_auto_off != enclosurePower.isAutoOff())
        {
            printMode();
        }

        // update internal ventilation
        if (last_state_internal_vent != ventilation.isEnclosureVentilationOn())
        {
            printInternalVentilationState();
        }

        // update external ventilation
        if (last_state_external_vent != ventilation.isExternalVentilationReq())
        {
            printExternalVentilationState();
        }
    }
}

void mFunc_screensaver(uint8_t param)
{
    if (LCDML.FUNC_setup()) // ****** SETUP *********
    {
        // remmove compiler warnings when the param variable is not used:
        LCDML_UNUSED(param);

        // update LCD content
        printScreensaver(true);
        LCDML.FUNC_setLoopInterval(100); // starts a trigger event for the loop function every 100 milliseconds
    }

    else if (LCDML.FUNC_loop())
    {
        printScreensaver(false);
        if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
        {
            LCDML.FUNC_goBackToMenu(); // leave this function
        }
    }

    else if (LCDML.FUNC_close())
    {
        // The screensaver go to the root menu
        LCDML.MENU_goRoot();
    }
}

bool menu_item_turn_off_light_visible = false;
void mFunc_turnOnLight(uint8_t param)
{
    if (LCDML.FUNC_setup()) // ****** SETUP *********
    {
        // remmove compiler warnings when the param variable is not used:
        LCDML_UNUSED(param);
        ledLighting.setOn(millis());

        // update menu to add "Light off"
        menu_item_turn_off_light_visible = true;
        LCDML.MENU_allCondetionRefresh();
        LCDML.DISP_update();

        // leave this function
        LCDML.FUNC_goBackToMenu();
        LCDML.SCREEN_start();
    }
}

void mFunc_turnOffLight(uint8_t param)
{
    if (LCDML.FUNC_setup()) // ****** SETUP *********
    {
        // remmove compiler warnings when the param variable is not used:
        LCDML_UNUSED(param);
        ledLighting.setOff();

        // update menu to remove "Light off"
        LCDML.MENU_allCondetionRefresh();
        LCDML.DISP_update();

        // leave this function
        LCDML.FUNC_goBackToMenu();
        LCDML.SCREEN_start();
    }
}

void mFunc_changeMode(uint8_t param)
{
    if (LCDML.FUNC_setup()) // ****** SETUP *********
    {
        switch (param)
        {
        case 0: // Enable auto-off
            enclosurePower.enableAutoOff();

            // update menu
            LCDML.MENU_allCondetionRefresh();
            LCDML.DISP_update();

            // leave this function
            LCDML.FUNC_goBackToMenu();
            LCDML.SCREEN_start();

            break;

        case 1: // Enable copycat
            enclosurePower.disableAutoOff();

            // update menu
            LCDML.MENU_allCondetionRefresh();
            LCDML.DISP_update();

            // leave this function
            LCDML.FUNC_goBackToMenu();
            LCDML.SCREEN_start();

            break;
        }
    }
}

uint32_t remaining_shutdown_time = 0;
char tmp_shutdown_time_string[3];
uint32_t last_shutdown_timer_update = 0;
bool shutdown_popup_active = false;
void printShutdownPopup(bool redraw)
{
    last_shutdown_timer_update = millis();

    if (redraw)
    {
        lcd.setCursor(3, 0);
        lcd.print("Ausschalten in");
        lcd.setCursor(4, 3);
        lcd.print("<Abbrechen>");
    }

    remaining_shutdown_time = enclosurePower.getShutdownTimer(millis());

    lcd.setCursor(7, 1);
    snprintf(tmp_shutdown_time_string, 3, "%02d", (int16_t)(remaining_shutdown_time / 60000));
    lcd.print(tmp_shutdown_time_string);

    lcd.print(":");

    snprintf(tmp_shutdown_time_string, 3, "%02d", (int16_t)((remaining_shutdown_time / 1000) % 60));
    lcd.print(tmp_shutdown_time_string);
}

void mFunc_shutdownPopup(uint8_t param)
{
    if (LCDML.FUNC_setup()) // ****** SETUP *********
    {
        // remmove compiler warnings when the param variable is not used:
        LCDML_UNUSED(param);

        lcd.turnOnBacklight(millis());

        shutdown_popup_active = true;

        // update LCD content
        printShutdownPopup(true);
        LCDML.FUNC_setLoopInterval(100); // starts a trigger event for the loop function every 100 milliseconds
        LCDML.FUNC_disableScreensaver();
    }

    else if (LCDML.FUNC_loop())
    {
        if (LCDML.BT_checkAny())
        {
            LCDML.FUNC_goBackToMenu();
        }

        // check if any event is active
        if (LCDML.CE_checkAny())
        {
            // check if the defined command char is pressed
            if (LCDML.CE_check(0))
            {
                LCDML.SCREEN_resetTimer();
                if (millis() >= (last_shutdown_timer_update + 1000))
                {
                    printShutdownPopup(false);
                }
                if (LCDML.BT_checkAny() || !enclosurePower.isShutdown()) // check if any button is pressed (enter, up, down, left, right)
                {
                    LCDML.FUNC_goBackToMenu(); // leave this function
                }
            }
        }
    }
    else if (LCDML.FUNC_close())
    {
        LCDML.CE_resetAll();

        shutdown_popup_active = false;
        enclosurePower.abort();

        LCDML.FUNC_goBackToMenu();
        LCDML.SCREEN_start();
    }
}

void updateMenuLoop(void)
{
    // remove turn off from menu
    if (!ledLighting.isOn() && menu_item_turn_off_light_visible)
    {
        menu_item_turn_off_light_visible = false;

        LCDML.MENU_allCondetionRefresh();
        LCDML.DISP_update();
    }

    // show shutdown popup
    if (enclosurePower.isShutdown() && !shutdown_popup_active)
    {
        LCDML.DISP_clear();
        LCDML.CE_set(0); // set button enter
    }
}

void mFunc_shutdown(uint8_t param)
{
    shutdown();
}
