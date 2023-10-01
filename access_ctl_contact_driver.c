/**
 * @file 		access_ctl_contact_driver.c
 *
 * @author 		Stephen Kairu (kairu@pheenek.com)
 *
 * @brief	    This file contains the implementations of a low-level driver for a
 *            magnetic contact switch sensor
 *
 * @version 	0.1
 *
 * @date 		2023-09-20
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
#include "access_ctl_contact_driver.h"

void (*contact_event_callback)(ContactEvent_t); /*< Variable to hold the pointer to the high-level function callback */

/**
 * @brief	 Initializes the magnetic contact sensor hardware
 *
 * @param none
 * @return none
 */
void contact_sensor_init(void)
{
    // Set contact sensor pin as an input
    DDRD &= ~(1 << DDD2);
    // any logical change generates an interrupt
    EICRA |= (1 << ISC00);
    // enable interrupt on contact sensor pin INT0
    EIMSK |= (1 << INT0);
}

/**
 * @brief	 Attaches a callback to a high-level function to be executed when events occur
 *
 * @param callback
 * @return none
 */
void attach_contact_event_callback(void (*callback)(ContactEvent_t event))
{
    contact_event_callback = callback;
}

/**
 * @brief	 Returns the current status of the contact sensor, and hence the door
 *        A low level means that the two contacts are in close proximity.
 *
 * @param none
 * @return ContactEvent_t
 */
ContactEvent_t door_status(void)
{
    if (bit_is_clear(PIND, PIND2))
    {
        return DOOR_CLOSED;
    }
    else
    {
        return DOOR_OPEN;
    }
}

/**
 * @brief	ISR for detecting and responding to a change in the state of the magnetic switch sensor
 */
ISR(INT0_vect)
{
    if (!contact_event_callback)
        return;

    if (bit_is_clear(PIND, PIND2))
    {
        contact_event_callback(DOOR_CLOSED);
    }
    else
    {
        contact_event_callback(DOOR_OPEN);
    }
}
