/**
 * @file 		access_ctl_keypad.h
 *
 * @author 		Stephen Kairu (kairu@pheenek.com)
 *
 * @brief	    This file contains the definitions for a Keypad class which controls interactions
 *            with the low-level keypad driver
 *
 * @version 	0.1
 *
 * @date 		2023-09-16
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
#ifndef ACCESS_CTL_KEYPAD_H
#define ACCESS_CTL_KEYPAD_H

#include "access_ctl_keypad_driver.h"

/**
 * Enumeration defining the available keypad states
 */
typedef enum
{
    IDLE_STATE,      /*< Keypad idle, doesn't respond to events */
    DEFAULT_STATE,   /*< Default keypad state on start-up */
    PIN_STATE,       /*< Keypad set to accept PIN input (4-digit code) */
    NAVIGATION_STATE /*< Keypad set to navigate menus 2, 4, 6, 8*/
} KeypadStates_t;

class AccessCtlKeypad
{
private:
    KeypadStates_t currentKeypadState = DEFAULT_STATE; /*< Variable to keep track of the current keypad state */
public:
    /**
     * @brief	Keypad constructor
     *        Calls the keypad_setup function to set up the low-level driver
     *
     * @param none
     * @return none
     */
    AccessCtlKeypad(void);
    ~AccessCtlKeypad(void) {}

    /**
     * @brief	 Function to attach a callback to a keypad event
     *
     * @param callback
     * @return none
     */
    void attachKeypadCallback(void (*callback)(char, KeyEdge_t));

    /**
     * @brief	 Getter function for the current keypad state
     *
     * @param none
     * @return KeypadStates_t
     */
    KeypadStates_t getCurrentKeypadState(void);

    /**
     * @brief	 Setter function for the current keypad state
     *
     * @param keypadState
     * @return none
     */
    void changeKeypadToState(KeypadStates_t keypadState);
};

#endif
