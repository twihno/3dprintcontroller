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

bool menu_item_turn_off_visible = false;
void updateMenuLoop(void)
{
    // remove turn off from menu
    if (!ledLighting.isOn() && menu_item_turn_off_visible)
    {
        menu_item_turn_off_visible = false;

        LCDML.MENU_allCondetionRefresh();
        LCDML.DISP_update();
    }
}

void printTemp(void)
{
    lcd.setCursor(2, 0);
    lcd.print("--.-/--\337C");
}

uint32_t remaining_time = 0;
char tmp_time_string[10];
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
        remaining_time = ledLighting.getTimestamp();

        screensaver_timer_light_off = false;
        remaining_time -= millis();

        snprintf(tmp_time_string, 3, "%02d", (int16_t)(remaining_time / 60000));
        lcd.print(tmp_time_string);

        lcd.print(":");

        snprintf(tmp_time_string, 3, "%02d", (int16_t)((remaining_time / 1000) % 60));
        lcd.print(tmp_time_string);
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

    if (LCDML.FUNC_loop())
    {
        printScreensaver(false);
        if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
        {
            LCDML.FUNC_goBackToMenu(); // leave this function
        }
    }

    if (LCDML.FUNC_close())
    {
        // The screensaver go to the root menu
        LCDML.MENU_goRoot();
    }
}

void mFunc_turnOnLight(uint8_t param)
{
    if (LCDML.FUNC_setup()) // ****** SETUP *********
    {
        // remmove compiler warnings when the param variable is not used:
        LCDML_UNUSED(param);
        ledLighting.setOn(millis());

        // update menu to add "Light off"
        menu_item_turn_off_visible = true;
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
