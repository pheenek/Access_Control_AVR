/**
 * @file 		access_ctl_display.h
 *
 * @author 		Stephen Kairu (kairu@pheenek.com)
 *
 * @brief	    This file contains the definitions for interfacing to the display
 *            The display for this application is a 1.3 inch OLED display, resolution: 128x64
 *
 * @version 	0.1
 *
 * @date 		2023-09-21
 *
 * ***************************************************************************
 * @copyright Copyright (c) 2023, Stephen Kairu
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the “Software”), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ***************************************************************************
 *
 */
#ifndef ACCESS_CTL_DISPLAY_H
#define ACCESS_CTL_DISPLAY_H

#include "U8glib.h"

/**
 * Enumeration defining all the screens that are part of the user interface
 */
typedef enum SCREENS : int8_t
{
    DEFAULT_SCREEN = 0,
    ERROR_SCREEN,
    PIN_ERROR_SCREEN,
    PIN_SUCCESS_SCREEN,
    SUCCESS_SCREEN,
    PASS_SCREEN,
    MENU_SCREEN,
    FINGERPRINT_DB_SCREEN,
    ADD_FINGERPRINT_SCREEN,
    RM_FINGERPRINT_SCREEN,
    DOOR_SCREEN,
    DOOR_OPEN_SCREEN,
    DOOR_CLOSE_SCREEN,
    CHANGE_PIN_SCREEN,
    CHANGE_PIN_ERROR_SCREEN,
    CHANGE_PIN_SUCCESS_SCREEN
} Screen_t;

/**
 * Enueration defining all the menus that are accessible as part of the user interface
 */
typedef enum MENU_MAX : int8_t
{
    DEFAULT_MAX = 0,
    MAIN_MENU_MAX = 3,
    FINGERPRINT_DB_MENU_MAX = 3,
    DOOR_MENU_MAX = 3,
    DOOR_OPEN_MAX = 2,
    DOOR_CLOSE_MAX = 2
} MenuMax_t;

/**
 * Enumeration defining all the PIN (4-digit security code) screens that are accessible as part
 * of the user interface
 */
typedef enum PIN_SCREENS : int8_t
{
    PIN_SCREEN,
    CURRENT_PIN_SCREEN,
    CHANGE_PIN_1,
    CHANGE_PIN_2
} PinScreens_t;

/**
 * Enumeration defining the number of PIN characters in form of steps
 * Used to track how many characters have been input so far
 */
typedef enum PIN_CHARS : int8_t
{
    ZERO_CHARS = 0,
    ONE_CHAR,
    TWO_CHARS,
    THREE_CHARS,
    FOUR_CHARS
} PinChars_t;

/**
 * Enumeration defining the steps the user interface should go through to add
 * a user's fingerprint to the system
 */
typedef enum ADD_FINGER_STEPS : uint8_t
{
    STEPS_NONE,
    INITIAL_CAPTURE_PROMPT,
    CAPTURE_SUCCESS,
    CAPTURE_ERROR,
    CONVERSION_ERROR,
    REMOVE_FINGER_PROMPT,
    REPEAT_CAPTURE_PROMPT,
    MATCH_SUCCESS,
    MATCH_ERROR,
    SAVE_SUCCESS,
    SAVE_ERROR
} AddFingerSteps_t;

/**
 * A diaplay class defining the attributes, behaviour and interfaces of the system display
 */
class AccessCtlDisplay
{
private:
    U8GLIB_SH1106_128X64 *u8g; /*< Instance of the U8G Graphics library that manages low-level control of the OLED display */

    int8_t SELECTED_MENU_ITEM = 0;                      /*< Keeps track of currently selected menu item */
    Screen_t currentScreen = DEFAULT_SCREEN;            /*< Keeps track of the currently displayed UI screen */
    MenuMax_t currentMenuMax = DEFAULT_MAX;             /*< Keeps track of the number of items on the current menu */
    PinChars_t numPinCharsInput = ZERO_CHARS;           /*< Keeps track of the number of pin characters already input */
    PinScreens_t currentPinScreen = PIN_SCREEN;         /*< Keeps track of the current screen for pin configuration */
    AddFingerSteps_t addFingerCurrentStep = STEPS_NONE; /*< Keeps track of the current step in the fingerprint registration process */

    /**
     * @brief   Clears the display
     *
     * @param none
     * @return none
     */
    void clearScreen(void);

    /**
     * @brief	 Draws a menu screen
     * 
     * @param none
     * @return none
     */
    void drawSelectionScreen(void);

    /**
     * @brief	 Draws the pin (security code) screen
     * 
     * @param none
     * @return none
     */
    void drawPassScreen(void);

    /**
     * @brief	 Draws a status/information display screen
     * 
     * @param none
     * @return none
     */
    void drawStatusScreen(void);

    /**
     * @brief	 Draws a fingerprint registration screen
     * 
     * @param none
     * @return none
     */
    void drawAddFingerScreen(void);

    /**
     * @brief	 Draws the fingerprint delete screen
     * 
     * @param none
     * @return none
     */
    void drawRmFingerScreen(void);

public:
    /**
     * @brief	Display constructor
     *          Sets up the display (OLED) hardware interface and configures display parameters:
     *          font, font size, display orientation (rotation)
     * 
     * @param none
     * @return none
     */
    AccessCtlDisplay(void)
    {
        u8g = new U8GLIB_SH1106_128X64(U8G_I2C_OPT_NONE);
        u8g->setFont(u8g_font_gdr12);
        u8g->setFontRefHeightText();
        u8g->setFontPosTop();
        u8g->setRot180();
    }

    /**
     * @brief	Destroy the Access Ctl Display object 
     */
    ~AccessCtlDisplay(void) {}

    /**
     * @brief	 Main loop for the diaplay object instance
     *          Should be called periodically (frequently) to update the display
     * 
     * @param none
     * @return none
     */
    void displayLoop(void);

    /**
     * @brief	 Updates the display. Called within the displayLoop to update the display screen
     * 
     * @param none
     * @return none
     */
    void updateAccessDisplay(void);

    /**
     * @brief	Scrolls down on menu items 
     *          Highlights the next item on the menu
     * 
     * @param none
     * @return none
     */
    void scrollDown(void);

    /**
     * @brief	 Scrolls up on menu items
     *           Highlights the previous item on the menu
     * 
     * @param none
     * @return none
     */
    void scrollUp(void);

    /**
     * @brief	 Handles selection of the current menu item and switches the display to the appropriate screen
     * 
     * @param none
     * @return none
     */
    void selectItem(void);

    /**
     * @brief	Returns the index of the currently selected menu item
     * 
     * @param none
     * @return int8_t 
     */
    int8_t getSelectedMenuItem(void);

    /**
     * @brief	 Handles switching the display to the main menu
     * 
     * @param none
     * @return none
     */
    void openMainMenu(void);

    /**
     * @brief	 Handles switching the display to the pin (security code screen)
     * 
     * @param none
     * @return none
     */
    void openPassScreen(void);

    /**
     * @brief	Returns the screen currently on display (enum value)
     * 
     * @param none
     * @return Screen_t 
     */
    Screen_t getCurrentScreen(void);

    /**
     * @brief	Switches the current screen to the screen passed as a parameter
     * 
     * @param screen 
     * @param max 
     */
    void setCurrentScreen(Screen_t screen, MenuMax_t max = DEFAULT_MAX);

    /**
     * @brief	Returns the current number of characters input on the pin (security code) screem
     * 
     * @param none
     * @return PinChars_t 
     */
    PinChars_t getNumCharsInput(void);

    /**
     * @brief	Returns the pin (security code) screem currently on display (enum value)
     * 
     * @param none
     * @return PinScreens_t 
     */
    PinScreens_t getCurrentPinScreen(void);

    /**
     * @brief	Switches the current pin (security code) screen on display to the pin screen
     *          passed as a parameter
     * 
     * @param pinScreen 
     * @return none
     */
    void setCurrentPinScreen(PinScreens_t pinScreen);

    /**
     * @brief	 Increments the number of pin (security code) characters that have been keyed-in
     * 
     * @param none
     * @return none
     */
    void addPinCharInput(void);

    /**
     * @brief	 Resets the number of pin (security code) characters that have been keyed-in to zero
     * 
     * @param none
     * @return none
     */
    void resetPinChars(void);

    /**
     * @brief	Returns the current step in the fingerprint registration process
     * 
     * @param none
     * @return AddFingerSteps_t 
     */
    AddFingerSteps_t getEnrollFingerStep(void);

    /**
     * @brief	Sets the current step in the fingerprint registratin process to the step specified
     * 
     * 
     * @param step 
     * @return none
     */
    void setEnrollFingerStep(AddFingerSteps_t step);
};

#endif
