/**
 * @file 		access_exit_btn_driver.h 
 * 
 * @author 		Stephen Kairu (kairu@pheenek.com) 
 * 
 * @brief	    This file contains the definitions of the exit button low-level driver
 *              When exiting the access-controlled space, one should not have to perfrom verification
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
#ifndef ACCESS_CTL_EXIT_BTN_DRIVER_H
#define ACCESS_CTL_EXIT_BTN_DRIVER_H

#include "global_inc.h"

/**
 * Enumeration defining all possible exit button states
 */
typedef enum EXIT {
  EXIT_DEACTIVATED,
  EXIT_ACTIVATED
} ExitBtnStatus_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief	 Initializes the exit button hardware
 * 
 * @param none
 * @return none
 */
void exit_btn_init(void);

/**
 * @brief	 Returns the current button status (activated/deactivated, pressed/not-pressed)
 * 
 * @param none
 * @return ExitBtnStatus_t 
 */
ExitBtnStatus_t exit_btn_status(void);

/**
 * @brief	 Sets the function to be called when an exit button event is detected
 * 
 * @param callback 
 * @return none
 */
void attach_exit_event_callback(void (*callback)(void));

#ifdef __cplusplus
}
#endif

#endif
 
