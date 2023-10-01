/**
 * @file 		access_ctl_display.cpp
 *
 * @author 		Stephen Kairu (kairu@pheenek.com)
 *
 * @brief	    This file contains the implementations for interfacing to the display
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
#include "access_ctl_display.h"
#include "timing_driver.h"

unsigned long info_screen_timing = 0; /*< Used to time the length of time an info message is displayed */
uint8_t mainMenuPage = 0;			  /*< Keeps track of the page of the main menu that's currently being displayed */

/**
 * @brief	 Main loop for the diaplay object instance
 *          Should be called periodically (frequently) to update the display
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::displayLoop(void)
{
	u8g->firstPage();

	do
	{
		updateAccessDisplay();
	} while (u8g->nextPage());
}

/**
 * @brief   Clears the display
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::clearScreen(void)
{
	u8g->firstPage();

	do
	{
	} while (u8g->nextPage());
}

/**
 * @brief	Returns the screen currently on display (enum value)
 *
 * @param none
 * @return Screen_t
 */
Screen_t AccessCtlDisplay::getCurrentScreen(void)
{
	return currentScreen;
}

/**
 * @brief	Switches the current screen to the screen passed as a parameter
 *
 * @param screen
 * @param max
 */
void AccessCtlDisplay::setCurrentScreen(Screen_t screen, MenuMax_t max)
{
	currentScreen = screen;
	if ((screen == ERROR_SCREEN) || (screen == SUCCESS_SCREEN) || (screen == PIN_ERROR_SCREEN) || (screen == CHANGE_PIN_SUCCESS_SCREEN) || (screen == CHANGE_PIN_ERROR_SCREEN))
	{
		info_screen_timing = get_timing_millis();
	}
}

/**
 * @brief	 Updates the display. Called within the displayLoop to update the display screen
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::updateAccessDisplay(void)
{
	switch (currentScreen)
	{
	case MENU_SCREEN:
	case FINGERPRINT_DB_SCREEN:
	case DOOR_SCREEN:
	case DOOR_OPEN_SCREEN:
	case DOOR_CLOSE_SCREEN:
		drawSelectionScreen();
		break;
	case DEFAULT_SCREEN:
	case ERROR_SCREEN:
	case PIN_ERROR_SCREEN:
	case PIN_SUCCESS_SCREEN:
	case SUCCESS_SCREEN:
	case CHANGE_PIN_SUCCESS_SCREEN:
	case CHANGE_PIN_ERROR_SCREEN:
		drawStatusScreen();
		break;
	case PASS_SCREEN:
		drawPassScreen();
		break;
	case ADD_FINGERPRINT_SCREEN:
		drawAddFingerScreen();
		break;
	case RM_FINGERPRINT_SCREEN:
		drawRmFingerScreen();
		break;
	default:
		break;
	}
}

/**
 * @brief	 Draws a fingerprint registration screen
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::drawAddFingerScreen(void)
{
	char *display_text[2];
	uint8_t i, h;
	u8g_uint_t w, d;

	h = u8g->getFontAscent() - u8g->getFontDescent();
	w = u8g->getWidth();

	switch (addFingerCurrentStep)
	{
	case INITIAL_CAPTURE_PROMPT:
		display_text[0] = "Scan finger";
		display_text[1] = "to register";
		break;
	case CAPTURE_SUCCESS:
		display_text[0] = "Fingerprint";
		display_text[1] = "Success!";
		if ((get_timing_millis() - info_screen_timing) > 1000)
		{
			setEnrollFingerStep(REMOVE_FINGER_PROMPT);
		}
		break;
	case CAPTURE_ERROR:
		display_text[0] = "Fingerprint";
		display_text[1] = "Error!";
		if ((get_timing_millis() - info_screen_timing) > 1000)
		{
			setEnrollFingerStep(INITIAL_CAPTURE_PROMPT);
		}
		break;
	case CONVERSION_ERROR:
		display_text[0] = "Conversion";
		display_text[1] = "Error!";
		if ((get_timing_millis() - info_screen_timing) > 1000)
		{
			setEnrollFingerStep(INITIAL_CAPTURE_PROMPT);
		}
		break;
	case REMOVE_FINGER_PROMPT:
		display_text[0] = "Remove finger";
		display_text[1] = "";
		break;
	case REPEAT_CAPTURE_PROMPT:
		display_text[0] = "Place finger";
		display_text[1] = "again";
		break;
	case MATCH_SUCCESS:
		display_text[0] = "Fingerprint";
		display_text[1] = "match!";
		break;
	case MATCH_ERROR:
		display_text[0] = "Fingerprint";
		display_text[1] = "match error!";
		if ((get_timing_millis() - info_screen_timing) > 1000)
		{
			setEnrollFingerStep(INITIAL_CAPTURE_PROMPT);
		}
		break;
	case SAVE_SUCCESS:
		display_text[0] = "Fingerprint";
		display_text[1] = "saved!";
		if ((get_timing_millis() - info_screen_timing) > 1000)
		{
			setEnrollFingerStep(INITIAL_CAPTURE_PROMPT);
		}
		break;
	case SAVE_ERROR:
		display_text[0] = "Save error!";
		display_text[1] = "";
		if ((get_timing_millis() - info_screen_timing) > 1000)
		{
			setEnrollFingerStep(INITIAL_CAPTURE_PROMPT);
		}
		break;

	default:
		break;
	}

	d = (w - u8g->getStrWidth(display_text[0])) / 2;
	u8g->drawStr(d, h * 1.5, display_text[0]);

	d = (w - u8g->getStrWidth(display_text[1])) / 2;
	u8g->drawStr(d, h * 2.5, display_text[1]);
}

/**
 * @brief	 Draws the fingerprint delete screen
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::drawRmFingerScreen(void)
{
}

/**
 * @brief	 Draws a menu screen
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::drawSelectionScreen(void)
{
	char *title;
	char *options[3] = {};
	uint8_t numOptions = 0;

	switch (currentScreen)
	{
	case MENU_SCREEN:
		title = "MENU";
		if (mainMenuPage == 0)
		{
			options[0] = "Back";
			options[1] = "Fingerprint DB";
			options[2] = "Door Ctl";
		}
		else if (mainMenuPage == 1)
		{
			options[0] = "Fingerprint DB";
			options[1] = "Door Ctl";
			options[2] = "Change PIN";
		}

		numOptions = 3;
		break;
	case FINGERPRINT_DB_SCREEN:
		title = "FINGERPRINT";
		options[0] = "Back";
		options[1] = "Add Finger";
		options[2] = "Remove Finger";
		numOptions = 3;
		break;
	case DOOR_SCREEN:
		title = "DOOR CTL";
		options[0] = "Back";
		options[1] = "Open Door";
		options[2] = "Close Door";
		numOptions = 3;
		break;
	case DOOR_OPEN_SCREEN:
		title = "Open Door?";
		options[0] = "Yes";
		options[1] = "No";
		numOptions = 2;
		break;
	case DOOR_CLOSE_SCREEN:
		title = "Close Door?";
		options[0] = "Yes";
		options[1] = "No";
		numOptions = 2;
		break;
	default:
		break;
	}

	uint8_t i, h;
	u8g_uint_t w, d;

	h = u8g->getFontAscent() - u8g->getFontDescent();
	w = u8g->getWidth();

	for (i = 0; i < numOptions; i++)
	{
		d = (w - u8g->getStrWidth(options[i])) / 2;
		u8g->setDefaultForegroundColor();
		if (i == SELECTED_MENU_ITEM)
		{
			u8g->drawBox(0, (i + 1) * h, w, h);
			u8g->setDefaultBackgroundColor();
		}
		u8g->drawStr(d, (i + 1) * h, options[i]);
	}
	d = (w - u8g->getStrWidth(title)) / 2;
	u8g->drawStr(d, 0, title);
}

/**
 * @brief	Returns the index of the currently selected menu item
 *
 * @param none
 * @return int8_t
 */
int8_t AccessCtlDisplay::getSelectedMenuItem(void)
{
	return SELECTED_MENU_ITEM;
}

/**
 * @brief	Scrolls down on menu items
 *          Highlights the next item on the menu
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::scrollDown(void)
{
	if ((currentScreen == MENU_SCREEN) && (mainMenuPage == 0) && (SELECTED_MENU_ITEM == (MAIN_MENU_MAX - 1)))
	{
		// We're in the main menu screen, on the first page of the main menu and the last item on the menu is currently selected
		mainMenuPage = 1;
	}
	else
	{
		SELECTED_MENU_ITEM = ((SELECTED_MENU_ITEM + 1) < currentMenuMax) ? SELECTED_MENU_ITEM + 1 : SELECTED_MENU_ITEM;
	}
}

/**
 * @brief	 Scrolls up on menu items
 *           Highlights the previous item on the menu
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::scrollUp(void)
{
	if ((currentScreen == MENU_SCREEN) && (mainMenuPage == 1) && (SELECTED_MENU_ITEM == 0))
	{
		// We're in the main menu screen, on the second page of the main menu and the first item on the menu is currently selected
		mainMenuPage = 0;
	}
	else
	{
		SELECTED_MENU_ITEM = ((SELECTED_MENU_ITEM - 1) >= 0) ? SELECTED_MENU_ITEM - 1 : SELECTED_MENU_ITEM;
	}
}

/**
 * @brief	 Handles switching the display to the main menu
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::openMainMenu(void)
{
	mainMenuPage = 0;
	currentScreen = MENU_SCREEN;
	currentMenuMax = MAIN_MENU_MAX;
}

/**
 * @brief	 Handles switching the display to the pin (security code screen)
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::openPassScreen(void)
{
	currentScreen = PASS_SCREEN;
	currentPinScreen = PIN_SCREEN;
}

/**
 * @brief	 Draws a status/information display screen
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::drawStatusScreen(void)
{
	char *display_text[2];
	uint8_t i, h;
	u8g_uint_t w, d;

	h = u8g->getFontAscent() - u8g->getFontDescent();
	w = u8g->getWidth();

	switch (currentScreen)
	{
	case DEFAULT_SCREEN:
		display_text[0] = "Place finger";
		display_text[1] = "on scanner";
		break;
	case PIN_ERROR_SCREEN:
		if ((get_timing_millis() - info_screen_timing) > 1000)
		{
			setCurrentScreen(PASS_SCREEN);
		}
		display_text[0] = "ACCESS DENIED!";
		display_text[1] = "";
		break;
	case ERROR_SCREEN:
		if ((get_timing_millis() - info_screen_timing) > 1000)
		{
			setCurrentScreen(DEFAULT_SCREEN);
		}
		display_text[0] = "ACCESS DENIED!";
		display_text[1] = "";
		break;
	case PIN_SUCCESS_SCREEN:
		if ((get_timing_millis() - info_screen_timing) > 1000)
		{
			openMainMenu();
		}
		display_text[0] = "ACCESS GRANTED!";
		display_text[1] = "";
		break;
	case SUCCESS_SCREEN:
		if ((get_timing_millis() - info_screen_timing) > 1000)
		{
			setCurrentScreen(DEFAULT_SCREEN);
		}
		display_text[0] = "ACCESS GRANTED!";
		display_text[1] = "";
		break;
	case CHANGE_PIN_SUCCESS_SCREEN:
		if ((get_timing_millis() - info_screen_timing) > 1000)
		{
			setCurrentScreen(MENU_SCREEN);
		}
		display_text[0] = "PIN saved!";
		display_text[1] = "";
		break;
	case CHANGE_PIN_ERROR_SCREEN:
		if ((get_timing_millis() - info_screen_timing) > 1000)
		{
			setCurrentScreen(MENU_SCREEN);
		}
		display_text[0] = "PINs don't";
		display_text[1] = "match!";
		break;
	default:
		break;
	}

	d = (w - u8g->getStrWidth(display_text[0])) / 2;
	u8g->drawStr(d, h * 1.5, display_text[0]);

	d = (w - u8g->getStrWidth(display_text[1])) / 2;
	u8g->drawStr(d, h * 2.5, display_text[1]);
}

/**
 * @brief	 Increments the number of pin (security code) characters that have been keyed-in
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::addPinCharInput(void)
{
	switch (numPinCharsInput)
	{
	case ZERO_CHARS:
		numPinCharsInput = ONE_CHAR;
		break;
	case ONE_CHAR:
		numPinCharsInput = TWO_CHARS;
		break;
	case TWO_CHARS:
		numPinCharsInput = THREE_CHARS;
		break;
	case THREE_CHARS:
		numPinCharsInput = FOUR_CHARS;
		break;
	}
}

/**
 * @brief	 Resets the number of pin (security code) characters that have been keyed-in to zero
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::resetPinChars(void)
{
	numPinCharsInput = ZERO_CHARS;
}

/**
 * @brief	Returns the current number of characters input on the pin (security code) screem
 *
 * @param none
 * @return PinChars_t
 */
PinChars_t AccessCtlDisplay::getNumCharsInput(void)
{
	return numPinCharsInput;
}

/**
 * @brief	 Draws the pin (security code) screen
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::drawPassScreen(void)
{
	char *title;
	switch (currentPinScreen)
	{
	case PIN_SCREEN:
		title = "Enter PIN";
		break;
	case CURRENT_PIN_SCREEN:
		title = "Current PIN:";
		break;
	case CHANGE_PIN_1:
		title = "New PIN";
		break;
	case CHANGE_PIN_2:
		title = "Confirm PIN";
		break;
	}

	char pin_chars[8] = {0};

	uint8_t i, h;
	u8g_uint_t w, d;

	h = u8g->getFontAscent() - u8g->getFontDescent();
	w = u8g->getWidth();

	d = (w - u8g->getStrWidth(pin_chars)) / 2;
	u8g->drawStr(d, (i + 1) * h, pin_chars);

	switch (numPinCharsInput)
	{
	case ZERO_CHARS:
		strcpy(pin_chars, "|_ _ _ _");
		break;
	case ONE_CHAR:
		strcpy(pin_chars, "* |_ _ _");
		break;
	case TWO_CHARS:
		strcpy(pin_chars, "* * |_ _");
		break;
	case THREE_CHARS:
		strcpy(pin_chars, "* * * |_");
		break;
	case FOUR_CHARS:
		strcpy(pin_chars, "* * * *|");
		break;
	default:
		break;
	}
	d = (w - u8g->getStrWidth(pin_chars)) / 2;
	u8g->drawStr(d, h * 2, pin_chars);

	d = (w - u8g->getStrWidth(title)) / 2;
	u8g->drawStr(d, 0, title);
}

/**
 * @brief	Returns the pin (security code) screem currently on display (enum value)
 *
 * @param none
 * @return PinScreens_t
 */
PinScreens_t AccessCtlDisplay::getCurrentPinScreen(void)
{
	return currentPinScreen;
}

/**
 * @brief	Switches the current pin (security code) screen on display to the pin screen
 *          passed as a parameter
 *
 * @param pinScreen
 * @return none
 */
void AccessCtlDisplay::setCurrentPinScreen(PinScreens_t pinScreen)
{
	currentPinScreen = pinScreen;
}

/**
 * @brief	 Handles selection of the current menu item and switches the display to the appropriate screen
 *
 * @param none
 * @return none
 */
void AccessCtlDisplay::selectItem(void)
{
	switch (currentScreen)
	{
	case MENU_SCREEN:
	{
		if (mainMenuPage == 0)
		{
			switch (SELECTED_MENU_ITEM)
			{
			case 0:
				currentScreen = DEFAULT_SCREEN;
				currentMenuMax = DEFAULT_MAX;
				break;
			case 1:
				currentScreen = FINGERPRINT_DB_SCREEN;
				currentMenuMax = FINGERPRINT_DB_MENU_MAX;
				break;
			case 2:
				currentScreen = DOOR_SCREEN;
				currentMenuMax = DOOR_MENU_MAX;
			default:
				break;
			}
		}
		else if (mainMenuPage == 1)
		{
			switch (SELECTED_MENU_ITEM)
			{
			case 0:
				currentScreen = FINGERPRINT_DB_SCREEN;
				currentMenuMax = FINGERPRINT_DB_MENU_MAX;
				break;
			case 1:
				currentScreen = DOOR_SCREEN;
				currentMenuMax = DOOR_MENU_MAX;
				break;
			case 2:
				clearScreen();
				currentScreen = PASS_SCREEN;
				currentPinScreen = CURRENT_PIN_SCREEN;
				currentMenuMax = DEFAULT_MAX;
			default:
				break;
			}
		}
		SELECTED_MENU_ITEM = 0;
		break;
	}
	case FINGERPRINT_DB_SCREEN:
	{
		switch (SELECTED_MENU_ITEM)
		{
		case 0:
			currentScreen = MENU_SCREEN;
			currentMenuMax = MAIN_MENU_MAX;
			break;
		case 1:
			currentScreen = ADD_FINGERPRINT_SCREEN;
			currentMenuMax = DEFAULT_MAX;
			addFingerCurrentStep = INITIAL_CAPTURE_PROMPT;
			break;
		case 2:
			currentScreen = RM_FINGERPRINT_SCREEN;
			currentMenuMax = DEFAULT_MAX;
		default:
			break;
		}
		SELECTED_MENU_ITEM = 0;
		break;
	}
	case DOOR_SCREEN:
	{
		switch (SELECTED_MENU_ITEM)
		{
		case 0:
			currentScreen = MENU_SCREEN;
			currentMenuMax = MAIN_MENU_MAX;
			break;
		case 1:
			currentScreen = DOOR_OPEN_SCREEN;
			currentMenuMax = DOOR_OPEN_MAX;
			break;
		case 2:
			currentScreen = DOOR_CLOSE_SCREEN;
			currentMenuMax = DOOR_CLOSE_MAX;
		default:
			break;
		}
		SELECTED_MENU_ITEM = 0;
		break;
	}
	case DOOR_OPEN_SCREEN:
	{
		switch (SELECTED_MENU_ITEM)
		{
		case 0:
			currentScreen = DOOR_SCREEN;
			currentMenuMax = DOOR_MENU_MAX;
			break;
		case 1:
			currentScreen = DOOR_SCREEN;
			currentMenuMax = DOOR_MENU_MAX;
			break;
		default:
			break;
		}
		SELECTED_MENU_ITEM = 0;
		break;
	}
	case DOOR_CLOSE_SCREEN:
	{
		switch (SELECTED_MENU_ITEM)
		{
		case 0:
			currentScreen = DOOR_SCREEN;
			currentMenuMax = DOOR_MENU_MAX;
			break;
		case 1:
			currentScreen = DOOR_SCREEN;
			currentMenuMax = DOOR_MENU_MAX;
			break;
		default:
			break;
		}
		SELECTED_MENU_ITEM = 0;
		break;
	}
	default:
		break;
	}
}

/**
 * @brief	Returns the current step in the fingerprint registration process
 *
 * @param none
 * @return AddFingerSteps_t
 */
AddFingerSteps_t AccessCtlDisplay::getEnrollFingerStep(void)
{
	return addFingerCurrentStep;
}

/**
 * @brief	Sets the current step in the fingerprint registratin process to the step specified
 *
 *
 * @param step
 * @return none
 */
void AccessCtlDisplay::setEnrollFingerStep(AddFingerSteps_t step)
{
	addFingerCurrentStep = step;
	switch (step)
	{
	case CAPTURE_SUCCESS:
	case CAPTURE_ERROR:
	case CONVERSION_ERROR:
	case MATCH_ERROR:
	case SAVE_SUCCESS:
	case SAVE_ERROR:
		info_screen_timing = get_timing_millis();
		break;

	default:
		break;
	}
}
