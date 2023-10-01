/**
 * @file 		access_exit_btn_driver.c 
 * 
 * @author 		Stephen Kairu (kairu@pheenek.com) 
 * 
 * @brief	    This file contains the implementations of the exit button low-level druver
 *              When exiting the access-controlled space, one should not have to perform verification
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
#include "access_exit_btn_driver.h"

void (*exit_event_callback)(void); /*< Stores the callback function for exit button events */

/**
 * @brief	 Initializes the exit button hardware
 * 
 * @param none
 * @return none
 */
void exit_btn_init(void)
{
  // Set exit button pin as an input
  DDRD &= ~(1 << DDD3);
  // any logical change generates an interrupt
  EICRA |= (1 << ISC10);
  // enable interrupt on contact sensor pin INT1
  EIMSK |= (1 << INT1);
}

/**
 * @brief	 Returns the current button status (activated/deactivated, pressed/not-pressed)
 * 
 * @param none
 * @return ExitBtnStatus_t 
 */
ExitBtnStatus_t exit_btn_status(void)
{
  if (bit_is_clear(PIND, PIND3))
  {
    return EXIT_ACTIVATED;
  }

  return EXIT_DEACTIVATED;
}

/**
 * @brief	 Sets the function to be called when an exit button event is detected
 * 
 * @param callback 
 * @return none
 */
void attach_exit_event_callback(void (*callback)(void))
{
  exit_event_callback = callback;
}

/**
 * @brief	ISR for detecting and responding to exit button events
 */
ISR(INT1_vect)
{
  if (!exit_event_callback) return;
  
  if (bit_is_clear(PIND, PIND3))
  {
    exit_event_callback();
  }
}
 
