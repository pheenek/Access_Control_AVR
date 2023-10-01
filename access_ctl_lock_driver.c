/**
 * @file 		access_ctl_lock_driver.c 
 * 
 * @author 		Stephen Kairu (kairu@pheenek.com) 
 * 
 * @brief	    This file contains implementations for the low-level solenoid lock driver
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
#include "access_ctl_lock_driver.h"

/**
 * @brief	 Initializes the solenoid lock hardware
 * 
 * @param none
 * @return none
 */
void lock_init(void)
{
  // set the lock pin as an output
  DDRB |= (1 << DDB5);
}

/**
 * @brief	 Energizes the solenoid lock, unlatching the door
 * 
 * @param none
 * @return none
 */
void open_lock(void)
{
  PORTB |= (1 << PORTB5);
}

/**
 * @brief	 De-energizes the solenoid lock, latching the door
 * 
 * @param none
 * @return none
 */
void close_lock(void)
{
  PORTB &= ~(1 << PORTB5);
}
