/**
 * @file 		access_ctl_keypad.cpp 
 * 
 * @author 		Stephen Kairu (kairu@pheenek.com) 
 * 
 * @brief	    This file contains the implementations for a Keypad class which controls interactions
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
#include "access_ctl_keypad.h"

/**
 * @brief	Keypad constructor
 *        Calls the keypad_setup function to set up the low-level driver
 * 
 * @param none
 * @return none
 */
AccessCtlKeypad::AccessCtlKeypad(void)
{
  keypad_setup();
}

/**
 * @brief	 Function to attach a callback to a keypad event
 * 
 * @param callback 
 * @return none
 */
void AccessCtlKeypad::attachKeypadCallback(void (*callback)(char, KeyEdge_t))
{
  attach_event_callback(callback);
}

/**
 * @brief	 Getter function for the current keypad state
 * 
 * @param none
 * @return KeypadStates_t 
 */
KeypadStates_t AccessCtlKeypad::getCurrentKeypadState(void)
{
  return currentKeypadState;
}

/**
 * @brief	 Setter function for the current keypad state
 * 
 * @param keypadState 
 * @return none
 */
void AccessCtlKeypad::changeKeypadToState(KeypadStates_t keypadState)
{
  currentKeypadState = keypadState;
}
 
