/**
 * @file 		AccessExitBtn.cpp 
 * 
 * @author 		Stephen Kairu (kairu@pheenek.com) 
 * 
 * @brief	    This files contains the implementations of the exit button interface
 * 
 * @version 	0.1 
 * 
 * @date 		2023-09-23
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
#include "AccessExitBtn.h"

/**
 * @brief	Constructor. Initializes the exit button peripheral interface
 * 
 * @param none
 * @return none
 */
AccessCtlExitBtn::AccessCtlExitBtn(void)
{
  exit_btn_init();
}

/**
 * @brief	 Checks whether the exit button is activated
 *          Returns true if the exit button is activated (pressed)
 * 
 * @return true 
 * @return false 
 */
bool AccessCtlExitBtn::isActivated(void)
{
  return (exit_btn_status() == EXIT_ACTIVATED);
}

/**
 * @brief	 Checks whether the exit button is not activated
 *          Returns true if the exit button is deactivated (not pressed)
 * 
 * @return true 
 * @return false 
 */
bool AccessCtlExitBtn::isNotActivated(void)
{
  return (exit_btn_status() == EXIT_DEACTIVATED);
}

/**
 * @brief	 Sets the callback function to be called when an exit button event occurs
 * 
 * @param callback 
 * @return none
 */
void AccessCtlExitBtn::attachExitCallback(void (*callback)(void))
{
  attach_exit_event_callback(callback);
}
 
